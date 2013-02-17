/*****************************************************************************
** mx37_nfc.h
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

#ifndef __MX37_NFC_H__
#define __MX37_NFC_H__

#include "type.h"
#include "flash_lib.h"

#define CCM_BASE_ADDR  		(0xE3F8C000)
#define CCM_CBCDR7          (CCM_BASE_ADDR+0x2C)
#define CCM_CCDR            (CCM_BASE_ADDR+0x4)

#define NFC_BASE_ADDR	    (0x7FFF0000)
#define NFC_IP_BASE			(0xE3FDB000)

#define NFC_MAB0_BASE       (NFC_BASE_ADDR+0x000)
#define NFC_MAB1_BASE       (NFC_BASE_ADDR+0x200)
#define NFC_MAB2_BASE       (NFC_BASE_ADDR+0x400)
#define NFC_MAB3_BASE       (NFC_BASE_ADDR+0x600)
#define NFC_MAB4_BASE       (NFC_BASE_ADDR+0x800)
#define NFC_MAB5_BASE       (NFC_BASE_ADDR+0xA00)
#define NFC_MAB6_BASE       (NFC_BASE_ADDR+0xC00)
#define NFC_MAB7_BASE       (NFC_BASE_ADDR+0xE00)

#define NFC_SAB0_BASE       (NFC_BASE_ADDR+0x1000)
#define NFC_SAB1_BASE       (NFC_BASE_ADDR+0x1040)
#define NFC_SAB2_BASE       (NFC_BASE_ADDR+0x1080)
#define NFC_SAB3_BASE       (NFC_BASE_ADDR+0x10C0)
#define NFC_SAB4_BASE       (NFC_BASE_ADDR+0x1100)
#define NFC_SAB5_BASE       (NFC_BASE_ADDR+0x1140)
#define NFC_SAB6_BASE       (NFC_BASE_ADDR+0x1180)
#define NFC_SAB7_BASE       (NFC_BASE_ADDR+0x11C0)
#define NFC_SAB_LEN         (64)
#define NFC_SAB_COUNT       (8)

#define NFC_REG_BASE            (NFC_BASE_ADDR+0x1E00)
#define NFC_FLASH_ADDR_CMD      (NFC_REG_BASE+0x00)
#define NFC_NF_CONFIG1          (NFC_REG_BASE+0x04)
#define NFC_ECC_STAT_RSLT       (NFC_REG_BASE+0x08)
#define NFC_LAUNCH_NFC          (NFC_REG_BASE+0x0C)

#define NFC_NF_WR_PROT    (NFC_IP_BASE+0x00)
#define NFC_ULOCK_BLK0    (NFC_IP_BASE+0x04)
#define NFC_ULOCK_BLK1    (NFC_IP_BASE+0x08)
#define NFC_ULOCK_BLK2    (NFC_IP_BASE+0x0C)
#define NFC_ULOCK_BLK3    (NFC_IP_BASE+0x10)
#define NFC_NF_CONFIG2    (NFC_IP_BASE+0x14)
#define NFC_IPC			  (NFC_IP_BASE+0x18)
#define NFC_AXI_ERR_ADD	  (NFC_IP_BASE+0x1c)

/* FMS & bus width */
#define NF_FMS_2KB                 (0x00000100)
#define NF_4KB					   (0x00000200)
#define NF_16BIT                   (0x00004000)
#define NFC_OPS_STAT			   (1 << 31)
#define NFC_IPC_CREQ			   (1 << 0)
#define NFC_IPC_ACK				   (1<<1)
#define NFC_ECC_MODE_4    		   (1<<6)
#define NFC_ECC_MODE_8			   ~(1<<6)
#define RBA_RESET			  	   ~(7 << 4)
#define SPAS_MASK			      (0xFF00FFFF)
#define RBA_BUFFER0			      (0 << 4)
#define RBA_BUFFER0			      (0 << 4)
#define RBA_BUFFER1			      (1 << 4)
#define RBA_BUFFER2			      (2 << 4)
#define RBA_BUFFER3			      (3 << 4)

#define IS_4BIT_ECC			\
	((raw_read(NFC_NF_CONFIG2) & NFC_ECC_MODE_4)>>6)

#define WRITE_NFC_IP_REG(val,reg) \
	do {	 \
		raw_write(NFC_IPC_CREQ, NFC_IPC); \
		while(!((*(volatile u32*)NFC_IPC & NFC_IPC_ACK)>>1));\
		raw_write(val, reg);\
		raw_write(0, NFC_IPC);\
	}while(0)

#define NFC_SET_RBA(val, buf_id)       \
	val = ((raw_read(NFC_NF_CONFIG1) & RBA_RESET) | buf_id);

