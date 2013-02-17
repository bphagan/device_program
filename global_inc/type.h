/*****************************************************************************
** type.h
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
 * @file type.h
 *
 * @brief the RAM Kernel type defines.
 *
 * @ingroup RAM Kernel
 */
#ifndef _TYPE_H_
#define _TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
* <Includes>
*****************************************************************************/

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define BIT0 	0x00000001
#define BIT1 	0x00000002
#define BIT2 	0x00000004
#define BIT3 	0x00000008
#define BIT4	0x00000010
#define BIT5 	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9 	0x00000200
#define BIT10 	0x00000400
#define BIT11 	0x00000800
#define BIT12 	0x00001000
#define BIT13 	0x00002000
#define BIT14 	0x00004000
#define BIT15 	0x00008000
#define BIT16 	0x00010000
#define BIT17 	0x00020000
#define BIT18 	0x00040000
#define BIT19 	0x00080000
#define BIT20 	0x00100000
#define BIT21 	0x00200000
#define BIT22 	0x00400000
#define BIT23 	0x00800000
#define BIT24 	0x01000000
#define BIT25 	0x02000000
#define BIT26 	0x04000000
#define BIT27 	0x08000000
#define BIT28 	0x10000000
#define BIT29 	0x20000000
#define BIT30 	0x40000000
#define BIT31 	0x80000000

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define __REG32(x)     (*((volatile u32 *)(x)))
#define __REG16(x)   (*((volatile u16 *)(x)))
#define __REG8(x)    (*((volatile u8 *)(x)))

#define __raw_writeb(v,a)       (*(volatile unsigned char  *)(a) = (v))
#define __raw_writew(v,a)       (*(volatile unsigned short *)(a) = (v))
#define __raw_writel(v,a)       (*(volatile unsigned int   *)(a) = (v))

#define __raw_readb(a)          (*(volatile unsigned char  *)(a))
#define __raw_readw(a)          (*(volatile unsigned short *)(a))
#define __raw_readl(a)          (*(volatile unsigned int   *)(a))

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned char uchar;   

typedef signed short s16;
typedef unsigned short u16;  
typedef unsigned short ushort;

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned int uint;
typedef unsigned long ulong;  

typedef signed long long s64;
typedef unsigned long long u64;

typedef void app(void);
typedef int (*usb_sw_fn_t)(void);

typedef void (*response_callback)(u16 ack, u16 csum, u32 len);
typedef void (*dump_callback)(const u8 *buffer, u16 ack, u16 csum, u32 len);



/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

/*****************************************************************************
* <Inline Function>
*****************************************************************************/
/* for fuse program */
static __inline u8 __readb(u32 addr) 
{
	return (u8)*(volatile u32 *)addr;
}

static __inline void __writeb(u8 val, u32 addr) 
{
	*(volatile u32 *)addr = val;
}

static __inline u8 __readw(u32 addr) 
{
	return (u16)*(volatile u32 *)addr;
}

static __inline void __writew(u16 val, u32 addr) 
{
	*(volatile u32 *)addr = val;
}

static __inline u32 __readl(u32 addr) 
{
	return *(volatile u32 *)addr;
}

static __inline void __writel(u32 val, u32 addr) 
{
	*(volatile u32 *)addr = val;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TYPE_H_ */
