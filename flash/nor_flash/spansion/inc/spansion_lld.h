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
 
 * @brief the spansion nor flash low level driver file
 * @ingroup spansion nor flash
 * @{
 */

#ifndef _SPANSION_LLD_H
#define _SPANSION_LLD_H

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/
/* LLD Command Definition */
#define NOR_AUTOSELECT_CMD               (0x90)
#define NOR_CFI_QUERY_CMD                (0x98)
#define NOR_CHIP_ERASE_CMD               (0x10)
#define NOR_ERASE_SETUP_CMD              (0x80)
#define NOR_PROGRAM_CMD                  (0xA0)
#define NOR_RESET_CMD                    (0xF0)
#define NOR_SECTOR_ERASE_CMD             (0x30)
#define NOR_UNLOCK_BYPASS_ENTRY_CMD      (0x20)
#define NOR_UNLOCK_BYPASS_PROGRAM_CMD    (0xA0)
#define NOR_UNLOCK_BYPASS_RESET_CMD1     (0x90)
#define NOR_UNLOCK_BYPASS_RESET_CMD2     (0x00)
#define NOR_UNLOCK_DATA1                 (0xAA)
#define NOR_UNLOCK_DATA2                 (0x55)
#define NOR_WRITE_BUFFER_ABORT_RESET_CMD (0xF0)
#define NOR_WRITE_BUFFER_LOAD_CMD        (0x25)
#define NOR_WRITE_BUFFER_PGM_CONFIRM_CMD (0x29)

#define LLD_UNLOCK_ADDR1   0x00000AAA
#define LLD_UNLOCK_ADDR2   0x00000554

/* auto select mode */
#define NOR_DEVID_ADDR1 (0x0E << 1)
#define NOR_DEVID_ADDR2 (0x0F << 1)

#define flash_wr(addr, val) *((u16 *)(addr)) = (val)
#define flash_rd(addr) *(u16 *)(addr)

#define DQ1_MASK   (0x02)  /* DQ1 mask for all interleave devices */
#define DQ2_MASK   (0x04)  /* DQ2 mask for all interleave devices */
#define DQ5_MASK   (0x20)  /* DQ5 mask for all interleave devices */
#define DQ6_MASK   (0x40)  /* DQ6 mask for all interleave devices */

#define DQ6_TGL_DQ1_MASK (dq6_toggles >> 5) /* Mask for DQ1 when device DQ6 toggling */
#define DQ6_TGL_DQ5_MASK (dq6_toggles >> 1) /* Mask for DQ5 when device DQ6 toggling */

#define SPANSION_MANUFACTURER_ID	0x01

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/* polling routine options */
typedef enum
{
	LLD_P_POLL_NONE = 0,			/* pull program status */
	LLD_P_POLL_PGM,				    /* pull program status */
	LLD_P_POLL_WRT_BUF_PGM,			/* Poll write buffer   */
	LLD_P_POLL_SEC_ERS,			    /* Poll sector erase   */
	LLD_P_POLL_CHIP_ERS,			/* Poll chip erase     */
	LLD_P_POLL_RESUME,
} poll_type_t;

typedef enum {
	DEV_STATUS_UNKNOWN = 0,
	DEV_NOT_BUSY,
	DEV_BUSY,
	DEV_EXCEEDED_TIME_LIMITS,
	DEV_SUSPEND,
	DEV_WRITE_BUFFER_ABORT,
	DEV_STATUS_GET_PROBLEM,
	DEV_VERIFY_ERROR,
	DEV_BYTES_PER_OP_WRONG,
	DEV_ERASE_ERROR,
	DEV_PROGRAM_ERROR,
	DEV_SECTOR_LOCK
} poll_status_t;

/*****************************************************************************
* global var
*****************************************************************************/


/*****************************************************************************
* function declare
*****************************************************************************/

/* usec delay utility */
extern void udelay(u32 delay);

/* nor reset command */
extern void lld_reset(u32 baseaddr);
/* read CFI */
extern u16 lld_read_CFI(u32 baseaddr, u32 offset);

/* poll the current device status */
extern poll_status_t lld_poll_status(u32 baseaddr, u32 offset, poll_type_t polltype);
/* erase sector */
extern poll_status_t lld_erase_sector(u32 baseaddr, u32 offset);
/* erase the whole chip */
extern poll_status_t lld_erase_chip(u32 baseaddr);
/* program one word */
extern poll_status_t lld_program_word(u32 baseaddr, u32 offset, u16 data);
/* write buffer program */
extern poll_status_t lld_program_writebuffer(u32 baseaddr, u32 offset, u32 count, u16 *databuf);
/* enter autoselect mode */
extern void lld_entry_autoselect(u32 baseaddr);
#endif
