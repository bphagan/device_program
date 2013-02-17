/*****************************************************************************
** pu_irom_mmc.c
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
 * @file pu_irom_mmc.c
 *
 * @brief source code for the mmc card operation
 *
 * @ingroup mmc
 */

//#define TY_DBG

/*==================================================================================
                                        INCLUDE FILES
==================================================================================*/
#include <stdio.h>
#include "pu_irom_sdhc_ip.h"
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"
#include "protocol.h"
#include "flash_lib.h"

#ifdef TY_DBG
#include "channel.h"
#endif

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UINT32 mmc_set_rca (void);
static UINT32 mmc_get_spec_ver(void);
static UINT32 mmc_set_bus_width (UINT32,UINT32);
static UINT32 mmc_get_card_capacity(UINT32 *capacity);

/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
UINT32 address_mode; /* Global variable for addressing mode */

static UINT32 g_u32Capacity = 0;

/*==========================================================================
                                     Global FUNCTIONS
==========================================================================*/

/*!
 * initialize the MMC device.
 * @bus_width
 * @return
 * int - SUCCESS (TRUE) or  FAIL
 */

UINT32 mmc_init(UINT32 bus_width)
{
    UINT32 status = FAIL;
	UINT32 spec_version=0;
	
    /* Get CID number of MMC Card */
    if(!card_get_cid())
    {
        /* Set RCA of the MMC Card */
        if(!mmc_set_rca())
        {
            /* Get Spec version supported by the card */
            spec_version = mmc_get_spec_ver();

            if (!mmc_get_card_capacity(&g_u32Capacity))
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
            /*Enable operating frequency */
            interface_configure_clock(OPERATING_FREQ);

            /*Put MMC in Transfer State */
            if(!card_set_data_transfer_mode ())
            {
                /* Set status variable as SUCESS */
                status = SUCCESS; 
             }

         }
    }
 
    return status;
	
}

/*!
 * read data from MMC card for specified length 
   from specified offset and copy it a dest pointer.
 * 1. Issue Commnand CMD16 to set block length as 512 bytes.
 * 2. Issue Command CMD17 to read single block.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 mmc_data_read (UINT32 *dest_ptr,UINT32 length,UINT32 offset,dump_callback callback)
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
    interface_config_block_info(BLK_LEN,ONE);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd,CMD16,BLK_LEN,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        read_block_status = FAIL;
    }
    else
    {
        while(len>0 && !read_block_status) 
        {
            
            /* Comfigure command CMD17 for single block read */	
            card_command_config(&cmd,CMD17,offset,READ,RESPONSE_48,
	                        DATA_PRESENT,ENABLE,ENABLE);	
			
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
				
                read_block_status = FAIL;
            }
            else
            {
                /* Call interface Data read function */
                read_block_status = interface_data_read(dest_ptr,BLK_LEN);
				
                /*decrement length by block size */
                len = len - BLK_LEN;
				
                /* Increment offset by Block Size */
		   address_mode == SECT_MODE ? (offset++) : (offset +=  BLK_LEN);

		  /* send the dump status and data to host */
		 if(callback){
		 	if(len > 0){
				csum = calculate_checksum((u8 *)dest_ptr, BLK_LEN);
				callback((u8 *)dest_ptr, FLASH_PARTLY, csum, BLK_LEN);
			}else{
				csum = calculate_checksum((u8 *)dest_ptr, len + BLK_LEN );
				callback((u8 *)dest_ptr, FLASH_PARTLY, csum, len + BLK_LEN);
			}
		 }
               /* Increment Destination pointer */
               dest_ptr = dest_ptr + (BLK_LEN/FOUR);
            }
	
        }
				
    }
    return read_block_status;
}

/*!
 * write data from buffer to card for specified length  
 * from specified offset and copy it a dest pointer.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 mmc_data_write (UINT32 *dest_ptr,UINT32 length,UINT32 offset,response_callback callback)
{
    command_t cmd;
    int len;
    UINT32 write_block_status=SUCCESS;
	
    /* Assing length of data to be read */
    len = length;
    
    if(address_mode == SECT_MODE)  
    {
        offset /= BLK_LEN;
    }
     /* Configure interface block and number of blocks */
     interface_config_block_info(BLK_LEN,ONE);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd,CMD16,BLK_LEN,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        write_block_status = FAIL;
    }
    else
    {
        while(len>0 && !write_block_status) 
        {
			
            /* Comfigure command CMD24 for single block write */	
            card_command_config(&cmd,CMD24,offset,WRITE,RESPONSE_48,
	                        DATA_PRESENT,ENABLE,ENABLE);	
			
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
				
                write_block_status = FAIL;
            }
            else
            {
                /* Call interface write read function */
                write_block_status = interface_data_write(dest_ptr,BLK_LEN);
				
                /*decrement length by block size */
                len = len - BLK_LEN;
				
                /* Increment offset by Block Size */
		   address_mode == SECT_MODE ? (offset++) : (offset +=  BLK_LEN);

		  /* send the prg status to host */
		  if(callback)
			callback(FLASH_PARTLY, offset, BLK_LEN);
		  
               /* Increment Destination pointer */
               dest_ptr = dest_ptr + (BLK_LEN/FOUR);
            }
	
        }
				
    }
    return write_block_status;
}

