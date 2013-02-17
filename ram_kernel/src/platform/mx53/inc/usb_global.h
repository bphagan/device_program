#ifndef USB_GLOBAL_INCLUDE /* To prevent inadvertently including a header twice */
#define USB_GLOBAL_INCLUDE  

#ifdef __cplusplus  /* allow #include in a C++ file (only put this in .h files) */
extern "C" {
#endif

/************** HEADER FILE INCLUDES ******************************************/
#include "su_basictypes.h"
/******************************************************************************/

/* (c) Copyright Motorola 1999-2000, All rights reserved.        
   Motorola Confidential Proprietary
   Contains confidential proprietary information of Motorola, Inc.
   Reverse engineering is prohibited.
   The copyright notice does not imply publication.
  
   DESCRIPTION: 
      This file contains the extern references and typedefs associated with 
      all global variables shared by other files. 
 
 ************** REVISION HISTORY **********************************************
  
   Date       Author      Reference
   ========   ========    ==========================
   99-10-17   lshen       CSGce38855 - usb global.
              Definittions of USB global constants and typedefs.
              - Initial file creation.
   99-11-22   hhuang      CSGce38855 - usb global.
              Modified the event definitions for changes related to work with the
              generic software event handler.
              Also moved definition of the setup packet size from usb_ep0_parser.c
              to this file.   
   99-12-15   hfeng       CSGce43609 - usb global
              Added USB_DSP_ENDPOINT_T for supporting usb mdi.
   00-01-24   Udi Elran   CSGce88170 -usb globals.
              Modified to support Neptune's USB.  
   01-10-25   Yuval Namir   LIBbb09596 -usb globals.
              Update defines to support Neptune's USB.  
   02-07-10   Yuval Namir   LIBbbxxxxx -usb globals.
              Update defines to support Neptune_LTS USB.  
   02-08-01   buo001     LIBbb47316
              LTS catchup to LCA TA02_G_06.03.15I (r1.2.1).
   02-10-30   bge008     LIBbb63679
              LTS catchup to LCA C350_G_09.04.01I.
   02-12-02   byn016     LIBbb62547
              Changes needed for NEPTUNE_LTS IROM 2.0
   04-29-04   wlss26     LIBee00646
              Clean up for Argon SCM-A11 ROM
   04-04-29   bss043
              Argon+/SCMA11 USB driver support

*/
/************** CONSTANTS *****************************************************/

/* Default device address */
#define USB_DEFAULT_ADDR  0x00

#ifndef NULL
#define NULL 0
#endif

/************** STRUCTURES, ENUMS, AND TYPEDEFS *******************************/

typedef enum {
	USB_DEFAULT_STATE,
	USB_ADDRESSED_STATE,
	USB_CONFIGURED_STATE,
	USB_SUSPENDED_STATE
	} USB_DEVICE_STATE_T;

/************** FUNCTION PROTOTYPES *******************************************/

/************** CLASS DEFINITIONS *********************************************/

/************** GLOBAL VARIABLES **********************************************/

#ifdef __cplusplus /* allow #include in a C++ file (only put this in .h files) */
}
#endif
#endif /* end of - prevent inadvertently including a header file twice */
