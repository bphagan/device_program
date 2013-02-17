#ifndef HAPI_GPIO_DEFS_INCLUDE /* To prevent inadvertently including a header twice */
#define HAPI_GPIO_DEFS_INCLUDE

#ifdef __cplusplus  /* allow #include in a C++ file (only put this in .h files) */
extern "C" {
#endif

/*==================================================================================================

    Header Name: hapi_gpio_defs.h

    General Description:
       This file contains the memory map of the GPIO.

===============================================================================
                    Freescale Confidential Proprietary
            Template ID and version: IL93-TMP-01-0106  Version 1.20
            (c) Copyright Freescale 2004, All Rights Reserved

                    Copyright: 2004-2008 FREESCALE, INC.
            All Rights Reserved. This file contains copyrighted material.
            Use of this file is restricted by the provisions of a
            Freescale Software License Agreement, which has either
            accompanied the delivery of this software in shrink wrap
            form or been expressly executed between the parties.

Revision History:
                 Modification    Tracking
Author               Date         Number     Description of Changes
----------------  ------------  ----------   ----------------------------------
Siva Pothireddy   29/Jul/2008   ENGcm06847   IOMUX changes for CSPI1
Chandan Singh     24/Jul/2008   ENGcm06748   IOMUX changes for RingoTO2 for eSDHC
Siva Pothireddy   04/Apr/2008   ENGcm04928   IOMUX defines are changed for ULPI.
Prabhat Singh     24/Sep/2007   ENGcm00253   IOMUX config for serial and ULPI interface
Sajith P V        10/Sep/2007   TLSbo96209   Modified Pad Configuration
Prabhat singh     07/Aug/2007   TLSbo94951   Addition of Philips USB ISP1301 PHY support and IOMUX changes for I2C2 module
Deepak Agarwal    13/Aug/2007   TLSbo95314   Iomuxing & clocking change for CSPI.
Deepak Agarwal    07/Aug/2007   TLSbo95313   Iomuxing & clocking change for I2C.
prabhat Singh     17/Jul/2007   Tlbso94839   Modified Register offset for Ringo IOMUX
Sai Kiran Bollu   15/Jun/2007   TLSbo94222   Ported to Ringo
Suresh Kumar      12/Jun/2007   TLSbo93947   Added boot support for spi eeprom/serial flash
Mahima Verma      11/Jun/2007   TLSbo93857   Ported to Marley.
Surender Kumar    07/Jun/2007   TLSbo93610   IOMUX for ESDHC
Suresh Kumar      30/May/2007   TLSbo93641   Porting IOMUX/GPIO for Marley
Bharat Bhushan    25/Jul/2006   TLSbo73972   IOMUX change in L3 and pinmuxing sheet.
Bharat Bhushan    20/Jul/2006   TLSbo73521   New Boot ROM Design Support for USB/UART Serial Downloader ( IOMUX Defines added )
Bharat Bhushan    28/Jun/2006   TLSbo72164   IOMUX Programming for 6-wire Serial Mode.
Bharat Bhushan    09/Jun/2006   TLSbo68884   IOMUX defines added for CSPI and USB .
Suresh Kumar      08/Jun/2006   TLSbo68884   IOMUX defines for UART1
Lucky Sharma      26/May/2006   TLSbo69185   Islay would use GP_SP_A8 instead of historical GP_AP_C9 for selection between UART/USB
Rziolkowski       25/Aug/2004   LIBff08888   Update to IOMUX programming for USB 4 wire to 6 wire.
Jvoss/Joeh        18/Aug/2004   LIBff06722   SCM-A11:change the IOMUX programming on HAPI_GPIO_USB_XCVR_EN.
                                             The integration team swapped the output MUX 0 and MUX 1 lines.
                                             Therefore MUX1 now becomes MUX0. Inputs remain the same.
Rziolkowski       12/Aug/2004   LIBff03632   Enable IOMUX for USB_VP1 and USB_VM1 for 6 wire mode for SCM-A11
Rziolkowski       01/Jul/2004   LIBee27940   Rework from inspection comments
Rziolkowski       30/Jun/2004   LIBee27940   Changed Argon+ configuration for USB XCVR enable (GPIO1)
Rziolkowski       06/Jun/2004   LIBee13501   Rework from inspection comments
Rziolkowski       28/May/2004   LIBee13501   Updates for SCM-A11
Jvoss             28/Apr/2004   LIBee01069   Argon+/SCM-A11 GPIO
                                             - Complete rewrite
====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

#define REG_NUM(num) (num << IOMUX_REG_NUM_SHIFT)
#define REG_OFFSET(num) (num << IOMUX_REG_OFFSET_SHIFT)
/*USB OTG power and OC reg number*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_PWR 185
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_OC  186

/*Pad config value for USB OTG */
#define HAPI_USBOTG_PWR_PAD_VALUE 0x0040
#define HAPI_USBOTG_OC_PAD_VALUE 0x01c0

/******************************ULPI IOMUX Defines ****************************/

#define HAPI_IOMUX_USB_CLK_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_CLK_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_CLK_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                IOMUX_IN_SION | (REG_NUM(0x5)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_CLK_DIR  (0xFF)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_GPIO2_0 5
#define HAPI_GPIO2_0_PAD_VALUE 0x00c3

#define HAPI_IOMUX_USB_DIR_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DIR_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DIR_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 IOMUX_IN_SION | (REG_NUM(0x7E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DIR_DIR  (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD19 206
#define HAPI_LD19_PAD_VALUE   0x00c3

/*Select input register configuration*/

#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DIR_SELECT_INPUT_REG 135
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DIR_SELECT_INPUT_VAL   0

#define HAPI_IOMUX_USB_STP_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_STP_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 (REG_NUM(0x80)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_DIR  (0xFF)

#define HAPI_IOMUX_USB_STP_GPIO_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_GPIO_PIN  (HAPI_GPIO_PIN_27)
#define HAPI_IOMUX_USB_STP_GPIO_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 |\
                                 (REG_NUM(0x80)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_GPIO_DIR  (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD21 208
#define HAPI_LD21_PAD_VALUE   0x00c3
#define HAPI_LD21_PAD_VALUE_PULLUP 0x00e1

#define HAPI_IOMUX_USB_NXT_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_NXT_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_NXT_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 IOMUX_IN_SION | (REG_NUM(0x81)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_NXT_DIR  (0xFF)

/*Select input register configuration*/

#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_NXT_SELECT_INPUT_REG 136
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_NXT_SELECT_INPUT_VAL   0

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD22 209
#define HAPI_LD22_PAD_VALUE   0x00c3

#define HAPI_IOMUX_USB_DAT0_ULPI_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_ULPI_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_ULPI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                 IOMUX_IN_SION | (REG_NUM(0x8E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_ULPI_DIR    (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1 222
#define HAPI_USB_SD1_DATA1_PAD_VALUE   0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_0_SELECT_INPUT_REG 127
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_0_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT1_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT1_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT1_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                IOMUX_IN_SION | (REG_NUM(0x8F)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT1_ULPI_DIR   (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2 223
#define HAPI_USB_SD1_DATA2_PAD_VALUE   0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_1_SELECT_INPUT_REG 128
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_1_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT2_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT2_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT2_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                IOMUX_IN_SION | (REG_NUM(0x90)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT2_ULPI_DIR   (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3 224
#define HAPI_USB_SD1_DATA3_PAD_VALUE   0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_2_SELECT_INPUT_REG 129
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_2_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT3_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT3_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT3_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                               IOMUX_IN_SION | (REG_NUM(0x7D)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT3_ULPI_DIR     (0xFF)

/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD18 205
#define HAPI_LD18_PAD_VALUE   0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_3_SELECT_INPUT_REG 130
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_3_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT4_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT4_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT4_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                              IOMUX_IN_SION | (REG_NUM(0x8B)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT4_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD 219
#define HAPI_SD1_CMD_PAD_VALUE 0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_4_SELECT_INPUT_REG 131
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_4_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT5_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                              IOMUX_IN_SION |  (REG_NUM(0x8C)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK (220)
#define HAPI_SD1_CLK_PAD_VALUE 0x00c3
/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_5_SELECT_INPUT_REG 132
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_5_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT6_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                            IOMUX_IN_SION |  (REG_NUM(0x8D)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0 (221)
#define HAPI_SD1_DATA0_PAD_VALUE 0x00c3

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_6_SELECT_INPUT_REG 133
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_6_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT7_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT7_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT7_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                           IOMUX_IN_SION | (REG_NUM(0x82)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT7_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD23 210
#define HAPI_LD23_PAD_VALUE   0x00c3
/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_7_SELECT_INPUT_REG 134
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_7_SELECT_INPUT_VAL 0

/************************************CSPI 1 defines *********************************/
#define HAPI_IOMUX_CSPI1_TX1_SS2_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_TX1_SS2_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_TX1_SS2_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                   (REG_NUM(89)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_TX1_SS2_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_MOSI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MOSI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MOSI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(91)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MOSI_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_MISO_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MISO_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MISO_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(92)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MISO_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SS0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(93)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS0_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SS1_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS1_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS1_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(94)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS1_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SCLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SCLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SCLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(95)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SCLK_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_RDY_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_RDY_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_RDY_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(96)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_RDY_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_TX1_SS2_REG (161)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_REG (163)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MISO_REG (164)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS0_REG (165)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS1_REG (166)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_REG (167)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_RDY_REG (168)

#define HAPI_CSPI1_TX1_SS2_PAD_VALUE 0x01E0
#define HAPI_CSPI1_MOSI_PAD_VALUE 0x01C0
#define HAPI_CSPI1_MISO_PAD_VALUE 0x01C0
#define HAPI_CSPI1_SS0_PAD_VALUE 0x01E0
#define HAPI_CSPI1_SS1_PAD_VALUE 0x01E0
#define HAPI_CSPI1_SCLK_PAD_VALUE 0x01C0
#define HAPI_CSPI1_RDY_PAD_VALUE 0x01E0

#define IOMUXC_CSPI1_IPP_IND_SS2_B_SELECT_INPUT_ADDR 12
#define IOMUXC_CSPI1_IPP_IND_SS2_B_SELECT_INPUT_VALUE 0x2 /*10b: Selecting Pad: TX1 for Mode: ALT2.*/


/************************************I2C1 defines *********************************/
#define HAPI_IOMUX_I2C1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | IOMUX_IN_SION |\
                                     (REG_NUM(67)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C1_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | IOMUX_IN_SION |\
                                     (REG_NUM(68)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_DAT_DIR     (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_CLK_REG (139)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_DAT_REG (140)
#define HAPI_I2C1_CLK_PAD_VALUE 0x01E8
#define HAPI_I2C1_DAT_PAD_VALUE 0x01E8

/************************************I2C2 IOMUX *********************************/
#define HAPI_IOMUX_I2C2_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | IOMUX_IN_SION |\
                                     (REG_NUM(69)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C2_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | IOMUX_IN_SION |\
                                     (REG_NUM(70)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_DAT_DIR     (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C2_CLK_REG  (141)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C2_DAT_REG  (142)
#define HAPI_I2C2_CLK_PAD_VALUE 0x01E8
#define HAPI_I2C2_DAT_PAD_VALUE 0x01E8

/************************** eSDHC1 IOMUX config ***********************************/
/* SD1_CMD MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(139)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_CMD_DIR   (0xFF)

/* SD1_CLK MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_CLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_CLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_CLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(140)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_CLK_DIR   (0xFF)

/* SD1_DAT0 MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                         (REG_NUM(141)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_DATA0_DIR  (0xFF)

/* SD1_DAT3 MUX config */
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                         (REG_NUM(144)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_SD1_DATA3_DIR  (0xFF)

/* PAD config */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_ADDR     (219)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_VAL      (0x01e3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_ADDR     (220)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_VAL      (0x01d3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_ADDR   (221)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_VAL    (0x01e3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_ADDR   (224)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_VAL    (0x01e3)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_SVAL     (0x01f3)

/* eMMC support */

/* CMD line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(139)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_DIR   (0xFF)

#define HAPI_GPIO_ESDHC1_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_ESDHC1_CMD_PIN   (HAPI_GPIO_PIN_6)
#define HAPI_GPIO_ESDHC1_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC1_CMD_DIR   (0x1)

/* DATA0 line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC1_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC1_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC1_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                           (REG_NUM(141)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC1_DATA0_DIR   (0xFF)

#define HAPI_GPIO_ESDHC1_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_ESDHC1_DATA0_PIN   (HAPI_GPIO_PIN_8)
#define HAPI_GPIO_ESDHC1_DATA0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC1_DATA0_DIR   (0x0)

/* Daisy Chain configuration */
#define IOMUXC_GPIO1_IPP_IND_G_IN_6_SELECT_INPUT_ADDR   (44)
#define IOMUXC_GPIO1_IPP_IND_G_IN_6_SELECT_INPUT_VAL    (2)
#define IOMUXC_GPIO1_IPP_IND_G_IN_8_SELECT_INPUT_ADDR   (46)
#define IOMUXC_GPIO1_IPP_IND_G_IN_8_SELECT_INPUT_VAL    (2)

/************************** eSDHC2 IOMUX config ***********************************/
/* SD2_CMD MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(145)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_CMD_DIR   (0xFF)

/* SD2_CLK MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_CLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_CLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_CLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                        (REG_NUM(146)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_CLK_DIR   (0xFF)

/* SD2_DATA0 MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                          (REG_NUM(147)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_DATA0_DIR   (0xFF)

/* SD2_DATA3 MUX config */
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                          (REG_NUM(150)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_SD2_DATA3_DIR   (0xFF)

/* PAD config */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ADDR   (225)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_VAL    (0x01e3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_ADDR   (226)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_VAL    (0x01d3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_ADDR (227)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0_VAL  (0x01e3)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_ADDR (230)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_VAL  (0x01e3)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SVAL   (0x01f3)

/* eMMC support */

/* CMD line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(145)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_DIR   (0xFF)

#define HAPI_GPIO_ESDHC2_CMD_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC2_CMD_PIN   (HAPI_GPIO_PIN_0)
#define HAPI_GPIO_ESDHC2_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC2_CMD_DIR   (0x1)

/* DATA0 line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC2_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC2_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC2_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                           (REG_NUM(147)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC2_DATA0_DIR   (0xFF)

#define HAPI_GPIO_ESDHC2_DATA0_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC2_DATA0_PIN   (HAPI_GPIO_PIN_2)
#define HAPI_GPIO_ESDHC2_DATA0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC2_DATA0_DIR   (0x0)

/* Daisy Chain configuration */
#define IOMUXC_GPIO2_IPP_IND_G_IN_0_SELECT_INPUT_ADDR   (48)
#define IOMUXC_GPIO2_IPP_IND_G_IN_0_SELECT_INPUT_VAL    (2)
#define IOMUXC_GPIO2_IPP_IND_G_IN_2_SELECT_INPUT_ADDR   (70)
#define IOMUXC_GPIO2_IPP_IND_G_IN_2_SELECT_INPUT_VAL    (2)
/************************** eSDHC3 IOMUX config ***********************************/

/* eSDHC3 PAD ATA_DATA4 for CMD line */
#define HAPI_IOMUX_ESDHC3_SD3_CMD_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC3_SD3_CMD_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC3_SD3_CMD_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                         (REG_NUM(162)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC3_SD3_CMD_DIR    (0xFF)

/* eSDHC3 PAD ATA_DATA3 for CLK line */
#define HAPI_IOMUX_ESDHC3_SD3_CLK_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC3_SD3_CLK_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC3_SD3_CLK_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                         (REG_NUM(161)) | IOMUX_IN_SION | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC3_SD3_CLK_DIR    (0xFF)

/* eSDHC3 PAD ATA_DIOR for DATA0 port  */
#define HAPI_IOMUX_ESDHC3_SD3_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC3_SD3_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC3_SD3_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                          (REG_NUM(153)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC3_SD3_DATA0_DIR   (0xFF)

/* eSDHC3 PAD ATA_RESET_B for DATA3 port  */
#define HAPI_IOMUX_ESDHC3_SD3_DATA3_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC3_SD3_DATA3_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC3_SD3_DATA3_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                           (REG_NUM(156)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC3_SD3_DATA3_DIR    (0xFF)

/* Pad config for eSDHC3 module */

/* eSDHC3 pad config CMD */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA4_ADDR   (242)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA4_VAL    (0x01e3)

/* eSDHC3 pad config CLK */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA3_ADDR   (241)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA3_VAL    (0x01d3)

/* eSDHC3 pad config DATA0 */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DIOR_ADDR    (233)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DIOR_VAL     (0x01e3)

/* eSDHC3 pad config DATA3 */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_RESET_B_ADDR (236)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_RESET_B_VAL  (0x01e3)

/* Daisy Chain configuration */
#define IOMUXC_ESDHC3_IPP_CMD_IN_SELECT_INPUT_ADDR    (28)
#define IOMUXC_ESDHC3_IPP_CMD_IN_SELECT_INPUT_VAL     (0x1)
#define IOMUXC_ESDHC3_IPP_CLK_IN_SELECT_INPUT_ADDR    (27)
#define IOMUXC_ESDHC3_IPP_CLK_IN_SELECT_INPUT_VAL     (0x1)
#define IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_ADDR  (29)
#define IOMUXC_ESDHC3_IPP_DATA0_IN_SELECT_INPUT_VAL   (0x1)
#define IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_ADDR  (32)
#define IOMUXC_ESDHC3_IPP_DATA3_IN_SELECT_INPUT_VAL   (0x1)

/* Pull-up values for CMD line used for MMC */
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA4_SVAL     (0x01f3)

/* eMMC support */

/* CMD line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(162)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC3_CMD_DIR   (0xFF)

#define HAPI_GPIO_ESDHC3_CMD_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC3_CMD_PIN   (HAPI_GPIO_PIN_17)
#define HAPI_GPIO_ESDHC3_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC3_CMD_DIR   (0x1)

/* DATA0 line configured as GPIO */
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                           (REG_NUM(153)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC3_DATA0_DIR   (0xFF)

#define HAPI_GPIO_ESDHC3_DATA0_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC3_DATA0_PIN   (HAPI_GPIO_PIN_8)
#define HAPI_GPIO_ESDHC3_DATA0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC3_DATA0_DIR   (0x0)

/* Daisy Chain configuration */
#define IOMUXC_GPIO2_IPP_IND_G_IN_17_SELECT_INPUT_ADDR  (56)
#define IOMUXC_GPIO2_IPP_IND_G_IN_17_SELECT_INPUT_VAL   (1)
#define IOMUXC_GPIO2_IPP_IND_G_IN_8_SELECT_INPUT_ADDR   (78)
#define IOMUXC_GPIO2_IPP_IND_G_IN_8_SELECT_INPUT_VAL    (1)
/************************** eSDHC IOMUX config end *******************************/

/* Pad strength defines */
#define LOW_DRIVE           (0x0)
#define MEDIUM_DRIVE        (0x1)
#define HIGH_DRIVE          (0x2)
#define MAX_DRIVE           (0x3)
#define PAD_STRENGTH_SHIFT  (0x1)
#define SLEW_SLOW           (0x0)
#define SLEW_FAST           (0x1)

/* PU/PD strength defines */
#define PD100KOHM           (0x0)
#define PU100KOHM           (0x1)
#define PU47KOHM            (0x2)
#define PU22KOHM            (0x3)
#define PUPD_STRENGTH_SHIFT (0x05)
#define PUPD_ENABLE         (0x80)


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
