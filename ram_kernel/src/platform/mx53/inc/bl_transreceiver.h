/*==================================================================================================

====================================================================================================

    Module Name:  bl_transreceiver.h

    General Description: This file contains the defines of transreceiver .
====================================================================================================
    Copyright (C) 2006,2007.2008 Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Prabhat Singh                01/02/2008     engcm03206   USB ULPI phy miss trigerring issue  
Prabhat Singh              29/01/2008       Engcm03148          USB lpb flow modification
 Siva Pothireddy               01-Dec-2007   engcm02041   Added support for serial. 
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

#define SERIAL_6WIRE

/* Buffer memory allocated for USB Core for data transfer */
#define BUFFER_SIZE             0x800

#ifdef SERIAL_3WIRE

#define TRANS_USB0_REG_VAL      0x000A1060
#define TRANS_USB0_REG_MASK     0xFFFFFFFF

#endif

#ifdef SERIAL_6WIRE

#define TRANS_USB0_REG_VAL      0x000E1060
#define TRANS_USB0_REG_MASK     0xFFFFFFFF

#endif
#define USB_OTG_TRANS_MASK      0xC0000000
#define USB_OTG_TRANS_SERIAL    0xC0000000
#define USB_OTG_TRANS_ULPI      0x80000000
#define USB_OTG_TRANS_RESRVD      0x40000000
#define USB_OTG_TRANS_UTMI      0x00000000
#define USB_OTG_FS_ONLY         0x01000000
#define USB_OTG_TRANS_WIDTH     0x10000000

#define USB_SERIAL_CONFIG_MASK  0x60000000
#define DIFF_UNIDIR             0x00000000
#define DIFF_BIDIR              0x20000000
#define SE_UNIDIR               0x40000000
#define SE_BIDIR                0x60000000

/*USB_CTRL_1 Register masks and values*/
#define USB_OTG_EXT_CLK_MASK    0x01000000
#define USB_OTG_EXT_CLK_ENB     0x01000000
#define USB_OTG_EXT_CLK_DIS     0x00000000


/* Enum for type of interface supported */
enum {
    UTMI_INF,
    ULPI_INF,
    SERIAL_INF,
};

/* extern declaration */
extern void usb_init(void);
extern void usb_otg_interface_init(void);

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* BL_TRANSRECEIVER_H */

