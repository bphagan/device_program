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

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define MX27	0
#define MEM_BASE_ADDR	0xA0000000
#define MEM_BOTTOM_ADDR	0xAFFFFFFF
/* watch dog registers */
#define WDOG_BASE_ADDR           0x10002000
#define WDOG_WCR                 (WDOG_BASE_ADDR+0x00)      // 16bit watchdog control reg
#define WDOG_WSR                 (WDOG_BASE_ADDR+0x02)      // 16bit watchdog service reg
#define WDOG_WRSR                (WDOG_BASE_ADDR+0x04)      // 16bit watchdog reset status reg

//# Clock  and Reset Module (CRM) 
#define CRM_BASE_ADDR             0x10027000  
#define CRM_PCCR1 				(CRM_BASE_ADDR+0x24)   					 // ; Perpheral Clock Control Reg1

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
u8 sys_get_chip_id(void);
extern void sys_reset(void);
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
