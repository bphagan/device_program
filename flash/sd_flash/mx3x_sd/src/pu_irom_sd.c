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
 * @brief source code for the sd card operation
 *
 * @ingroup sd
 */

//#define TY_DBG

/*=================================================================================
                                        INCLUDE FILES
==================================================================================*/
#include "pu_irom_sdhc_ip.h"
#include "pu_irom_card.h"
#include "pu_irom_sd.h"
#include "protocol.h"
#include "flash_lib.h"
#include "stdio.h"

#ifdef TY_DBG
#include "channel.h"
#endif

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UINT32 sd_get_rca (void);
static UINT32 sd_get_bit_mode_support(void);
static UINT32 sd_set_bus_width (UINT32);
static UINT32 sd_get_card_capacity(UINT32 *capacity);
                                
/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
#define RCA_SHIFT 16
#define SD_R1_STATUS_APP_CMD_MSK 0x20
#define BIT_MODE_4_SUPPORT 5
#define SD_BUS_WIDTH_OFFSET 6
#define BIT_4_MODE 4
#define SD_STATUS_LEN 64

/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
UINT32 address_mode; /* Global variable for addressing mode */

static UINT32 g_u32Capacity = 0;
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
    //UINT32 status = -10;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_init\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif
    

    /* Get CID number of SD Memory Card */
    if(!card_get_cid ())
    {
        //status = -11;
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Get cid success!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        /* Set RCA of the SD Card */
        if (!sd_get_rca())
        {
            //status = -12;
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Get rca success!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
            if (!sd_get_card_capacity(&g_u32Capacity))
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, get card capacity success!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
            }
            else
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, get card capacity failed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
            }

            /*Put SD Card in Transfer State */
            if (!card_set_data_transfer_mode ())
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, set transfer mode success!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
                /* Set Bus width of the device */
                status = SUCCESS; 
            }
            else
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, set transfer mode failed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
            }
        }
    }

    /*Enable operating frequency */
    interface_configure_clock(OPERATING_FREQ);

	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_init, status: %d\n", status);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return status;
}

/*!
 * read data from SD card for specified length 
   from specified offset and copy it a dest pointer.
 * 1. Issue Commnand CMD16 to set block length as 512 bytes.
 * 2. Issue Command CMD17 to read single block.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 sd_data_read (UINT32 *dest_ptr,UINT32 length,UINT32 offset,dump_callback callback)
{
    command_t cmd;
    int len;
    UINT32 read_block_status=SUCCESS;
    U16 csum;
	
    /* Assing length of data to be read */
    len = length;
   
    if(address_mode == SECT_MODE)  
    {
        offset /= BLK_LEN;
    }    
    /* Configure interface block and number of blocks */
    interface_config_block_info(BLK_LEN, ONE);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd, CMD16, BLK_LEN, READ, RESPONSE_48,
                    DATA_PRESENT_NONE, ENABLE, ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if (interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        read_block_status = FAIL;
    }
    else
    {
        while (len > 0 && !read_block_status) 
        {
            
            /* Comfigure command CMD17 for single block read */	
            card_command_config(&cmd, CMD17, offset, READ, RESPONSE_48,
	                        DATA_PRESENT, ENABLE, ENABLE);	
			
            if (interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
				
                read_block_status = FAIL;
            }
            else
            {
                /* Call interface Data read function */
                read_block_status = interface_data_read(dest_ptr, BLK_LEN);
				
                /*decrement length by block size */
                len = len - BLK_LEN;
				
                /* Increment offset by Block Size */
		        address_mode == SECT_MODE ? (offset++) : (offset +=  BLK_LEN);

		        /* send the dump status and data to host */
		        if(callback)
                {
		 	        if(len > 0)
                    {
				        csum = calculate_checksum((u8 *)dest_ptr, BLK_LEN);
				        callback((u8 *)dest_ptr, FLASH_PARTLY, csum, BLK_LEN);
			        }
                    else
                    {
				        csum = calculate_checksum((u8 *)dest_ptr, len + BLK_LEN );
				        callback((u8 *)dest_ptr, FLASH_PARTLY, csum, len + BLK_LEN);
			        }
		        }
                /* Increment Destination pointer */
                dest_ptr = dest_ptr + (BLK_LEN / FOUR);
            }
        }
    }

    return read_block_status;
}

