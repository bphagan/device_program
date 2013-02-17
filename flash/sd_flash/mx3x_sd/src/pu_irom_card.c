/*****************************************************************************
** pu_irom_card.c
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
 * @file pu_irom_card.c
 *
 * @brief source code for the sd/mmc card operation
 *
 * @ingroup mmc
 */

//#define TY_DBG

/*=================================================================================
                                        INCLUDE FILES
==================================================================================*/
#include "pu_irom_sdhc_ip.h"
#include "pu_irom_card.h"
#include "pu_irom_sd.h"
#include "tortola_irom_timer.h"
#include "config_pad_mode.h"
#include "Atlas_spi.h"

#ifdef TY_DBG
#include "channel.h"
#include "stdio.h"
#endif

/*================================================================================
                         LOCAL FUNCTION PROTOTYPES
=================================================================================*/
static void aips_init();
static void sd_buffer_en(void);
static void sd_power_en(void);

/*================================================================================
                          Hash Defines And Macros
=================================================================================*/
#define MMCSD_INIT_DELAY 64

#define SDHC_CMD_DAT_CONT_ADDR              0x5000400c
#define SDHC_CMD_DAT_CONT_INIT_BIT_MASK     0x00000080

#define SPBA_SDHC1_PRR          SPBA_PRR1
#define SDHC_BASE_ADDR          (SDHC1_BASE_ADDR+0x0)  //  TEST on SDHC1
#define SDHC_EVENT              20
#define SPBA_SDHC_PRR           SPBA_SDHC1_PRR 
#define SDHC_INT_ROUTINE        SDHC1_INT_ROUTINE 

#define GRANT_SDMA_ACCESS_TO_SPBA \
        do { \
                reg32_write(SPBA_SDHC_PRR, 5); \
        } while (5 != (reg32_read(SPBA_SDHC_PRR)&5))


/*=========================================================================
                                      GLOBAL Variables
==========================================================================*/
UINT32 Card_rca = 0x1;                   /* Relative Card Address */
card_ident Card_identification;		 /* Card Identification Data */

/*==========================================================================
                                    Global FUNCTIONS
==========================================================================*/

/*!
 * init the aips 
 *
 */
void aips_init()
{
	
	*(U32*)0x43F00040 =0x0;  // AIPS1_OPACR0_7
	*(U32*)0x43F00044 =0x0; // AIPS1_OPACR8_15
	*(U32*)0x43F00048 =0x0;  // AIPS1_OPACR16_23
	*(U32*)0x43F0004C =0x0;  // AIPS1_OPACR24_31
	*(U32*)0x43F00050 =0x0;  // AIPS1_OPACR32_33

	*(U32*)0x43F00000 =0x77777777;  // AIPS1_MPROT0_7
	*(U32*)0x43F00004 =0x77777777;  // AIPS1_MPROT8_15

	// configure AIPS2
	*(U32*)0x53F00040 =0x0;  // AIPS2_OPACR0_7
	*(U32*)0x53F00044 =0x0;  // AIPS2_OPACR8_15
	*(U32*)0x53F00048 =0x0;  // AIPS2_OPACR16_23
	*(U32*)0x53F0004C =0x0;  // AIPS2_OPACR24_31
	*(U32*)0x53F00050 =0x0;  // AIPS2_OPACR32_33

	*(U32*)0x53F00000 =0x77777777;  // AIPS2_MPROT0_7
	*(U32*)0x53F00004 =0x77777777;  // AIPS2_MPROT8_15
	
}

/*!
 * initialize the MMC/SD/CE-ATA card devices.
 * @bus_width
 * @base_address
 * @RETURN
   int - SUCCESS 0 (TRUE) or FAILURE 1
 * Initialize the card corresponding to card type.
 */

