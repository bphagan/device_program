/*****************************************************************************
** nor_flash.h
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
 * @file nor_flash.h
 * @defgroup spansion nor flash
 
 * @brief the header file for nor flash
 * @ingroup spansion nor flash
 * @{
 */

#ifndef __NOR_FLASH_H_
#define __NOR_FLASH_H_
/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/
/* flash CS0 base address define */
#if defined(MCU_MX31) || defined(MCU_MX32) || defined(MCU_MX35)
#define FLASH_BASE_ADDR	0xA0000000 /* mx31 CS0 address*/
#elif defined(MCU_MX27)
#define FLASH_BASE_ADDR	0xC0000000 /* mx31 CS0 address*/
#else
#error No such MCU chip type!
#endif

#define DEVICE_64M	(64 * 1024 * 1024)
#define DEVICE_32M	(32 * 1024 * 1024)
#define DEVICE_16M	(16 * 1024 * 1024)

#define SECTOR_128K	(128 * 1024)
#define SECTOR_32K	(32 * 1024)
/*****************************************************************************
* <Typedefs>
*****************************************************************************/

struct nor_flash_model {

	u8 device_name[16];
	u32 device_size; /* read from CFI */
	u32 device_id; /* read from CFI and do compare */
	u32 max_wb_word; /* write buffer max supported word */
	u32 sector_size[2];
	u32 sector_mask; /* mask address offset to get sector_size[] index */
};

/*****************************************************************************
* global var
*****************************************************************************/


/*!
 * nor flash function declarations
 */
/**
 * initialize nor flash 
 * where we can identify the nor flash mode, and configure it
 */ 
extern s16 nor_flash_init(void);
/** 
 * erase nor flash
 * Spansion nor flash provide chip erase and sector erase.
 */
extern s16 nor_flash_erase(u32 dest, u32 byte_count, 
				response_callback callback);
/**
 * program nor flash
 * Spansion nor flash provide word program and write buffer program.
 */
extern s16 nor_flash_program(u32 source, u32 dest, u32 byte_count,
				response_callback callback);
/*read nor flash*/
extern s16 nor_flash_read(u32 source, u32 dest, u32 byte_count,
				dump_callback callback, u32 bufsize);
/* compare content and return flash check sum*/
extern s16 nor_flash_compare(u32 source, u32 flash_addr, u32 byte_count, 
				u16 *pcsum, response_callback callback);
/**
 * get nor flash size
 */ 
extern s16 nor_flash_get_capacity(u32 *size);
/**@}*/

#endif
