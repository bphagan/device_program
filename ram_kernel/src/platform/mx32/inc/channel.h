/*****************************************************************************
** channel.h
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
 * @file channel.h
 *
 * @brief the RAM Kernel channel defines for USB and UART.
 *
 * @ingroup RAM Kernel
 */
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/
/*!
 * USB base address for OTG, H1 and H2
 */
#define USB_MODULE_BASE_ADDR 0x43F88000 
#define USB_OTG_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x000) 
#define USB_H1_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x200) 
#define USB_H2_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x400) 
#define USB_CONTROL_REG (USB_MODULE_BASE_ADDR + 0x600) 
#define USB_OTG_MIRROR_REG (USB_MODULE_BASE_ADDR + 0x604) 
  
/*!
 * USB Host 1 register address
 */
#define USB_H1_ID (USB_H1_BASE_ADDR +0x000) //   Identification Register                
#define USB_H1_HWGENERAL (USB_H1_BASE_ADDR +0x004) //   General Hardware Parameters            
#define USB_H1_HWHOST (USB_H1_BASE_ADDR +0x008) //   Host Hardware Parameters               
#define USB_H1_HWTXBUF (USB_H1_BASE_ADDR +0x010) //   TX Buffer Hardware Parameters          
#define USB_H1_HWRXBUF (USB_H1_BASE_ADDR +0x014) //   RX Buffer Hardware Parameters          
#define USB_H1_CAPLENGTH (USB_H1_BASE_ADDR +0x100) //   Capability Register Length             
#define USB_H1_HCIVERSION (USB_H1_BASE_ADDR +0x102) //   Host Interface Version Number          
#define USB_H1_HCSPARAMS (USB_H1_BASE_ADDR +0x104) //   Host Ctrl. Structural Parameters       
#define USB_H1_HCCPARAMS (USB_H1_BASE_ADDR +0x108) //   Host Ctrl. Capability Parameters       
#define USB_H1_USBCMD (USB_H1_BASE_ADDR +0x140) //   USB Command                            
#define USB_H1_USBSTS (USB_H1_BASE_ADDR +0x144) //   USB Status                             
#define USB_H1_USBINTR (USB_H1_BASE_ADDR +0x148) //   USB Interrupt Enable                   
#define USB_H1_FRINDEX (USB_H1_BASE_ADDR +0x14C) //   USB Frame Index
#define USB_H1_PERIODICLISTBASE (USB_H1_BASE_ADDR +0x154) //   Frame List Base Address                
#define USB_H1_ASYNCLISTADDR (USB_H1_BASE_ADDR +0x158) //   Next Asynchronous List Address         
#define USB_H1_BURSTSIZE (USB_H1_BASE_ADDR +0x160) //   Programmable Burst Size                
#define USB_H1_TXFILLTUNING (USB_H1_BASE_ADDR +0x164) //   Host Transmit Pre-Buffer Packet Tuning 
#define USB_H1_CONFIGFLAG (USB_H1_BASE_ADDR +0x180) //   Configured Flag Register               
#define USB_H1_PORTSC1 (USB_H1_BASE_ADDR +0x184) //   Port Status/Control                    
#define USB_H1_USBMODE (USB_H1_BASE_ADDR +0x1A8) //   USB Device Mode                        
  
/*!
 * USB Host 2 register address
 */
