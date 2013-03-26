/*****************************************************************************
** mx53_nfc.h
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

#ifndef __MX53_NFC_H__
#define __MX53_NFC_H__

#include "type.h"
#include "flash_lib.h"
   
#define AXI_BASE_ADDR 	0xF7FF0000
#define NFC_BASE_ADDR 	0x63FDB000 

#define NFC_MAB0_BASE	(AXI_BASE_ADDR + 0x000)
#define NFC_MAB1_BASE	(AXI_BASE_ADDR + 0x200)
#define NFC_MAB2_BASE	(AXI_BASE_ADDR + 0x400)
#define NFC_MAB3_BASE	(AXI_BASE_ADDR + 0x600)
#define NFC_MAB4_BASE	(AXI_BASE_ADDR + 0x800)
#define NFC_MAB5_BASE	(AXI_BASE_ADDR + 0xA00)
#define NFC_MAB6_BASE	(AXI_BASE_ADDR + 0xC00)
#define NFC_MAB7_BASE	(AXI_BASE_ADDR + 0xE00)
		
#define NFC_SAB0_BASE	(AXI_BASE_ADDR + 0x1000)
#define NFC_SAB1_BASE	(AXI_BASE_ADDR + 0x1040)
#define NFC_SAB2_BASE	(AXI_BASE_ADDR + 0x1080)
#define NFC_SAB3_BASE	(AXI_BASE_ADDR + 0x10C0)
#define NFC_SAB4_BASE	(AXI_BASE_ADDR + 0x1100)
#define NFC_SAB5_BASE	(AXI_BASE_ADDR + 0x1140)
#define NFC_SAB6_BASE	(AXI_BASE_ADDR + 0x1180)
#define NFC_SAB7_BASE	(AXI_BASE_ADDR + 0x11C0)
#define NFC_SAB_LEN     64                   
#define NFC_SAB_COUNT  	8 

#define NFC_NAND_CMD		AXI_BASE_ADDR + 0x1E00	
#define NFC_NAND_ADD_0		AXI_BASE_ADDR + 0x1E04
#define NFC_NAND_ADD_1		AXI_BASE_ADDR + 0x1E08			
#define NFC_NAND_ADD_2		AXI_BASE_ADDR + 0x1E0C			
#define NFC_NAND_ADD_3		AXI_BASE_ADDR + 0x1E10			
#define NFC_NAND_ADD_4		AXI_BASE_ADDR + 0x1E14			
#define NFC_NAND_ADD_5		AXI_BASE_ADDR + 0x1E18			
#define NFC_NAND_ADD_6		AXI_BASE_ADDR + 0x1E1C			
#define NFC_NAND_ADD_7		AXI_BASE_ADDR + 0x1E20
#define NFC_NAND_ADD_8		AXI_BASE_ADDR + 0x1E24			
#define NFC_NAND_ADD_9		AXI_BASE_ADDR + 0x1E28			
#define NFC_NAND_ADD_10		AXI_BASE_ADDR + 0x1E2C			
#define NFC_NAND_ADD_11		AXI_BASE_ADDR + 0x1E30			
			

#define NFC_CONFIGURATION1	AXI_BASE_ADDR + 0x1E34
#define NFC_ECC_STATUS_RESULT	AXI_BASE_ADDR + 0x1E38			
#define NFC_STATUS_SUM		AXI_BASE_ADDR + 0x1E3C			
#define NFC_LAUNCH_NFC		AXI_BASE_ADDR + 0x1E40			


#define NFC_WR_PROTECT		NFC_BASE_ADDR + 0x00			
/*#define NFC_UNLOCK_BLK_ADD0	NFC_BASE_ADDR + 0x04			
#define NFC_UNLOCK_BLK_ADD1	NFC_BASE_ADDR + 0x08			
#define NFC_UNLOCK_BLK_ADD2	NFC_BASE_ADDR + 0x0C			
#define NFC_UNLOCK_BLK_ADD3	NFC_BASE_ADDR + 0x10
#define NFC_UNLOCK_BLK_ADD4	NFC_BASE_ADDR + 0x14			
#define NFC_UNLOCK_BLK_ADD5	NFC_BASE_ADDR + 0x18			
#define NFC_UNLOCK_BLK_ADD6	NFC_BASE_ADDR + 0x1C			
#define NFC_UNLOCK_BLK_ADD7	NFC_BASE_ADDR + 0x20			
*/
			
