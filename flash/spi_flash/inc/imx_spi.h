/*****************************************************************************
** imx_spi.h
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
#ifndef __IMX_SPI_H__
#define __IMX_SPI_H__

/* Only for SPI master support */
struct imx_spi_dev {
	unsigned int base;	/* base address of SPI module */
	unsigned int freq;	/* desired clock freq in Hz for this device */
	unsigned int ss_pol;	/* ss polarity: 1=active high; 0=active low */
	unsigned int ss;       	/* slave select */
	unsigned int in_sctl;  	/* inactive sclk ctl: 1=stay low; 0=stay high */
	unsigned int in_dctl;  	/* inactive data ctl: 1=stay low; 0=stay high */
	unsigned int ssctl;    	/* burst mode: 0=single; 1=multi */
	unsigned int sclkpol;  	/* sclk polarity: active high=0; active low=1 */
	unsigned int sclkpha;	/* sclk phase: 0=phase 0; 1=phase1 */
	unsigned int fifo_sz; 	/* fifo size in bytes for either tx or rx */
	void *reg;			/* pointer to a set of SPI registers */
};

struct spi_v2_3_reg {
	unsigned int ctrl_reg;
	unsigned int cfg_reg;
};

/* setup IOMUX for the spi device */
int imx_spi_init_v2_3 (
	struct imx_spi_dev *dev
);

/* transfer up to fifo bytes data via spi. 
 * The data transferred is the sum of both 
 * the tx and rx
 */  
int imx_spi_xfer_v2_3 (
	struct imx_spi_dev *dev,    /* spi device pointer */
	unsigned char *tx_buf,      /* tx buffer (has to be 4-byte aligned) */
	unsigned char *rx_buf,      /* rx buffer (has to be 4-byte aligned) */
	int burst_bytes             /* total number of bytes in one burst or xfer */
);

typedef int imx_spi_init_func_t(
	struct imx_spi_dev *
);

typedef int imx_spi_xfer_func_t(
	struct imx_spi_dev *, 
	unsigned char *, 
	unsigned char *, int
);


typedef void imx_spi_io_cfg_func_t(
	struct imx_spi_dev *
);

extern imx_spi_io_cfg_func_t *imx_spi_io_cfg;

#endif // __IMX_SPI_H__

