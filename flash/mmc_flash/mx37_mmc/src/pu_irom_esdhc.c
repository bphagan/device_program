/*=================================================================================

    Module Name:  pu_irom_esdhc.c

    General Description: Limited IROM eSDHC Driver.

===================================================================================
                               Copyright: 2004,2005,2006,2007 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a 
                   Freescale Software License Agreement, which has either 
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.


Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number     Description of Changes
-------------------------   ------------    ----------   --------------------------
Sajith P V                  10-Sep-2007      TLSbo96209   Modified Pad Configuration
Sajith P V                  10/09/2007      TLSbo96203   Modifed GPIO configuration.
Prabhat Singh                 20/08/2007      TLSbo95750   Modified masking of interrupt  
Deepak Agarwal              30/July/2007   TLSbo94587   CE-ATA, Ported to Ringo.
Prabhat Singh               13/07/2007      Tlbso94839   Porting for Ringo
Surender Kumar (r66464)     07/06/2007      TLSbo93610   Porting for Marley
Surender Kumar (r66464)     09/03/2006      TLSbo68167 	 Initial implementation.


Portability: Portable to other compilers or platforms.



====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

//#define TY_DBG

#include "pu_irom_esdhc.h" 
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"
#include "pu_irom_timer.h"
#include "hapi_gpio_defs.h"
#include "hapi_gpio.h"

#ifdef TY_DBG
#include "stdio.h"
#include "channel.h"
#endif

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define IOMUXC_BASE_ADDR                (0xc3fa8000)
#define GPIO1_BASE_ADDR                 (0xc3f84000)
#define GPIO2_BASE_ADDR                 (0xc3f88000)
#define GPIO3_BASE_ADDR                 (0xc3f8c000)

static VP_U32 const iomux_sw_mux_ctrl_reg_array[3] = 
{
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0008),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0230),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0508)
};

static VP_U32 const data_dir_reg_ptr_array[3] = {
    (UINT32 *) ((UINT32) GPIO1_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO2_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO3_BASE_ADDR + 4)
};

#define esdhc_1_regs_base_address       (0xc0004000)
#define esdhc_2_regs_base_address       (0xc0008000)
#define esdhc_3_regs_base_address       (0xc0020000)

#define HAPI_GPIO_pad_config(port, reg_index, val)    \
    iomux_sw_mux_ctrl_reg_array[port][reg_index] = (val)

#define HAPI_GPIO_config(port, pin, io_select, dir) \
    {   \
        UINT32 tmp, rnum, roffset, cfg_val;    \
        if (((io_select) & 0x00000200) == 0x00000200) {   \
            rnum = ((io_select) >> 12) & 0x000000ff; \
            roffset = ((io_select) >> 10) & 0x00000003;    \
            cfg_val = ((io_select) & 0x000000ff); \
            tmp = iomux_sw_mux_ctrl_reg_array[port][rnum];    \
            tmp &= ~(0x000000ff << (roffset * 8));   \
            tmp |= (cfg_val << (roffset * 8));  \
            iomux_sw_mux_ctrl_reg_array[port][rnum] = tmp;    \
        }   \
        if ((io_select & 0x100) == 0x100) { \
            /* Configure the direction of GPIO */ \
            if (dir) {  \
                *data_dir_reg_ptr_array[port] |= (1 << pin); \
            } else { \
                *data_dir_reg_ptr_array[port] &= ~(1 << pin); \
            } \
        } \
    }

/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/
                                                                       

/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/
pESDHC_t esdhc_base_pointer;

/* Disable/Enable the data xfer status checking */
UINT32 esdhc_check_op_done = SUCCESS;

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void esdhc_cmd_config(command_t *);
static void esdhc_wait_end_cmd_resp_intr(void);
static UINT32 esdhc_check_response(void);
static UINT32 esdhc_wait_buf_rdy_intr(UINT32, UINT32);
static void esdhc_wait_op_done_intr(void);
static UINT32 esdhc_check_data(void);
static void esdhc_set_data_transfer_width(UINT32 data_transfer_width);
static UINT32 esdhc_poll_cihb_cdihb(data_present_select data_present);
static void esdhc_set_endianness(UINT32 endian_mode);
static void esdhc_clear_buf_rdy_intr(UINT32 mask);
static void esdhc_iomux_configuration(void);
static UINT32 esdhc_check_data_crc_status(void);

#ifdef TY_DBG
UINT32 esdhc_dump_register();
#endif
/*=============================================================================
FUNCTION: void interface_initialization_active(void)

DESCRIPTION:
    Send 80 SD clock to card and wait for INITA bit to get cleared.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
=============================================================================*/
void interface_initialization_active(void)
{
    /* Send 80 clock ticks for card to power up */
    esdhc_base_pointer->system_control |= ESDHC_SYSCTL_INITA;

    /* Start a general purpose timer */
    GPT_delay(ESDHC_CARD_INIT_TIMEOUT);

    /* Wait for clearance of INITA bit */
    while(esdhc_base_pointer->system_control & ESDHC_SYSCTL_INITA)
    {
        /*
         * If some thing goes wrong with the eSDHC and INITA is not set
         * and if the timer expires after, return.
         */
        if(GPT_status() == TRUE)
        {
            break;
        }
    }

    /* Disable Timer */
    GPT_disable();
}

