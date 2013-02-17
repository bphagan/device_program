/*****************************************************************************
** nand_flash.c
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
#include "protocol.h"
#include "flash_lib.h"
#include "nfc_base.h"
#include "nand_device_info.h"

/* global nand device 
 * handle
 */ 
struct nand_device_info* nand = NULL;

/* indication for bbt enable 
 * or not, define in the main.c
 * host will send command to 
 * set this flag  
 */ 
extern FL_BBT_FLAG flag_fl_bbt;

/* indication for the follow
 * up operation or not.defined
 * in the main.c file.  
 * host will send command to 
 * set this flag  
 */ 
extern u8 go_on;

/* store the number of bad  
 * block met during operaton.
 * will use this value to adjust
 * the following up opeartion(read/prg) 
 * start end addr  
 */ 
static u32 bb_skip;

/* store the number of bad  
 * block met during operaton.
 * will use this value to adjust
 * the following up opeartion(compare) 
 * start end addr  
 */ 
static u32 cmp_block;

/* indication for interleave  
 * or not, define in the main.c
 * host will send command to 
 * set this flag  
 */ 
extern FL_INTLV_FLAG flag_fl_intlv;

/* number of interleave chips, 
 * treat the none-interleave 
 * mode as interleave only 1
 * chips.So,for none interleave
 * the number will be 1   
 */
u32 num_of_pipline = 1;

/* indication for using logic
 * block address(LBA) or not.
 * Currently wince bsp use the
 * LBA mode, while linux not
 * due to the kernel(MTD) out
 * of our control
 */
 
 extern u8 flag_lba; 
 
 
static s16 __get_good_block(u32 *start_phb)
{
	u32 block_count = nand->blk_count * nand->num_chips;

	/* search until good block */
	while(!is_good_block(nand, *start_phb, 0) && *start_phb < block_count) 
		(*start_phb)++;

	if (*start_phb >= block_count)
		return FLASH_ERROR_EOF;
	
	return FLASH_ERROR_NO;
}


static s16 __get_phy_block(u32 lgc_blk, u32 *phy_blk)
{
	u32 i = 0;
	u32 blk = 0;
	s16 ret = FLASH_ERROR_NO;
	
	for (; i < lgc_blk + 1; i++, blk++) {
		ret = __get_good_block(&blk);
		if (ret != FLASH_ERROR_NO)
			return ret;
	}
	
	*phy_blk = --blk;
		
	return ret;
}

/*!
 * Function to erase all blocks
 * @param	[in] addr - address
 * @param	[in] size - size
 */

s32 __check_param(u32 addr, u32 size)
{
	u32 page_size = nand->page_size;
	u32 ppb = nand->ppb;
	u32 blk_size = page_size * ppb;
	u32 blk_count = nand->blk_count * nand->num_chips;

	if ((addr / blk_size) > blk_count || 
				size == 0 || 
		((addr + size) / blk_size) > blk_count)
		   
			return FLASH_ERROR_OVER_ADDR;
		
	return FLASH_ERROR_NO;
}
 /*!
 * Function to erase all blocks
 * @param	[out] addr - address
 */
static void __adjust_addr(u32 *block)
{
	if (!flag_lba) {
		/*reset the bb_skip */
		if(go_on == 0) 
			bb_skip = 0;
		
		/* FIXME recount the start block 
		*  May meet bad block during last 
		*  programing, should ajust the
		*  following up programing start addr	
		*/	
		*block += bb_skip;
	} else {
		/* logic to physical block */
		__get_phy_block(*block, block);		
	}	
}

/*!
 * Function to read nand flash id
 * @param	[out] man_id - manufacture id
 * @param	[out] dev_id - device id
 */
void nand_read_id(u8 *id, int len)
{
	nfc_send_read_id(id, NAND_DEVICE_ID_BYTE_COUNT);
}

/*!
 * Function to get the flash capacity
 * @param	[out] size - flash size
 */