#define NFC_CONFIGURATION2	NFC_BASE_ADDR + 0x24
#define NFC_CONFIGURATION3	NFC_BASE_ADDR + 0x28			
#define NFC_IPC			NFC_BASE_ADDR + 0x2C			
#define NFC_AXI_ERR_ADDR	NFC_BASE_ADDR +	0x30			
		

/*---------------------------------------------------------------------------*/
/* NFC CONFIGURATION1							     */
/*---------------------------------------------------------------------------*/

#define NFC_CONF1_CS_SHIFT 12
#define NFC_CONF1_CS_SIZE 3
#define NFC_CONF1_CS_MASK 0x00007000
#define GET_NFC_CONF1_CS \
	((raw_read(NFC_CONFIGURATION1) & NFC_CONF1_CS_MASK) >> NFC_CONF1_CS_SHIFT)
#define SET_NFC_CONF1_CS(code) \
	(raw_write((raw_read(NFC_CONFIGURATION1) & ~NFC_CONF1_CS_MASK) | \
	(code << NFC_CONF1_CS_SHIFT), NFC_CONFIGURATION1))


#define NFC_CONF1_RBA_SHIFT 4
#define NFC_CONF1_RBA_SIZE 3
#define NFC_CONF1_RBA_MASK 0x00000070
#define GET_NFC_CONF1_RBA \
	((raw_read(NFC_CONFIGURATION1) & NFC_CONF1_RBA_MASK) >> NFC_CONF1_RBA_SHIFT)
#define SET_NFC_CONF1_RBA(code) \
	(raw_write((raw_read(NFC_CONFIGURATION1) & ~NFC_CONF1_RBA_MASK) | \
	(code << NFC_CONF1_RBA_SHIFT), NFC_CONFIGURATION1))


/*---------------------------------------------------------------------------*/
/*	NFC IPC								     */
/*---------------------------------------------------------------------------*/

#define NFC_INT_BUSY	!(raw_read(NFC_IPC) & 0x80000000) 
#define NFC_READY  	(raw_read(NFC_IPC) &= ~0x10000000)
#define IP_BUSY		(!(raw_read(NFC_IPC) & 0x00000002))

/*---------------------------------------------------------------------------*/
/* NFC ERROR code for internal                                               */
/*---------------------------------------------------------------------------*/
#define	NFC_NO_ERR			0x00
#define NFC_SB_1BIT_ECC_ERR		0x01
#define NFC_SB_2BIT_ECC_ERR		0x02
#define NFC_PB_1BIT_ECC_ERR		0x04
#define NFC_PB_2BIT_ECC_ERR		0x08
#define NFC_ERASE_ERR			0x10
#define NFC_WRITE_ERR			0x20
#define NFC_READ_ERR			0x40
#define NFC_ILLEGAL_ACCESS		0x80

