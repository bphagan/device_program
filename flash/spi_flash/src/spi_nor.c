/*****************************************************************************
** spi_nor.c
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

#include <type.h>
#include <stdlib.h>
#include <protocol.h>
#include <flash_lib.h>
#include <imx_spi.h>
#include <spi_nor.h>
#if defined(MCU_MX51)
#include <spi_nor_mx51.h>
#elif defined(MCU_MX53)
#include <spi_nor_mx53.h>
#endif

u8 g_tx_buf[256];
u8 g_rx_buf[256];

static imx_spi_write_func_t *spi_write_func = NULL;
static imx_spi_erase_func_t *spi_erase_func = NULL;
static imx_spi_read_func_t *spi_read_func = NULL;
static spi_flash_model *model = NULL;

extern void atk_response_send(u16 ack, u16 csum, u32 len);

void spi_norflash_query(void* data)
{
	u8 tmp[4];
	u8 *ptr = (u8 *)data;

	g_tx_buf[3] = JEDEC_ID;
	if (spi_nor_xfer(imx_spi_nor, g_tx_buf, tmp, (4 * 8)) != 0)
		return;

	ptr[0] = tmp[2];
	ptr[1] = tmp[1];
	ptr[2] = tmp[0];
}

/*!
 * Function to get the flash capacity
 * @param	[out] size - flash size
 */
s16 spi_flash_get_capacity(u32 *size)
{
	if (model)
		*size = ((model->block_size * model->block_count) >> 10);
		
	return 0;
}

void spi_flash_get_model(u8 *fmodel, u32 *len)
{
	int i;
	
	if (model) {
		for (i = 0; model->name[i] != '\0'; i++)
			fmodel[i] = model->name[i];
		*len = i;
	}
}

s16 spi_flash_compare(u32 src, u32 dest, u32 len,response_callback callback)
{
	/* send the verify status to host */
		if(callback != NULL)
			callback(FLASH_VERIFY, 0, len);
		
	return 0;
}

s16 spi_flash_init(void)
{
	u8 id[4] = {0};
	u32 i, j, k;

	
	for (k = 0; imx_spi_nor_array[k].base != 0 && !model; k++)  {
		
		imx_spi_nor = &imx_spi_nor_array[k];
		imx_spi_io_cfg = imx_spi_io_cfg_array[k];

		if (spi_nor_init(&imx_spi_nor_array[k]) != 0)
			return FLASH_ERROR_INIT;

		spi_norflash_query(id);
		for (j = 0; supported_model[j] != 0; j++) {
			for (i = 0; supported_model[j][i].name !=NULL; i++) {
				if ((supported_model[j][i].device_id1 == id[0]) &&
				    (supported_model[j][i].device_id2 == id[1]) &&
				    (supported_model[j][i].device_id3 == id[2])) {
					model = (spi_flash_model *)&supported_model[j][i];
					goto Found;
				}
			}
		}
		
	}
	
Found:
	/* find it? */
	if (!model)
		return FLASH_ERROR_INIT;
		
	switch (j) {
	
	case 0:
		spi_write_func = (imx_spi_write_func_t *)spi_nor_program_buf_sst;
		spi_erase_func = (imx_spi_erase_func_t *)spi_nor_erase_block_sst;
		spi_read_func = (imx_spi_read_func_t *)spi_nor_read_sst;
		
		break;
	case 1:
		spi_write_func = (imx_spi_write_func_t *)spi_nor_program_buf_atm;
		spi_erase_func = (imx_spi_erase_func_t *)spi_nor_erase_block_atm;
		spi_read_func = (imx_spi_read_func_t *)spi_nor_read_atm;
		
		break;
	default:
		return FLASH_ERROR_INIT;
		
		break;
	}
	
	return 0;
}

/*!
 * Read from SPI NOR at src address to RAM at dest with len bytes
 * @param   src     source address in the flash
 * @param   dest    destination address in the RAM
 * @param   len     # of bytes to copy
 */
int spi_flash_read(u32 src, u32 dest, u32 len, dump_callback callback)
{

	int ret = 0;
	
	if (!model)
		ret = FLASH_ERROR_INIT;
	else 
		ret = spi_read_func(model, src, dest, len, callback);
	
	return ret;
		
}

/*!
 * program data from RAM to flash
 * @param dest	destination address in flash
 * @param src	source address in RAM
 * @param len	# of bytes to program
 * Note: - when starting AAI programming,
 *       1) the starting addr has to be 16-bit aligned
 *       2) the prog len has to be even number of bytes
 */
int spi_flash_program(u32 dest, u32 src, u32 len, response_callback callback)
{
	int ret = 0;
	
	if (!model) {
		ret = FLASH_ERROR_INIT;
	} else {
		ret = spi_erase_func(model, dest, len, 0);
		
		if (ret == 0)
			ret = spi_write_func(model, dest, src, len, callback);
	}
	
	return ret;
}

/*!
 * Erase a variable bytes data from SPI NOR flash for 64K blocks
 * @param addr	starting addresss in the SPI NOR flash
 * @param len	# of bytes to erase
 */
int spi_flash_erase(u32 addr, u32 len, response_callback callback)
{
	int ret = 0;
    
	if (!model)
		ret = FLASH_ERROR_INIT;
	else 
		ret = spi_erase_func(model, addr, len, callback);
	
	return ret;
}
