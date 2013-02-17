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
#include "string.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/* function declare */
/* USB functions */
static void setup_dQH(struct s_dQH* qhead);
static void setup_dTD(struct s_dTD* td);

/* EP1out and EP2in rx/tx channel setup function */
static void setup_EP1out_rx(u32 buf_addr, u32 offset, u32 count);
static void setup_EP2in_tx(u32 buf_addr, u32 count);
/* UART get/put functions */
static u8 uart_getchar(void);
static void uart_putchar(u8 c);

/*****************************************************************************
* <Global Variables>
*****************************************************************************/
static u8 channel;
cache_usb_t cache_usb = {{0},STATE_CLEAN};

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
 * This function is used to clear the dQH
 * 
 * @qhead  receive data buffer
 *
 * @return
 */

void ClearDQH(void)
{
	u8 i = 0;
	volatile u32  * EP_QUEUE_HEADPtr;
	
	EP_QUEUE_HEADPtr = (volatile u32  *)((volatile u32  *)dQHBASE);
	// Clear the dQH Memory
	for ( i = 0; i < (64*6)/4 ; i++)
	{
		*EP_QUEUE_HEADPtr = 0;
		EP_QUEUE_HEADPtr++;
	}
}


/*!
 * This function is used to setup the dQH
 * 
 * @qhead  receive data buffer
 *
 * @return
 */
	
void setup_dQH(struct s_dQH* qhead)
{
	volatile struct s_dQH_SETUP* dQH_word = (volatile struct s_dQH_SETUP*) qhead->dQHBase;


	//======
	// 0x0
	//======
	//Bit31:30 Mult; Bit29 zlt; Bit26:16 MPS; Bit15 ios
	dQH_word->dQH_WORD0 = (((u32)(qhead->ZLT) << 29)|((u32)(qhead->MPS) <<16) | ((u32)(qhead->ios) <<15));

	//======
	// 0x4
	//======
	// Current dTD Pointer => for hw use, not modified by DCD software
	dQH_word->dQH_WORD1 = 0x0;
	
	//======
	// 0x8
	//======
	// Next dTD Pointer 
	dQH_word->dQH_WORD2 = (((qhead->NextLinkPtr) & 0xFFFFFFE0) | qhead->Terminate);
	
	//======
	// 0xC
	//======
	// Bit30:16 TotalBytes; Bit15 ioc; Bit11:10 MultO; Bit7:0 Status	
	dQH_word->dQH_WORD3 = ((((u32)(qhead->TotalBytes) & 0x7FFF)  << 16) | ((u32)(qhead->ioc) <<15) | (qhead->Status));
	
	//======
	// 0x10
	//======
	// Bit31:12 Buffer Pointer (Page 0)
	dQH_word->dQH_WORD4 = ((qhead->BuffPtr0 & 0xFFFFF000) | (qhead->CurrentOffset & 0xFFF));


	//======
	// 0x14
	//======
	// Bit31:12 Buffer Pointer (Page 1)
	dQH_word->dQH_WORD5 = (qhead->BuffPtr1 & 0xFFFFF000);
	
	//======
	// 0x18
	//======
	// Bit31:12 Buffer Pointer (Page 2)
	dQH_word->dQH_WORD6 = (qhead->BuffPtr2 & 0xFFFFF000);
	
	//======
	// 0x1C
	//======
	// Bit31:12 Buffer Pointer (Page 3)
	dQH_word->dQH_WORD7 = (qhead->BuffPtr3 & 0xFFFFF000);
	
	//======
	// 0x20
	//======
	// Bit31:12 Buffer Pointer (Page 4)
	dQH_word->dQH_WORD8 = (qhead->BuffPtr4 & 0xFFFFF000);

	//======
	// 0x24
	//======
	// Reserved
	dQH_word->dQH_WORD9 = 0;
	
	//======
	// 0x28
	//======
	// Setup Buffer 0
	dQH_word->dQH_WORD10 = 0;
	
	//======
	// 0x2C
	//======
	// Setup Buffer 1
	dQH_word->dQH_WORD11 = 0;


}

/*!
 * This function is used to setup the TD
 * 
 * @td  pointer to the TD structure
 *
 * @return
 */
