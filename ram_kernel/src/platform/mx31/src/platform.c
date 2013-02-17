/*****************************************************************************
** platform.c
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
 * @file platform.c
 *
 * @brief the platform specific functions file
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"
#include "platform.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

/*!
 * Function to reset the MX31
 */
void sys_reset(void)
{
	u16 wdog_conf;
	wdog_conf = (*(volatile u16*)(WDOG_WCR) | 0x1000) & ~0x0018;
	*(volatile u16*)(WDOG_WCR) = wdog_conf;
	wdog_conf |= 0x4;
	*(volatile u16*)(WDOG_WCR) = wdog_conf;
	
	while(1);
	return;
}

u8 sys_get_chip_id(void)
{
	return MX31;
}