/*=============================================================================
FUNCTION:  interface_reset(UINT32 data_transfer_width, UINT32 endian_mode)         

DESCRIPTION: 
    Execute a software reset and set data bus width for eSDHC. 
    
ARGUMENTS PASSED:
    None
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
1.Reset the entire Host Controller except for the card detection circuit. 
  Done by writing 1 to RSTA bit in SYSCTRL register of eSDHC.

2. Set bus width for eSDHC.
==================================================================================================*/
UINT32 interface_reset(UINT32 data_transfer_width, UINT32 endian_mode)
{
    UINT32 reset_status = SUCCESS;

#ifdef TY_DBG
    {
        // Terry adds for debug, :-)
        U8 au8StrBuf[100] = { 0 };
        sprintf(au8StrBuf, "Ty, Entry: interface_reset\n");
        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
    }
#endif

    /* Reset the entire host controller by writing 1 to RSTA bit of SYSCTRL Register */
    esdhc_base_pointer->system_control |= ESDHC_SOFTWARE_RESET;

    /* Start a general purpose timer (3 millsec delay) */
    GPT_delay(ESDHC_OPER_TIMEOUT); 

    /* Wait for clearance of CIHB and CDIHB Bits */
    while(esdhc_base_pointer->system_control & ESDHC_SOFTWARE_RESET)
    {
        /* If some thing goes wrong with the ESDHC and int is not received
           and if the timer expires after 3 mill sec,return FALSE */
        if(GPT_status() == TRUE)
        {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, GPT Timeout!\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
            reset_status = FAIL;
            break;
        }
    }

    /* Disable Timer */
    GPT_disable();

    /* Set data bus width of ESDCH */
    esdhc_set_data_transfer_width(data_transfer_width);

    /* Set Endianness of ESDHC */
    esdhc_set_endianness(endian_mode);

    /* set data timeout delay to max */
    esdhc_base_pointer->system_control = (esdhc_base_pointer->system_control & 0xfff0ffff) | 0x000e0000;

#ifdef TY_DBG
    {
        // Terry adds for debug, :-)
        U8 au8StrBuf[100] = { 0 };
        sprintf(au8StrBuf, "Ty, Exit: interface_reset\n");
        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
    }
#endif

     return reset_status;
}


/*==================================================================================
FUNCTION: void interface_init(UINT32 base_address)

DESCRIPTION:
   Initialize eSDHC base address. 

ARGUMENTS PASSED:
   UINT32 base_address 

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
1. Initialize esdhc base pointer to basE_address.

==================================================================================================*/
void interface_init(UINT32 base_address)
{
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Entry, interface_init");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    esdhc_base_pointer = (pESDHC_t)base_address;

    /* Initialize IOMUX registers for eSDHC module */
    esdhc_iomux_configuration();

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Exit, interface_init");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
}

/*=============================================================================
FUNCTION: void interface_clear_interrupt(void)

DESCRIPTION:
   Clear interrupts at eSDHC level.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
1. Clear the eSDHC interrupt.
=============================================================================*/
void interface_clear_interrupt(void)
{
    /* Clear Interrupt status register */
    esdhc_base_pointer->interrupt_status = ESDHC_CLEAR_INTERRUPT;
}

/*==================================================================================================

FUNCTION: void interface_configure_clock(sdhc_freq_t)         

DESCRIPTION: 
    Enable Clock and set operating frequency for . 
    
ARGUMENTS PASSED:
    None
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
1.	Set DTOCV and SDCLKFS bit to get SD_CLK of frequency around 400 KHz.
2.	Enable Clock for e-SDHC by setting IPG_PERCLK, HCLK.

==================================================================================================*/
void interface_configure_clock(sdhc_freq_t frequency)
{
    /* Clear SDCLKEN bit */
    //esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_SDCLKEN_MASK);

    /* Clear DTOCV, SDCLKFS, DVFS bits */
    esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_FREQ_MASK);

    /* Disable the PEREN, HCKEN and IPGEN */
    esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_INPUT_CLOCK_MASK);

    if(frequency == IDENTIFICATION_FREQ)
    {
        esdhc_base_pointer->system_control |= ESDHC_SYSCTL_IDENT_FREQ;
    }
    else if(frequency == OPERATING_FREQ)
    {
        esdhc_base_pointer->system_control |= ESDHC_SYSCTL_OPERT_FREQ;
    }

    /* Start a general purpose timer */
    //GPT_delay(ESDHC_OPER_TIMEOUT);

    /* Wait for clock to be stable */
    //while(!(esdhc_base_pointer->present_state & ESDHC_PRSSTAT_SDSTB_BIT))
    //{
        /* Check for GPT status */
        //if(GPT_status() == TRUE)
        //{
            //break;
//        }
//    }

    /* Disable Timer */
//    GPT_disable();

    /* Set SDCLKEN bit to enable clock */
//    esdhc_base_pointer->system_control |= ESDHC_SYSCTL_SDCLKEN_MASK;

    /* Mask Data Timeout Error Status Enable Interrupt (DTOESEN) */
    esdhc_base_pointer->interrupt_status_enable &= (~ESDHC_IRQSTATEN_DTOESEN);

    /* Set the Data Timeout Counter Value(DTOCV) */
    esdhc_base_pointer->system_control |= ESDHC_SYSCTL_DTOCV_VAL;

    /* Enable Data Timeout Error Status Enable Interrupt (DTOESEN) */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_IRQSTATEN_DTOESEN;
}

/*==================================================================================================

FUNCTION: static void esdhc_set_data_transfer_width(UINT32 data_transfer_width)         

DESCRIPTION: 
    Set data transfer width for e-SDHC. . 
    
ARGUMENTS PASSED:
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
1. Set DWT bit of protocol control register according to bus_width.

==================================================================================================*/