/* FMS & bus width */
#define NF_FMS_2KB			0x00000001
#define NF_4KB				0x00000002
#define NF_16BIT			~(0x00000008)
#define NFC_OPS_STAT			(1 << 31)
#define NFC_IPC_CREQ			(1 << 0)
#define NFC_IPC_ACK			(1<<1)
#define NFC_ECC_MODE_8			(1<<6)
#define NFC_ECC_MODE_4		        ~(3<<6)
#define NFC_ECC_MODE_14		        (1<<7)
#define NFC_ECC_MODE_16		        (3<<6)
#define RBA_RESET			~(7 << 4)
#define SPAS_MASK			0xFF00FFFF
/*#define RBA_BUFFER0			(0 << 4)*/
#define RBA_BUFFER0			(0 << 4)
#define RBA_BUFFER1			(1 << 4)
#define RBA_BUFFER2			(2 << 4)
#define RBA_BUFFER3			(3 << 4)
#define RBA_BUFFER4			(4 << 4)
#define RBA_BUFFER5			(5 << 4)
#define RBA_BUFFER6			(6 << 4)
#define RBA_BUFFER7			(7 << 4)

/* command for LAUNCH_NFC */
#define LAUNCH_ADDRESS_INPUT		0x2
#define LAUNCH_COMMAND_INPUT		0x1
#define LAUNCH_READ_ID			0x10 
#define LAUNCH_READ_STATUS		0x1000
#define LAUNCH_AUTO_READ		0x80
#define LAUNCH_AUTO_ERASE		0x200
#define LAUNCH_AUTO_PRO			0x40

#define CLEAR_OPS_STAT() \
	WRITE_NFC_IP_REG((raw_read(NFC_IPC) & ~NFC_OPS_STAT), NFC_IPC);
/*BBP Need to add 14/16 bit ECC*/
#define IS_8BIT_ECC			\
	((raw_read(NFC_CONFIGURATION2) & NFC_ECC_MODE_8)>>6)
	
#define WRITE_NFC_IP_REG(val,reg) \
	do {	 \
		raw_write(NFC_IPC_CREQ, NFC_IPC); \
		while(!((raw_read(NFC_IPC) & NFC_IPC_ACK)>>1));\
		raw_write(val, reg);\
		raw_write(0, NFC_IPC);\
	}while(0)
	

#define SET_SPAS(v)			\
	raw_write(((raw_read(NFC_CONFIGURATION2) & SPAS_MASK) | ((v)<<16)), \
	NFC_CONFIGURATION2)

#define NFC_SEL_RAM_BUFFER(val) \
	(raw_write((raw_read(NFC_CONFIGURATION1) & ~NFC_CONF1_RBA_MASK) | \
	(val << NFC_CONF1_RBA_SHIFT),NFC_CONFIGURATION1))
		
#define SPAS_64		(32)
#define SPAS_128	(64)
#define SPAS_218	(109)
#define SPAS_224	(112)

/*marco to detect the busy status*/
#define NFC_BUSY  (!( *(volatile u32 *)NFC_IPC & 0x80000000 ))

/*marco to define the raw_read/write*/
#define raw_read(addr) *(u32 *)((addr))
#define raw_write(val,addr) *((u32 *)(addr)) = (val)

/*BBP Need to add support for larger spare areas offset*/
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
static u32 back_cmd;

/*!
 * Function to wait for basic NFC operation completion
 */
static u8 nfc_wait(void)
{
	while (1) {
		if (raw_read(NFC_IPC) & NFC_OPS_STAT) {
			WRITE_NFC_IP_REG((raw_read(NFC_IPC) & ~NFC_OPS_STAT), 
			NFC_IPC);
			break;
		}
			
	}
	return 0;
			
}

/*!
 * Function to read status from nand flash register
 */
u32 nand_read_status(void)
{	
	u32 status;

	CLEAR_OPS_STAT();

	do {
		raw_write(LAUNCH_READ_STATUS,NFC_LAUNCH_NFC);
		nfc_wait();
		status = (raw_read(NFC_CONFIGURATION1) & 0xFFFF0000) >> 16;
	} while ((status & 0x40) == 0); /*0x40: Busy */

  	return status;
}

/*!
 * Function to wait nand ready
 */
void nand_wait(void)
{
	while(!(NAND_STATUS_READY  & nand_read_status()));
}


/*!
 * Function to input address
 */
