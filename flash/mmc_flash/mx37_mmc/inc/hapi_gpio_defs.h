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

             (c) Copyright Motorola 1997 - 2004, All rights reserved.        
             Motorola Confidential Proprietary
             Contains confidential proprietary information of Motorola, Inc.
             Reverse engineering is prohibited.
             The copyright notice does not imply publication.
  
                        Copyright: 2004,2005,2006,2007,2008 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a
              Freescale Software License Agreement, which has either
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Radhish                     02/07/2008      ENGcm06379   eMMC4.3 support/FastBoot eSD Boot Support
Mahima Verma                12-Oct-2007     ENGcm00827   Iomux changes updated.
prabhat singh                  09/10/2007       engcm00737  setting SION bit in IOMUX I2C1 module  register 
Mahima Verma                13-Sep-2007     TLSbo96294   Iomux change for USB. 
Surender Kumar              24-Aug-2007     TLSbo94734   High Capacity SD
Suresh Kumar                21-Aug-2007     TLSbo95760   CSPI burst length fixes
Mahima Verma                20-Aug-2007     TLSbo95872   Iomux changes.
Mahima Verma                19-Jul-2007     TLSbo94701   Iomuxing & clocking change.
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

/*************************** UART IOMUX DEFINES *****************************/

#define HAPI_IOMUX_UART1_RXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_RXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_RXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(85)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_RXD_DIR     (0xFF)

#define HAPI_IOMUX_UART1_TXD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART1_TXD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART1_TXD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                     (REG_NUM(86)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART1_TXD_DIR     (0xFF)

/******************************ULPI IOMUX Defines ****************************/

#define HAPI_IOMUX_USB_CLK_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_CLK_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_CLK_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(65)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_CLK_DIR  (0xFF)

#define HAPI_IOMUX_USB_DIR_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DIR_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DIR_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(66)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DIR_DIR  (0xFF)

#define HAPI_IOMUX_USB_STP_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_STP_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                 (REG_NUM(67)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_DIR  (0xFF)

#define HAPI_IOMUX_USB_NXT_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_NXT_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_NXT_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                (REG_NUM(68)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_NXT_DIR  (0xFF)

#define HAPI_IOMUX_USB_DAT0_ULPI_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_ULPI_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_ULPI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(85)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_ULPI_DIR    (0xFF)

#define HAPI_IOMUX_USB_DAT1_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT1_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT1_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                       (REG_NUM(86)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT1_ULPI_DIR   (0xFF)

#define HAPI_IOMUX_USB_DAT2_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT2_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT2_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                       (REG_NUM(87)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT2_ULPI_DIR   (0xFF)

#define HAPI_IOMUX_USB_DAT3_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT3_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT3_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(88)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT3_ULPI_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT4_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT4_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT4_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                         (REG_NUM(89)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT4_ULPI_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT5_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                         (REG_NUM(90)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_ULPI_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT6_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(91)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_ULPI_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT7_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT7_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT7_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                         (REG_NUM(92)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT7_ULPI_DIR     (0xFF)

#define HAPI_IOMUX_USB_GPIO1_5     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(135)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_5_DIR        (0xFF)

#define HAPI_IOMUX_USB_GPIO1_6     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                            (REG_NUM(136)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_GPIO1_6_DIR        (0xFF)