static void esdhc_set_data_transfer_width(UINT32 data_transfer_width)
{
    /*
     * Set DWT bit of protocol control register according to bus_width
     * 2-1->DTW[1:0]:
     *      00b) 1-bit mode
     *      01b) 4-bit mode
     *      10b) 8-bit mode
     *      11b) Reserved
     */
    esdhc_base_pointer->protocol_control =
            (esdhc_base_pointer->protocol_control & (~ ESDHC_BUS_WIDTH_MASK))
            | data_transfer_width;
   
}

/*==================================================================================================

FUNCTION: static void esdhc_set_endianness(UINT32 endian_mode)         

DESCRIPTION: 
    Set endianness mode for e-SDHC. . 
    
ARGUMENTS PASSED:
    endian_mode_t  endianness
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
1. . Set the EMODE bit of protocol control register according to endianness.

==================================================================================================*/

static void esdhc_set_endianness(UINT32 endian_mode)
{
   /* Clear DWT bit of protocol control register according to endianess */
    esdhc_base_pointer->protocol_control &= ~(ESDHC_ENDIAN_MODE_MASK);

    /* Set DWT bit of protocol control register */
    esdhc_base_pointer->protocol_control |= endian_mode;
}

/*=============================================================================
FUNCTION: UINT32 esdhc_poll_cihb_cdihb(data_present_select data_present)

DESCRIPTION:
    Poll the CIHB & CDIHB bits of the present state register and wait until
    it goes low.

ARGUMENTS PASSED:
    data_present_select data_present

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
static UINT32 esdhc_poll_cihb_cdihb(data_present_select data_present)
{
    UINT32 init_status = SUCCESS;

    /* Start a general purpose timer */
    GPT_delay(ESDHC_OPER_TIMEOUT);

    /*
     * Wait for the command line to be free (poll the CIHB bit of the present
     * state register)
     */
    while((esdhc_base_pointer->present_state & ESDHC_PRESENT_STATE_CIHB) ==
           ESDHC_PRESENT_STATE_CIHB)
    {
        /*
         * If some thing goes wrong with the eSDHC and INTR is not received
         * and if the timer expires, return FAIL.
         */
        if(GPT_status() == TRUE)
        {
            init_status = FAIL;
            break;
        }
    }

    /* Disable Timer */
    GPT_disable();

    /*
     * Wait for the data line to be free (poll the CDIHB bit of
     * the present state register).
     */
    if((init_status == SUCCESS) && (data_present == DATA_PRESENT))
    {
        /* Start a general purpose timer */
        GPT_delay(ESDHC_STATUS_TIME_OUT_READ);

        while((esdhc_base_pointer->present_state & ESDHC_PRESENT_STATE_CDIHB) ==
               ESDHC_PRESENT_STATE_CDIHB)
        {
            /*
             * If some thing goes wrong with the eSDHC and int is not received
             * and if the timer expires, return FAIL
             */
            if(GPT_status() == TRUE)
            {
                init_status =  FAIL ;
                break;
            }
        }

        /* Disable Timer */
        GPT_disable();
    }

    return init_status;
}

/*=============================================================================
FUNCTION: UINT32 interface_wait_cmd_data_line(data_present_select data_present)

DESCRIPTION:
    Wait until the command and data lines are free.

ARGUMENTS PASSED:
    data_present_select data_present

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
UINT32 interface_wait_cmd_data_lines(data_present_select data_present)
{
    UINT32 cmd_status = SUCCESS;

    cmd_status = esdhc_poll_cihb_cdihb(data_present);

    return cmd_status;
}

/*==================================================================================================

FUNCTION: interface_send_cmd_wait_resp        

DESCRIPTION: 
    execute a command and wait for the response

ARGUMENTS PASSED:
    COMMAND_t * - a pointer to structure defining a command
    
RETURN VALUE:
    SUCCESS if the response is OK
    FAIL otherwise

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None

IMPORTANT NOTES:
    
==================================================================================================*/

UINT32 interface_send_cmd_wait_resp(command_t *cmd)
{
    UINT32 cmd_status = SUCCESS;

    /* Clear Interrupt status register */
    esdhc_base_pointer->interrupt_status = ESDHC_CLEAR_INTERRUPT;

    /* Enable Interrupt */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_INTERRUPT_ENABLE;

    /* Before sending any command, check for CMD and data line release */
    cmd_status = interface_wait_cmd_data_lines(cmd->data_present);

    if(cmd_status == FAIL)
    {
#ifdef TY_DBG
        {
	        // Terry adds for debug, :-)
	        U8 au8StrBuf[100] = { 0 };
	        sprintf(au8StrBuf, "Ty, interface_wait_cmd_data_lines failed!\n");
	        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
        }
#endif
        return FAIL;
    }

    /* Configure Command */
    esdhc_cmd_config(cmd);

    /* Wait for interrupt CTOE or CC */
    esdhc_wait_end_cmd_resp_intr();

    /* Mask all interrupts */
    esdhc_base_pointer->interrupt_signal_enable = ZERO;

    /* Check if an error occured */
    return esdhc_check_response();
}

