/*
 * Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "nand_device_info.h"

/*
 * Type 2
 */
static struct nand_device_info nand_device_info_table_type_2[] =
{	
	{
	.end_of_table             = false,
	.man_id			  = 0x20,
	.dev_id			  = 0x76,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 64LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "NAND512W3",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x75,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 32LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9F5608U0D",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x45,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 32LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 11,
	.bbi_page_offset          = 0,
	.bus_width		  = 16,
	.scan_pg_num              = 1,
	.model			  = "K9F5608U0D",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x76,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 64LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9F1208U0M",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x36,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 64LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9K1208Q0C",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x79,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9K1G08U0B",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0x98,
	.dev_id			  = 0x79,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58DVG02A1FT00",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x78,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9K1G08U0B",
	},
	{
	.end_of_table             = false,
	.man_id			  = 0x20,
	.dev_id			  = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.ppb      		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "NAND01GW3",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xad,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb      		  = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Hynix",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0x2c,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Micron",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xec,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model                    = "K9F1F08",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb      		  = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG0S3",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model                    = "Sandisk",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x20,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "NAND02GW3",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model 			  = "HY27UF082G2M, HY27UG082G2M, HY27UG082G1M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F2G08",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9F2G08U0M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xaa,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9F2G08R0A",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0x98,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG1S3",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x20,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "ST Micro",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xad,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "HY27UH084G2M, HY27UG084G2M, HY27UH084G1M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F4G08",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xec,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sumsung",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TH58NVG2S3",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "HY27UH088G2M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x20,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb      		  = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "NAND08GW3BxANx",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F8G08FABWG",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Toshiba",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x20,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "ST Micro",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Hynix",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Micron",
	},
	{true}
};

/*
 * Large MLC
 */
static struct nand_device_info nand_device_info_table_large_mlc[] =
{
	{
	.end_of_table             = false,
	.man_id			  = 0xec,
	.dev_id			  = 0x76,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 64LL*SZ_1M,
	.page_size		  = 512,
	.oob_size		  = 16,
	.ppb      		  = 32,
	.bbm_offset		  = 5,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9F1208U0M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG1D4BFT00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk MLC",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk MLC",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TH58NVG3D4xFT00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk MLC",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TH58NVG4D4xFT00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x45,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "Sandisk MLC",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG2D4BFT00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9G4G08U0M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "HY27UT084G2M, HY27UU088G5M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x20,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "NAND04GW3C2AN1E",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9G8G08U0M, K9HAG08U1M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "HY27UV08AG5M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = 
	"Intel JS29F08G08AAMiB1 and Micron MT29F8G08MAA; "
	"Intel JS29F08G08CAMiB1 and Micron MT29F16G08QAA",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9LAG08U0M K9HBG08U1M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "Intel JS29F32G08FAMiB1 and Micron MT29F32G08TAA",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "MT29F4G08",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x89,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "JS29F08G08AAMiB2, JS29F08G08CAMiB2",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x89,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "JS29F32G08FAMiB2",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "HY27UW08CGFM",
	},
	{true}
};

/*
 * Type 7
 */
static struct nand_device_info nand_device_info_table_type_7[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F8G08FABWG",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F4G08AAA",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xdc,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 512LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9F4G08",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9K8G08UXM, K9NBG08U5A, K9WAG08U1A",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9WAG08UXM",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xec,
	.dev_id                   = 0xda,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 256LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9F2G08U0A",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xf1,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 128LL*SZ_1M,
	.ppb                      = 64,
	.page_size		  = 2*SZ_1K,
	.oob_size		  = 64,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9F1F08",
	},
	{true}
};

/*
 * Type 8
 */
static struct nand_device_info nand_device_info_table_type_8[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9GAG08U0M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb      		  = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = 
	"K9LBG08U0M (32Gb), K9HCG08U1M (64Gb), K9MDG08U5M (128Gb)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "H27UAG, H27UBG",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "H27UCG",
	},
	{true}
};

