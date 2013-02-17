/*==================================================================================================

====================================================================================================

    Module Name:  bl_transreceiver.h

    General Description: This file contains the defines of transreceiver .
====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Siva Pothireddy              07-Jul-2008    ENGcm06427   Warnings Fixed.
Mahima Verma                 06/11/2007     TLSbo93857   Ported to Marley.
Suresh Kumar                 10/18/2006     TLSbo80774   Porting to Zappa.
Bharat Bhushan               20/07/2006     TLSbo73521   SPI interface deleted and ULPI interface added.
Bharat Bhushan               28/06/2006     TLSbo72164   Defines for Moana 6-Wrie Serial Interface Support.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#ifndef BL_TRANSRECEIVER_H
#define BL_TRANSRECEIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"

/* Buffer memory allocated for USB Core for data transfer */
#define BUFFER_SIZE             0x800

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


#define ULPI_OEXTEN             0x00000001

/* Enum for type of interface supported */
enum {
    ULPI_INF,
    SERIAL_INF,
};

/* extern declaration */
extern void usb_otg_interface_init(void);
extern void usb_init(void);

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* BL_TRANSRECEIVER_H */