#define USB_H2_ID (USB_H2_BASE_ADDR +0x000) //   Identification Register                
#define USB_H2_HWGENERAL (USB_H2_BASE_ADDR +0x004) //   General Hardware Parameters            
#define USB_H2_HWHOST (USB_H2_BASE_ADDR +0x008) //   Host Hardware Parameters               
#define USB_H2_HWTXBUF (USB_H2_BASE_ADDR +0x010) //   TX Buffer Hardware Parameters          
#define USB_H2_HWRXBUF (USB_H2_BASE_ADDR +0x014) //   RX Buffer Hardware Parameters          
#define USB_H2_CAPLENGTH (USB_H2_BASE_ADDR +0x100) //   Capability Register Length             
#define USB_H2_HCIVERSION (USB_H2_BASE_ADDR +0x102) //   Host Interface Version Number          
#define USB_H2_HCSPARAMS (USB_H2_BASE_ADDR +0x104) //   Host Ctrl. Structural Parameters       
#define USB_H2_HCCPARAMS (USB_H2_BASE_ADDR +0x108) //   Host Ctrl. Capability Parameters       
#define USB_H2_USBCMD (USB_H2_BASE_ADDR +0x140) //   USB Command                            
#define USB_H2_USBSTS (USB_H2_BASE_ADDR +0x144) //   USB Status                             
#define USB_H2_USBINTR (USB_H2_BASE_ADDR +0x148) //   USB Interrupt Enable                   
#define USB_H2_FRINDEX (USB_H2_BASE_ADDR +0x14C) //   USB Frame Index
#define USB_H2_PERIODICLISTBASE (USB_H2_BASE_ADDR +0x154) //   Frame List Base Address                
#define USB_H2_ASYNCLISTADDR (USB_H2_BASE_ADDR +0x158) //   Next Asynchronous List Address         
#define USB_H2_BURSTSIZE (USB_H2_BASE_ADDR +0x160) //   Programmable Burst Size                
#define USB_H2_TXFILLTUNING (USB_H2_BASE_ADDR +0x164) //   Host Transmit Pre-Buffer Packet Tuning 
#define USB_H2_CONFIGFLAG (USB_H2_BASE_ADDR +0x180) //   Configured Flag Register               
#define USB_H2_PORTSC1 (USB_H2_BASE_ADDR +0x184) //   Port Status/Control                    
#define USB_H2_USBMODE (USB_H2_BASE_ADDR +0x1A8) //   USB Device Mode                        
  
/*!
 * USB OTG register address
 */
#define USB_OTG_ID		(USB_OTG_BASE_ADDR + 0x000) //   Identification Register
#define USB_OTG_HWGENERAL	(USB_OTG_BASE_ADDR + 0x004) //   General Hardware Parameters
#define USB_OTG_HWHOST		(USB_OTG_BASE_ADDR + 0x008) //   Host Hardware Parameters
#define USB_OTG_HWDEVICE	(USB_OTG_BASE_ADDR + 0x00C) //   Device Hardware Parameters
#define USB_OTG_HWTXBUF		(USB_OTG_BASE_ADDR + 0x010) //   TX Buffer Hardware Parameters
#define USB_OTG_HWRXBUF		(USB_OTG_BASE_ADDR + 0x014) //   RX Buffer Hardware Parameters
#define USB_OTG_CAPLENGTH	(USB_OTG_BASE_ADDR + 0x100) //   Capability Register Length
#define USB_OTG_HCIVERSION	(USB_OTG_BASE_ADDR + 0x102) //   Host Interface Version Number
#define USB_OTG_HCSPARAMS	(USB_OTG_BASE_ADDR + 0x104) //   Host Ctrl. Structural Parameters	
#define USB_OTG_HCCPARAMS	(USB_OTG_BASE_ADDR + 0x108) //   Host Ctrl. Capability Parameters
#define USB_OTG_DCIVERSION	(USB_OTG_BASE_ADDR + 0x120) //   Dev. Interface Version Number
#define USB_OTG_DCCPARAMS	(USB_OTG_BASE_ADDR + 0x124) //   Device Ctrl. Capability Parameters
  
