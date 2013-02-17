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

#include "hapi_gpio_defs.h"
#include "pu_irom_esdhc.h" 
#include "pu_irom_card.h"
#include "pu_irom_mmc.h"
#include "pu_irom_timer.h"

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

#define IOMUXC_BASE_ADDR                (0x43fac000)
#define GPIO1_BASE_ADDR                 (0x53fcc000)
#define GPIO2_BASE_ADDR                 (0x53fd0000)
#define GPIO3_BASE_ADDR                 (0x53fa4000)

static VP_U32 const iomux_sw_mux_ctrl_reg_array[3] = 
{
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0008),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x022c),
    (UINT32 *) ((UINT32) IOMUXC_BASE_ADDR + 0x0460)
};

static VP_U32 const data_dir_reg_ptr_array[3] = {
    (UINT32 *) ((UINT32) GPIO1_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO2_BASE_ADDR + 4),
    (UINT32 *) ((UINT32) GPIO3_BASE_ADDR + 4)
};

#define esdhc_1_regs_base_address       (0x53fb4000)
#define esdhc_2_regs_base_address       (0x53fb8000)

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
static void esdhc_registers_save(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr);
static void esdhc_registers_get(esdhc_reg_bkp_t *esdhc_reg_bkp_ptr);
#ifdef TY_DBG
static UINT32 esdhc_dump_register();
#endif
/*==================================================================================================

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
    
    /* send 80 clock ticks for card to power up */
    esdhc_base_pointer->system_control |= ESDHC_SOFTWARE_INIT;

    /* Set data bus width of ESDCH */
    esdhc_set_data_transfer_width(data_transfer_width);

    /* Set Endianness of ESDHC */
    esdhc_set_endianness(endian_mode);

    /* set data timeout delay to max */
    esdhc_base_pointer->system_control = (esdhc_base_pointer->system_control & 0xfff0ffff) | 0x000e0000;

    esdhc_base_pointer->protocol_control |= 0x00000008;
	
    return reset_status;
}

