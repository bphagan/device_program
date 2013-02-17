/*****************************************************************************
** nfc_base.c
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
#include "nand_flash.h"
#include "flash_lib.h"
#include "protocol.h"
#include "nfc_base.h"

#if defined(MCU_MX25)
#include "mx25_nfc.h"
#elif defined(MCU_MX51)
#if defined(REV_TO2)
#include "mx51_to2_nfc.h" 
#else
#include "mx51_nfc.h"
#endif
#elif defined(MCU_MX35)
#include "mx35_nfc.h"
#elif defined(MCU_MX37)
#include "mx37_nfc.h"
#elif defined(MCU_MX31) || defined(MCU_MX32)
#include "mx3_nfc.h"
#elif defined(MCU_MX27)
#include "mx27_nfc.h"
#endif

/* extern global nand device 
 * handle,defined in the
 * nand_flash.c file 
 */ 
extern struct nand_device_info* nand;

/* indication for bi swap enable 
 * or not, define in the main.c
 * host will send command to 
 * set this flag  
 */ 
extern BI_SWAP_FLAG flag_bi_swap;

/* number of interleave
 * chips. treat non-interleave
 * as interleave num of 1
 */  
extern u32 num_of_pipline;

/*!
 * Function to do base nfc basic init
 * @param none
 */
void nfc_base_init(void)
{
	nfc_init();
	
	/* FIXME,some nand 
	 * flash need reset 
	 * first,like Micron
	 */
	nfc_command_input(NAND_CMD_RESET);
}

/*!
 * Function to read id
 * @param	[out] tmp 
 */
void nfc_send_read_id(u8* id, int len)
{
	send_read_id(id, len);	
}

/*!
 * Function to set fms
 * @param	[in] bus_width
 * @param	[in] page_size
 * @param	[in] oob_size   
 */
void nfc_set_fms(u8 bus_width, u32 page_size,u16 oob_size)
{
	set_fms(bus_width,page_size,oob_size);
}

/*
 * This function does the trick of swapping the 464th byte in the last RAM
 * buffer in the main area with the 0th byte in the spare area. This seems
 * to be the optimal way of addressing the NFC imcompatibility problem with
 * the NAND flash out of factory in terms of BI field.
 * Note: this function only operates on the NFC's internal RAM buffers and
 * for 2K page only.
 */

void nand_bi_main_sp(void)
{
	u16 tmp1, tmp2, new_tmp1;
	tmp1 = BAD_BLK_MARKER_MAIN;
	tmp2 = BAD_BLK_MARKER_SP_0;

	new_tmp1 = (tmp1 & 0xFF00) | (tmp2 >> 8);
	tmp2 = (tmp1 << 8) | (tmp2 & 0xFF);
	BAD_BLK_MARKER_MAIN = new_tmp1;
	BAD_BLK_MARKER_SP_0 = tmp2;
}

/*!
 * Function to copy memory content
 * Parser the command, and then call the corresponding functions.
 * @param	[in] SourceAddress  - source address
 * @param	[in] TargetAddress -Destination address
 * @param	[in] ByteSize	-byte size
 */
void nfc_memcpy(u32 d, u32 s, u32 len)
{
	u32 i;
	for(i = 0; i < len; i += 2)
		*(volatile u16 *)(d + i) = *(volatile u16 *)(s + i);
}

/*!
 * Function to copy spare content
 * @param	[in] nd - nand structure
 * @param	[in] pbuf  - data buf address
 * @param	[in] pspare - spare buf address
 * @param	[in] len - byte size
 * @param	[in] bfrom - direction
 */