/**********************************ESDHC1 IOMUX DEFINES ***************************/
#define HAPI_IOMUX_SD1_CMD_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_CMD_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_CMD_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | IOMUX_IN_SION | \
                                   (REG_NUM(51)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_CMD_DIR     (0xFF)

#define HAPI_IOMUX_SD1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | \
                                   (REG_NUM(52)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_CLK_DIR     (0xFF)

#define HAPI_IOMUX_SD1_DATA0_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_DATA0_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_DATA0_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(53)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_DATA0_DIR     (0xFF)

#define HAPI_IOMUX_SD1_DATA1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_DATA1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_DATA1_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(54)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_DATA1_DIR     (0xFF)

#define HAPI_IOMUX_SD1_DATA2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_DATA2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_DATA2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(55)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_DATA2_DIR     (0xFF)

#define HAPI_IOMUX_SD1_DATA3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD1_DATA3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD1_DATA3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(56)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD1_DATA3_DIR     (0xFF)

#define HAPI_IOMUX_SD2_DATA0_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD2_DATA0_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD2_DATA0_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                     (REG_NUM(59)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD2_DATA0_DIR     (0xFF)


#define HAPI_IOMUX_SD2_DATA1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD2_DATA1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD2_DATA1_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                     (REG_NUM(60)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD2_DATA1_DIR     (0xFF)

#define HAPI_IOMUX_SD2_DATA2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD2_DATA2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD2_DATA2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                     (REG_NUM(61)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD2_DATA2_DIR     (0xFF)

#define HAPI_IOMUX_SD2_DATA3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_SD2_DATA3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_SD2_DATA3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                     (REG_NUM(62)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_SD2_DATA3_DIR     (0xFF)

#define HAPI_IOMUX_PAD_GPIO1_4_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_PAD_GPIO1_4_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_PAD_GPIO1_4_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(134)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_PAD_GPIO1_4_DIR     (0xFF)

#define HAPI_IOMUX_PAD_GPIO1_5_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_PAD_GPIO1_5_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_PAD_GPIO1_5_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(135)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_PAD_GPIO1_5_DIR     (0xFF)

#define HAPI_IOMUX_PAD_GPIO1_6_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_PAD_GPIO1_6_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_PAD_GPIO1_6_SEL     (HAPI_GPIO_SEL_IOMUX | \
                                 IOMUX_OUT_MUX6 | (REG_NUM(136)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_PAD_GPIO1_6_DIR     (0xFF)

/**************END ESDHC1 IOMUX Defination ***************************************/

/***************ESDHC3 IOMUX Defination   ***************************************/
#define HAPI_IOMUX_NANDF_WE_B_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_WE_B_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_WE_B_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(25)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_WE_B_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_RE_B_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_RE_B_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_RE_B_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(26)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_RE_B_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_ALE_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_ALE_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_ALE_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(27)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_ALE_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_CLE_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CLE_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CLE_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(28)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CLE_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_WP_B_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_WP_B_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_WP_B_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                      (REG_NUM(29)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_WP_B_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_RB_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_RB_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_RB_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                    (REG_NUM(30)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_RB_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_CS0_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS0_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS0_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(31)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS0_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_CS1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS1_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(32)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS1_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_CS2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(33)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS2_DIR     (0xFF)

#define HAPI_IOMUX_NANDF_CS3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_NANDF_CS3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_NANDF_CS3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | IOMUX_IN_SION |\
                                     (REG_NUM(34)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_NANDF_CS3_DIR     (0xFF)

#define HAPI_IOMUX_DI1_PIN12_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_DI1_PIN12_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_DI1_PIN12_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(96)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_DI1_PIN12_DIR     (0xFF)

#define HAPI_IOMUX_DI1_D0_CS_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_DI1_D0_CS_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_DI1_D0_CS_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                     (REG_NUM(98)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_DI1_D0_CS_DIR     (0xFF)

#define HAPI_IOMUX_GPIO1_1_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO1_1_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO1_1_SEL     (HAPI_GPIO_SEL_IOMUX | \
                                 IOMUX_OUT_MUX2 | (REG_NUM(131)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO1_1_DIR     (0xFF)



/****************************************END *************************************/
/*********************************************************************************/
/*eSDHC1,3 EMMC specific Port Configurations*/
/*eSDHC1*/
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_SEL (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                               (REG_NUM(51)) | (REG_OFFSET(0)))
                                               
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_SEL (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 | \
                                                 (REG_NUM(53)) | (REG_OFFSET(0)))
/*eSDHC3*/
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_NANDF_CS1_SD3DAT0_SEL (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                                       (REG_NUM(32)) | (REG_OFFSET(0)))
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_NANDF_CS3_SD3CMD_SEL (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                                        (REG_NUM(34)) | (REG_OFFSET(0)))
                                                        
/*********************************************************************************/


/************************************CSPI 1 defines *********************************/

#define HAPI_GPIO_CSPI1_MOSI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_MOSI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_MOSI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(75)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_MOSI_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_MISO_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_MISO_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_MISO_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(76)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_MISO_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_SS0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_SS0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_SS0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(77)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_SS0_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_SS1_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_SS1_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_SS1_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(78)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_SS1_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_SCLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_SCLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_SCLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(79)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_SCLK_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_SS2_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_SS2_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_SS2_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 |\
                                   (REG_NUM(85)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_SS2_DIR    (HAPI_GPIO_INPUT)

#define HAPI_GPIO_CSPI1_RDY_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_CSPI1_RDY_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_CSPI1_RDY_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX3 |\
                                   (REG_NUM(87)) | (REG_OFFSET(0)))
#define HAPI_GPIO_CSPI1_RDY_DIR    (HAPI_GPIO_INPUT)

/************************************I2C1 defines *********************************/

#define HAPI_IOMUX_I2C1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    IOMUX_IN_SION | (REG_NUM(63)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C1_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                     IOMUX_IN_SION | (REG_NUM(64)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_DAT_DIR     (0xFF)

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
