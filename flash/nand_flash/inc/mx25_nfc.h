/*****************************************************************************
** mx25_nfc.h
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

#ifndef __MX25_NFC_H__
#define __MX25_NFC_H__

#include "type.h"
#include "flash_lib.h"

#define CCM_RCSR 	        (0x53F80000+0x28)
//#define CCM_PCDR0 	        (0x53F80000+0x18)
#define NFC_BASE_ADDR	    (0xBB000000)

#define NFC_MAB0_BASE       (NFC_BASE_ADDR+0x000)	/* main area buffer0 */
#define NFC_MAB1_BASE       (NFC_BASE_ADDR+0x200)	/* main area buffer1 */
#define NFC_MAB2_BASE       (NFC_BASE_ADDR+0x400)	/* main area buffer2 */
#define NFC_MAB3_BASE       (NFC_BASE_ADDR+0x600)	/* main area buffer3 */
#define NFC_MAB4_BASE       (NFC_BASE_ADDR+0x800)	/* main area buffer4 */
#define NFC_MAB5_BASE       (NFC_BASE_ADDR+0xA00)	/* main area buffer5 */
#define NFC_MAB6_BASE       (NFC_BASE_ADDR+0xC00)	/* main area buffer6 */
#define NFC_MAB7_BASE       (NFC_BASE_ADDR+0xE00)	/* main area buffer7 */

#define NFC_SAB0_BASE       (NFC_BASE_ADDR+0x1000)	/* spare area buffer0 */
#define NFC_SAB1_BASE       (NFC_BASE_ADDR+0x1040)	/* spare area buffer1 */
#define NFC_SAB2_BASE       (NFC_BASE_ADDR+0x1080)	/* spare area buffer2 */
#define NFC_SAB3_BASE       (NFC_BASE_ADDR+0x10C0)	/* spare area buffer3 */
#define NFC_SAB4_BASE       (NFC_BASE_ADDR+0x1100)	/* spare area buffer4 */
#define NFC_SAB5_BASE       (NFC_BASE_ADDR+0x1140)	/* spare area buffer5 */
#define NFC_SAB6_BASE       (NFC_BASE_ADDR+0x1180)	/* spare area buffer6 */
#define NFC_SAB7_BASE       (NFC_BASE_ADDR+0x11C0)	/* spare area buffer7 */
#define NFC_SAB_LEN         (64)                        /* spare area length */
#define NFC_SAB_COUNT       (8)                         /* spare area count */

#define NFC_REG_BASE            (NFC_BASE_ADDR+0x1E00)  /* nfc register area */
#define NFC_RAM_BUF_ADDR        (NFC_REG_BASE+0x04)
#define NFC_NAND_FLASH_ADDR     (NFC_REG_BASE+0x06)
#define NFC_NAND_FLASH_CMD      (NFC_REG_BASE+0x08)
#define NFC_CONFIGURATION       (NFC_REG_BASE+0x0A)
#define NFC_ECC_STAT_RSLT1      (NFC_REG_BASE+0x0C)
#define NFC_ECC_STAT_RSLT2      (NFC_REG_BASE+0x0E)
#define NFC_REG_SPAS            (NFC_REG_BASE+0x10)
#define NFC_NF_WR_PROT          (NFC_REG_BASE+0x12)
#define NFC_NF_WR_PROT_STAT     (NFC_REG_BASE+0x18)
#define NFC_NF_CONFIG1          (NFC_REG_BASE+0x1A)
#define NFC_NF_CONFIG2          (NFC_REG_BASE+0x1C)
#define NFC_ULOCK_START_BLK0    (NFC_REG_BASE+0x20)
#define NFC_ULOCK_END_BLK0      (NFC_REG_BASE+0x22)
#define NFC_ULOCK_START_BLK1    (NFC_REG_BASE+0x24)
#define NFC_ULOCK_END_BLK1      (NFC_REG_BASE+0x26)
#define NFC_ULOCK_START_BLK2    (NFC_REG_BASE+0x28)
#define NFC_ULOCK_END_BLK2      (NFC_REG_BASE+0x2A)
#define NFC_ULOCK_START_BLK3    (NFC_REG_BASE+0x2C)
#define NFC_ULOCK_END_BLK3      (NFC_REG_BASE+0x2E)

