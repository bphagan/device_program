/*****************************************************************************
** spansion_ldd.c
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
 * @file spansion_ldd.c
 * @defgroup spansion nor flash
 
 * @brief the spansion nor flash low level driver file, _ONLY_ support x16 spansion
 * 	nor flash.
 * @ingroup spansion nor flash
 * @{
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"
#include "spansion_lld.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*****************************************************************************
* global var
*****************************************************************************/

/*****************************************************************************
* functions
*****************************************************************************/
static void lld_reset_wb_abort(u32 baseaddr);
static poll_status_t lld_get_status(u32 baseaddr, u32 offset, u8 wbprogram);

void udelay(u32 delay)
{
	int i;
	for (i = 0; i < delay*600; i++) {
	}
}

/**
* lld_poll_status
*
* Polls flash device for embedded operation completion
*
* Function polls the Flash device to determine when an embedded
*  operation has finished.  
*  Function performs a verify on the polling address if the device
*  returns from status routine in a non-busy/non-error state.
*
* <polling_type> variable is used to determine type of polling to perform.
*  This variable tells the status routine what mode the device is in.
*  Future versions of this function will also use the <polling_type>
*  variable to properly initialize and implement watchdog timers.
*  Acceptable values for <polling_type> are:
*   LLD_P_POLL_PGM 
*   LLD_P_POLL_WRT_BUF_PGM
*   LLD_P_POLL_SEC_ERS   
*   LLD_P_POLL_CHIP_ERS 
*
*/
poll_status_t lld_poll_status(u32 baseaddr, u32 offset, poll_type_t polltype)
{       
	poll_status_t dev_status;
	u32 polling_counter = 0xFFFFFFFF;
	u8 wbprogram = 0;

	/* wait for 4us */
	udelay(4);

	/* set the WriteBuffer flag if writebuffer operation */
	if (polltype == LLD_P_POLL_WRT_BUF_PGM)
		wbprogram = 1;

	do {
		polling_counter--;
		dev_status = lld_get_status(baseaddr, offset, wbprogram);
	} while((dev_status == DEV_BUSY) && polling_counter);

	/* if device returns status other than "not busy" then we
	have a polling error state. */                
	if(dev_status != DEV_NOT_BUSY) {
		if(dev_status == DEV_WRITE_BUFFER_ABORT) {
			lld_reset_wb_abort(baseaddr);
		} else {
			/* Issue software reset. */
			lld_reset(baseaddr);
		}

		/* indicate to caller that there was an error */
		return dev_status;
	}

	return dev_status;
}


/**
* lld_get_status 
*
* Determines Flash Status for GL-R device
*
*/

static poll_status_t lld_get_status(u32 baseaddr, u32 offset, u8 wbprogram)
{
	u16 dq6_toggles;
	u16 status_read_1;
	u16 status_read_2;
	u16 status_read_3;


	status_read_1 = flash_rd(baseaddr + offset);
	status_read_2 = flash_rd(baseaddr + offset);
	status_read_3 = flash_rd(baseaddr + offset);

	/* Any DQ6 toggles */
	dq6_toggles = ( (status_read_1 ^ status_read_2) &
			(status_read_2 ^ status_read_3) &
	   		DQ6_MASK );

	if (dq6_toggles)
	{			    					
		/**
		 * Checking WriteBuffer Abort condition
		 * Check for all devices that have DQ6 toggling 
		 * also have Write Buffer Abort DQ1 set
		 */
		if (wbprogram && 
			((DQ6_TGL_DQ1_MASK & status_read_1) == DQ6_TGL_DQ1_MASK) )
			return DEV_WRITE_BUFFER_ABORT;

		/* Checking Timeout condition: 
		Check for all devices that have DQ6 toggling also have Time Out DQ5 set. */
		if ((DQ6_TGL_DQ5_MASK & status_read_1) == DQ6_TGL_DQ5_MASK )
			return DEV_EXCEEDED_TIME_LIMITS;	

		/* No timeout, no WB error */
		return DEV_BUSY;
	} else {
		/* no DQ6 toggles on all devices */
		/* Checking Erase Suspend condition */
		status_read_1 = flash_rd(baseaddr + offset);
		status_read_2 = flash_rd(baseaddr + offset);

		/* Checking Erase Suspend condition */
		if (((status_read_1 ^ status_read_2) & DQ2_MASK) == 0)     
			return DEV_NOT_BUSY;         /* All devices DQ2 not toggling */

		if (((status_read_1 ^ status_read_2) & DQ2_MASK) == DQ2_MASK)   
			return DEV_SUSPEND;          /* All devices DQ2 toggling */	
		else
			return DEV_BUSY;             /* Wait for all devices DQ2 toggling */			
	}
}

