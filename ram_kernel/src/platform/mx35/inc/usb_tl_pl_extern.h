/*==================================================================================================

====================================================================================================

    Module Name:  usb_tl_pl_extern.h

    General Description: This file contains the extern variable of transaction layer which are 
    exposed to Protocol Layer.
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

#ifndef USB_TL_PL_EXTERN_H
#define USB_TL_PL_EXTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"
#include "usb_common.h"

extern usb_status_t tl_receive_data(usb_buffer_descriptor_t* bd);
extern usb_status_t tl_send_data(usb_buffer_descriptor_t* bd);


#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* USB_TL_PL_EXTERN_H */
