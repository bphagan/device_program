/*****************************************************************************
** channel.c
**
** Copyright 2008 - 2009  Freescale Semiconductor, Inc. All Rights Reserved.
**
** This file contains copyrighted material. Use of this file is
** restricted by the provisions of a Freescale Software License
** Agreement, which has either been electronically accepted by
** you or has been expressly executed between the parties.
**
** Description: Explanation for the usage of this file.
**
** Revision History:
** -----------------
*****************************************************************************/

/*!
 * @file channel.c
 *
 * @brief the RAM Kernel channel source file
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "channel.h"
#include "platform.h"
#include "protocol.h"
#include "debug.h"
#include "usb_hwinterface_layer.h"
#include "usb_tl_pl_extern.h"
#include "serial_downloader.h"
#include "bl_transreceiver.h"
#include "usb_common.h"
#include "usb_tl_al_extern.h"
/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/* function declare */

/* UART get/put functions */
static u8 uart_getchar(void);
static void uart_putchar(u8 c);


/*****************************************************************************
* <Global Variables>
*****************************************************************************/
static u8 channel;

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

#define WD_TIMEOUT 0x20
static void inline watchdog_service(void)
{
	if (*(volatile u16 *)0x53FDC000 & 0x04) {
		*(volatile u16 *)0x53FDC002 = 0x5555;
		*(volatile u16 *)0x53FDC002 = 0xAAAA;
	}
}

/*!
 * delay
 */
static void delay(void)
{
    int i;
    for (i=0;i<300;i++) {
    } 
}

/*!
 * Function to get a character from UART FIFO
 *
 * @return character value
 */
static u8 uart_getchar(void)
{
	return (*(volatile u32 *)UART1_URXD_1 & 0xFF);
}

/*!
 * Function to put a character into UART FIFO
 */
static void uart_putchar(u8 c)
{
	*(volatile u32 *)UART1_UTXD_1 = c;
}

/*!
 * Function to initial channel of USB or UART
 *
 * @ch channel type
 */
void atk_channel_init(u8 ch)
{
	/* service watchdog */
	watchdog_service();
	
	sys_init();

	channel = ch;
	if (channel == CHAN_USB) {
		/*Reset USB*/
		*(VP_U32)USB_OTG_DEVICEADDR =0;
		*(VP_U32)USB_OTG_USBCMD &= ~BIT0;
		*(VP_U32)USB_OTG_USBCMD |= BIT1;
		while( *(VP_U32)USB_OTG_USBCMD & BIT1);
		/*Initialize USB agagin*/
		usb_init();

		while (1) {
			/* Check for bus activity on USB */
			if(tl_check_for_bus_activity() == TRUE) {
            			serial_downloader_usb();
				break;
			}
		watchdog_service();
		}
	}
}

/*!
 * Function to receive data from host through channel
 *
 * @buf  buffer to fill in
 * @count  read data size
 *
 * @return 0
 */
u32 atk_channel_recv(u8 *buf, u32 count)
{	
	u32 i = 0, len;
	u32 to = WD_TIMEOUT;
	usb_buffer_descriptor_t  buf_desc;
	usb_status_t status = USB_FAILURE;
	
	if (channel == CHAN_USB) {

		watchdog_service();
		while (count) {
		
			/* fix the size length to 16K due to HW limit */
			if (count > 0x10000) {
				len = 0x10000; 
			} else {
				len = count;
			}
			/* setup EP out rx channel */
			buf_desc.buffer = buf;
			buf_desc.size = len;
			buf_desc.bytes_transfered = 0;
			status = (usb_status_t )tl_receive_data(&buf_desc);
			
			count -=  buf_desc.bytes_transfered ;
			buf +=  buf_desc.bytes_transfered ;
			
			if (--to <= 0) {
				watchdog_service();
				to = WD_TIMEOUT;
			}
		}

	} else {
		watchdog_service();
		for (i=0; i < count; i++) {

			/* check the receive status */
			while (!(*(volatile u32 *)UART1_USR2_1 & 0x1)) {
				if (--to <= 0) {
					watchdog_service();
					to = WD_TIMEOUT;
				}
			}
			buf[i] = uart_getchar(); 
			if (--to <= 0) {
				watchdog_service();
				to = WD_TIMEOUT;
			}
		}
	}
	
	return 0;
}

/*!
 * Function to send data to host through channel
 *
 * @buf  buf to send
 * @count  send data size
 *
 * @return 0
 */
u32 atk_channel_send(const u8 *buf, u32 count)
{
	u32 size;
	u32 i;
	u32 to = WD_TIMEOUT;
	usb_buffer_descriptor_t  buf_desc;
	usb_status_t status = USB_FAILURE;

	if (channel == CHAN_USB) {
		
		watchdog_service();
		while (count) {
                     
			size = count > BULK_BUFFER_SIZE ? BULK_BUFFER_SIZE : count;
			/* FIXME: if the buffer is messed by the USB, use static buffer arrary */
			buf_desc.buffer = (u8 *)buf;
			buf_desc.size = size;
			buf_desc.bytes_transfered = 0;
			status = (usb_status_t )tl_send_data(&buf_desc);

			count -= size;
			buf += size; /* update buffer addr */
			if (--to <= 0) {
				watchdog_service();
				to = WD_TIMEOUT;
			}
		}
		
	} else {

		watchdog_service();
		for (i = 0; i < count; i++) {
			delay();
			/* put data to UART transmit fifo */
			uart_putchar(buf[i]);
			/* wait for TF empty */
			while (!(*(volatile u32 *)UART1_USR2_1 & 0x4000)) {
				if (--to <= 0) {
					watchdog_service();
					to = WD_TIMEOUT;
				}
			}
			if (--to <= 0) {
				watchdog_service();
				to = WD_TIMEOUT;
			}
		}
	}

	return 0;
}
