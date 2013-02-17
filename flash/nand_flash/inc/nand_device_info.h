/*
 * Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */
#ifndef __DRIVERS_NAND_DEVICE_INFO_H
#define __DRIVERS_NAND_DEVICE_INFO_H

#include <type.h>

 /*
  * The number of ID bytes to read from the NAND Flash device and hand over to
  * the identification system.
  */

#define NAND_DEVICE_ID_BYTE_COUNT  (6)
#define SZ_1K	(1 << 10)
#define SZ_1M	(1 << 20)
#define SZ_1G	(1 << 30)

typedef int bool;	
#define false 0
#define true  1

#define NAND_MFR_TOSHIBA        0x98
#define NAND_MFR_SAMSUNG        0xec
#define NAND_MFR_FUJITSU        0x04
#define NAND_MFR_NATIONAL       0x8f
#define NAND_MFR_RENESAS        0x07
#define NAND_MFR_STMICRO        0x20
#define NAND_MFR_HYNIX          0xad
#define NAND_MFR_MICRON         0x2c
#define NAND_MFR_AMD            0x01
#define NAND_MFR_SANDISK        0x45
#define NAND_MFR_INTEL          0x89


 /*
  * The number of ID bytes to read from the NAND Flash device and hand over to
  * the identification system.
  */

enum nand_cell_type {
	NAND_DEVICE_CELL_TECH_SLC = 0,
	NAND_DEVICE_CELL_TECH_MLC = 1,
};

/**
 * struct nand_device_info - Information about a single NAND Flash device.
 *
 * This structure contains all the *essential* information about a NAND Flash
 * device, derived from the device's data sheet. For each manufacturer, we have
 * an array of these structures.
 *
 * @end_of_table:              If true, marks the end of a table of device
 *                             information.
 * @man_id:         	       The manufacturer code (1st ID byte) reported by
 *                             the device.
 * @dev_id:                    The device code (2nd ID byte) reported by the
 *                             device.
 * @cell_type:                 The storage cell technology.
 * @chip_size_in_bytes:        The total size of the storage behind a single
 *                             chip select, in bytes. Notice that this is *not*
 *                             necessarily the total size of the storage in a
 *                             *package*, which may contain several chips.
 * @block_size_in_pages:       The number of pages in a block.
 * @blk_count		       the block count in one chip. No need to set staticly.
 * @ppb			       number of pages in one block.
 * @page_size:		       page size
 * @oob_size		       OOB size
 * @bbm_offset                 offset for bad block indication within one page
 * @scan_pg_num		       how many pages need to scan for the bad block indication
 * @bbi_page_offset            offset for the page which contains the bad block indication within one block
 * @bus_width		       bus width(8bit or 16bit)
 * @row_addr_cycle	       row address cycles, No need to set staticly.
 * @num_chips		       number of chips in NAND package.
 * @bbt			       bad block table
 * @model		       NAND flash model type.
 */

struct nand_device_info {

	/* End of table marker */
	bool	end_of_table;

	/* Manufacturer and Device codes */
	u8  	man_id;
	u8	dev_id;

	/* Technology */
	enum nand_cell_type  cell_type;

	/* Geometry */
	u64 	chip_size_in_bytes;
	u32   	blk_count;
	u32   	ppb;
	u16 	page_size;
	u16	oob_size;
	
	/* bad block management */
	u8    	bbm_offset;
	u8	scan_pg_num;
	u16   	bbi_page_offset;
	
	u8	bus_width;
	u8    	row_addr_cycle;
	u8    	num_chips;
	u8*   	bbt; 
	
	const char  *model;

};

/**
 * nand_device_get_info - Get info about a device based on ID bytes.
 *
 * @id_bytes:  An array of NAND_DEVICE_ID_BYTE_COUNT ID bytes retrieved from the
 *             NAND Flash device.
 */

struct nand_device_info *nand_device_get_info(const u8 id_bytes[]);

/**
 * nand_device_print_info - Prints information about a NAND Flash device.
 *
 * @info  A pointer to a NAND Flash device information structure.
 */

void nand_device_print_info(struct nand_device_info *info);

#endif
