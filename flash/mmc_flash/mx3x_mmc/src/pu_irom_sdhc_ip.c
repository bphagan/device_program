/*****************************************************************************
** pu_irom_sdhc_ip.c
**
** Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
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
 * @file pu_irom_sdhc_ip.c
 *
 * @brief source code for the mmc card operation
 *
 * @ingroup mmc
 */
/*====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "Common.h"
#include "MX31_def.h"
#include "pu_irom_sdhc_ipp.h"
#include "pu_irom_sdhc_ip.h"


/*==================================================================================================
                                           Global Defines 
==================================================================================================*/      
/* Gloal pointer to SDHC register set */
volatile psdhc_t psdhc;

/*==================================================================================================
                                            MACROS
==================================================================================================*/      

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                          Static Functions 
==================================================================================================*/
/*!
 * Configure SDHC registers for sending a command to MMC/SD.
 * @cmd
 * command_t * - a pointer to structure defining a command
*/
 
static void sdhc_cmd_config(command_t *cmd)                                                           
{
    /* Write command index */
    psdhc->sdhc_cmd = cmd->command;

    /* Write command arg */ 
    psdhc->sdhc_arg = cmd->arg;

    /* workaround for CMD0, send 80 clock cycles before CMD0 */
    if (cmd->command == 0)
    {
        /* Set the type of transfer */
        psdhc->sdhc_cmd_dat_cont = (((cmd->data_transfer) << SDHC_CMD_DATA_CTRL_WRITE_READ_SHIFT) |
                                    ((cmd->response_format) << SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_SHIFT) |
                                    ((cmd->data_present) << SDHC_CMD_DATA_CTRL_DATA_ENABLE_SHIFT) |
                                    ((SDHC_CMD_DATA_CTRL_BUS_WIDTH_1_BIT) << SDHC_CMD_DATA_CTRL_BUS_WIDTH_SHIFT) | 
                                    (SDHC_CMD_DATA_CTRL_INIT)
                                   );
    }
    else
    {
        psdhc->sdhc_cmd_dat_cont = (((cmd->data_transfer) << SDHC_CMD_DATA_CTRL_WRITE_READ_SHIFT) |
                                    ((cmd->response_format) << SDHC_CMD_DATA_CTRL_FROMAT_OF_RESP_SHIFT) |
                                    ((cmd->data_present) << SDHC_CMD_DATA_CTRL_DATA_ENABLE_SHIFT) |
                                    ((SDHC_CMD_DATA_CTRL_BUS_WIDTH_1_BIT) << SDHC_CMD_DATA_CTRL_BUS_WIDTH_SHIFT) 
                                   );
    }

    return; 
}

/*!
 * Start the clock and wait until the clock is started.
*/
 
static void sdhc_start_clk(void)
{
    /* Start the clock */
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_START;

    /* Wait till the clock has started, then the command
     * will begin transfering to the card */
 
    while(!(psdhc->sdhc_status & SDHC_STATUS_CLK_RUN_MSK));
    return;
}

/*!
 * Stop the clock and wait until the clock is stoped.
 */ 
static void sdhc_stop_clk(void )
{
    /* Stop MMC/SD clock */
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;

    /* Wait until clock is stopped */
    while((psdhc->sdhc_status & SDHC_STATUS_CLK_RUN_MSK));
}

/*!
 * Wait a END_CMD_RESP interrupt by polling status register. The fields 
 * RESP_CRC_ERR (Status[5]) and TIME_OUT_RESP(STATUS[1]) are checked 
 * to determine if an error has occurred.
 */
 
static void sdhc_wait_end_cmd_resp_intr(void)
{
    /* Wait for end command response interrupt 
     * This interrupt may raise when one of STATUS[1],
     * STATUS[5] or STATUS[13] are set. */
   
    while(!(psdhc->sdhc_status & SDHC_STATUS_END_CMD_RESP_MSK));
}

/*!
 * Check whether the interrupt is an END_CMD_RESP  
 * or a response time out or a CRC error. 
*/
 