/*==================================================================================================
FUNCTION: esdhc_cmd_config          

DESCRIPTION: 
    Configure ESDHC registers for sending a command to MMC.

ARGUMENTS PASSED:
    COMMAND_t * - a pointer to structure defining a command
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
 
static void esdhc_cmd_config(command_t *cmd)                                                           
{
   
    /* Write Command Argument in Command Argument Register */
    esdhc_base_pointer->command_argument = cmd->arg;

    /* 
    *Configure e-SDHC Register value according to Command
    */
    esdhc_base_pointer->command_transfer_type = (((cmd->data_transfer)<<ESDHC_DATA_TRANSFER_SHIFT) | 
					     ((cmd->response_format)<<ESDHC_RESPONSE_FORMAT_SHIFT) |
	                                     ((cmd->data_present)<<ESDHC_DATA_PRESENT_SHIFT) | 
	                                     ((cmd->crc_check) << ESDHC_CRC_CHECK_SHIFT) | 
	                                     ((cmd->cmdindex_check) << ESDHC_CMD_INDEX_CHECK_SHIFT) | 
                                         ((cmd->command) << ESDHC_CMD_INDEX_SHIFT) | 
										 ((cmd->block_count_enable_check) << ESDHC_BLOCK_COUNT_ENABLE_SHIFT) |
										 ((cmd->multi_single_block) << ESDHC_MULTI_SINGLE_BLOCK_SELECT_SHIFT));
	                                
}


/*==================================================================================================

FUNCTION: esdhc_wait_end_cmd_resp_intr          

DESCRIPTION: 
    Wait a END_CMD_RESP interrupt by interrupt status register. e-SDHC sets this bit after
    receving command response.
    
ARGUMENTS PASSED:
    None
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
 
static void esdhc_wait_end_cmd_resp_intr(void)
{
    /* Wait interrupt (END COMMAND RESPONSE)
    */
    /* Start a general purpose timer (3 millsec delay) */
    GPT_delay(ESDHC_OPER_TIMEOUT);
	 
    while(!((esdhc_base_pointer->interrupt_status) & ESDHC_STATUS_END_CMD_RESP_TIME_MSK))
    {
         /* If some thing goes wrong with the ESDHC and int is not received
            and if the timer expires after 3 mill sec,return FALSE */
           if(GPT_status() == TRUE)
           {
#ifdef TY_DBG
            {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty,GPT Timeoout,interrupt_status:%d\n", esdhc_base_pointer->interrupt_status);
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
              break;
           }
    }

    /* Disable Timer */
    GPT_disable();

}


/*==================================================================================================

FUNCTION: esdhc_check_response          
.
DESCRIPTION: 
    Check whether the interrupt is an END_CMD_RESP  
	or a response time out or a CRC error or command index error. 

ARGUMENTS PASSED:
    None
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
 
static UINT32 esdhc_check_response(void)
{
    UINT32 status = FAIL;
	
    /* Check whether the interrupt is an END_CMD_RESP  
    * or a response time out or a CRC error 
    */ 		
    if((esdhc_base_pointer->interrupt_status & ESDHC_STATUS_END_CMD_RESP_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_RESP_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CRC_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_INDEX_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_END_BIT_ERR_MSK))
    {
        status = SUCCESS;
    }

#ifdef TY_DBG
	{
        esdhc_dump_register();
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, chk_resp: interrupt_status: %d, judge: %d result: %d\n", esdhc_base_pointer->interrupt_status, ((esdhc_base_pointer->interrupt_status & ESDHC_STATUS_END_CMD_RESP_MSK) &&
	!(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_RESP_MSK) &&
	!(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CRC_ERR_MSK) &&
    !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_INDEX_ERR_MSK) &&
    !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_END_BIT_ERR_MSK)), status);
        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
        memset(au8StrBuf, 0, 100);
        sprintf(au8StrBuf, "Ty, 1:%d 2:%d 3:%d 4:%d 5:%d", esdhc_base_pointer->interrupt_status & ESDHC_STATUS_END_CMD_RESP_MSK, esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_RESP_MSK, esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CRC_ERR_MSK, esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_INDEX_ERR_MSK, esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_END_BIT_ERR_MSK);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif
	
    return status;
			
}

/*==================================================================================================

FUNCTION: void interface_read_response ( command_response_t* esdhc_rsp)          
.
DESCRIPTION: 
    This function will read response from e-SDHC register according to reponse format.

ARGUMENTS PASSED:
    command_response* esdhc_rsp
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/

void interface_read_response (command_response_t *cmd_resp)
{
    // Convert resp register to cmd_resp, for resp registers shift 8 bits
    switch (cmd_resp->format)
    {
        case RESPONSE_136:
            cmd_resp->cmd_rsp3 = (esdhc_base_pointer->command_response3 << 8) | (esdhc_base_pointer->command_response2 >> 24);
            cmd_resp->cmd_rsp2 = (esdhc_base_pointer->command_response2 << 8) | (esdhc_base_pointer->command_response1 >> 24);
            cmd_resp->cmd_rsp1 = (esdhc_base_pointer->command_response1 << 8) | (esdhc_base_pointer->command_response0 >> 24);
            cmd_resp->cmd_rsp0 = esdhc_base_pointer->command_response0 << 8;
            break;
        case RESPONSE_48:
        case RESPONSE_48_CHECK_BUSY:
        default:
            /* get response values from e-SDHC CMDRSP registers.*/
            cmd_resp->cmd_rsp0 = (UINT32)esdhc_base_pointer->command_response0;
            cmd_resp->cmd_rsp1 = (UINT32)esdhc_base_pointer->command_response1;
            cmd_resp->cmd_rsp2 = (UINT32)esdhc_base_pointer->command_response2;
            cmd_resp->cmd_rsp3 = (UINT32)esdhc_base_pointer->command_response3;
            break;
    }
}

