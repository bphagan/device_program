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

                        Copyright: 2004-2007 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a
              Freescale Software License Agreement, which has either
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Prabhat Singh                24/09/2007     engcm00253  IOMUX config for serial and ULPI interface
Sajith P V                  10-Sep-2007      TLSbo96209   Modified Pad Configuration
Prabhat singh               07-Aug-2007      TLSbo94951    Addition of Philips USB ISP1301 PHY support and IOMUX changes for I2C2 module
Deepak Agarwal				13-Aug-2007		TLSbo95314   Iomuxing & clocking change for CSPI.
Deepak Agarwal              07-Aug-2007     TLSbo95313   Iomuxing & clocking change for I2C.
prabhat Singh              17-July-2007    Tlbso94839   Modified Register offset for Ringo IOMUX
Sai Kiran Bollu             15-Jun-2007     TLSbo94222   Ported to Ringo
Suresh Kumar                12-Jun-07       TLSbo93947   Added boot support for spi eeprom/serial flash
Mahima Verma                11-Jun-2007     TLSbo93857   Ported to Marley.
Surender Kumar              07-Jun-07       TLSbo93610   IOMUX for ESDHC
Suresh Kumar                30-May-07       TLSbo93641   Porting IOMUX/GPIO for Marley

   25-july-2006 Bharat Bhushan  CR-TLSbo73972
                IOMUX change in L3 and pinmuxing sheet.
   20-july-2006 Bharat Bhushan  CR-TLSbo73521
                New Boot ROM Design Support for USB/UART Serial Downloader ( IOMUX Defines added )
   28-jun-2006 Bharat Bhushan CR-TLSbo72164
               IOMUX Programming for 6-wire Serial Mode.
   09-jun-2006 Bharat Bhushan CR-TLSbo68884
               IOMUX defines added for CSPI and USB .
   08-Jun-2006 Suresh Kumar CR-TLSbo68884
               IOMUX defines for UART1
   26-May-2006 Lucky Sharma   CR- TLSbo69185 islay would use GP_SP_A8 instead of historical GP_AP_C9 for selection between UART/USB
   04-08-25   rziolkowski CR - LIBff08888
              Update to IOMUX programming for USB 4 wire to 6 wire.
   04-08-18   jvoss/joeh  CR - LIBff06722
              SCM-A11:change the IOMUX programming on HAPI_GPIO_USB_XCVR_EN.
              The integration team swapped the output MUX 0 and MUX 1 lines.
              Therefore MUX1 now becomes MUX0. Inputs remain the same.
   04-08-12   rziolkowski CR - LIBff03632
              Enable IOMUX for USB_VP1 and USB_VM1 for 6 wire mode for SCM-A11
   04-01-07   rziolkowski CR - LIBee27940
              Rework from inspection comments
   04-30-06   rziolkowski CR - LIBee27940
              Changed Argon+ configuration for USB XCVR enable (GPIO1)
   04-06-06   rziolkowski CR - LIBee13501
              Rework from inspection comments
   04-05-28   rziolkowski CR - LIBee13501
              Updates for SCM-A11
   04-04-28   jvoss       CR - LIBee01069
              Argon+/SCM-A11 GPIO
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
#define HAPI_GPIO2_0_PAD_VALUE 0x00e1

#define HAPI_IOMUX_USB_DIR_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DIR_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DIR_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 IOMUX_IN_SION | (REG_NUM(0x7E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DIR_DIR  (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD19 206
#define HAPI_LD19_PAD_VALUE   0x00e1

/*Select input register configuration*/
   
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DIR_SELECT_INPUT_REG 135
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DIR_SELECT_INPUT_VAL   0



#define HAPI_IOMUX_USB_STP_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_STP_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 (REG_NUM(0x80)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_DIR  (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD21 208
#define HAPI_LD21_PAD_VALUE   0x0061



#define HAPI_IOMUX_USB_NXT_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_NXT_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_NXT_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                 IOMUX_IN_SION | (REG_NUM(0x81)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_NXT_DIR  (0xFF)

/*Select input register configuration*/
   
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_NXT_SELECT_INPUT_REG 136
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_NXT_SELECT_INPUT_VAL   0


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD22 209
#define HAPI_LD22_PAD_VALUE   0x00e1


#define HAPI_IOMUX_USB_DAT0_ULPI_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_ULPI_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_ULPI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                 IOMUX_IN_SION | (REG_NUM(0x8E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_ULPI_DIR    (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1 222
#define HAPI_USB_SD1_DATA1_PAD_VALUE   0x00e1

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
#define HAPI_USB_SD1_DATA2_PAD_VALUE   0x00e1

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
#define HAPI_USB_SD1_DATA3_PAD_VALUE   0x00e1


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
#define HAPI_LD18_PAD_VALUE   0x00e1


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
#define HAPI_SD1_CMD_PAD_VALUE 0x00e1


