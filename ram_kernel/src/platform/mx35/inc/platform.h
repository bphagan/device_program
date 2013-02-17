/*****************************************************************************
** platform.h
**
** Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.
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
 * @file platform.h
 *
 * @brief the platform specific functions file
 *
 * @ingroup RAM Kernel
 */
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
* <Includes>
*****************************************************************************/

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define MX35	4
#define MEM_BASE_ADDR	0x80000000
#define MEM_BOTTOM_ADDR	0x87FFFFFF
/* watch dog registers */
#define WDOG_BASE_ADDR	0x53FDC000
#define WDOG_WCR	(WDOG_BASE_ADDR)
#define WDOG_WSR	(WDOG_BASE_ADDR + 0x2)

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
extern void sys_reset(void);
extern u8 sys_get_chip_id(void);
extern void sys_init(void);
/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PLATFORM_H_ */
