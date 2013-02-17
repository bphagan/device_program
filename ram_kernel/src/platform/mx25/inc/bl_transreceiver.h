/*==================================================================================================

====================================================================================================

    Module Name:  bl_transreceiver.h

    General Description: This file contains the defines of transreceiver .
====================================================================================================
    Copyright (C) 2006,2007,2008 Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Radhish                      05/05/2008     ENGcm05522   Set the OEXTEN bit before enabling the ulpi mode
Radhish                      19/03/2008     ENGcm04722   OTG PWR pin Fix
Prabhat Singh                  08/08/2007     TLSbo94951    Added serial phy Atlas/philips support 
Sai Kiran Bollu                 07/25/2007     TLSbo94949   Change to USB 6Wire mode.  
Bharat Bhushan               09/25/2006     TLSbo78968   New Serial Boot strategy implementation.  
Bharat Bhushan               06/30/2006     TLSbo70190   USB 3 Wire Serial Mode Change.  
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

#define USB_CTRL_PP_SET         0x00000800
#define ULPI_OEXTEN             0x02000000

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

