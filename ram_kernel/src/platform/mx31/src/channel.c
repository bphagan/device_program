/*****************************************************************************
** channel.c
**
** Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
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
#include "protocol.h"
#include "debug.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/* function declare */
/* USB functions */
static void setup_dTD(u32 base, u32 next_linkptr, u8 Terminate, u16 total_bytes,
			u8 ioc, u8 Status, u32 BufferPtr0, u16 CurrentOffset, u32 BufferPtr1, 
			u32 BufferPtr2, u32 BufferPtr3, u32 BufferPtr4);
/* EP1out and EP2in rx/tx channel setup function */
static void setup_EP1out_rx(u32 buf_addr, u32 offset, u32 count);
static void setup_EP2in_tx(u32 buf_addr, u32 count);
/* UART get/put functions */
static u8 uart_getchar(void);
static void uart_putchar(u8 c);
/* USB channel switch, work around for ROM code bug */
static int usb_channel_switch(void);

extern void usb_init_bs(void);

/*****************************************************************************
* <Global Variables>
*****************************************************************************/
static u8 channel;
extern usb_sw_fn_t usbchan_switch;

/*****************************************************************************
* <Local Variables>
*****************************************************************************/
/*!
 * delay
 */
static void delay(void)
{
    int i;
    for (i=0;i<300;i++) {
    } 
}

static void usb_delay(void)
{
    int i;
    for (i=0; i<1000000; i++) {
    } 
}
/*==================================================================================================

FUNCTION: setup_dTD

DESCRIPTION: 
   	This function is used to setup the dTD

ARGUMENTS PASSED:
	u32 base_dTD - Base Address of the dTD
	u32 NextLinkPtr - Next Link Pointer, 
	u8 	terminate - Terminate - TERMINATE; not Terminate - NOT_TERMINATE
	u16 total_bytes - Total Bytes to be transfered in this dQH
	u8 	ioc - interrupt on complete, set - IOC_SET, not set - IOC_NOTSET
	u8 	Status - Status 
	u32 BuffPtr0 - Buffer Pointer page 0
	u16 CurrentOffset - current offset
	u32 BuffPtr1 - Buffer Pointer page 1
	u32 BuffPtr2 - Buffer Pointer page 1
	u32 BuffPtr3 - Buffer Pointer page 1
	u32 BuffPtr4 - Buffer Pointer page 1
	  
RETURN VALUE:
	None
		
IMPORTANT NOTES:
	None
		
==================================================================================================*/