#define USB_OTG_USBCMD (USB_OTG_BASE_ADDR + 0x140) //   USB Command
#define USB_OTG_USBSTS (USB_OTG_BASE_ADDR + 0x144) //   USB Status
#define USB_OTG_USBINTR (USB_OTG_BASE_ADDR + 0x148) //   USB Interrupt Enable
#define USB_OTG_FRINDEX (USB_OTG_BASE_ADDR+ 0x14C) //   USB Frame Index
#define USB_OTG_PERIODICLISTBASE (USB_OTG_BASE_ADDR + 0x154) //   Frame List Base Address
#define USB_OTG_ASYNCLISTADDR (USB_OTG_BASE_ADDR + 0x158) //   Next Asynchronous List Address
#define USB_OTG_BURSTSIZE (USB_OTG_BASE_ADDR + 0x160) //   Programmable Burst Size
#define USB_OTG_TXFILLTUNING (USB_OTG_BASE_ADDR + 0x164) //   Host Transmit Pre-Buffer Packet Tuning
#define USB_OTG_ENDPTNAK (USB_OTG_BASE_ADDR + 0x178)
#define USB_OTG_CONFIGFLAG (USB_OTG_BASE_ADDR + 0x180) //   Configured Flag Register
#define USB_OTG_PORTSC1 (USB_OTG_BASE_ADDR + 0x184) //   Port Status/Control  
#define USB_OTG_OTGSC (USB_OTG_BASE_ADDR + 0x1A4) //   On-The-Go (OTG) Status and Control   
#define USB_OTG_USBMODE (USB_OTG_BASE_ADDR + 0x1A8) //   USB Device Mode
#define USB_OTG_ENDPTSETUPSTAT (USB_OTG_BASE_ADDR + 0x1AC) //   Endpoint Setup Status
#define USB_OTG_ENDPTPRIME (USB_OTG_BASE_ADDR + 0x1B0) //   Endpoint Initialization
#define USB_OTG_ENDPTFLUSH (USB_OTG_BASE_ADDR + 0x1B4) //   Endpoint De-Initialize
#define USB_OTG_ENDPTSTATUS (USB_OTG_BASE_ADDR + 0x1B8) //   Endpoint Status
#define USB_OTG_ENDPTCOMPLETE (USB_OTG_BASE_ADDR + 0x1BC) //   Endpoint Complete
#define USB_OTG_ENDPTCTRL0 (USB_OTG_BASE_ADDR + 0x1C0) //   Endpoint Control 0
#define USB_OTG_ENDPTCTRL1 (USB_OTG_BASE_ADDR + 0x1C4) //   Endpoint Control 1
#define USB_OTG_ENDPTCTRL2 (USB_OTG_BASE_ADDR + 0x1C8) //   Endpoint Control 2
#define USB_OTG_ENDPTCTRL3 (USB_OTG_BASE_ADDR + 0x1CC) //   Endpoint Control 3
#define USB_OTG_ENDPTCTRL4 (USB_OTG_BASE_ADDR + 0x1D0) //   Endpoint Control 4
#define USB_OTG_ENDPTCTRL5 (USB_OTG_BASE_ADDR + 0x1D4) //   Endpoint Control 5
#define USB_OTG_ENDPTCTRL6 (USB_OTG_BASE_ADDR + 0x1D8) //   Endpoint Control 6
#define USB_OTG_ENDPTCTRL7 (USB_OTG_BASE_ADDR + 0x1DC) //   Endpoint Control 7

/*!
 * UART1 registers address
 */
#define UART1_BASE_ADDR	0x43F90000 
#define UART1_URXD_1	(UART1_BASE_ADDR+0x00) //  32bit uart1 receiver reg
#define UART1_UTXD_1	(UART1_BASE_ADDR+0x40) //  32bit uart1 transmitter reg
#define UART1_UCR1_1	(UART1_BASE_ADDR+0x80) //  32bit uart1 control 1 reg
#define UART1_UCR2_1	(UART1_BASE_ADDR+0x84) //  32bit uart1 control 2 reg
#define UART1_UCR3_1	(UART1_BASE_ADDR+0x88) //  32bit uart1 control 3 reg
#define UART1_UCR4_1	(UART1_BASE_ADDR+0x8C) //  32bit uart1 control 4 reg
#define UART1_UFCR_1	(UART1_BASE_ADDR+0x90) //  32bit uart1 fifo control reg
#define UART1_USR1_1	(UART1_BASE_ADDR+0x94) //  32bit uart1 status 1 reg
#define UART1_USR2_1	(UART1_BASE_ADDR+0x98) //  32bit uart1 status 2 reg
#define UART1_UESC_1	(UART1_BASE_ADDR+0x9C) //  32bit uart1 escape char reg
#define UART1_UTIM_1	(UART1_BASE_ADDR+0xA0) //  32bit uart1 escape timer reg
#define UART1_UBIR_1	(UART1_BASE_ADDR+0xA4) //  32bit uart1 BRM incremental reg
#define UART1_UBMR_1	(UART1_BASE_ADDR+0xA8) //  32bit uart1 BRM modulator reg
#define UART1_UBRC_1	(UART1_BASE_ADDR+0xAC) //  32bit uart1 baud rate count reg
#define UART1_ONEMS_1	(UART1_BASE_ADDR+0xB0) //  32bit uart1 one ms reg
#define UART1_UTS_1	(UART1_BASE_ADDR+0xB4) //  32bit uart1 test reg

