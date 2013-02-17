/*****************************************************************************
** spi_nor_mx51.h
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

#ifndef _SPI_NOR_MX51_H_
#define _SPI_NOR_MX51_H_

#define IOMUXC_BASE_ADDR	0x73fa8000
#define CSPI2_BASE_ADDR		0x83fac000
#define GPIO3_BASE_ADDR		0x73f8c000
#define CSPI1_BASE_ADDR		0x70010000

#define IMX_SPI_ACTIVE_HIGH		1
#define IMX_SPI_ACTIVE_LOW		0

struct spi_v2_3_reg spi_nor_reg;

void  mx51_spi_io_cfg_3stack(struct imx_spi_dev *dev)
{
	unsigned int reg;

	/* for babbage board */
	switch (dev->base) {
	case CSPI2_BASE_ADDR:
		 /* ALT2 : MOSI : ecspi2 */
		__writel(0x2, IOMUXC_BASE_ADDR + 0x154);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x53C);

		/* ALT2 : MISO : ecspi2 */
		__writel(0x2, IOMUXC_BASE_ADDR + 0x128);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x504);

		/*  de-select SS0 of instance: ecspi1 */
		__writel(0x2, IOMUXC_BASE_ADDR + 0x298);
		__writel(0x85, IOMUXC_BASE_ADDR + 0x698);
		
		/* ALT2 : SS1 : ecspi2 */
		__writel(0x2, IOMUXC_BASE_ADDR + 0x160);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x548);

		/* ALT3 : GPIO mode */
		__writel(0x3, IOMUXC_BASE_ADDR + 0x150);
		__writel(0xE0, IOMUXC_BASE_ADDR + 0x538);
		
		reg = __readl(GPIO3_BASE_ADDR + 0x0);
		reg |= 0x1000000;  /* write a 1 */
		__writel(reg, GPIO3_BASE_ADDR + 0x0);
		
		reg = __readl(GPIO3_BASE_ADDR + 0x4);
		reg |= 0x1000000;  /* configure GPIO lines as output */
		__writel(reg, GPIO3_BASE_ADDR + 0x4);

		/* ALT2 : SCLK : ecspi2 */
		__writel(0x2, IOMUXC_BASE_ADDR + 0x124);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x500);

		break;
	default:
		break;
	}

}

void mx51_spi_io_cfg_evk(struct imx_spi_dev *dev)
{
	/* for babbage board */
	switch (dev->base) {
	case CSPI1_BASE_ADDR:
		/* ALT0: MOSI: ecspi1 */
		__writel(0x0, IOMUXC_BASE_ADDR + 0x210);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x600);

		/* ALT0: MISO: ecspi1 */
		__writel(0x0, IOMUXC_BASE_ADDR + 0x214);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x604);

		if (dev->ss == 0) {
			/* de-select SS1 of instance: ecspi1 */
			__writel(0x3, IOMUXC_BASE_ADDR + 0x21C);
			__writel(0x85, IOMUXC_BASE_ADDR + 0x60C);

			/* ALT0: SS0: ecspi1 */
			__writel(0x0, IOMUXC_BASE_ADDR + 0x218);
			__writel(0x185, IOMUXC_BASE_ADDR + 0x608);
		} else if (dev->ss == 1) {
			/* de-select SS0 of instance: ecspi1 */
			__writel(0x3, IOMUXC_BASE_ADDR + 0x218);
			__writel(0x85, IOMUXC_BASE_ADDR + 0x608);

			/* ALT0: SS1: ecspi1 */
			__writel(0x0, IOMUXC_BASE_ADDR + 0x21C);
			__writel(0x105, IOMUXC_BASE_ADDR + 0x60C);
		}

		/* ALT0: RDY: ecspi1 */
		__writel(0x0, IOMUXC_BASE_ADDR + 0x220);
		__writel(0x180, IOMUXC_BASE_ADDR + 0x610);

		/* ALT0: SCLK: ecspi1 */
		__writel(0x0, IOMUXC_BASE_ADDR + 0x224);
		__writel(0x105, IOMUXC_BASE_ADDR + 0x614);

		break;
	default:
		break;
	}

}

imx_spi_init_func_t *spi_nor_init = imx_spi_init_v2_3;
imx_spi_xfer_func_t *spi_nor_xfer = imx_spi_xfer_v2_3;

struct imx_spi_dev *imx_spi_nor;
struct imx_spi_dev imx_spi_nor_array[] = {
	/* for 3stack board */
	{
		base :	CSPI2_BASE_ADDR,
		freq :	25000000,
		ss_pol : 	IMX_SPI_ACTIVE_LOW,
		ss : 		1,  /* slave select 1 */
		fifo_sz :	32,
		reg :		&spi_nor_reg,
	},
	 
	/* for evk board */
	{
		base :	CSPI1_BASE_ADDR,
		freq :	25000000,
		ss_pol : 	IMX_SPI_ACTIVE_LOW,
		ss : 		1,  /* slave select 1 */
		fifo_sz :	32,
		reg :		&spi_nor_reg,
	},
	
	{ 0 },
 
};

imx_spi_io_cfg_func_t* imx_spi_io_cfg;

imx_spi_io_cfg_func_t  *imx_spi_io_cfg_array[] = {
	mx51_spi_io_cfg_3stack,
	mx51_spi_io_cfg_evk
};

#endif /* _SPI_NOR_MX51_H_ */