void setup_dTD(struct s_dTD* td)
{
	volatile struct s_dTD_SETUP* dTD_word = (volatile struct s_dTD_SETUP*) td->dTDBase;
	

	// Bit31:5 Next Link Pointer ; Bit0 Terminate
	dTD_word->dTD_WORD0 = ((td->dTDNextLinkPtr & 0xFFFFFFE0) | td->Terminate);
	
	// Bit30:16 TotalBytes, Bit15 ioc, Bit7:0 status
	dTD_word->dTD_WORD1 = ((((u32)td->TotalBytes & 0x7FFF) << 16)| ((u32)td->ioc <<15) | (td->Status));
	
	// Bit31:12 Buffer Pointer Page 0 ; Bit11:0 Current Offset
	dTD_word->dTD_WORD2 = ((td->BuffPtr0 & 0xFFFFF000) | (td->CurrentOffset & 0xFFF));
	
	// Bit31:12 Buffer Pointer Page 1 ; Bit10:0 Frame Number
	dTD_word->dTD_WORD3 = (td->BuffPtr1 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 2 ;
	dTD_word->dTD_WORD4 = (td->BuffPtr2 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 3 ; 
	dTD_word->dTD_WORD5 = (td->BuffPtr3 & 0xFFFFF000);

	// Bit31:12 Buffer Pointer Page 4 ; 
	dTD_word->dTD_WORD6 = (td->BuffPtr4 & 0xFFFFF000);

}

/*!
 * This function is used to enable out
 * 
 * @return
 */
 
void EnableEP1OUT(void)
{
	u32 TotalBytes = 0x10;
	struct s_dQH qhead;
	
	qhead.dQHBase 		= dQH2_EP1OUT;
	qhead.ZLT 			= ZLT_DISABLE;
	qhead.MPS 			= MPS_64;
	qhead.ios 			= IOS_SET;
	qhead.NextLinkPtr  	= dTD0_EP1OUT;
	qhead.Terminate 	= TERMINATE;
	qhead.TotalBytes  	= TotalBytes;
	qhead.ioc 			= IOC_SET;
	qhead.Status 		= NO_STATUS;
	qhead.BuffPtr0  	= BUFPTR_P0_EP1OUT;
	qhead.CurrentOffset = (BUFPTR_P0_EP1OUT & 0xFFF);
	qhead.BuffPtr1  	= 0;
	qhead.BuffPtr2 		= 0;
	qhead.BuffPtr3  	= 0;
	qhead.BuffPtr4 = 0;

		
	// EP1 OUT command = 16 bytes
	setup_dQH(&qhead);
	
	// Endpoint 1 : MPS = 64, OUT (Rx endpoint)
	*(u32 *)USB_OTG_ENDPTCTRL1 = 0x00080048;

	// Enable EP1 OUT
	*(u32 *)USB_OTG_ENDPTCTRL1 |= EP1OUT_ENABLE;
}

/*!
 * This function is used to set up out command
 * 
 * @return
 */
void EP1OutCommandSetup(void)
{
	u32 TotalBytes = COMMAND;
	struct s_dTD td;
// OUT
	// setup dTD
	// dTD for status of GET_DEVICE_DESCRIPTOR
	td.dTDBase          = dTD0_EP1OUT;
	td.dTDNextLinkPtr   = dTD1_EP1OUT;
	td.Terminate        = TERMINATE;
	td.TotalBytes       = TotalBytes;
	td.ioc              = IOC_SET;
	td.Status           = ACTIVE;
	td.BuffPtr0         = BUFPTR_P0_EP1OUT;
	td.CurrentOffset    = (BUFPTR_P0_EP1OUT & 0xFFF);
	td.BuffPtr1         = 0;
	td.BuffPtr2         = 0;
	td.BuffPtr3         = 0;
	td.BuffPtr4         = 0;

	setup_dTD(&td);

	// 1. write dQH next ptr and dQH terminate bit to 0 
	*(u32 *)(dQH2_EP1OUT+0x8)= (dTD0_EP1OUT);
	
	// 2. clear active & halt bit in dQH
	*(u32 *)(dQH2_EP1OUT+0xC) &= ~0xFF;
	
	// 3. prime endpoint by writing '1' in ENDPTPRIME
	*(u32 *)USB_OTG_ENDPTPRIME |= EP1OUT_PRIME;

}

/*!
 * This function is used to rx binary data for the download
 * @address
 * @offset
 * @bytecount  
 * @return
 */

void setup_EP1out_rx(u32 buf_addr, u32 offset, u32 count)
{
	struct s_dTD td;
	// setting up the dTD buffer pointer depend on the ByteCounts
	// each page is 0x1000 and the max recommanded transfer is 0x4000 (16k bytes)
	u32 BufferPtrPage0 = buf_addr;
	u32 BufferPtrPage1 = (buf_addr + 0x1000);
	u32 BufferPtrPage2 = (buf_addr + 0x2000);
	u32 BufferPtrPage3 = (buf_addr + 0x3000);
	u32 BufferPtrPage4 = (buf_addr + 0x4000);
	
	// Clear the EP1 OUT complete status if set
	if (*(u32 *)USB_OTG_ENDPTCOMPLETE & BIT1)
		*(u32 *)USB_OTG_ENDPTCOMPLETE = BIT1;
	
// OUT
	// setup dTD
	// dTD for status of GET_DEVICE_DESCRIPTOR
	td.dTDBase         = dTD0_EP1OUT;
	td.dTDNextLinkPtr  = dTD1_EP1OUT;
	td.Terminate       = TERMINATE;
	td.TotalBytes  		 = count;
	td.ioc 				     = IOC_SET;
	td.Status 			   = ACTIVE;
	td.BuffPtr0  		   = BufferPtrPage0; 
	td.CurrentOffset   = offset; 
	td.BuffPtr1  		   = BufferPtrPage1;
	td.BuffPtr2 		   = BufferPtrPage2;
	td.BuffPtr3  		   = BufferPtrPage3;
	td.BuffPtr4  		   = BufferPtrPage4;

	setup_dTD(&td);

	// 1. write dQH next ptr and dQH terminate bit to 0 
	*(u32 *)(dQH2_EP1OUT+0x8)= (dTD0_EP1OUT);
	
	// 2. clear active & halt bit in dQH
	*(u32 *)(dQH2_EP1OUT+0xC) &= ~0xFF;
	
	// 3. prime endpoint by writing '1' in ENDPTPRIME
	*(u32 *)USB_OTG_ENDPTPRIME |= EP1OUT_PRIME;
	
	// 4. Wait for the Complete Status 
	while (!(*(volatile u32  *)USB_OTG_ENDPTCOMPLETE & BIT1));
	//clear the complete status
	*(volatile u32  *)USB_OTG_ENDPTCOMPLETE = BIT1;
}

/*!
 * This function is used to enable input
 * 
 * @return
 */
 
void EnableEP2IN(void)
{
	// EP2 IN response = 4 bytes
	u32 TotalBytes = 0x4;
	struct s_dQH qhead;
	
	qhead.dQHBase 		  = dQH5_EP2IN;
	qhead.ZLT 			    = ZLT_DISABLE;
	qhead.MPS 			    = MPS_64;
	qhead.ios 			    = IOS_SET;
	qhead.NextLinkPtr   = dTD0_EP2IN;
	qhead.Terminate 	  = TERMINATE;
	qhead.TotalBytes    = TotalBytes;
	qhead.ioc 			    = IOC_SET;
	qhead.Status 		    = NO_STATUS;
	qhead.BuffPtr0  	  = BUFPTR_P0_EP2IN;
	qhead.CurrentOffset = (BUFPTR_P0_EP2IN & 0xFFF);
	qhead.BuffPtr1  	  = 0;
	qhead.BuffPtr2 		  = 0;
	qhead.BuffPtr3  	  = 0;
	qhead.BuffPtr4 		  = 0;

		
	// EP1 OUT command = 16 bytes
	setup_dQH(&qhead);

	// Endpoint 2: MPS = 64, IN (Tx endpoint)
	*(u32 *)USB_OTG_ENDPTCTRL2 = 0x00480008;

	// Enable EP2 IN
	*(u32 *)USB_OTG_ENDPTCTRL2 |= EP2IN_ENABLE;
	
	// 3. prime endpoint by writing '1' in ENDPTPRIME
	*(u32 *)USB_OTG_ENDPTPRIME |= EP2IN_PRIME;
	
}

/*!
 * This function is used to transmit the data for READ command
 * @BufPtrAddress
 * @TotalBytes  
 * @return
 */
 
void setup_EP2in_tx(u32 buf_addr, u32 count)
{
	struct s_dTD td;
	
	td.dTDBase 			    = dTD0_EP2IN;
	td.dTDNextLinkPtr  	= dTD1_EP2IN;
	td.Terminate 		    = TERMINATE;
	td.TotalBytes  	  	= count;
	td.ioc 				      = IOC_SET;
	td.Status 			    = ACTIVE;
	td.BuffPtr0  		    = buf_addr;
	td.CurrentOffset   	= buf_addr & 0xFFF; 
	td.BuffPtr1  		    = buf_addr + 0x1000;
	td.BuffPtr2 		    = buf_addr + 0x2000;
	td.BuffPtr3  		    = buf_addr + 0x3000;
	td.BuffPtr4  		    = buf_addr + 0x4000;

	setup_dTD(&td);
	
	// 1. write dQH next ptr and dQH terminate bit to 0 
	*(u32 *)(dQH5_EP2IN+0x8)= (dTD0_EP2IN);
	
	// 2. clear active & halt bit in dQH
	*(u32 *)(dQH5_EP2IN+0xC) &= ~0xFF;
	
	// 3. prime endpoint by writing '1' in ENDPTPRIME
	*(u32 *)USB_OTG_ENDPTPRIME = EP2IN_PRIME;
	
	// wait for complete set and clear
	while (!(*(volatile u32  *)USB_OTG_ENDPTCOMPLETE & EP2IN_COMPLETE));
	
	*(u32 *)USB_OTG_ENDPTCOMPLETE = EP2IN_COMPLETE;

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
#ifdef UNIT_TEST
	/* initial UART to test the basic function of RAM Kernel */
	//uart_init();
#endif

	/* FIXME, this is just a workaround for usb 
	 * use NFC internal RAM, set init state
	 */
	if (channel == CHAN_USB) 
		cache_usb.sate = STATE_EMPTY;
		
	return;
}


/* FIXME, this is just a workaround for the rom usb 
 * use NFC internal RAM
 */ 		 		 
static __inline void pop_usb_dqh(void) 
{
	if(cache_usb.sate == STATE_DIRTY) 
			memcpy((u16*)dQHBASE,&cache_usb.data[0],sizeof(cache_usb.data));

}

static __inline void push_usb_dqh(void)
{
	if(cache_usb.sate == STATE_EMPTY) {
			memcpy(&cache_usb.data[0],(u16*)dQHBASE,sizeof(cache_usb.data));
			cache_usb.sate = STATE_DIRTY;
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
	
	if (channel == CHAN_USB) {
	
		/* FIXME, this is just a workaround for usb 
		 * use NFC internal RAM, need recovery the usb information
		 * from the back up buffer.The back up buffer was filled when
		 * the first time trans data		 
		 */		 	 
		pop_usb_dqh();
		
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
		
		/* FIXME, this is just a workaround for usb 
		 * use NFC internal RAM.The back up buffer was 
		 * filled when the first time trans data		 
		 */
		 push_usb_dqh();
		
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
	
		/* FIXME, this is just a workaround for usb 
		 * use NFC internal RAM, need recovery the usb information
		 * from the back up buffer.The back up buffer was filled when
		 * the first time trans data	 
		 */		 	 
		pop_usb_dqh();

		while (count) {
			size = count > MAX_USB_DATA_LEN ? MAX_USB_DATA_LEN : count;
			/* FIXME: if the buffer is messed by the USB, use static buffer arrary */
			/* setup EP2 Tx data channel */
			setup_EP2in_tx((u32)buf, size);

			count -= size;
			buf += size; /* update buffer addr */
		}
		
		/* FIXME, this is just a workaround for usb 
		 * use NFC internal RAM.The back up buffer was 
		 * filled when the first time usb trans data		 
		 */
		 push_usb_dqh();
		 
	} else {

		for (i = 0; i < count; i++) {
			/* put data to UART transmit fifo */
			delay();
			uart_putchar(buf[i]);
			/* wait for TF empty */
			while (!(*(volatile u32 *)UART1_USR2_1 & 0x4000));
		}
	}

	return 0;
}

#ifdef _DEBUG
void atk_debug(const char *format, /* args*/ ...)
{
	u8 strData[DBG_LOG_LEN] = { 0 };
	u8 strPatten[RKL_RESPONSE_LEN] = {'d','b','g','_','l','o','g','s'};
  va_list args ;
  va_start(args, format) ;
  vsnprintf((char*)strData, 256, format, args) ;
  va_end(args) ;
  atk_channel_send(strPatten, sizeof(strPatten));
  atk_channel_send(strData, sizeof(strData));
}
#endif