void copy_spare(struct nand_device_info *nd, char *pbuf, char *pspare,int len, u8 bfrom)
{
	u16 i, j;
	u16 m = nd->oob_size;
	u16 n = nd->page_size >> 9;
	u8 *d = (u8 *) pbuf;
	u8 *s = (u8 *) pspare;
	u16 t = NFC_SAB_LEN;


	m /= num_of_pipline;
	n /= num_of_pipline;
	len /= num_of_pipline;

	j = (m / n >> 1) << 1;

	if(!s)
		s = (u8 *)NFC_SAB0_BASE;

	if (bfrom) {
		for (i = 0; i < n - 1; i++)
			nfc_memcpy((u32)&d[i * j], (u32)&s[i * t], j);

		/* the last section */
		nfc_memcpy((u32)&d[i * j], (u32)&s[i * t], len - i * j);
	} else {
		for (i = 0; i < n - 1; i++)
			nfc_memcpy((u32)&s[i * t], (u32)&d[i * j], j);

		/* the last section */
		nfc_memcpy((u32)&s[i * t], (u32)&d[i * j], len - i * j);
	}
}

/*!
 * Function to check whether nand block is good
 * @param	[in] BlockNum - block number
 */
u8 nand_block_is_good(u32 block)
{
	u16 flag;
	u8 i = 0, j = 0;
	u32 p_size = nand->page_size / num_of_pipline;
	u8 col_addr_cycle = p_size > 512 ? 2 : 1;
	u32 page_addr = block * nand->ppb;	
	u8 ncs = block / nand->blk_count;
	
	/* get the offset page */
	page_addr += nand->bbi_page_offset;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	
	for(i = 0; i < nand->scan_pg_num; i++){
	
		for(j = 0; j < num_of_pipline; j++) {
			
			/* send read command */
			nfc_command_input(NAND_CMD_READ);
	
			/* address cycle, row & col */
			nfc_address_cycle(0, col_addr_cycle);
			nfc_address_cycle(page_addr + j + i, 
					  nand->row_addr_cycle);
	
			/* send page read command for large page */
			if (p_size > 512)
				nfc_command_input(NAND_CMD_READ_CONFIRM);
	
			/* trans data from nand flash to nfc buffer */
			send_read_page();
	
			/* check ecc status */
			if(nfc_ecc_uncorrectable_error(p_size))
	    			return 0;
	
			/* bi swap */
			if((flag_bi_swap == BI_SWAP_ENABLE) &&
			   	(p_size > 512)) {
				nand_bi_main_sp();
				flag = BAD_BLK_MARKER_SP_0;
			} else {
				flag = *(volatile u16 *)(NFC_SAB0_BASE + 4);
			}

			/* check bad or not */
			if ((flag & 0xFF00) != 0xFF00) {
				return 0;
			}
		}
	}
	
	return 1;
}

/*!
 * Function to  mark bad block
 * @param	[in] BlockNum - block number
 */
s16 nand_mark_bad_block(u32 block)
{
	u8 i = 0, j = 0, k;
	u32 p_size = nand->page_size / num_of_pipline;
	u8 col_addr_cycle = p_size > 512 ? 2 : 1;
	u32 page_addr = block * nand->ppb;
	u8 ncs = block / nand->blk_count;
	
	/* get the offset page */
	page_addr += nand->bbi_page_offset;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	

	/* filled the memory with zero */
	for(; j < NFC_SAB_COUNT; j++) {
	    for(k = 0; k < NFC_SAB_LEN; k += 2) {
		    *(volatile u16 *)(NFC_SAB0_BASE + k + j * NFC_SAB_LEN) = 0;
	    }
    	}
	    	
	for(; i < num_of_pipline; i++) {	

		/* bi swap*/
		if((flag_bi_swap == BI_SWAP_ENABLE) &&
			(p_size > 512))
			nand_bi_main_sp();
	
		/* send prog initial command */
		nfc_command_input(NAND_CMD_PAGE_PROG);
	
		/* address cycle */
		nfc_address_cycle(0, col_addr_cycle);
	
		nfc_address_cycle(page_addr++, nand->row_addr_cycle);
	
		/* trans data from nfc to nand flash */
		send_prog_page();
	
		/* send prog confirm command */
		nfc_command_input(NAND_CMD_PAGE_PROG_CONFIRM);
	
		/* wait prog completely*/
		while (!(nand_read_status() & NAND_STATUS_READY));
	
		/* check prog status */
		if (nand_read_status() & NAND_STATUS_PROG_ERROR)
	    		return FLASH_ERROR_PROG;
	}
	
	return FLASH_ERROR_NO;
}

