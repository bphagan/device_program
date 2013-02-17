/*==================================================================================================

====================================================================================================

    Module Name:  usb_common.h

    General Description: This file contains the variables common to all usb 
    layers.
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

#ifndef USB_COMMON_H
#define USB_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"

/* USB Device State which are handled by DCD */
typedef enum
{
    USB_DEV_DUMMY_STATE,
    USB_DEV_DEFAULT_STATE,
    USB_DEV_ADDRESSED_STATE,
    USB_DEV_CONFIGURED_STATE
}usb_state_t;


/* Buffer descriptor used for data transfer on USB */
typedef struct {
    void * buffer ;	/* Address of the buffer to/from data is to be transmitted */
    U32 size ;          /*  size of the buffer to  be transmitted/recieved */
    U32 bytes_transfered; /* actual number of bytes transfered */
}usb_buffer_descriptor_t;

/* Status of all transaction on USB */
typedef enum
{
    USB_SUCCESS,
    USB_FAILURE,
    USB_INVALID = -1 /* Always Keep this entry in last */
}usb_status_t;

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* USB_COMMON_H */


