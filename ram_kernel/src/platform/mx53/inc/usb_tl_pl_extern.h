/*==================================================================================================

====================================================================================================

    Module Name:  usb_tl_pl_extern.h

    General Description: This file contains the extern variable of transaction layer which are 
    exposed to Protocol Layer.
====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
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
