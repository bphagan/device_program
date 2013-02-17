/*****************************************************************************
** fake_fuselib.c
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
 * @file fake_fuselib.c
 *
 * @brief fake fuse library
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "debug.h"
#include "type.h"
#include "protocol.h"
#include "fuse_lib.h"

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
static u8 fuse_box[10] = {

	0x01, 0x02, 0x03, 0x04, 0x05, 
	0x16, 0x17, 0x18, 0x19, 0x1A,
};

/*!
 * Read a fuse word. 
 * @addr  fuse element address.
 * @pval  fuse word value returned.
 *
 * @return 
 *	If read successful, return RET_SUCCESS; 
 *	if the fuse element is read protected, return FUSE_READ_PROTECT; 
 *	otherwise return FUSE_FAILED.
 */
s32 atk_fuse_lib_read(u32 addr, u8 *pval)
{
	dbg("Fake Fuse Lib: read routing(%x, %x)\n", addr, *pval);

	if (addr > 9) {
		return FUSE_FAILED;
	}
	*pval = fuse_box[addr];
	return RET_SUCCESS;
}

/*!
 * Sense a fuse word. 
 * @addr  fuse element address.
 * @pval  fuse word value returned.
 *
 * @return 
 *	If sense successful, return RET_SUCCESS; 
 *	if the fuse element is read protected, return FUSE_READ_PROTECT; 
 *	otherwise return FUSE_FAILED.
 */
s32 atk_fuse_lib_sense(u32 addr, u8 *pval, u8 bit)
{
	dbg("Fake Fuse Lib: sense routing(%x, %x)\n", addr, *pval);

	if (addr > 9) {
		return FUSE_FAILED;
	}
	*pval = fuse_box[addr];
	return RET_SUCCESS;
}

/*!
 * Override a fuse word.
 * @addr  fuse element address.
 * @val  fuse word value.
 *
 * @return
 *	If override successful, return RET_SUCCESS; 
 *	if the fuse element is override protected, return FUSE_OVERRIDE_PROTECT; 
 *	otherwise return FUSE_FAILED.
 */
s32 atk_fuse_lib_override(u32 addr, u8 val)
{
	dbg("Fake Fuse Lib: override routing(%x, %x)\n", addr, val);

	if (addr > 9) {
		return FUSE_FAILED;
	}
	fuse_box[addr] = val;
	return RET_SUCCESS;
}

/*!
 * Program a fuse element.
 * @addr  fuse element address.
 * @val  fuse element value. 
 *
 * @return
 *	If program successful and verify is passed, return RET_SUCCESS; 
 *	if the fuse element is write protected, return FUSE_WRITE_PROTECT; 
 *	if the program successfully , but verify can¡¯t be done, return FUSE_VERIFY_FAILED; 
 *	otherwise return FUSE_FAILED.
 */
s32 atk_fuse_lib_program(u32 addr, u8 val)
{
	dbg("Fake Fuse Lib: program routing(%x, %x)\n", addr, val);

	if (addr > 9) {
		return FUSE_FAILED;
	}
	fuse_box[addr] = val;
	return RET_SUCCESS;
}
