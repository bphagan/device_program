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
#if defined (REV_TO1)
#include "hapi_gpio_defs_to1.h"
#elif defined (REV_TO2)
#include "hapi_gpio_defs_to2.h"
#endif
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

#define IOMUXC_BASE_ADDR                (0x73fa8000)
#define GPIO1_BASE_ADDR                 (0x73f84000)
#define GPIO2_BASE_ADDR                 (0x73f88000)
#define GPIO3_BASE_ADDR                 (0x73f8c000)

#if defined (REV_TO1)
static VP_U32 const iomux_sw_mux_ctrl_reg_array[3] = 
{
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x001c),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x03f8),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0928)
};
#elif defined (REV_TO2)
static VP_U32 const iomux_sw_mux_ctrl_reg_array[3] = 
{
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x001c),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x03f0),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x08c4)
};
#endif

static VP_U32 const data_dir_reg_ptr_array[3] = {
    (UINT32 *) ((UINT32) GPIO1_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO2_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO3_BASE_ADDR + 4)
};

#define esdhc_1_regs_base_address       (0x70004000)
#define esdhc_2_regs_base_address       (0x70008000)
#define esdhc_3_regs_base_address       (0x70020000)
#define esdhc_4_regs_base_address       (0x70024000)

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

/*==================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void esdhc_cmd_config(command_t *);
static void esdhc_wait_end_cmd_resp_intr(void);
static UINT32 esdhc_check_response(void);
static UINT32 esdhc_wait_buf_rdy_intr(UINT32, UINT32, multi_single_block_select);
static void esdhc_wait_op_done_intr(void);
static UINT32 esdhc_check_data(void);
static void esdhc_set_data_transfer_width(UINT32 data_transfer_width);
static UINT32 esdhc_poll_cihb_cdihb(data_present_select data_present);
static void esdhc_set_endianness(UINT32 endian_mode);
static void esdhc_clear_buf_rdy_intr(UINT32 mask);
static void esdhc_iomux_configuration(void);
static UINT32 esdhc_check_data_crc_status(void);
#if defined (REV_TO1)
static void esdhc_registers_save(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr);
static void esdhc_registers_get(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr);
#endif
#ifdef TY_DBG
static UINT32 esdhc_dump_register();
#endif
/*==================================================================================================

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
==================================================================================================*/
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