static void nfc_address_input(u32 address)
{	
	raw_write(address, NFC_NAND_ADD_0);
	
	CLEAR_OPS_STAT();
        
	raw_write(LAUNCH_ADDRESS_INPUT, NFC_LAUNCH_NFC);
	
	 /* Wait for Basic Operation Complete */
        nfc_wait();
}

/*!
 * Function to write flash address cycle
 */
static void nfc_address_cycle(u32 Address, u8 NumOfCycle)
{
	u32 mask = 0xffff;
	
	if(back_cmd == NAND_CMD_ERASE) {
                raw_write(Address, NFC_NAND_ADD_0);
	   	
	} else {
		/* for other than erase */
		raw_write(0, NFC_NAND_ADD_0);	
		raw_write((raw_read(NFC_NAND_ADD_0) | 
		         ((Address & mask) << 16)), NFC_NAND_ADD_0);
		raw_write(((raw_read(NFC_NAND_ADD_8) & (mask << 16)) | 
		          ((Address & (mask << 16)) >> 16)), NFC_NAND_ADD_8);
	}
}

/*!
 * Function to input command
 */
static void nfc_command_input(u32 command)
{
	//back up the cmd
	back_cmd = command;
		
	switch ((u8)command)
	{
                case NAND_CMD_READ:	
                        raw_write(command, NFC_NAND_CMD);
                        break;	
                case NAND_CMD_RESET:
                        raw_write(command, NFC_NAND_CMD);
                        CLEAR_OPS_STAT();
                        raw_write(LAUNCH_COMMAND_INPUT,NFC_LAUNCH_NFC);
                        nfc_wait();
                        break;
                case NAND_CMD_ERASE:
                        break;
                case NAND_CMD_READID:
                        raw_write(command, NFC_NAND_CMD);
                        CLEAR_OPS_STAT();
                        raw_write(LAUNCH_COMMAND_INPUT,NFC_LAUNCH_NFC);
                        nfc_wait();
                        break;
                case NAND_CMD_PAGE_PROG:
                        raw_write(command, NFC_NAND_CMD);
                        raw_write(raw_read(NFC_NAND_CMD) | 
			(NAND_CMD_PAGE_PROG_CONFIRM << 8), NFC_NAND_CMD);
                        break;	
                case NAND_CMD_READ_CONFIRM:
                        raw_write(raw_read(NFC_NAND_CMD) | (command << 8), 
			NFC_NAND_CMD);
                        break;
                case NAND_CMD_PAGE_PROG_CONFIRM:
                        break;
                case NAND_CMD_ERASE_CONFIRM:	
                        raw_write(NAND_CMD_ERASE, NFC_NAND_CMD);
                        raw_write(raw_read(NFC_NAND_CMD) | 
			(NAND_CMD_ERASE_CONFIRM << 8), NFC_NAND_CMD);
			
			CLEAR_OPS_STAT();
                        /* launch auto erase operation */
                        raw_write(LAUNCH_AUTO_ERASE, NFC_LAUNCH_NFC);
                        nfc_wait();
                        break;
                default:
                        break;
			
       }	 
}

/* BBP Not needed in mx53
static void nfc_block_unlock(u8 val)
{
        raw_write(0x0, NFC_UNLOCK_BLK_ADD0 + (val << 2));
        raw_write(0xffff<<16, NFC_UNLOCK_BLK_ADD0 + (val << 2));
}

static void nfc_unlock_cs(u32 cs)
{
        /*Flash UN-Lock Setting/
        u32 data2write;
        u32 new_cs;

        new_cs = (0x7 & cs)<<3;
        data2write = 0x84 | new_cs;
        raw_write(data2write, NFC_WR_PROTECT);
} 
*/

/*!
  * Automation operations
  */

/*!
 * Function to send command to read page
 */
void send_read_page(void)
{	
        NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
        
        CLEAR_OPS_STAT();
        /* lauch auto read operation */
        raw_write(LAUNCH_AUTO_READ, NFC_LAUNCH_NFC);
        nfc_wait();
        nand_wait();
}

