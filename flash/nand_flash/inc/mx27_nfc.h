/*****************************************************************************
** mx27_nfc.h
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

#ifndef __MX27_NFC_H__
#define __MX27_NFC_H__

#include "type.h"
#include "flash_lib.h"

#define CCM_RCSR	    (0x10027000+0x814)
#define CCM_PDR0 	    (0x10027000+0x18)
#define NFC_BASE_ADDR	    (0xD8000000)

#define NFC_MAB0_BASE       (NFC_BASE_ADDR+0x000)	
#define NFC_MAB1_BASE       (NFC_BASE_ADDR+0x200)	
#define NFC_MAB2_BASE       (NFC_BASE_ADDR+0x400)	
#define NFC_MAB3_BASE       (NFC_BASE_ADDR+0x600)	
#define NFC_SAB0_BASE       (NFC_BASE_ADDR+0x800)	
#define NFC_SAB1_BASE       (NFC_BASE_ADDR+0x810)	
#define NFC_SAB2_BASE       (NFC_BASE_ADDR+0x820)	
#define NFC_SAB3_BASE       (NFC_BASE_ADDR+0x830)
#define NFC_SAB_LEN         (16)                 
#define NFC_SAB_COUNT       (4)                     	

#define NFC_REG_BASE        (NFC_BASE_ADDR+0xE00)   
#define NFC_BUFSIZE         (NFC_REG_BASE+0x00)
#define NFC_BLK_ADD_LOCK    (NFC_REG_BASE+0x02)
#define NFC_RAM_BUF_ADDR    (NFC_REG_BASE+0x04)
#define NFC_NAND_FLASH_ADDR (NFC_REG_BASE+0x06)
#define NFC_NAND_FLASH_CMD  (NFC_REG_BASE+0x08)
#define NFC_CONFIGURATION   (NFC_REG_BASE+0x0A)
#define NFC_ECC_STAT_RES    (NFC_REG_BASE+0x0C)
#define NFC_ECC_RSLT_MA     (NFC_REG_BASE+0x0E)
#define NFC_ECC_RSLT_SA     (NFC_REG_BASE+0x10)
#define NFC_NF_WR_PROT      (NFC_REG_BASE+0x12)
#define NFC_ULOCK_START_BLK (NFC_REG_BASE+0x14)
#define NFC_ULOCK_END_BLK   (NFC_REG_BASE+0x16)
#define NFC_NF_WR_PROT_STAT (NFC_REG_BASE+0x18)
#define NFC_NF_CONFIG1      (NFC_REG_BASE+0x1A)
#define NFC_NF_CONFIG2      (NFC_REG_BASE+0x1C)

#define NF_FMS_2KB                 (0x20)
#define NF_16BIT                   (0x10)
#define PCDR0_NFCDIV_MASK          (0x0000F000)
#define PCDR0_NFCDIV_10            (0x9)

#define NFC_BUSY  (!( *(volatile u16 *)NFC_NF_CONFIG2 & 0x8000 ))

/* main area for bad block marker*/
#define BAD_BLK_MARKER_MAIN     (*((volatile u16 *)(NFC_MAB3_BASE + 464)))
/* spare area for swapped main area data */
#define BAD_BLK_MARKER_SP_0     (*((volatile u16 *)(NFC_SAB3_BASE + 4)))

#define NAND_MAIN_BYTESIZE          (nand->page_size / num_of_pipline)
#define NAND_SPARE_BYTESIZE         (nand->oob_size / num_of_pipline)
extern u32 num_of_pipline;
extern struct nand_device_info* nand;

/*!
 * Function to wait for basic NFC operation completion
 *
 */
static u8 nfc_wait(void)
{
	while(NFC_BUSY);
	return 0;
}

/*!
 * Function to input address
 *
 */
static void nfc_address_input(u16 address)
{
	*(volatile u16 *)NFC_NAND_FLASH_ADDR = address;
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0002;
	nfc_wait();
}

/*!
 * Function to write flash address cycle
 *
 */
static void nfc_address_cycle(u32 Address, u8 NumOfCycle)
{
	u8 i;
	for(i=0; i<NumOfCycle; i++)
		nfc_address_input( (u16)( (Address>>(i*8))&0xFF ) );
}

