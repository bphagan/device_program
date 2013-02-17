/*****************************************************************************
** nor_flash.c
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
 * @file nor flash.c
 *
 * @brief source code for basic nor flash operations
 *
 * @ingroup spansion nor flash
  * @{
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"
#include "protocol.h"
#include "nor_flash.h"
#include "flash_lib.h"
#include "spansion_lld.h"
#include <stdio.h>


/*****************************************************************************
* <Macro>
*****************************************************************************/

static struct nor_flash_model supported_model[] = {

	{ 
	.device_name = "SG29GL512N", 
	.device_size = DEVICE_64M,
	.max_wb_word = 16,
	.device_id = 0x22012223, 
	.sector_size = { SECTOR_128K, 0 }, 
	.sector_mask = 0,
	},
	{ 
	.device_name = "S71WS256ND0", 
	.device_size = DEVICE_32M,
	.max_wb_word = 32,
	.device_id = 0x22002230, 
	.sector_size = { SECTOR_32K, SECTOR_128K }, 
	.sector_mask = ~(0x1FFFFUL),
	},
};

static struct nor_flash_model *model = NULL;

/* check offset and size param */
static s32 check_param(u32 addr, u32 size)
{
	if ( (addr >= FLASH_BASE_ADDR + model->device_size) ||
			addr < FLASH_BASE_ADDR || size == 0 || 
			(addr + size > FLASH_BASE_ADDR + model->device_size) )	
		return FLASH_ERROR_OVER_ADDR;
	return 0;
}

/* get sector size */
static inline u32 _get_aligned_sector_size(u32 sector)
{
	u32 offset_insector = sector,
	    left_size, sector_size,
	    half_dev_size = model->device_size >> 1;

	if (sector >= model->device_size) 
		return 0;
	/* get start and end sector head offset */
	if (offset_insector >= half_dev_size) {
		left_size = model->device_size - offset_insector;
		sector_size = model->sector_size[(left_size & model->sector_mask)==0?0:1];
	} else {
		sector_size = model->sector_size[(offset_insector & model->sector_mask)==0?0:1];
	}
	return sector_size;
}

/** 
 * return the sector size and override the sector offset to aligned offset
 */
static inline u32 _get_sector_size(u32 *psector_off)
{
	u32 offset_insector = *psector_off,
	    left_size, sector_size,
	    half_dev_size = model->device_size >> 1;

	if (*psector_off >= model->device_size) 
		return 0;
	/* get start and end sector head offset */
	if (offset_insector >= half_dev_size) {
		left_size = model->device_size - offset_insector;
		sector_size = model->sector_size[(left_size & model->sector_mask)==0?0:1];
	} else {
		sector_size = model->sector_size[(offset_insector & model->sector_mask)==0?0:1];
	}

	/* FIXME: not sure that all the sector
	 * is aligned with it's own size.
	 * Here just suppose all sectors is aligned on it's own size
	 */
	/* align the sector offset */
	*psector_off = offset_insector & ~(sector_size-1);
	return sector_size;
}

/*!
 * Function to move flash to the read mode
 */
void nor_flash_reset(void)
{
	lld_reset(FLASH_BASE_ADDR);
}

/*!
 * Get flash model name
 */
void nor_flash_get_model(u8 *mode_name, u32 *len)
{
	int i = 0;
	mode_name[0] = 'N';
	mode_name[1] = 'O';
	mode_name[2] = 'R';
	mode_name[3] = ' ';

	do {
		mode_name[i+4] = model->device_name[i];
		i ++;
	} while (model->device_name[i-1] != '\0');
	*len = i + 3;
}

/*!
 * Function to check if the flash manufacture code is 0x01
 *
 * @return	 OK if Flash Manufacture code is 0x01 , else ERR
 */
