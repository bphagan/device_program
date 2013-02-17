/*==================================================================================================

====================================================================================================

    Module Name:  usb_ipl_al_extern.h

    General Description: This file contains the extern variable of hw interface layer which are 
    exposed to application layer.
====================================================================================================
Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.

This file contains copyrighted material. Use of this file is
restricted by the provisions of a Freescale Software License
Agreement, which has either been electronically accepted by
you or has been expressly executed between the parties.

Revision History
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