/*==================================================================================================

FUNCTION: UINT32 interface_reset(UINT32 data_transfer_width, UINT32 endian_mode)

DESCRIPTION:
    Execute a software reset and set data bus width and endianness for eSDHC.

ARGUMENTS PASSED:
    UINT32 data_transfer_width, UINT32 endian_mode

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
1. Reset the entire Host Controller except for the card detection circuit.
   Done by writing 1 to RSTA bit in SYSCTRL register of eSDHC.
2. Poll for RSTA bit to get clear.
3. Set bus width and endianness for eSDHC.
==================================================================================================*/
UINT32 interface_reset(UINT32 data_transfer_width, UINT32 endian_mode)
{
    UINT32 reset_status = SUCCESS;

    /* Reset the eSDHC by writing 1 to RSTA bit of SYSCTRL Register */
    esdhc_base_pointer->system_control |= ESDHC_SOFTWARE_RESET;

    /* Start a general purpose timer */
    GPT_delay(ESDHC_OPER_TIMEOUT);

    /* Wait for clearance of rest bit */
    while(esdhc_base_pointer->system_control & ESDHC_SOFTWARE_RESET)
    {
        /*
         * If some thing goes wrong with the eSDHC and INT is not received
         * and if the timer expires, return FAIL
         */
        if(GPT_status() == TRUE)
        {
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

    return reset_status;
}

/*=============================================================================
FUNCTION: void interface_reset_data_line(void)

DESCRIPTION:
    Execute a Software Reset For DATA Line.

ARGUMENTS PASSED:
    None

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
1. Software Reset For CMD Line.
=============================================================================*/
void interface_reset_data_line(void)
{
    /*
     * Reset the eSDHC DATA line by writing 1 to RSTD bit
     * of SYSCTRL Register
     */
    esdhc_base_pointer->system_control |= ESDHC_SYSCTRL_RSTD;
}

/*==================================================================================================

FUNCTION: void interface_set_bus_width_endianess(UINT32 data_transfer_width, UINT32 endian_mode)

DESCRIPTION:
     Set data bus width and endianess for eSDHC.

ARGUMENTS PASSED:
    UINT32 data_transfer_width, UINT32 endian_mode

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:

1. Set bus width for eSDHC.
==================================================================================================*/

void interface_set_bus_width_endianess(UINT32 data_transfer_width, UINT32 endian_mode)
{
    /* Set data bus width of eSDHC */
    esdhc_set_data_transfer_width(data_transfer_width);

    /* Set Endianness of eSDHC */
    esdhc_set_endianness(endian_mode);
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
1. Initialize eSDHC base pointer to eSDHC base_address.
2. Configure the IOMUX
==================================================================================================*/

#define HAPI_SRC_REG_ADDR                   0x73fd0000
#define HAPI_BT_SDMMC_SRC                   (0x00180000)
#define HAPI_BT_SDMMC_SRC_SHIFT             ((UINT8)19)


void interface_init(UINT32 base_address)
{
    esdhc_base_pointer = (pESDHC_t)base_address;

    /* Initialize IOMUX registers for eSDHC module */
    esdhc_iomux_configuration();
}

/*==================================================================================
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
==================================================================================================*/

void interface_clear_interrupt(void)
{
    /* Clear Interrupt status register */
    esdhc_base_pointer->interrupt_status = ESDHC_CLEAR_INTERRUPT;
}

/*==================================================================================================

FUNCTION: void interface_configure_clock(sdhc_freq_t frequency)

DESCRIPTION:
    Enable Clock and set operating frequency for.

ARGUMENTS PASSED:
    sdhc_freq_t frequency

RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
1. Clear DTOCV, SDCLKFS, DVFS bits in SYSCTRL.
2. Disable the PEREN, HCKEN and IPGEN in SYSCTRL.
3. Configure the identification/operating frequency by setting
   SDCLKFS and DVS in SYSCTRL.
4. Mask Data Timeout Error Status Enable Interrupt (DTOESEN) in IRQSTATEN.
5. Set the Data Timeout Counter Value(DTOCV) in SYSCTL.
6. Enable Data Timeout Error Status Enable Interrupt (DTOESEN) in IRQSTATEN.
==================================================================================================*/
void interface_configure_clock(sdhc_freq_t frequency)
{
#if defined (REV_TO2)
    /* Clear SDCLKEN bit */
    esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_SDCLKEN_MASK);
#endif

    /* Disable the PEREN, HCKEN and IPGEN */
    esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_INPUT_CLOCK_MASK);

   /* Clear DTOCV SDCLKFS ,DVFS bits */
    esdhc_base_pointer->system_control &= (~ESDHC_SYSCTL_FREQ_MASK);

    if(frequency == IDENTIFICATION_FREQ)
    {
        esdhc_base_pointer->system_control |= ESDHC_SYSCTL_IDENT_FREQ;
    }
    else if(frequency == OPERATING_FREQ)
    {
#if defined (REV_TO2)
        esdhc_base_pointer->system_control |= ESDHC_SYSCTL_OPERT_FREQ;
#else
        esdhc_base_pointer->system_control |= ESDHC_SYSCTL_OPERT_FREQ;
#endif
        
    }

#if defined (REV_TO2)
    /* Start a general purpose timer */
    GPT_delay(ESDHC_OPER_TIMEOUT);
    /* Wait for clock to be stable */
    while(!(esdhc_base_pointer->present_state & ESDHC_PRSSTAT_SDSTB_BIT))
    {
        /* Check for GPT status */
        if(GPT_status() == TRUE)
        {
            break;
        }
    }
    /* Disable Timer */
    GPT_disable();

    /* Set SDCLKEN bit to enable clock */
    esdhc_base_pointer->system_control |= ESDHC_SYSCTL_SDCLKEN_MASK;
#endif

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
    Set data transfer width for eSDHC.

ARGUMENTS PASSED:
    UINT32 data_transfer_width

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
    /* Set DWT bit of protocol control register according to bus_width */
    esdhc_base_pointer->protocol_control &= ~(ESDHC_BUS_WIDTH_MASK);
    esdhc_base_pointer->protocol_control |= data_transfer_width;
}

/*==================================================================================================

FUNCTION: static void esdhc_set_endianness(UINT32 endian_mode)

DESCRIPTION:
    Set endianness mode for eSDHC.

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

/*==================================================================================================
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
==================================================================================================*/

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

/*==================================================================================================
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
==================================================================================================*/
UINT32 interface_wait_cmd_data_lines(data_present_select data_present)
{
    UINT32 cmd_status = SUCCESS;

    cmd_status = esdhc_poll_cihb_cdihb(data_present);

    return cmd_status;
}

/*==================================================================================================
FUNCTION: UINT32 interface_send_cmd_wait_resp(command_t *cmd)

DESCRIPTION:
    execute a command and wait for the response

ARGUMENTS PASSED:
    COMMAND_t *cmd - a pointer to structure defining a command

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:

==================================================================================================*/

UINT32 interface_send_cmd_wait_resp(command_t *cmd)
{
    UINT32 cmd_status = SUCCESS;
#if defined (REV_TO1)
    esdhc_reg_bkp_t esdhc_reg_bkp = {ZERO, ZERO, ZERO, ZERO, ZERO};
#endif
    /* Clear Interrupt status register */
    esdhc_base_pointer->interrupt_status = ESDHC_CLEAR_INTERRUPT;

    /* Enable Interrupt */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_INTERRUPT_ENABLE;

    /* Before sending any command, check for CMD and data line release */
    cmd_status = interface_wait_cmd_data_lines(cmd->data_present);

    if(cmd_status == FAIL)
    {
        return FAIL;
    }

#if defined (REV_TO1)
    if(cmd->data_transfer == WRITE)
    {
        /* Save the eSDHC register set */
        esdhc_registers_save(&esdhc_reg_bkp);
    }
#endif

    /* Configure Command */
    esdhc_cmd_config(cmd);

    /* Wait for interrupt CTOE or CC */
    esdhc_wait_end_cmd_resp_intr();

    /* Mask all interrupts */
    esdhc_base_pointer->interrupt_signal_enable = ZERO;

    /* Check if an error occured */
    cmd_status = esdhc_check_response();

#if defined (REV_TO1)
    if(cmd->data_transfer == WRITE)
    {
        /* Retrive the eSDHC register set */
        esdhc_registers_get(&esdhc_reg_bkp);
    }
#endif

    return cmd_status;
}

#if defined (REV_TO1)
/*==================================================================================================
FUNCTION: void esdhc_registers_get(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr)

DESCRIPTION:
    Retrive the eSDHC register after applying RSTD.

ARGUMENTS PASSED:
    esdhc_reg_bkp_t *esdhc_reg_bkp_ptr
RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
==================================================================================================*/

static void esdhc_registers_get(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr)
{
    esdhc_base_pointer->dma_system_address = esdhc_reg_bkp_ptr->dma_system_address;
    esdhc_base_pointer->block_attributes = esdhc_reg_bkp_ptr->block_attributes;
    esdhc_base_pointer->protocol_control = esdhc_reg_bkp_ptr->protocol_control;
    esdhc_base_pointer->watermark_level = esdhc_reg_bkp_ptr->watermark_level;
    esdhc_base_pointer->adma_system_address = esdhc_reg_bkp_ptr->adma_system_address;
}

/*==================================================================================================
FUNCTION: void esdhc_registers_save(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr)

DESCRIPTION:
    Save the eSDHC register before setting the data transfer
    direction to write.

ARGUMENTS PASSED:
    esdhc_reg_bkp_t *esdhc_reg_bkp_ptr
RETURN VALUE:
    None

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
==================================================================================================*/

static void esdhc_registers_save(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr)
{
    esdhc_reg_bkp_ptr->dma_system_address = esdhc_base_pointer->dma_system_address;
    esdhc_reg_bkp_ptr->block_attributes = esdhc_base_pointer->block_attributes;
    esdhc_reg_bkp_ptr->protocol_control = esdhc_base_pointer->protocol_control;
    esdhc_reg_bkp_ptr->watermark_level = esdhc_base_pointer->watermark_level;
    esdhc_reg_bkp_ptr->adma_system_address = esdhc_base_pointer->adma_system_address;
}
#endif

/*==================================================================================================
FUNCTION: void esdhc_cmd_config(command_t *cmd)

DESCRIPTION:
    Configure eSDHC registers for sending a command to MMC.

ARGUMENTS PASSED:
    COMMAND_t *cmd - a pointer to structure defining a command

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

    /* Configure eSDHC Register value according to Command */
    esdhc_base_pointer->command_transfer_type =
                (((cmd->data_transfer) << ESDHC_DATA_TRANSFER_SHIFT) |
                ((cmd->response_format) << ESDHC_RESPONSE_FORMAT_SHIFT) |
                ((cmd->data_present) << ESDHC_DATA_PRESENT_SHIFT) |
                ((cmd->crc_check) << ESDHC_CRC_CHECK_SHIFT) |
                ((cmd->cmdindex_check) << ESDHC_CMD_INDEX_CHECK_SHIFT) |
                ((cmd->command) << ESDHC_CMD_INDEX_SHIFT) |
                ((cmd->block_count_enable_check) << ESDHC_BLOCK_COUNT_ENABLE_SHIFT) |
                ((cmd->multi_single_block) << ESDHC_MULTI_SINGLE_BLOCK_SELECT_SHIFT));
}

