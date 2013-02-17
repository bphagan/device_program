/*==================================================================================================

    Module Name:  bl_transreceiver.c

    General Description: This file contains the Transreceiver initalisation.

====================================================================================================
    Copyright (C) 2006,2007,2008  Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Prabhat Singh                01/02/2008     engcm03206   USB ULPI phy miss trigerring issue  
Prabhat Singh              29/01/2008       Engcm03148          USB lpb flow modification 
Siva Pothireddy              04/01/2008      engcm02650   Added clk changes for USB.
Siva Pothireddy               11-Jan-2008   ENGcm02768   Change in reading the BT USB SRC 1 0 from the SBMR. 
Siva Pothireddy               01-Dec-2007   engcm02041   usb_init changes,included serial PHY. 
Prabhat Singh                  23/11/2007      Engcm02065   Iomux changes for ULPI and serial mode
Prabhat Singh                 20/11/2007       engcm01902   Device module (usb,uart etc..)  clock changes 
Suresh Kumar                 10-Sep-2007    ENGcm00389   UART/USB polling design change.
Mahima Verma                 20-Aug-2007    TLSbo95872   Iomux changes.
Mahima Verma                 11-Jun-2007    TLSbo93857   Ported to Marley.
Suresh Kumar                 18-Oct-2006    TLSbo80774   Porting to Zappa.
Bharat Bhushan               24-Aug-2006    TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               20/07/2006     TLSbo73521   New Boot ROM Design Support for USB/UART 
                                                         Serial Downloader
Bharat Bhushan               28/06/2006     TLSbo72164   Moana 6-Wrie Serial Interface Support.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
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
To switch into ULPI mode ROM code need to following steps to avoid USB phy miss triggered 
in case of ULPI mode as defalut mode is Serial.

1. we should make sure to set ULPI_STP(or EIM_CS2) pin to High, either by GPIO out 1 or GPIO input  with external pullup resistor
2. switch EIM_D[24-31] into ULPI_DAT mode
3. after ULPI_STP is high, we can switch the ULPI_DAT into input mode by set PTS into non-serial mode and non-ulpi mode.
4. After that, we can switch the EIM_CS2 pin into ULPI_STP mode
5. enable otg_ext_clk_en, bit24 of USB_CTRL_1.
6. switch PTS into ulpi mode.  

==================================================================================================*/
void usb_otg_interface_init(void)
{
    usb_plat_config_data_t config_data_ptr;
        
    /* IP Layer Initialisation */
    config_data_ptr.buffer_address = (UINT32)usb_buffer;
    config_data_ptr.buffer_size  = BUFFER_SIZE;

    ipl_init(&config_data_ptr);

    /* Enable the UTMI interface */
    usb_utmi_interface_enable();
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
    U32 temp;
   

    /* set it to be utmi interface */
    temp  = *(VP_U32)USB_OTG_PORTSC1;
    temp &= ~USB_OTG_TRANS_MASK;
    temp |= USB_OTG_TRANS_UTMI;
    temp &= ~USB_OTG_FS_ONLY;
    temp |= USB_OTG_TRANS_WIDTH;

    *(VP_U32)USB_OTG_PORTSC1 = temp;
    
}
