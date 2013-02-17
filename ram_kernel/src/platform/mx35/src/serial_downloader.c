/*==================================================================================================
                                                                               
    Module Name:  SerialDownloader.c

    General Description: Serial Downloader for USB and UART 

====================================================================================================
Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.

This file contains copyrighted material. Use of this file is
restricted by the provisions of a Freescale Software License
Agreement, which has either been electronically accepted by
you or has been expressly executed between the parties.
  

Revision History:
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "su_basictypes.h"
#include "usb_common.h"
#include "usb_ipl_al_extern.h"
#include "usb_tl_al_extern.h"
#include "serial_downloader.h"
#include "bl_transreceiver.h"

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


