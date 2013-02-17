/*==================================================================================================

====================================================================================================

    Module Name:  bl_transreceiver.h

    General Description: This file contains the defines of transreceiver .
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

#ifndef BL_TRANSRECEIVER_H
#define BL_TRANSRECEIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"

#define SERIAL_6WIRE

/* Buffer memory allocated for USB Core for data transfer */
#define BUFFER_SIZE             0x800

#ifdef SERIAL_3WIRE

#define TRANS_USB0_REG_VAL      0x000A1060
#define TRANS_USB0_REG_MASK     0xFFFFFFFF

#endif

#ifdef SERIAL_6WIRE

#define TRANS_USB0_REG_VAL		0x000E1060
#define TRANS_USB0_REG_MASK     0xFFFFFFFF

#endif

/* USB OTG specific hash defines */
#define USB_OTG_TRANS_MASK      0xC0000000
#define USB_OTG_TRANS_SERIAL    0xC0000000
#define USB_OTG_TRANS_ULPI      0x80000000
#define USB_OTG_TRANS_PHILIP    0x40000000
#define USB_OTG_TRANS_UTMI      0x00000000
#define USB_OTG_FS_ONLY         0x01000000
#define USB_OTG_TRANS_WIDTH     0x10000000

#define USB_SERIAL_CONFIG_MASK  0x60000000
#define DIFF_UNIDIR             0x00000000
#define DIFF_BIDIR              0x20000000
#define SE_UNIDIR               0x40000000
#define SE_BIDIR                0x60000000

/* Enum for type of interface supported */
enum {
    UTMI_INF,
    ULPI_INF,
    SERIAL_INF_ATLAS,  
    SERIAL_INF_ISP1301,
};
 
/* extern declaration */
extern void usb_init(void);
extern void usb_otg_interface_init(void);

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* BL_TRANSRECEIVER_H */