/*!
 * erase data from card for specified length 
 * from specified offset
 * 1. Issue Commnand CMD35 to set first block to erase
 * 2. Issue Command CMD36 to set end block to erase  
 * 3. Issue Command CMD38 to start erase 
 *
 * In MMC card, CMD32, CMD33 and CMD34 are reserved.
 *
 * @param [in] offset offset in MMC card from which erase starts.
 * @param [in] size   size to erase. 
 * @return
 * Return result in UINT32 format.
 */
UINT32 mmc_data_erase (UINT32 offset, UINT32 size)
{
	command_t cmd;
	U8 startEraseBlockCmd = CMD35; 
	U8 endEraseBlockCmd   = CMD36;
	UINT32 startBlock = offset / BLK_LEN; 
	UINT32 endBlock   = (offset + size) / BLK_LEN;
	U32 ret;

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
    	/* Configure end erase command to set end block*/
		card_command_config(&cmd, endEraseBlockCmd, endBlock, SD_COMMAND, 
                        RESPONSE_48, DATA_PRESENT_NONE, ENABLE,ENABLE);
    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
        {
		    /* Comfigure command to start erase*/	
        	card_command_config(&cmd, CMD38, 0, SD_COMMAND, RESPONSE_48,
	                              DATA_PRESENT_NONE, ENABLE, ENABLE);
	    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
            {
	    		//wait for completion
				return ret;             	
           	}
	   	}
	}
	
	return ret;
}

/*==========================================================================
                                     LOCAL FUNCTIONS
==========================================================================*/

/*!
 * validate the operating volatge range of the card.
 * 1.Issue CMD1 to MMC card.
 * 2.Read the command response.
 * 3.Compare the response value with standard value specified in specification.
 * @return
 * UINT32
 */

UINT32 mmc_voltage_validation (void)
{
    command_t cmd;
    command_response_t response;
    UINT32 voltage_validation_command=0;
    UINT32 ocr_val=0;
    UINT32 voltage_validation = FAIL;
	
    ocr_val = (UINT32) ((MMC_OCR_VALUE) & 0xFFFFFFFF);
	
    while((voltage_validation_command < MMCSD_READY_TIMEOUT ) && (voltage_validation != SUCCESS)) 
    {  	
        /* Configure CMD1 for MMC card */
        /* Argument will be expected OCR value */
        card_command_config(&cmd, CMD1, ocr_val, READ, RESPONSE_48_WITHOUT_CRC,
                                  DATA_PRESENT_NONE, DISABLE, DISABLE);
                 
        /* Issue CMD1 to MMC card to determine OCR value */
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
		
            /* Check if card busy bit is cleared or not */
            if(!(response.cmd_rsp0 & CARD_BUSY_BIT))
            {
                /* Iterate One more time */
                voltage_validation_command++;
            }
            else
            {
                if((response.cmd_rsp0 & MMC_OCR_HC_RES) == MMC_OCR_HC_RES)
                {  
                    address_mode = SECT_MODE; 
                    voltage_validation = SUCCESS;
                }
                else if((response.cmd_rsp0 & MMC_OCR_LC_RES) == MMC_OCR_LC_RES)
                {
                    address_mode = BYTE_MODE; 
                    voltage_validation = SUCCESS;
                }
            }
                     
        }
    }
	
    return voltage_validation;
}

/*!
 * Get MMC card capacity.
 * Issue Commnand CMD9 to get card CSD.
 * @dest_ptr
 * @length
 * @offset
 * @return
   UINT32
 */
UINT32 mmc_get_capacity(UINT32 *capacity)
{
    if (NULL == capacity)
    {
        return -1;
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: mmc_get_capacity(),capacity:%d", g_u32Capacity);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    *capacity = g_u32Capacity;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: mmc_get_capacity()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return 0;
}

static UINT32 mmc_get_card_capacity(UINT32 *capacity)
{
    command_t cmd;
    command_response_t response;
    card_specific_data csd;
    UINT32 u32Read_BL_Len = 0;
    S32    i32C_Size = 0;
    S32    i32C_Size_Mult = 0;
    S32    result = 0;
    UINT32 u32Capacity = 0;
    UINT32 card_address = (Card_rca << RCA_SHIFT);

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: mmc_get_card_capacity()");
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
		    sprintf(au8StrBuf, "Ty,csd0:%d,csd1:%d,csd2:%d,csd3:%d\n", csd.csd0, csd.csd1, csd.csd2, csd.csd3);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        u32Read_BL_Len   = ((csd.csd2 & MMC_CSD_READ_BL_LEN_MASK) >> MMC_CSD_READ_BL_LEN_OFFSET);

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Read_BL_Len:%d\n", u32Read_BL_Len);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        i32C_Size = ((csd.csd1 & MMC_CSD_C_SIZE_PART1_MASK) >> MMC_CSD_C_SIZE_PART1_OFFSET) | ((csd.csd2 & MMC_CSD_C_SIZE_PART2_MASK) >> MMC_CSD_C_SIZE_PART2_OFFSET << MMC_CSD_C_SIZE_PART1_LEN);
        i32C_Size_Mult = ((csd.csd1 & MMC_CSD_C_SIZE_MULT_MASK) >> MMC_CSD_C_SIZE_MULT_OFFSET);

        if (i32C_Size_Mult < 0 || i32C_Size_Mult > 7)
        {
            return -2;
        }
        /* memory capacity = BLOCKNR * BLOCK_LEN */
        /* Where BLOCKNR = (C_SIZE + 1) * MULT
            MULT = 2^(C_SIZE_MULT+2)
            BLOCK_LEN = 2^READ_BL_LEN */
        u32Capacity = (UINT32)((long long)(i32C_Size + 1) * (long long)(1 << (i32C_Size_Mult + 2)) * (long long)(1 << u32Read_BL_Len) >> 10); /* >>10 to get kbytes */

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, C_Size:%d,C_Size_Mult:%d,Capacity:%d\n", i32C_Size, i32C_Size_Mult, u32Capacity);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        *capacity = u32Capacity;
	
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Exit: mmc_get_card_capacity()");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
    }

    return result;
}