s16 nand_get_capacity(u32 *size)
{
	u32 ndsize = nand->page_size * 
		     nand->ppb * 
		     nand->num_chips *
		     (nand->blk_count >> 10);
		     
	/* the capacity is size*1024 Bytes */
	if (size && nand)
	{
                *size = ndsize >= 0xFFFFFFFF ? 0xFFFFFFFF : ndsize;
                return FLASH_ERROR_NO;
   	}
   	else
   	{ 
                return FLASH_FAILED;
        }
}

extern void atk_response_send(u16 ack, u16 csum, u32 len);
 
 /*!
 * Function to initialize nand
 * @param	none 
 */
s16 nand_init(void)
{
 	u8 id[NAND_DEVICE_ID_BYTE_COUNT];
	u64 page_count;
	struct nand_device_info  *dev_info;
 	u32 i;
	
  	/* get flash id */
  	if(!nand) {
		nfc_base_init();
   		nand_read_id((u8*)id, sizeof(id));
		dev_info = nand_device_get_info(id);
		if (!dev_info)
			return FLASH_ERROR_INIT;
			
		nand = dev_info;
		/* preset the value */
		num_of_pipline = 1;
		nand->num_chips = 1;
		
		page_count = nand->chip_size_in_bytes / nand->page_size;
		nand->blk_count = page_count / nand->ppb;
		if (page_count <= (u64)(1 << 8))
			nand->row_addr_cycle = 1;
		else if (page_count <= (u64)(1 << 16))
			nand->row_addr_cycle = 2;
		else if (page_count <= (u64)(1 << 24))
			nand->row_addr_cycle = 3;
		else if (page_count <= (u64)(1ULL << 32))
			nand->row_addr_cycle = 4;
		else if (page_count <= (u64)(1ULL << 40))
			nand->row_addr_cycle = 5;
		
		nfc_set_fms(nand->bus_width, 
			    nand->page_size, 
			    nand->oob_size);
   	}
   	
   	if(nand) {
   		/* check interleave mode */
	   	if(flag_fl_intlv == FL_INTLV_ENABLE &&  
		   nand->num_chips > 1) {
		   		
			num_of_pipline = nand->num_chips;
			nand->page_size *= num_of_pipline;
			nand->oob_size *= num_of_pipline;
			nand->num_chips = 1;
			
			if(nand->bbt) {
				free(nand->bbt);
				nand->bbt = NULL;
			}
		
		} else if (flag_fl_intlv == FL_INTLV_DISABLE &&
		           num_of_pipline > 1) {
			
			nand->page_size /= num_of_pipline;
			nand->oob_size /= num_of_pipline;
			nand->num_chips = num_of_pipline;
			num_of_pipline = 1;
			
			if(nand->bbt) {
				free(nand->bbt);
				nand->bbt = NULL;
			}
		}
		
		/* check bbt mode */	
		if(flag_fl_bbt != FL_BBT_ENABLE) {
			return FLASH_ERROR_NO;
		} else {
			if(nand->bbt) {
				return FLASH_ERROR_NO;
			} else {
				/* use phy address to scan */
				flag_lba = 0;
				
			
			if(flag_fl_intlv != FL_INTLV_ENABLE) {
			#if defined(MCU_MX51)
				u32 temp = 0;
				/*force the chips to 1 to sync with redboot*/
				nand->num_chips = 1;
				/* set num_of_device to decode the cs */
				temp = *(u32*)0x83fdb028;
				temp &= ~(7 << 12);
				*(u32*)0x83fdb028 = temp;
			#endif					
			}
				/* FIXME, currently, Linux can only support
				 * lower than 4G space.
				 */
				 nand_get_capacity(&i);
				 if (i >= (1 << 22))
				 	nand->blk_count /= i >> 21;

				nand->bbt = malloc((nand->blk_count *
						    nand->num_chips) >> 2);
				if (nand->bbt) {
					memset(nand->bbt,0,
					      (nand->blk_count *
					       nand->num_chips) >> 2);
					if (nand_scan_bbt(nand) == 0 ) {
						return FLASH_ERROR_NO;
					}
				}
			}	
		} 		
	}
	
	return FLASH_ERROR_INIT;	
}