/*
 * Type 9
 */
static struct nand_device_info nand_device_info_table_type_9[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG3D1DTG00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb      		  = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG4D1DTG00",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TH58NVG6D1DTG20",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x89,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "JS29F16G08AAMC1, JS29F32G08CAMC1",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "MT29F16G08MAA, MT29F32G08QAA",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb      		  = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = 
	"MT29F64G08TAA (32Gb), MT29F32G08CBAAA (32Gb) MT29F64G08CFAAA (64Gb)",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0x2c,
	.dev_id                   = 0xd9,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 8LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "MT29F128G08CJAAA",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x89,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "JSF64G08FAMC1",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9LBG08U0D",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "K9GAG08U0D, K9LBG08U1D, K9HCG08U5D",
	},
	{true}
};

/*
 * Type 10
 */
static struct nand_device_info nand_device_info_table_type_10[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd3,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 1LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "Sumsung SLC",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd5,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9NCG08U5M",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_SLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 64,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 128,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "Sumsung SLC",
	},
	{true}
};

/*
 * Type 11
 */
static struct nand_device_info nand_device_info_table_type_11[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 8*SZ_1K,
	.oob_size		  = 376,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TC58NVG5D2ELAM8 (4GB), TH58NVG6D2ELAM8 (8GB)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x98,
	.dev_id                   = 0xde,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 8LL*SZ_1G,
	.ppb      		  = 128,
	.page_size		  = 8*SZ_1K,
	.oob_size		  = 376,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 127,
	.bus_width		  = 8,
	.scan_pg_num              = 1,
	.model			  = "TH58NVG7D2ELAM8",
	},
	{true}
};

/*
 * Type 15
 */
static struct nand_device_info nand_device_info_table_type_15[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0xec,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 8*SZ_1K,
	.oob_size		  = 512,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "K9GBGD8U0M, K9GBGD8S0M",
	},
	{true}
};

/*
 * BCH ECC12
 */
static struct nand_device_info nand_device_info_table_bch_ecc12[] =
{
	{
	.end_of_table             = false,
	.man_id                   = 0xad,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb      		  = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 224,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = 
	"H27UBG8T2M (4GB, 1CE), H27UCG8UDM (8GB, 2CE), H27UDG8VEM (16GB, 4CE)",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0xad,
	.dev_id                   = 0xde,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 8LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 224,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 126,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "H27UEG8YEM (32GB, 4CE)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0xd7,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = 
	"MT29F32G08CBAAA (4GB, 1CE), MT29F64G08CFAAA (8GB, 2CE)",
	},
	{
	.end_of_table             = false,
	.man_id        		  = 0x2c,
	.dev_id                   = 0xd9,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 8LL*SZ_1G,
	.ppb                      = 128,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 218,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "MT29F128G08CJAAA (16GB, 2CE)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0x48,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 2LL*SZ_1G,
	.ppb                      = 256,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 224,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = "MT29F16G08CBABA (2GB, 1CE)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0x68,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 4LL*SZ_1G,
	.ppb                      = 256,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 224,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = 
	"MT29F32G08CBABA (4GB, 1CE); "
	"MT29F64G08CEABA (8GB, 2CE); "
	"MT29F64G08CFABA (8GB, 2CE)",
	},
	{
	.end_of_table             = false,
	.man_id                   = 0x2c,
	.dev_id                   = 0x88,
	.cell_type                = NAND_DEVICE_CELL_TECH_MLC,
	.chip_size_in_bytes       = 8LL*SZ_1G,
	.ppb                      = 256,
	.page_size		  = 4*SZ_1K,
	.oob_size		  = 224,
	.bbm_offset		  = 0,
	.bbi_page_offset          = 0,
	.bus_width		  = 8,
	.scan_pg_num              = 2,
	.model			  = 
	"MT29F128G08CJABA (16GB, 2CE); "
	"MT29F128G08CKABA (16GB, 2CE); "
	"MT29F256G08CUABA (32GB, 4CE)",
	},
	{true}
};