static U32 sdhc_check_response(void)
{
    U32 sdhc_status = SDHC_STATUS_PASS;

    /* Check whether the interrupt is an END_CMD_RESP  
     * or a time out or a CRC error 
     */ 		
     if((psdhc->sdhc_status & SDHC_STATUS_END_CMD_RESP_MSK) &&
	!(psdhc->sdhc_status & SDHC_STATUS_TIME_OUT_RESP_MSK) &&
	!(psdhc->sdhc_status & SDHC_STATUS_RESP_CRC_ERR_MSK))
     {
          sdhc_status = SDHC_STATUS_PASS;
     }
     else
     {
          sdhc_status = SDHC_STATUS_FAILURE;
     }
   
     return sdhc_status;
}

/*!
 * Set SDHC_BLK_LEN and SDHC_NOB registers.
 * @blk_len  U32 - the length of the block to be transfered
 * @nob U32 - the number of blocks to be transfered
 */
 
void interface_config_block_info(U32 blk_len, U32 nob)
{
    psdhc->sdhc_blk_len = blk_len;
    psdhc->sdhc_nob = nob;
}

/*!
 * Wait a BUF_READ_READY or BUF_WRITE_READY interrupt by polling STATUS register.
 * @mask U32 - an integer defining the mask to be applied on the STATUS register
 */
 
static void sdhc_wait_buf_rdy_intr(U32 mask)
{
    if((mask == SDHC_STATUS_BUF_READ_RDY_MSK) || (mask == SDHC_STATUS_BUF_WRITE_RDY_MSK))
    {
          /* Wait for interrupt (BUF_READ_RDY/BUF_WRITE_RDY) */
          while(!(psdhc->sdhc_status & mask));	
    }
		
}

/*! 
 * Wait a WRITE_OP_DONE or a READ_OP_DONE by pooling STAUTUS register.
 * @op_done_mask U32 - an integer defining the mask to be applied on the STATUS register
 */   
  
static void sdhc_wait_op_done_intr(U32 op_done_mask)
{
    if((op_done_mask == SDHC_STATUS_READ_OP_DONE_MSK) || (op_done_mask == SDHC_STATUS_WRITE_OP_DONE_MSK))
    {
         /* Wait interrupt (WRITE_OP_DONE/READ_OP_DONE) */
         while(!(psdhc->sdhc_status & op_done_mask));
 
    }
		

}

/*!
 * If WRITE_OP_DONE/READ_OP_DONE occured check WR_CRC_ERR_CODE/RD_CRC_ERR_CODE 
 * and WRITE_CRC_ERR/READ_CRC_ERR to determine if an error occured
 * @op_done_mask  U32 - an integer defining the WRITE_OP_DONE/READ_OP_DONE mask to be 
   applied on the STATUS register
 * @crc_err_code_mask U32 - an integer defining the WR_CRC_ERR_CODE/RD_CRC_ERR_CODE mask 
 * to be applied on the STATUS register
 * @crc_err_mask U32 - an integer defining the WRITE_CRC_ERR/READ_CRC_ERR mask 
 * to be applied on the STATUS register
 * @return UINT32
 */
 
static U32 sdhc_check_data(U32 op_done_mask, U32 crc_err_code_mask, U32 crc_err_mask)
{
    U32 sdhc_status = SDHC_STATUS_FAILURE;

    /* Check whether the interrupt is an OP_DONE  
     * or a data time out or a CRC error  */
     if((psdhc->sdhc_status & op_done_mask) &&
       !(psdhc->sdhc_status & crc_err_code_mask) &&
       !(psdhc->sdhc_status & crc_err_mask))
     {
         sdhc_status = SDHC_STATUS_PASS;
     }
     else
     {
         sdhc_status = SDHC_STATUS_FAILURE;
     }
     return sdhc_status;
}

/*! 
 * execute a command and wait for the response
 */

U32 
interface_send_cmd_wait_resp(command_t *cmd)
{

    /* Start the clock */
    sdhc_start_clk();
 
    /* Clear Interrupt status Register */
    psdhc->sdhc_status = 0xFFFFFFFF;

    /* Enable interrupts */
    psdhc->sdhc_int_cntr = SDHC_INTERRUPTS_MASK;

    /* Configure Command */
    sdhc_cmd_config(cmd);

    /* Wait for interrupt end_command_resp */
    sdhc_wait_end_cmd_resp_intr();

    /* Mask all interrupts */
    psdhc->sdhc_int_cntr = 0;

    /* Check if an error occured */
    return sdhc_check_response();

}