void setup_dTD(u32 base, u32 next_linkptr, u8 terminate, u16 total_bytes, 
				u8 ioc, u8 status,
				u32 bufptr0, u16 offset, u32 bufptr1, 
				u32 bufptr2, u32 bufptr3, u32 bufptr4)
{
	volatile struct s_dTD_SETUP* dTD_word = (volatile struct s_dTD_SETUP*)base;
	

	// Bit31:5 Next Link Pointer ; Bit0 terminate
	dTD_word->dTD_WORD0 = (next_linkptr & 0xFFFFFFE0) | terminate;
	
	// Bit30:16 total_bytes, Bit15 ioc, Bit7:0 status
	dTD_word->dTD_WORD1 = (((u32)total_bytes & 0x7FFF) << 16)| ((u32)ioc <<15) | (status);
	
	// Bit31:12 Buffer Pointer Page 0 ; Bit11:0 Current Offset
	dTD_word->dTD_WORD2 = (bufptr0 & 0xFFFFF000) | (offset & 0xFFF);
	
	// Bit31:12 Buffer Pointer Page 1 ; Bit10:0 Frame Number
	dTD_word->dTD_WORD3 = (bufptr1 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 2 ;
	dTD_word->dTD_WORD4 = (bufptr2 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 3 ; 
	dTD_word->dTD_WORD5 = (bufptr3 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 4 ; 
	dTD_word->dTD_WORD6 = (bufptr4 & 0xFFFFF000);

}

/*==================================================================================================

FUNCTION: setup_EP1out

DESCRIPTION: 
   	This function is used to prepare the Setup command from PC and prime the endpoint

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	None
==================================================================================================*/
void setup_EP1out(u32 read_byte)
{
	// setup dTD
	// dTD for status of GET_DEVICE_DESCRIPTOR
	setup_dTD(dTD0_EP1OUT, dTD1_EP1OUT, TERMINATE, read_byte, IOC_SET, ACTIVE, BUFPTR_P0_EP1OUT,(BUFPTR_P0_EP1OUT & 0xFFF),0,0,0,0);
	// 1. write dQH next ptr and dQH terminate bit to 0 
	*(u32 *)(dQH2_EP1OUT+0x8)= (dTD0_EP1OUT);
	
	// 2. clear active & halt bit in dQH
	*(u32 *)(dQH2_EP1OUT+0xC) &= ~0xFF;
	
	// 3. prime endpoint by writing '1' in ENDPTPRIME
	*(u32 *)USB_OTG_ENDPTPRIME |= EP1OUT_PRIME;
	

}

/*!
 * Function to setup the receive from host channel
 * 
 * @buf_addr  receive data buffer
 * @count  receive data size
 *
 * @return
 */
void setup_EP1out_rx(u32 buf_addr, u32 offset, u32 count)
{
	u32 bufpage0, bufpage1, bufpage2,
	    bufpage3, bufpage4;

	/* fill the buffer page address */
	bufpage0 = buf_addr;
	bufpage1 = buf_addr + 0x1000;
	bufpage2 = buf_addr + 0x2000;
	bufpage3 = buf_addr + 0x3000;
	bufpage4 = buf_addr + 0x4000;
	
	/* Clear the EP1 OUT complete status if set */
	if (*(u32 *)USB_OTG_ENDPTCOMPLETE & BIT1)
		*(u32 *)USB_OTG_ENDPTCOMPLETE = BIT1;
	
	/* setup dTD for status of GET_DEVICE_DESCRIPTOR */
	setup_dTD(dTD0_EP1OUT, dTD1_EP1OUT, TERMINATE, count, IOC_SET, ACTIVE,
			bufpage0, offset, bufpage1, bufpage2,
			bufpage3, bufpage4);

	/* write dQH next ptr and dQH terminate bit to 0 */
	*(u32 *)(dQH2_EP1OUT + 0x8)= (dTD0_EP1OUT);
	
	/* clear active & halt bit in dQH */
	*(u32 *)(dQH2_EP1OUT + 0xC) &= ~0xFF;
	
	/* prime endpoint by writing '1' in ENDPTPRIME */
	*(u32 *)USB_OTG_ENDPTPRIME |= EP1OUT_PRIME;
	
	/* Wait for the Complete Status */
	while (!(*(volatile u32 *)USB_OTG_ENDPTCOMPLETE & BIT1));

	/* clear the complete status */
	*(volatile u32 *)USB_OTG_ENDPTCOMPLETE = BIT1;

	return;
}

/*!
 * Function to setup the transmit to host channel
 * 
 * @buf_addr  transmit data buffer
 * @count  transmit data size
 *
 * @return
 */
void setup_EP2in_tx(u32 buf_addr, u32 count)
{
	u32 bufpage0, bufpage1, bufpage2,
	    bufpage3, bufpage4;

	/* fill the buffer page address */
	bufpage0 = buf_addr;
	bufpage1 = buf_addr + 0x1000;
	bufpage2 = buf_addr + 0x2000;
	bufpage3 = buf_addr + 0x3000;
	bufpage4 = buf_addr + 0x4000;

	/* setup the dTD with buffer page */
	setup_dTD(dTD0_EP2IN, dTD1_EP2IN, TERMINATE, count, IOC_SET, ACTIVE,
			bufpage0, bufpage0 & 0xFFF, bufpage1, 
			bufpage2, bufpage3, bufpage4);
	
	/* write dQH next ptr and dQH terminate bit to 0 */
	*(u32 *)(dQH5_EP2IN + 0x8)= dTD0_EP2IN;
	
	/* clear active & halt bit in dQH */
	*(u32 *)(dQH5_EP2IN + 0xC) &= ~0xFF;
	
	/* prime endpoint by writing '1' in ENDPTPRIME */
	*(u32 *)USB_OTG_ENDPTPRIME = EP2IN_PRIME;
	
	/* wait for complete set and clear */
	while (!(*(volatile u32 *)USB_OTG_ENDPTCOMPLETE & EP2IN_COMPLETE));
	
	*(u32 *)USB_OTG_ENDPTCOMPLETE = EP2IN_COMPLETE;

	return;
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

#ifdef UNIT_TEST
/*!
 * Function to initial the UART1
 */
static void uart_init(void)
{
	/*!
	 * configure GPIO for UART1
	 */
	/* Configure TXD1 as functional output, RX1 as functional input	*/
	*(volatile u32 *)SW_MUX_CTL_CSPI2_SCLK_CSPI2_SPI_RDY_RXD1_TXD1 &= 0xffff0000;
	*(volatile u32 *)SW_MUX_CTL_CSPI2_SCLK_CSPI2_SPI_RDY_RXD1_TXD1 |= 0x00001210;
	/* Configure CTS1 as functional output, RTS1 as functional input */
	*(volatile u32 *)SW_MUX_CTL_RTS1_CTS1_DTR_DCE1_DSR_DCE1 &= 0x0000ffff;
	*(volatile u32 *)SW_MUX_CTL_RTS1_CTS1_DTR_DCE1_DSR_DCE1 |= 0x12100000;

	/*!
	 * enable the UART1 clock 
	 */
	/* re-write reset values to CCM_MPCTL */
	*(volatile u32 *)CCM_PDR0 =  0xFF870B48;
	/* Verify that UART1 clock is enabled: CGR[23:22]=11 */
	*(volatile u32 *)CCM_CGR0 |= 0x00C00000;
	/* Finally program pll and wait for lock... */
	if (*(volatile u32 *)CCM_MPCTL != 0x04001800) {
		*(volatile u32 *)CCM_MPCTL= 0x04001800 ;
	}

	/*!
	 * configure the UART1 HW
	 */
	/* set to odd parity, 1 stop bit, 8bit tx/rx length */
	*(volatile u32 *)UART1_UCR2_1 = 0x60A6;
	/* Control register3:RXDMUXSEL = 1 */
	*(volatile u32 *)UART1_UCR3_1 = 0x0004;
	/* Control register4: 32 characters in the RxFIFO */
	*(volatile u32 *)UART1_UCR4_1 = 0x8000;
	/* Control register1: Enable UART */
	*(volatile u32 *)UART1_UCR1_1 = 0x0001;
	/**
	 * Set up reference freq divide for UART module
	 * ipg_perclk=13MHz
	 * ref_clk=ipg_perclk/RFDIV; ref_clk=13MHz --> RFDIV=1
	 */
	*(volatile u32 *)UART1_UFCR_1 = 0x0A81;
	
	/* Make sure that no test mode is active */
	*(volatile u32 *)UART1_UTS_1 = 0x0000;

	/**
	 * Set Boud Rate to 115200 KBPS
	 * (Boud Rate)=RefFreq/(16x(UBMR+1)/(UBIR+1))
	 * (UBMR+1)=16; (UBIR+1)=426 
	 * UBIR register MUST be updated before the UBMR register
	 */
	*(volatile u32 *)UART1_UBIR_1 = 0x0F;
	
	/* rel 2.9 clock mode detection	*/
	if (((*(volatile u32 *)CCM_CCMR ) & CLOCK_SEL_MASK )== CKIL_CLOCK_SEL) {
		/**
		* RefFreq= ( 32 * 1024 *6) / 4 = 48*1024 Khz
		* (UBMR+1)=16; (UBIR+1)=426
		* So Baudrate =  (48 * 1024 )/( 16 * 426 / 16 ) =115380 ; 
		*/
		*(volatile u32 *)UART1_UBMR_1 = 0x1A9;
	} else {
		/**
		 * RefFreq= ( 26 *6) / 4 = 39 Mhz 
		 * (UBMR+1)=16; (UBIR+1)= 339 ;
		 * So Baudrate =  (39 )/( 16 * 339 / 16 ) =115044 ; 
		 */
		*(volatile u32 *)UART1_UBMR_1 = 0x152;
	}

}
#endif

/*!
 * Function to initial channel of USB or UART
 *
 * @ch channel type
 */
void atk_channel_init(u8 ch)
{
	channel = ch;
	dbg("Initial the channel finish\n");

	if (channel == CHAN_USB) {
		*(volatile u32 *)USB_OTG_PERIODICLISTBASE =0;
		*(volatile u32 *)USB_OTG_USBCMD &= ~BIT0;
		*(volatile u32 *)USB_OTG_USBCMD |= BIT1;
		while (*(volatile u32 *)USB_OTG_USBCMD & BIT1);
		usb_delay();
		usb_init_bs();
	}
      
	/* hook for usb switch function */
	usbchan_switch = usb_channel_switch;
#ifdef UNIT_TEST
	/* initial UART to test the basic function of RAM Kernel */
	//uart_init();
#endif
	return;
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
	
	if (channel == CHAN_USB) {

		while (count) {

			/* fix the size length to 16K due to HW limit */
			if (count > MAX_USB_DATA_LEN) {
				len = MAX_USB_DATA_LEN; 
			} else {
				len = count;
			}
			/* setup EP out rx channel */
			setup_EP1out_rx((u32)&buf[i], (u32)(&buf[i]) & 0xFFF, len);

			count -= len;
			i += len;
		}

	} else {
		for (i=0; i < count; i++) {
			/* check the receive status */
			while (!(*(volatile u32 *)UART1_USR2_1 & 0x1));
			buf[i] = uart_getchar(); 
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

	if (channel == CHAN_USB) {

		while (count) {

			size = count > MAX_USB_DATA_LEN ? MAX_USB_DATA_LEN : count;
			/* FIXME: if the buffer is messed by the USB, use static buffer arrary */
			/* setup EP2 Tx data channel */
			setup_EP2in_tx((u32)buf, size);

			count -= size;
			buf += size; /* update buffer addr */
		}
		
	} else {

		for (i = 0; i < count; i++) {
			delay();
			/* put data to UART transmit fifo */
			uart_putchar(buf[i]);
			/* wait for TF empty */
			while (!(*(volatile u32 *)UART1_USR2_1 & 0x4000));
		}
	}

	return 0;
}

/*!
 * Function to switch current channel to USB
 * Workaround for ROM Code usb initial bug
 */
static int usb_channel_switch(void)
{
	if (channel == CHAN_USB) {
		/* fatal error, we can not do it */
		dbg("We are already use USB channel\n");
		return -1;
	}

	usb_init_bs();

	channel = CHAN_USB;

	return 0;
}