/*
 * The following macros make it convenient to extract information from an ID
 * byte array. All these macros begin with the prefix "ID_".
 *
 * Macros of the form:
 *
 *         ID_GET_[<manufacturer>_[<modifier>_]]<field>
 *
 * extract the given field from an ID byte array. Macros of the form:
 *
 *         ID_[<manufacturer>_[<modifier>_]]<field>_<meaning>
 *
 * contain the value for the given field that has the given meaning.
 *
 * If the <manufacturer> appears, it means this macro represents a view of this
 * field that is specific to the given manufacturer.
 *
 * If the <modifier> appears, it means this macro represents a view of this
 * field that the given manufacturer applies only under specific conditions.
 *
 * Here is a simple example:
 *
 *         ID_PAGE_SIZE_CODE_2K
 *
 * This macro has the value of the "Page Size" field that indicates the page
 * size is 2K.
 *
 * A more complicated example:
 *
 *         ID_SAMSUNG_6_BYTE_PAGE_SIZE_CODE_8K  (0x2)
 *
 * This macro has the value of the "Page Size" field for Samsung parts that
 * indicates the page size is 8K. However, this interpretation is only correct
 * for devices that return 6 ID bytes.
 */

/* Byte 1 ------------------------------------------------------------------- */

#define ID_GET_BYTE_1(id)    ((id)[0])

#define ID_GET_MFR_CODE(id)  ID_GET_BYTE_1(id)

/* Byte 2 ------------------------------------------------------------------- */

#define ID_GET_BYTE_2(id)                      ((id)[1])

#define ID_GET_dev_id(id)                      ID_GET_BYTE_2(id)
    #define ID_SAMSUNG_dev_id_1_GBIT           (0xf1)
    #define ID_SAMSUNG_dev_id_2_GBIT           (0xda)
    #define ID_HYNIX_dev_id_ECC12              (0xd7)
    #define ID_HYNIX_dev_id_ECC12_LARGE        (0xde)
    #define ID_MICRON_dev_id_ECC12             (0xd7) /* ECC12        */
    #define ID_MICRON_dev_id_ECC12_LARGE       (0xd9) /* ECC12 8GB/CE */
    #define ID_MICRON_dev_id_ECC12_2GB_PER_CE  (0x48) /* L63B  2GB/CE */
    #define ID_MICRON_dev_id_ECC12_4GB_PER_CE  (0x68) /* L63B  4GB/CE */
    #define ID_MICRON_dev_id_ECC12_8GB_PER_CE  (0x88) /* L63B  8GB/CE */

/* Byte 3 ------------------------------------------------------------------- */

#define ID_GET_BYTE_3(id)               ((id)[2])

#define ID_GET_DIE_COUNT_CODE(id)       ((ID_GET_BYTE_3(id) >> 0) & 0x3)

#define ID_GET_CELL_TYPE_CODE(id)       ((ID_GET_BYTE_3(id) >> 2) & 0x3)
    #define ID_CELL_TYPE_CODE_SLC       (0x0) /* All others => MLC. */

#define ID_GET_SAMSUNG_SIMUL_PROG(id)   ((ID_GET_BYTE_3(id) >> 4) & 0x3)

#define ID_GET_MICRON_SIMUL_PROG(id)    ((ID_GET_BYTE_3(id) >> 4) & 0x3)

#define ID_GET_CACHE_PROGRAM(id)        ((ID_GET_BYTE_3(id) >> 7) & 0x1)

/* Byte 4 ------------------------------------------------------------------- */

#define ID_GET_BYTE_4(id)                       ((id)[3])
    #define ID_HYNIX_BYTE_4_ECC12_DEVICE        (0x25)

