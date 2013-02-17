/*****************************************************************************
** platform.h
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
#include "su_basictypes.h"
/*****************************************************************************
* <Macros>
*****************************************************************************/
#define MX25    7	
#define MEM_BASE_ADDR	0x80000000
#define MEM_BOTTOM_ADDR	0x8FFFFFFF
/* watch dog registers */
#define WDOG_BASE_ADDR           0x53FDC000
#define WDOG_WCR                 (WDOG_BASE_ADDR+0x00)      // 16bit watchdog control reg
#define WDOG_WSR                 (WDOG_BASE_ADDR+0x02)      // 16bit watchdog service reg
#define WDOG_WRSR                (WDOG_BASE_ADDR+0x04)      // 16bit watchdog reset status reg

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
U8 sys_get_chip_id(void);
extern void sys_reset(void);
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