/*!
 * Function to input command
 *
 */
static void nfc_command_input(u16 command)
{
	*(volatile u16 *)NFC_NAND_FLASH_CMD  = command;
	*(volatile u16 *)NFC_NF_CONFIG2      = 0x0001;
	nfc_wait();
}

/*!
 * Function to input data
 *
 */
static void nfc_flash_data_input(void)
{
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0004;
	nfc_wait();
}

/*!
 * Function to output data
 */
static void nfc_flash_data_output(void)
{
	*(volatile u16 *)NFC_NF_CONFIG2 = 0x0008;
	nfc_wait();
}

/*!
 * Function to check ecc status
 */
static u8 nfc_ecc_uncorrectable_error(u32 page_size)
{
	return ( *(volatile u32 *)NFC_ECC_STAT_RES & 0xA ) ? 1 : 0;
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
 * Function to wait the nand flash ready
 */
void nand_wait(void)
{
	while(!(NAND_STATUS_READY  & nand_read_status()));
}

/*!
 * Function to send command to read page
 */
static void send_read_page(void) 
{
	u8 i;
	u8 j = (NAND_MAIN_BYTESIZE) >> 9;
	
	for (i=0;i<j;i++) {
		*(volatile u16 *)NFC_RAM_BUF_ADDR = i;
		nfc_flash_data_output();		
	}
}

/*!
 * Function to send command to write page
 */
static void send_prog_page(void)
{
	u8 i;
	u8 j = (NAND_MAIN_BYTESIZE) >> 9;
	
	for (i=0;i<j;i++) {
		*(volatile u16 *)NFC_RAM_BUF_ADDR = i;
		nfc_flash_data_input();		
	}
}

/*!
 * Function to set nfc spare data
 */
void  set_nfc_spare(FLASH_FILE_FORMAT file_format)
{
	u32 i;
	if (FILE_FORMAT_NB0 == file_format) {
		/* fill internal RAM buffer */
  		for(i=0; i<64; i+=2){
   			if((i == 4)||(i == 20) ||(i == 36)||(i == 52))
				*(volatile u16 *)(NFC_SAB0_BASE+i) = 0xFF00;
			else
      			*(volatile u16 *)(NFC_SAB0_BASE+i) = 0xFFFF;
		}
	} else if (FILE_FORMAT_NORMAL == file_format) {
  		/* fill internal RAM buffer */
  		for(i=0; i<64; i+=2)
			*(volatile u16 *)(NFC_SAB0_BASE+i) = 0xFFFF;
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
  	*(volatile u32 *)CCM_PDR0  &= ~PCDR0_NFCDIV_MASK;
  	  	
  	/* set NFC_PODF */  	
  	*(volatile u32 *)CCM_PDR0  |= (PCDR0_NFCDIV_10 << 12);   

	/* select Buffer 0 */
  	*(volatile u16 *)NFC_RAM_BUF_ADDR    = 0;  
  		
	/* unlock the blk */     
  	*(volatile u16 *)NFC_ULOCK_START_BLK = 0x0000;
  	*(volatile u16 *)NFC_ULOCK_END_BLK   = 0xFFFF;
  	*(volatile u16 *)NFC_NF_WR_PROT      = 0x0004;
  	  	
  	/* unlock the internal RAM buffer */  	
  	*(volatile u16 *)NFC_CONFIGURATION   = 0x0002; 
  	  	
  	/* clear all operation */  	
  	*(volatile u16 *)NFC_NF_CONFIG2      = 0x8000; 
  	
	/* enable ECC and disable spare only, disable interrupt*/  	
  	*(volatile u16 *)NFC_NF_CONFIG1      = 0x0018; 

}

/*!
 * Function to set FMS
 */
void set_fms(u8 bus_width, u32 page_size,u16 oob_size)
{
	if(bus_width == 16)
		*(volatile u32 *)CCM_RCSR  |=  NF_16BIT;
	if(page_size == 512)
		*(volatile u32 *)CCM_RCSR  &= ~NF_FMS_2KB;
				   
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


#endif /* __MX3_NFC_H__ */