#define ID_GET_PAGE_SIZE_CODE(id)               ((ID_GET_BYTE_4(id) >> 0) & 0x3)
    #define ID_PAGE_SIZE_CODE_1K                (0x0)
    #define ID_PAGE_SIZE_CODE_2K                (0x1)
    #define ID_PAGE_SIZE_CODE_4K                (0x2)
    #define ID_PAGE_SIZE_CODE_8K                (0x3)
    #define ID_SAMSUNG_6_BYTE_PAGE_SIZE_CODE_8K (0x2)

#define ID_GET_OOB_SIZE_CODE(id)                ((ID_GET_BYTE_4(id) >> 2) & 0x1)

#define ID_GET_BLOCK_SIZE_CODE(id)              ((ID_GET_BYTE_4(id) >> 4) & 0x3)

/* Byte 5 ------------------------------------------------------------------- */

#define ID_GET_BYTE_5(id)                  ((id)[4])
    #define ID_MICRON_BYTE_5_ECC12         (0x84)

#define ID_GET_SAMSUNG_ECC_LEVEL_CODE(id)  ((ID_GET_BYTE_5(id) >> 4) & 0x7)
    #define ID_SAMSUNG_ECC_LEVEL_CODE_8    (0x03)
    #define ID_SAMSUNG_ECC_LEVEL_CODE_24   (0x05)

#define ID_GET_PLANE_COUNT_CODE(id)        ((ID_GET_BYTE_5(id) >> 2) & 0x3)

/* Byte 6 ------------------------------------------------------------------- */

#define ID_GET_BYTE_6(id)                        ((id)[5])
    #define ID_TOSHIBA_BYTE_6_PAGE_SIZE_CODE_8K  (0x54)
    #define ID_TOSHIBA_BYTE_6_PAGE_SIZE_CODE_4K  (0x13)

#define ID_GET_SAMSUNG_DEVICE_VERSION_CODE(id)   ((ID_GET_BYTE_6(id)>>0) & 0x7)
    #define ID_SAMSUNG_DEVICE_VERSION_CODE_40NM  (0x01)

static struct nand_device_info *nand_device_info_search(
	struct nand_device_info *table, u8 mfr_code, u8 dev_id)
{

	for (; !table->end_of_table; table++) {
		if (table->man_id != mfr_code)
			continue;
		if (table->dev_id != dev_id)
			continue;
		return table;
	}

	return 0;

}

static struct nand_device_info *nand_device_info_fn_toshiba(const u8 id[])
{
	struct nand_device_info  *table;