/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_4_SELECT_INPUT_REG 131
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_4_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT5_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                              IOMUX_IN_SION |  (REG_NUM(0x8C)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK 220
#define HAPI_SD1_CLK_PAD_VALUE 0x00e1
/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_5_SELECT_INPUT_REG 132
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_5_SELECT_INPUT_VAL 0

#define HAPI_IOMUX_USB_DAT6_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                            IOMUX_IN_SION |  (REG_NUM(0x8D)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0 221
#define HAPI_SD1_DATA0_PAD_VALUE 0x00e1

/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_6_SELECT_INPUT_REG 133
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_6_SELECT_INPUT_VAL 0


#define HAPI_IOMUX_USB_DAT7_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT7_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT7_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                           IOMUX_IN_SION | (REG_NUM(0x82)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT7_ULPI_DIR     (0xFF)
/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_LD23 209
#define HAPI_LD23_PAD_VALUE   0x00e1
/*Select input register configuration*/
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_7_SELECT_INPUT_REG 134
#define HAPI_IOMUXC_USB_TOP_IPP_IND_OTG_DATA_7_SELECT_INPUT_VAL 0
/******************************SERIAL IOMUX Defines ****************************/
/************************************SERIAL  END *************************************/

/***************ESDHC3 IOMUX Defination   ***************************************/

#define HAPI_IOMUX_ATA_DIOR_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DIOR_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DIOR_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(153)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DIOR_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DIOW_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DIOW_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DIOW_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(154)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DIOW_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DMACK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DMACK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DMACK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(155)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DMACK_DIR     (0xFF)

#define HAPI_IOMUX_ATA_RESET_B_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_RESET_B_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_RESET_B_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(156)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_RESET_B_DIR     (0xFF)

#define HAPI_IOMUX_ATA_IORDY_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_IORDY_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_IORDY_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(157)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_IORDY_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DATA0_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DATA0_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DATA0_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(158)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DATA0_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DATA1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DATA1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DATA1_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(159)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DATA1_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DATA2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DATA2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DATA2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(160)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DATA2_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DATA3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DATA3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DATA3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(161)) | (REG_OFFSET(0)))
 #define HAPI_IOMUX_ATA_DATA3_DIR     (0xFF)

#define HAPI_IOMUX_ATA_DATA4_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ATA_DATA4_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ATA_DATA4_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                 IOMUX_IN_SION | (REG_NUM(162)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ATA_DATA4_DIR     (0xFF)

/************************************CSPI 1 defines *********************************/

#define HAPI_IOMUX_CSPI1_TX1_SS2_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_TX1_SS2_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_TX1_SS2_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 |\
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
#define HAPI_IOMUX_CSPI1_RDY_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 |\
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
/*Pad config value for SD1/SD2*/

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_REG  (224)
#define HAPI_SD1_DATA3_PAD_VALUE 0x01E3
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_REG  (230)
#define HAPI_SD2_DATA3_PAD_VALUE 0x01E3


/*Pad config value for ehdc3 used for PATA and MMC*/
  /*Register number of PAD*/

#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DIOR_REG        (233)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DIOW_REG       (234)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DMACK_REG     (235)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_RESET_B_REG  (236)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_IORDY_REG     (237)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA0_REG     (238)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA1_REG     (239)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA2_REG     (240)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA3_REG     (241)
#define  HAPI_IOMUXC_SW_PAD_CTL_PAD_ATA_DATA4_REG     (242)

/*PAD values of esdhc3 */
#define  HAPI_ATA_DIOR_PAD_VALUE  0x01d3
#define  HAPI_ATA_DIOW_PAD_VALUE  0x01d3
#define  HAPI_ATA_DMACK_PAD_VALUE  0x01d3
#define  HAPI_ATA_IORDY_PAD_VALUE  0x01d3
#define  HAPI_ATA_DATA0_PAD_VALUE  0x01d3
#define  HAPI_ATA_DATA1_PAD_VALUE  0x01d3
#define  HAPI_ATA_DATA2_PAD_VALUE  0x01d3
#define  HAPI_ATA_DATA3_PAD_VALUE  0x00d3
#define  HAPI_ATA_DATA4_PAD_VALUE  0x01d3
#define  HAPI_ATA_RESET_B_PAD_VALUE  0x01E3

/*software select input control register  */
#define HAPI_IOMUXC_ESDHC3_IPP_DAT0_IN_SELECT_INPUT_REG (28)
#define HAPI_IOMUXC_ESDHC3_IPP_DAT1_IN_SELECT_INPUT_REG (29)
#define HAPI_IOMUXC_ESDHC3_IPP_DAT2_IN_SELECT_INPUT_REG (30)
#define HAPI_IOMUXC_ESDHC3_IPP_DAT3_IN_SELECT_INPUT_REG (31)
#define HAPI_IOMUXC_ESDHC3_IPP_CARD_CLK_IN_SELECT_INPUT_REG (26)
#define HAPI_IOMUXC_ESDHC3_IPP_CMD_IN_SELECT_INPUT_REG (27)



#define HAPI_ESDHC3_IPP_DAT0_IN_SELECT_INPUT_VAL 0x01
#define HAPI_ESDHC3_IPP_DAT1_IN_SELECT_INPUT_VAL 0x01
#define HAPI_ESDHC3_IPP_DAT2_IN_SELECT_INPUT_VAL 0x01
#define HAPI_ESDHC3_IPP_DAT3_IN_SELECT_INPUT_VAL 0x01
#define HAPI_ESDHC3_IPP_CARD_CLK_IN_SELECT_INPUT_VAL 0x01
#define HAPI_ESDHC3_IPP_CMD_IN_SELECT_INPUT_VAL   0x01



/* Pad strength defines */
#define LOW_DRIVE       0x0
#define MEDIUM_DRIVE    0x1
#define HIGH_DRIVE      0x2
#define MAX_DRIVE       0x3
#define PAD_STRENGTH_SHIFT	0x1

#define SLEW_SLOW	0x0
#define SLEW_FAST	0x1

/* PU/PD strength defines */
#define PD100KOHM       0x0
#define PU100KOHM       0x1
#define PU47KOHM        0x2
#define PU22KOHM        0x3

#define PUPD_STRENGTH_SHIFT	0x5
#define PUPD_ENABLE	        0x80


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
