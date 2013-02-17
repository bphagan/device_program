/*****************************************************************************
** pu_irom_sd.c
**
** Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
**
** This file contains copyrighted material. Use of this file is
** restricted by the provisions of a Freescale Software License
** Agreement, which has either been electronically accepted by
** you or has been expressly executed between the parties.
**
** Description: Explanation for the usage of this file.
**
** Revision History:
** -----------------
*****************************************************************************/

/*!
 * @file pu_irom_sd.c
 *
 * @brief source code for the mmc card operation
 *
 * @ingroup mmc
 */

/*=================================================================================
                                        INCLUDE FILES
==================================================================================*/
#include "pu_irom_sdhc_ip.h"
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UINT32 sd_get_rca (void);
static UINT32 sd_get_bit_mode_support(void);
static UINT32 sd_set_bus_width (UINT32);
                                
/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
#define SD_OCR_VALUE 0x80ff8000
#define RCA_SHIFT 16
#define SD_R1_STATUS_APP_CMD_MSK 0x20
#define BIT_MODE_4_SUPPORT 5
#define SD_BUS_WIDTH_OFFSET 6
#define BIT_4_MODE 4
#define SD_STATUS_LEN 64
/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/

/*==========================================================================
                                     Global FUNCTIONS
==========================================================================*/
/*!
 * initialize the SD memory card.
 * @bus_width
 * @return 
 * int - SUCCESS (TRUE) or  FAIL
 */

UINT32 sd_init(UINT32 bus_width)
{
    UINT32 status = FAIL; 
	
    /* Get CID number of SD Memory Card */
    if(!card_get_cid ())
    {
        /* Set RCA of the SD Card */
        if(!sd_get_rca())
        {
            /*Enable operating frequency */
            interface_configure_clock(OPERATING_FREQ);

            /*Put SD Card in Transfer State */
            if(!card_set_data_transfer_mode ())
            {
                /* Set Bus width of the device */
                status = SUCCESS; 
             }
        }
    }
	
    return status;
	
}

/*!
 * validate the operating volatge range of the SD Memory card.
 * 1.Issue CMD55 to SD card with RCA value with default RCA i.e. 0x0000 
 * 2. Issue ACMD41 with argument value specified in specification.
 * 2.Read the command response.
 * 3.Compare the response value with standard value specified in specification.
 * 4.if it is not in the range send R15 command to put in in-active state.
 * @return
   int - voltage range
 */

UINT32 sd_voltage_validation (void)
{
    command_t cmd;
    command_response_t response;
    UINT32 voltage_validation_command =0;
    UINT32 default_rca = 0;
    UINT32 ocr_value=0;
    UINT32 voltage_validation = FAIL;
	
    while((voltage_validation_command < MMCSD_READY_TIMEOUT) && (voltage_validation != SUCCESS)) 
    {
        /* Configure CMD55 for SD card */
        /* This command expects defualt RCA 0x0000 as argument.*/
        card_command_config(&cmd,CMD55,default_rca,READ,RESPONSE_48,
                                  DATA_PRESENT_NONE,ENABLE,ENABLE);
	                    
	           
        /* Issue CMD55 to SD Memory card*/
        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
            voltage_validation = FAIL;
            break;
        }
        else
        {
            /* Configure ACMD41 for SD card */
            /* This command expects operating voltage range as argument.*/
	
            ocr_value = ((UINT32)(SD_OCR_VALUE) & 0xFFFFFFFF);
		
            card_command_config(&cmd,ACMD41,ocr_value,READ,RESPONSE_48_WITHOUT_CRC,DATA_PRESENT_NONE,DISABLE,DISABLE);
		
            /* Issue ACMD41 to SD Memory card to determine OCR value */
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
                voltage_validation = FAIL;
                break;
            }
            else
            {
                /* Read Response from CMDRSP0 Register */
                response.format = RESPONSE_48;
                interface_read_response(&response);
			
                /* Obtain OCR Values from the response */
                /* Obtain OCR value from the response buffer
                */
                ocr_value = response.cmd_rsp0;
		
                /* Check if volatge lies in range or not*/
                if((ocr_value & MMC_OCR_VALUE_MASK) == MMC_OCR_VALUE_MASK)
                {
                    /* Check if card busy bit is cleared or not */
                    if(!(response.cmd_rsp0 & CARD_BUSY_BIT))
                    {
                        /* Iterate One more time */
                        voltage_validation_command++;
                    }
                    else
                    {
                        voltage_validation = SUCCESS;
                    }
                }
            }
        }
    }
	
    return voltage_validation;
}

/*!
 * return RCA published from SD Memory Card.
 * 1.Send Command CMD3 with No Argument
 * 2.SD Memory card will publish its RCA which will be used for future references.
 * 3. Check for card current state. 
 * @return 
 * UINT32
 */