/*!
 * Read the response returned by the card after a command 
 */

U32 interface_read_response(command_response_t * resp)
{
    U32 status = SDHC_STATUS_FAILURE;
    U16 resp_h = 0;
    U16 resp_l = 0;

    if(resp != 0)
    {
        /* Stop MMC clock */
        sdhc_stop_clk();
       
        if(resp->format == RESPONSE_136)
        { 
            /* response is read in MSB first order */ 
            resp_h = psdhc->sdhc_res_fifo & 0xffff;
            resp_l = psdhc->sdhc_res_fifo & 0xffff;
            resp->cmd_rsp3 = (resp_h << 16) | resp_l;

            resp_h = psdhc->sdhc_res_fifo & 0xffff;
            resp_l = psdhc->sdhc_res_fifo & 0xffff;
            resp->cmd_rsp2 = (resp_h << 16) | resp_l;

            resp_h = psdhc->sdhc_res_fifo & 0xffff;
            resp_l = psdhc->sdhc_res_fifo & 0xffff;
            resp->cmd_rsp1 = (resp_h << 16) | resp_l;

            resp_h = psdhc->sdhc_res_fifo & 0xffff;
            resp_l = psdhc->sdhc_res_fifo & 0xffff;
            resp->cmd_rsp0 = (resp_h << 16) | resp_l;
        }
        else if((resp->format == RESPONSE_48) || (resp->format == RESPONSE_48_WITHOUT_CRC))
        {
            /* 
               Extract the bit 8-39 from the 48 bit response and return
               32-bit significant response in cmd_rsp0
            */ 
            resp->cmd_rsp0 = ((UINT32)(psdhc->sdhc_res_fifo & 0x00ff) << 24) | ((UINT32)(psdhc->sdhc_res_fifo & 0xffff) << 8)
                             | ((UINT32)(psdhc->sdhc_res_fifo & 0xff00) >> 8);
 
        }

        /* Clear w1c bits from STATUS register */
        psdhc->sdhc_status = psdhc->sdhc_status | SDHC_STATUS_CLEAR;

        status = SDHC_STATUS_PASS;
    }

    return status;

}

/*!
 * Read data from cmd->arg address to cmd->arg + blk_len.
 */

U32 interface_data_read(U32* dest_ptr, U32 blk_len) 
{
    U32 i,j=0;
    U32 status = SDHC_STATUS_FAILURE;
    

    /* Enable interrupts */
    psdhc->sdhc_int_cntr = SDHC_INTERRUPTS_MASK;
	
    for(i = 0; i < blk_len/(FIFO_SIZE*FIFO_SIZE); i++)
    {
        /* Wait for BRR bit to be set */
        sdhc_wait_buf_rdy_intr(SDHC_STATUS_BUF_READ_RDY_MSK);
		
        for(j=0;j<FIFO_SIZE;j++)
        { 
            /* Read 32 bit data from buffer data port register */
            *dest_ptr = psdhc->sdhc_buffer_access;
		
            /*increment destination pointer */
            dest_ptr++;
        }
    }
	
    /* Wait for transfer complete operation interrupt */	
    sdhc_wait_op_done_intr(SDHC_STATUS_READ_OP_DONE_MSK);
		
    /* Check for status errors */	
    status = sdhc_check_data(SDHC_STATUS_READ_OP_DONE_MSK, SDHC_STATUS_TIME_OUT_READ, SDHC_STATUS_READ_CRC_ERR_MSK);
	
    return status;
	
}

