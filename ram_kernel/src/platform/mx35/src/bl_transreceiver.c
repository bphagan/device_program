/*==================================================================================================

    Module Name:  bl_transreceiver.c

    General Description: This file contains the Transreceiver initalisation.

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
#include "bl_transreceiver.h"
#include "usb_tl_al_extern.h"
#include "usb_ipl_al_extern.h"
#include "usb_hwinterface_layer.h"

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

==================================================================================================*/
void usb_otg_interface_init(void)
{
    usb_plat_config_data_t config_data_ptr;

    /* Read the USB Source E-fuse . b01- External ULPI PHY, b10-Ext Serial PHY (ATLAS), b10-Ext Serial PHY (isp1301), b00-Internal UTMI PHY */

    /* IP Layer Initialisation */
    //config_data_ptr.buffer_address = 0x88000000;//0xbb000000;//(UINT32)usb_buffer;
    memset(usb_buffer, 0, BUFFER_SIZE);
    config_data_ptr.buffer_address = (UINT32)usb_buffer;
    config_data_ptr.buffer_size  = BUFFER_SIZE;

    ipl_init(&config_data_ptr);
	
    /* Enable the UTMI interface */
    usb_utmi_interface_enable();

    *(VP_U32)USB_OTG_SUBSCFG &= ~0x7; /* Set the AHBBRST to 3b'000   */

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
    
}

