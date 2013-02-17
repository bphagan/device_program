/*****************************************************************************
** fake_flashlib.c
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
 * @file fake_flashlib.c
 *
 * @brief fake flash library
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include <string.h>
#include "debug.h"
#include "type.h"
#include "protocol.h"
#include "flash_lib.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define FLASH_SIZE	(1024*1024)
/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/
static u8 flash[FLASH_SIZE];

/*!
 * Initial the flash library device, including check device vendor, 
 * id and other physical geometric, etc.
 * @return
 *	If initial ok, return RET_SUCCESS
 */
s16 atk_flash_lib_initial(void)
{
	dbg("Fake Flash Lib: initial routing\n");
	return RET_SUCCESS;
}

/*!
 * Erase an area of flash. 
 * @addr  flash address where to be erased
 * @size  erase size in bytes. 
 *
 * @return
 *	If erase successful, return RET_SUCCESS; 
 *	otherwise return FLASH_FAILED;
 */
s16 atk_flash_lib_erase(u32 addr, u32 size, response_callback callback)
{
	u16 real_size;

	dbg("Fake Flash Lib: erase routing(%x, %x)\n", addr, size);
	if (addr > FLASH_SIZE) {
		return FLASH_FAILED;
	}
	if (addr + size > FLASH_SIZE) {
		real_size = FLASH_SIZE - addr;
	} else {
		real_size = size;
	}
	memset((void *)(flash+addr), 0, real_size);
	return RET_SUCCESS;
}

/*!
 *  Dump an area of flash and return the actually dumped data size.
 *
 *  @addr  the flash address where to be dumped
 *  @buffer  an input buffer for library function to fill data in
 *  @pcount  dump size in bytes, and return the actually dump size.
 *  @return
 *	If read successful, return RET_SUCCESS; 
 *	if the dump range exceed the flash size, return FLASH_PARTLY; 
 *	if ECC error, return FLASH_ECC_FAILED; 
 *	otherwise return FLASH_FAILED.
 */
s16 atk_flash_lib_read(u32 addr, u8 *buffer, u32 *pcount)
{
	s16 ret = RET_SUCCESS;

	dbg("Fake Flash Lib: read routing(%x, %x, %x)\n", addr, buffer, *pcount);

	if (addr > FLASH_SIZE) {

		return FLASH_FAILED;
	}

	if (addr + *pcount > FLASH_SIZE) {
		*pcount = FLASH_SIZE - addr;
		ret = FLASH_PARTLY;
	}
	memcpy((void *)buffer, (void *)(flash+addr), *pcount);
	return ret;
}

static __inline u16 calculate_checksum(const u8 *buffer, u32 count)
{
	u16 csum = 0;

	while (count --) {
		csum += *(buffer++);
	}

	return csum;
}

/* flash program function */
s16 atk_flash_lib_program(u32 addr, const u8 *buffer, 
				u32 *pcount, u16 *pcsum, u8 mode,u8 file_format)
{
	s16 ret = RET_SUCCESS;

	dbg("Fake Flash Lib: program routing(%x, %x, %x)\n", addr, buffer, *pcount);

	if (addr > FLASH_SIZE) {

		return FLASH_FAILED;
	}

	if (addr + *pcount > FLASH_SIZE) {
		*pcount = FLASH_SIZE - addr;
		ret = FLASH_PARTLY;
	}
	memcpy((void *)(flash+addr), buffer, *pcount);
	
	*pcsum = calculate_checksum(buffer, *pcount);
	return ret;
}

void atk_flash_get_model(u8 *fmodel, u32 *len)
{
	u8 model[] = "fake";
	int i;
	for(i=0;i<sizeof(model);i++)
		fmodel[i] =  model[i];
	*len = sizeof(model) - 1;
}