static UINT32 sd_get_rca (void)
{
    command_t cmd;
    UINT32 card_state=0;
    UINT32 rca_request=0;
    command_response_t response;
	
    /* Configure CMD3 for MMC card */
    /* 32bit card address is expected as Argument */
    card_command_config(&cmd,CMD3,NO_ARG,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	                             
    /* Get relative address of the card
     */
     
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        rca_request = FAIL;
    }
    else
    {
        /* Read Command response */
        response.format = RESPONSE_48; 
        interface_read_response (&response);
		
        Card_rca = ((UINT32) (response.cmd_rsp0 >> RCA_SHIFT));
		
        card_state = (((UINT32) (response.cmd_rsp0 & MMCSD_R1_STATUS_CURR_STATE)) >> CURR_STATE_SHIFT);
	
        if(card_state == IDENT)
        {
            rca_request = SUCCESS;
			
        }
        else		
        {
            rca_request = FAIL;
        }
    }
		
	return rca_request;
}

/*!
 * read SD SCR register information.
 * @return
 * UINT32
 */

static UINT32 sd_get_bit_mode_support(void)
{
    command_t cmd;
    UINT32 rd_data_buff[128];
    UINT32 bit4_mode_support;
    command_response_t response;
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
    /* Configure CMD55 for SD card */
    /* This command expects RCA as argument.*/
    card_command_config(&cmd,CMD55,card_address,READ,RESPONSE_48,
                                  DATA_PRESENT_NONE,ENABLE,ENABLE);
	                                  	           
    /* Issue CMD55 to SD Memory card*/
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        bit4_mode_support = 0;
    }
    else
    {
        /* Read Command response */
        response.format = RESPONSE_48;
        interface_read_response (&response);
		
        /* Afetr giving ACMD Command, the R1 response should have
         * STATUS_APP_CMD set
	 */
        if(response.cmd_rsp0 & SD_R1_STATUS_APP_CMD_MSK)
	{
			
	    /* Configure ACMD51 for SD card */
	    /* This command expects No argument.*/
			
            card_command_config(&cmd,ACMD51,NO_ARG,READ,RESPONSE_48,DATA_PRESENT,ENABLE,ENABLE);
		
            /* Issue ACMD51 to SD Memory card */
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
                bit4_mode_support = 0;
            }
            else
            {
                /* Read Response from e-SDHC buffer */
                interface_data_read(rd_data_buff,512);
				
                /* Check for bus width supported */
                bit4_mode_support = (rd_data_buff[SD_BUS_WIDTH_OFFSET] & BIT_MODE_4_SUPPORT);
				
                if(bit4_mode_support)
                {
                    bit4_mode_support = BIT_4_MODE;
                }
				
            }
        }
    }
	
    return bit4_mode_support;
}


/*!
 * set bus width of SD Memory Card.
 * 1. Check if the value of data bus width 4 is supported or not? 
 * 2. if bus width request is 4 ot 1
 * 3. if request is for 4 bit and data bus width of 4 bit is
 *     is not supported than Report error that SD Card doesnt support 
 *     multiple bit width pattern.
 * 4. send ACMD6 with argument 00 for 1 bit and 10 for 4 bit mode
 * 5. send ACMD13 to check whether required bus width is set or not.
 * @bus_width
 * @return
 * UINT32
 */

static UINT32 sd_set_bus_width (UINT32 bus_width)
{
    command_t cmd;
    UINT32 set_bus_width_status=0;
    command_response_t response;
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
    if ((bus_width == FOUR ) || (bus_width == ONE))
    {
        /* Configure CMD55 for SD card */
        /* This command expects RCA as argument.*/
		
        card_command_config(&cmd,CMD55,card_address,READ,RESPONSE_48,
	                                  DATA_PRESENT_NONE,ENABLE,ENABLE);
		                    
		           
        /* Issue CMD55 to SD Memory card*/
        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
            set_bus_width_status = FAIL;
        }
        else
        {
            /* Read Command response */
            response.format = RESPONSE_48;
            interface_read_response (&response);
			
            /* Afetr giving ACMD Command, the R1 response should have
             * STATUS_APP_CMD set
             */
            if(response.cmd_rsp0 & SD_R1_STATUS_APP_CMD_MSK)
            {
			                          
                bus_width = (bus_width>>ONE);
				
                /* Configure ACMD6 for SD card */
		/* This command expects argument 00 for 1 bit mode support.*/
	        /* 10 for 4 bit mode support*/
                card_command_config(&cmd,ACMD6,bus_width,READ,RESPONSE_48,DATA_PRESENT_NONE,ENABLE,ENABLE);
		        
		       
                /* Issue ACMD6 to SD Memory card*/
                if(interface_send_cmd_wait_resp(&cmd) == FAIL)
                {
                    set_bus_width_status = FAIL;
                }
				
                else
                {
                    set_bus_width_status = SUCCESS;
                }
            }
        }
    }
	
    return set_bus_width_status;	
}