/*!
 * set RCA of MMC card.
 * 1.Set RCA value to relative card address.
 * 2.Send Command CMD3 with argument of 16 bits which will be used as RCA value.
 * 3.This will set the RCA of the card as desired value.
 * @return
   SUCCESS / FAILURE
 */
static UINT32 mmc_set_rca (void)
{
    command_t cmd;
    UINT32 card_state=0;
    UINT32 rca_request=0;
    command_response_t response;
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
    /* Configure CMD3 for MMC card */
    /* 32bit card address is expected as Argument */
    card_command_config(&cmd,CMD3,card_address,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	                    
	                    
    /* Assigns relative address to the card
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
 * read MMC CSD register and return SPEC_VER.
 * 1.Send CMD9 to get CSD value of MMC Card. 
 * 2.Extract CSD value from CMDRSP0,CMDRSP1,CMDRSP2,CMDRSP3 registers.
 * 3.Return Spec version of MMC card. 
 * @return 
 * UINT32
 */
static UINT32 mmc_get_spec_ver (void)
{
    command_t cmd;
    command_response_t response;
    card_specific_data csd;
    UINT32 mmc_spec_version;
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
    /* Configure CMD9 for MMC card */
    /* 16bit card address is expected as Argument */
    card_command_config(&cmd,CMD9,card_address,READ,RESPONSE_136,
                    DATA_PRESENT_NONE,ENABLE,DISABLE);
	
	
    /* Issue Command CMD9 to Extrace CSD register contents
     */
     
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        mmc_spec_version = 0;
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
		
	mmc_spec_version = ((csd.csd3 && MMC_SPEC_VER) >> MMC_SPEC_VER_SHIFT);
    }
	
    return mmc_spec_version;
		
}

/*!
 * will set bus width of MMC Card.
 * 1. Check if the value of SPEC_VER is 4 or above 
 * 2. if bus width request is 4 or 8 and spec verison less than 4
 * 3. Report error that MMC doesnt support multiple bit width pattern.
 * 4. send CMD6 with argument 0x3B70x00; (8-bit, x=2; 4-bit, x=1; 1-bit, x=0)
 * 5. send CMD13 to wait card ready (busy line released)
 * @spec_version
 * @bus_width
 * @return
 * UINT32
 */
static UINT32 mmc_set_bus_width (UINT32 spec_version,UINT32 bus_width)
{
    command_t cmd;
    UINT32 switch_error;
    UINT32 bus_size;
    UINT32 set_bus_width_status;
    command_response_t response;
   
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
    if ((bus_width == FOUR || bus_width == EIGHT) && (spec_version < FOUR ))
    {
        set_bus_width_status = FAIL;
    }
    else
    {
        bus_size = (bus_width >> BUS_SIZE_SHIFT);
		
        /* Configure CMD6 to write to EXT_CSD register for BUS_WIDTH */
	card_command_config(&cmd,CMD6,((BUS_WIDTH)|(bus_size<<EIGHT)),READ,RESPONSE_48,
	                    DATA_PRESENT_NONE,ENABLE,ENABLE);		
		
		
        /* Sending the card from stand-by to transfer state
        */
		
        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
            set_bus_width_status = FAIL;
        }
        else
        {
            /* Configure CMD13 to read status of the card becuase CMD6 has R1b response */
            card_command_config(&cmd,CMD13,card_address,READ,RESPONSE_48,
	                    DATA_PRESENT_NONE,ENABLE,ENABLE);
			
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
                set_bus_width_status = FAIL;
            }
			
            else
            {
                /* Read Command response */
                response.format = RESPONSE_48;
                interface_read_response (&response);

                switch_error = ((UINT32) (response.cmd_rsp0 & MMC_R1_SWITCH_ERROR_MASK) >> SWITCH_ERROR_SHIFT);
				
                if(!switch_error)
                {
                    set_bus_width_status = SUCCESS;
                }
            }	
        }
    }
	
    return set_bus_width_status;
}

