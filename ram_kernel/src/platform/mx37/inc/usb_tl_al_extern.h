/*==================================================================================================

====================================================================================================

    Module Name:  usb_tl_al_extern.h

    General Description: This file contains the extern variable of transaction layer which are 
    exposed to Application Layer.
====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.

Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Mahima Verma                 20/Aug/2007    TLSbo95872   Change in descriptor value according to USB2.0.
Mahima Verma                 19/Jul/2007    TLSbo94597   Changes in USB to support simulator testing.
Mahima Verma                 06/11/2007     TLSbo93857   Ported to Marley.
Suresh Kumar                 10/18/2006     TLSbo80774   Porting to Zappa.
Bharat Bhushan               08/24/2006     TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               08/04/2006     TLSbo74877   Maximum Packet Size changed from 0x08 to 0x40 for EP0
Bharat Bhushan               28/06/2006     TLSbo72164   Defines of USB VERSION Changed from 2.0 to 1.10 
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#ifndef USB_TL_AL_EXTERN_H
#define USB_TL_AL_EXTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"
#include "usb_common.h"

#define VID	0x15A2
#define	PID	0x002C

/* Constants defined to represent device descriptor elements. */
#define USB_DEV_DESC_LEN                                 0x12
#define USB_DEV_DESC_TYPE                                0x01
#define USB_DEV_DESC_SPEC_LB                             0x00
#define USB_DEV_DESC_SPEC_HB                             0x02
#define USB_DEV_DESC_DEV_CLASS                           0x00
#define USB_DEV_DESC_DEV_SUBCLASS                        0x00
#define USB_DEV_DESC_DEV_PROTOCOL                        0x00
#define USB_DEV_DESC_EP0_MAXPACKETSIZE                   0x40
#define USB_DEV_DESC_VENDORID_LB                         (VID & 0x00FF) 
#define USB_DEV_DESC_VENDORID_HB                         ((VID & 0xFF00) >> 0x8) 
#define USB_DEV_DESC_PRODUCTID_LB                        (PID & 0x00FF)
#define USB_DEV_DESC_PRODUCTID_HB                        ((PID & 0xFF00) >> 0x8)
#define USB_DEV_DESC_DEV_RELEASE_NUM_LB                  0x01
#define USB_DEV_DESC_DEV_RELEASE_NUM_HB                  0x00
#define USB_DEV_DESC_DEV_STRING_IND_MANUFACTURE          0x01
#define USB_DEV_DESC_DEV_STRING_IND_PRODUCT              0x02
#define USB_DEV_DESC_DEV_STRING_IND_SERIAL_NUM           0x00
#define USB_DEV_DESC_DEV_NUM_CONFIGURATIONS              0x01

/* Constants defined to represent device qualifier descriptor elements. */
#define	USB_DEV_QUALIFIER_DESC_LEN                       0x0A
#define	USB_DEV_QUALIFIER_DESC_TYPE                      0x06
#define USB_DEV_DESC_NUM_OT_SPEED_CONF                   0x01
#define USB_DEV_DESC_RESERVED                            0x00

/* Constants defindes to represent elements of configuration descriptor. */

#define USB_DEV_CONFIG_DESC_LEN                          0x09 /* Length of configuration descriptor. */ 
#define USB_DEV_CONFIG_DESC_TYPE                         0x02 /* Descriptor type. */
#define USB_DEV_CONFIG_DESC_TTL_LEN_LB                   0x20 /* Total length of configuration information. */
#define USB_DEV_CONFIG_DESC_TTL_LEN_HB                   0x00 /* Total length of configuration information. */
#define USB_DEV_CONFIG_DESC_NUM_0F_INF                   0x01 /* Number of interfaces in this configuration. */ 
#define USB_DEV_CONFIG_DESC_CONFIG_VALUE                 0x01 /* Configuration value. */
#define USB_DEV_CONFIG_DESC_STRING_INDEX                 0x04 /* String index for this configuration. */
#define USB_DEV_CONFIG_DESC_ATTRIBUTES                   0xC0 /* Self powered and supported remote wakeup. */
#define USB_DEV_CONFIG_DESC_MAX_POWER                    0x05 /* Max power consumed by phone. */
 
