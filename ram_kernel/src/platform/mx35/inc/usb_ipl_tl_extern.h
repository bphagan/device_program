/*==================================================================================================

====================================================================================================

    Module Name:  usb_ipl_tl_extern.h

    General Description: This file contains the extern variable of hw interface layer which are 
    exposed to transaction layer.
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

#ifndef USB_IPL_TL_EXTERN_H
#define USB_IPL_TL_EXTERN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "su_basictypes.h"
#include "usb_common.h"
	
/* Maximum packet size defination */
#define MPS_8	8
#define MPS_64	64

/* enum for endpoint numbers */
enum
{
    EP0,
    EP1,
    EP2,
    EP3,
    EP4,
    EP5
};

enum 
{
    OUT,
    IN
};   
/* enum for data transfer type on endpoints */
enum
{
    CONTROL,
    ISOCHRONOUS,
    BULK,
    INTERRUPT
};

/* Data Structure used for configuring the Endpoints. */
typedef struct {
    U8  end_pt_no;	/* Endpoint number */
    U8  direction;	/* Direction of endpoint */
    U8  transfer_type; 	/* type of transfer supporting on the endpoint */
    U16  max_pkt_size;	/* maximum packet size in bytes */
}usb_end_pt_info_t;

/* extern declaration of the functions */
extern BOOL ipl_check_bus_reset(void);
extern BOOL ipl_check_setup_token(void);
extern void ipl_handle_bus_reset(void);
extern void ipl_set_device_address(UINT16 address);
extern void ipl_send_stall_handshake(UINT8 endpt , UINT8 direction);
extern void ipl_set_configuration(usb_end_pt_info_t* config_data);
extern usb_status_t ipl_send_data(UINT8 endptno , usb_buffer_descriptor_t* bd,BOOL zlt);
extern usb_status_t ipl_receive_setup_data(usb_buffer_descriptor_t* bd);
extern usb_status_t ipl_receive_data(UINT8 endptno, usb_buffer_descriptor_t* bd);
extern UINT32 ipl_get_ep0_rxtx_buffer(void);
extern BOOL ipl_is_interface_high_speed(void);

#ifdef __cplusplus
} /* extern C++ */
#endif

#endif  /* USB_IPL_TL_EXTERN_H */