static s8 nor_flash_scan_model(void)
{
	u32 nr_model = sizeof(supported_model)/sizeof(struct nor_flash_model);
	u32 i, id;
	u16 id1, id2;
	u16 manuid;

	/* entry autoselect mode */
	lld_entry_autoselect(FLASH_BASE_ADDR);
	/* read manufacturer id */
	manuid = *(u16 *)FLASH_BASE_ADDR;
	id1 = *(u16 *)(FLASH_BASE_ADDR + NOR_DEVID_ADDR1);
	id2 = *(u16 *)(FLASH_BASE_ADDR + NOR_DEVID_ADDR2);
	if (manuid != SPANSION_MANUFACTURER_ID) {
		return -1;
	}
	/* read id */
	id = id1 | (((u32)id2 << 16) & 0xFFFF0000);

	/* exit autoselect mode */
	lld_reset(FLASH_BASE_ADDR);

	for (i = 0; i < nr_model; i ++) {
		if (supported_model[i].device_id == id) {
			model = &supported_model[i];
			break;
		}
	}
	if (model == NULL) {
		/* can not get the supported flash model */
		return -1;
	}

	return 0;
}

/*!
 * Function to read flash from source address to destination address
 *
 * @param	[in] source  -Flash source address
 * @param	[in] dest	- RAM destination addrerss
 * @param	[in] byte_count	-bytes to be read
 * @param	[in] callback	-send response and dump data to host
 * @param	[in] bufsize	-ram kernel offered buf size
 * @return 	operation result
 */
s16 nor_flash_read(u32 source, u32 dest, u32 byte_count, 
				dump_callback callback, u32 bufsize)
{
	u32 count = 0 ;	
	u32 i = 0, j = 0, b = 0;
	u16 *src_ptr;
	u16 *dest_ptr, *last_ptr;
	u32 times, left_bytes, left_size, 
	    blocks_per_time, left_blocks;
	u16 csum;

	/* check parameters */
  u32 ret  = check_param(source, byte_count);
	if (0 != ret)
	return ret;

	src_ptr = (u16 *)source;
	count = byte_count >> 1;	

	times = byte_count / bufsize;
	blocks_per_time = bufsize / OP_BLOCK_SIZE;
	left_size = byte_count % bufsize;
	left_blocks = left_size / OP_BLOCK_SIZE;
	left_bytes = left_size % OP_BLOCK_SIZE;

	/* for each data expand the ram kernel buffer */
	for (j = 0; j < times; j ++) {
		dest_ptr = (u16 *)dest;
		last_ptr = dest_ptr;
		
		/* dump each block */
		for (b = 0; b < blocks_per_time; b++) {
			for (i = 0; i < (OP_BLOCK_SIZE >> 1); i++) {
				*dest_ptr++ = *src_ptr++;
			}

			/* make check sum */
			csum = calculate_checksum((u8 *)last_ptr, OP_BLOCK_SIZE); 
			if (left_size == 0 && j == times - 1 && b == blocks_per_time - 1) {
				/* send response and data */
				callback((u8 *)last_ptr, RET_SUCCESS, csum, OP_BLOCK_SIZE);
				return RET_SUCCESS;
			} else {
				/* send response and data */
				callback((u8 *)last_ptr, FLASH_PARTLY, csum, OP_BLOCK_SIZE);
			}
			last_ptr = dest_ptr;
		}
	}

	/* left data within buffer */
	dest_ptr = (u16 *)dest;
	last_ptr = dest_ptr;

	for (b = 0; b < left_blocks; b ++) {

		for (i = 0; i < (OP_BLOCK_SIZE >> 1); i++) {
			*dest_ptr++ = *src_ptr++;
		}

		/* make check sum */
		csum = calculate_checksum((u8 *)last_ptr, OP_BLOCK_SIZE); 
		if (left_bytes == 0 && b == left_blocks - 1) {
			/* send response and data */
			callback((u8 *)last_ptr, RET_SUCCESS, csum, OP_BLOCK_SIZE);
			return RET_SUCCESS;
		} else {
			/* send response and data */
			callback((u8 *)last_ptr, FLASH_PARTLY, csum, OP_BLOCK_SIZE);
		}
		last_ptr = dest_ptr;

	}

	for (i = 0; i < (left_bytes >> 1) + 1; i++) {
		*dest_ptr++ = *src_ptr++;
	}
	csum = calculate_checksum((u8 *)last_ptr, left_bytes); 
	callback((u8 *)last_ptr, RET_SUCCESS, csum, left_bytes);

	return RET_SUCCESS;
}