	/* Check for an SLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) == ID_CELL_TYPE_CODE_SLC) {
		/* Type 2 */
		return nand_device_info_search(nand_device_info_table_type_2,
				ID_GET_MFR_CODE(id), ID_GET_dev_id(id));
	}

	/*
	 * Look for 8K page Toshiba MLC devices.
	 *
	 * The page size field in byte 4 can't be used because the field was
	 * redefined in the 8K parts so the value meaning "8K page" is the same
	 * as the value meaning "4K page" on the 4K page devices.
	 *
	 * The only identifiable difference between the 4K and 8K page Toshiba
	 * devices with a device code of 0xd7 is the undocumented 6th ID byte.
	 * The 4K device returns a value of 0x13 and the 8K a value of 0x54.
	 * Toshiba has verified that this is an acceptable method to distinguish
	 * the two device families.
	 */

	if (ID_GET_BYTE_6(id) == ID_TOSHIBA_BYTE_6_PAGE_SIZE_CODE_8K) {
		/* Type 11 */
		table = nand_device_info_table_type_11;
	} else if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
		/* Type 9 */
		table = nand_device_info_table_type_9;
	} else {
		/* Large MLC */
		table = nand_device_info_table_large_mlc;
	}

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_samsung(const u8 id[])
{
	struct nand_device_info  *table;


	/* Check for Small Block */
	if ((ID_GET_BYTE_3(id) == 0xc0) || (ID_GET_BYTE_3(id) == 0xbd)) {
		table = nand_device_info_table_type_2;
		
	}else{
	/* Check for an MLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) != ID_CELL_TYPE_CODE_SLC) {

		/* Is this a Samsung 8K Page MLC device with 24 bit ECC? */
		if ((ID_GET_SAMSUNG_ECC_LEVEL_CODE(id) ==
					ID_SAMSUNG_ECC_LEVEL_CODE_24) &&
		    (ID_GET_PAGE_SIZE_CODE(id) ==
					ID_SAMSUNG_6_BYTE_PAGE_SIZE_CODE_8K)) {
			/* Type 15 */
			table = nand_device_info_table_type_15;
		}
		/* Is this a Samsung 42nm ECC8 device with a 6 byte ID? */
		else if ((ID_GET_SAMSUNG_ECC_LEVEL_CODE(id) ==
					ID_SAMSUNG_ECC_LEVEL_CODE_8) &&
			(ID_GET_SAMSUNG_DEVICE_VERSION_CODE(id) ==
					ID_SAMSUNG_DEVICE_VERSION_CODE_40NM)) {
			/* Type 9 */
			table = nand_device_info_table_type_9;
		} else if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
			/* Type 8 */
			table = nand_device_info_table_type_8;
		} else {
			/* Large MLC */
			table = nand_device_info_table_large_mlc;
		}

	} else {

		/* Check the page size first. */
		if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
			/* Type 10 */
			table = nand_device_info_table_type_10;
		}
		/* Check the chip size. */
		else if (ID_GET_dev_id(id) ==
						ID_SAMSUNG_dev_id_1_GBIT) {
			if (!ID_GET_CACHE_PROGRAM(id)) {
				/*
				 * 128 MiB Samsung chips without cache program
				 * are Type 7.
				 *
				 * The K9F1G08U0B does not support multi-plane
				 * program, so the if statement below cannot be
				 * used to identify it.
				 */
				table = nand_device_info_table_type_7;

			} else {
				/* Smaller sizes are Type 2 by default. */
				table = nand_device_info_table_type_2;
			}
		} else {
			/* Check number of simultaneously programmed pages. */
			if (ID_GET_SAMSUNG_SIMUL_PROG(id) &&
						ID_GET_PLANE_COUNT_CODE(id)) {
				/* Type 7 */
				table = nand_device_info_table_type_7;
			} else {
				/* Type 2 */
				table = nand_device_info_table_type_2;
			}

		}

	}
	}

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_stmicro(const u8 id[])
{
	struct nand_device_info  *table;

	/* Check for an SLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) == ID_CELL_TYPE_CODE_SLC)
		/* Type 2 */
		table = nand_device_info_table_type_2;
	else
		/* Large MLC */
		table = nand_device_info_table_large_mlc;

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_hynix(const u8 id[])
{
	struct nand_device_info  *table;

	/* Check for an SLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) == ID_CELL_TYPE_CODE_SLC) {
		/* Type 2 */
		return nand_device_info_search(nand_device_info_table_type_2,
				ID_GET_MFR_CODE(id), ID_GET_dev_id(id));
	}

	/*
	 * Check for ECC12 devices.
	 *
	 * We look at the 4th ID byte to distinguish some Hynix ECC12 devices
	 * from the similar ECC8 part. For example H27UBG8T2M (ECC12) 4th byte
	 * is 0x25, whereas H27UDG8WFM (ECC8) 4th byte is 0xB6.
	 */

	if ((ID_GET_dev_id(id) == ID_HYNIX_dev_id_ECC12 &&
			ID_GET_BYTE_4(id) == ID_HYNIX_BYTE_4_ECC12_DEVICE) ||
	    (ID_GET_dev_id(id) == ID_HYNIX_dev_id_ECC12_LARGE)) {
		/* BCH ECC 12 */
		table = nand_device_info_table_bch_ecc12;
	} else if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
		/*
		 * So far, all other Samsung and Hynix 4K page devices are
		 * Type 8.
		 */
		table = nand_device_info_table_type_8;
	} else
		/* Large MLC */
		table = nand_device_info_table_large_mlc;

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_micron(const u8 id[])
{
	struct nand_device_info  *table;

	/* Check for an SLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) == ID_CELL_TYPE_CODE_SLC) {

		/* Check number of simultaneously programmed pages. */

		if (ID_GET_MICRON_SIMUL_PROG(id)) {
			/* Type 7 */
			table = nand_device_info_table_type_7;
		} else {
			/* Zero simultaneously programmed pages means Type 2. */
			table = nand_device_info_table_type_2;
		}

		return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

	}

	/*
	 * We look at the 5th ID byte to distinguish some Micron ECC12 NANDs
	 * from the similar ECC8 part.
	 *
	 * For example MT29F64G08CFAAA (ECC12) 5th byte is 0x84, whereas
	 * MT29F64G08TAA (ECC8) 5th byte is 0x78.
	 *
	 * We also have a special case for the Micron L63B family
	 * (256 page/block), which has unique device codes but no ID fields that
	 * can easily be used to distinguish the family.
	 */

	if ((ID_GET_dev_id(id) == ID_MICRON_dev_id_ECC12 &&
				ID_GET_BYTE_5(id) == ID_MICRON_BYTE_5_ECC12)  ||
	   (ID_GET_dev_id(id) == ID_MICRON_dev_id_ECC12_LARGE)      ||
	   (ID_GET_dev_id(id) == ID_MICRON_dev_id_ECC12_2GB_PER_CE) ||
	   (ID_GET_dev_id(id) == ID_MICRON_dev_id_ECC12_4GB_PER_CE) ||
	   (ID_GET_dev_id(id) == ID_MICRON_dev_id_ECC12_8GB_PER_CE)) {
		/* BCH ECC 12 */
		table = nand_device_info_table_bch_ecc12;
	} else if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
		/* Toshiba devices with 4K pages are Type 9. */
		table = nand_device_info_table_type_9;
	} else {
		/* Large MLC */
		table = nand_device_info_table_large_mlc;
	}

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_sandisk(const u8 id[])
{
	struct nand_device_info  *table;

	if (ID_GET_CELL_TYPE_CODE(id) != ID_CELL_TYPE_CODE_SLC) {
		/* Large MLC */
		table = nand_device_info_table_large_mlc;
	} else {
		/* Type 2 */
		table = nand_device_info_table_type_2;
	}

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

static struct nand_device_info *nand_device_info_fn_intel(const u8 id[])
{
	struct nand_device_info  *table;

	/* Check for an SLC device. */

	if (ID_GET_CELL_TYPE_CODE(id) == ID_CELL_TYPE_CODE_SLC) {
		/* Type 2 */
		return nand_device_info_search(nand_device_info_table_type_2,
				ID_GET_MFR_CODE(id), ID_GET_dev_id(id));
	}

	if (ID_GET_PAGE_SIZE_CODE(id) == ID_PAGE_SIZE_CODE_4K) {
		/* Type 9 */
		table = nand_device_info_table_type_9;
	} else {
		/* Large MLC */
		table = nand_device_info_table_large_mlc;
	}

	return nand_device_info_search(table, ID_GET_MFR_CODE(id),
							ID_GET_dev_id(id));

}

/**
 * struct nand_device_type_info - Information about a NAND Flash type.
 *
 * @name:   A human-readable name for this type.
 * @table:  The device info table for this type.
 */

struct nand_device_type_info {
	struct nand_device_info  *table;
	const char               *name;
};

/*
 * A table that maps manufacturer IDs to device information tables.
 */

static struct nand_device_type_info  nand_device_type_directory[] =
{
	{nand_device_info_table_type_2,    "Type 2"   },
	{nand_device_info_table_large_mlc, "Large MLC"},
	{nand_device_info_table_type_7,    "Type 7"   },
	{nand_device_info_table_type_8,    "Type 8"   },
	{nand_device_info_table_type_9,    "Type 9"   },
	{nand_device_info_table_type_10,   "Type 10"  },
	{nand_device_info_table_type_11,   "Type 11"  },
	{nand_device_info_table_type_15,   "Type 15"  },
	{nand_device_info_table_bch_ecc12, "BCH ECC12"},
	{0, 0},
};

/**
 * struct nand_device_mfr_info - Information about a NAND Flash manufacturer.
 *
 * @id:     The value of the first NAND Flash ID byte, which identifies the
 *          manufacturer.
 * @fn:     A pointer to a function to use for identifying devices from the
 *          given manufacturer.
 */

struct nand_device_mfr_info {
	u8                  id;
	struct nand_device_info  *(*fn)(const u8 id[]);
};

/*
 * A table that maps manufacturer IDs to device information tables.
 */

static struct nand_device_mfr_info  nand_device_mfr_directory[] =
{
	{
	.id = NAND_MFR_TOSHIBA,
	.fn = nand_device_info_fn_toshiba,
	},
	{
	.id = NAND_MFR_SAMSUNG,
	.fn = nand_device_info_fn_samsung,
	},
	{
	.id = NAND_MFR_FUJITSU,
	.fn = 0,
	},
	{
	.id = NAND_MFR_NATIONAL,
	.fn = 0,
	},
	{
	.id = NAND_MFR_RENESAS,
	.fn = 0,
	},
	{
	.id = NAND_MFR_STMICRO,
	.fn = nand_device_info_fn_stmicro,
	},
	{
	.id = NAND_MFR_HYNIX,
	.fn = nand_device_info_fn_hynix,
	},
	{
	.id = NAND_MFR_MICRON,
	.fn = nand_device_info_fn_micron,
	},
	{
	.id = NAND_MFR_AMD,
	.fn = 0,
	},
	{
	.id = NAND_MFR_SANDISK,
	.fn = nand_device_info_fn_sandisk,
	},
	{
	.id = NAND_MFR_INTEL,
	.fn = nand_device_info_fn_intel,
	},
	{0, 0}
};

/**
 * nand_device_info_test_table - Validate a device info table.
 *
 * This function runs tests on the given device info table to check that it
 * meets the current assumptions.
 */

static int  nand_device_info_test_table(
			struct nand_device_info *table, const char * name)
{
	unsigned  i;
	unsigned  j;
	u8   mfr_code;
	u8   dev_id;

	/* Loop over entries in this table. */

	for (i = 0; !table[i].end_of_table; i++) {

		/* Get discriminating attributes of the current device. */

		mfr_code    = table[i].man_id;
		dev_id = table[i].dev_id;

		/* Compare with the remaining devices in this table. */

		for (j = i + 1; !table[j].end_of_table; j++) {
			if ((mfr_code    == table[j].man_id) &&
			    (dev_id == table[j].dev_id))
				return 1;
		}

	}

	return 0;
}

/**
 * nand_device_info_test_data - Test the NAND Flash device data.
 */

static int nand_device_info_test_data(void)
{

	unsigned  i;
	int ret = 0;

	for (i = 0; nand_device_type_directory[i].name; i++) {
		ret = nand_device_info_test_table(
					nand_device_type_directory[i].table,
					nand_device_type_directory[i].name);
		if (ret)
			break;
	}
	
	return ret;

}

struct nand_device_info * nand_device_get_info(const u8 id[])
{
	unsigned                 i;
	int 			 ret;
	u8                  mfr_id = ID_GET_MFR_CODE(id);
	struct nand_device_info  *(*fn)(const u8 id[]) = 0;

	/* Test the data. */

	ret = nand_device_info_test_data();
	if(ret)
		return 0;

	/* Look for information about this manufacturer. */

	for (i = 0; nand_device_mfr_directory[i].id; i++) {
		if (nand_device_mfr_directory[i].id == mfr_id) {
			fn = nand_device_mfr_directory[i].fn;
			break;
		}
	}

	if (!fn)
		return 0;

	/*
	 * If control arrives here, we found both a table of device information,
	 * and a function we can use to identify the current device. Attempt to
	 * identify the device and return the result.
	 */

	return fn(id);

}