#define SET_SPAS(v)			\
	raw_write(((raw_read(NFC_NF_CONFIG2) & SPAS_MASK) | ((v)<<16)),NFC_NF_CONFIG2)

#define NFC_SEL_RAM_BUFFER(val) \
	raw_write(((raw_read(NFC_NF_CONFIG1) & RBA_RESET) | val), NFC_NF_CONFIG1);

#define SPAS_64     (32) /* half word */
#define SPAS_128    (64) /* half word */

/*marco to detect the busy status*/
#define NFC_BUSY  (!( *(volatile u32 *)NFC_IPC & 0x80000000 ))

/*marco to define the raw_read/write*/
#define raw_read(addr) *(u32 *)((addr))
#define raw_write(val,addr) *((u32 *)(addr)) = (val)

/* main area for bad block marker*/
#define BAD_BLK_MARKER_OFFS      \
	(NAND_MAIN_BYTESIZE - (((((NAND_SPARE_BYTESIZE /(NAND_MAIN_BYTESIZE >> 9)) >> 1)) << 1) * \
	((NAND_MAIN_BYTESIZE >> 9) -1 )))
#define BAD_BLK_MARKER_MAIN 	(*((volatile u16 *)(NFC_MAB0_BASE + BAD_BLK_MARKER_OFFS)))
/* spare area for swapped main area data */
#define BAD_BLK_MARKER_SP_OFFS     \
	(((NAND_MAIN_BYTESIZE >> 9) - 1) * NFC_SAB_LEN)
#define BAD_BLK_MARKER_SP_0     (*((volatile u16 *)(NFC_SAB0_BASE + BAD_BLK_MARKER_SP_OFFS)))

#define NAND_MAIN_BYTESIZE          (nand->page_size / num_of_pipline)
#define NAND_SPARE_BYTESIZE         (nand->oob_size / num_of_pipline)
extern u32 num_of_pipline;
extern struct nand_device_info* nand;

/*!
 * Function to wait for basic NFC operation completion
 */
static u8 nfc_wait(void)
{
	while (1) {
		if (raw_read(NFC_IPC) & NFC_OPS_STAT) {
			WRITE_NFC_IP_REG((raw_read(NFC_IPC) & ~NFC_OPS_STAT), NFC_IPC);
			break;
		}

	}
	return 0;
}

/*!
 * Function to input address
 */
static void nfc_address_input(u32 address)
{
	*(volatile u32 *)NFC_FLASH_ADDR_CMD = address<<16;
	*(volatile u32 *)NFC_LAUNCH_NFC = 0x0002;
	nfc_wait();
}

/*!
 * Function to write flash address cycle
 */
static void nfc_address_cycle(u32 Address, u8 NumOfCycle)
{
	u8 i;

	for(i=0; i<NumOfCycle; i++)
		nfc_address_input( (u16)( (Address>>(i*8))&0xFF ) );
}

/*!
 * Function to input command
 */
static void nfc_command_input(u16 command)
{
	*(volatile u32 *)NFC_FLASH_ADDR_CMD  = command;
	*(volatile u32 *)NFC_LAUNCH_NFC      = 0x0001;
	nfc_wait();
}

/*!
 * Function to input data
 */
static void nfc_flash_data_input(void)
{
	*(volatile u32 *)NFC_LAUNCH_NFC = 0x0004;
	nfc_wait();
}

/*!
 * Function to output data
 */
static void nfc_flash_data_output(void)
{
	*(volatile u32 *)NFC_LAUNCH_NFC = 0x0008;
	nfc_wait();
}

/*!
 * Function to send command to read page
 */
void send_read_page(void)
{
	NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
	nfc_flash_data_output();
}

/*!
 * Function to send command to write page
 */
void send_prog_page(void)
{
	NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
	nfc_flash_data_input();
}

/*!
 * Function to read status from nand flash register
 */
u8 nand_read_status(void)
{
	NFC_SEL_RAM_BUFFER(RBA_BUFFER0);

	nfc_command_input(NAND_CMD_READ_STATUS);
	/* Read Status */
	*(volatile u32 *)NFC_LAUNCH_NFC = 0x0020;
	nfc_wait();

	return (u8)((*(volatile u32 *)(NFC_MAB0_BASE)) & 0xFF) ;
}
/*!
 * Function to wait nand ready
 */
void nand_wait(void)
{
	while(!(NAND_STATUS_READY  & nand_read_status()));
}

/*!
 * Function to check ecc status
 */
