/*****************************************************************************
** spi_nor.h
**
** Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
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

#ifndef _IMX_SPI_NOR_H_
#define _IMX_SPI_NOR_H_

#include <type.h>
#include <imx_spi.h>

#define READ		0x03    	// tx: 1 byte cmd + 3 byte addr; rx: variable bytes
#define READ_HS	0x0B    		// tx: 1 byte cmd + 3 byte addr + 1 byte dummy; rx: variable bytes
#define RDSR		0x05    	// read status register 1 byte tx cmd + 1 byte rx status
#define RDSR_BUSY	(1 << 0)    	// 1=write-in-progress (default 0)
#define RDSR_WEL	(1 << 1)    	// 1=write enable (default 0)
#define RDSR_BP0	(1 << 2)    	// block write prot level (default 1)
#define RDSR_BP1        (1 << 3)    	// block write prot level (default 1)
#define RDSR_BP2	(1 << 4)    	// block write prot level (default 1)
#define RDSR_BP3	(1 << 5)    	// block write prot level (default 1)
#define RDSR_AAI	(1 << 6)    	// 1=AAI prog mode; 0=byte prog (default 0)
#define RDSR_BPL	(1 << 7)    	// 1=BP3,BP2,BP1,BP0 RO; 0=R/W (default 0)
#define WREN		0x06    	// write enable. 1 byte tx cmd
#define WRDI		0x04    	// write disable. 1 byte tx cmd
#define EWSR		0x50    	// Enable write status. 1 byte tx cmd
#define WRSR		0x01    	// Write status register. 1 byte tx cmd + 1 byte tx value
#define ERASE_4K	0x20    	// sector erase. 1 byte cmd + 3 byte addr
#define ERASE_32K	0x52    	// 32K block erase. 1 byte cmd + 3 byte addr
#define ERASE_64K	0xD8    	// 64K block erase. 1 byte cmd + 3 byte addr
#define ERASE_CHIP	0x60    	// whole chip erase
#define BYTE_PROG	0x02    	// all tx: 1 cmd + 3 addr + 1 data
#define AAI_PROG	0xAD    	// all tx: [1 cmd + 3 addr + 2 data] + RDSR
					//   + [1cmd + 2 data] + .. + [WRDI] + [RDSR]
#define JEDEC_ID	0x9F    	// read JEDEC ID. tx: 1 byte cmd; rx: 3 byte ID


/* Atmel SPI-NOR commands */
#define WR_2_MEM_DIR	0x82
#define BUF1_WR		0x84
#define BUF2_WR		0x87
#define BUF1_TO_MEM     0x83
#define BUF2_TO_MEM     0x86
#define STAT_READ	0xD7
#define STAT_PG_SZ	(1 << 0)  	// 1=Page size is 512, 0=Page size is 528 (default 0)
#define STAT_PROT	(1 << 1)  	// 1=sector protection enabled (default 0)
#define STAT_COMP	(1 << 6)
#define STAT_BUSY	(1 << 7) 	// 1=Device not busy
#define CONFIG_REG1	0x3D
#define CONFIG_REG2	0x2A
#define CONFIG_REG3	0x80
#define CONFIG_REG4	0xA6

#define SZ_64K		0x10000
#define SZ_32K		0x8000
#define SZ_4K		0x1000

// Information about supported devices
typedef struct {
	char* name;
	u8 device_id1;
	u8 device_id2;
	u8 device_id3;
	u32 block_size;
	u32 block_count;
}spi_flash_model;

typedef int imx_spi_write_func_t(spi_flash_model *model, u32 dest, u32 src, int len, response_callback callback);
typedef int imx_spi_erase_func_t(spi_flash_model *model, u32 addr, u32 len, response_callback callback);
typedef int imx_spi_read_func_t(spi_flash_model *model, u32 dest, u32 src, int len, dump_callback callback);


extern struct imx_spi_dev *imx_spi_nor;


extern const spi_flash_model* supported_model[];

int spi_nor_program_buf_sst(spi_flash_model *model, u32 dest, u32 src, int len, response_callback callback);
int spi_nor_erase_block_sst(spi_flash_model *model, u32 addr, u32 len, response_callback callback);
int spi_nor_read_sst(spi_flash_model *model, u32 dest, u32 src, int len, dump_callback callback);

int spi_nor_program_buf_atm(spi_flash_model *model, u32 dest, u32 src, int len, response_callback callback);
int spi_nor_erase_block_atm(spi_flash_model *model, u32 addr, u32 len, response_callback callback);
int spi_nor_read_atm(spi_flash_model *model, u32 dest, u32 src, int len, dump_callback callback);

s16 spi_flash_init(void);
s16 spi_flash_get_capacity(u32 *size);
void spi_flash_get_model(u8 *fmodel, u32 *len);
int spi_flash_erase(u32 addr, u32 len, response_callback callback);
int spi_flash_program(u32 dest, u32 src, u32 len, response_callback callback);
int spi_flash_read(u32 src, u32 dest, u32 len, dump_callback callback);
s16 spi_flash_compare(u32 src, u32 dest, u32 len,response_callback callback);

#endif /* _IMX_SPI_NOR_H_ */
