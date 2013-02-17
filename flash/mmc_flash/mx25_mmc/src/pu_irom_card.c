/*=================================================================================

    Module Name:  pu_irom_card.c

    General Description: Limited IROM MMC/SD Generic Driver

===================================================================================
                               Copyright: 2004,2005,2006,2007 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a 
                   Freescale Software License Agreement, which has either 
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.


Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number     Description of Changes
-------------------------   ------------    ----------   --------------------------
Prabhat singh              27/08/2007       TLSbo95910   pull up DAT3 line after card detection to behave data line 
Prabhat Singh                 20/08/2007      TLSbo95750 IOMUX config for SD card 
Prabhat Singh                 17/08/2007      Tlbso94839   Ported to Ringo 
Deepak Agarwal              30/July/2007   TLSbo94587   CE-ATA, Ported to Ringo.
Surender Kumar              07-Jun-2007     TLSbo93610   Porting for Marley
Surender Kumar (r66464)     09/15/2006      TLSbo79133 	 Initial implementation.
Suresh Kumar (r65753)       12-Feb-2006     TLSbo90616   Add 2 sec delay before any command

Portability: Portable to other compilers or platforms.
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
#include "pu_irom_esdhc.h"
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"
#include "pu_irom_sd.h"
#include "pu_irom_timer.h"

#ifdef TY_DBG
#include "channel.h"
#include "stdio.h"
#endif

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
#define MMCSD_INIT_DELAY 64

/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
UINT32 address_mode;
UINT32 Card_rca = 0x1;                   /* Relative Card Address */
card_ident Card_identification;		 /* Card Identification Data */
enum CARD_TYPE nCardType = CARD_NONE;

/*==========================================================================
                                    Global FUNCTIONS
==========================================================================*/

/*==========================================================================
FUNCTION: UINT32 card_init(int bus_width, UINT32 base_address)

DESCRIPTION:
   card_init() function will initialize the MMC/SD card devices.

ARGUMENTS PASSED:
   int bus_width
   UINT32 *base_address

RETURN VALUE:
   int - SUCCESS 0 (TRUE) or FAILURE 1

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Initialize the card corresponding to card type.
==============================================================================*/

UINT32 card_init(UINT32 bus_width, UINT32 base_address)
{
    UINT32 init_status = FAIL;
   
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: card_init\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* initialize Interface Controller */
    interface_init(base_address);

    /* Software Reset to Interface Controller */
    interface_reset(ESDHC_ONE_BIT_SUPPORT, ESDHC_LITTLE_ENDIAN_MODE);
    
    /* Enable Identification Frequency */
    interface_configure_clock(IDENTIFICATION_FREQ);
    
    /* Add delay of 2 msec, let mmc/sd card to initialize */
    GPT_delay(MMCSD_INIT_DELAY);
   
    /* Wait untill timer expires */ 
    while(!GPT_status());

    /* Disable Timer */
    GPT_disable();

    /* Issue Software Reset to card */
    card_software_reset(); 
    
	
    /* Check if the card is SD Memory Card */
     if(!sd_voltage_validation())
	   {
           nCardType = CARD_SD;
           /* Call SD Initialization Function */
           init_status = sd_init(bus_width);
       }
     else
     {
        /* Check if the card is MMC Memory Card*/
        if(!mmc_voltage_validation())
        {
            nCardType = CARD_MMC;
         
           /* Call MMC Initialization Function */
           init_status = mmc_init(bus_width);
        }
     }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: card_init\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return init_status;
}


/*==========================================================================
FUNCTION: UINT32 card_software_reset (void)
DESCRIPTION:
   card_software_reset () function will issue CMD0 to card. This gives
   software reset to card.

ARGUMENTS PASSED:
   None.

RETURN VALUE:
   int - SUCCESS (TRUE) or  FAILURE

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Issue CMD0 to MMC/SD card.
==============================================================================*/

UINT32 card_software_reset(void)
{
    command_t cmd;
    UINT32 response = FAIL;
	
    /*Configure CMD0 for MMC/SD card*/
    /*CMD0 doesnt expect any response */
    card_command_config (&cmd,CMD0,NO_ARG,READ,RESPONSE_NONE,
                    DATA_PRESENT_NONE,DISABLE,DISABLE);
	
    /*Issue CMD0 to MMC/SD card to put in active state */
    if(interface_send_cmd_wait_resp(&cmd) != FAIL)
    {
        response = SUCCESS;
    }
    
    return response;
}


/*==========================================================================
FUNCTION: UINT32 card_get_cid (void)
DESCRIPTION:
   card_get_cid () function will return the CID value of card.

ARGUMENTS PASSED:
   None.

RETURN VALUE:
   SUCCESS / FAILURE

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Issue CMD2 to card.
  2.Read the command response. Response will be expected in CMDRSP0,
    CMDRSP1, CMDRSP2, CMDRSP3 registers.
  3.Assign the response values to CID structures.
==============================================================================*/

UINT32 card_get_cid (void)
{

    command_t cmd;
    UINT32 cid_request=FAIL;
    command_response_t response;
	
   
    /* Configure CMD2 for card */
    /* No Argument is expected for CMD2 */
    card_command_config(&cmd,CMD2,NO_ARG,READ,RESPONSE_136,DATA_PRESENT_NONE,ENABLE,DISABLE);
	
    /* Issue CMD2 to card to determine CID contents */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Get cid fail!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        cid_request = FAIL; 
    }
	
    else
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Get cid succeed!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        /* Read Command response  */
        response.format= RESPONSE_136;
        interface_read_response (&response);
		
        /* Assign CID values to mmc_cid structures */
        Card_identification.cid0 = response.cmd_rsp0;
        Card_identification.cid1 = response.cmd_rsp1;
        Card_identification.cid2 = response.cmd_rsp2;
        Card_identification.cid3 = response.cmd_rsp3;
		
        /* Assign cid_request as SUCCESS */
        cid_request = SUCCESS;
    }
	
    return cid_request;
}