/*!
 * Function to  erase nand block
 * @param	[in] BlockNum	- block number
 */
s16 nand_erase_block(u32 block)
{
	u8 i = 0;
	u32 page_addr = block * nand->ppb;
	u8 ncs = block / nand->blk_count;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	

	for(; i < num_of_pipline; i++) {	
	
		/* send erase command */
		nfc_command_input(NAND_CMD_ERASE);
	
		/* addr cycle only row addr */
		nfc_address_cycle(page_addr++, nand->row_addr_cycle);
	
		/* send erase confirm command */
		nfc_command_input(NAND_CMD_ERASE_CONFIRM);
	
		/* check the status */
		if( nand_read_status() & NAND_STATUS_PROG_ERROR )
			return FLASH_ERROR_ERASE;
	}
	return FLASH_ERROR_NO;
}

/*!
 * Function to  read one page
 * @param	[in] BlockNum	- block number
 * @param	[in] PageNum - page number
 * @param	[in] TargetAddress	- destination address
 * @param	[in] ByteSize	- byte size to be read
 */
s16 nand_read_page(u32 block, u32 page, u32 dest, u32 len,u32 offs)
{
	u8 i = 0;
	u32 r_size = 0;
	u32 p_size = nand->page_size / num_of_pipline;
	u8 col_addr_cycle = p_size > 512 ? 2 : 1;
	u32 page_addr = block * nand->ppb + page;
	u8 ncs = block / nand->blk_count;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	
	for(; i < num_of_pipline && len; i++) {	
		
		/* send read command */
		nfc_command_input(NAND_CMD_READ);
	
		/* addr cycle: row & col */
		nfc_address_cycle(0, col_addr_cycle);
		nfc_address_cycle(page_addr++, nand->row_addr_cycle);
	
		/* send read confirm command for large page */
		if (p_size > 512)
		nfc_command_input(NAND_CMD_READ_CONFIRM);
	
		/* trans data from nand to nfc buffer*/
		send_read_page();
		
		/* check ecc status */
		if(nfc_ecc_uncorrectable_error(p_size))
			return FLASH_ERROR_ECC;
	
		/* bi swap */
		if((flag_bi_swap == BI_SWAP_ENABLE) &&
			(p_size > 512))
			nand_bi_main_sp();

		r_size = min(len, p_size);
				
		/* trans data from nfc buffer to data buffer*/
		nfc_memcpy(dest,NFC_MAB0_BASE + offs, r_size);
		
		/* update */
		len -= r_size;
		dest += r_size;
	}
	
	return FLASH_ERROR_NO;
}

 /*!
 * Function to  write one page
 * @param	[in] BlockNum	- block number
 * @param	[in] PageNum page number
 * @param	[in] SourceAddress	-source address
 * @param	[in]ByteSize	-byte size to be written
 */
