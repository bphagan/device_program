/*****************************************************************************
** spi_nor_atmel.c
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

static int spi_nor_status_atm(void)
{
	g_tx_buf[1] = STAT_READ;
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (2 * 8)) != 0) {
		return 0;
	}
	return g_rx_buf[0];
}

int spi_nor_program_buf_atm(spi_flash_model *model, u32 dest, u32 src, int len, response_callback callback)
{
	u32 d_addr = dest;
	u8 *s_buf = (u8 *)src;
	u32 final_addr = 0;
	int page_size = 528, trans_bytes = 0, buf_ptr = 0, bytes_sent = 0, byte_sent_per_iter = 0;
	int page_no = 0, buf_addr = 0, page_off = 0, i = 0, j = 0, k = 0, fifo_size = 32;
	int remain_len = 0;

	/* Read the status register to get the Page size */
	if (spi_nor_status_atm() & STAT_PG_SZ) {
		page_size = 512;
	} else {
		g_tx_buf[0] = CONFIG_REG4;
		g_tx_buf[1] = CONFIG_REG3;
		g_tx_buf[2] = CONFIG_REG2;
		g_tx_buf[3] = CONFIG_REG1;

		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (4 * 8)) != 0) {
			return FLASH_ERROR_PROG;
		}

		while (!(spi_nor_status_atm() & STAT_BUSY)) {}
	
		return FLASH_ERROR_PROG;
	}

	/* Due to the way CSPI operates send data less that 4 bytes in a different manner */
	remain_len = len % 4;
	if (remain_len)
		len -= remain_len;

	while (1) {
		page_no = d_addr / page_size;
		/* Get the offset within the page if address is not page-aligned */
		if ((page_off = (d_addr % page_size))) {
			if (page_no == 0) {
				buf_addr = d_addr;
			} else {
				buf_addr = page_off;
			}
			trans_bytes = page_size - buf_addr;
		} else {
			buf_addr = 0;
			trans_bytes = page_size;
		}

		if (len <=0)
			break;

		if (trans_bytes > len)
			trans_bytes = len;

		bytes_sent = trans_bytes;
		/* Write the data to the SPI-NOR Buffer first */
		while (trans_bytes > 0) {
			final_addr = (buf_addr & 0x3FF);
			g_tx_buf[0] = final_addr;
			g_tx_buf[1] = final_addr >> 8;
			g_tx_buf[2] = final_addr >> 16;
			g_tx_buf[3] = BUF1_WR; /*Opcode */

			/* 4 bytes already used for Opcode & address bytes,
			check to ensure we do not overflow the SPI TX buffer */
			if (trans_bytes > (fifo_size - 4))
				byte_sent_per_iter = fifo_size;
			else
				byte_sent_per_iter = trans_bytes + 4;

			for (i = 4; i < byte_sent_per_iter; i += 4) {
				g_tx_buf[i + 3] = s_buf[buf_ptr++];
				g_tx_buf[i + 2] = s_buf[buf_ptr++];
				g_tx_buf[i + 1] = s_buf[buf_ptr++];
				g_tx_buf[i] = s_buf[buf_ptr++];
			}
			if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (byte_sent_per_iter * 8)) != 0) {

				return FLASH_ERROR_PROG;
			}

			while (!(spi_nor_status_atm() & STAT_BUSY)) {}

			/* Deduct 4 bytes as it is used for Opcode & address bytes */
			trans_bytes -= (byte_sent_per_iter - 4);
			/* Update the destination buffer address */
			buf_addr += (byte_sent_per_iter - 4);
		}

		/* Send the command to write data from the SPI-NOR Buffer to Flash memory */
		if (page_size == 512) {
			final_addr = (page_no & 0x1FFF) << 9;
		} else {
			final_addr = (page_no & 0x1FFF) << 10;
		}

		/* Specify the Page address in Flash where the data should be written to */
		g_tx_buf[0] = final_addr;
		g_tx_buf[1] = final_addr >> 8;
		g_tx_buf[2] = final_addr >> 16;
		g_tx_buf[3] = BUF1_TO_MEM; /*Opcode */
		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (4 * 8)) != 0) {
			return FLASH_ERROR_PROG;
		}

		while (!(spi_nor_status_atm() & STAT_BUSY)) {}
		
		/* send the prg status to host */
		if(callback)
			callback(FLASH_PARTLY, 0, bytes_sent);

		d_addr += bytes_sent;
		len -= bytes_sent;
	}

	if (remain_len) {
		buf_ptr += remain_len;
		/* Write the remaining data bytes first */
		for (i = 0; i < remain_len; i++) {
			g_tx_buf[i] = s_buf[buf_ptr--];
		}
		/* Write the address bytes next in the same word as the data byte from the next byte */
		for (j = i, k = 0; j < 4; j++, k++) {
			g_tx_buf[j] = final_addr >> (k * 8);
		}
		/* Write the remaining address bytes in the next word */
		j = 0;
		final_addr = (buf_addr & 0x3FF);

		for (j = 0; k < 3; j++, k++) {
			g_tx_buf[j] = final_addr >> (k * 8);
		}
		/* Finally the Opcode to write the data to the buffer */
		g_tx_buf[j] = BUF1_WR; /*Opcode */

		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (remain_len + 4) * 8) != 0) {
		
			return FLASH_ERROR_PROG;
		}

		while (!(spi_nor_status_atm() & STAT_BUSY)) {}

		if (page_size == 512) {
			final_addr = (page_no & 0x1FFF) << 9;
		} else {
			final_addr = (page_no & 0x1FFF) << 10;
		}

		g_tx_buf[0] = final_addr;
		g_tx_buf[1] = final_addr >> 8;
		g_tx_buf[2] = final_addr >> 16;
		g_tx_buf[3] = BUF1_TO_MEM; /*Opcode */
		if (spi_nor_xfer(imx_spi_nor, g_tx_buf, g_rx_buf, (4 * 8)) != 0) {
			return FLASH_ERROR_PROG;
		}

		while (!(spi_nor_status_atm() & STAT_BUSY)) {}
		
		/* send the prg status to host */
		if(callback)
			callback(FLASH_PARTLY, 0, remain_len);

	}

	return 0;
}

int spi_nor_erase_block_atm(spi_flash_model *model, u32 address, u32 size, response_callback callback)
{
	/* Erase not implemented, the write command has a built-in erase */
	return 0;
}
int spi_nor_read_atm(spi_flash_model *model, u32 src, u32 dest, int len, dump_callback callback)
{
	u32 *cmd = (u32 *)g_tx_buf;
	u32 max_rx_sz = imx_spi_nor->fifo_sz - 4;
	u8 *d_buf = (u8 *)dest;
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