/**
* lld_reset 
* Writes a Software Reset command to the flash device
*/
void lld_reset(u32 baseaddr)
{
	flash_wr(baseaddr, NOR_RESET_CMD);
}

/** 
* lld_read_CFI
* Read CFI word operation
*/
u16 lld_read_CFI(u32 baseaddr, u32 offset)
{
	u16 cfi_data;
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_CFI_QUERY_CMD);
	cfi_data = flash_rd(baseaddr + offset);
	lld_reset(baseaddr);
	return cfi_data;
}

/**
* lld_erase_sector
* This function only issues the Sector Erase Command sequence.
*/
poll_status_t lld_erase_sector(u32 baseaddr, u32 offset)
{       
	/* Issue Sector Erase Command Sequence */

	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_ERASE_SETUP_CMD);

	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	/* Write Sector Erase Command to Offset */
	flash_wr(baseaddr + offset, NOR_SECTOR_ERASE_CMD);

	return lld_poll_status(baseaddr, offset, LLD_P_POLL_SEC_ERS);
}

/**
* lld_erase_chip
* Writes a Chip Erase Command to Flash Device
*
* This function only issues the Chip Erase Command sequence.
*
*/
poll_status_t lld_erase_chip(u32 baseaddr)
{       
	poll_status_t status;

	/* Issue Chip Erase Command Sequence */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_ERASE_SETUP_CMD);

	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	/* Write Chip Erase Command to Base Address */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_CHIP_ERASE_CMD);

	status = lld_poll_status(baseaddr, 0, LLD_P_POLL_CHIP_ERS);
	/* reset if error */
	if (status != DEV_NOT_BUSY) {
		lld_reset(baseaddr);
	}
	return status;
}

/**
* lld_program_word 
*
* Writes a Program Command to Flash Device
*
* This function only issues the Program Command sequence.
*
*/
poll_status_t lld_program_word(u32 baseaddr, u32 offset, u16 data)
{       
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	/* Write Program Command */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_PROGRAM_CMD);
	/* Write Data */
	flash_wr(baseaddr + offset, data);

	return lld_poll_status(baseaddr, offset, LLD_P_POLL_PGM);
}

/**
* 
* lld_program_writebuffer
*
* Performs a Write Buffer Programming Operation.
*
* Function programs a write-buffer overlay of addresses to data 
* passed via <databuf>.
* Function issues all required commands and polls for completion.
*
* There are 4 main sections to the function:
*  Set-up and write command sequence
*  Determine number of locations to program and load buffer
*  Start operation with "Program Buffer to Flash" command
*  Poll for completion
*/
poll_status_t lld_program_writebuffer(u32 baseaddr, u32 offset, u32 count, u16 *databuf)
{       
	u32 last_loaded_addr;
	u32 current_offset;
	u32 i;
	u32 sector_addr = baseaddr + offset;

	/* Initialize variables */
	current_offset   = offset;
	last_loaded_addr = offset;

	/* Issue unlock command sequence */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);
	/* Write Write Buffer Load Command */
	flash_wr(sector_addr, NOR_WRITE_BUFFER_LOAD_CMD);

	/* Write buffer count */
	flash_wr(sector_addr, count - 1);

	/* Load Data into Buffer */
	for (i = 0; i < count; i++) {
		/* Store last loaded address & data value (for polling) */
		last_loaded_addr = current_offset;
		/* Write Data */
		flash_wr(baseaddr + current_offset, *databuf++);    
		current_offset += 2;
	}

	/* Issue Program Buffer to Flash command */
	flash_wr(sector_addr, NOR_WRITE_BUFFER_PGM_CONFIRM_CMD);

	return lld_poll_status(baseaddr, last_loaded_addr, LLD_P_POLL_WRT_BUF_PGM);
}

/**
* lld_reset_wb_abort
* Writes "Write To Buffer Abort" Reset to Flash
*/
static void lld_reset_wb_abort(u32 baseaddr)
{       
	/* Issue Write Buffer Abort Reset Command Sequence */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);

	/* Write to Buffer Abort Reset Command */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_WRITE_BUFFER_ABORT_RESET_CMD);  
}

/**
 * lld_entry_autoselect
 * Entry autoselect mode
 */
void lld_entry_autoselect(u32 baseaddr)
{ 
	/* Issue Autoselect Command Sequence */
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_UNLOCK_DATA1);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR2, NOR_UNLOCK_DATA2);
	flash_wr(baseaddr + LLD_UNLOCK_ADDR1, NOR_AUTOSELECT_CMD); 
}