/*!
 * write data from buffer to SD card for specified length  
 * from specified offset and copy it a dest pointer.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 sd_data_write (UINT32 *dest_ptr,UINT32 length,UINT32 offset,response_callback callback)
{
    command_t cmd;
    int len;
    UINT32 write_block_status=SUCCESS;
	
    /* Assing length of data to be read */
    len = length;
    
    if (address_mode == SECT_MODE)  
    {
        offset /= BLK_LEN;
    }
     /* Configure interface block and number of blocks */
    interface_config_block_info(BLK_LEN,ONE);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd,CMD16,BLK_LEN,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if (interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        write_block_status = FAIL;
    }
    else
    {
        while (len > 0 && !write_block_status) 
        {
			
            /* Comfigure command CMD24 for single block write */	
            card_command_config(&cmd,CMD24,offset,WRITE,RESPONSE_48,
	                        DATA_PRESENT,ENABLE,ENABLE);	
			
            if (interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
                write_block_status = FAIL;
            }
            else
            {
                /* Call interface write read function */
                write_block_status = interface_data_write(dest_ptr, BLK_LEN);
				
                /*decrement length by block size */
                len = len - BLK_LEN;
				
                /* Increment offset by Block Size */
		        address_mode == SECT_MODE ? (offset++) : (offset +=  BLK_LEN);

		        /* send the prg status to host */
		        if(callback)
			        callback(FLASH_PARTLY, offset, BLK_LEN);
		  
                /* Increment Destination pointer */
                dest_ptr = dest_ptr + (BLK_LEN / FOUR);
            }
        }
    }

    return write_block_status;
}

/*!
 * erase data from card for specified length 
 * from specified offset
 * 1. Issue Commnand CMD32 to set first block to erase
 * 2. Issue Command CMD33 to set end block to erase  
 * 3. Issue Command CMD38 to start erase 
 *
 * @param [in] offset offset in SD card from which erase starts.
 * @param [in] size   size to erase. 
 * @return
 * Return result in UINT32 format.
 */