#define USB_DEV_INF_DESC_LEN                             0x09 /* Interface descriptor length. */
#define USB_DEV_INF_DESC_TYPE                            0x04 /* The descriptor type, 4 interface descriptor. */
#define USB_DEV_INF_DESC_INF_INDEX                       0x00 /* Interface index. */
#define USB_DEV_INF_DESC_ALT_SETTING                     0x00 /* The alternate setting is 0. */
#define USB_DEV_INF_DESC_NUM_OF_EP                       0x02 /* Control endpoint and data endpoint 1 and 2. */
#define USB_DEV_INF_DESC_INF_CLASS                       0xFF /* Interface class: Vendor Specific. */
#define USB_DEV_INF_DESC_INF_SUBCLASS_S_BLANK            0x40 /* (Subclass) Motorola Flash Download. */
#define USB_DEV_INF_DESC_INF_SUBCLASS_NS_BLANK           0x42

#define USB_DEV_INF_DESC_INF_PROTOCOL                    0x01 /* (Interface protocol) Vendor Specific, ROM bootloader interface. */
#define USB_DEV_INF_DESC_STRING_INDEX                    0x05  /* Index of interface string descriptor. */


/* Constants defined to represent the endpoint descriptor elements. */

/* Endpoint 1 descriptor. */
#define USB_EP1_DESC_SIZE                                0x07 /* Size of descriptor in bytes. */
#define USB_EP1_DESC_TYPE                                0x05 /* Descriptor type. */
#define USB_EP1_DESC_EP_ADDR                             0x01 /* (Endpoint address) Endpoint 1, OUT. */
#define USB_EP1_DESC_ATTRIBUTES                          0x02 /* (Attributes) Bulk Endpoint. */
#define USB_EP1_DESC_MAX_PACKET_SIZE_HS_LB               0x00 /* Max Packet Size. */
#define USB_EP1_DESC_MAX_PACKET_SIZE_HS_HB               0x02 /* Max Packet Size. */
#define USB_EP1_DESC_MAX_PACKET_SIZE_FS_LB               0x40 /* Max Packet Size. */
#define USB_EP1_DESC_MAX_PACKET_SIZE_FS_HB               0x00 /* Max Packet Size. */
#define USB_EP1_DESC_INTERVAL                            0x00 /* Interval, ignored. */

/* Endpoint 2 descriptor. */
#define USB_EP2_DESC_SIZE                                0x07 /* Size of descriptor in bytes. */
#define USB_EP2_DESC_TYPE                                0x05 /* Descriptor type. */
#define USB_EP2_DESC_EP_ADDR                             0x82 /* (Endpoint address) Endpoint 2, IN. */
#define USB_EP2_DESC_ATTRIBUTES                          0x02 /* (Attributes) Bulk Endpoint. */
#define USB_EP2_DESC_MAX_PACKET_SIZE_HS_LB               0x00 /* Max Packet Size. */
#define USB_EP2_DESC_MAX_PACKET_SIZE_HS_HB               0x02 /* Max Packet Size. */
#define USB_EP2_DESC_MAX_PACKET_SIZE_FS_LB               0x40 /* Max Packet Size. */
#define USB_EP2_DESC_MAX_PACKET_SIZE_FS_HB               0x00 /* Max Packet Size. */
#define USB_EP2_DESC_INTERVAL                            0x00 /* Interval, ignored. */

/* String Descriptor 0 */
#define USB_STR0_DESC_SIZE                                0x04 /* Size of descriptor in bytes. */
#define USB_STR0_DESC_TYPE                                0x03 /* Descriptor type. */
#define USB_LANGUAGE_ID_LB				  0x09 /* Language id of english */
#define USB_LANGUAGE_ID_HB				  0x04 /* Language id of english */

/* String Descriptor 1 */
#define USB_STR1_DESC_SIZE                                0x3A /* Size of descriptor in bytes. */
#define USB_STR1_DESC_TYPE                                0x03 /* Descriptor type. */

