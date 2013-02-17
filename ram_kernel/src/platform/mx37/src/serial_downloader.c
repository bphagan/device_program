/*==================================================================================================

    Module Name:  SerialDownloader.c

    General Description: Serial Downloader for USB and UART

====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Siva Pothireddy              07-Jul-2008    ENGcm06427   Warnings Fixed.
Mahima Verma                 19-Jul-2007    TLSbo94597   Changes in USB to support simulator testing.
Suresh Kumar                 13-Oct-2006    TLSbo80774   Serial mode support
Suresh Kumar                 30/08/2006     TLSbo76529   Porting to Zappa.
Bharat Bhushan               28/06/2006     TLSbo72164   Clock programming for USB Core is done.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
-------------------------   ------------    ----------   -------------------------------------------
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#include "su_basictypes.h"
#include "usb_common.h"
#include "usb_ipl_al_extern.h"
#include "usb_tl_al_extern.h"
#include "serial_downloader.h"
#include "bl_transreceiver.h"
#include "usb_transaction_layer.h"
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/

/*=================================================================================================
                                 GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
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

FUNCTION: serial_downloader_usb

DESCRIPTION: Initialize the USB and starts the parser

ARGUMENTS PASSED:
   None

RETURN VALUE:
   None

PRE-CONDITIONS:
   USB path is being followed.

POST-CONDITIONS:
   None

IMPORTANT NOTES:
   Never returns

==================================================================================================*/

void serial_downloader_usb(void)
{
    usb_state_t state;
    /* Handle bus reset */
    tl_handle_bus_reset();

    /* Transfer Layer Initialisation */
    tl_init();

    /* Get the state of the USB  */
    state = tl_get_state();
    /* Enumeration the USB Device. */
    while( state != USB_DEV_CONFIGURED_STATE )
    {
        /* enumeration of usb */
        tl_configure();
	    
        /* Get the state of the USB  */
	    state = tl_get_state();
    }
}