#ifdef UNIT_TEST
/*!
 * UART gpio pins' registers
 */
#define IOMUXC_BASE_ADDR 0x43fac000
#define SW_MUX_CTL_CSPI2_SCLK_CSPI2_SPI_RDY_RXD1_TXD1 (IOMUXC_BASE_ADDR + 0x80)
#define SW_MUX_CTL_RTS1_CTS1_DTR_DCE1_DSR_DCE1 (IOMUXC_BASE_ADDR + 0x7c)

#define CCM_BASE_ADDR 0x53F80000 
#define CCM_CCMR (CCM_BASE_ADDR+0x00) //  32bit Clock Source Control Reg
#define CCM_PDR0 (CCM_BASE_ADDR+0x04) //  32bit MCU PLL Control Reg
#define CCM_PDR1 (CCM_BASE_ADDR+0x08) //  32bit MCU PLL Control Reg
#define CCM_RCSR (CCM_BASE_ADDR+0x0C) //  32bit MCU PLL Control Reg
#define CCM_MPCTL (CCM_BASE_ADDR+0x10) //  32bit Serial Perpheral PLL Ctrl 0
#define CCM_UPCTL (CCM_BASE_ADDR+0x14) //  32bit Serial Perpheral PLL Ctrl 1
#define CCM_SPCTL (CCM_BASE_ADDR+0x18) //  32bit Serial Perpheral PLL Ctrl 1
#define CCM_COSR (CCM_BASE_ADDR+0x1C) //  32bit Osc 26M register
#define CCM_CGR0 (CCM_BASE_ADDR+0x20) //  32bit Serial Perpheral Clk Div Reg
#define CCM_CGR1 (CCM_BASE_ADDR+0x24) //  32bit Perpheral Clk Control Reg 0
#define CCM_CGR2 (CCM_BASE_ADDR+0x28) //  32bit Perpheral Clk Control Reg 0

#define CLOCK_SEL_MASK	0x00000006
#define CKIL_CLOCK_SEL	0x00000002
#define CKIH_CLOCK_SEL	0x00000004

#endif /* UNIT_TEST */

/*!
 * USB specific
 */
#define MPS_8	8
#define MPS_64	64

#define OUT	0
#define IN	1

#define EP0	0
#define EP1	1
#define EP2	2

#define ZLT_ENABLE	0
#define ZLT_DISABLE	1

#define IOS_NOTSET	0
#define IOS_SET		1

#define IOC_NOTSET	0
#define IOC_SET		1

#define TERMINATE	1
#define NOT_TERMINATE	0

#define DEFAULT_STATE	0
#define ADDR_STATE	1


#define NO_STATUS	0
#define ACTIVE	BIT7
#define HALTED	BIT6
#define DATA_BUFFER_ERROR	BIT5
#define TRANSACTION_ERROR	BIT3

#define DEVICE_DESC	0x1
#define CONF_DESC	0x2
#define STR_DES0	0x3
#define STR_DES1	0x4
#define STR_DES2	0x5
#define STR_DES3	0x6

#define EP1OUT_ENABLE	BIT7
#define EP2IN_ENABLE	BIT23

#define EP0OUT_COMPLETE BIT0
#define EP1OUT_COMPLETE	BIT1
#define EP0IN_COMPLETE	BIT16
#define EP2IN_COMPLETE	BIT18

#define EP1OUT_PRIME	BIT1
#define EP2IN_PRIME	BIT18
//ES Changed by Eyal Segev to speedup verification
#ifdef RTL_STUB
#define TIMEOUT_VALUE	100
#else
#define TIMEOUT_VALUE	100000
#endif /* RTL_STUB */

/*!
 * dQH address bit [10:0] MUST be ZERO
 * dQH(0-5) region
 * 0x1FFFC000 to 0x1FFFC180 
 */