/*==================================================================================================

FUNCTION: void esdhc_wait_end_cmd_resp_intr(void)

DESCRIPTION:
    Wait for CC or CTOE interrupt in interrupt status register. eSDHC sets this bit after
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
    /* Start a general purpose timer */
    GPT_delay(ESDHC_OPER_TIMEOUT);

    while(!((esdhc_base_pointer->interrupt_status) & ESDHC_STATUS_END_CMD_RESP_TIME_MSK))
    {
        /*
         * If some thing goes wrong with the ESDHC and int is not received
         * and if the timer expires,return FAIL
         */
        if(GPT_status() == TRUE)
        {
            break;
        }
    }

    /* Disable Timer */
    GPT_disable();
}

/*==================================================================================================

FUNCTION: UINT32 esdhc_check_response(void)

DESCRIPTION:
    Check whether the interrupt is an END_CMD_RESP
    or a response time out or a CRC error or command index error.

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
==================================================================================================*/

static UINT32 esdhc_check_response(void)
{
    UINT32 status = FAIL;

    UINT32 interrupt_status = esdhc_base_pointer->interrupt_status;

    /* Check whether the interrupt is an CC or CTOE or CCE error */
    if((interrupt_status & ESDHC_STATUS_END_CMD_RESP_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_TIME_OUT_RESP_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CRC_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_INDEX_ERR_MSK) &&
        !(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_RESP_CMD_END_BIT_ERR_MSK))
    {
        status = SUCCESS;
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, chk_resp: sdhc_status: %d, judge: %d result: %d\n", esdhc_base_pointer->interrupt_status, ((esdhc_base_pointer->interrupt_status & ESDHC_STATUS_END_CMD_RESP_MSK) &&
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

FUNCTION: void interface_read_response(command_response_t *esdhc_rsp)

DESCRIPTION:
    This function will read response from eSDHC register according to reponse format.

ARGUMENTS PASSED:
    command_response *esdhc_rsp

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

FUNCTION: UINT32 interface_data_read(UINT32 *dest_ptr, UINT32 blk_len)

DESCRIPTION:
    This function will read response from eSDHC register according to reponse format.

ARGUMENTS PASSED:
   UINT32 *dest_ptr
   UINT32 blk_len

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
==================================================================================================*/

UINT32 interface_data_read(UINT32 *dest_ptr, UINT32 blk_len)
{
    UINT32 i = ZERO;
    UINT32 j = ZERO;
    UINT32 status = FAIL;
    UINT32 block_count = ZERO;
    multi_single_block_select multi_single_block = SINGLE;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Entry: interface_data_read!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

#ifdef TY_DBG
    esdhc_dump_register();
#endif

    if((blk_len) <= (ESDHC_FIFO_SIZE * FOUR))
    {
        block_count = 1;
    }
    else
    {
        block_count = (blk_len)/(ESDHC_FIFO_SIZE * FOUR);
        //multi_single_block = MULTIPLE;
    }

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, blk_len:%d,block_count:%d,multi_single_block:%d!\n", blk_len, block_count, multi_single_block);
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
                                         ESDHC_READ_DATA_TIME_OUT,
                                         multi_single_block);

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, fifo_size:%d,status:%d!\n", fifo_size, status);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
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
		    sprintf(au8StrBuf, "Ty, Exit: interface_data_read!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    return status;
}

/*==================================================================================================

FUNCTION: UINT32 esdhc_wait_buf_rdy_intr(UINT32 mask,
                                         UINT32 timeout,
                                         multi_single_block_select multi_single_block)

DESCRIPTION:
    Wait a BUF_READ_READY/BUF_WRITE_READY interrupt by polling STATUS register.

ARGUMENTS PASSED:
    UINT32 mask - an integer defining the mask to be applied on the STATUS
                  register
    UINT32 timeout - Timeout used durring read or write.
    multi_single_block_select multi_single_block

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
==================================================================================================*/

static UINT32 esdhc_wait_buf_rdy_intr(UINT32 mask,
                                      UINT32 timeout,
                                      multi_single_block_select multi_single_block)
{
    UINT32 status = SUCCESS;

    /* Start a general purpose timer */
    GPT_delay(timeout);

    while(!(esdhc_base_pointer->interrupt_status & mask))
    {
        /*
         * If some thing goes wrong with the eSDHC and INT is not received
         * and if the timer expires, return FAIL
         */
        if(GPT_status() == TRUE)
        {
            status = FAIL;
            break;
        }
    }

    if(multi_single_block == MULTIPLE && (esdhc_base_pointer->interrupt_status & mask))
    {
        esdhc_base_pointer->interrupt_status |= mask;
    }

    /* Disable Timer */
    GPT_disable();

    return status;
}

/*==================================================================================================

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
==================================================================================================*/
static void esdhc_clear_buf_rdy_intr(UINT32 mask)
{
    esdhc_base_pointer->interrupt_status = mask;
}

/*==================================================================================================

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
==================================================================================================*/

static void esdhc_wait_op_done_intr(void)
{
    while(!(esdhc_base_pointer->interrupt_status & ESDHC_STATUS_DATA_RW_MSK));
}

/*==================================================================================================

FUNCTION: UINT32 esdhc_check_data(void)

DESCRIPTION:
    Check for Data timeout error, data CRC error and data end bit error
    with transfer complete intr to determine if an error occured.

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

    /* Check whether the interrupt is an TC or DTOE/DCE/DEBE */
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

FUNCTION: void interface_config_block_info(UINT32 blk_len, UINT32 nob, UINT32 wml)

DESCRIPTION:
    Set Block length and read water mark level for eSDHC.

ARGUMENTS PASSED:
    U32 blk_len - the length of the block to be transfered
    U32 nob
    U32 wml
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
#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: interface_config_block_info(), wml:%d", wml);
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    /* Configre block Attributes register */
    esdhc_base_pointer->block_attributes = ((nob<< ESDHC_BLOCK_SHIFT) | blk_len);

    /* Set Read Water Mark Level register */
    esdhc_base_pointer->watermark_level = wml;

#ifdef TY_DBG
    esdhc_dump_register();
#endif

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, exit: interface_config_block_info()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif
}

/*=================================================================================

FUNCTION: UINT32 interface_data_write(UINT32 *dest_ptr, UINT32 blk_len)

DESCRIPTION:
    This function will write data to device attached to interface

ARGUMENTS PASSED:
   UINT32 * dest_ptr
   UINT32 blk_len

RETURN VALUE:
    UINT32 - SUCCESS or FAIL

PRE-CONDITIONS:
    None

POST-CONDITIONS:
    None

IMPORTANT NOTES:
    None
===============================================================================*/

UINT32 interface_data_write (UINT32 *dest_ptr,UINT32 blk_len)
{
    UINT32 i = ZERO;
    UINT32 j = ZERO;
    UINT32 status = FAIL;
    UINT32 block_count = ZERO;
    multi_single_block_select multi_single_block = SINGLE;

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, entry: interface_data_write()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

#ifdef TY_DBG
    esdhc_dump_register();
#endif

    if((blk_len) <= (ESDHC_FIFO_SIZE * FOUR))
    {
        block_count = 1;
    }
    else
    {
        block_count = (blk_len)/(ESDHC_FIFO_SIZE * FOUR);
        multi_single_block = MULTIPLE;
    }

#ifdef TY_DBG
	{
		// Terry adds for debug, :-)
		U8 au8StrBuf[100] = { 0 };
		sprintf(au8StrBuf, "Ty, block_count:%d,blk_len:%d", block_count, blk_len);
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

        /* Wait for BWR bit to be set */
        status = esdhc_wait_buf_rdy_intr(ESDHC_STATUS_BUF_WRITE_RDY_MSK,
                                         ESDHC_WRITE_DATA_TIME_OUT,
                                         multi_single_block);
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, esdhc_wait_buf_rdy_intr:%d", status);
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        if(status == SUCCESS)
        {
            for(j = ZERO; j < fifo_size; j++)
            {
                esdhc_base_pointer->data_buffer_access = *dest_ptr;

                /* Increment destination pointer */
                dest_ptr++;

                /* Decement block length by data write */
                blk_len -= (FOUR);
            }

            /* Clear the BWR */
            esdhc_clear_buf_rdy_intr(ESDHC_STATUS_BUF_WRITE_RDY_MSK);
        }
        else
        {
            break;
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
		sprintf(au8StrBuf, "Ty, exit: interface_data_write()");
		atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	}
#endif

    return status;
}

/*==================================================================================================

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
==================================================================================================*/
static void esdhc_iomux_configuration(void)
{
    UINT32 u32Interface_esdhc =0;

    u32Interface_esdhc = (*((VP_U32)(HAPI_SRC_REG_ADDR + 1 * 4)) & HAPI_BT_SDMMC_SRC) >> HAPI_BT_SDMMC_SRC_SHIFT;

    if (ESDHC1 == u32Interface_esdhc)
    {
        esdhc_base_pointer = (pESDHC_t)esdhc_1_regs_base_address;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 1 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

        /*Initialization IOMUX registers  for esdhc1 module*/
		/* CMD MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_SD1_CMD_PORT,
                         HAPI_IOMUX_ESDHC1_SD1_CMD_PIN,
                         HAPI_IOMUX_ESDHC1_SD1_CMD_SEL,
                         HAPI_IOMUX_ESDHC1_SD1_CMD_DIR);

        /* CMD PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_VAL);

        /* CLK MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_SD1_CLK_PORT,
                         HAPI_IOMUX_ESDHC1_SD1_CLK_PIN,
                         HAPI_IOMUX_ESDHC1_SD1_CLK_SEL,
                         HAPI_IOMUX_ESDHC1_SD1_CLK_DIR);

        /* CLK PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_VAL);

        /* DATA0 MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_SD1_DATA0_PORT,
                         HAPI_IOMUX_ESDHC1_SD1_DATA0_PIN,
                         HAPI_IOMUX_ESDHC1_SD1_DATA0_SEL,
                         HAPI_IOMUX_ESDHC1_SD1_DATA0_DIR);

        /* DATA0 PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_VAL);

        /* DATA3 MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_SD1_DATA3_PORT,
                         HAPI_IOMUX_ESDHC1_SD1_DATA3_PIN,
                         HAPI_IOMUX_ESDHC1_SD1_DATA3_SEL,
                         HAPI_IOMUX_ESDHC1_SD1_DATA3_DIR);

        /* DAT3 pull up */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_VAL);
    }
    /*Initialization IOMUX registers  for esdhc2 module*/
    else if (u32Interface_esdhc == ESDHC2)
    {
        esdhc_base_pointer = (pESDHC_t)esdhc_2_regs_base_address;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 2 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

/* CMD MUX config */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_SD2_CMD_PORT,
                         HAPI_IOMUX_ESDHC2_SD2_CMD_PIN,
                         HAPI_IOMUX_ESDHC2_SD2_CMD_SEL,
                         HAPI_IOMUX_ESDHC2_SD2_CMD_DIR);

        /* CMD PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_VAL);

        /* CLK MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_SD2_CLK_PORT,
                         HAPI_IOMUX_ESDHC2_SD2_CLK_PIN,
                         HAPI_IOMUX_ESDHC2_SD2_CLK_SEL,
                         HAPI_IOMUX_ESDHC2_SD2_CLK_DIR);

        /* CLK PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_VAL);

        /* DATA0 MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_SD2_DATA0_PORT,
                         HAPI_IOMUX_ESDHC2_SD2_DATA0_PIN,
                         HAPI_IOMUX_ESDHC2_SD2_DATA0_SEL,
                         HAPI_IOMUX_ESDHC2_SD2_DATA0_DIR);

        /* DATA0 PAD control */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_VAL);

        /* DATA3 MUX control */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_SD2_DATA3_PORT,
                         HAPI_IOMUX_ESDHC2_SD2_DATA3_PIN,
                         HAPI_IOMUX_ESDHC2_SD2_DATA3_SEL,
                         HAPI_IOMUX_ESDHC2_SD2_DATA3_DIR);

        /* DAT3 pull up */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_VAL);
    }
    else if(u32Interface_esdhc == ESDHC3)
    {
        esdhc_base_pointer = (pESDHC_t)esdhc_3_regs_base_address;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 3 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

/* CMD */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_RDY_INT_PORT,
                         HAPI_IOMUX_NANDF_RDY_INT_PIN,
                         HAPI_IOMUX_NANDF_RDY_INT_SEL,
                         HAPI_IOMUX_NANDF_RDY_INT_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_VAL);

        /* CLK */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS7_PORT,
                         HAPI_IOMUX_NANDF_CS7_PIN,
                         HAPI_IOMUX_NANDF_CS7_SEL,
                         HAPI_IOMUX_NANDF_CS7_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS7_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS7_VAL);

        /* DATA0 */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_WE_B_PORT,
                         HAPI_IOMUX_NANDF_WE_B_PIN,
                         HAPI_IOMUX_NANDF_WE_B_SEL,
                         HAPI_IOMUX_NANDF_WE_B_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_ADDR,
                             IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_WE_B_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_WE_B_VAL);

        /* DATA3 */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_RB0_PORT,
                         HAPI_IOMUX_NANDF_RB0_PIN,
                         HAPI_IOMUX_NANDF_RB0_SEL,
                         HAPI_IOMUX_NANDF_RB0_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_ADDR,
                             IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB0_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB0_VAL);
        
    }
    else if(u32Interface_esdhc == ESDHC4)
    {
        esdhc_base_pointer = (pESDHC_t)esdhc_4_regs_base_address;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 4 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

/* CMD */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_RB1_PORT,
                         HAPI_IOMUX_NANDF_RB1_PIN,
                         HAPI_IOMUX_NANDF_RB1_SEL,
                         HAPI_IOMUX_NANDF_RB1_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_VAL);

        /* CLK */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS2_PORT,
                         HAPI_IOMUX_NANDF_CS2_PIN,
                         HAPI_IOMUX_NANDF_CS2_SEL,
                         HAPI_IOMUX_NANDF_CS2_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS2_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS2_VAL);

        /* DATA0 */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS3_PORT,
                         HAPI_IOMUX_NANDF_CS3_PIN,
                         HAPI_IOMUX_NANDF_CS3_SEL,
                         HAPI_IOMUX_NANDF_CS3_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS3_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS3_VAL);

        /* DATA3 */
        HAPI_GPIO_config(HAPI_IOMUX_NANDF_CS6_PORT,
                         HAPI_IOMUX_NANDF_CS6_PIN,
                         HAPI_IOMUX_NANDF_CS6_SEL,
                         HAPI_IOMUX_NANDF_CS6_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS6_ADDR,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS6_VAL);
        
    }    

}

