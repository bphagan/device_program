/*****************************************************************************
** flash_lib.h
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
 * @file flash_lib.h
 *
 * @brief the RAM Kernel flash library header file.
 *
 * @ingroup RAM Kernel
 */
#ifndef _FLASH_LIB_H_
#define _FLASH_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************
* <Includes>
*****************************************************************************/

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define FLASH_MODEL_MAX		128

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
typedef enum 
{
	FLASH_PRG_BOUNDARY,
	FLASH_PRG_UNBOUNDARY,
} FLASH_PRG_MODE;

typedef enum 
{
	FILE_FORMAT_NORMAL,
	FILE_FORMAT_NB0,
	FILE_FORMAT_OPS /*prog user set oob data*/
}FLASH_FILE_FORMAT;

typedef enum
{
	BI_SWAP_DISABLE,
	BI_SWAP_ENABLE
}BI_SWAP_FLAG;

typedef enum
{
	FL_BBT_DISABLE,
	FL_BBT_ENABLE
}FL_BBT_FLAG;

typedef enum
{
	FL_INTLV_DISABLE,
	FL_INTLV_ENABLE
}FL_INTLV_FLAG;

/*!
 * flash library function declarations
 */
/* flash initial function */
extern s16 atk_flash_lib_initial(void);
/* flash erase with from addr to addr+size */
extern s16 atk_flash_lib_erase(u32 addr, u32 size, response_callback callback);
/* flash read from addr with size of pcount, and put data into buffer */
extern s16 atk_flash_lib_read(u32 addr, u8 *buffer, u32 count,
		dump_callback callback, u32 bufsize);
/* flash program function */
extern s16 atk_flash_lib_program(u32 addr, const u8 *buffer, 
		u32 *pcount, u16 *pcsum, u8 mode,u8 file_format, 
		response_callback callback);
extern void atk_flash_get_model(u8 *fmodel, u32 *len);
extern s16 atk_flash_get_capacity(u32 *size);


/*!
 * Function to calculate the check sum of data
 *
 * @buffer data buffer
 * @count  data length
 *
 * @return the checksum value.
 */
static __inline u16 calculate_checksum(const u8 *buffer, u32 count)
{
	u16 csum = 0;

	while (count --) {
		csum += *(buffer++);
	}

	return csum;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FLASH_LIB_H_ */
