#ifndef HAPI_GPIO_DEFS_INCLUDE /* To prevent inadvertently including a header twice */
#define HAPI_GPIO_DEFS_INCLUDE

#ifdef __cplusplus  /* allow #include in a C++ file (only put this in .h files) */
extern "C" {
#endif

/*==================================================================================================

    Header Name: hapi_gpio_defs.h

    General Description:
       This file contains the memory map of the GPIO.

====================================================================================================

                        Copyright: 2004-2008  FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a
              Freescale Software License Agreement, which has either
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.

Revision History:
                     Modification   Tracking
Author                  Date         Number     Description of Changes
----------------    -----------   ----------   -------------------------------------------
Siva Pothireddy      12/Sep/2008 ENGcm07375   Ecspi2 IOMUX changes
Chandan Singh       14/Jul/2008   ENGcm06500   Added All UART IOMUX defines for ElvisTO2.
Chandan Singh       08/Jul/2008   ENGcm05628   Added I2C2 and HS-I2C module IOMUX defines
Siva Pothireddy     07/Jul/2008   ENGcm06219   New IOMUX changes after ER2
Siva Pothireddy     02/Jul/2008   ENGcm06218   I2C1 IOMUX changes for Elvis TO2
Chandan Singh       13/Jun/2008   ENGcm05617   Changes for eMMC-4.3 support for ElvisTO2
Chandan Singh       13/Jun/2008   ENGcm06111   IOMUX changes done for eSDHC ElvisTO2
Linto Antony        13/Jun/2008   ENGcm06113   IOMUX changes for TO2 based on ELVIS.01.00.36 release
Linto Antony        15/May/2008   ENGcm05638   IOMUX changes for TO2
Prabhat Singh       07/Feb/2008   ENGcm03276   CE-ATA bootable from esdhc1/2/3/4
Prabhat Singh       01/Feb/2008   ENGcm03206   USB ULPI phy miss trigerring issue
Prabhat Singh       29/Jan/2008   ENGcm03148   USB lpb flow modification
Prabhat Singh       25/Jan/2008   ENGcm03124   esdhc3 iomux config
Prabhat Singh       22/Jan/2007   ENGcm03037   cspi and ecspi1  IOMUX rtl fix
Prabhat Sigh        14/Jan/2008   ENGcm02433   ecspi all ports bootable
Siva Pothireddy     31/Dec/2007   ENGcm02429   Added support for LPB Feature
Prabhat Singh       10/Jan/2008   ENGcm02433   I2C1 IOMUX SION bit and IOMUX spec update
Prabhat Singh       26/Dec/2007   ENGcm02532   Iomux changes for esdhc1-2-3
Prabhat Singh       22/Nov/2007   ENGcm02065   Iomux changes for Elvis
Mahima Verma        13/Sep/2007   TLSbo96294   Iomux change for USB.
Surender Kumar      24/Aug/2007   TLSbo94734   High Capacity SD
Suresh Kumar        21/Aug/2007   TLSbo95760   CSPI burst length fixes
Mahima Verma        20/Aug/2007   TLSbo95872   Iomux changes.
Mahima Verma        19/Jul/2007   TLSbo94701   Iomuxing & clocking change.
Suresh Kumar        12/Jun/2007   TLSbo93947   Added boot support for spi eeprom/serial flash
Mahima Verma        11/Jun/2007   TLSbo93857   Ported to Marley.
Surender Kumar      07/Jun/2007   TLSbo93610   IOMUX for ESDHC
Suresh Kumar        30/May/2007   TLSbo93641   Porting IOMUX/GPIO for Marley
Bharat Bhushan      25/Jul/2006   TLSbo73972   IOMUX change in L3 and pinmuxing sheet.
Bharat Bhushan      20/Jul/2006   TLSbo73521   New Boot ROM Design Support for USB/UART Serial Downloader ( IOMUX Defines added )
Bharat Bhushan      28/Jun/2006   TLSbo72164   IOMUX Programming for 6-wire Serial Mode.
Bharat Bhushan      09/Jun/2006   TLSbo68884   IOMUX defines added for CSPI and USB .
Suresh Kumar        08/Jun/2006   TLSbo68884   IOMUX defines for UART1
Lucky Sharma        26/May/2006   TLSbo69185   Islay would use GP_SP_A8 instead of historical GP_AP_C9 for selection between UART/USB
Rziolkowski         25/Aug/2004   LIBff08888   Update to IOMUX programming for USB 4 wire to 6 wire.
Jvoss/Joeh          18/Aug/2004   LIBff06722   SCM-A11:change the IOMUX programming on HAPI_GPIO_USB_XCVR_EN.
                                               The integration team swapped the output MUX 0 and MUX 1 lines.
                                               Therefore MUX1 now becomes MUX0. Inputs remain the same.
Rziolkowski         12/Aug/2004   LIBff03632   Enable IOMUX for USB_VP1 and USB_VM1 for 6 wire mode for SCM-A11
Rziolkowski         01/Jul/2004   LIBee27940   Rework from inspection comments
Rziolkowski         30/Jun/2004   LIBee27940   Changed Argon+ configuration for USB XCVR enable (GPIO1)
Rziolkowski         06/Jun/2004   LIBee13501   Rework from inspection comments
Rziolkowski         28/May/2004   LIBee13501   Updates for SCM-A11
Jvoss               28/Apr/2004   LIBee01069   Argon+/SCM-A11 GPIO
                                               - Complete rewrite
====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

#define REG_NUM(num) (num << IOMUX_REG_NUM_SHIFT)
#define REG_OFFSET(num) (num << IOMUX_REG_OFFSET_SHIFT)

/* UART1 IOMUX DEFINES */

#define HAPI_IOMUX_UART1_RXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_RXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_RXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(131)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_RXD_DIR     (0xFF)

#define HAPI_IOMUX_UART1_TXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_TXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_TXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(132)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_TXD_DIR     (0xFF)

#define HAPI_IOMUX_UART1_RTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_RTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_RTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(133)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_RTS_DIR     (0xFF)

#define HAPI_IOMUX_UART1_CTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_CTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_CTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(134)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_CTS_DIR     (0xFF)

/*IOMUX UART1 PAD control register address*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_RXD_ADDR  (138)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_TXD_ADDR  (139)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_RTS_ADDR  (140)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_CTS_ADDR  (141)

/*IOMUX UART1 PAD control register value*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_RXD_VAL  (0x01c5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_TXD_VAL  (0x01c5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_RTS_VAL  (0x01c4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART1_CTS_VAL  (0x01c4)

/* UART2 IOMUX DEFINES */

#define HAPI_IOMUX_UART2_RXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART2_RXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART2_RXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(135)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART2_RXD_DIR     (0xFF)

#define HAPI_IOMUX_UART2_TXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART2_TXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART2_TXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(136)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART2_TXD_DIR     (0xFF)

#define HAPI_IOMUX_UART2_RTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART2_RTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART2_RTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(158)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART2_RTS_DIR     (0xFF)

#define HAPI_IOMUX_UART2_CTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART2_CTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART2_CTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(155)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART2_CTS_DIR     (0xFF)

/*IOMUX UART2 PAD control register address*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART2_RXD_ADDR    (142)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART2_TXD_ADDR    (143)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA3_ADDR  (169)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA0_ADDR  (166)

/*IOMUX UART2 PAD control register value*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART2_RXD_VAL    (0x01c5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_UART2_TXD_VAL    (0x01e5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA3_VAL  (0x01c4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA0_VAL  (0x01c4)

/* Daisy Chain */
#define HAPI_IOMUXC_UART2_IPP_UART_RXD_MUX_SELECT_INPUT_ADDR (74)
#define HAPI_IOMUXC_UART2_IPP_UART_RXD_MUX_SELECT_INPUT_VAL  (0x2)
#define HAPI_IOMUXC_UART2_IPP_UART_RTS_B_SELECT_INPUT_ADDR   (73)
#define HAPI_IOMUXC_UART2_IPP_UART_RTS_B_SELECT_INPUT_VAL    (0x5)

/* UART3 IOMUX DEFINES */

#define HAPI_IOMUX_UART3_RXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_RXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_RXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(122)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_RXD_DIR     (0xFF)

#define HAPI_IOMUX_UART3_TXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_TXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_TXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(124)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_TXD_DIR     (0xFF)

#define HAPI_IOMUX_UART3_RTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_RTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_RTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(148)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_RTS_DIR     (0xFF)

#define HAPI_IOMUX_UART3_CTS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_CTS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_CTS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(149)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_CTS_DIR     (0xFF)

/*IOMUX UART2 PAD control register address*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_AUD3_BB_RXD_ADDR (129)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_AUD3_BB_FS_ADDR  (131)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_ADDR    (155)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_KEY_COL5_ADDR    (156)

/*IOMUX UART2 PAD control register value*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_AUD3_BB_RXD_VAL  (0x01c5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_AUD3_BB_FS_VAL   (0x01c5)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_KEY_COL4_VAL     (0x01e4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_KEY_COL5_VAL     (0x01e4)

/* Daisy Chain */
#define HAPI_IOMUXC_UART3_IPP_UART_RXD_MUX_SELECT_INPUT_ADDR (76)
#define HAPI_IOMUXC_UART3_IPP_UART_RXD_MUX_SELECT_INPUT_VAL  (0x2)
#define HAPI_IOMUXC_UART3_IPP_UART_RTS_B_SELECT_INPUT_ADDR   (75)
#define HAPI_IOMUXC_UART3_IPP_UART_RTS_B_SELECT_INPUT_VAL    (0x4)

/******************************ULPI IOMUX Defines ****************************/
/*EIM_CS2 pad used as USB OTG USB_STP */
#define HAPI_IOMUX_USB_STP_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_STP_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                 (REG_NUM(51)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_DIR  (0xFF)

/*Configure GPIO2 pin 27 */
#define HAPI_IOMUX_USB_EIM_CS2_PORT (HAPI_GPIO_PORT_MCU2)
#define HAPI_IOMUX_USB_EIM_CS2_PIN  (HAPI_GPIO_PIN_27)
#define HAPI_IOMUX_USB_EIM_CS2_DIR HAPI_GPIO_OUTPUT
#define HAPI_IOMUX_USB_EIM_CS2_SEL  HAPI_GPIO_SEL_GPIO

/*EIM_CS3 pad used as USB OTG USB_NXT */
#define HAPI_IOMUX_USB_NXT_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_NXT_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_NXT_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(52)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_NXT_DIR  (0xFF)
/*EIM_CS4 pad used as USB OTG USB_CLK */
#define HAPI_IOMUX_USB_CLK_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_CLK_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_CLK_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(53)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_CLK_DIR  (0xFF)

/*EIM_CS5 pad used as USB OTG USB_DIR */
#define HAPI_IOMUX_USB_DIR_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DIR_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DIR_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(54)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DIR_DIR  (0xFF)

/*EIM_D24 pad used as USB OTG DATA0*/
#define HAPI_IOMUX_USB_DAT0_ULPI_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_ULPI_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_ULPI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(24)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_ULPI_DIR    (0xFF)
/*EIM_D25 pad used as USB OTG DATA1*/
#define HAPI_IOMUX_USB_DAT1_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT1_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT1_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                       (REG_NUM(25)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT1_ULPI_DIR   (0xFF)
/*EIM_D26 pad used as USB OTG DATA2*/
#define HAPI_IOMUX_USB_DAT2_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT2_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT2_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                       (REG_NUM(26)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT2_ULPI_DIR   (0xFF)
/*EIM_D27 pad used as USB OTG DATA3*/
#define HAPI_IOMUX_USB_DAT3_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT3_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT3_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(27)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT3_ULPI_DIR     (0xFF)
/*EIM_D28 pad used as USB OTG DATA4*/
#define HAPI_IOMUX_USB_DAT4_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT4_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT4_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                         (REG_NUM(28)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT4_ULPI_DIR     (0xFF)
/*EIM_D29 pad used as USB OTG DATA5*/
#define HAPI_IOMUX_USB_DAT5_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                         (REG_NUM(29)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_ULPI_DIR     (0xFF)
/*EIM_D30 pad used as USB OTG DATA6*/
#define HAPI_IOMUX_USB_DAT6_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(30)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_ULPI_DIR     (0xFF)
/*EIM_D31 pad used as USB OTG DATA7*/
#define HAPI_IOMUX_USB_DAT7_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT7_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT7_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(31)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT7_ULPI_DIR     (0xFF)

/*IOMUX ULPI PAD control pad registers offset */
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS2_ADDR 35
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS3_ADDR 36
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS4_ADDR 37
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS5_ADDR 38
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D24_ADDR 8
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D25_ADDR 9
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D26_ADDR 10
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D27_ADDR 11
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D28_ADDR 12
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D29_ADDR 13
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D30_ADDR 14
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D31_ADDR 15

/*IOMUX ULPI PAD control pad registers value */
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS2_VAL 0x0005
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS3_VAL 0x0080
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS4_VAL 0x0080
#define IOMUXC_SW_PAD_CTL_PAD_EIM_CS5_VAL 0x0180

#define IOMUXC_SW_PAD_CTL_PAD_EIM_D24_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D25_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D26_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D27_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D28_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D29_VAL  0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D30_VAL 0x0085
#define IOMUXC_SW_PAD_CTL_PAD_EIM_D31_VAL 0x0085


#define HAPI_IOMUX_USB_GPIO1_5     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(240)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_5_DIR        (0xFF)

#define HAPI_IOMUX_USB_GPIO1_6     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(241)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_6_DIR        (0xFF)

/*****************************END ULPI IOMUX config *********************/
/*****************************IOMUX USB Serial configuration *******************/

/*config GPIO1_8 pad for usboh3 instance USB_PWR port*/
#define HAPI_IOMUX_USB_GPIO1_8_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_GPIO1_8_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_GPIO1_8_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(243)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_8_DIR        (0xFF)



/*config GPIO1_9 pad for usboh3 instance USB_OC port*/
#define HAPI_IOMUX_USB_GPIO1_9_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_GPIO1_9_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_GPIO1_9_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(244)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_9_DIR        (0xFF)


/*USBOTG_DATA0-USBOTG_DATA6 uses pad EIM_D24 to EIM_D30 */


#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_8_ADDR      266
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_8_VAL        0x0085
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_9_ADDR      267
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_9_VAL       0x0085
/*****************************END serial IOMUX config *********************/

/******************CSPI IOMUX config ****************************************/
/*CSPI  SCLK line */
#define HAPI_IOMUX_USBH1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USBH1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USBH1_CLK_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(151)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USBH1_CLK_DIR     (0xFF)
/*CSPI MOSI*/
#define HAPI_IOMUX_USBH1_DIR_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USBH1_DIR_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USBH1_DIR_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(152)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USBH1_DIR_DIR     (0xFF)

/*CSPI RDY port */
#define HAPI_IOMUX_USBH1_STP_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USBH1_STP_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USBH1_STP_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(153)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USBH1_STP_DIR     (0xFF)

/*CSPI MISO port */
#define HAPI_IOMUX_USBH1_NXT_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USBH1_NXT_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USBH1_NXT_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(154)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USBH1_NXT_DIR     (0xFF)




/*CSPI SS1*/
#define HAPI_IOMUX_USBH1_DATA5_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USBH1_DATA5_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USBH1_DATA5_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(160)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USBH1_DATA5_DIR     (0xFF)


/*CSPI  SCLK line */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_CLK_ADDR   162
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_CLK_VAL      0x0105
/*CSPI MOSI*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DIR_ADDR   163
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DIR_VAL     0x0105
/*CSPI RDY*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_STP_ADDR   164
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_STP_VAL      0x0180

/*CSPI MISO*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_NXT_ADDR   165
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_NXT_VAL      0x0105

/*CSPI SS1*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA5_ADDR   171
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBH1_DATA5_VAL      0x0105

#define IOMUXC_CSPI_IPP_CSPI_CLK_IN_SELECT_INPUT_ADDR 20
#define IOMUXC_CSPI_IPP_CSPI_CLK_IN_SELECT_INPUT_VAL   0x1
#define IOMUXC_CSPI_IPP_MISO_SELECT_INPUT_ADDR 21
#define IOMUXC_CSPI_IPP_MISO_SELECT_INPUT_VAL   0x0
#define IOMUXC_CSPI_IPP_MOSI_SELECT_INPUT_ADDR 22
#define IOMUXC_CSPI_IPP_MOSI_SELECT_INPUT_VAL   0x1
#define IOMUXC_CSPI_IPP_SS1_B_SELECT_INPUT_ADDR 23
#define IOMUXC_CSPI_IPP_SS1_B_SELECT_INPUT_VAL   0x0

/******************CSPI IOMUX config end ****************************************/
/******************eCSPI1 IOMUX config start***************************************/
/*eCSPI1  MOSI line */
#define HAPI_IOMUX_CSPI1_MOSI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MOSI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MOSI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (REG_NUM(125)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MOSI_DIR     (0xFF)

/*eCSPI1  MISO line */
#define HAPI_IOMUX_CSPI1_MISO_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MISO_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MISO_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (REG_NUM(126)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MISO_DIR     (0xFF)

/*eCSPI1  SS1 line */
#define HAPI_IOMUX_CSPI1_SS1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS1_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (REG_NUM(128)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS1_DIR     (0xFF)

/*eCSPI1  RDY line */
#define HAPI_IOMUX_CSPI1_RDY_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_RDY_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_RDY_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (REG_NUM(129)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_RDY_DIR     (0xFF)

/*eCSPI1  SCLK line */
#define HAPI_IOMUX_CSPI1_SCLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SCLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SCLK_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (REG_NUM(130)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SCLK_DIR     (0xFF)



#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_ADDR  132
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_VAL    0x0105
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MISO_ADDR  133
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MISO_VAL     0x0105
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS1_ADDR     135
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS1_VAL       0x0105
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_RDY_ADDR     136
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_RDY_VAL       0x0180
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_ADDR  137
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_VAL      0x0105



/******************eCSPI1 IOMUX   Config end***************************************/
/******************eCSPI2 IOMUX config start***************************************/
/*CSPI RDY line */
#define HAPI_IOMUX_ECSPI2_NANDF_RB1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ECSPI2_NANDF_RB1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ECSPI2_NANDF_RB1_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(65)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ECSPI2_NANDF_RB1_DIR     (0xFF)
/*CSPI SCLK*/
#define HAPI_IOMUX_ECSPI2_NANDF_RB2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ECSPI2_NANDF_RB2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ECSPI2_NANDF_RB2_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(66)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ECSPI2_NANDF_RB2_DIR     (0xFF)

/*CSPI MISO*/
#define HAPI_IOMUX_ECSPI2_NANDF_RB3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ECSPI2_NANDF_RB3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ECSPI2_NANDF_RB3_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(67)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ECSPI2_NANDF_RB3_DIR     (0xFF)

/*CSPI MOSI*/
#define HAPI_IOMUX_ECSPI2_NANDF_D15_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ECSPI2_NANDF_D15_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ECSPI2_NANDF_D15_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(78)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ECSPI2_NANDF_D15_DIR     (0xFF)


/*CSPI SS1*/
#define HAPI_IOMUX_ECSPI2_NANDF_D12_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ECSPI2_NANDF_D12_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ECSPI2_NANDF_D12_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(81)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ECSPI2_NANDF_D12_DIR     (0xFF)


/*IOMUX pad control pad register of eCSPI2*/
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB1_ADDR 67
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB1_VAL    0x0180
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB2_ADDR 68
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB2_VAL    0x0104
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB3_ADDR 69
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_RB3_VAL    0x0104
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_D15_ADDR 83
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_D15_VAL    0x0104
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_D12_ADDR 86
#define IOMUXC_ECSPI2_SW_PAD_CTL_PAD_NANDF_D12_VAL    0x0104


#define IOMUXC_ECSPI2_IPP_IND_SS_B_1_SELECT_INPUT_ADDR  27
#define IOMUXC_ECSPI2_IPP_IND_SS_B_1_SELECT_INPUT_VAL   0x1


/******************eCSPI1 IOMUX   Config end***************************************/

/************************** eSDHC1 IOMUX config ***********************************/
/* SD1_CMD MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(222)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_CMD_DIR   (0xFF)

/* SD1_CLK MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_CLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_CLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_CLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(223)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_CLK_DIR   (0xFF)

/* SD1_DAT0 MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                         (REG_NUM(224)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_DIR  (0xFF)

/* SD1_DAT3 MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                         (REG_NUM(227)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_DIR  (0xFF)

/* PAD config */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_ADDR     (235)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_VAL      (0x20e4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_ADDR     (236)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_VAL      (0x20d4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_ADDR   (237)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_VAL    (0x20e4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_ADDR   (240)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_VAL    (0x20e4)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_SVAL     (0x20f4)

/************************** eSDHC2 IOMUX config ***********************************/
/* SD2_CMD MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(230)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_CMD_DIR   (0xFF)

/* SD2_CLK MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_CLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_CLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_CLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(231)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_CLK_DIR   (0xFF)

/* SD2_DATA0 MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                          (REG_NUM(232)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_DIR   (0xFF)

/* SD2_DATA3 MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                          (REG_NUM(235)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_DIR   (0xFF)

/* PAD config */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ADDR   (243)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_VAL    (0x20e4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_ADDR   (244)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_VAL    (0x20d4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_ADDR (245)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_VAL  (0x20e4)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_ADDR (248)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_VAL  (0x20e4)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SVAL   (0x20f4)

/************************** eSDHC3 IOMUX config ***********************************/

/* eSDHC3 PAD NANDF_RDY_INT for CMD line */
#define HAPI_IOMUX_NANDF_RDY_INT_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_RDY_INT_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_RDY_INT_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                        (REG_NUM(77)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_RDY_INT_DIR    (0xFF)

/* eSDHC3 PAD NANDF_CS7 for CLK line */
#define HAPI_IOMUX_NANDF_CS7_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS7_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS7_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                    (REG_NUM(76)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS7_DIR    (0xFF)

/* eSDHC3 PAD NANDF_WE_B for DATA0 port  */
#define HAPI_IOMUX_NANDF_WE_B_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_WE_B_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_WE_B_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                    (REG_NUM(59)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_WE_B_DIR   (0xFF)

/* eSDHC3 PAD NANDF_RB0 for DATA3 port  */
#define HAPI_IOMUX_NANDF_RB0_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_RB0_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_RB0_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                    (REG_NUM(64)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_RB0_DIR    (0xFF)

/* Pad config for eSDHC3 module */

/* eSDHC3 pad config CMD */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_ADDR   (82)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_VAL    (0x21e4)

/* eSDHC3 pad config CLK */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS7_ADDR       (81)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS7_VAL        (0x2094)

/* eSDHC3 pad config DATA0 */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_WE_B_ADDR      (61)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_WE_B_VAL       (0x21a4)

/* eSDHC3 pad config DATA3 */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB0_ADDR       (66)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB0_VAL        (0x21e4)

/* Daisy Chain configuration */
#define IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_ADDR    (30)
#define IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_VAL     (0x0)
#define IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_ADDR    (33)
#define IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_VAL     (0x0)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RDY_INT_SVAL    (0x21f4)

/* eMMC support */

/* CMD line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                         (REG_NUM(77)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_DIR   (0xFF)

#define HAPI_GPIO_ESDHC3_CMD_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC3_CMD_PIN   (HAPI_GPIO_PIN_25)
#define HAPI_GPIO_ESDHC3_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC3_CMD_DIR   (0x1)

/* DATA0 line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                           (REG_NUM(59)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_DIR   (0xFF)

#define HAPI_GPIO_ESDHC3_DATA0_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC3_DATA0_PIN   (HAPI_GPIO_PIN_3)
#define HAPI_GPIO_ESDHC3_DATA0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC3_DATA0_DIR   (0x0)

/**************************** eSDHC4 IOMUX config *********************************/

/* eSDHC4 CMD Line */
#define HAPI_IOMUX_NANDF_RB1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_RB1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_RB1_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                     (REG_NUM(65)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_RB1_DIR     (0xFF)

/* eSDHC4 CLK Line */
#define HAPI_IOMUX_NANDF_CS2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                     (REG_NUM(71)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS2_DIR     (0xFF)

/* eSDHC4 DATA0 Line */
#define HAPI_IOMUX_NANDF_CS3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                     (REG_NUM(72)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS3_DIR     (0xFF)

/* eSDHC4 DATA3 Line */
#define HAPI_IOMUX_NANDF_CS6_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS6_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS6_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                     (REG_NUM(75)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS6_DIR     (0xFF)

/* eSDHC4 pad config CMD line */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_ADDR   (67)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_VAL    (0x21e4)

/* eSDHC4 pad config CLK line */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS2_ADDR   (76)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS2_VAL    (0x20d4)

/* eSDHC4 pad config DAT0 line */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS3_ADDR   (77)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS3_VAL    (0x21e4)

/* eSDHC4 pad config DAT3 line */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS6_ADDR   (80)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_CS6_VAL    (0x21a4)


/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_NANDF_RB1_SVAL    (0x21f4)

/* eMMC support */

/* CMD line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC4_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC4_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC4_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                         (REG_NUM(65)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC4_CMD_DIR   (0xFF)

#define HAPI_GPIO_ESDHC4_CMD_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC4_CMD_PIN   (HAPI_GPIO_PIN_9)
#define HAPI_GPIO_ESDHC4_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC4_CMD_DIR   (0x1)

/* DATA0 line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC4_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC4_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC4_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                           (REG_NUM(72)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC4_DATA0_DIR   (0xFF)

#define HAPI_GPIO_ESDHC4_DATA0_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC4_DATA0_PIN   (HAPI_GPIO_PIN_19)
#define HAPI_GPIO_ESDHC4_DATA0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC4_DATA0_DIR   (0x0)


/************************** eSDHC IOMUX config end *******************************/


/************************** I2C1 IOMUX config ************************************/
/* cspi1_sclk port is used as for clock line in ALT1 mode */
#define HAPI_IOMUX_I2C1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                    (IOMUX_IN_SION) | (REG_NUM(130)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_CLK_DIR     (0xFF)

/* cspi1_mosi port is used as for data line in ALT1 mode */
#define HAPI_IOMUX_I2C1_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                    (IOMUX_IN_SION) | (REG_NUM(125)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_DAT_DIR     (0xFF)

/* I2C1 SDA */
#define HAPI_I2C1_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_ADDR   (132)
#define HAPI_I2C1_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_VAL    (0x01ad)

/* I2C1 SCL */
#define HAPI_I2C1_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_ADDR   (137)
#define HAPI_I2C1_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_VAL    (0x01ad)

/* I2C1 Select input register */
#define HAPI_IOMUXC_I2C1_IPP_SCL_IN_SELECT_INPUT_ADDR    (59)
#define HAPI_IOMUXC_I2C1_IPP_SCL_IN_SELECT_INPUT_VAL     (0x1)
#define HAPI_IOMUXC_I2C1_IPP_SDA_IN_SELECT_INPUT_ADDR    (60)
#define HAPI_IOMUXC_I2C1_IPP_SDA_IN_SELECT_INPUT_VAL     (0x1)

/************************** I2C2 IOMUX config ************************************/
/* GPIO1_2 port is used as for clock line in ALT2 mode */
#define HAPI_IOMUX_I2C2_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                    (IOMUX_IN_SION) | (REG_NUM(236)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_CLK_DIR     (0xFF)

/* GPIO1_3 port is used as for data line in ALT2 mode */
#define HAPI_IOMUX_I2C2_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                    (IOMUX_IN_SION) | (REG_NUM(237)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_DAT_DIR     (0xFF)

/* I2C2 SDA */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_GPIO1_3_ADDR   (250)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_GPIO1_3_VAL    (0x01ed)

/* I2C2 SCL */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_GPIO1_2_ADDR   (249)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_GPIO1_2_VAL    (0x01ed)

/* I2C2 Select input register */
#define HAPI_IOMUXC_I2C2_IPP_SCL_IN_SELECT_INPUT_ADDR    (61)
#define HAPI_IOMUXC_I2C2_IPP_SCL_IN_SELECT_INPUT_VAL     (0x3)
#define HAPI_IOMUXC_I2C2_IPP_SDA_IN_SELECT_INPUT_ADDR    (62)
#define HAPI_IOMUXC_I2C2_IPP_SDA_IN_SELECT_INPUT_VAL     (0x3)

/************************* HS-I2C IOMUX config ***********************************/
/* I2C1_CLK port is used as for clock line in ALT0 mode */
#define HAPI_IOMUX_HS_I2C_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_HS_I2C_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_HS_I2C_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (IOMUX_IN_SION) | (REG_NUM(119)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_HS_I2C_CLK_DIR     (0xFF)

/* I2C1_DAT port is used as for data line in ALT0 mode */
#define HAPI_IOMUX_HS_I2C_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_HS_I2C_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_HS_I2C_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                      (IOMUX_IN_SION) | (REG_NUM(120)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_HS_I2C_DAT_DIR     (0xFF)

/* I2C1 SCL */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_CLK_ADDR (126)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_CLK_VAL  (0x009c)

/* I2C1 SDA */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_DAT_ADDR (127)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_DAT_VAL  (0x009c)

/************************* I2C IOMUX config end **********************************/

/* USB LPB Feature MACROS*/
/*config GPIO1_2 pad for  instance gpio1 */
#define HAPI_IOMUX_LPB_GPIO1_2_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_LPB_GPIO1_2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_LPB_GPIO1_2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(236)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_LPB_GPIO1_2_DIR        (0x00)

/*config GPIO1_3 pad for instance gpio1 */
#define HAPI_IOMUX_LPB_GPIO1_3_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_LPB_GPIO1_3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_LPB_GPIO1_3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(237)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_LPB_GPIO1_3_DIR        (0x00)




/*==================================================================================================
                                            MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus /* allow #include in a C++ file (only put this in .h files) */
}
#endif
#endif /* end of - prevent inadvertently including a header file twice */
