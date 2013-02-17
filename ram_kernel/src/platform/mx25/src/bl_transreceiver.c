/*==================================================================================================

    Module Name:  bl_transreceiver.c

    General Description: This file contains the Transreceiver initalisation.

====================================================================================================
    Copyright (C) 2008, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Radhish                      23/05/2008     ENGcm05804   Incorrect GPIO PSR read of GPIO_A
Radhish                      05/05/2008     ENGcm05522   Set the OEXTEN bit before enabling the ulpi mode
Radhish                      23/04/2008     ENGcm05364   Setting of PFSC,Mode select has to be done 
                                                         before R/S bit getting set
Radhish                      08/04/2008     ENGcm05181   NFC Buffer for usb operation   
Radhish                      19/03/2008     ENGcm04722   OTG PWR pin Fix
Radhish                      05/02/2008     ENGcm03236   Porting for Senna
Prabhat Singh                24/09/2007     engcm00253  IOMUX config for serial and ULPI interface
Prabhat singh                 08/08/2007    TLSbo94951   Addition of Philips USB ISP1301 PHY support                      
Prabhat Singh                24/07/2007      TLSBo94950  Added support for USB UTMI interface and  corrected comment for USB clock calculation  
Sai Kiran Bollu               07/24/2007     TLSbo94949   Changed to 6Wire mode for ringo and removed compilation warnings.
Balvinder Singh              30/05/2007     TLSbo93193   Corrected the GPIO programming of GPIO25(GP_SP_A5) 
Balvinder Singh              03/12/2007     TLSbo92286   Ported ULPI HS from Skyeplus
Bharat Bhushan               09/25/2006     TLSbo78968   New Serial Boot strategy implementation.
Bharat Bhushan               05/10/2006     TLSbo70190   Initial Version ( USB Layer Architecture).

-------------------------   ------------    ----------   -------------------------------------------
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#include "suapi.h"
#include "bl_transreceiver.h"
#include "usb_tl_al_extern.h"
#include "usb_ipl_al_extern.h"
#include "usb_hwinterface_layer.h"
#include "usb_transaction_layer.h"
#include "hapi_gpio_defs.h"
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/
UINT8 __attribute__((section("usb_buffer_no_init"))) usb_buffer[BUFFER_SIZE];
/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/
/*=================================================================================================
                                 GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/

void usb_otg_interface_init(void);
void usb_utmi_interface_enable(void);

/*==================================================================================================

                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/*==================================================================================================
                                     GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================

FUNCTION: usb_init

DESCRIPTION: Initialize the usb interface and usb OTG

ARGUMENTS PASSED:
   None

RETURN VALUE:
   None

PRE-CONDITIONS:
   USB path is being followed.

POST-CONDITIONS:
   None

IMPORTANT NOTES:

==================================================================================================*/
 void usb_init(void)
{

    /* Clock initialisation not needed as the default clock is 60 MHz .  
   
       Fref = 24MHz
       MFI = 10
       PDF = 1 => divide by 2
       MFN = 0
       MFD = 5
       Fout = 2 * Fref ( MFI * ( MFN / MFD))/PDF = 2 * 24 * ( 10 + ( 0/5))/2 = 2 * 24 * 10 / 2  = 240 MHz

       USB_DIV = 4 => Divide by 4
        
       clock to USBOTG = Fout/USB_DIV => 240 / 4 = 60MHz
     */ 
    /*Unlock the Nfc Buffer region used for usb*/

    /* initialise the interface ( SERIAL 3Wire/ ULPI / UTMI) */
    usb_otg_interface_init();

}

/*==================================================================================================

FUNCTION: usb_otg_interface_init

DESCRIPTION: Initialize the transreceiver .

ARGUMENTS PASSED:
   None
   
RETURN VALUE:
   None
  
PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

IMPORTANT NOTES:

==================================================================================================*/

#define CLOCK_REG_ADDR               (0x53f80000)
#define HAPI_CLOCK_PER_GPT_EN        (0x00000020) /*CGCR0*/
#define HAPI_CLOCK_AHB_USBOTG_EN     (0x10000000) /*CGCR0*/
#define HAPI_CLOCK_IPG_WDOG_EN       (0x00080000) /*CGCR2*/