s16 nand_write_page(u32 block, u32 page, u32 src, u32 len,u8 file_format)
{
	u32 i = 0;
	u32 w_size = 0;
	u32 p_size = nand->page_size / num_of_pipline;
	u8 col_addr_cycle = p_size > 512 ? 2 : 1;;
	u32 page_addr = block * nand->ppb + page;
	u8 ncs = block / nand->blk_count;
	int need_write = 0;
	
	/* check for linux ubifs support */		
	if (file_format == FILE_FORMAT_NORMAL) {
        	for (; i < len; i += 4) {
                	if (*(u32 *)(src +  i) != 0xFFFFFFFF) {
                        	need_write = 1;
                        	break;
                	}
        	}
        } else {
        	need_write =  1;
	}
	
	if (!need_write)
		return FLASH_ERROR_NO;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	
	for(i = 0; i < num_of_pipline && len; i++) {
		
		/* set nfc spare data */
	    	set_nfc_spare(file_format);
	
		/* get the min value */
		w_size = min(len, p_size);
		
		/* zero buffer in case len < page size */
		if( w_size < p_size) 
			memset((void *)NFC_MAB0_BASE,0xff,p_size);
			
	    	/* copy the data */
		nfc_memcpy(NFC_MAB0_BASE, src, w_size);
	
		/* bi swap */
		if((flag_bi_swap == BI_SWAP_ENABLE) &&
			(p_size > 512))
			nand_bi_main_sp();
	
		/* send prog inital command */
		nfc_command_input(NAND_CMD_PAGE_PROG);
	
		/* addr cycle: row & col */
		nfc_address_cycle(0, col_addr_cycle);
		nfc_address_cycle(page_addr++, nand->row_addr_cycle);
	
		/* trans data from nfc to nand flash*/
		send_prog_page();
	
		/* send prog confirm command */
		nfc_command_input(NAND_CMD_PAGE_PROG_CONFIRM);
	
		/* wait prog completely*/
		nand_wait();
	
		/* check prog status */
		if(nand_read_status() & NAND_STATUS_PROG_ERROR)
			return FLASH_ERROR_PROG;
	
		/* update */
		len -= w_size;
		src += w_size;
	}
	
	return FLASH_ERROR_NO;
}

 /*!
 * Function to  compare one page
 * @param	[in] BlockNum	- block number
 * @param	[in] PageNum - page number
 * @param	[in] TargetAddress	-destination address
 * @param	[in]	ByteSize	- byte size to be compared
 */
s16 nand_compare_page(u32 block, u32 page, u32 dest, u32 len)
{
	u32 i = 0;
	u32 r_size = 0;
	u32 p_size = nand->page_size / num_of_pipline;
	u8 col_addr_cycle = p_size > 512 ? 2 : 1;
	u32 page_addr = block * nand->ppb + page;
	u8 ncs = block / nand->blk_count;
	
	/* FIXME, treat the non-interleave as
	 * interleave one chip. Since we use 
	 * ADD_OP mode 1, so need ajust the
	 * addr value 
	 */
	if(num_of_pipline > 1) {
		page_addr *= num_of_pipline;
	} else { 
		page_addr *= nand->num_chips;
		page_addr += ncs;
	}
	
	for(; i < num_of_pipline && len; i++) {

		/* send page read command */
		nfc_command_input(NAND_CMD_READ);
	
		/* address cycle, row & col */
		nfc_address_cycle(0, col_addr_cycle);
		nfc_address_cycle(page_addr++, nand->row_addr_cycle);
	
		/* send page read confirm command for large page */
		if (p_size > 512)
			nfc_command_input(NAND_CMD_READ_CONFIRM);
	
		/* trans data from nand flash to nfc buffer */
		send_read_page();
	
		/* check ecc status */
		if(nfc_ecc_uncorrectable_error(p_size))
			return FLASH_ERROR_ECC;
	
		/* bi swap */
		if((flag_bi_swap == BI_SWAP_ENABLE) && (p_size > 512))
			nand_bi_main_sp();
	
		r_size = min(len, p_size);
		
		/* compare data */
		for(i = 0; i < r_size; i += 2) {
			if((*(volatile u16 *)(NFC_MAB0_BASE+i)) != 
			   (*(volatile u16 *)(dest + i))) {
	      			return FLASH_ERROR_VERIFY;
	  		}
		}
		
		/* update */
		len -= r_size;
		dest += r_size;		
	}

	return FLASH_ERROR_NO;
}