UINT32 sd_data_erase (UINT32 offset, UINT32 size)
{
	command_t cmd;
	U8 startEraseBlockCmd = CMD32; 
	U8 endEraseBlockCmd   = CMD33;
	UINT32 startBlock = offset / BLK_LEN; 
	UINT32 endBlock   = (offset + size) / BLK_LEN;
	U32 ret;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_data_erase\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

	if (address_mode != SECT_MODE) 
    {
        /* Byte mode, erase by sectors in both mode */
        startBlock *= BLK_LEN;
		endBlock   *= BLK_LEN;
   	}
	
	/* Configure start erase command to set first block*/
	card_command_config(&cmd,startEraseBlockCmd, startBlock, SD_COMMAND, RESPONSE_48,
                    DATA_PRESENT_NONE, ENABLE,ENABLE);
    	/* wait response */
	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty: Send CMD32 succeed!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
    	/* Configure end erase command to set end block*/
		card_command_config(&cmd, endEraseBlockCmd, endBlock, SD_COMMAND, 
                        RESPONSE_48, DATA_PRESENT_NONE, ENABLE,ENABLE);
    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
        {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty: Send CMD33 succeed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
		    /* Comfigure command to start erase*/	
        	card_command_config(&cmd, CMD38, 0, SD_COMMAND, RESPONSE_48,
	                              DATA_PRESENT_NONE, ENABLE, ENABLE);
	    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty: Send CMD38 succeed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
	    		//wait for completion
				return ret;             	
           	}
            else
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty: Send CMD38 failed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
            }
	   	}
        else
        {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty: Send CMD33 failed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
        }
	}
    else
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty: Send CMD32 failed!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
    }
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_data_erase, ret:%d\n", ret);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

	return ret;
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
    //UINT32 voltage_validation = -30;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_voltage_validation\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    while ((voltage_validation_command < MMCSD_READY_TIMEOUT) && (voltage_validation != SUCCESS)) 
    //while (voltage_validation != SUCCESS)
    {
        /* Configure CMD55 for SD card */
        /* This command expects defualt RCA 0x0000 as argument.*/
        card_command_config(&cmd,CMD55,default_rca,READ,RESPONSE_48,
                                  DATA_PRESENT_NONE,ENABLE,ENABLE);
	                    
	           
        /* Issue CMD55 to SD Memory card*/
        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Use ACMD failed\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
            voltage_validation = FAIL;
            //voltage_validation = -31;
            break;
        }
        else
        {
            /* Configure ACMD41 for SD card */
            /* This command expects operating voltage range as argument.*/

#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Use ACMD succeed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif

            ocr_value = ((UINT32)(SD_OCR_VALUE) & 0xFFFFFFFF);
		
            card_command_config(&cmd,ACMD41,ocr_value,READ,RESPONSE_48_WITHOUT_CRC,DATA_PRESENT_NONE,DISABLE,DISABLE);
		
            /* Issue ACMD41 to SD Memory card to determine OCR value */
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, Get OCR failed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
                voltage_validation = FAIL;
                //voltage_validation = -32;
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
                if((ocr_value & SD_OCR_VALUE_MASK) == SD_OCR_VALUE_MASK)
                {
#ifdef TY_DBG
	                {
		                // Terry adds for debug, :-)
		                U8 au8StrBuf[100] = { 0 };
		                sprintf(au8StrBuf, "Ty, Get OCR succeed!\n");
		                atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	                }
#endif

                    /* Check if card busy bit is cleared or not */
                    if(!(response.cmd_rsp0 & CARD_BUSY_BIT))
                    {
                        /* Iterate One more time */
                        voltage_validation_command++;
                    }
                    else
                    {
                        
                        if ((response.cmd_rsp0 & SD_OCR_HC_RES) == SD_OCR_HC_RES)
                        {
                            voltage_validation = SUCCESS;
                            address_mode = SECT_MODE;
                        }
                        else if((response.cmd_rsp0 & SD_OCR_LC_RES) == SD_OCR_LC_RES)
                        {
                            voltage_validation = SUCCESS;
                            address_mode = BYTE_MODE;
                        }
                    }
                }
            }
        }
    }
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_voltage_validation, v_v:%d\n", voltage_validation);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

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
	
    /* Configure CMD3 for SD card */
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
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Card_rca:%d\n", Card_rca);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

        card_state = (((UINT32) (response.cmd_rsp0 & SD_R6_STATUS_CURR_STATE)) >> CURR_STATE_SHIFT);
	
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
 * Get SD card capacity.
 * Issue Commnand CMD9 to get card CSD.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 sd_get_capacity(UINT32 *capacity)
{
    if (NULL == capacity)
    {
        return -1;
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: sd_get_capacity(),capacity:%d", g_u32Capacity);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    *capacity = g_u32Capacity;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: sd_get_capacity()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return 0;
}

static UINT32 sd_get_card_capacity(UINT32 *capacity)
{
    command_t cmd;
    command_response_t response;
    card_specific_data csd;
    UINT32 u32Read_BL_Len = 0;
    S32    i32C_Size = 0;
    S32    i32C_Size_Mult = 0;
    UINT32 u32CSD_Structure = 0;
    S32    result = 0;
    UINT32 u32Capacity = 0;
    UINT32 card_address = (Card_rca << RCA_SHIFT);

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: sd_get_card_capacity()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    if (NULL == capacity)
    {
        return -1;
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Card_rca:%d card_address:%d", Card_rca, card_address);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Configure CMD9 for SD card */
    /* 16bit card address is expected as Argument */
    card_command_config(&cmd,CMD9,card_address, READ, RESPONSE_136,
                    DATA_PRESENT_NONE, ENABLE, DISABLE);
	
	
    /* Issue Command CMD9 to Extrace CSD register contents
     */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
	    	U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, send CMD9 failed!");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        result = -1;
    }
    else
    {
        /* Read Command response */
        response.format = RESPONSE_136;
        interface_read_response (&response);
		
        /* Assign Response to CSD Strcuture */
        csd.csd0 = response.cmd_rsp0;
	    csd.csd1 = response.cmd_rsp1;
	    csd.csd2 = response.cmd_rsp2;
	    csd.csd3 = response.cmd_rsp3;
	    
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty,csd0:%d,csd1:%d,csd2:%d,csd3:%d\n", (UINT32)csd.csd0, (UINT32)csd.csd1, (UINT32)csd.csd2, (UINT32)csd.csd3);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

	    u32CSD_Structure = ((csd.csd3 & SD_CSD_CSD_STRUCTURE_MASK) >> SD_CSD_CSD_STRUCTURE_OFFSET);
        u32Read_BL_Len   = ((csd.csd2 & SD_CSD_READ_BL_LEN_MASK) >> SD_CSD_READ_BL_LEN_OFFSET);

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, CSD Ver:%d, Read_BL_Len:%d\n", u32CSD_Structure, u32Read_BL_Len);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        switch (u32CSD_Structure)
        {
            case 0:
                /* CSD Version 1.0 */
                {
                    if (u32Read_BL_Len < 9 || u32Read_BL_Len > 11)
                    {
                        return -2;
                    }
                    i32C_Size = ((csd.csd1 & SD_CSD_VER1_C_SIZE_PART1_MASK) >> SD_CSD_VER1_C_SIZE_PART1_OFFSET) | ((csd.csd2 & SD_CSD_VER1_C_SIZE_PART2_MASK) >> SD_CSD_VER1_C_SIZE_PART2_OFFSET << SD_CSD_VER1_C_SIZE_PART1_LEN);
                    i32C_Size_Mult = ((csd.csd1 & SD_CSD_C_SIZE_MULT_MASK) >> SD_CSD_C_SIZE_MULT_OFFSET);

                    /* memory capacity = BLOCKNR * BLOCK_LEN */
                    /* Where BLOCKNR = (C_SIZE + 1) * MULT
                        MULT = 2^(C_SIZE_MULT+2)
                        BLOCK_LEN = 2^READ_BL_LEN */
                    u32Capacity = (UINT32)((long long)((i32C_Size + 1) * (1 << (i32C_Size_Mult + 2))) * (long long)(1 << u32Read_BL_Len) >> 10); /* >>10 to get kbytes */

#ifdef TY_DBG
	                {
		                // Terry adds for debug, :-)
		                U8 au8StrBuf[100] = { 0 };
		                sprintf(au8StrBuf, "Ty, C_Size:%d,C_Size_Mult:%d,Capacity:%d\n", i32C_Size, i32C_Size_Mult, u32Capacity);
		                atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	                }
#endif
                    *capacity = u32Capacity;
                }
                break;
            case 1:
                /* CSD Version 2.0 */
                {
                    if (u32Read_BL_Len != 9)
                    {
                        return -2;
                    }
                    i32C_Size = ((csd.csd1 & SD_CSD_VER2_C_SIZE_PART1_MASK) >> SD_CSD_VER2_C_SIZE_PART1_OFFSET) | ((csd.csd2 & SD_CSD_VER2_C_SIZE_PART2_MASK) >> SD_CSD_VER2_C_SIZE_PART2_OFFSET << SD_CSD_VER2_C_SIZE_PART1_LEN);
                    u32Capacity = (i32C_Size + 1) * 512;
#ifdef TY_DBG
	                {
		                // Terry adds for debug, :-)
		                U8 au8StrBuf[100] = { 0 };
		                sprintf(au8StrBuf, "Ty, C_Size:%d,Capacity:%d\n", i32C_Size, u32Capacity);
		                atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	                }
#endif
                    *capacity = u32Capacity;
                }
                break;
            default:
                /* Reserved version, not recognized */
                result = -2;
                break;
        }
    }
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_get_card_capacity()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return result;
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