UINT32 card_init(UINT32 bus_width, UINT32 base_address)
{
    UINT32 init_status = FAIL;
    //UINT32 init_status = -20;
   
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: card_init\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

   	aips_init();
 
    sd_power_en();
    //sd_buffer_en();

    /* set voltage to 3V, adjustable resistor to 3.15V */
    //reg16_write(0xB4000004,0x3000); 

    //GRANT_SDMA_ACCESS_TO_SPBA;
    //sdma_init();

    wait(50000);
    /* initialize iomax */
    //card_config_iomax();

    /* initialize Interface Controller */
    interface_init(base_address);

    /* Software Reset to Interface Controller */
    interface_reset();
    
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
    card_multiple_voltage_support();
    
    /* Check if the card is SD Memory Card */
    init_status = sd_voltage_validation();
    if(!init_status)
    {
        /* Call SD Initialization Function */
        init_status = sd_init(bus_width);
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


/*!
 * read data from MMC/SD card for specified length 
 * from specified offset and copy it a dest pointer.
 * @dest_ptr
 * @len
 * @offset
 * @return the data len
 */
UINT32 card_data_read (UINT32 *dest_ptr,UINT32 len,UINT32 offset)
{
    UINT32 read_status = FAIL;
	
    read_status = sd_data_read(dest_ptr, len, offset, 0);

    if(read_status)
    {    
        len=0;
    }
    return len;
	
}


/*!
 * issue CMD0 to card. This gives software reset to card.
 * @return
 * int - SUCCESS (TRUE) or  FAILURE
*/

UINT32 card_software_reset(void)
{
    command_t cmd;
    UINT32 response = FAIL;

    /*Configure CMD0 for MMC/SD card*/
    /*CMD0 doesnt expect any response */
    card_command_config (&cmd, CMD0, NO_ARG, READ, RESPONSE_NONE,
                    DATA_PRESENT_NONE, DISABLE,DISABLE);
	
    /*Issue CMD0 to MMC/SD card to put in active state */
    if (interface_send_cmd_wait_resp(&cmd) != FAIL)
    {
        response = SUCCESS;
    }
	
    return response;
}

/*!
 * issue CMD8 to card. Sends SD Memory Card interface condition, which includes host supply voltage information and asks the card whether card supports voltage.
 * @return
 * int - SUCCESS (TRUE) or  FAILURE
*/
UINT32 card_multiple_voltage_support(void)
{
    command_t cmd;
    UINT32 response = FAIL;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: card_multiple_voltage_support\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /*Configure CMD8 for MMC/SD card*/
    card_command_config(&cmd, CMD8, 0x000001aa, READ, RESPONSE_48,
                    DATA_PRESENT_NONE, DISABLE, DISABLE);
	
    /*Issue CMD0 to MMC/SD card to put in active state */
    if (interface_send_cmd_wait_resp(&cmd) != FAIL)
    {
        response = SUCCESS;
    }
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: card_multiple_voltage_support\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return response;
}

/*!
 * function will return the CID value of card.
 * @return
 * int - SUCCESS (TRUE) or  FAILURE
 */

UINT32 card_get_cid (void)
{

    command_t cmd;
    UINT32 cid_request=FAIL;
    command_response_t response;
	
   
    /* Configure CMD2 for card */
    /* No Argument is expected for CMD2 */
    card_command_config(&cmd, CMD2,NO_ARG,READ,RESPONSE_136,DATA_PRESENT_NONE,ENABLE,DISABLE);
	
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

/*!
 * put card in transfer mode.
 * @return
 * int - SUCCESS (TRUE) or  FAILURE
 */

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

    /* Configure CMD7 for SD card */
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


/*!
 * configure the command paramteres for card.
 * @cmd_config
 * @index
 * @argument
 * @transfer
 * @format
 * @data
 * @crc
 * @cmdindex
 */

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
}

UINT32 card_config_iomax(void)
{
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Entry: card_config_iomax\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    config_pad_settings(SD1_CMD, 0x200); // Loopback mode required at the cmd pin
    config_pad_mode(SD1_CLK,   func_out, func_in);
    config_pad_mode(SD1_CMD,   func_out, func_in);
    config_pad_mode(SD1_DATA0, func_out, func_in);
    config_pad_mode(SD1_DATA1, func_out, func_in);
    config_pad_mode(SD1_DATA2, func_out, func_in);
    config_pad_mode(SD1_DATA3, func_out, func_in);

    wait(50000);
  
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, Exit: card_config_iomax\n");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return 0;
}

void sd_buffer_en(void)
{

 // int i;
//  mxc_gpio_init();
  //SW_MUX_CTL_M_REQUEST_M_GRANT_CSI_D4_CSI_D5

	config_pad_mode(GPIO3_0, gpio_out, gpio_in);
	*(P_U32)GPIO3_GDIR0 |= 0x00000001;
//	*(P_U32)GPIO3_DR0 |= 0x00000002;
	*(P_U32)GPIO3_DR0 |= 0x00000001;

}

void sd_power_en(void)
{
	U32 Atl_ID;
	
	Atlas_spi_init();
	
	Atl_ID=Atlas_read_reg(ATLAS_ID);
	
	Atlas_write_reg(PWR_MISC, GPO1_EN|GPO2_DIS|GPO3_DIS|GPO4_DIS);

	wait(5000);
}

void wait(int time) 
{
	int i;
	for (i = 0; i < time; ) 
        i++;
}