U32 interface_data_write(U32* dest_ptr, U32 blk_len)
{
    U32 i,j=0;
    U32 status = SDHC_STATUS_FAILURE;


    /* Enable interrupts */
    psdhc->sdhc_int_cntr = SDHC_INTERRUPTS_MASK;
       
    for(i = 0; i < blk_len/(FIFO_SIZE*FIFO_SIZE); i++)
    {
        /* Wait for BRR bit to be set */
        sdhc_wait_buf_rdy_intr(SDHC_STATUS_BUF_WRITE_RDY_MSK);

        for(j=0;j<FIFO_SIZE;j++)
        {
            /* Read 32 bit data from buffer data port register */
            psdhc->sdhc_buffer_access =*dest_ptr;;
               
            /*increment destination pointer */
            dest_ptr++;
        }
    }
       
    /* Wait for transfer complete operation interrupt */
    sdhc_wait_op_done_intr(SDHC_STATUS_WRITE_OP_DONE_MSK);

    /* Check for status errors */
    status = sdhc_check_data(SDHC_STATUS_WRITE_OP_DONE_MSK, SDHC_STATUS_WR_CRC_ERR_CODE_MSK, SDHC_STATUS_WRITE_CRC_ERR_MSK);
       
    return status;
       
}



/*!
 * Execute a software reset.     
 */
 
void interface_reset()
{
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_RESET;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_RESET | SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
    psdhc->sdhc_str_stp_clk = SDHC_STR_STP_CLK_STOP;
}

/*!
 * This function configures the clock rate.
 */
 
void interface_configure_clock(sdhc_freq_t frequency)
{
    /* Clear the clock rate register */
    psdhc->sdhc_clk_rate = psdhc->sdhc_clk_rate & ~SDHC_CLK_RATE_PRESCALER_MASK;
    psdhc->sdhc_clk_rate = psdhc->sdhc_clk_rate & ~SDHC_CLK_RATE_DIVIDE_MASK;


    if ( ( (*(VP_U32)CCM_CCMR ) & CLOCK_SEL_MASK ) == CKIL_CLOCK_SEL)
    {
        /* IPG_PER_CLK is 49.15 MHz after reset */
        if(frequency == IDENTIFICATION_FREQ)
        {
            /* Below 100 kHz ( ~96 kHz) */
            psdhc->sdhc_clk_rate |= (PRE_CLK_DIV_64 << SDHC_CLK_RATE_PRESCALER_SHIFT) | CLK_DIV_8;
            
            /* Start SDHC clock */
            sdhc_start_clk();
        }
        else if(frequency == OPERATING_FREQ)
        {
            /* Below 20 MHz (~16.384 MHz) */ 
            psdhc->sdhc_clk_rate |= (PRE_CLK_DIV << SDHC_CLK_RATE_PRESCALER_SHIFT) | CLK_DIV_3;              
        }
    }
    else
    {
        /* IPG_PER_CLK is 39 MHz after reset */ 
        if(frequency == IDENTIFICATION_FREQ)
        {
            /* Below 100 kHz ( ~101.5 kHz) */
            psdhc->sdhc_clk_rate |= (PRE_CLK_DIV_64 << SDHC_CLK_RATE_PRESCALER_SHIFT) | CLK_DIV_6;
            
            /* Start SDHC clock */
            sdhc_start_clk();
        }
        else if(frequency == OPERATING_FREQ)
        {
            /* Below 20 MHz (~19.5 MHz) */ 
            psdhc->sdhc_clk_rate |= (PRE_CLK_DIV << SDHC_CLK_RATE_PRESCALER_SHIFT) | CLK_DIV_2;              
        }
    }
}

/*
 *Initialize the interface.
 */
 
void interface_init(UINT32 base_address)
{
     /* IOMUX programming */
     VP_U32 iomux_sw_ctl_reg1 = (VP_U32)(0x43FAC000 + 0x18);
     VP_U32 iomux_sw_ctl_reg2 = (VP_U32)(0x43FAC000 + 0x1c);

     *iomux_sw_ctl_reg1 = *iomux_sw_ctl_reg1 & 0x000000FF;
     *iomux_sw_ctl_reg1 = *iomux_sw_ctl_reg1 | 0x12121200;

     *iomux_sw_ctl_reg2 = *iomux_sw_ctl_reg2 & 0xFF000000;  
     *iomux_sw_ctl_reg2 = *iomux_sw_ctl_reg2 | 0x00121012;
    
     /* Initialize base address */ 
     psdhc = (psdhc_t)base_address; 
}