/*!
 * Function to send command to write page
 */
void send_prog_page(void)
{
        NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
        
        CLEAR_OPS_STAT();
        /* launch auto programming operation */
        raw_write(LAUNCH_AUTO_PRO, NFC_LAUNCH_NFC); 
        nfc_wait();
}

/*!
 * Function to check ecc status
 */
/*BBP need to modify for 14/16 bit ECC support*/
u8 nfc_ecc_uncorrectable_error(u32 page_size)
{
        u32 ecc_stat, err;
        int no_subpages = 1;
        int ret = 0;
        u8 ecc_bit_mask, err_limit;

       /*
        Elvis TO2: 1'b1   8bit error 
                   0'b1   4bit error
       */
        ecc_bit_mask = (IS_8BIT_ECC? 0xf : 0x7);
        err_limit = (IS_8BIT_ECC? 0x8 : 0x4);

	no_subpages = page_size>>9;

        ecc_stat = raw_read(NFC_ECC_STATUS_RESULT);
	
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
        u32 m = NFC_SAB_COUNT;
        u32 n = NFC_SAB_LEN;
        u32 pg_size = nand->page_size / num_of_pipline;
        u32 d = NFC_SAB0_BASE;
        
	switch (file_format) {
	case FILE_FORMAT_NB0:
		/* for wince setting */
        	for(j = 0; j < m; j++) {
			for(i = 0; i < n; i += 2) {
				if((j == ((pg_size >> 9) - 1)) && (i == 0))
					*(volatile u16 *)(d + i + j * n) = 0xFF00;
				else
					*(volatile u16 *)(d + i + j * n) = 0xFFFF;
			}
		}
		break;
	case FILE_FORMAT_NORMAL:
		/* for linux setting */
        	for(j = 0; j < m; j++) {
  	       		for(i = 0; i < n; i += 2) {
		        	*(volatile u16 *)(d + i + j * n) = 0xFFFF;
  	        	}
        	}
		break;
	default:
		break;
	}
	
}

/*!
 * Function to init nfc
 */
void nfc_init(void)
{
	u8 i;
		
/*	Setup IOMUX for ARD NAND */	
	for(i = 0; i < 8; i++){
		raw_write(0, 0x53fa8228 + (i << 2));
		raw_write(0, 0x53fa819c + (i << 2));
	}	
		raw_write(0, 0x53fa81dc);
		raw_write(0, 0x53fa81e0);
		raw_write(0, 0x63fd800c); //Set EIM_DAx pins for NAND

        	
        /* NFC_CONFIGURATION2  TO2
                ST_CMD 			- 	8'b01110000   
		SPAS			-	8'b01101101
		INT_MSK			-	1'b1   disable interrupt
		AUTO_PROG_DONE_MSK 	-	1'b0
		NUM_ADR_PHASE1		-	2'b10  5 address
		EDC			-	3'b00
		PPB			-	2'b10
		ECC_MODE		-	1'b01   8bit error
		NUM_ADR_PHASE0		-	1'b1   (5-2 = 3) address phase
		NUM_CMD_PHASES		-	1'b1   2 pahses
		ECC_EN			-	1'b1   Ecc enable
		SYM			-	1'b1   symmetric RE
		PS			-	2'b10  4kb page
	*/
        raw_write(0x706DA27E,NFC_CONFIGURATION2);
	
	/* NO_SDMA,FMP=6,SBB=6,little Endian,Flash Width=x8*/
	raw_write(0x00160608, NFC_CONFIGURATION3);

        NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
        
        SET_NFC_CONF1_CS(0);
}

/*!
 * Function to read id
 */