//u32 atk_channel_send(const u8 *buf, u32 count);
 /*!
 * Function to read data from nand flash 
 * @param	[in] src - nand flash address
 * @param	[in] dest - destination address
 * @param	[in] len - byte size to be read
 * @param   	[in] callback - call back function to send data & progress
 */
s16 nand_read(u32 src, u32 dest, u32 len,dump_callback callback)
{

	s16 ret;
	u16 csum;
	u32 page_size = nand->page_size;
	u32 ppb = nand->ppb;
	u32 blk_count = nand->blk_count * nand->num_chips;
	u32 blk_size = page_size * ppb;
	u32 block = src / blk_size;
	u32 page  = (src % blk_size) / page_size;
	u32 offset = src % page_size;
	u32 readlen = 0;
	
	/* FIXME,adjust the start
	 * block address due to 
	 * the bad block meet in 
	 * pre-read phase	 	 
	 */
	__adjust_addr(&block);
	
	/* param check */
	ret = __check_param(block *blk_size,len);
	if (0 != ret)
		return ret;
		
	do {
     		if (page >= ppb) {
       			block++;
       			page = 0;
     		}
     		/* check bad block first*/
		if ( page == 0) {
			if(!is_good_block(nand,block,0)){
				block++;
				bb_skip++;
         			continue;
       			}
     		} 
     		/* check the offset */
		if(offset == 0)
			readlen = min(len, page_size);
		else
		 	readlen = ((len + offset) > page_size) ? page_size - offset : len;
		 	
		/* read the page */
		ret = nand_read_page(block, page, dest, readlen, offset);
		
		if (FLASH_ERROR_NO != ret)
			return ret;
			
		/* send the dump status and data to host */
		if (callback != NULL) {
			csum = calculate_checksum((u8 *)dest, readlen);
			callback((u8 *)dest, FLASH_PARTLY, csum, readlen);
		}
		
		/* update the value */
		len -= readlen;
		dest += readlen;
		page++;
		offset = 0;
	} while (len && block < blk_count);
   
	/* check the blknum */
	if(block >= blk_count )
		ret = FLASH_ERROR_EOF;
		
	return ret;
}

 /*!
 * Function to Write data to nand flash
 * @param	[in] dest - nand flash address
 * @param	[in] src - data buffer address
 * @param	[in] len - byte to be written
 * @param   	[in] callback the call back function to notify the progress
 */
s16 nand_write(u32 dest, u32 src, u32 len, u8 file_format, response_callback callback)
{
	s16 ret;
	u32 page_size = nand->page_size;
	u32 ppb = nand->ppb;
	u32 blk_count = nand->blk_count * nand->num_chips;
	u32 blk_size = page_size * ppb;
	u32 block = dest/blk_size;
	u32 page  = 0;
	u32 writelen = 0;
	
	/* FIXME,adjust the start
	 * block address due to 
	 * the bad block meet in 
	 * pre-prog phase	 	 
	 */
	__adjust_addr(&block);
	cmp_block = block;
		
	/* param check */
	ret = __check_param(block * blk_size ,len);
	if (0 != ret)
		return ret;

	do {
	
		if (page >= ppb) {
			block++;
			page = 0;
		}
		
		if (0 == page) {
			/* check bad block first*/
    			if(!is_good_block(nand, block,0)) {
         			block++;
         			bb_skip++;
         			continue;
       			}
       			/* erase the block */
			if (nand_erase_block(block) != FLASH_ERROR_NO) {
           			mark_bad_block(nand, block, 0);
           			block++;
           			bb_skip++;
           			continue;
        		}
		}
		
		/* write the page */
		writelen = min(len, page_size);
		ret = nand_write_page(block, page, src, writelen,file_format);
		
     		/* if PROG error */
		if (FLASH_ERROR_NO != ret) 
			return ret;
		
		/* send the prg status to host */
		if(callback != NULL)
			callback(FLASH_PARTLY, block, writelen);
		
		/* update the value */
		len -= writelen;
		src += writelen;
		page++;
	} while (len && block < blk_count);
	
	/* check the blknum */
	if(block >= blk_count )
		ret = FLASH_ERROR_EOF;
		
	return ret;
}

 /*!
 * Function to compare the content between source and dest
 * @param	[in] src - nand flash address
 * @param	[in] dest - target address
 * @param	[in] len - length to be compared
 * @param   	[in] callback - the call back function to notify the progress
 */
