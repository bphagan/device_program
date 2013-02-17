/*****************************************************************************
** spi_nor_mx53.h
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

#ifndef _SPI_NOR_MX53_H_
#define _SPI_NOR_MX53_H_

#define IOMUXC_BASE_ADDR	0x53fa8000
#define CSPI2_BASE_ADDR		0x63fac000
#define GPIO3_BASE_ADDR		0x53f8c000
#define CSPI1_BASE_ADDR		0x50010000

#define IMX_SPI_ACTIVE_HIGH		1
#define IMX_SPI_ACTIVE_LOW		0

struct spi_v2_3_reg spi_nor_reg;

void  mx53_spi_io_cfg_arm2(struct imx_spi_dev *dev)
{
	unsigned int reg;

	/* for babbage board */
	switch (dev->base) {
	case CSPI1_BASE_ADDR:
		 /* MOSI */
                __writel(0x04, IOMUXC_BASE_ADDR + 0x120);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x468);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x7A4);

                /* MISO */
                __writel(0x4, IOMUXC_BASE_ADDR + 0x11C);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x464);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x7A0);

                if (dev->ss == 0) {
                        /* de-select SS1 */
                        __writel(0x1, IOMUXC_BASE_ADDR + 0x124);
                        __writel(0x1E4, IOMUXC_BASE_ADDR + 0x46C);
                        
                        /* Select mux mode: ALT4 for SS0 */
                        __writel(0x4, IOMUXC_BASE_ADDR + 0x114);
                        __writel(0x104, IOMUXC_BASE_ADDR + 0x45C);
                        __writel(0x3, IOMUXC_BASE_ADDR + 0x7AC);
                } else if (dev->ss == 1) {
                        /* de-select SS0 */
                        __writel(0x1, IOMUXC_BASE_ADDR + 0x114);
                        __writel(0x1E4, IOMUXC_BASE_ADDR + 0x45C);
                        
                        /* Select mux mode: ALT4 for SS1 */
                        __writel(0x4, IOMUXC_BASE_ADDR + 0x124);
                        __writel(0x104, IOMUXC_BASE_ADDR + 0x46C);
                        __writel(0x2, IOMUXC_BASE_ADDR + 0x7AC);
                }
                
                /* SCLK */
                __writel(0x4, IOMUXC_BASE_ADDR + 0x118);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x460);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x79C);

		break;
	default:
		break;
	}

}

void mx53_spi_io_cfg_evk(struct imx_spi_dev *dev)
{
	/* for MX53 EVK board */
	switch (dev->base) {
	case CSPI1_BASE_ADDR:
		/* MOSI */
                __writel(0x04, IOMUXC_BASE_ADDR + 0x120);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x468);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x7A4);

                /* MISO */
                __writel(0x4, IOMUXC_BASE_ADDR + 0x11C);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x464);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x7A0);

                if (dev->ss == 0) {
                        /* de-select SS1 */
                        __writel(0x1, IOMUXC_BASE_ADDR + 0x124);
                        __writel(0x1E4, IOMUXC_BASE_ADDR + 0x46C);
                        
                        /* Select mux mode: ALT4 for SS0 */
                        __writel(0x4, IOMUXC_BASE_ADDR + 0x114);
                        __writel(0x104, IOMUXC_BASE_ADDR + 0x45C);
                        __writel(0x3, IOMUXC_BASE_ADDR + 0x7AC);
                } else if (dev->ss == 1) {
                        /* de-select SS0 */
                        __writel(0x1, IOMUXC_BASE_ADDR + 0x114);
                        __writel(0x1E4, IOMUXC_BASE_ADDR + 0x45C);
                        
                        /* Select mux mode: ALT4 for SS1 */
                        __writel(0x4, IOMUXC_BASE_ADDR + 0x124);
                        __writel(0x104, IOMUXC_BASE_ADDR + 0x46C);
                        __writel(0x2, IOMUXC_BASE_ADDR + 0x7AC);
                }
                
                /* SCLK */
                __writel(0x4, IOMUXC_BASE_ADDR + 0x118);
                __writel(0x104, IOMUXC_BASE_ADDR + 0x460);
                __writel(0x3, IOMUXC_BASE_ADDR + 0x79C);

		break;
	default:
		break;
	}

}

imx_spi_init_func_t *spi_nor_init = imx_spi_init_v2_3;
imx_spi_xfer_func_t *spi_nor_xfer = imx_spi_xfer_v2_3;

struct imx_spi_dev *imx_spi_nor;
struct imx_spi_dev imx_spi_nor_array[] = {
	/* for arm2 board */
	{
		base :	CSPI1_BASE_ADDR,
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
	mx53_spi_io_cfg_arm2,
	mx53_spi_io_cfg_evk
};

#endif /* _SPI_NOR_MX53_H_ */
