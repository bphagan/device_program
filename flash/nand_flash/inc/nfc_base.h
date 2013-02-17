/*****************************************************************************
** nfc_base.h
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

#ifndef __NFC_BASE_H__
#define __NFC_BASE_H__

#include "type.h"

u8 nand_block_is_good(u32 block);
s16 nand_mark_bad_block(u32 block);
s16 nand_erase_block(u32 block);
s16 nand_read_page(u32 block, u32 page, u32 dest, u32 len,u32 offs);
s16 nand_write_page(u32 block, u32 page, u32 src, u32 len,u8 file_format);
s16 nand_compare_page(u32 block, u32 page, u32 dest, u32 len);
void nfc_memcpy(u32 d, u32 s, u32 len);
void copy_spare(struct nand_device_info *nd, char *pbuf, char *pspare,int len, u8 bfrom);
void nand_bi_main_sp(void);
void nfc_base_init(void);
void nfc_send_read_id(u8* id, int len);
void nfc_set_fms(u8 bus_width, u32 page_size,u16 oob_size);
#endif /* __NFC_BASE_H__ */
