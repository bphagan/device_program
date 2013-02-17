/*==================================================================================================

====================================================================================================

    Module Name:  usb_transaction_layer.h

    General Description: This is the Header File for TL.
====================================================================================================
                               Freescale Confidential Proprietary
                       Copyright (c) 2006-2008 Freescale Inc. All Rights Reserved


Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Radhish                      05/05/2008     ENGcm05524   Remove the Enumeration Flow in LPB case
Radhish                      29/02/2008     ENGcm03622   LPB Support for Senna 
Suresh Kumar                15/Oct/2006     TLSbo80774   Initial Version for Zappa
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/


#ifndef USB_TRANSACTION_LAYER_H
#define USB_TRANSACTION_LAYER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"
#include "usb_tl_al_extern.h"

#define SETUP_DATA_LENGTH	0x8
#define ENDPT_NUMBER_MASK 	0x0F
#define ENDPT_DIR_MASK 		0x80
#define ENDPT_DIR_SHIFT 	0x7 
#define ENDPT_TRNS_TYPE_MASK 	0x03

#define USB_MAX_DEVICE_ADDR 		127
#define USB_DEV_VALUE_OF_UNCONFIG       0x0

#define USB_DEV_CONFIG_DESC_CONFIG_VALUE	0x01
/* Default device address */
#define USB_DEFAULT_ADDR  			0x00

/* DESCRIPTOR Type */
#define DEVICE_DESC	 	0x1
#define CONF_DESC	 	0x2
#define STRING_DESC	 	0x3
#define INTERFACE_DESC   	0X4
#define ENDPOINT_DESC    	0x5
#define DEVICE_QUALIFIER 	0x6
#define OTHER_SPEED_CONF_DESC	0x7

/* String SUB DESCRIPTOR type */
#define STR_DES0		0x0
#define STR_DES1		0x1
#define STR_DES2		0x2
#define STR_DES3		0x3
#define STR_DES4		0x4
#define STR_DES5		0x5

/* Descriptor Index */	
#define FILL_DEVICE_DESC	0x1
#define FILL_DEVICE_QF_DESC	0x2
#define FILL_CONF_DESC		0x3
#define FILL_OT_CONF_DESC	0x4
#define FILL_STR_DES0		0x5
#define FILL_STR_DES1		0x6
#define FILL_STR_DES2		0x7
#define FILL_STR_DES3		0x8

#define LEN_OF_CONFIG_VALUE	0x1
	
#define	NUM_OF_ENDPT_OFFSET 	0x4
#define	CONFIG_NUMBER_OFFSET 	0x5
#define STRING_DESC_LEN_OFFSET	0x0
#define DEVICE_DESC_LEN_OFFSET	0x0
#define CONF_DESC_LEN_OFFSET	0x0
#define INF_DESC_LEN_OFFSET	0x0
#define EP_DESC_LEN_OFFSET	0x0

/* Supported TYPE values. */
#define HAB_ENGINEERING               ((UINT8)0x1)
#define HAB_PRODUCT                   ((UINT8)0x2)
#define HAB_SEC_DISABLED              ((UINT8)0x8)

/* Constants defined to represent the elements within the setup packet. */
enum 
{
    BMREQUESTTYPE,
    BREQUEST,
    WVALUE_LOWBYTE,
    WVALUE_HIGHBYTE,
    WINDEX_LOWBYTE,
    WINDEX_HIGHBYTE,
    WLENGTH_LOWBYTE,
    WLENGTH_HIGHBYTE
};

/* Enum constants for function to identify the USB Standard Request defined 
 * in USB Specification. 
 */
enum 
{
   USB_GET_STATUS,
   USB_CLEAR_FEATURE,
   USB_RESERVED_REQ_ONE,
   USB_SET_FEATURE,
   USB_RESERVED_REQ_TWO,
   USB_SET_ADDRESS,
   USB_GET_DESCRIPTOR,
   USB_SET_DESCRIPTOR,
   USB_GET_CONFIGURATION,
   USB_SET_CONFIGURATION,
   USB_GET_INTERFACE,
   USB_SET_INTERFACE,
   USB_SYNCH_FRAME
};


#ifdef __cplusplus
} /* extern C++ */
#endif

#endif /* USB_TRANSACTION_LAYER_H */
