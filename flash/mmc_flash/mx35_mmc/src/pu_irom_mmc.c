/*=================================================================================

    Module Name:  pu_irom_mmc.c

    General Description: Limited IROM MMC Driver.

===================================================================================
                               Freescale Confidential Proprietary
                        Template ID and version: IL93-TMP-01-0106  Version 1.20
                        (c) Copyright Freescale, All Rights Reserved


				Copyright: 2007 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a
                   Freescale Software License Agreement, which has either
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.


Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number     Description of Changes
-------------------------   ------------    ----------   --------------------------
Prabhat Singh                      17-July-2007    Tlbso94839        Added support for High capacity SD for Ringo
Surender Kumar (r66464)     09/03/2006      TLSbo79133 	 Initial implementation.
Suresh Kumar                      09/Feb/2007     TLSbo90422   Change loopcount to 3000
                                                         to get timeout period below 5 sec
Surender Kumar                    21/Feb/2007     TLSbo90953   Support for High Capacity MMC Card

Portability: Portable to other compilers or platforms.


===================================================================================
                                        INCLUDE FILES
==================================================================================*/

//#define TY_DBG

#include <stdio.h>
#include "pu_irom_esdhc.h"
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"
#include "protocol.h"
#include "flash_lib.h"
#include "pu_irom_timer.h"

#ifdef TY_DBG
#include "channel.h"
#endif

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UINT32 mmc_set_rca (void);
static UINT32 mmc_get_csd(void);
static UINT32 mmc_get_card_capacity(UINT32 *capacity);

/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
/*
 * Extract the CSD fields from the response
 * reg   : Response regiser value i.e. CMDRSP0/CMDRSP1/CMDRSP2/CMDRSP3
 * mask  : Mask for specific field.
 * shift : Shift value.
 *
 * NOTE:
 *     CSD fields mask and shift are not as per MMC spec but it's
 *     depends upon how the data is present in eSDHC response registers.
 * MSB --> CMDRSP3 [127 - 104]
 *         CMDRSP2 [103 -  72]
 *         CMDRSP1 [ 71 -  40]
 * LSB --> CMDRSP0 [ 39 -   8]
 */
#define MMC_CSD_EXTRACT(reg, mask, shift) (((UINT32)reg & mask) >> shift)

/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
extern UINT32 address_mode; /* Global variable for addressing mode */

static UINT32 g_u32Capacity = 0;

/* MMC card CSD struture */
static mmc_csd_t mmc_csd = {ZERO, ZERO, ZERO, ZERO, ZERO};

/*==========================================================================
                                     Global FUNCTIONS
==========================================================================*/

/*==========================================================================
FUNCTION: UINT32  mmc_init (UINT32 bus_width)
DESCRIPTION:
   mmc_init () function will initialize the MMC device.

ARGUMENTS PASSED:
   Int bus_width

RETURN VALUE:
   int - SUCCESS (TRUE) or  FAIL

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:

==============================================================================*/