/*!
 * Function to write flash from source address to destination address
 * Take advantage of the spansion nor write buffer program feature,
 * we can write 32 words at once.
 *
 * @param	[in] source	- source address
 * @param	[in] dest		-destination address
 * @param	[in]byte_count	-byte sizes to be programmed
 * @param	[in] callback	-send response to host during progress
 * @return 	0 successful, less than 0 error
 */
s16 nor_flash_program(u32 source, u32 dest, u32 byte_count, 
					response_callback callback)
{
	u32 i = 0;
	u32 start_sector, end_sector;
	u32 sector_size, 
	    pgsize; /* program size(word) in current sector */
	u16 *psrc;
	u32 dstaddr;
	poll_status_t status;

	/* check flash initial */
	if (model == NULL) {
		return ERROR_COMMAND;
	}

	/* check parameters */
	u32 ret  = check_param(dest, byte_count);
	if (0 != ret)
	return ret;

	psrc= (u16 *)source;
	/* get start sector info */
	dstaddr = start_sector = dest - FLASH_BASE_ADDR;
	end_sector = start_sector + byte_count;

	/* get aligned start_sector */
	sector_size = _get_sector_size(&start_sector);

	/* get the program size in current program sector */
	pgsize = sector_size - (dest - FLASH_BASE_ADDR - start_sector);
	pgsize >>= 1; /* size in word */

	do {
		u32 unaligned_size = (model->max_wb_word << 1) - 
					(dstaddr % (model->max_wb_word << 1));
		unaligned_size >>= 1;
		unaligned_size = unaligned_size > pgsize ? pgsize:unaligned_size;

		/* erase this sector firstly */
		if (nor_flash_erase(dstaddr + FLASH_BASE_ADDR, (pgsize << 1) - 1, NULL)) {
			return FLASH_ERROR_ERASE;
		}

		/* send flashed byte size response */
		callback(FLASH_PARTLY, 0, pgsize << 1);
		
		if (unaligned_size) {
			/**
			 * write buffer program only can program the 0x20 word aligned 
			 * page buffer per operation.
			 * here align the next buffer
			 */
			status = lld_program_writebuffer(FLASH_BASE_ADDR, dstaddr, 
					unaligned_size, psrc);
			if (status != DEV_NOT_BUSY) {
				return FLASH_ERROR_PROG;
			}
			dstaddr += unaligned_size << 1;
			psrc += unaligned_size;
			pgsize -= unaligned_size;
		}

		/* write max wb program words first */
		for (i = 0; i < pgsize / model->max_wb_word; i++) {

			status = lld_program_writebuffer(FLASH_BASE_ADDR, dstaddr, 
					model->max_wb_word, psrc);
			if (status != DEV_NOT_BUSY) {
				return FLASH_ERROR_PROG;
			}
			dstaddr += model->max_wb_word << 1;
			psrc += model->max_wb_word;
		}
		/* write left program words in this sector */
		if (pgsize %= model->max_wb_word) {
			status = lld_program_writebuffer(FLASH_BASE_ADDR, dstaddr, 
					pgsize, psrc);
			if (status != DEV_NOT_BUSY) {
				return FLASH_ERROR_PROG;
			}
			dstaddr += pgsize << 1;
			psrc += pgsize;
		}

		/* peek for next sector program info */
		start_sector += sector_size;
		sector_size = _get_aligned_sector_size(start_sector);
		/* next sector is last one? */
		if (start_sector + sector_size >= end_sector) {
			pgsize = end_sector - start_sector;
		} else {
			/* not last one, programe sector size */
			pgsize = sector_size;
		}
		pgsize >>= 1;

	} while (start_sector < end_sector);

	return RET_SUCCESS;		
}

