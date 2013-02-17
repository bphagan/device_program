/*****************************************************************************
** board_evk.c
**
** Copyright 2010 Freescale Semiconductor, Inc. All Rights Reserved.
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

/*!
 * @file board_evk.c
 *
 * @brief the platform specific functions file
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include <mx53.h>
#include <mx53_pins.h>
#include <type.h>
#include <iomux.h>

u32 *imx_esdhc_base_addr;

int esdhc_gpio_init(void)
{
	u32 interface_esdhc = 0;
	s32 status = 0;
	uint soc_sbmr = __readl(SRC_BASE_ADDR + 0x4);

	interface_esdhc = (soc_sbmr & (0x00300000)) >> 20;

	switch (interface_esdhc) {
	case 0:
		imx_esdhc_base_addr = (u32 *)MMC_SDHC1_BASE_ADDR;

		mxc_request_iomux(MX53_PIN_SD1_CMD, IOMUX_CONFIG_ALT0);
		mxc_request_iomux(MX53_PIN_SD1_CLK, IOMUX_CONFIG_ALT0);
		mxc_request_iomux(MX53_PIN_SD1_DATA0, IOMUX_CONFIG_ALT0);
		mxc_request_iomux(MX53_PIN_SD1_DATA1, IOMUX_CONFIG_ALT0);
		mxc_request_iomux(MX53_PIN_SD1_DATA2, IOMUX_CONFIG_ALT0);
		mxc_request_iomux(MX53_PIN_SD1_DATA3, IOMUX_CONFIG_ALT0);

		mxc_iomux_set_pad(MX53_PIN_SD1_CMD, 0x1E4);
		mxc_iomux_set_pad(MX53_PIN_SD1_CLK, 0xD4);
		mxc_iomux_set_pad(MX53_PIN_SD1_DATA0, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_SD1_DATA1, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_SD1_DATA2, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_SD1_DATA3, 0x1D4);
		break;
	case 2:
		imx_esdhc_base_addr = (u32 *)MMC_SDHC3_BASE_ADDR;

		mxc_request_iomux(MX53_PIN_ATA_RESET_B, IOMUX_CONFIG_ALT2);
		mxc_request_iomux(MX53_PIN_ATA_IORDY, IOMUX_CONFIG_ALT2);
		mxc_request_iomux(MX53_PIN_ATA_DATA8, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA9, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA10, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA11, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA0, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA1, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA2, IOMUX_CONFIG_ALT4);
		mxc_request_iomux(MX53_PIN_ATA_DATA3, IOMUX_CONFIG_ALT4);

		mxc_iomux_set_pad(MX53_PIN_ATA_RESET_B, 0x1E4);
		mxc_iomux_set_pad(MX53_PIN_ATA_IORDY, 0xD4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA8, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA9, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA10, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA11, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA0, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA1, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA2, 0x1D4);
		mxc_iomux_set_pad(MX53_PIN_ATA_DATA3, 0x1D4);

		break;
	default:
		status = -1;
		break;
	}

	return status;
}

extern int fsl_esdhc_mmc_init(void);

int board_mmc_init(void)
{
	if (!esdhc_gpio_init())
		return fsl_esdhc_mmc_init();
	else
		return -1;
}
