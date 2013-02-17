/*****************************************************************************
** spi_nor_sst.c
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

#include <protocol.h>
#include <type.h>
#include <flash_lib.h>
#include <spi_nor.h>

extern u8 g_tx_buf[256];
extern u8 g_rx_buf[256];

extern imx_spi_init_func_t *spi_nor_init;
extern imx_spi_xfer_func_t *spi_nor_xfer;

#define WRITE_ENABLE()          spi_nor_cmd_1byte(WREN)
#define WRITE_DISABLE()         spi_nor_cmd_1byte(WRDI)
#define ENABLE_WRITE_STATUS()   spi_nor_cmd_1byte(EWSR)

static int spi_nor_status(void)
{
	g_tx_buf[1] = RDSR;
	
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (2 * 8)) != 0) {

		return 0;
	}
	return g_rx_buf[0];
}

/*!
 * Write 'val' to flash WRSR (write status register)
 */
static int spi_nor_write_status(u8 val)
{
	g_tx_buf[0] = val;
	g_tx_buf[1] = WRSR;
	
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (2 * 8)) != 0) {

		return -1;
	}
	
	return 0;
}

static int spi_nor_cmd_1byte(u8 cmd)
{
	g_tx_buf[0] = cmd;
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (1 * 8)) != 0) {
		return -1;
	}
	
	return 0;
}

static int spi_nor_program_1byte(u8 data, void *addr)
{
	u32 addr_val = (u32) addr;

	/* need to do write-enable command */
	if (WRITE_ENABLE() != 0) {
		return FLASH_ERROR_PROG;
	}
	
	/* need to skip bytes 1, 2, 3 */
	g_tx_buf[0] = BYTE_PROG;
	g_tx_buf[4] = data;
	g_tx_buf[5] = addr_val & 0xFF;
	g_tx_buf[6] = (addr_val >> 8) & 0xFF;
	g_tx_buf[7] = (addr_val >> 16) & 0xFF;

	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (5 * 8)) != 0) {
		return FLASH_ERROR_PROG;
	}

	while (spi_nor_status() & RDSR_BUSY) {}
	
	return 0;
}

/* need revisit this function and modify it later */

int spi_nor_program_buf_sst(spi_flash_model *model, u32 dest, u32 src, int len, response_callback callback)
{
	u32 d_addr = dest;
	u8 *s_buf = (u8 *)src;
	u32 count = 0;

	if (ENABLE_WRITE_STATUS() != 0 || spi_nor_write_status(0) != 0) {
		return FLASH_ERROR_PROG;
	}

	if ((d_addr & 1) != 0) {
		/* program 1st byte */
		if (spi_nor_program_1byte(s_buf[0], (void *)d_addr) != 0) {

			return FLASH_ERROR_PROG;
		}
		
		if(callback)
			callback(FLASH_PARTLY, 0, 1);
		
		if (--len == 0)
			return 0;
			
		d_addr++;
		s_buf++;
	}

	/* need to do write-enable command */
	if (WRITE_ENABLE() != 0) {
		return FLASH_ERROR_PROG;
	}

	/*
	 * These two bytes write will be copied to txfifo first with
	 * g_tx_buf[1] being shifted out and followed by g_tx_buf[0].
	 * The reason for this is we will specify burst len=6. So SPI will
	 * do this kind of data movement.
	 */
	
	/* need to skip bytes 2, 3 */
	g_tx_buf[0] = d_addr >> 16;
	g_tx_buf[1] = AAI_PROG;    
	
	/*  byte shifted order is: 7, 6, 5, 4 */
	g_tx_buf[4] = s_buf[1];
	g_tx_buf[5] = s_buf[0];
	g_tx_buf[6] = d_addr;
	g_tx_buf[7] = d_addr >> 8;
	
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (6 * 8)) != 0) {
		return FLASH_ERROR_PROG;
	}

	while (spi_nor_status() & RDSR_BUSY) {}
	
	if(callback)
		callback(FLASH_PARTLY, 0, 2);

	for (d_addr += 2, s_buf += 2, len -= 2;
		len > 1;
		d_addr += 2, s_buf += 2, len -= 2, count += 2) {
		/* byte shifted order is: 2,1,0 */
		g_tx_buf[2] = AAI_PROG;
		g_tx_buf[1] = s_buf[0];
		g_tx_buf[0] = s_buf[1];

		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (3 * 8)) != 0) {

			return FLASH_ERROR_PROG;
		}

		while (spi_nor_status() & RDSR_BUSY) {}
		
		if((callback) && (!(count % 0x1000)))
			callback(FLASH_PARTLY, 0, 0x1000);

	}
	
	WRITE_DISABLE();
	while (spi_nor_status() & RDSR_BUSY) {}

	if (WRITE_ENABLE() != 0) {
		return FLASH_ERROR_PROG;
	}
	
	if (len == 1) {
		/* need to do write-enable command only 1 byte left */
		if (spi_nor_program_1byte(s_buf[0], (void *)d_addr) != 0) {
			return FLASH_ERROR_PROG;
		}
		
		if(callback)
			callback(FLASH_PARTLY, 0, 1);
	}

	return 0;
}

