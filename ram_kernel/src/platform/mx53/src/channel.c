/*****************************************************************************
** channel.c
**
** Copyright 2008 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
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
static inline void watchdog_service(void)
{
	if (__REG16(WDOG_WCR) & 0x04) {
		__REG16(WDOG_WSR) = 0x5555;
		__REG16(WDOG_WSR) = 0xAAAA;
	}
}

static void delay(void)
{
    int i;
    for (i=0;i<300;i++) {} 
}

/*!
 * Function to set uart baudrate
 * due to the pll re-setting change
 */
void serial_setbrg(void)
{
        u32 clk = 21600000;

        __REG32(UART_PHYS + UFCR) = 0x4 << 7;
        __REG32(UART_PHYS + UBIR) = 0xf;
        __REG32(UART_PHYS + UBMR) = clk / (2 * 115200);
}
#if 0
/*!
 * Function to re-init uart
 * due to the pll re-setting
 * @return int value
 */
static int uart_init(void)
{ 
	__REG32(UART_PHYS + UCR1) = 0x0;
        __REG32(UART_PHYS + UCR2) = 0x0;

        while (!(__REG32(UART_PHYS + UCR2) & UCR2_SRST)) ;

        __REG32(UART_PHYS + UCR3) = 0x0704;
        __REG32(UART_PHYS + UCR4) = 0x8000;
        __REG32(UART_PHYS + UESC) = 0x002b;
        __REG32(UART_PHYS + UTIM) = 0x0;

        __REG32(UART_PHYS + UTS) = 0x0;

        serial_setbrg();

        __REG32(UART_PHYS + UCR2) =
            UCR2_WS | UCR2_IRTS | UCR2_RXEN | UCR2_TXEN | UCR2_SRST;

        __REG32(UART_PHYS + UCR1) = UCR1_UARTEN;

        return 0;


}
#endif
/*!
 * Function to get a character from UART FIFO
 *
 * @return character value
 */
static u8 uart_getchar(void)
{
	return __REG32(UART_PHYS + URXD) & 0xFF;
}

/*!
 * Function to put a character into UART FIFO
 */
static void uart_putchar(u8 c)
{
	__REG32(UART_PHYS + UTXD) = c;
}

/*!
 * Function to initial channel of USB or UART
 *
 * @ch channel type
 */
void atk_channel_init(u8 ch)
{
        watchdog_service();
        int i;
	
        channel = ch;
	switch (channel) {
	case CHAN_USB:
	        sys_init();
		/*Reset USB*/
		*(VP_U32)USB_OTG_DEVICEADDR = 0;
		*(VP_U32)USB_OTG_USBCMD &= ~BIT0;
		*(VP_U32)USB_OTG_USBCMD |= BIT1;
                while (*(VP_U32)USB_OTG_USBCMD & BIT1);
	        /*Initialize USB agagin*/
                usb_init();
            	watchdog_service();
                while(1) {
			/* Check for bus activity on USB */
			if(tl_check_for_bus_activity() == TRUE) {
				serial_downloader_usb();
				break;
			}
		watchdog_service();
		}
		
        	break;
	case CHAN_UART:
		/* disable watchdog */
		watchdog_service();
		break;
	default:
		break;
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
		for (i = 0; i < count; i++) {
			/* check the receive status */
			while (!(__REG32(UART_PHYS + USR2) & 0x1)) {
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
			size = count > BULK_BUFFER_SIZE ? 
				BULK_BUFFER_SIZE : count;
			buf_desc.buffer = (void *)buf;
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
			while (!(__REG32(UART_PHYS + USR2) & 0x4000)) {
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