/*!
 * Function to initialize nor flash
 *
 * @return	0 successful, less than 0 error
 */
s16 nor_flash_init(void)
{
	nor_flash_reset();
	/* get the current nor flash model */
	if (nor_flash_scan_model()) {
		return FLASH_ERROR_INIT;
	}
	return 0;
}

/*!
 * Function to erase flash
 *
 * @param	[in] dest  - destination address
 * @param	[in] byte_count - bytes to be erased
 * @param	[in] callback	-send response to host during progress
 * @return 	0 successful, less than 0 error
 */
s16 nor_flash_erase(u32 dest, u32 byte_count, response_callback callback)
{
	u32 start_offset = dest - FLASH_BASE_ADDR,
	    start_sector, end_sector, sector_size;
	poll_status_t status;

	if (model == NULL) {
		return ERROR_COMMAND;
	}
	/* check parameters */	
	u32 ret  = check_param(dest, byte_count);
	if (0 != ret)
	return ret;

	/* get start and end sector aligned offset */
	start_sector = start_offset;
	end_sector = start_offset + byte_count - 1;
	_get_sector_size(&start_sector);
	_get_sector_size(&end_sector);

	/* sector erase for each sectors */
	while (start_sector <= end_sector) {

		/* call sector erase function */
		status = lld_erase_sector(FLASH_BASE_ADDR, start_sector);
		if (status != DEV_NOT_BUSY) {
			return FLASH_ERROR_ERASE;
		}
		sector_size = _get_aligned_sector_size(start_sector);
		/* call response callback */
		if (callback != NULL && start_sector < end_sector) {
			callback(FLASH_ERASE, 0, sector_size);
		}
		start_sector += sector_size;
	}

	return RET_SUCCESS;
}

/*!
 * Function to compare content and return flash check sum
 *
 * @param	[in] source  - buffer address
 * @param	[in] flash_addr - flash addr to be compared
 * @param	[in] byte_count - byte size
 * @param	[out] byte_count - byte size
 * @param	[in] callback	-send response to host during progress
 * @return 	0 successful, less than 0 error
 */
s16 nor_flash_compare(u32 source, u32 flash_addr, u32 byte_count, 
		u16 *pcsum, response_callback callback)
{
	u32 count = 0 ;	
	u32 i = 0;
	u8 *pSrc_ptr;
	u8 *pDest_ptr;
	s16 ret = RET_SUCCESS;

	pSrc_ptr = (u8 *)source;
	pDest_ptr = (u8 *)flash_addr;
	count = byte_count;	
	*pcsum =0;
	
	for ( i = 0; i < count ; i++) {
		if (pDest_ptr[i] != pSrc_ptr[i]) {
			ret = FLASH_ERROR_VERIFY;
			break;
		} else {
			*pcsum += pDest_ptr[i] & 0xFF;
		}
		if (0 == (i % OP_BLOCK_SIZE)) {
			/* send flashed byte size response */
			callback(FLASH_VERIFY, 0, OP_BLOCK_SIZE);
		}
	}
	return ret;
}

/*!
 * Function to get nor flash size
 *
 * @return	0 successful, less than 0 error
 */
s16 nor_flash_get_capacity(u32 *size)
{
	/* the capacity is size*1024 Bytes */
	if (size && model)
		*size = (((model->device_size>>10)) > 0xFFFFFFFF) ? 0xFFFFFFFF : (model->device_size)>>10;
   	return FLASH_ERROR_NO;
}

/**@}*/
