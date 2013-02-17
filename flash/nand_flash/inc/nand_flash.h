/*****************************************************************************
** nand_flash.h
**
** Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.
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

#ifndef __NAND_FLASH_H__
#define __NAND_FLASH_H__

#include "type.h"
#include "stdlib.h"
#include "string.h"
#include "nand_device_info.h"

#define NAND_CMD_READ              (0x00)
#define NAND_CMD_READ1             (0x01)
#define NAND_CMD_READ2             (0x50)
#define NAND_CMD_READ_CONFIRM      (0x30)
#define NAND_CMD_PAGE_PROG         (0x80)
#define NAND_CMD_PAGE_PROG_CONFIRM (0x10)
#define NAND_CMD_ERASE             (0x60)
#define NAND_CMD_ERASE_CONFIRM     (0xD0)
#define NAND_CMD_READID            (0x90)
#define NAND_CMD_RESET             (0xFF)

#define NAND_CMD_READ_STATUS       (0x70)
#define NAND_STATUS_READY          (0x40)
#define NAND_STATUS_NOT_PROTECT    (0x80)
#define NAND_STATUS_PROG_ERROR     (0x01)

/*!
 * nand flash function declarations
 */
/*initialize nand flash */ 
extern s16 nand_init(void);
/*read flash content */
extern s16 nand_read (u32 FlashAddress, u32 TargetAddress, u32 ByteSize,dump_callback callback);
/*write data to flash*/
extern s16 nand_write(u32 FlashAddress, u32 SourceAddress, u32 ByteSize,u8 file_format,response_callback callback);
/* Compare memory content*/
extern s16 nand_compare(u32 FlashAddress, u32 TargetAddress, u32 ByteSize,response_callback callback);
/* Erase content in specific range*/
extern s16 nand_erase_conditional(u32 StartAddress, u32 EndAddress,response_callback callback);
extern void copy_spare(struct nand_device_info *nd,char *pbuf,char *pspare,int len,u8 bfrom);
extern s16 mark_bad_block(struct nand_device_info *nd,u32 nrblk, int recstbbt);
extern u8 is_good_block(struct nand_device_info* nd, u32 nrblk,int allowbbt);
extern int nand_scan_bbt(struct nand_device_info *nd);
extern u8 nand_isbad_bbt(struct nand_device_info *nd, u32 nrblk, int allowbbt);
extern int nand_bbt_markbad(struct nand_device_info *nd, u32 nrblk);
extern s16 nand_get_capacity(u32 *size);


#endif /* __NAND_FLASH_H__ */