/*==================================================================================================

FUNCTION: UINT32 interface_data_read (UINT32 *,UINT32 )          
.
DESCRIPTION: 
    This function will read response from e-SDHC register according to reponse format.

ARGUMENTS PASSED:
   UINT32 * dest_ptr
   UINT32 blk_len
 
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/

UINT32 interface_data_read (UINT32 *dest_ptr,UINT32 blk_len)
{
    UINT32 i = ZERO;
    UINT32 j = ZERO;
    UINT32 status = FAIL;
    UINT32 block_count = ZERO;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Entry: interface_data_read!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    if((blk_len) <= (ESDHC_FIFO_SIZE * FOUR))
    {
        block_count = 1;
    }
    else
    {
        block_count = (blk_len)/(ESDHC_FIFO_SIZE * FOUR);
    }

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, blk_len:%d,block_count:%d!\n", blk_len, block_count);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    /* Enable Interrupt */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_INTERRUPT_ENABLE;

    for(i = ZERO; i < block_count; i++)
    {
        INT32 fifo_size = ZERO;

        if((blk_len) < (ESDHC_FIFO_SIZE * FOUR))
        {
            fifo_size = (blk_len/FOUR);
        }
        else
        {
            fifo_size = ESDHC_FIFO_SIZE;
        }

        /* Wait for BRR bit to be set */
        status = esdhc_wait_buf_rdy_intr(ESDHC_STATUS_BUF_READ_RDY_MSK,
                                         ESDHC_READ_DATA_TIME_OUT);

        if(status == SUCCESS)
        {
            for(j = ZERO; j < fifo_size; j++)
            {
                *dest_ptr = esdhc_base_pointer->data_buffer_access;

                /* Increment destination pointer */
                dest_ptr++;

                /* Decement block length by data read */
                blk_len -= (FOUR);
            }

            /* Clear the BRR */
            esdhc_clear_buf_rdy_intr(ESDHC_STATUS_BUF_READ_RDY_MSK);
        }
        else
        {
            break;
        }
    }

    if((esdhc_check_op_done == SUCCESS) && (status == SUCCESS))
    {
        /* Wait for transfer complete operation interrupt */
        esdhc_wait_op_done_intr();

        /* Check for status errors */
        status = esdhc_check_data();
    }

    if((esdhc_check_op_done == FAIL) && (status == SUCCESS))
    {
        status = esdhc_check_data_crc_status();
    }

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Exit: interface_data_read!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    return status;
}

/*==================================================================================================

FUNCTION: esdhc_wait_buf_rdy_intr         

DESCRIPTION: 
    Wait a BUF_READ_READY  interrupt by pooling STATUS register.

ARGUMENTS PASSED:
    unsigned int - an integer defining the mask to be applied on the STATUS
    					register
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
static UINT32 esdhc_wait_buf_rdy_intr(UINT32 mask, UINT32 timeout)
{
    UINT32 status = SUCCESS;
    
    /* Wait interrupt (BUF_READ_RDY)
    */
   
   /* Start a general purpose timer (3 millsec delay) */
    GPT_delay(timeout);
 
    while(!(esdhc_base_pointer->interrupt_status & mask))
    {
        /* If some thing goes wrong with the ESDHC and int is not received
          and if the timer expires after 3 mill sec,return FALSE */
         if(GPT_status() == TRUE)
         {
#ifdef TY_DBG
			{
			    // Terry adds for debug, :-)
			    U8 au8StrBuf[100] = { 0 };
			    sprintf(au8StrBuf, "Ty, GPT Timeout in esdhc_wait_buf_rdy_intr!\n");
			    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
			}
#endif
             status = FAIL;
             break;
         }
    }

    /* Disable Timer */
    GPT_disable();

    return status;
}

/*=============================================================================
FUNCTION: void esdhc_clear_buf_rdy_intr(UINT32 mask)

DESCRIPTION:
    Clear BUF_READ_READY/BUF_WRITE_READY interrupt by writing 1 to STATUS register.

ARGUMENTS PASSED:
    UINT32 mask - An integer defining the mask to be applied on the STATUS
                  register

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
static void esdhc_clear_buf_rdy_intr(UINT32 mask)
{
    esdhc_base_pointer->interrupt_status = mask;
}

/*=============================================================================
FUNCTION: void esdhc_wait_op_done_intr(void)

DESCRIPTION:
    Wait for TC, DEBE, DCE or DTOE by polling Interrupt STATUS register.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
static void esdhc_wait_op_done_intr(void)
{
    while(!(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_DATA_RW_MSK));
}

/*==================================================================================================

FUNCTION: esdhc_check_data         

DESCRIPTION: 
    If READ_OP_DONE occured check ESDHC_STATUS_TIME_OUT_READ and RD_CRC_ERR_CODE and 
    to determine if an error occured

ARGUMENTS PASSED:
    UINT32 - an integer defining the Transfer complete mask to be 
    			   applied on the STATUS register
    			   
    UINT32 - an integar defining the ESDHC read data time out error.
    			   
    UINT32 - an integer defining the READ_CRC_ERR mask 
   				   to be applied on the STATUS register
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
 
static UINT32 esdhc_check_data(void)  
{	
	
    UINT32 status = FAIL;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: esdhc_check_data()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, interrupt_status:%d,done:%d,timeout:%d,crc:%d", 
                esdhc_base_pointer->interrupt_status, 
                (esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TRANSFER_COMPLETE_MSK),
                (esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_READ_MASK),
                (esdhc_base_pointer->interrupt_status & ESDHC_STATUS_READ_CRC_ERR_MSK),
                (esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RW_DATA_END_BIT_ERR_MSK));
        
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Check whether the interrupt is an OP_DONE  
    * or a data time out or a CRC error 
    */ 		
    if((esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TRANSFER_COMPLETE_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_READ_MASK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_READ_CRC_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RW_DATA_END_BIT_ERR_MSK))
    {
        esdhc_base_pointer->interrupt_status = ESDHC_STATUS_TRANSFER_COMPLETE_MSK;

        status = SUCCESS;
    }
    else
    {
        status = FAIL;
    }
    		
	
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: esdhc_check_data()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return status;
}

