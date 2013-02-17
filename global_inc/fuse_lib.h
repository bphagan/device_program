/*****************************************************************************
** fuse_lib.h
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
 * @file fuse_lib.h
 *
 * @brief the RAM Kernel fuse library header file.
 *
 * @ingroup RAM Kernel
 */
#ifndef _FUSE_LIB_H_
#define _FUSE_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
* <Includes>
*****************************************************************************/

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*!
 * fuse library function declarations
 */
/* fuse read function */
extern s32 atk_fuse_lib_read(u32 addr, u8 *pval);
/* fuse sense function */
extern s32 atk_fuse_lib_sense(u32 addr, u8 *pval, u8 bit);
/* fuse override function */
extern s32 atk_fuse_lib_override(u32 addr, u8 val);
/* fuse program function */
extern s32 atk_fuse_lib_program(u32 addr, u8 val);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FUSE_LIB_H_ */
