/*==================================================================================================

====================================================================================================

    Module Name:  usb_ipl_al_extern.h

    General Description: This file contains the extern variable of hw interface layer which are 
    exposed to application layer.
====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Bharat Bhushan               07/20/2006     TLSbo73521   Cleanup of code. 
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#ifndef USB_IPL_AL_EXTERN_H
#define USB_IPL_AL_EXTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"

typedef struct {
    U32 buffer_address;
    U32 buffer_size;
}usb_plat_config_data_t;

extern void ipl_init(usb_plat_config_data_t *config_data_ptr);


#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* USB_IPL_AL_EXTERN_H */