UINT32 mmc_init(UINT32 bus_width)
{
    UINT32 status = FAIL;

    /* Get CID number of MMC Card */
    if(!card_get_cid())
    {
        /* Set RCA of the MMC Card */
        if(!mmc_set_rca())
        {
#if defined (REV_TO2)
            /* Set weak pull-up for the CMD line */
            esdhc_set_cmd_pullup(WEAK);
#endif

            /* Get Spec version supported by the card */
            status = mmc_get_csd();

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

/*==========================================================================
FUNCTION: UINT32 mmc_data_read (UINT32 *dest_ptr,UINT32 len,UINT32 offset)
DESCRIPTION:
   mmc_data_read () function will read data from MMC card for specified length 
   from specified offset and copy it a dest pointer.

ARGUMENTS PASSED:
   None

RETURN VALUE:
   UINT32

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1. Issue Commnand CMD16 to set block length as 512 bytes.
  2. Issue Command CMD17 to read single block.  
==============================================================================*/
UINT32 mmc_data_read (UINT32 *dest_ptr,UINT32 length,UINT32 offset,dump_callback callback)
{
    command_t cmd;
    INT32 len = ZERO;
    UINT32 read_block_status=SUCCESS;
    UINT32 blk_len = ESDHC_BLK_LEN;
    U16 csum;
	

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: mmc_data_read()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Assing length of data to be read */
    len = length;
   
    if(address_mode == SECT_MODE)  
    {
        blk_len = (ESDHC_BLK_LEN/512);
        offset /= ESDHC_BLK_LEN;
    }
 
#if defined (REV_TO1)
    /* Configure interface block and number of blocks */
    interface_config_block_info(ESDHC_BLK_LEN,
                                ONE,
                                ESDHC_READ_WATER_MARK_LEVEL_BL_512);
#endif

    /* Configure CMD16 to set block length as 512 bytes. */
    card_command_config(&cmd, CMD16,
                              ESDHC_BLK_LEN,
                              READ,
                              RESPONSE_48,
                              DATA_PRESENT_NONE,
                              ENABLE,
                              ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
		{
			// Terry adds for debug, :-)
			U8 au8StrBuf[100] = { 0 };
			sprintf(au8StrBuf, "Ty, Issue CMD16 failed!");
			atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
		}
#endif	
        read_block_status = FAIL;
    }
    else
    {
        while((len > 0) && !read_block_status)
        {
#if defined (REV_TO2)
            /* Clear interrupt before setting block config */
            interface_clear_interrupt();

            /* Configure interface block and number of blocks */
            interface_config_block_info(ESDHC_BLK_LEN,
                                        ONE,
                                        ESDHC_READ_WATER_MARK_LEVEL_BL_512);
#endif
            
            /* Comfigure command CMD17 for single block read */	
            card_command_config(&cmd, CMD17,
                                      offset,
                                      READ,
                                      RESPONSE_48,
                                      DATA_PRESENT,
                                      ENABLE,
                                      ENABLE);
			
            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
#ifdef TY_DBG
				{
					// Terry adds for debug, :-)
					U8 au8StrBuf[100] = { 0 };
					sprintf(au8StrBuf, "Ty, Issue CMD17 failed!");
					atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
				}
#endif	
                read_block_status = FAIL;
            }
            else
            {
                /* Call interface Data read function */
                read_block_status = interface_data_read(dest_ptr,ESDHC_BLK_LEN);
				
                /*decrement length by block size */
                len = len - ESDHC_BLK_LEN;
				
                /* Increment offset by Block Size */
                offset = offset + blk_len;
			   /* send the dump status and data to host */
			  if(callback){
				if(len > 0){
					csum = calculate_checksum((u8 *)dest_ptr, ESDHC_BLK_LEN);
					callback((u8 *)dest_ptr, FLASH_PARTLY, csum, ESDHC_BLK_LEN);
				}else{
					csum = calculate_checksum((u8 *)dest_ptr, len + ESDHC_BLK_LEN );
					callback((u8 *)dest_ptr, FLASH_PARTLY, csum, len + ESDHC_BLK_LEN);
				}
			 }
               /* Increment Destination pointer */
               dest_ptr = dest_ptr + (ESDHC_BLK_LEN/FOUR);
            }
	
        }
				
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: mmc_data_read()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

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

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: mmc_data_write()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Assing length of data to be read */
    len = length;
    
    if(address_mode == SECT_MODE)  
    {
        offset /= ESDHC_BLK_LEN;
    }
     /* Configure interface block and number of blocks */
    interface_config_block_info(ESDHC_BLK_LEN, ONE, ESDHC_WRITE_WATER_MARK_LEVEL_BL_512);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd,CMD16,ESDHC_BLK_LEN,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
		{
			// Terry adds for debug, :-)
			U8 au8StrBuf[100] = { 0 };
			sprintf(au8StrBuf, "Ty, issue CMD16 failed!");
			atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
		}
#endif
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
#ifdef TY_DBG
				{
					// Terry adds for debug, :-)
					U8 au8StrBuf[100] = { 0 };
					sprintf(au8StrBuf, "Ty, issue CMD24 failed!");
					atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
				}
#endif
                write_block_status = FAIL;
            }
            else
            {
                /* Call interface write read function */
                write_block_status = interface_data_write(dest_ptr,ESDHC_BLK_LEN);
				
#ifdef TY_DBG
				{
					// Terry adds for debug, :-)
					U8 au8StrBuf[100] = { 0 };
					sprintf(au8StrBuf, "Ty, write_block_status:%d", write_block_status);
					atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
				}
#endif

                /*decrement length by block size */
                len = len - ESDHC_BLK_LEN;
				
                /* Increment offset by Block Size */
		        address_mode == SECT_MODE ? (offset++) : (offset +=  ESDHC_BLK_LEN);

		        /* send the prg status to host */
		        if(callback)
			        callback(FLASH_PARTLY, offset, ESDHC_BLK_LEN);
		  
                /* Increment Destination pointer */
                dest_ptr = dest_ptr + (ESDHC_BLK_LEN/FOUR);
            }
	
        }
				
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: mmc_data_write()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

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
	UINT32 startBlock = offset / ESDHC_BLK_LEN; 
	UINT32 endBlock   = (offset + size) / ESDHC_BLK_LEN;
	U32 ret;

	if (address_mode != SECT_MODE) 
    {
        /* Byte mode, erase by sectors in both mode */
        startBlock *= ESDHC_BLK_LEN;
		endBlock   *= ESDHC_BLK_LEN;
   	}
	
	/* Configure start erase command to set first block*/
	card_command_config(&cmd,startEraseBlockCmd, startBlock, READ, RESPONSE_48,
                    DATA_PRESENT_NONE, ENABLE,ENABLE);
    	/* wait response */
	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
    {
    	/* Configure end erase command to set end block*/
		card_command_config(&cmd, endEraseBlockCmd, endBlock, READ, 
                        RESPONSE_48, DATA_PRESENT_NONE, ENABLE,ENABLE);
    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
        {
		    /* Comfigure command to start erase*/	
        	card_command_config(&cmd, CMD38, 0, READ, RESPONSE_48,
	                              DATA_PRESENT_NONE, ENABLE, ENABLE);
	    	if ((ret = interface_send_cmd_wait_resp(&cmd)) == SUCCESS)
            {
                UINT32 transfer_status = 0;
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty: Send CMD38 succeed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
	    		//wait for completion
                transfer_status = card_check_status(MMCSD_CMD_SEL_CARD_TIMEOUT,
                                            TRAN,
                                            R1_ERROR);
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

/*==========================================================================
FUNCTION: static int mmc_voltage_validation (void)
DESCRIPTION:
   mmc_voltage_validation () function will validate the operating volatge
   range of the card.

ARGUMENTS PASSED:
   None.

RETURN VALUE:
   int - SUCCESS/FAIL

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Issue CMD1 to MMC card.
  2.Read the command response.
  3.Compare the response value with standard value specified in specification.
==============================================================================*/

UINT32 mmc_voltage_validation (void)
{
    command_t cmd;
    command_response_t response;
    UINT32 voltage_validation_count = ZERO;
    UINT32 ocr_val = MMC_HV_HC_OCR_VALUE;
    UINT32 voltage_validation = FAIL;
	
    /* Start timer for CMD1 timeout */
    GPT_delay(ESDHC_CMD1_TIMEOUT);
	
    while((voltage_validation_count < CARD_READY_TIMEOUT)
           && (voltage_validation != SUCCESS) && (!GPT_status()))
    {  	
        /* Configure CMD1 for MMC card */
        /* Argument will be expected OCR value */
        card_command_config(&cmd, CMD1,
                                  ocr_val,
                                  READ,
                                  RESPONSE_48,
                                  DATA_PRESENT_NONE,
                                  DISABLE,
                                  DISABLE);
                 
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
                voltage_validation_count++;
            }
            else
            {
                /* Check the card access mode supported */
                if((response.cmd_rsp0 & MMC_OCR_HC_BIT_MASK) == MMC_OCR_HC_RESP_VAL)
                {
                    address_mode = SECT_MODE; 
                    voltage_validation = SUCCESS;
                }
                else
                {
                    address_mode = BYTE_MODE; 
                    voltage_validation = SUCCESS;
                }
            }
                     
        }
    }

    /* Disable Timer */
    GPT_disable();

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
    UINT32 card_address = (Card_rca << CARD_RCA_SHIFT);

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

        u32Read_BL_Len   = MMC_CSD_EXTRACT(csd.csd2, MMC_CSD_READ_BL_LEN_MASK, MMC_CSD_READ_BL_LEN_OFFSET);

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Read_BL_Len:%d\n", u32Read_BL_Len);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        i32C_Size = MMC_CSD_EXTRACT(csd.csd1, MMC_CSD_C_SIZE_PART1_MASK, MMC_CSD_C_SIZE_PART1_OFFSET) | 
            (MMC_CSD_EXTRACT(csd.csd2, MMC_CSD_C_SIZE_PART2_MASK, MMC_CSD_C_SIZE_PART2_OFFSET) << MMC_CSD_C_SIZE_PART1_LEN);
        i32C_Size_Mult = MMC_CSD_EXTRACT(csd.csd1, MMC_CSD_C_SIZE_MULT_MASK, MMC_CSD_C_SIZE_MULT_OFFSET);

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

/*==========================================================================
FUNCTION: static UINT32 mmc_set_rca (void)
DESCRIPTION:
   mmc_set_rca () function will set RCA of MMC card.

ARGUMENTS PASSED:
  None

RETURN VALUE:
   SUCCESS / FAILURE

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Set RCA value to relative card address.
  2.Send Command CMD3 with argument of 16 bits which will be used as RCA value.
  3.This will set the RCA of the card as desired value.
==============================================================================*/
static UINT32 mmc_set_rca (void)
{
    command_t cmd;
    UINT32 rca_request = ZERO;
    command_response_t response;
    UINT32 card_address = (Card_rca << CARD_RCA_SHIFT);
	
    /*
     * Configure CMD3 for MMC card
     * 32bit card address is expected as Argument
     */
    card_command_config(&cmd, CMD3,
                              card_address,
                              READ,
                              RESPONSE_48,
                              DATA_PRESENT_NONE,
                              ENABLE,
                              ENABLE);

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
		

        if(R1_CURRENT_STATE(response.cmd_rsp0) == IDENT)
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

/*==========================================================================
FUNCTION: UINT32 mmc_get_csd(void)
DESCRIPTION:
   Read MMC CSD register fields in to mmc_csd.

ARGUMENTS PASSED:
   None

RETURN VALUE:
   UINT32 -- SUCCESS or FAIL.

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Send CMD9 to get CSD value of MMC Card. 
  2.Extract CSD value from CMDRSP0,CMDRSP1,CMDRSP2,CMDRSP3 registers.
  3.Return Spec version of MMC card. 
==============================================================================*/
static UINT32 mmc_get_csd(void)
{
		
    command_t cmd;
    command_response_t response;
    UINT32 mmc_csd_status = FAIL;
    UINT32 card_address = (Card_rca << CARD_RCA_SHIFT);
	
    /*
     * Configure CMD9 for MMC card
     * 16bit card address is expected as Argument
     */
    card_command_config(&cmd, CMD9,
                              card_address,
                              READ,
                              RESPONSE_136,
                              DATA_PRESENT_NONE,
                              ENABLE,
                              DISABLE);
     
    /* Issue Command CMD9 to Extrace CSD register contents */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        mmc_csd_status = FAIL;
    }
	
    else
    {
        /* Read Command response */
        response.format = RESPONSE_136;
        interface_read_response (&response);
		
        /* Assign Response to CSD Strcuture */
        mmc_csd.csd_struture = MMC_CSD_EXTRACT(response.cmd_rsp3,
                                               MMC_CSD_CSD_STRUT_MASK,
                                               MMC_CSD_CSD_STRUT_SHIFT);

        /* MMC spec version */
        mmc_csd.spec_vers = MMC_CSD_EXTRACT(response.cmd_rsp3,
                                            MMC_CSD_SPEC_VERS_MASK,
                                            MMC_CSD_SPEC_VERS_SHIFT);

        /* Defines the asynchronous part of the data access time. */
        mmc_csd.taac = MMC_CSD_EXTRACT(response.cmd_rsp3,
                                       MMC_CSD_TAAC_MASK,
                                       MMC_CSD_TAAC_SHIFT);

        /* Clock dependent factor of the data access time */
        mmc_csd.nsac = MMC_CSD_EXTRACT(response.cmd_rsp3,
                                       MMC_CSD_NSAC_MASK,
                                       MMC_CSD_NSAC_SHIFT);

        /* Typical block program time as a multiple of the read access time. */
        mmc_csd.r2w_factor = MMC_CSD_EXTRACT(response.cmd_rsp0,
                                             MMC_CSD_R2W_FACTOR_MASK,
                                             MMC_CSD_R2W_FACTOR_SHIFT);

        mmc_csd_status = SUCCESS;
    }
	
    return mmc_csd_status;
		
}