void send_read_id(u8* id, int len)
{
	int i;
	volatile u16* s = (volatile u16 *)NFC_MAB0_BASE;
	nfc_command_input(NAND_CMD_RESET);
        NFC_SEL_RAM_BUFFER(RBA_BUFFER0);
        nfc_command_input(NAND_CMD_READID);
        nfc_address_input(0);
        CLEAR_OPS_STAT();
        raw_write(LAUNCH_READ_ID, NFC_LAUNCH_NFC);
        /* Wait for Basic Operation Complete */
        nfc_wait();
        for (i = 0; i < (len >> 1); i++) {
		*(u16*)id  = *s;
		id += 2;
		s++;
	}
	if (len & 0x1)
		*id = (u8)*s;
}

/*!
 * Function to set FMS
 */
void set_fms(u8 bus_width, u32 page_size,u16 oob_size)
{
	u8 i = 1;
	u32 tmp = 0;
	u16 spare_size_perpage = 0;
	
        if(bus_width == 16)
                raw_write(raw_read(NFC_CONFIGURATION3) & NF_16BIT, 
		NFC_CONFIGURATION3);  /* Set to 16-bit NAND */
        if(page_size == 4096) {
                /* Set to 4K Page Size */
                raw_write(raw_read(NFC_CONFIGURATION2) & ~3, NFC_CONFIGURATION2);
                raw_write(raw_read(NFC_CONFIGURATION2) | 2, NFC_CONFIGURATION2);
        }
        if (page_size == 2048) {
                /* Set to 2K Page Size */
                raw_write(raw_read(NFC_CONFIGURATION2) & ~3, NFC_CONFIGURATION2);
                raw_write(raw_read(NFC_CONFIGURATION2) | 1, NFC_CONFIGURATION2);
        }	
        if (page_size <= 512)
        {
                /*  NFC_CONFIGURATION2
                NUM_ADR_PHASE1		-	2'b01  4 address phase 
                NUM_ADR_PHASE0		-	1'b0   (4-1 = 3) address phase
                NUM_CMD_PHASES		-	1'b0   1 pahses 
                PS			-	2'b00  1/2kb page   
                */
                raw_write(raw_read(NFC_CONFIGURATION2) & ~0x3033, 
		NFC_CONFIGURATION2);
		
                raw_write(raw_read(NFC_CONFIGURATION2) | 0x1000, 
		NFC_CONFIGURATION2);	
        }
	/* set the spas size */
	SET_SPAS(oob_size >>1);  
	
	/* spare sie for per page is oob_size/(page_size/512)*/
	spare_size_perpage = oob_size / (page_size >> 9);
	
	if (spare_size_perpage == 16) {
                /* 4bit ECC  1'b0 */
                raw_write(raw_read(NFC_CONFIGURATION2) & NFC_ECC_MODE_4, NFC_CONFIGURATION2);
	}
	else if (spare_size_perpage >= 26) {
                /* 8bit ECC  1'b1*/
                raw_write(raw_read(NFC_CONFIGURATION2) | NFC_ECC_MODE_8, NFC_CONFIGURATION2);
        }
	       
	/* set to ADD_OP mode 1 */
	raw_write(raw_read(NFC_CONFIGURATION3) & ~0x3, NFC_CONFIGURATION3);
	
	raw_write(raw_read(NFC_CONFIGURATION3) | 0x1, NFC_CONFIGURATION3);
	
	/* probe to find the number of chips */
	for(; i < 8; i++ ) {
		SET_NFC_CONF1_CS(i);
		send_read_id((u8*)&tmp, 4);
		if((u8)tmp != nand->man_id ||  
		   (u8)(tmp >> 8) != nand->dev_id)
		   break;	
	}
	
	nand->num_chips = i;
	                		
	/* set num_of_device to decode the cs */
	raw_write(raw_read(NFC_CONFIGURATION3) & (~(7 << 12)), NFC_CONFIGURATION3);
	
	raw_write(raw_read(NFC_CONFIGURATION3) | ((i - 1) << 12), NFC_CONFIGURATION3);
}
 
#endif /* __MX53_NFC_H__ */
