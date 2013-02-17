/*****************************************************************************
** spi_nor_ids.c
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

#include <spi_nor.h>

const spi_flash_model __attribute__ ((aligned(8)))  sst_model[] = {
	{
		.name = "sst25vf016b",
		.device_id1 = 0xbf, 
		.device_id2 = 0x25, 
		.device_id3 = 0x41,  
		.block_size = 0x10000,
		.block_count = 32,
	},
	{
		.name = "MX25L6405D",
		.device_id1 = 0xc2, 
		.device_id2 = 0x20, 
		.device_id3 = 0x17,  
		.block_size = 0x10000,
		.block_count = 128,
	},

	{ 0,}
};


const spi_flash_model __attribute__ ((aligned(8)))  atm_model[] = {
	{
		.name = "at45db321d",
		.device_id1 = 0x1f, 
		.device_id2 = 0x27, 
		.device_id3 = 0x01,  
		.block_size = 512,
		.block_count = 8192,
	},
	
	{ 0,}
};

const spi_flash_model __attribute__ ((aligned(8)))  *supported_model[] = {
	/* 0 */
	sst_model,
	
	/* 1 */
	atm_model,
	
	0

};