/*==================================================================================================

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
==================================================================================================*/
void esdhc_set_cmd_pullup(esdhc_pullup_t pull_up)
{
    UINT32 u32Interface_esdhc =0;

    u32Interface_esdhc = (*((VP_U32)(HAPI_SRC_REG_ADDR + 1 * 4)) & HAPI_BT_SDMMC_SRC) >> HAPI_BT_SDMMC_SRC_SHIFT;

    if(pull_up == STRONG)
    {
        /* Configure strong pull-up on CMD line */
        if(u32Interface_esdhc == ESDHC1)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_SVAL);
           
        }
        else if(u32Interface_esdhc == ESDHC2)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SVAL);
        }
        else if(u32Interface_esdhc == ESDHC3)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_SVAL);
        }
        else if(u32Interface_esdhc == ESDHC4)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_SVAL);
        }
    }
    else if(pull_up == WEAK)
    {
        /* Configure weak pull-up on CMD line */
        if(u32Interface_esdhc == ESDHC1)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_VAL);
        }
        else if(u32Interface_esdhc == ESDHC2)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_VAL);
        }
        else if(u32Interface_esdhc == ESDHC3)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_VAL);
        }
        else if(u32Interface_esdhc == ESDHC4)
        {
            /* CMD PAD control */
            HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_ADDR,
                                 HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_VAL);
        }
    }
}

#ifdef TY_DBG
static UINT32 esdhc_dump_register()
{

#define ESDHC_REG_NUM           23

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
         {"adma_error_status_register", &(esdhc_base_pointer->adma_error_status_register)},
         {"adma_system_address", &(esdhc_base_pointer->adma_system_address)},
         {"vendor_specific_register", &(esdhc_base_pointer->vendor_specific_register)},
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
