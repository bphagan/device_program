/*=================================================================================

    Module Name:  pu_irom_sd.c

    General Description: Limited IROM SD Driver.

===================================================================================
                               Freescale Confidential Proprietary
                        Template ID and version: IL93-TMP-01-0106  Version 1.20
                        (c) Copyright Freescale 2004, All Rights Reserved


				Copyright: 2005 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a
                   Freescale Software License Agreement, which has either
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.


Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number     Description of Changes
-------------------------   ------------    ----------   --------------------------
Surender Kumar (r66464)     09/15/2006      TLSbo79133 	 Initial implementation.
Suresh Kumar                09/Feb/2007     TLSbo90422   Change loopcount to 3000
                                                         to get timeout period below 5 sec


Portability: Portable to other compilers or platforms


===================================================================================
                                        INCLUDE FILES
==================================================================================*/

//#define TY_DBG

#include "pu_irom_esdhc.h"
#include "pu_irom_card.h"
#include "pu_irom_sd.h"
#include "protocol.h"
#include "flash_lib.h"
#include "stdio.h"

#ifdef TY_DBG
#include "channel.h"
#endif

/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/

/* SD card SRC struture */
static sd_scr_t sd_card_scr = {ZERO, ZERO};

struct rkl_request {
	u32 addr;	/* NAND: offset address, NOR: physical address */
	u32 param; 	/* flash size or fuse value */
	u32 param1; /* reversed */
	cmd_t cmd;	/* flash or fuse command */
};
/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UINT32 sd_get_rca (void);
static UINT32 sd_get_card_capacity(UINT32 *capacity);
static UINT32 sd_set_boot_partition(void);
static UINT32 sd_get_scr(void);

/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
#define SD_OCR_VALUE_HC 0xC0ff8000
#define SD_OCR_VALUE_LC 0x80ff8000
#define SD_OCR_VALUE_BAK 0x80ff8000
#define SD_HC_CCS_CHECK   0x40000000
#define MMC_OCR_HC_RES 0xC0FF8000
#define MMC_OCR_VALUE_MASK 0x00FF8000
#define CMD8_VOLTAGE_OCR_PATTERN 0x000001AA
#define RCA_SHIFT 16
#define SD_R1_STATUS_APP_CMD_MSK 0x20
#define BIT_MODE_4_SUPPORT 5
//#define SD_BUS_WIDTH_OFFSET 6
#define BIT_4_MODE 4
/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
UINT8  SDver2card;
UINT8 SDver1card;
extern UINT32 address_mode; /* Global variable for addressing mode */

static UINT32 g_u32Capacity = 0;