/* FMS & bus width */
#define NF_FMS_2KB                 (0x00000100)
#define NF_4KB					   (0x00000200)
#define NF_16BIT                   (0x00004000)
#define NFC_ECC_MODE_4	1
#define NFC_ECC_MODE_8	~1
#define IS_4BIT_ECC	(raw_read(NFC_NF_CONFIG1) & NFC_ECC_MODE_4)
#define SPAS_64		(32) /* half word */

#define NFC_BUSY  (!( *(volatile u16 *)NFC_NF_CONFIG2 & 0x8000 ))

/* main area for bad block marker*/
#define BAD_BLK_MARKER_OFFS      \
	(NAND_MAIN_BYTESIZE - (((((NAND_SPARE_BYTESIZE /(NAND_MAIN_BYTESIZE >> 9)) >> 1)) << 1) * \
	((NAND_MAIN_BYTESIZE >> 9) -1 )))
#define BAD_BLK_MARKER_MAIN 	(*((volatile u16 *)(NFC_MAB0_BASE + BAD_BLK_MARKER_OFFS)))
/* spare area for swapped main area data */
#define BAD_BLK_MARKER_SP_OFFS     \
	(((NAND_MAIN_BYTESIZE >> 9) - 1) * NFC_SAB_LEN)
#define BAD_BLK_MARKER_SP_0     (*((volatile u16 *)(NFC_SAB0_BASE + BAD_BLK_MARKER_SP_OFFS)))

/*marco to define the raw_read/write*/
#define raw_read(addr) *(u16 *)((addr))
#define raw_write(val,addr) *((u16 *)(addr)) = (val)

#define NAND_MAIN_BYTESIZE          (nand->page_size / num_of_pipline)
#define NAND_SPARE_BYTESIZE         (nand->oob_size / num_of_pipline)
extern u32 num_of_pipline;
extern struct nand_device_info* nand;

/*!
 * Function to wait for basic NFC operation completion
 *
 */
u8 nfc_wait(void)
{
	while(NFC_BUSY);
	return 0;
}

/*!
 * Function to input address
 */
void nfc_address_input(u16 address)
{
	*(volatile u16 *)NFC_NAND_FLASH_ADDR = address;
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0002;
	nfc_wait();
}

/*!
 * Function to write flash address cycle
 */
void nfc_address_cycle(u32 Address, u8 NumOfCycle)
{
	u8 i;

	for(i=0; i<NumOfCycle; i++)
		nfc_address_input((u16)( (Address>>(i*8))&0xFF ) );
}

/*!
 * Function to input command
 */
void nfc_command_input(u16 command)
{
	*(volatile u16 *)NFC_NAND_FLASH_CMD  = command;
	*(volatile u16 *)NFC_NF_CONFIG2      = 0x0001;
	nfc_wait();
}

/*!
 * Function to input data
 */
void nfc_flash_data_input(void)
{
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0004;
	nfc_wait();
}

/*!
 * Function to output data
 */
void nfc_flash_data_output(void)
{
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0008;
	nfc_wait();
}

/*!
 * Function to send command to read page
 */
void send_read_page(void)
{
	*(volatile u16 *)NFC_RAM_BUF_ADDR = 0;
	nfc_flash_data_output();
}

/*!
 * Function to send command to write page
 */
void send_prog_page(void)
{
	*(volatile u16 *)NFC_RAM_BUF_ADDR = 0;
	nfc_flash_data_input();
}

/*!
 * Function to read status from nand flash register
 */