/*==================================================================================================

FUNCTION: void interface_reset_cmd_line(void)

DESCRIPTION:
    Execute a Software Reset For CMD Line.

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
==================================================================================================*/
void interface_reset_cmd_line(void)
{
    /*
     * Reset the eSDHC CMD line by writing 1 to RSTC bit
     * of SYSCTRL Register
     */
    esdhc_base_pointer->system_control |= ESDHC_SYSCTRL_RSTC;
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
1. Initialize esdhc base pointer to basE_address.

==================================================================================================*/

#define CLOCK_REG_ADDR             (0x53f80000)
#define RCSR_BT_SRC                (0x00300000)
#define RCSR_BT_SRC_SHIFT          ((UINT8)20)

#define HAPI_CLOCK_AHB_PER_ESDHC1_EN (0x00200008) /*CGCR0*/
#define HAPI_CLOCK_AHB_PER_ESDHC2_EN (0x00400010) /*CGCR0*/
#define HAPI_CLOCK_IPG_ESDHC1_EN     (0x00002000) /*CGCR1*/
#define HAPI_CLOCK_IPG_ESDHC2_EN     (0x00004000) /*CGCR1*/

#define HAPI_CLOCK_PER_GPT_EN        (0x00000020) /*CGCR0*/
#define HAPI_CLOCK_AHB_USBOTG_EN     (0x10000000) /*CGCR0*/
#define HAPI_CLOCK_IPG_GPT_EN        (0x00780000) /*CGCR1*/
#define HAPI_CLOCK_IPG_GPIO_EN       (0x00070000) /*CGCR1*/ 
#define HAPI_CLOCK_IPG_IOMUX_EN      (0x08000000) /*CGCR1*/
#define HAPI_CLOCK_IPG_WDOG_EN       (0x00080000) /*CGCR2*/

void interface_init(UINT32 base_address)
{
    UINT32 u32Interface_esdhc =0;

    /*Enable the clock output of GPIO,IOMUX,GPT */
    (*(VP_U32)(CLOCK_REG_ADDR + 3 * 4)) |= (HAPI_CLOCK_PER_GPT_EN | HAPI_CLOCK_AHB_USBOTG_EN);
    (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= (HAPI_CLOCK_PER_GPT_EN | HAPI_CLOCK_AHB_USBOTG_EN);
    (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= HAPI_CLOCK_IPG_WDOG_EN;

#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, Entry: interface_init!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif

    u32Interface_esdhc = (*((VP_U32)(CLOCK_REG_ADDR + 10 * 4)) & RCSR_BT_SRC) >> RCSR_BT_SRC_SHIFT;


    esdhc_base_pointer = (pESDHC_t)base_address;

    switch (u32Interface_esdhc)
    {
        case ESDHC1:
            esdhc_base_pointer = (pESDHC_t)esdhc_1_regs_base_address;

            /*Enable the Clock for the esdhc module*/
            (*(VP_U32)(CLOCK_REG_ADDR + 3 * 4)) |= HAPI_CLOCK_AHB_PER_ESDHC1_EN;
            (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= HAPI_CLOCK_IPG_ESDHC1_EN;
            
#ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 1 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        /* CMD line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU1,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_REG,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_CMD_REG,
                             HAPI_ESDHC1_CMD_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* CLK line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU1,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_REG,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_CLK_REG,
                             HAPI_ESDHC1_CLK_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* DATA0 line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA0_REG,
                             HAPI_ESDHC1_DATA0_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* DATA1 line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA1_REG,
                             HAPI_ESDHC1_DATA1_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* DATA2 line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA2_REG,
                             HAPI_ESDHC1_DATA2_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* DATA3 line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA3_REG,
                             HAPI_ESDHC1_DATA3_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE);

        /* DATA7 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_DATA7_PORT,
                         HAPI_IOMUX_ESDHC1_DATA7_PIN,
                         HAPI_IOMUX_ESDHC1_DATA7_SEL,
                         HAPI_IOMUX_ESDHC1_DATA7_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC1_IPP_DAT7_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC1_IPP_DAT7_IN_SELECT_INPUT_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA7_REG,
                             HAPI_ESDHC1_DATA7_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_VALUE);


        /* DATA6 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_DATA6_PORT,
                         HAPI_IOMUX_ESDHC1_DATA6_PIN,
                         HAPI_IOMUX_ESDHC1_DATA6_SEL,
                         HAPI_IOMUX_ESDHC1_DATA6_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC1_IPP_DAT6_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC1_IPP_DAT6_IN_SELECT_INPUT_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA6_REG,
                             HAPI_ESDHC1_DATA6_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_VALUE);

        /* DATA5 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_DATA5_PORT,
                         HAPI_IOMUX_ESDHC1_DATA5_PIN,
                         HAPI_IOMUX_ESDHC1_DATA5_SEL,
                         HAPI_IOMUX_ESDHC1_DATA5_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC1_IPP_DAT5_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC1_IPP_DAT5_IN_SELECT_INPUT_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA5_REG,
                             HAPI_ESDHC1_DATA5_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_VALUE);

        /* DATA4 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC1_DATA4_PORT,
                         HAPI_IOMUX_ESDHC1_DATA4_PIN,
                         HAPI_IOMUX_ESDHC1_DATA4_SEL,
                         HAPI_IOMUX_ESDHC1_DATA4_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC1_IPP_DAT4_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC1_IPP_DAT4_IN_SELECT_INPUT_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA4_REG,
                             HAPI_ESDHC1_DATA4_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_VALUE);
            
            break;
        case ESDHC2:
            esdhc_base_pointer = (pESDHC_t)esdhc_2_regs_base_address;

            /*Enable the Clock for the esdhc module*/
            (*(VP_U32)(CLOCK_REG_ADDR + 3 * 4)) |= HAPI_CLOCK_AHB_PER_ESDHC2_EN;
            (*(VP_U32)(CLOCK_REG_ADDR + 4 * 4)) |= HAPI_CLOCK_IPG_ESDHC2_EN;

 #ifdef TY_DBG
	    {
		    // Terry adds for debug, :-)
		    U8 au8StrBuf[100] = { 0 };
		    sprintf(au8StrBuf, "Ty, ESDHC 2 !!\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        /* CMD line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU1,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDC_REG,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDC_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_CMD_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_CMD_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_CMD_REG,
                             HAPI_ESDHC2_CMD_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* CLK line */
        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU1,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDIO_REG,
                             HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDIO_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_CLK_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_CLK_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_CLK_REG,
                             HAPI_ESDHC2_CLK_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* DATA0 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA0_PORT,
                         HAPI_IOMUX_ESDHC2_DATA0_PIN,
                         HAPI_IOMUX_ESDHC2_DATA0_SEL,
                         HAPI_IOMUX_ESDHC2_DATA0_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT0_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT0_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA0_REG,
                             HAPI_ESDHC2_DATA0_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* DATA1 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA1_PORT,
                         HAPI_IOMUX_ESDHC2_DATA1_PIN,
                         HAPI_IOMUX_ESDHC2_DATA1_SEL,
                         HAPI_IOMUX_ESDHC2_DATA1_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT1_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT1_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA1_REG,
                             HAPI_ESDHC2_DATA1_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* DATA2 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA2_PORT,
                         HAPI_IOMUX_ESDHC2_DATA2_PIN,
                         HAPI_IOMUX_ESDHC2_DATA2_SEL,
                         HAPI_IOMUX_ESDHC2_DATA2_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT2_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT2_IN_SELECT_INPUT_VAL);


        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA2_REG,
                             HAPI_ESDHC2_DATA2_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* DATA3 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA3_PORT,
                         HAPI_IOMUX_ESDHC2_DATA3_PIN,
                         HAPI_IOMUX_ESDHC2_DATA3_SEL,
                         HAPI_IOMUX_ESDHC2_DATA3_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT3_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT3_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA3_REG,
                             HAPI_ESDHC2_DATA3_PAD_VALUE);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);

        /* DATA4 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA4_PORT,
                         HAPI_IOMUX_ESDHC2_DATA4_PIN,
                         HAPI_IOMUX_ESDHC2_DATA4_SEL,
                         HAPI_IOMUX_ESDHC2_DATA4_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT4_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT4_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA4_REG,
                             HAPI_ESDHC2_DATA4_PAD_VALUE);


        /* DATA5 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA5_PORT,
                         HAPI_IOMUX_ESDHC2_DATA5_PIN,
                         HAPI_IOMUX_ESDHC2_DATA5_SEL,
                         HAPI_IOMUX_ESDHC2_DATA5_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT5_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT5_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA5_REG,
                             HAPI_ESDHC2_DATA5_PAD_VALUE);


        /* DATA6 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA6_PORT,
                         HAPI_IOMUX_ESDHC2_DATA6_PIN,
                         HAPI_IOMUX_ESDHC2_DATA6_SEL,
                         HAPI_IOMUX_ESDHC2_DATA6_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT6_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT6_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA6_REG,
                             HAPI_ESDHC2_DATA6_PAD_VALUE);


        /* DATA7 line */
        HAPI_GPIO_config(HAPI_IOMUX_ESDHC2_DATA7_PORT,
                         HAPI_IOMUX_ESDHC2_DATA7_PIN,
                         HAPI_IOMUX_ESDHC2_DATA7_SEL,
                         HAPI_IOMUX_ESDHC2_DATA7_DIR);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU3,
                             HAPI_IOMUXC_ESDHC2_IPP_DAT7_IN_SELECT_INPUT_REG,
                             HAPI_ESDHC2_IPP_DAT7_IN_SELECT_INPUT_VAL);

        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA7_REG,
                             HAPI_ESDHC2_DATA7_PAD_VALUE);


        HAPI_GPIO_pad_config(HAPI_GPIO_PORT_MCU2,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG,
                             HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE);
            break;
        default:
            break;
    }

#ifdef TY_DBG
    {
	    // Terry adds for debug, :-)
	    U8 au8StrBuf[100] = { 0 };
	    sprintf(au8StrBuf, "Ty, Exit: interface_init!\n");
	    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
    }
#endif
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
   /* Clear DTOCV SDCLKFS bits */
   esdhc_base_pointer->system_control &= ESDHC_FREQ_MASK;
	
    if(frequency == IDENTIFICATION_FREQ)
    { 
        /* Input frequecy to eSDHC is 36 MHZ */ 
        /* PLL3 is the source of input frequency*/
        /*Set DTOCV and SDCLKFS bit to get SD_CLK of frequency below 400 KHZ (70.31 KHZ) */
        esdhc_base_pointer->system_control |= ESDHC_IDENT_FREQ;
    }
    else if(frequency == OPERATING_FREQ)
    {
        /*Set DTOCV and SDCLKFS bit to get SD_CLK of frequency around 25 MHz.(18 MHz)*/
        esdhc_base_pointer->system_control |= ESDHC_OPERT_FREQ;
    }  

    /* Mask Data Timeout Error Status Enable Interrupt (DTOESEN) */
    esdhc_base_pointer->interrupt_status_enable &= (~ESDHC_IRQSTATEN_DTOESEN);

    /* Set the Data Timeout Counter Value(DTOCV) */
    esdhc_base_pointer->system_control |= ESDHC_DTOCV_VAL;

    /* Enable Data Timeout Error Status Enable Interrupt (DTOESEN) */
    esdhc_base_pointer->interrupt_status_enable |= ESDHC_IRQSTATEN_DTOESEN;

    /* Enable ipg_perclk, HCLK enable and IPG Clock enable. */
    esdhc_base_pointer->system_control |= ESDHC_CLOCK_ENABLE;
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
    /* Set DWT bit of protocol control register according to bus_width */
    esdhc_base_pointer->protocol_control &= ~(ESDHC_BUS_WIDTH_MASK);
    esdhc_base_pointer->protocol_control |= data_transfer_width;
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
	
    /* Set DWT bit of protocol control register according to bus_width */
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
    esdhc_reg_bkp_t esdhc_reg_bkp = {ZERO, ZERO, ZERO, ZERO, ZERO};

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
		    sprintf(au8StrBuf, "Ty, CMD status == FAIL\n");
		    atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	    }
