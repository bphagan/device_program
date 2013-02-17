/*****************************************************************************
** flash_lib.c
**
** Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
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
 * @file flash_lib.c
 *
 * @brief source code for the interfaces of flash lib
 *
 * @ingroup spi_nor_flash
 * @{
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include <type.h>
#include <protocol.h>
#include <flash_lib.h>
#include <spi_nor.h>

/*!
 * Function to initialize the flash library device, including check device vendor, 
 * id and other physical geometric, etc
 * @return	- If initialization is ok, return RET_SUCCESS, otherwise error information will be returned
 */
s16 atk_flash_lib_initial (void)
{
	return (spi_flash_init());
		
}
/*!
 * Function to erase an area of flash
 *
 * @param	[in] addr	-flash offset address where to be erased
 * @param	[in] size -erase size in bytes.
 * 
 * @return 	- If erase successful, return RET_SUCCESS; otherwise return FLASH_FAILED
 */
s16 atk_flash_lib_erase (u32 addr, u32 size, response_callback callback)
{
	return (spi_flash_erase(addr, size, callback));
}
/*!
 * Function to read an area of flash and return the actually read data size
 *
 * @param	[in]	addr	-the flash offset address where to be dumped
 * @param	[out] buffer	-an input buffer for library function to fill data in
 * @param	[in/out] pcount 	-dump size in bytes, and return the actually dump size.
 * @param	[in] callback	-send response to host during progress
 * @return	- If read successful, return RET_SUCCESS
 *                       If the dump range exceed the flash size, return FLASH_PARTLY
 *                       If ECC error, return FLASH_ECC_FAILED
 *                       Otherwise return FLASH_FAILED.
 */
s16 atk_flash_lib_read (u32 addr, u8 *buffer, u32 count, 
					dump_callback callback, u32 bufsize)
{
	return (spi_flash_read(addr, (u32)buffer, count, callback));
}
/*!
 * Function to Program an area of flash, return the actual programmed size and checksum.
 *
 * @param	[in] addr	-the flash offset address where to be program
 * @param	[in] buffer	-buffer contains the program data
 * @param	[in/out] pcount	-program size in bytes, and return the actually program size.
 * @param	[out] pcsum	-return the actually programmed data checksum on flash
 * @param	[in] mode	-boundary or un-boundary mode
 * @param	[in] file_format	-used for nb0
 * @param	[in] callback	-send response to host during progress
 * @return 	0 successful, less than 0 error
 */
s16 atk_flash_lib_program (u32 addr, const u8 *buffer, u32 *pcount, 
				u16 *pcsum, u8 mode,u8 file_format,
				response_callback callback)
{
	s16 ret;
	ret = spi_flash_program((u32)addr, (u32)buffer, *pcount, callback);
	
	if (mode) {
		if (ret == 0) {
			ret = spi_flash_compare((u32)buffer, addr, *pcount, callback);
			if (ret == 0)
				*pcsum = calculate_checksum(buffer,*pcount);
		}
	}
	
	return ret;	
}

/*!
 * Function to get the flash model
 * @param	[out] fmodel- the flash model
 * @param	[out] len		-the len
 * @return 	void
 */
void atk_flash_get_model(u8 *fmodel, u32 *len)
{
	spi_flash_get_model(fmodel, len);
}

s16 atk_flash_get_capacity(u32 * size)
{
	s16 ret;
	ret = spi_flash_get_capacity(size);
	if (FLASH_ERROR_NO == ret)
		return RET_SUCCESS;

	return ret;		
}
/**@}*/