/*=============================================================================
FUNCTION: UINT32 esdhc_check_data_crc_status(void)

DESCRIPTION:
    Check for Data timeout error, data CRC error and data end bit error
    to determine if an error occured.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
static UINT32 esdhc_check_data_crc_status(void)
{
    UINT32 status = FAIL;

    /* Check whether the interrupt is DTOE/DCE/DEBE */
    if(!(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_READ_MASK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_READ_CRC_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RW_DATA_END_BIT_ERR_MSK))
    {
        status = SUCCESS;
    }
    else
    {
        status = FAIL;
    }

    return status;
}

/*==================================================================================================

FUNCTION: interface_config_block_info          

DESCRIPTION: 
    Set Block length.

ARGUMENTS PASSED:
    U32 - the length of the block to be transfered
    
RETURN VALUE:
    None

PRE-CONDITIONS:
    None
 
POST-CONDITIONS:
    None
   
IMPORTANT NOTES:
    None
==================================================================================================*/
 
void interface_config_block_info(UINT32 blk_len, UINT32 nob, UINT32 wml)
{
    /* Configure Block length as 512 byte in block attribute register */
   //esdhc_base_pointer->block_attributes = ESDHC_CONFIG_BLOCK;

   /* Configre block Attributes register */
   esdhc_base_pointer->block_attributes = ((nob<<ESDHC_BLOCK_SHIFT) | blk_len);

   /* Set Read Water MArk Level register */
   esdhc_base_pointer->watermark_level = wml; 
}




/*=================================================================================
=================

FUNCTION: UINT32 interface_data_write (UINT32 *,UINT32 )
.
DESCRIPTION:
    This function will write data to device  attached to interface

ARGUMENTS PASSED:
   UINT32 * dest_ptr
   UINT32 blk_len

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
===================================================================================
===============*/