#endif
        return FAIL;
    }

    if(cmd->data_transfer == WRITE)
    {
        /* Save the eSDHC register set */
        esdhc_registers_save(&esdhc_reg_bkp);
    }

    /* Configure Command */
    esdhc_cmd_config(cmd);

    /* Wait for interrupt CTOE or CC */
    esdhc_wait_end_cmd_resp_intr();

    /* Mask all interrupts */
    esdhc_base_pointer->interrupt_signal_enable = ZERO;

    /* Check if an error occured */
    cmd_status = esdhc_check_response();

    if(cmd->data_transfer == WRITE)
    {
        /* Retrive the eSDHC register set */
        esdhc_registers_get(&esdhc_reg_bkp);
    }

    return cmd_status;
}

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

    /* Check whether the interrupt is an CC or CTOE or CCE error */
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
                                         ESDHC_READ_DATA_TIME_OUT,
                                         multi_single_block);

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

    if(multi_single_block == MULTIPLE && (esdhc_base_pointer->interrupt_status & mask))
    {
        esdhc_base_pointer->interrupt_status |= mask;
    }

    /* Disable Timer */
    GPT_disable();

    return status;
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
    /* Configre block Attributes register */
    esdhc_base_pointer->block_attributes = ((nob<< ESDHC_BLOCK_SHIFT) | blk_len);

    /* Set Read Water Mark Level register */
    esdhc_base_pointer->watermark_level = wml;
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

UINT32 interface_data_write(UINT32 *dest_ptr, UINT32 blk_len)
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
	    sprintf(au8StrBuf, "Ty, Entry: interface_data_write!\n");
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
        }
        else
        {
#ifdef TY_DBG
	        {
		        // Terry adds for debug, :-)
		        U8 au8StrBuf[100] = { 0 };
		        sprintf(au8StrBuf, "Ty, Wait buf rdy FAIL\n");
		        atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
	        }
#endif
            break;
        }
    }

    if(status == SUCCESS)
    {
        /* Wait for transfer complete operation interrupt */
        esdhc_wait_op_done_intr();

        /* Check for status errors */
        status = esdhc_check_data();

#ifdef TY_DBG
        {
            // Terry adds for debug, :-)
            U8 au8StrBuf[100] = { 0 };
            sprintf(au8StrBuf, "Ty, check data:%d\n", status);
            atk_channel_send(au8StrBuf, sizeof(au8StrBuf));
        }
#endif
    }

    return status;
}

#ifdef TY_DBG
static UINT32 esdhc_dump_register()
{

#define ESDHC_REG_NUM           22

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