/*==========================================================================
FUNCTION: UINT32 card_set_data_transfer_mode (void)
DESCRIPTION:
   card_set_data_transfer_mode () function will put card in transfer mode.

ARGUMENTS PASSED:
   None

RETURN VALUE:
   SUCCESS / FAILURE

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1.Send CMD7 to put card in data transfer mode. 
    This command will select the card and put card in data transfer mode.
  2.CMD7 toggles card between stand by mode and data transfer mode.

==============================================================================*/

UINT32 card_set_data_transfer_mode (void)
{
    command_t cmd;
    UINT32 card_state = 0;
    UINT32 transfer_status =0;
    command_response_t response;
    UINT32 card_address = (Card_rca << RCA_SHIFT);
	
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Entry: Set trans mode,Card_rca:%d!\n", Card_rca);
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, card_address:%d\n", card_address);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Configure CMD7 for MMC card */
    /* 16bit card address is expected as Argument */
    card_command_config(&cmd,CMD7,card_address,READ,RESPONSE_48,
                    DATA_PRESENT_NONE,ENABLE,ENABLE);
	
    /* Sending the card from stand-by to transfer state
    */
    if(interface_send_cmd_wait_resp(&cmd) == FAIL)
    {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Select card failed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
        transfer_status = FAIL;
    }
    else
    {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Select card succeed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
        /* Configure CMD13 to read status of the card becuase CMD7 has R1b response */
            card_command_config(&cmd,CMD13,card_address,READ,RESPONSE_48,
                            DATA_PRESENT_NONE,ENABLE,ENABLE);

            if(interface_send_cmd_wait_resp(&cmd) == FAIL)
            {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, read status failed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
                transfer_status = FAIL;
            }

            else
            {

#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, read status succeed!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
                /* Read Command response */
                response.format = RESPONSE_48;
                interface_read_response (&response);
		
                card_state = ((UINT32) (response.cmd_rsp0 & MMCSD_R1_STATUS_CURR_STATE) >> CURR_STATE_SHIFT);
	
                if(card_state == TRAN)
                {
                     transfer_status = SUCCESS;
			
	        }
		
	        else
	        {
                     transfer_status = FAIL;
                }
            }	
		
    }
		
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Exit: Set trans mode!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
    return transfer_status;
	
}

/*==========================================================================
FUNCTION: UINT32 card_check_status(UINT32 timeout,
                                   UINT32 card_state,
                                   UINT32 status_bits)
DESCRIPTION:
   Check the card satus by sending CMD13.

ARGUMENTS PASSED:
   UINT32 timeout     - Timeout used for GPT.
   UINT32 card_state  - Expected state of card
   UINT32 status_bits - Expected ERROR bit/bits set by card

RETURN VALUE:
   UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
==============================================================================*/

UINT32 card_check_status(UINT32 timeout, UINT32 card_state, UINT32 status_bits)
{
    command_t cmd;
    UINT32 card_status = FAIL;
    command_response_t response;
    UINT32 card_address = (Card_rca << CARD_RCA_SHIFT);

    /* Start timer for status polling timeout */
    GPT_delay(timeout);

    while(!GPT_status())
    {
        /* Configure CMD13 to read status of the card */
        card_command_config(&cmd, CMD13,
                                  card_address,
                                  READ,
                                  RESPONSE_48,
                                  DATA_PRESENT_NONE,
                                  ENABLE,
                                  ENABLE);

        if(interface_send_cmd_wait_resp(&cmd) == FAIL)
        {
            card_status = FAIL;
            break;
        }
        else
        {
            /* Read Command response */
            response.format = RESPONSE_48;
            interface_read_response(&response);

            /* Check for SWITCH command error bits */
            if(response.cmd_rsp0 & status_bits)
            {
                card_status = FAIL;
                break;
            }

            /* Check for the present state of card */
            if(R1_CURRENT_STATE(response.cmd_rsp0) == card_state)
            {
                card_status = SUCCESS;
                break;
            }
        }
    } /* while(!GPT_status()) */

    /* Disable Timer */
    GPT_disable();

    return card_status;}


/*==========================================================================
FUNCTION:  void card_command_config (command_t)
DESCRIPTION:
   card_command_config () will configure the command paramteres for card.

ARGUMENTS PASSED:
   command_t

RETURN VALUE:
   UINT32

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

Detailed Description:
  1. Configure Commnand structure according to passed arguments.  
==============================================================================*/

void card_command_config (command_t *cmd_config,UINT32 index, UINT32 argument,
                                xfer_type_t transfer,response_format_t format, data_present_select data,
                                crc_check_enable crc, cmdindex_check_enable cmdindex )
{
	
    command_t *cmd;
	
    /* Assign cmd to cmd_config */
    cmd = cmd_config;
	
    /* Configure Command index */	
    cmd->command = index;
	
    /* Configure Command Argument */
    cmd->arg = argument;
	
    /* Configure Data transfer type */
    cmd->data_transfer = transfer;
	
    /* Configure Response Format */
    cmd->response_format = format;
	
    /* Configure Data Present Select */
    cmd->data_present = data;
	
    /* Configiure CRC check Enable */
    cmd->crc_check = crc;
	
    /*Configure Command index check enable */
    cmd->cmdindex_check = cmdindex;

	/*Configure Block count enable */
    cmd->block_count_enable_check = data ? ENABLE : DISABLE;

	/*Configure Multi single block select */
	cmd->multi_single_block = SINGLE;
}