#define dQHBASE	0x1FFFC000
#define	dQH0_EP0OUT	(dQHBASE + 0x000)	// EP0 OUT
#define	dQH1_EP0IN	(dQHBASE + 0x040)	// EP0 IN
#define	dQH2_EP1OUT	(dQHBASE + 0x080)	// EP1 OUT
#define	dQH5_EP2IN	(dQHBASE + 0x140)	// EP2 IN

/*!
 * dTD for dQH0_EP0OUT region
 * 0x1FFFC180 to 0x1FFFC1C0
 */
#define dTD0_EP0OUT	(dQHBASE + 0x180)
#define dTD1_EP0OUT	(dQHBASE + 0x1A0)	// of no use
	
/*!
 * dTD for dQH1_EP0IN region
 * 0x1FFFC1C0 to 0x1FFFC200
 */
#define dTD0_EP0IN	(dQHBASE + 0x1C0)
#define dTD1_EP0IN	(dQHBASE + 0x1E0)	// of no use

/*!
 * dTD for dQH2_EP1OUT region
 * 0x1FFFC200 to 0x1FFFC240
 */
#define dTD0_EP1OUT	(dQHBASE + 0x200)
#define dTD1_EP1OUT	(dQHBASE + 0x220)

/*!
 * dTD for dQH5_EP1OUT region
 * 0x1FFFC240 to 0x1FFFC240
 */
#define dTD0_EP2IN	(dQHBASE + 0x240)
#define dTD1_EP2IN	(dQHBASE + 0x260)

/*!
 * Buffer Pointer for EP0 IN
 * 0x1FFFC280 to 0x1FFFC2C0
 */
#define BUFPTR_P0_EP0IN		(dQHBASE + 0x280)

/*!
 * Buffer Pointer for EP1 OUT (16 bytes should be enough)
 * 0x1FFFC2C0 to 0x1FFFC2D0
 */
#define BUFPTR_P0_EP1OUT	(dQHBASE + 0x2C0)

/*!
 * Buffer Pointer for EP1 OUT (16 bytes should be enough)
 * 0x1FFFC2D0 to 0x1FFFC300
 */
#define BUFPTR_P0_EP2IN		(dQHBASE + 0x2D0)


//=====================
// Bootstrap specific
//=====================
// Command Packet Format: Header(2)+Address(4)+Format(1)+ByteCount(4)+Data(4) 
#define	ReadHeader	0x0101
#define WriteHeader 0x0202
#define PCHeader 	0x0303
#define WriteFile 	0x0404
#define ErrorHeader	0x0505
#define CSFHeader	0x0606
#define HWConfigHeader	0x0707
#define ExecuteHeader	0x0808
#define ReEnumHeader	0x0909

#define ProductionPart 	0x12343412
#define DevelopmentPart 0x56787856
#define WriteComplete	0x128A8A12
#define ReEnumAck		0x89232389

#define COMMAND 0x10
#define ByteCount_16kBytes	0x4000

#define DONE		1
#define CONTINUE	0
#define RE_ENUM		2

#define COMPLETE	0x88

#define MAX_USB_DATA_LEN	(16*1024)

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
typedef struct s_dQH_SETUP{
	u32 dQH_WORD0;	
	u32 dQH_WORD1;	
	u32 dQH_WORD2;	
	u32 dQH_WORD3;	
	u32 dQH_WORD4;	
	u32 dQH_WORD5;	
	u32 dQH_WORD6;	
	u32 dQH_WORD7;	
	u32 dQH_WORD8;	
	u32 dQH_WORD9;	
	u32 dQH_WORD10;	
	u32 dQH_WORD11;	

} s_dQH_SETUP;

typedef struct s_dTD_SETUP{
	u32 dTD_WORD0;	
	u32 dTD_WORD1;	
	u32 dTD_WORD2;	
	u32 dTD_WORD3;	
	u32 dTD_WORD4;	
	u32 dTD_WORD5;	
	u32 dTD_WORD6;	
	u32 dTD_WORD7;	
} s_dTD_SETUP;

/*!
 * channel type
 */
typedef enum {
	CHAN_UART,
	CHAN_USB,
} CHANNEL_TYPE;

/*!
 * channel exported functions
 */
extern void atk_channel_init(u8 ch);
extern u32 atk_channel_recv(u8 *buf, u32 count);
extern u32 atk_channel_send(const u8 *buf, u32 count);

#endif /* _CHANNEL_H_ */