void usb_otg_interface_init(void)
{
    usb_plat_config_data_t config_data_ptr;
    //UINT32 usb_src;
    UINT32 temp;

    /*Enable the clock output of GPIO,IOMUX,GPT */
    (*(VP_U32)(CLOCK_REG_ADDR + 3 * 4)) |= (HAPI_CLOCK_PER_GPT_EN | HAPI_CLOCK_AHB_USBOTG_EN);
    (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= (HAPI_CLOCK_PER_GPT_EN | HAPI_CLOCK_AHB_USBOTG_EN);
    (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= HAPI_CLOCK_IPG_WDOG_EN;

    /* Read the USB Source E-fuse . b01- External ULPI PHY, b10-Ext Serial PHY (ATLAS), b10-Ext Serial PHY (isp1301), b00-Internal UTMI PHY */
    // usb_src = ((*(VP_U32)HAPI_CLOCK_REG_RCSR_ADDR) & HAPI_RCSR_BT_USB_SRC) >> HAPI_RCSR_BT_USB_SRC_SHIFT;
    
    /*POWER POLARITY related configuration has to be Done before GPIO_A pad is 
      Switched to OTG PWR Functionality*/
    /*Set the PKE bit to 0 to disable pull/keeper */
    *(VP_U32)(IOMUX_SW_PAD_CTRL_REG_ADDR + HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_PWR * 4) = HAPI_USBOTG_PWR_PAD_VALUE;

    /* Read the GPIO_A and set the POWER_POL (PP)bit as shown below. 
     * if the external IC is High active, a pull down on GPIO_A is added on the board.
     * ROM will read back 0 with GPIO 
     * If the external lC is Low active, a pull up on GPIO_A is added on the board.
     * ROM  will read back 1 with GPIO 
     * Now if the ROM reads back 0,then it is confirmed that the ext IC is High Active.
     * So ROM shud write POWER_POL(PP) bit to 1. 
     * And if the ROM reads back 1,then it is confirmed that the ext IC is Low Active.
     * So ROM shud write POWER_POL(PP) bit to 0 
     */
    temp = (*(VP_U32)(IOMUX_SW_MUX_CTRL_REG_ADDR + 8));
    temp = (temp) & 0x00000001;


    if (temp == 0)
    {
        /*Set POWER POL(PP) bit to 1*/
    
        temp  = *(VP_U32)USB_CONTROL_REG;
    
        temp |= USB_CTRL_PP_SET;
        
        *(VP_U32)USB_CONTROL_REG = temp;
    }
    else
    {
        /*Set the POWER POL(PP) bit to 0 */
        temp  = *(VP_U32)USB_CONTROL_REG;
    
        temp &= ~USB_CTRL_PP_SET;
         
        *(VP_U32)USB_CONTROL_REG = temp;
     
    }
     
    /* Configure GPIO_A for OTG_PWR pin Funcitonality */ 
    if ((HAPI_IOMUX_USB_PWR_ULPI_SEL & 512) == 512)
    {
        UINT32 rnum, roffset, cfg_val, tmp;

        rnum = (HAPI_IOMUX_USB_PWR_ULPI_SEL >> IOMUX_REG_NUM_SHIFT) & BYTE_MASK;
        roffset = (HAPI_IOMUX_USB_PWR_ULPI_SEL >> IOMUX_REG_OFFSET_SHIFT) & REGOFST_MASK;
        cfg_val = (HAPI_IOMUX_USB_PWR_ULPI_SEL & BYTE_MASK);
        tmp = *((VP_U32)(IOMUX_SW_MUX_CTRL_REG_ADDR + (rnum * 4)));
        tmp &= ~(BYTE_MASK << (roffset * 8));
        tmp |= (cfg_val << (roffset * 8));
         *((VP_U32)(IOMUX_SW_MUX_CTRL_REG_ADDR + (rnum * 4))) = tmp;
    }
    *(VP_U32)(IOMUX_SW_PAD_CTRL_REG_ADDR + HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_PWR * 4) = HAPI_USBOTG_PWR_PAD_VALUE;

        
    /* IP Layer Initialisation */
    config_data_ptr.buffer_address = (UINT32)usb_buffer;
	config_data_ptr.buffer_size  = BUFFER_SIZE;

    ipl_init(&config_data_ptr);
        
    *(VP_U32)USB_OTG_SUBSCFG &= ~0x7; /* Set the AHBBRST to 3b'000   */

    //usb_utmi_interface_enable();
}

/*==================================================================================================

FUNCTION: usb_utmi_interface_enable

DESCRIPTION: Initialize and enable the utmi interface of communication.

ARGUMENTS PASSED:
   None

RETURN VALUE:
   None

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

IMPORTANT NOTES:

==================================================================================================*/
void usb_utmi_interface_enable(void)
{
    UINT32 temp;

    /* set it to be utmi interface */
    temp  = *(VP_U32)USB_OTG_PORTSC1;
    temp &= ~USB_OTG_TRANS_MASK;
    temp |= USB_OTG_TRANS_UTMI;
    temp &= ~USB_OTG_FS_ONLY;
    temp |= USB_OTG_TRANS_WIDTH;

    *(VP_U32)USB_OTG_PORTSC1 = temp;

	/*Enable UTMI interface in PHY control Reg*/
    *(VP_U32)USB_PHY_CTR_FUNC|=	USB_UTMI_PHYCTRL_UTMI_ENABLE;  
   	 
 
    
}