u8 nand_read_status(void)
{
	*(volatile u16 *)NFC_RAM_BUF_ADDR = 0;
	nfc_command_input(NAND_CMD_READ_STATUS);
	/* Read Status */
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0020;
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

	ecc_stat = *(volatile u16 *)NFC_ECC_STAT_RSLT1;
	ecc_stat +=  (*(volatile u16 *)NFC_ECC_STAT_RSLT2)<<16;

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
void  set_nfc_spare(FLASH_FILE_FORMAT file_format)
{
	u32 i,j;
	if (FILE_FORMAT_NB0 == file_format) {
		/* fill internal RAM buffer */
        for(j=0;j<NFC_SAB_COUNT;j++){
  		    for(i=0; i<NFC_SAB_LEN; i+=2) {
   			    if((j == ((NAND_MAIN_BYTESIZE >> 9) - 1)) && (i == 0))
				    *(volatile u16 *)(NFC_SAB0_BASE+i+j*NFC_SAB_LEN) = 0xFF00;
			    else
      			    *(volatile u16 *)(NFC_SAB0_BASE+i+j*NFC_SAB_LEN) = 0xFFFF;
		    }
        }
	} else if (FILE_FORMAT_NORMAL == file_format) {
  	    /* fill internal RAM buffer */
        for(j=0;j<NFC_SAB_COUNT;j++){
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
	/* Set to 8-bit NAND */
	*(volatile u32 *)CCM_RCSR  &= ~NF_16BIT;

	/* Set to 2K Page Size */
	*(volatile u32 *)CCM_RCSR  |= NF_FMS_2KB;
	*(volatile u32 *)CCM_RCSR  &= ~NF_4KB;

	/*clear spas size */
	*(volatile u16 *)NFC_REG_SPAS &= 0xFF00;

	/* select Buffer 0 */
	*(volatile u16 *)NFC_RAM_BUF_ADDR    = 0;

	/* unlock the blk */
	*(volatile u16 *)NFC_ULOCK_START_BLK0 = 0;
	*(volatile u16 *)NFC_ULOCK_END_BLK0   = 0xFFFF;
	*(volatile u16 *)NFC_NF_WR_PROT      = 0x0004;

	/* unlock the internal RAM buffer */
	*(volatile u16 *)NFC_CONFIGURATION   = 0x0002;

	/* clear all operation */
	*(volatile u16 *)NFC_NF_CONFIG2      = 0x8000;

	/* enable ECC and disable spare only, disable interrupt*/
	*(volatile u16 *)NFC_NF_CONFIG1      = 0x0C1B;

}
/*!
 * Function to set FMS
 */
void set_fms(u8 bus_width, u32 page_size,u16 oob_size)
{
	u16 spare_size_perpage;
	
	if(bus_width == 16)
		*(volatile u32 *)CCM_RCSR  |=  NF_16BIT;   /* Set to 16-bit NAND */
	if(page_size == 4096){
		/* Set to 4K Page Size */
		*(volatile u32 *)CCM_RCSR  |= NF_4KB;
		*(volatile u32 *)CCM_RCSR  &= ~NF_FMS_2KB;
	}
	/* spare sie for per page is oob_size/(page_size/512)*/
	spare_size_perpage = oob_size / (page_size >> 9);
	
	if (spare_size_perpage == 16) {
                /* 4bit ECC  1'b1 */
                raw_write(raw_read(NFC_NF_CONFIG1) | NFC_ECC_MODE_4, NFC_NF_CONFIG1);
	}
	else if (spare_size_perpage >= 26) {
                /* 8bit ECC  1'b0*/
                raw_write(raw_read(NFC_NF_CONFIG1) & NFC_ECC_MODE_8, NFC_NF_CONFIG1);
        }
	/* set the spas size */
	*(volatile u16 *)NFC_REG_SPAS |= (oob_size)>>1;

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
	*(volatile u16 *)NFC_RAM_BUF_ADDR = 0;
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0010;
	/* wait for complete */
	nfc_wait();
	for (i = 0; i < (len >> 1); i++) {
		*(u16*)id  = *s;
		id += 2;
		s++;
	}
	if (len & 0x1)
		*id = (u8)*s;
}


#endif /* __MX25_NFC_H__ */
