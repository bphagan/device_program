#ifndef _PU_IROM_SDHC_IPP_H_
#define _PU_IROM_SDHC_IPP_H_
/*==================================================================================================
                                                                               
    Module Name:  pu_irom_sdhc_ipp.h

    General Description: Private include file for SDHC IP.

====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.
  
Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Suresh Kumar                 03/Oct/2006    TLSbo79133     Initial Version 


-------------------------   ------------    ----------   ------------------------------------------- 
Portability: Non-Portable.
References : iMX31 L3 Specifications V1.43

====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "Common.h"

/*==================================================================================================
                                      MACROS AND DEFINES
==================================================================================================*/      
#define BLK_LEN   512
#define FIFO_SIZE 4   /* For SD 1-bit Mode, FIFO is of 4 words */

/* General defines */
#define IPG_PER_CLK_REF_TO_MPLL_CKIL           48*1024    /* in kHz */         
#define IPG_PER_CLK_REF_TO_MPLL_CKIH           39*1000    /* in kHz */
#define CLOCK_SEL_MASK                         0x00000006
#define CKIL_CLOCK_SEL                         0x00000002


/* Command and data control masks */
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP      0x00000007
#define SDHC_CMD_DATA_CTRL_DATA_ENABLE         0x00000008
#define SDHC_CMD_DATA_CTRL_WRITE_READ          0x00000010
#define SDHC_CMD_DATA_CTRL_INIT                0x00000080
#define SDHC_CMD_DATA_CTRL_BUS_WIDTH           0x00000300
#define SDHC_CMD_DATA_CTRL_START_READ_WAIT     0x00000400
#define SDHC_CMD_DATA_CTRL_STOP_READ_WAIT      0x00000800
#define SDHC_CMD_DATA_CTRL_CMD_RESP_LONG_OFF   0x00001000

/* Command and data control values */
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_SHIFT     0x0
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_NONE      0x0
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_48        0x1
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_136       0x2
#define SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_48_N0_CRC 0x3

#define SDHC_CMD_DATA_CTRL_DATA_ENABLE_SHIFT        0x3

#define SDHC_CMD_DATA_CTRL_BUS_WIDTH_SHIFT          0x8
#define SDHC_CMD_DATA_CTRL_BUS_WIDTH_1_BIT          0x0
#define SDHC_CMD_DATA_CTRL_BUS_WIDTH_4_BIT          0x2

#define SDHC_CMD_DATA_CTRL_WRITE_READ_SHIFT         0x4

#define SDHC_CMD_DATA_CTRL_INIT_SHIFT               0x7

/* Interrupt control regiter Mask */
/* Bit - 0: READ_OP_DONE
 * Bit - 2: END_CMD_RES
 * Bit - 4: BUF_READ_EN
 * Bit - 14: CARD_REMOVAL_EN
 * Bit - 15: CARD_INSERTION_EN
 */
#define SDHC_INTERRUPTS_MASK                  0x0000c015

/* Clock rate register masks */
#define SDHC_CLK_RATE_DIVIDE_MASK             0x0000000F
#define SDHC_CLK_RATE_PRESCALER_MASK          0x0000FFF0
#define SDHC_CLK_RATE_DIVIDE_SHIFT            0x0
#define SDHC_CLK_RATE_PRESCALER_SHIFT         0x4

/* Status regsiter Masks */
#define SDHC_STATUS_CLK_RUN_MSK               0x100
#define SDHC_STATUS_END_CMD_RESP_MSK          0x2000
#define SDHC_STATUS_TIME_OUT_RESP_MSK         0x2
#define SDHC_STATUS_RESP_CRC_ERR_MSK          0x20
#define SDHC_STATUS_BUF_READ_RDY_MSK          0x80
#define SDHC_STATUS_BUF_WRITE_RDY_MSK         0x40
#define SDHC_STATUS_WRITE_OP_DONE_MSK         0x1000
#define SDHC_STATUS_WR_CRC_ERR_CODE_MSK       0x600
#define SDHC_STATUS_WRITE_CRC_ERR_MSK         0x4
#define SDHC_STATUS_READ_OP_DONE_MSK          0x800
#define SDHC_STATUS_TIME_OUT_READ             0x1
#define SDHC_STATUS_READ_CRC_ERR_MSK          0x8
#define SDHC_STATUS_CLEAR                     ((U32)(0xC0007E2F))

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/* SDHC Clock Control register constants*/
enum sdhc_str_stp_clk_val
{
    SDHC_STR_STP_CLK_START = 0x2,
    SDHC_STR_STP_CLK_STOP = 0x1,
    SDHC_STR_STP_CLK_RESET = 0x8
};

enum sdhc_int_cntr_val
{
    SDHC_INT_CNTR_END_CMD_RESP = 0x4,
    SDHC_INT_CNTR_BUF_WR_RDY = 0x8
};

/* Clock rate register constants */
enum clock_rate_prescaler
{
    PRE_CLK_DIV =0x000, 
    PRE_CLK_DIV_2 =0x001, 
    PRE_CLK_DIV_4 =0x002, 
    PRE_CLK_DIV_8 =0x004, 
    PRE_CLK_DIV_16 =0x008, 
    PRE_CLK_DIV_32 =0x010, 
    PRE_CLK_DIV_64 =0x020, 
    PRE_CLK_DIV_128 =0x040, 
    PRE_CLK_DIV_256 =0x080, 
    PRE_CLK_DIV_512 =0x100, 
    PRE_CLK_DIV_1024 =0x200, 
    PRE_CLK_DIV_2048 =0x400, 
    PRE_CLK_DIV_4096 =0x800
};

enum clock_rate_divider
{
    CLK_DIV_2 =0x01, 
    CLK_DIV_3 =0x02, 
    CLK_DIV_4 =0x03, 
    CLK_DIV_5 =0x04, 
    CLK_DIV_6 =0x05, 
    CLK_DIV_7 =0x06, 
    CLK_DIV_8 =0x07, 
    CLK_DIV_9 =0x08, 
    CLK_DIV_10 =0x09, 
    CLK_DIV_11 =0x0a, 
    CLK_DIV_12 =0x0b, 
    CLK_DIV_13 =0x0c, 
    CLK_DIV_14 =0x0d,
    CLK_DIV_15 =0x0e,
    CLK_DIV_16 =0x0f
};

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* SDHC register Set */
typedef struct 
{
    U32 sdhc_str_stp_clk;
    U32 sdhc_status;
    U32 sdhc_clk_rate;
    U32 sdhc_cmd_dat_cont;
    U32 sdhc_response_to;
    U32 sdhc_read_to;
    U32 sdhc_blk_len;
    U32 sdhc_nob;
    U32 sdhc_rev_no;
    U32 sdhc_int_cntr;
    U32 sdhc_cmd;
    U32 sdhc_arg;
    U32 sdhc_reserved;
    U32 sdhc_res_fifo;
    U32 sdhc_buffer_access;
    U32 sdhc_remaining_nob;
    U32 sdhc_remaining_blk_size;
}sdhc_t, *psdhc_t;

#endif
