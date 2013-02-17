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
//==================
// USB specific, senna only has host2
//==================
// #########################################
// # UART1                                 #
// # $1000_A000 to $1000_AFFF              #
// #########################################
#define UART1_BASE_ADDR          0x43F90000
#define UART1_URXD_1             (UART1_BASE_ADDR+0x00)     // 32bit uart1 receiver reg
#define UART1_UTXD_1             (UART1_BASE_ADDR+0x40)     // 32bit uart1 transmitter reg
#define UART1_UCR1_1             (UART1_BASE_ADDR+0x80)     // 32bit uart1 control 1 reg
#define UART1_UCR2_1             (UART1_BASE_ADDR+0x84)     // 32bit uart1 control 2 reg
#define UART1_UCR3_1             (UART1_BASE_ADDR+0x88)     // 32bit uart1 control 3 reg
#define UART1_UCR4_1             (UART1_BASE_ADDR+0x8C)     // 32bit uart1 control 4 reg
#define UART1_UFCR_1             (UART1_BASE_ADDR+0x90)     // 32bit uart1 fifo control reg
#define UART1_USR1_1             (UART1_BASE_ADDR+0x94)     // 32bit uart1 status 1 reg
#define UART1_USR2_1             (UART1_BASE_ADDR+0x98)     // 32bit uart1 status 2 reg
#define UART1_UESC_1             (UART1_BASE_ADDR+0x9C)     // 32bit uart1 escape char reg
#define UART1_UTIM_1             (UART1_BASE_ADDR+0xA0)     // 32bit uart1 escape timer reg
#define UART1_UBIR_1             (UART1_BASE_ADDR+0xA4)     // 32bit uart1 BRM incremental reg
#define UART1_UBMR_1             (UART1_BASE_ADDR+0xA8)     // 32bit uart1 BRM modulator reg
#define UART1_UBRC_1             (UART1_BASE_ADDR+0xAC)     // 32bit uart1 baud rate count reg
#define UART1_ONEMS_1            (UART1_BASE_ADDR+0xB0)     // 32bit uart1 one ms reg
#define UART1_UTS_1              (UART1_BASE_ADDR+0xB4)     // 32bit uart1 test reg


//ES Changed by Eyal Segev to speedup verification
#ifdef RTL_STUB
#define TIMEOUT_VALUE	100
#else
#define TIMEOUT_VALUE	100000
#endif /* RTL_STUB */


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