/* String Descriptor 2 */
#define USB_STR2_DESC_SIZE_NS                             0x20 /* Size of descriptor in bytes for Non Secure Download*/
#define USB_STR2_DESC_SIZE_SE                             0x20 /* Size of descriptor in bytes for Secure Engg. download*/
#define USB_STR2_DESC_SIZE_S                              0x20 /* Size of descriptor in bytes for Secure production download*/
#define USB_STR2_DESC_TYPE                                0x03 /* Descriptor type. */

/* String Descriptor 3 */
#define USB_STR3_DESC_SIZE                                0x20 /* Size of descriptor in bytes. */
#define USB_STR3_DESC_TYPE                                0x03 /* Descriptor type. */

#define __PACKED __attribute__((packed))

/* USB Device Descriptor structure according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  type;
    U8  bcd_usb_l;
    U8  bcd_usb_h;
    U8  device_class;
    U8  device_sub_class;
    U8  device_protocol;
    U8  max_pkt_size_ep0;
    U8  vendor_id_l;
    U8  vendor_id_h;
    U8  product_id_l;
    U8  product_id_h;
    U8  bcd_device_l;
    U8  bcd_device_h;
    U8  str_manufacturer_idx;
    U8  str_product_idx;
    U8  str_serial_num_idx;
    U8  num_of_configurations;
}__PACKED usb_device_desc_t;

/* USB Interface Descriptor structure according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  interface_num;
    U8  alternate_setting;
    U8  num_of_endpts;
    U8  interface_class;
    U8  interface_sub_class;
    U8  interface_protocol;
    U8  str_interface_idx;
}__PACKED usb_interface_desc_t;

/* USB Endpoint Descriptor structure according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  endpoint_addrs;
    U8  attributes;
    U8  max_pkt_size_l;
    U8  max_pkt_size_h;
    U8  interval;
}__PACKED usb_endpoint_desc_t;

/* USB Config Descriptor structure including interface and endpoint descriptor according
 * to USB2.0 Specification */
typedef struct  {
    U8  length;
    U8  descriptor_type;
    U8  total_length_l;
    U8  total_length_h;
    U8  num_of_interfaces;
    U8  configuration_value;
    U8  configuration;
    U8  attributes;
    U8  max_power;
    usb_interface_desc_t  usb_interface_desc;
    usb_endpoint_desc_t  usb_endpoint_desc[USB_DEV_INF_DESC_NUM_OF_EP];
}__PACKED usb_config_desc_t;

/* USB Device Qualifier Descriptor structure  according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  bcd_usb_lb;
    U8  bcd_usb_hb;
    U8  device_class;
    U8  device_subclass;
    U8  device_protocol;
    U8  max_pkt_size_ep0;
    U8  num_of_other_speed_conf;
    U8  reserved;
}__PACKED usb_device_qualifier_desc_t;

/* USB string Descriptor structure 0 according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  language_id0_l;
    U8  language_id0_h;
}__PACKED usb_str0_desc_t;


/* USB string Descriptor structure 1 according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  string[56];
}__PACKED usb_str1_desc_t;

/* USB string Descriptor structure 2 according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  string[34];
}__PACKED usb_str2_desc_t;

/* USB string Descriptor structure 3 according to USB2.0 Specification */
typedef struct {
    U8  length;
    U8  descriptor_type;
    U8  string[30];
}__PACKED usb_str3_desc_t;

/* ALL USB Descriptors for both FS and HS */
typedef struct {
    usb_device_desc_t* device_desc; 
    usb_config_desc_t* config_desc; 
    usb_config_desc_t* ot_speed_config_desc; 
    usb_device_qualifier_desc_t* device_qf_desc;
    usb_str0_desc_t* str_desc0; 
    usb_str1_desc_t* str_desc1;
    usb_str2_desc_t* str_desc2; 
    usb_str3_desc_t* str_desc3;
}__PACKED usb_desc_t;



/* extern function declaration */
extern void tl_init(void);
extern void tl_configure(void);
extern usb_state_t tl_get_state(void);
extern BOOL tl_check_for_bus_activity(void);
extern void tl_handle_bus_reset(void);

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* USB_TL_AL_EXTERN_H */

