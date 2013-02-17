/*****************************************************************************
** imx_spi.c
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

#include <imx_spi.h>
#include <type.h>

/*!
 * Initialization function for a spi slave device. It must be called BEFORE
 * any spi operations. The SPI module will be -disabled- after this call.
 */
int imx_spi_init_v2_3 (struct imx_spi_dev *dev)
{

	/*unsigned int clk_src = get_peri_clock(dev->base); */
	/*hard code */
	unsigned int clk_src = 600000000;
	unsigned int pre_div = 0, post_div = 0, i, reg_ctrl, reg_config;
	struct spi_v2_3_reg *reg = (struct spi_v2_3_reg *)dev->reg;

	if (dev->freq == 0) {
		return -1;
	}

	/* iomux config */
	imx_spi_io_cfg(dev);

	reg_ctrl = __readl(dev->base + 0x8);

	/* reset the spi */
	__writel(0, dev->base + 0x8);
	__writel(reg_ctrl | 0x1, dev->base + 0x8);

	/* control clock setup */
	if (clk_src > dev->freq) {
		pre_div = clk_src / dev->freq;
		if (pre_div > 16) {
		    post_div = pre_div / 16;
		    pre_div = 15;
		}
		if (post_div != 0) {
		    for (i = 0; i < 16; i++) {
			if ((1 << i) >= post_div)
			    break;
		    }
		    if (i == 16) {
			return -1;
		    }
		    post_div = i;
		}
	}

	/* control register setup */
	reg_ctrl = (reg_ctrl & ~(3 << 18)) | dev->ss << 18;
	reg_ctrl = (reg_ctrl & ~(0xF << 12)) | pre_div << 12;
	reg_ctrl = (reg_ctrl & ~(0xF << 8)) | post_div << 8;
	reg_ctrl |= 1 << (dev->ss + 4);
	reg_ctrl &= ~0x1;

	/* configuration register setup */
	reg_config = __readl(dev->base + 0xC);
	reg_config = (reg_config & ~(1 << ((dev->ss + 12)))) |
			(dev->ss_pol << (dev->ss + 12));
	reg_config = (reg_config & ~(1 << ((dev->ss + 20)))) |
			(dev->in_sctl << (dev->ss + 20));
	reg_config = (reg_config & ~(1 << ((dev->ss + 16)))) |
			(dev->in_dctl << (dev->ss + 16));
	reg_config = (reg_config & ~(1 << ((dev->ss + 8)))) |
			(dev->ssctl << (dev->ss + 8));
	reg_config = (reg_config & ~(1 << ((dev->ss + 4)))) |
			(dev->sclkpol << (dev->ss + 4));
	reg_config = (reg_config & ~(1 << ((dev->ss + 0)))) |
			(dev->sclkpha << (dev->ss + 0));

	__writel(reg_ctrl, dev->base + 0x8);
	__writel(reg_config, dev->base + 0xC);

	/* update register */
	reg->cfg_reg = reg_config;
	reg->ctrl_reg = reg_ctrl;

	/* clear interrupt reg */
	__writel(0, dev->base + 0x10);
	__writel(3 << 6, dev->base + 0x18);

	return 0;
}

/*!
 * This function should only be called after the imx_spi_init_xxx().
 * It sets up the spi module according to the initialized value and then
 * enables the SPI module. This function is called by the xfer function.
 *
 * Note: If one wants to change the SPI parameters such as clock, the
 *       imx_spi_init_xxx() needs to be called again.
 */
static void spi_start_v2_3(struct imx_spi_dev *dev,
                           struct spi_v2_3_reg *reg, int len)
{
	if (reg->ctrl_reg == 0)
		return;

	/* iomux config */
	imx_spi_io_cfg(dev);

	reg->ctrl_reg = (reg->ctrl_reg & ~0xFFF00000) | ((len - 1) << 20);

	__writel(reg->ctrl_reg | 0x1, dev->base + 0x8);
	__writel(reg->cfg_reg, dev->base + 0xC);

}

/*!
 * Stop the SPI module that the slave device is connected to.
 */
static void  spi_stop_v2_3(struct imx_spi_dev *dev)
{
    __writel(0, dev->base + 0x8);
}

/*!
 * Transfer up to burst_bytes bytes data via spi. The amount of data
 * is the sum of both the tx and rx.
 * After this call, the SPI module that the slave is connected to will
 * be -disabled- again.
 */
int imx_spi_xfer_v2_3 (struct imx_spi_dev *dev,
			unsigned char *tx_buf,
			unsigned char *rx_buf,
			int burst_bits)
{
	unsigned int *p_buf;
	unsigned int reg;
	int len, ret_val = 0;
	int burst_bytes = burst_bits / 8;

	/* Account for rounding of non-byte aligned burst sizes */
	if ((burst_bits % 8) != 0)
		burst_bytes++;

	if (burst_bytes  > dev->fifo_sz)
		return -1;

	spi_start_v2_3(dev, dev->reg, burst_bits);

	/* move data to the tx fifo */
	for (p_buf = (unsigned int *)tx_buf, len = burst_bytes;
		len > 0; p_buf++, len -= 4) {
		__writel(*p_buf, dev->base + 0x4);
	}

	/* set xch bit */
	reg = __readl(dev->base + 0x8);
	reg |= (1 << 2);
	__writel(reg, dev->base + 0x8);

	/* poll on the TC bit */
	while ((__readl(dev->base + 0x18) & (1 << 7)) == 0);

	/* clear the TC bit */
	__writel(3 << 6, dev->base + 0x18);

	/* get data from rx fifo*/
	for (p_buf = (unsigned int *)rx_buf, len = burst_bytes;
		len > 0; p_buf++, len -= 4) {
		*p_buf = __readl(dev->base + 0x0);
	}

	spi_stop_v2_3(dev);

	return ret_val;
}
