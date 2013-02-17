/*****************************************************************************
** debug.h
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
 * @file debug.h
 *
 * @brief the RAM Kernel debug defines.
 *
 * @ingroup RAM Kernel
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include <stdio.h>

/*****************************************************************************
* <Macros>
*****************************************************************************/

#ifdef _DEBUG
#define dbg(format, arg...)	printf(format, ##arg)
#else
#define dbg(format, arg...)
#endif

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEBUG_H_ */