/*==========================================================================
                                     Global FUNCTIONS
==========================================================================*/
/*==========================================================================
FUNCTION: UINT32 sd_init (int bus_width)
DESCRIPTION:
   sd_init () function will initialize the SD memory card.

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

UINT32 sd_init(UINT32 bus_width)
{
    UINT32 status = FAIL;
	
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
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Get cid success!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        /* Set RCA of the SD Card */
        if(!sd_get_rca())
        {
            /*Enable operating frequency */
            interface_configure_clock(OPERATING_FREQ);

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
            if(!card_set_data_transfer_mode ())
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, set transfer mode success!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
                /* Get the SD SCR */
                status = sd_get_scr();
                /* Set Boot Partition to partition #1 */
                if((status == SUCCESS) &&
                    (sd_card_scr.spec_version != SD_CARD_1_0))
                {
                    /* Set the boot partition */
                    sd_set_boot_partition();
                }
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
   
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_data_read");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    if(address_mode == SECT_MODE)  
    {
        offset /= ESDHC_BLK_LEN;
    }    
    /* Configure interface block and number of blocks */
    interface_config_block_info(ESDHC_BLK_LEN, ONE, ESDHC_READ_WATER_MARK_LEVEL_BL_512);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd, CMD16, ESDHC_BLK_LEN, READ, RESPONSE_48,
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
#ifdef TY_DBG
			{
				// Terry adds for debug, :-)
				U8 au8StrBuf[100] = { 0 };
				sprintf(au8StrBuf, "Ty, Read len:%d", len);
				atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
			}
#endif 
            /* Comfigure command CMD17 for single block read */	
            card_command_config(&cmd, CMD17, offset, READ, RESPONSE_48,
	                        DATA_PRESENT, ENABLE, ENABLE);	
			
            if (interface_send_cmd_wait_resp(&cmd) == FAIL)
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
                read_block_status = interface_data_read(dest_ptr, ESDHC_BLK_LEN);
#ifdef TY_DBG
			    {
				    // Terry adds for debug, :-)
				    U8 au8StrBuf[100] = { 0 };
				    sprintf(au8StrBuf, "Ty, read_block_status:%d", read_block_status);
				    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
			    }
#endif	
                /*decrement length by block size */
                len = len - ESDHC_BLK_LEN;
				
                /* Increment offset by Block Size */
		        address_mode == SECT_MODE ? (offset++) : (offset +=  ESDHC_BLK_LEN);

		        /* send the dump status and data to host */
		        if(callback)
                {
		 	        if(len > 0)
                    {
				        csum = calculate_checksum((u8 *)dest_ptr, ESDHC_BLK_LEN);
				        callback((u8 *)dest_ptr, FLASH_PARTLY, csum, ESDHC_BLK_LEN);
			        }
                    else
                    {
				        csum = calculate_checksum((u8 *)dest_ptr, len + ESDHC_BLK_LEN );
				        callback((u8 *)dest_ptr, FLASH_PARTLY, csum, len + ESDHC_BLK_LEN);
			        }
		        }
                /* Increment Destination pointer */
                dest_ptr = dest_ptr + (ESDHC_BLK_LEN / FOUR);
            }
        }
    }
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_data_read");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

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
UINT32 sd_data_write (UINT32 *dest_ptr, UINT32 length, UINT32 offset, response_callback callback)
{
    command_t cmd;
    int len;
    UINT32 write_block_status=SUCCESS;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_data_write\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Assing length of data to be read */
    len = length;
    
    if (address_mode == SECT_MODE)  
    {
        offset /= ESDHC_BLK_LEN;
    }
     /* Configure interface block and number of blocks */
    interface_config_block_info(ESDHC_BLK_LEN, ONE, ESDHC_WRITE_WATER_MARK_LEVEL_BL_512);
 
    /* Configure CMD16 to set block length as 512 bytes.*/
    card_command_config(&cmd, CMD16, ESDHC_BLK_LEN, READ, RESPONSE_48,
                    DATA_PRESENT_NONE, ENABLE,ENABLE);
	
    /* Issue command CMD16 to set block length as 512 bytes */
    if (interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
        {
            // Terry adds for debug, :-)
            U8 au8StrBuf[100] = { 0 };
            sprintf(au8StrBuf, "Ty, issue CMD16 failed!\n");
            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
        }
#endif
        write_block_status = FAIL;
    }
    else
    {
        while (len > 0 && !write_block_status) 
        {
            /* Comfigure command CMD24 for single block write */	
            card_command_config(&cmd, CMD24, offset, WRITE, RESPONSE_48,
	                        DATA_PRESENT, ENABLE, ENABLE);	
			
            if (interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, issue CMD24 failed!\n");
		            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	            }
#endif
                write_block_status = FAIL;
            }
            else
            {
                /* Call interface write read function */
                write_block_status = interface_data_write(dest_ptr, ESDHC_BLK_LEN);
			
#ifdef TY_DBG
	            {
		            // Terry adds for debug, :-)
		            U8 au8StrBuf[100] = { 0 };
		            sprintf(au8StrBuf, "Ty, write_block_status: %d\n", write_block_status);
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
                dest_ptr = dest_ptr + (ESDHC_BLK_LEN / FOUR);
            }
        }
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: sd_data_write\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

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
	UINT32 startBlock = offset / ESDHC_BLK_LEN; 
	UINT32 endBlock   = (offset + size) / ESDHC_BLK_LEN;
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
        startBlock *= ESDHC_BLK_LEN;
		endBlock   *= ESDHC_BLK_LEN;
   	}
	
	/* Configure start erase command to set first block*/
	card_command_config(&cmd,startEraseBlockCmd, startBlock, READ, RESPONSE_48,
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
		card_command_config(&cmd, endEraseBlockCmd, endBlock, READ, 
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
        	card_command_config(&cmd, CMD38, 0, READ, RESPONSE_48,
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


/*==========================================================================
FUNCTION: static UINT32 sd_voltage_validation (void)
DESCRIPTION:
   sd_voltage_validation () function will validate the operating volatge
   range of the SD Memory card.

ARGUMENTS PASSED:
   None.

RETURN VALUE:
   int - voltage range

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Issue CMD55 to SD card with RCA value with default RCA i.e. 0x0000 
  2. Issue ACMD41 with argument value specified in specification.
  2.Read the command response.
  3.Compare the response value with standard value specified in specification.
  4.if it is not in the range send R15 command to put in in-active state.
==============================================================================*/

UINT32 sd_voltage_validation (void)
{
    command_t cmd;
    command_response_t response;
    UINT32 voltage_validation_command =0;
    UINT32 default_rca = 0;
    UINT32 ocr_value=0;
    UINT32 voltage_validation = FAIL;
	SDver2card=FALSE;
	SDver1card=FALSE;
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: sd_voltage_validation\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    while((voltage_validation_command < MMCSD_READY_TIMEOUT) && (voltage_validation != SUCCESS)) 
    {
        card_command_config(&cmd,CMD8,CMD8_VOLTAGE_OCR_PATTERN,READ,RESPONSE_48,
                                  DATA_PRESENT_NONE,ENABLE,ENABLE);
	                    
	           
                      
        /* Issue CMD8 to SD Memory card*/
        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
            SDver2card=FALSE;
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
	        /*Check Response of CMD8 command .If response is matching with send data of check pattern and voltage range it will be SDver2 card with high/low capacity*/
	        if(ocr_value==CMD8_VOLTAGE_OCR_PATTERN)
	        {
#ifdef TY_DBG
                {
	                // Terry adds for debug, :-)
	                U8 au8StrBuf[100] = { 0 };
	                sprintf(au8StrBuf, "Ty, SDver2 Card!\n");
	               atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
                }
#endif
                SDver2card=TRUE;       
	        }
	          
        }
      
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
	            sprintf(au8StrBuf, "Ty, Issue CMD55 failed!\n");
	            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
            }
#endif
            voltage_validation = FAIL;
            break;
        }
        else
        {
#ifdef TY_DBG
            {
	            // Terry adds for debug, :-)
	            U8 au8StrBuf[100] = { 0 };
	            sprintf(au8StrBuf, "Ty, Issue CMD55 Succeed!\n");
	            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
            }
#endif
            /* Check for SD version 1 or 2 and accordingly set HCS(high capacity check) bit[30] in OCR reg of SD host side  */
	        if(SDver2card)
	     	{
                ocr_value = ((UINT32)(SD_OCR_VALUE_HC) & 0xFFFFFFFF);
				
		    }
	        else
	    	{
#ifdef TY_DBG
                {
	                // Terry adds for debug, :-)
	                U8 au8StrBuf[100] = { 0 };
	                sprintf(au8StrBuf, "Ty, SDver1 Card!\n");
	                atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
                }
#endif
                ocr_value = ((UINT32)(SD_OCR_VALUE_LC) & 0xFFFFFFFF);
		        SDver1card=TRUE;   
		    }
            /* Configure ACMD41 for SD card */
            /* This command expects operating voltage range as argument.*/
	
            card_command_config(&cmd,ACMD41,ocr_value,READ,RESPONSE_48_CHECK_BUSY,DATA_PRESENT_NONE,DISABLE,DISABLE);
		
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
                break;
            }
            else
            {
#ifdef TY_DBG
                {
	                // Terry adds for debug, :-)
	                U8 au8StrBuf[100] = { 0 };
	                sprintf(au8StrBuf, "Ty, Get OCR succeed!\n");
	                atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
                }
#endif
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
                        if(SDver1card)
		     	      	{
                            voltage_validation = SUCCESS;
		     	      	}
			            /*Check for High capacity or Low capacity SDver2 card*/
                        else if(ocr_value &SD_HC_CCS_CHECK)
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

/*==========================================================================
FUNCTION: static int sd_get_rca (void)
DESCRIPTION:
   sd_get_rca () function will set RCA value of SD memory card.

ARGUMENTS PASSED:
   none

RETURN VALUE:
   This function will return RCA published from SD Memory Card.

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Send Command CMD3 with No Argument
  2.SD Memory card will publish its RCA which will be used for future references.
  3. Check for card current state. 
==============================================================================*/
static UINT32 sd_get_rca (void)
{
    command_t cmd;
    UINT32 card_state=0;
    UINT32 rca_request=0;
    command_response_t response;
	
    /* Configure CMD3 for SD card */
    /* 32bit card address is expected as Argument */
    card_command_config(&cmd, CMD3,
                              NO_ARG,
                              READ,
                              RESPONSE_48,
                              DATA_PRESENT_NONE,
                              ENABLE,
                              ENABLE);

    /* Get relative address of the card */
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
    card_command_config(&cmd, CMD9, card_address, READ, RESPONSE_136,
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

/*==========================================================================
FUNCTION: UINT32 sd_set_boot_partition (void)
DESCRIPTION:
  Set boot partition for Partition1

ARGUMENTS PASSED:
   None

RETURN VALUE:
   UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:

==============================================================================*/
static UINT32 sd_set_boot_partition(void)
{
    command_t cmd;
    UINT32 set_partition_status = FAIL;
    UINT8 response_data[SD_STATUS_SIZE];

    /* Change block length to 64 bytes */
    interface_config_block_info(ESDHC_CONFIG_BLOCK_64,
                                ONE,
                                ESDHC_READ_WATER_MARK_LEVEL_BL_64);

    /* Configure CMD6 to switch the command */
    card_command_config(&cmd, CMD6,
                              SD_BOOT_SWITCH_ARG,
                              READ,
                              RESPONSE_48,
                              DATA_PRESENT,
                              ENABLE,
                              ENABLE);

    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
        set_partition_status = FAIL;
    }
    else
    {
        /* Read 512 bits data structure returned from command CMD6 */
        interface_data_read((UINT32 *)response_data, SD_SWITCH_BLK_LEN);

        /* Check for valid response */
        if((response_data[SD_STATUS_PM_OFFSET] & SD_STATUS_PM_MASK) == SD_STATUS_PM_VAL)
        {
            /* Send CMD37 to select partition PARTITION1 */
            card_command_config(&cmd, CMD37,
                                      SD_PARTITION1,
                                      READ,
                                      RESPONSE_48_CHECK_BUSY,
                                      DATA_PRESENT_NONE,
                                      ENABLE,
                                      ENABLE);

            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
                set_partition_status = FAIL;
            }
            else
            {
                /* Check the status of card */
                set_partition_status = card_check_status(SD_CMD_SEL_PARTITION_TIMEOUT,
                                                         TRAN,
                                                         R1_OUT_OF_RANGE);
            }
        }
        else
        {
            set_partition_status = FAIL;
        }
    }

    /* Set block length to 512 bytes */
    interface_config_block_info(ESDHC_CONFIG_BLOCK_512,
                                ONE,
                                ESDHC_READ_WATER_MARK_LEVEL_BL_512);

    return set_partition_status;
}

/*==========================================================================
FUNCTION: static UINT32 sd_get_scr(void)
DESCRIPTION:
    Read SD SCR register information and extracts the SD card spec
    version and bus width.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    UINT32 - SUCCESS or FAIL.

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

Detailed Description:
    None
==============================================================================*/
static UINT32 sd_get_scr(void)
{
    command_t cmd;
    command_response_t response;
    UINT32 sd_scr_status = FAIL;
    UINT32 sd_bus_width = SD_BUS_WIDTH_1;
    UINT32 rd_data_buff[SD_RESPONSE_SCR_SIZE];
    UINT32 card_address = (Card_rca << CARD_RCA_SHIFT);

    /* Initialize the spec version to SD-1.x */
    sd_card_scr.spec_version = SD_CARD_1_0;

    /* Set the block length to 8 btyes. */
    interface_config_block_info(ESDHC_CONFIG_BLOCK_8,
                                ONE,
                                ESDHC_READ_WATER_MARK_LEVEL_BL_8);

    /* Configure CMD55 for SD card This command expects RCA as argument. */
    card_command_config(&cmd, CMD55,
                              card_address,
                              READ,
                              RESPONSE_48,
                              DATA_PRESENT_NONE,
                              ENABLE,
                              ENABLE);

    /* Issue CMD55 to SD Memory card */
    if(interface_send_cmd_wait_resp(&cmd) == SUCCESS)
    {
        /* Read Command response */
        response.format = RESPONSE_48;
        interface_read_response(&response);

        /*
         * Afetr giving ACMD Command, the R1 response should have
         * STATUS_APP_CMD set
         */
        if(response.cmd_rsp0 & R1_APP_CMD)
        {
            /*
             * Configure ACMD51 for SD card
             * This command expects No argument.
             */
            card_command_config(&cmd, ACMD51,
                                      NO_ARG,
                                      READ,
                                      RESPONSE_48,
                                      DATA_PRESENT,
                                      ENABLE,
                                      ENABLE);

            /* Issue ACMD51 to SD Memory card */
            if(interface_send_cmd_wait_resp(&cmd) == SUCCESS)
            {
                /* Read Response from eSDHC buffer */
                if(interface_data_read(rd_data_buff, ESDHC_CONFIG_BLOCK_8) == SUCCESS)
                {
                    /* Extract the SD spec version. */
                    sd_card_scr.spec_version = rd_data_buff[SD_SPEC_VER_OFFSET] & SD_SPEC_VER_MASK;

                    /* Extract the SD_BUS_WIDTHS. */
                    sd_bus_width = rd_data_buff[SD_BUS_WIDTH_OFFSET] & SD_BUS_WIDTH_MASK;
                    sd_card_scr.bus_width = sd_bus_width >> SD_BUS_WIDTH_SHIFT;

                    sd_scr_status = SUCCESS;
                }
            }
        }
    }

    /* Set block length to 512 bytes */
    interface_config_block_info(ESDHC_CONFIG_BLOCK_512,
                                ONE,
                                ESDHC_READ_WATER_MARK_LEVEL_BL_512);

    return sd_scr_status;
}