UINT32 interface_data_write (UINT32 *dest_ptr,UINT32 blk_len)
{
    UINT32 i=0;
    UINT32 status = FAIL;

#ifdef TY_DBG
	{
	    // Terry adds for debug, :-)
	    U8 au8StrBuf[100] = { 0 };
	    sprintf(au8StrBuf, "Ty, Entry: interface_data_write!\n");
	    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[300] = { 0 };
		sprintf(au8StrBuf, "Ty, interrupt_status:%d,present_state:%d,protocol_control:%d,system_control:%d, command_transfer_type:%d, block_attributes:%d, watermark_level:%d\n", esdhc_base_pointer->interrupt_status, esdhc_base_pointer->present_state, esdhc_base_pointer->protocol_control, esdhc_base_pointer->system_control, esdhc_base_pointer->command_transfer_type, esdhc_base_pointer->block_attributes, esdhc_base_pointer->watermark_level);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Enable Interrupt */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_INTERRUPT_ENABLE;

    for(i = 0; i < (blk_len)/FOUR; i++)
    {
        /* Wait for BWR bit to be set */
        status = esdhc_wait_buf_rdy_intr(ESDHC_STATUS_BUF_WRITE_RDY_MSK, SINGLE);

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, status:%d,blk_len:%d,loop:%d!\n", status, blk_len, (blk_len)/FOUR);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        if(status == SUCCESS)
        {
            esdhc_base_pointer->data_buffer_access = *dest_ptr;

            /*increment destination pointer */
            dest_ptr++;
        }
    }

    if(status == SUCCESS)
    {
        /* Wait for transfer complete operation interrupt */
        esdhc_wait_op_done_intr();
    
        /* Check for status errors */
        status = esdhc_check_data();
    }

#ifdef TY_DBG
	{
	    // Terry adds for debug, :-)
	    U8 au8StrBuf[100] = { 0 };
	    sprintf(au8StrBuf, "Ty, Exit: interface_data_write!\n");
	    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return status;
       
}

/*=============================================================================
FUNCTION: void esdhc_iomux_configuration(void)

DESCRIPTION:
    Do the IOMUX configuration for eSDHC ports

ARGUMENTS PASSED:
    None

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
#define HAPI_BT_SDMMC_SRC        (0x00000200)
#define HAPI_BT_SDMMC_SRC_SHIFT  (9)
#define hapi_src_reg             (0xe3f94000)
#define hapi_src_reg_src_sbmr    (hapi_src_reg + (4))

static void esdhc_iomux_configuration(void)
{
    UINT32 interface_esdhc = 0;

    //interface_esdhc = HAPI_IC_ID_BT_SDMMC_SRC_READ();
    interface_esdhc = ((*(VP_U32)(hapi_src_reg_src_sbmr)) & HAPI_BT_SDMMC_SRC) >> HAPI_BT_SDMMC_SRC_SHIFT;

    /* IOMUX PROGRAMMING */
    if(interface_esdhc == ESDHC1)
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC1");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        esdhc_base_pointer = (pESDHC_t)esdhc_1_regs_base_address;

        HAPI_GPIO_config(HAPI_IOMUX_SD1_CMD_PORT,HAPI_IOMUX_SD1_CMD_PIN,
                         HAPI_IOMUX_SD1_CMD_SEL,HAPI_IOMUX_SD1_CMD_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD1_CLK_PORT,HAPI_IOMUX_SD1_CLK_PIN,
                         HAPI_IOMUX_SD1_CLK_SEL,HAPI_IOMUX_SD1_CLK_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD1_DATA0_PORT,HAPI_IOMUX_SD1_DATA0_PIN,
                         HAPI_IOMUX_SD1_DATA0_SEL,HAPI_IOMUX_SD1_DATA0_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD1_DATA1_PORT,HAPI_IOMUX_SD1_DATA1_PIN,
                         HAPI_IOMUX_SD1_DATA1_SEL,HAPI_IOMUX_SD1_DATA1_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD1_DATA2_PORT,HAPI_IOMUX_SD1_DATA2_PIN,
                         HAPI_IOMUX_SD1_DATA2_SEL,HAPI_IOMUX_SD1_DATA2_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD1_DATA3_PORT,HAPI_IOMUX_SD1_DATA3_PIN,
                         HAPI_IOMUX_SD1_DATA3_SEL,HAPI_IOMUX_SD1_DATA3_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD2_DATA0_PORT,HAPI_IOMUX_SD2_DATA0_PIN,
                         HAPI_IOMUX_SD2_DATA0_SEL,HAPI_IOMUX_SD2_DATA0_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD2_DATA1_PORT,HAPI_IOMUX_SD2_DATA1_PIN,
                         HAPI_IOMUX_SD2_DATA1_SEL,HAPI_IOMUX_SD2_DATA1_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD2_DATA2_PORT,HAPI_IOMUX_SD2_DATA2_PIN,
                         HAPI_IOMUX_SD2_DATA2_SEL,HAPI_IOMUX_SD2_DATA2_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_SD2_DATA3_PORT,HAPI_IOMUX_SD2_DATA3_PIN,
                         HAPI_IOMUX_SD2_DATA3_SEL,HAPI_IOMUX_SD2_DATA3_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_PAD_GPIO1_4_PORT,HAPI_IOMUX_PAD_GPIO1_4_PIN,
                         HAPI_IOMUX_PAD_GPIO1_4_SEL,HAPI_IOMUX_PAD_GPIO1_4_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_PAD_GPIO1_5_PORT,HAPI_IOMUX_PAD_GPIO1_5_PIN,
                         HAPI_IOMUX_PAD_GPIO1_5_SEL,HAPI_IOMUX_PAD_GPIO1_5_DIR);
        HAPI_GPIO_config(HAPI_IOMUX_PAD_GPIO1_6_PORT,HAPI_IOMUX_PAD_GPIO1_6_PIN,
                         HAPI_IOMUX_PAD_GPIO1_6_SEL,HAPI_IOMUX_PAD_GPIO1_6_DIR);

       /* Configure PAD setting for MMC/SD */
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,65,0x0190);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,66,0x00d0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,67,0x01d0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,68,0x01d0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,69,0x01d0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,70,0x01A0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,73,0x0190);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,74,0x0190);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,75,0x0190);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,76,0x0190);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,146,0x01e0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,147,0x01e0);
       HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,148,0x0005);
    }
    else if(interface_esdhc == ESDHC3)
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC3");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        esdhc_base_pointer = (pESDHC_t)esdhc_3_regs_base_address;

        HAPI_GPIO_config(HAPI_IOMUX_NANDF_WE_B_PORT,HAPI_IOMUX_NANDF_WE_B_PIN,
                         HAPI_IOMUX_NANDF_WE_B_SEL,HAPI_IOMUX_NANDF_WE_B_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_RE_B_PORT,HAPI_IOMUX_NANDF_RE_B_PIN,
                         HAPI_IOMUX_NANDF_RE_B_SEL,HAPI_IOMUX_NANDF_RE_B_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_ALE_PORT,HAPI_IOMUX_NANDF_ALE_PIN,
                         HAPI_IOMUX_NANDF_ALE_SEL,HAPI_IOMUX_NANDF_ALE_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_CLE_PORT,HAPI_IOMUX_NANDF_CLE_PIN,
                         HAPI_IOMUX_NANDF_CLE_SEL,HAPI_IOMUX_NANDF_CLE_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_WP_B_PORT,HAPI_IOMUX_NANDF_WP_B_PIN,
                         HAPI_IOMUX_NANDF_WP_B_SEL,HAPI_IOMUX_NANDF_WP_B_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_RB_PORT,HAPI_IOMUX_NANDF_RB_PIN,
                         HAPI_IOMUX_NANDF_RB_SEL,HAPI_IOMUX_NANDF_RB_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS0_PORT,HAPI_IOMUX_NANDF_CS0_PIN,
                         HAPI_IOMUX_NANDF_CS0_SEL,HAPI_IOMUX_NANDF_CS0_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS1_PORT,HAPI_IOMUX_NANDF_CS1_PIN,
                         HAPI_IOMUX_NANDF_CS1_SEL,HAPI_IOMUX_NANDF_CS1_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS2_PORT,HAPI_IOMUX_NANDF_CS2_PIN,
                         HAPI_IOMUX_NANDF_CS2_SEL,HAPI_IOMUX_NANDF_CS2_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS3_PORT,HAPI_IOMUX_NANDF_CS3_PIN,
                         HAPI_IOMUX_NANDF_CS3_SEL,HAPI_IOMUX_NANDF_CS3_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_DI1_PIN12_PORT,HAPI_IOMUX_DI1_PIN12_PIN,
                         HAPI_IOMUX_DI1_PIN12_SEL,HAPI_IOMUX_DI1_PIN12_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_DI1_D0_CS_PORT,HAPI_IOMUX_DI1_D0_CS_PIN,
                         HAPI_IOMUX_DI1_D0_CS_SEL,HAPI_IOMUX_DI1_D0_CS_DIR);
       HAPI_GPIO_config(HAPI_IOMUX_GPIO1_1_PORT,HAPI_IOMUX_GPIO1_1_PIN,
                         HAPI_IOMUX_GPIO1_1_SEL,HAPI_IOMUX_GPIO1_1_DIR);

      /* Configure PAD for ESDHC3 */
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,39,0x0190);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,40,0x0190);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,41,0x0190);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,42,0x0190);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,43,0x01E0);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,44,0x01d0);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,45,0x0110);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,46,0x0110);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,47,0x0050);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,48,0x0110);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,110,0x0140);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,112,0x0140);
      HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,163,0x0004);
    }
    else
    {
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, wrong ESDHC!");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
    }
}