s16 nand_compare(u32 src, u32 dest, u32 len,response_callback callback)
{

	u32 page_size = nand->page_size;
	u32 ppb = nand->ppb;
	u32 blk_count = nand->blk_count * nand->num_chips;
	u32 blk_size = page_size * ppb;
	u32 block = src/blk_size;
	u32 page  = 0;
	u32 readlen;
	s16 ret;
	
	/* FIXME,adjust the start
	 * block address of compare
	 * to the most recently prog
	 * start block	 	 	 
	 */
	block = cmp_block;
		
	do {
		if (page >= ppb) {
       			block++;
       			page = 0;
     		}
		if (page == 0) {
			if(!is_good_block(nand, block, 0)) {
				block++;
         			continue;
       			}
		}
		/* set the read size */
		readlen = min(len, page_size);

		/* compare the page */
		ret = nand_compare_page(block, page, dest, readlen);
		
		if (FLASH_ERROR_NO != ret)
			return ret;

		/* send the verify status to host */
		if(callback != NULL)
			callback(FLASH_VERIFY, block, readlen);

		/* update the value */
     		len -= readlen;
     		dest += readlen;
     		page++;
   	} while (len && block < blk_count);
   	
	/* check the blknum */
	if(block >= blk_count )
		ret = FLASH_ERROR_EOF;
		
   	return ret;
}

 /*!
 * Function to erase flash content between start address and endadress
 * @param 	[in] start - start address to be erased
 * @param	[in] end - end address to be erased
 */
s16 nand_erase_conditional(u32 start, u32 end,response_callback callback)
{

	s16 ret;
	u32 i,j,k;
	u32 page_size = nand->page_size;
	u32 ppb = nand->ppb;
	u32 blk_count = nand->blk_count * nand->num_chips;
	u32 blk_size = page_size * ppb;
		
	ret = __check_param(start, end - start);
	if (0 != ret)
		return ret;

	i = start / blk_size;
	k = (end - 1) / blk_size;
	
	for (j = 0; i <= k; i++) {
       		ret = nand_erase_block(i);
       		if (FLASH_ERROR_NO != ret) {
       			mark_bad_block(nand, i, k >= blk_count - 4 ? 1 : 0);
       			j++;
       		} else {
       			if (callback)
         			callback(FLASH_ERASE, i, blk_size);
       		}
   	}
	/*FIX ME ,This is for the Linux bbt upate*/
	if ((k >= blk_count -4) && (nand->bbt)) {
		free(nand->bbt);
		nand->bbt = NULL;
		nand_init();
	}
	
   	/*partial erease*/
   	if (j > 0)
   		return FLASH_ERROR_PART_ERASE;

   	return ret;
}

 /*!
 * Function to check bad block
 * @param 	[in] nd - nand structure
 * @param	[in] nrblk - number of blocks
 * @param	[in] allowbbt - allow write bbt or not
 */
u8 is_good_block(struct nand_device_info* nd, u32 nrblk,int allowbbt)
{
	if(flag_fl_bbt == FL_BBT_ENABLE) {
		return (!nand_isbad_bbt(nd,nrblk,allowbbt));
	} else {
		return (nand_block_is_good(nrblk));
	}
	
}

 /*!
 * Function to mark bad block
 * @param 	[in] nd - nand structure
 * @param	[in] nrblk - number of blocks
 * @param	[in] recstbbt - reconstruct bbt or not
 */
s16 mark_bad_block(struct nand_device_info *nd, u32 nrblk, int recstbbt)
{	
	if (flag_fl_bbt == FL_BBT_ENABLE && !recstbbt) {
		return (nand_bbt_markbad(nd,nrblk));
	} else {
		return (nand_mark_bad_block(nrblk));
	}
}
