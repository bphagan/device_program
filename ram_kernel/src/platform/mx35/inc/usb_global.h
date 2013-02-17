#ifndef USB_GLOBAL_INCLUDE /* To prevent inadvertently including a header twice */
#define USB_GLOBAL_INCLUDE  

#ifdef __cplusplus  /* allow #include in a C++ file (only put this in .h files) */
extern "C" {
#endif

/************** HEADER FILE INCLUDES ******************************************/
#include "su_basictypes.h"
/******************************************************************************/

/* Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.

This file contains copyrighted material. Use of this file is
restricted by the provisions of a Freescale Software License
Agreement, which has either been electronically accepted by
you or has been expressly executed between the parties.
  
   DESCRIPTION: 
      This file contains the extern references and typedefs associated with 
      all global variables shared by other files. 
 
 ************** REVISION HISTORY **********************************************
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