int spi_nor_erase_block_sst(spi_flash_model *model, u32 address, u32 len, response_callback callback)
{
	u32 *cmd = (u32 *)g_tx_buf;
	u32 addr = address;
	u32 block_size = model->block_size;
	u32 chip_size = model->block_size * model->block_count;

	if (ENABLE_WRITE_STATUS() != 0 || spi_nor_write_status(0) != 0) {
		return FLASH_ERROR_ERASE;
	}

	if ((addr % block_size) || (addr + len > chip_size) || (addr > chip_size))
		return FLASH_ERROR_OVER_ADDR;
		
	while ((int)len > 0) {
	
		if (block_size == SZ_64K) {
			*cmd = (ERASE_64K << 24) | addr;
		} else if (block_size == SZ_32K) {
			*cmd = (ERASE_32K << 24) | addr;
		} else if (block_size == SZ_4K) {
			*cmd = (ERASE_4K << 24) | addr;
		} else {
			return FLASH_ERROR_ERASE;
		}
		
		/* need to do write-enable command */
		if (WRITE_ENABLE() != 0) {
			return FLASH_ERROR_ERASE;
		}

		/* now do the block erase */
		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (4 * 8)) != 0) {
			return FLASH_ERROR_ERASE;
		}

		while (spi_nor_status() & RDSR_BUSY) {}
		
		if (callback)
			callback(FLASH_ERASE, 0, block_size);
		
		len -= block_size;
		addr += block_size;
	}

	return 0;
}
int spi_nor_read_sst(spi_flash_model *model, u32 src, u32 dest, int len, dump_callback callback)
{
	u32 *cmd = (u32 *)g_tx_buf;
	u32 max_rx_sz = imx_spi_nor->fifo_sz - 4;
	u8 *d_buf = (u8 *) dest;
	u8 *s_buf;
	u16 csum;
	int i;

	*cmd = (READ << 24) | ((u32)src & 0x00FFFFFF);

	while (len) {
	
		if (len < max_rx_sz) {
			/* deal with the last round read */
			if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (len + 4) * 8) != 0)
				return FLASH_ERROR_READ;
		
			/* throw away 4 bytes (5th received bytes is real) */
			s_buf = g_rx_buf + 4;
		
			/* now adjust the endianness */
			for (i = len; i >= 0; i -= 4, s_buf += 4) {
				if (i < 4) {
					if (i == 1) {
						*d_buf = s_buf[0];
					} else if (i == 2) {
						*d_buf++ = s_buf[1];
						*d_buf++ = s_buf[0];
					} else if (i == 3) {
						*d_buf++ = s_buf[2];
						*d_buf++ = s_buf[1];
						*d_buf++ = s_buf[0];
					}
				
					/* send the dump status and data to host */
					if (callback) {
						csum = calculate_checksum((u8 *)dest, len);
						callback((u8 *)dest, FLASH_PARTLY, csum, len);
					}
				
					return 0;
				}
				/* copy 4 bytes */
				*d_buf++ = s_buf[3];
				*d_buf++ = s_buf[2];
				*d_buf++ = s_buf[1];
				*d_buf++ = s_buf[0];
			}
		}
		/* now grab max_rx_sz data (+4 is needed due to 4-throw away bytes */
		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (max_rx_sz + 4) * 8) != 0)
			return FLASH_ERROR_READ;
			
		/* throw away 4 bytes (5th received bytes is real) */	
		s_buf = g_rx_buf + 4;
		
		/* now adjust the endianness */
		for (i = 0; i < max_rx_sz; i += 4, s_buf += 4) {
		    *d_buf++ = s_buf[3];
		    *d_buf++ = s_buf[2];
		    *d_buf++ = s_buf[1];
		    *d_buf++ = s_buf[0];
		}
		
		/* send the dump status and data to host */
		if (callback) {
			csum = calculate_checksum((u8 *)dest, max_rx_sz);
			callback((u8 *)dest, FLASH_PARTLY, csum, max_rx_sz);
		}
		
		/* increase # of bytes in NOR address as cmd == g_tx_buf */
		*cmd += max_rx_sz;
		
		/* update bytes left */		
		len -= max_rx_sz;
		
		/* update the dest */
		dest += max_rx_sz;
	}
		
	return 0;
}