/*=============================================================================
FUNCTION: void esdhc_set_cmd_pullup(esdhc_pullup_t pull_up)

DESCRIPTION:
    Configure the CMD line PAD configuration for strong or weak pull-up

ARGUMENTS PASSED:
    esdhc_pullup_t pull_up - STRONG: strong pull-up, WEAK: weak pull-up

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
=============================================================================*/
void esdhc_set_cmd_pullup(esdhc_pullup_t pull_up)
{
    UINT32 interface_esdhc = 0;

    //interface_esdhc = HAPI_IC_ID_BT_SDMMC_SRC_READ();
    interface_esdhc = ((*(VP_U32)(hapi_src_reg_src_sbmr)) & HAPI_BT_SDMMC_SRC) >> HAPI_BT_SDMMC_SRC_SHIFT;

    if(pull_up == STRONG)
    {
        /* Configure strong pull-up on CMD line */
        if(interface_esdhc == ESDHC1)
        {
            /* CMD PAD control */
            /*HYS = 1;PKE=1 ; PUS :11'b 22K Pullup */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,65,0x01B0);
        }
        else if(interface_esdhc == ESDHC3)
        {
            /* CMD PAD control */
            /*HYS = 1;PKE = 1;PUE = 1;PUS = 11'b 22K PU*/
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,48,0x0130);
        }
    }
    else if(pull_up == WEAK)
    {
        /* Configure weak pull-up on CMD line */
        if(interface_esdhc == ESDHC1)
        {
            /* CMD PAD control */
            /*HYS = 1;PKE=1 ; PUS :10'b 100K Pullup */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,65,0x01A0);
        }
        else if(interface_esdhc == ESDHC3)
        {
            /* CMD PAD control */
            /*HYS = 1;PKE = 1;PUE = 1;PUS = 10'b 100K PU*/
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,48,0x0120);
        }
    }
}

#ifdef TY_DBG
UINT32 esdhc_dump_register()
{

#define ESDHC_REG_NUM           20

    typedef struct reg_info {
        U8 *reg_name;
        U32 *reg_address;
    };

    struct reg_info aRegInfoAry[ESDHC_REG_NUM] = {
         {"dma_system_address", &(esdhc_base_pointer->dma_system_address)},
         {"block_attributes", &(esdhc_base_pointer->block_attributes)},
         {"command_argument", &(esdhc_base_pointer->command_argument)},
         {"command_transfer_type", &(esdhc_base_pointer->command_transfer_type)},
         {"command_response0", &(esdhc_base_pointer->command_response0)},
         {"command_response1", &(esdhc_base_pointer->command_response1)},
         {"command_response2", &(esdhc_base_pointer->command_response2)},
         {"command_response3", &(esdhc_base_pointer->command_response3)},
         {"data_buffer_access", &(esdhc_base_pointer->data_buffer_access)},
         {"present_state", &(esdhc_base_pointer->present_state)},
         {"protocol_control", &(esdhc_base_pointer->protocol_control)},
         {"system_control", &(esdhc_base_pointer->system_control)},
         {"interrupt_status", &(esdhc_base_pointer->interrupt_status)},
         {"interrupt_status_enable", &(esdhc_base_pointer->interrupt_status_enable)},
         {"interrupt_signal_enable", &(esdhc_base_pointer->interrupt_signal_enable)},
         {"autocmd12_status", &(esdhc_base_pointer->autocmd12_status)},
         {"host_controller_capabilities", &(esdhc_base_pointer->host_controller_capabilities)},
         {"watermark_level", &(esdhc_base_pointer->watermark_level)},
         {"force_event", &(esdhc_base_pointer->force_event)},
         {"host_controller_version", &(esdhc_base_pointer->host_controller_version)},
     };

    U8 i = 0;

    for (i = 0; i < ESDHC_REG_NUM; ++i)
    {
        U8 au8StrBuf[100] = { 0 };
        U8 au8Str1[50] = { 0 };
        U8 *pu8Str2 = ": \%d\n";

        memcpy(au8Str1, aRegInfoAry[i].reg_name, strlen(aRegInfoAry[i].reg_name));
        strcat(au8Str1, pu8Str2);

        sprintf(au8StrBuf, au8Str1, *(aRegInfoAry[i].reg_address));

        atk_channel_send(au8StrBuf, strlen(au8StrBuf));
    }

    return 0;
}
#endif