u8 nfc_ecc_uncorrectable_error(u32 page_size)
{
	u32 ecc_stat, err;
	int no_subpages = 1;
	int ret = 0;
	u8 ecc_bit_mask, err_limit;

	ecc_bit_mask = (IS_4BIT_ECC ? 0x7 : 0xf);
	err_limit = (IS_4BIT_ECC ? 0x4 : 0x8);

	no_subpages = page_size>>9;

	ecc_stat = *(volatile u32 *)NFC_ECC_STAT_RSLT;

	do {
		err = ecc_stat & ecc_bit_mask;
		if (err > err_limit) {
			ret = 1;
			break;
		}
		ecc_stat >>= 4;
	} while (--no_subpages);

	return ret;

}

/*!
 * Function to set nfc spare data
 */
void  set_nfc_spare(FLASH_FILE_FORMAT file_format )
{
	u32 i,j;
	/*this is for wince spare setting */
	if (FILE_FORMAT_NB0 == file_format) {
		/* fill internal RAM buffer */
        for(j=0;j<NFC_SAB_COUNT;j++) {
  		    for(i=0; i<NFC_SAB_LEN; i+=2){
   			    if((j== ((NAND_MAIN_BYTESIZE >> 9) - 1)) && (i==0))
				    *(volatile u16 *)(NFC_SAB0_BASE+i+j*NFC_SAB_LEN) = 0xFF00;
			    else
      			    *(volatile u16 *)(NFC_SAB0_BASE+i+j*NFC_SAB_LEN) = 0xFFFF;
		    }
        }
	} else if (FILE_FORMAT_NORMAL == file_format) {
  	    /* fill internal RAM buffer */
        for(j=0;j<NFC_SAB_COUNT;j++) {
  	        for(i=0; i<NFC_SAB_LEN; i+=2) {
		        *(volatile u16 *)(NFC_SAB0_BASE+i+j*NFC_SAB_LEN) = 0xFFFF;
  	        }
        }
	}
}

/*!
 * Function to init nfc
 */
void nfc_init(void)
{
	raw_write((raw_read(CCM_CBCDR7)& ~7) | 0x2,CCM_CBCDR7);
	raw_write(raw_read(CCM_CCDR)| 0x1,CCM_CCDR);

	/*clear spas size */
	*(volatile u32 *)NFC_NF_CONFIG2 &= SPAS_MASK;

	/* select Buffer 0 */
	NFC_SEL_RAM_BUFFER(RBA_BUFFER0);

	/* unlock the blk */
	*(volatile u32 *)NFC_ULOCK_BLK0 = (0xFFFF << 16);
	/* unlock the internal RAM buffer */
	*(volatile u32 *)NFC_NF_WR_PROT	= 0x20004;

	/* clear all operation */
	*(volatile u32 *)NFC_IPC = 0x80000000;

	/* 128pages,4bit ECC,little endian,enable ECC,disable interrupt,2Kpage*/
	*(volatile u32 *)NFC_NF_CONFIG2 = 0x1149;
}

/*!
 * Function to set FMS
 */
void set_fms(u8 bus_width, u32 page_size,u16 oob_size)
{
        u16 spare_size_perpage = 0;
        
	if(page_size == 4096) {
		/* Set to 4K Page Size */
		*(volatile u32 *)NFC_NF_CONFIG2 &= ~3;
		*(volatile u32 *)NFC_NF_CONFIG2 |= 2;
	}
	/* spare sie for per page is oob_size/(page_size/512)*/
	spare_size_perpage = oob_size / (page_size >> 9);
	
	if (spare_size_perpage == 16) {
                /* 4bit ECC  1'b1 */
                raw_write(raw_read(NFC_NF_CONFIG2) | NFC_ECC_MODE_4, NFC_NF_CONFIG2);
	}
	else if (spare_size_perpage >= 26) {
                /* 8bit ECC  1'b0*/
                raw_write(raw_read(NFC_NF_CONFIG2) & NFC_ECC_MODE_8, NFC_NF_CONFIG2);
        }
	/* set the spas size */
	SET_SPAS(oob_size >>1);

}

/*!
 * Function to read id
 */
void send_read_id(u8* id, int len)
{
	int i;
	volatile u16* s = (volatile u16 *)NFC_MAB0_BASE;
	nfc_command_input(0x90);
	nfc_address_input(0);
	NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
	*(volatile u32 *)NFC_LAUNCH_NFC = 0x0010;
	nfc_wait();
	for (i = 0; i < (len >> 1); i++) {
		*(u16*)id  = *s;
		id += 2;
		s++;
	}
	if (len & 0x1)
		*id = (u8)*s;
}


#endif /* __MX37_NFC_H__ */
