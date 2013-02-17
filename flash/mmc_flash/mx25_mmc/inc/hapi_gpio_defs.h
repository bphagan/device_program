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

                        Copyright: 2004-2008 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a
              Freescale Software License Agreement, which has either
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Chandan Singh               15/05/2008      ENGcm05693   Loop back setting for eSDHC CMD and CLK pads as suggested by RTL
Radhish                     27/03/2008      ENGcm05061   eMMC defines Added
Radhish                     08/04/2008      ENGcm05180   MOdified the LPB GPIO's to GPIO_C and GPIO_F
Radhish                     31/03/2008      ENGcm05075   Aligned the uart/i2c defines wrt to v2.4.xls
Radhish                     29/02/2008      ENGcm03622   LPB Support for Senna
Radhish                     29/02/2008      ENGcm03628   Update the iomux define with the latest pin muxing sheet
Jameer Mulani               11/02/2008      ENGcm03304   IOMUX definitions added for CSPI I2c and ESDHC.
Radhish                     5-Feb-2008      ENGcm03236   IOMUX configuration for USB(senna)
Radhish                     31-01-2008      ENGcm03175   Added defines for the UARTs
Prabhat Singh               24/09/2007      engcm00253   IOMUX config for serial and ULPI interface
Sajith P V                  10-Sep-2007     TLSbo96209   Modified Pad Configuration
Prabhat singh               07-Aug-2007     TLSbo94951   Addition of Philips USB ISP1301 PHY support and IOMUX changes for I2C2 module
Deepak Agarwal              13-Aug-2007     TLSbo95314   Iomuxing & clocking change for CSPI.
Deepak Agarwal              07-Aug-2007     TLSbo95313   Iomuxing & clocking change for I2C.
prabhat Singh               17-July-2007    Tlbso94839   Modified Register offset for Ringo IOMUX
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

#define IOMUX_ADDR                      0x43fac000
#define IOMUX_SW_MUX_CTRL_REG_ADDR      (IOMUX_ADDR + 0x0008)
#define IOMUX_SW_PAD_CTRL_REG_ADDR      (IOMUX_ADDR + 0x022c)
#define IOMUX_DAISY_SEL_IN_REG_ADDR     (IOMUX_ADDR + 0x0460)

#define BYTE_MASK   0x000000FF
#define REGOFST_MASK   0x00000003

#define HAPI_GPIO_INPUT         0
#define HAPI_GPIO_OUTPUT        1

/* SW_MUX_CTL field's offsets */
#define IOMUX_OUT_SHIFT         0
#define IOMUX_IN_SHIFT          4
#define IOMUX_DAISY_SHIFT       0 

/* Representation of UIN32 io_select parameter in HAPI_GPIO_Config Function */
#define IOMUX_REG_NUM_SHIFT    12
#define IOMUX_REG_OFFSET_SHIFT 10

#define HAPI_GPIO_SEL_SHIFT     8
#define HAPI_GPIO_SEL_IOMUX  (2 << HAPI_GPIO_SEL_SHIFT) /* Pin routed through IOMUX only */
#define HAPI_GPIO_SEL_GPIO   (1 << HAPI_GPIO_SEL_SHIFT) /* Pin routed through GPIO only */
#define HAPI_GPIO_SEL_GPIO_IOMUX (3 << HAPI_GPIO_SEL_SHIFT) /* Pin routed through both IOMUX and GPIO */

/* ALT Modes constants*/
#define IOMUX_OUT_MUX0 (0 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX1 Output */
#define IOMUX_OUT_MUX1 (1 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX1 Output */
#define IOMUX_OUT_MUX2 (2 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX2 Output */
#define IOMUX_OUT_MUX3 (3 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX3 Output */
#define IOMUX_OUT_MUX4 (4 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX4 Output */
#define IOMUX_OUT_MUX5 (5 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX5 Output */
#define IOMUX_OUT_MUX6 (6 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX6 Output */
#define IOMUX_OUT_MUX7 (7 << IOMUX_OUT_SHIFT) /* IOMUX Selection for MUX6 Output */

/* SION direction */
#define IOMUX_IN_NONE (0 << IOMUX_IN_SHIFT)  /* IOMUX Selection for MUX_MODE func. */
#define IOMUX_IN_SION (1 << IOMUX_IN_SHIFT)  /* IOMUX force input path */

/* used to specify GPIO port */
typedef enum
{
    HAPI_GPIO_PORT_MCU1 = 0,
    HAPI_GPIO_PORT_MCU2 = 1,
    HAPI_GPIO_PORT_MCU3 = 2,
    HAPI_GPIO_NUM_PORTS = 3
} HAPI_GPIO_PORT_T;

/* used to specify GPIO pin number */
typedef enum
{
    HAPI_GPIO_PIN_0 = 0,
    HAPI_GPIO_PIN_1,
    HAPI_GPIO_PIN_2,
    HAPI_GPIO_PIN_3,
    HAPI_GPIO_PIN_4,
    HAPI_GPIO_PIN_5,
    HAPI_GPIO_PIN_6,
    HAPI_GPIO_PIN_7,
    HAPI_GPIO_PIN_8,
    HAPI_GPIO_PIN_9,
    HAPI_GPIO_PIN_10,
    HAPI_GPIO_PIN_11,
    HAPI_GPIO_PIN_12,
    HAPI_GPIO_PIN_13,
    HAPI_GPIO_PIN_14,
    HAPI_GPIO_PIN_15,
    HAPI_GPIO_PIN_16,
    HAPI_GPIO_PIN_17,
    HAPI_GPIO_PIN_18,
    HAPI_GPIO_PIN_19,
    HAPI_GPIO_PIN_20,
    HAPI_GPIO_PIN_21,
    HAPI_GPIO_PIN_22,
    HAPI_GPIO_PIN_23,
    HAPI_GPIO_PIN_24,
    HAPI_GPIO_PIN_25,
    HAPI_GPIO_PIN_26,
    HAPI_GPIO_PIN_27,
    HAPI_GPIO_PIN_28,
    HAPI_GPIO_PIN_29,
    HAPI_GPIO_PIN_30,
    HAPI_GPIO_PIN_31,
    HAPI_GPIO_PIN_MAX
} HAPI_GPIO_PIN_T;


#define REG_NUM(num) (num << IOMUX_REG_NUM_SHIFT)
#define REG_OFFSET(num) (num << IOMUX_REG_OFFSET_SHIFT)

/*USB-ULPI Defines Start*/

/*PWR*/
#define HAPI_IOMUX_USB_PWR_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_PWR_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_PWR_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(123)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_PWR_ULPI_DIR     (0xFF)

#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_PWR 113
#define HAPI_USBOTG_PWR_PAD_VALUE 0x0060

/*OC*/

#define HAPI_IOMUX_USB_OC_ULPI_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_OC_ULPI_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_OC_ULPI_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                       (REG_NUM(124)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_OC_ULPI_DIR     (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_USBOTG_OC  114
#define HAPI_USBOTG_OC_PAD_VALUE 0x00c0

/*DATA0*/
#define HAPI_IOMUX_USB_DAT0_ULPI_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_ULPI_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_ULPI_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                        (REG_NUM(70)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_ULPI_DIR    (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID2_DATA0_REG 59
#define HAPI_USB_CSID2_DATA0_PAD_VALUE   0x00e1

/*DAT1*/

#define HAPI_IOMUX_USB_DAT1_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT1_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT1_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(71)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT1_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID3_DAT1_REG 60
#define HAPI_USB_CSID3_DAT1_PAD_VALUE   0x00e1

/*DAT2*/

#define HAPI_IOMUX_USB_DAT2_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT2_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT2_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(72)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT2_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID4_DAT2_REG 61
#define HAPI_USB_CSID4_DAT2_PAD_VALUE   0x01e1

/*DAT3*/

#define HAPI_IOMUX_USB_DAT3_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT3_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT3_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(73)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT3_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID5_DAT3_REG 62
#define HAPI_USB_CSID5_DAT3_PAD_VALUE   0x00e1

/*DAT4*/

#define HAPI_IOMUX_USB_DAT4_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT4_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT4_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(74)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT4_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID6_DAT4_REG 63
#define HAPI_USB_CSID6_DAT4_PAD_VALUE   0x00e1


/*DAT5*/

#define HAPI_IOMUX_USB_DAT5_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(75)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID7_DAT5_REG 64
#define HAPI_USB_CSID7_DAT5_PAD_VALUE   0x01e1

/*DAT6*/

#define HAPI_IOMUX_USB_DAT6_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(76)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID8_DAT6_REG 65
#define HAPI_USB_CSID8_DAT6_PAD_VALUE   0x00e1

/*DAT7*/

#define HAPI_IOMUX_USB_DAT7_ULPI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT7_ULPI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT7_ULPI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 | \
                                       (REG_NUM(77)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT7_ULPI_DIR   (0xFF)


/*PAD config register*/
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSID9_DAT7_REG 66
#define HAPI_USB_CSID9_DAT7_PAD_VALUE   0x00e1

/*DIR*/
#define HAPI_IOMUX_USB_DIR_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DIR_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DIR_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 |\
                                (REG_NUM(78)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DIR_DIR  (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSI_MCLK_DIR_REG 67
#define HAPI_USB_CSI_MCLK_DIR_PAD_VALUE   0x00e0

/*STP*/
#define HAPI_IOMUX_USB_STP_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_STP_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_STP_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 |\
                                (REG_NUM(79)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_STP_DIR (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSI_VSYNC_STP_REG 68
#define HAPI_USB_CSI_VSYNC_STP_PAD_VALUE   0x0061

/*NXT*/
#define HAPI_IOMUX_USB_NXT_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_NXT_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_NXT_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 |\
                                (REG_NUM(80)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_NXT_DIR  (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSI_HSYNC_NXT_REG 69
#define HAPI_USB_CSI_HVSYNC_NXT_PAD_VALUE   0x00e0

/*CLK*/
#define HAPI_IOMUX_USB_CLK_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_CLK_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_CLK_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 |\
                                (REG_NUM(81)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_CLK_DIR  (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSI_PIX_CLK_REG 70
#define HAPI_USB_CSI_PIX_CLK_PAD_VALUE   0x00e0

/*USB-ULPI Defines End*/

/*UBS LPB realted Defines Start*/
/*GPIO_C*/
#define HAPI_IOMUX_LPB_GPIO1_0_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_LPB_GPIO1_0_PIN     (HAPI_GPIO_PIN_2)
#define HAPI_IOMUX_LPB_GPIO1_0_SEL     (HAPI_GPIO_SEL_GPIO_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(125)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_LPB_GPIO1_0_DIR        (0x00)

/*GPIO_F*/
#define HAPI_IOMUX_LPB_GPIO1_1_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_LPB_GPIO1_1_PIN     (HAPI_GPIO_PIN_5)
#define HAPI_IOMUX_LPB_GPIO1_1_SEL     (HAPI_GPIO_SEL_GPIO_IOMUX | IOMUX_OUT_MUX0 | \
                                     (REG_NUM(128)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_LPB_GPIO1_1_DIR        (0x00)

/*POWER_FAIL*/

#define HAPI_IOMUX_LPB_ATLAS_INT_PORT   (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_LPB_ATLAS_INT_PIN    (HAPI_GPIO_PIN_19)
#define HAPI_IOMUX_LPB_ATLAS_INT_SEL    (HAPI_GPIO_SEL_GPIO | IOMUX_OUT_MUX5 | \
                                     (REG_NUM(133)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_LPB_ATLAS_INT_DIR    (0x00)

#define HAPI_IOMUX_LPB_PWRFAIL_PORT     (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_LPB_PWRFAIL_REG      133
#define HAPI_IOMUX_LPB_PWRFAIL_REG_VAL  0x00000005


/*UBS LPB realted Defines End*/
/******************************SERIAL IOMUX Defines ****************************/
#if 0
#define HAPI_IOMUX_USB_DAT0_TXEN_SERIAL_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT0_TXEN_SERIAL_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT0_TXEN_SERIAL_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                             IOMUX_IN_SION |  (REG_NUM(0x8E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT0_TXEN_SERIAL_DIR    (0xFF)

#define HAPI_IOMUX_USB_DAT1_TXDAT_SERIAL_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT1_TXDAT_SERIAL_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT1_TXDAT_SERIAL_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                             IOMUX_IN_SION |  (REG_NUM(0x8F)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT1_TXDAT_SERIAL_DIR   (0xFF)

#define HAPI_IOMUX_USB_DAT2_TXSE0_SERIAL_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT2_TXSE0_SERIAL_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT2_TXSE0_SERIAL_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 | \
                                            IOMUX_IN_SION |   (REG_NUM(0x90)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT2_TXSE0_SERIAL_DIR   (0xFF)

#define HAPI_IOMUX_USB_DAT3_INT_SERIAL_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT3_INT_SERIAL_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT3_INT_SERIAL_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX4 |\
                                       IOMUX_IN_SION | (REG_NUM(0x7D)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT3_INT_SERIAL_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT4_RXDM_SERIAL_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT4_RXDM_SERIAL_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT4_RXDM_SERIAL_SEL     (HAPI_GPIO_SEL_IOMUX | \
                                       IOMUX_IN_SION | (REG_NUM(0x7E)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT4_RXDM_SERIAL_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT5_RCV_SERIAL_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT5_RCV_SERIAL_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT5_RCV_SERIAL_SEL      (HAPI_GPIO_SEL_IOMUX | \
                                       IOMUX_IN_SION | (REG_NUM(0x80)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT5_RCV_SERIAL_DIR     (0xFF)

#define HAPI_IOMUX_USB_DAT6_SERIAL_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_USB_DAT6_SERIAL_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_USB_DAT6_SERIAL_SEL     (HAPI_GPIO_SEL_IOMUX | \
                                       IOMUX_IN_SION | (REG_NUM(0x81)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_USB_DAT6_SERIAL_DIR     (0xFF)
#endif
/************************************SERIAL  END *************************************/

/************************************CSPI  STARTS *********************************/

/************************************CSPI 1 defines *********************************/
#define HAPI_IOMUX_CSPI1_MOSI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MOSI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MOSI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    (REG_NUM(84)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MOSI_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_MISO_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_MISO_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_MISO_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    (REG_NUM(85)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_MISO_DIR   (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI1_SCLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SCLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SCLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    (REG_NUM(88)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SCLK_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_RDY_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_RDY_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_RDY_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(89)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_RDY_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SS0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(86)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS0_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SS1_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS1_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS1_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                   (REG_NUM(87)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS1_DIR   (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI1_SS2_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS2_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS2_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 |\
                                   (REG_NUM(125)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS2_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI1_SS3_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI1_SS3_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI1_SS3_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 |\
                                   (REG_NUM(132)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI1_SS3_DIR   (HAPI_GPIO_INPUT)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MOSI_REG   (73)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_MISO_REG   (74)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SCLK_REG   (77)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_RDY_REG    (78)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS0_REG    (75)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS1_REG    (76)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS2_REG    (115)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI1_SS3_REG    (120)

#define HAPI_CSPI1_MOSI_PAD_VALUE   0x00A0
#define HAPI_CSPI1_MISO_PAD_VALUE   0x00A0
#define HAPI_CSPI1_SCLK_PAD_VALUE   0x00A0
#define HAPI_CSPI1_RDY_PAD_VALUE    0x00A0
#define HAPI_CSPI1_SS0_PAD_VALUE    0x00E0
#define HAPI_CSPI1_SS1_PAD_VALUE    0x00A0
#define HAPI_CSPI1_SS2_PAD_VALUE    0x00E0
#define HAPI_CSPI1_SS3_PAD_VALUE    0x00A0

#define HAPI_CSPI1_IPP_IND_SS3_B_SELECT_INPUT_REG   (12)
#define HAPI_CSPI1_IPP_IND_SS3_B_SELECT_INPUT_VALUE (1)

/************************************CSPI 2 defines *********************************/

#define HAPI_IOMUX_CSPI2_MOSI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_MOSI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_MOSI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(98)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_MOSI_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI2_MISO_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_MISO_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_MISO_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(99)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_MISO_DIR   (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI2_SCLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_SCLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_SCLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(100)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_SCLK_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI2_RDY_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_RDY_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_RDY_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(101)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_RDY_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI2_SS0_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_SS0_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_SS0_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(102)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_SS0_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI2_SS1_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_SS1_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_SS1_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(103)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_SS1_DIR    (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI2_SS2_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_SS2_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_SS2_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(125)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_SS2_DIR    (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI2_SS3_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI2_SS3_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI2_SS3_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX6 |\
                                    (REG_NUM(96)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI2_SS3_DIR    (HAPI_GPIO_INPUT)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_MOSI_REG   (87)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_MISO_REG   (88)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_SCLK_REG   (89)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_RDY_REG    (90)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_SS0_REG    (91)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_SS1_REG    (92)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_SS2_REG    (115)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI2_SS3_REG    (85)

#define HAPI_CSPI2_MOSI_PAD_VALUE   0x00E0
#define HAPI_CSPI2_MISO_PAD_VALUE   0x01E0
#define HAPI_CSPI2_SCLK_PAD_VALUE   0x00E0
#define HAPI_CSPI2_RDY_PAD_VALUE    0x00E0
#define HAPI_CSPI2_SS0_PAD_VALUE    0x00E0
#define HAPI_CSPI2_SS1_PAD_VALUE    0x00E0
#define HAPI_CSPI2_SS2_PAD_VALUE    0x00E0
#define HAPI_CSPI2_SS3_PAD_VALUE    0x00E0

#define HAPI_CSPI2_IPP_IND_MOSI_SELECT_INPUT_REG        (16)
#define HAPI_CSPI2_IPP_IND_MISO_SELECT_INPUT_REG        (15)
#define HAPI_CSPI2_IPP_IND_SS0_B_SELECT_INPUT_REG       (17)
#define HAPI_CSPI2_IPP_IND_SS1_B_SELECT_INPUT_REG       (18)
#define HAPI_CSPI2_IPP_CSPI_CLK_IN_SELECT_INPUT_REG     (13)
#define HAPI_CSPI2_IPP_IND_DATAREADY_B_SELECT_INPUT_REG (14)


#define HAPI_CSPI2_IPP_IND_MOSI_SELECT_INPUT_VALUE          (1)
#define HAPI_CSPI2_IPP_IND_MISO_SELECT_INPUT_VALUE          (1)
#define HAPI_CSPI2_IPP_CSPI_CLK_IN_SELECT_INPUT_VALUE       (1)
#define HAPI_CSPI2_IPP_IND_DATAREADY_B_SELECT_INPUT_VALUE   (1)
#define HAPI_CSPI2_IPP_IND_SS0_B_SELECT_INPUT_VALUE         (1)
#define HAPI_CSPI2_IPP_IND_SS1_B_SELECT_INPUT_VALUE         (1)


/************************************CSPI 3 defines *********************************/

#define HAPI_IOMUX_CSPI3_MOSI_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_MOSI_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_MOSI_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(70)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_MOSI_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI3_MISO_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_MISO_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_MISO_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(71)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_MISO_DIR   (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI3_SCLK_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_SCLK_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_SCLK_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(72)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_SCLK_DIR   (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI3_RDY_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_RDY_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_RDY_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(73)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_RDY_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI3_SS0_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_SS0_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_SS0_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(74)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_SS0_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI3_SS1_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_SS1_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_SS1_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(75)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_SS1_DIR    (HAPI_GPIO_INPUT)


#define HAPI_IOMUX_CSPI3_SS2_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_SS2_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_SS2_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(76)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_SS2_DIR    (HAPI_GPIO_INPUT)

#define HAPI_IOMUX_CSPI3_SS3_PORT   (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_CSPI3_SS3_PIN    (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_CSPI3_SS3_SEL    (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX7 |\
                                    (REG_NUM(77)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_CSPI3_SS3_DIR    (HAPI_GPIO_INPUT)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_MOSI_REG   (59)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_MISO_REG   (60)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_SCLK_REG   (61)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_RDY_REG    (62)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_SS0_REG    (63)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_SS1_REG    (64)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_SS2_REG    (65)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_CSPI3_SS3_REG    (66)

#define HAPI_CSPI3_MOSI_PAD_VALUE   0x00E0
#define HAPI_CSPI3_MISO_PAD_VALUE   0x00E0
#define HAPI_CSPI3_SCLK_PAD_VALUE   0x01E0
#define HAPI_CSPI3_RDY_PAD_VALUE    0x00E0
#define HAPI_CSPI3_SS0_PAD_VALUE    0x00E0
#define HAPI_CSPI3_SS1_PAD_VALUE    0x01E0
#define HAPI_CSPI3_SS2_PAD_VALUE    0x00E0
#define HAPI_CSPI3_SS3_PAD_VALUE    0x00E0

#define HAPI_CSPI3_IPP_IND_SS3_B_SELECT_INPUT_REG   (26)
#define HAPI_CSPI3_IPP_IND_SS3_B_SELECT_INPUT_VALUE (0)

#define HAPI_CSPI3_IPP_IND_MOSI_SELECT_INPUT_REG        (22)
#define HAPI_CSPI3_IPP_IND_MISO_SELECT_INPUT_REG        (21)
#define HAPI_CSPI3_IPP_IND_SS0_B_SELECT_INPUT_REG       (23)
#define HAPI_CSPI3_IPP_IND_SS1_B_SELECT_INPUT_REG       (24)
#define HAPI_CSPI3_IPP_IND_SS2_B_SELECT_INPUT_REG       (25)
#define HAPI_CSPI3_IPP_CSPI_CLK_IN_SELECT_INPUT_REG     (19)
#define HAPI_CSPI3_IPP_IND_DATAREADY_B_SELECT_INPUT_REG (20)


#define HAPI_CSPI3_IPP_IND_MOSI_SELECT_INPUT_VALUE          (1)
#define HAPI_CSPI3_IPP_IND_MISO_SELECT_INPUT_VALUE          (1)
#define HAPI_CSPI3_IPP_CSPI_CLK_IN_SELECT_INPUT_VALUE       (1)
#define HAPI_CSPI3_IPP_IND_DATAREADY_B_SELECT_INPUT_VALUE   (1)
#define HAPI_CSPI3_IPP_IND_SS0_B_SELECT_INPUT_VALUE         (1)
#define HAPI_CSPI3_IPP_IND_SS1_B_SELECT_INPUT_VALUE         (1)
#define HAPI_CSPI3_IPP_IND_SS2_B_SELECT_INPUT_VALUE         (1)

/************************************CSPI  ENDS *********************************/



 /************************************I2C  STARTS *********************************/

/************************************I2C1 defines *********************************/
#define HAPI_IOMUX_I2C1_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    (REG_NUM(82)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C1_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C1_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C1_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 |\
                                    (REG_NUM(83)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C1_DAT_DIR     (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_CLK_REG (71)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C1_DAT_REG (72)

#define HAPI_I2C1_CLK_PAD_VALUE 0x00A8
#define HAPI_I2C1_DAT_PAD_VALUE 0x00A8

/************************************I2C2 IOMUX *********************************/

#define HAPI_IOMUX_I2C2_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(118)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C2_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C2_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C2_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(119)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C2_DAT_DIR     (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C2_CLK_REG  (107)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C2_DAT_REG  (108)

#define HAPI_I2C2_CLK_PAD_VALUE 0x00E8
#define HAPI_I2C2_DAT_PAD_VALUE 0x00E8

/************************************I2C3 IOMUX *********************************/

#define HAPI_IOMUX_I2C3_CLK_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C3_CLK_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C3_CLK_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(87)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C3_CLK_DIR     (0xFF)

#define HAPI_IOMUX_I2C3_DAT_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_I2C3_DAT_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_I2C3_DAT_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(127)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_I2C3_DAT_DIR     (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C3_CLK_REG  (76)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_I2C3_DAT_REG  (117)

#define HAPI_IOMUXC_I2C3_IPP_SCL_IN_SELECT_INPUT_VALUE_REG (50)
#define HAPI_IOMUXC_I2C3_IPP_SDA_IN_SELECT_INPUT_VALUE_REG (49)


#define HAPI_I2C3_CLK_PAD_VALUE 0x00A8
#define HAPI_I2C3_DAT_PAD_VALUE 0x00A8

#define HAPI_IOMUXC_I2C3_IPP_SCL_IN_SELECT_INPUT_VALUE   0x01
#define HAPI_IOMUXC_I2C3_IPP_SDA_IN_SELECT_INPUT_VALUE   0x02


/************************************I2C  ENDS *********************************/


/******************Esdhc 1 IOMUX config ****************************************/
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_REG    (98)
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_VALUE  (0x0010)

#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_REG    (99)
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_VALUE  (0x0010)

#define HAPI_IOMUX_ESDHC1_DATA4_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_DATA4_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_DATA4_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(97)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_DATA4_DIR   (0xFF)


#define HAPI_IOMUX_ESDHC1_DATA5_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_DATA5_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_DATA5_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(96)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_DATA5_DIR   (0xFF)

#define HAPI_IOMUX_ESDHC1_DATA6_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_DATA6_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_DATA6_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(95)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_DATA6_DIR   (0xFF)

#define HAPI_IOMUX_ESDHC1_DATA7_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC1_DATA7_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC1_DATA7_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                      (REG_NUM(94)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC1_DATA7_DIR   (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_CMD_REG   (87)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_CLK_REG   (88)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA0_REG (89)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA1_REG (90)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA2_REG (91)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA3_REG (92)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA4_REG (86)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA5_REG (85)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA6_REG (84)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC1_DATA7_REG (83)

#define HAPI_ESDHC1_CMD_PAD_VALUE   0x00D1
#define HAPI_ESDHC1_CLK_PAD_VALUE   0x00D1
#define HAPI_ESDHC1_DATA0_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA1_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA2_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA3_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA4_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA5_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA6_PAD_VALUE 0x00D1
#define HAPI_ESDHC1_DATA7_PAD_VALUE 0x00D0


#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_REG (132)
#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_REG (134)


#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_SDHC1_VALUE 0x02
#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_UART_VALUE  0x02

#define HAPI_IOMUXC_ESDHC1_IPP_DAT4_IN_SELECT_INPUT_REG (27)
#define HAPI_IOMUXC_ESDHC1_IPP_DAT5_IN_SELECT_INPUT_REG (28)
#define HAPI_IOMUXC_ESDHC1_IPP_DAT6_IN_SELECT_INPUT_REG (29)
#define HAPI_IOMUXC_ESDHC1_IPP_DAT7_IN_SELECT_INPUT_REG (30)

#define HAPI_ESDHC1_IPP_DAT4_IN_SELECT_INPUT_VALUE (0x1)
#define HAPI_ESDHC1_IPP_DAT5_IN_SELECT_INPUT_VALUE (0x1)
#define HAPI_ESDHC1_IPP_DAT6_IN_SELECT_INPUT_VALUE (0x1)
#define HAPI_ESDHC1_IPP_DAT7_IN_SELECT_INPUT_VALUE (0x1)

/****************************************END *************************************/

/******************Esdhc 2 IOMUX config ****************************************/
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDC_REG   (112)  /* eSDHC-2 CMD */
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDC_VALUE (0x0011)

#define HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDIO_REG   (113)  /* eDSHC-2 CLK */
#define HAPI_IOMUXC_SW_MUX_CTL_PAD_FEC_MDIO_VALUE (0x0011)

#define HAPI_IOMUX_ESDHC2_DATA0_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA0_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA0_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(114)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA0_DIR  (0xFF)


#define HAPI_IOMUX_ESDHC2_DATA1_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA1_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA1_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                     (REG_NUM(115)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA1_DIR  (0xFF)

#define HAPI_IOMUX_ESDHC2_DATA2_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA2_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA2_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                        (REG_NUM(116)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA2_DIR     (0xFF)

#define HAPI_IOMUX_ESDHC2_DATA3_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA3_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA3_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                        (REG_NUM(117)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA3_DIR     (0xFF)


#define HAPI_IOMUX_ESDHC2_DATA4_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA4_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA4_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(118)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA4_DIR     (0xFF)


#define HAPI_IOMUX_ESDHC2_DATA5_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA5_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA5_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(119)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA5_DIR     (0xFF)

#define HAPI_IOMUX_ESDHC2_DATA6_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA6_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA6_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(120)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA6_DIR     (0xFF)

#define HAPI_IOMUX_ESDHC2_DATA7_PORT    (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_ESDHC2_DATA7_PIN     (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_ESDHC2_DATA7_SEL     (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX2 | \
                                        (REG_NUM(121)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_ESDHC2_DATA7_DIR     (0xFF)


#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_CMD_REG   (101)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_CLK_REG   (102)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA0_REG (103)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA1_REG (104)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA2_REG (105)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA3_REG (106)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA4_REG (107)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA5_REG (108)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA6_REG (109)
#define HAPI_IOMUXC_SW_PAD_CTL_PAD_ESDHC2_DATA7_REG (110)

#define HAPI_ESDHC2_CMD_PAD_VALUE   0x00D1
#define HAPI_ESDHC2_CLK_PAD_VALUE   0x00D1
#define HAPI_ESDHC2_DATA0_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA1_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA2_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA3_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA4_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA5_PAD_VALUE 0x00D1
#define HAPI_ESDHC2_DATA6_PAD_VALUE 0x01D1
#define HAPI_ESDHC2_DATA7_PAD_VALUE 0x00D3


#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_REG (124)


#define HAPI_IOMUXC_SW_PAD_CTL_GRP_DSE_FEC_VALUE  0x02


/*software select input control register  */
#define HAPI_IOMUXC_ESDHC2_IPP_CMD_IN_SELECT_INPUT_REG      (32)
#define HAPI_IOMUXC_ESDHC2_IPP_CLK_IN_SELECT_INPUT_REG      (31)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT0_IN_SELECT_INPUT_REG     (33)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT1_IN_SELECT_INPUT_REG     (34)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT2_IN_SELECT_INPUT_REG     (35)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT3_IN_SELECT_INPUT_REG     (36)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT4_IN_SELECT_INPUT_REG     (37)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT5_IN_SELECT_INPUT_REG     (38)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT6_IN_SELECT_INPUT_REG     (39)
#define HAPI_IOMUXC_ESDHC2_IPP_DAT7_IN_SELECT_INPUT_REG     (40)


#define HAPI_ESDHC2_IPP_CMD_IN_SELECT_INPUT_VAL         0x02
#define HAPI_ESDHC2_IPP_CLK_IN_SELECT_INPUT_VAL         0x02
#define HAPI_ESDHC2_IPP_DAT0_IN_SELECT_INPUT_VAL        0x02
#define HAPI_ESDHC2_IPP_DAT1_IN_SELECT_INPUT_VAL        0x02
#define HAPI_ESDHC2_IPP_DAT2_IN_SELECT_INPUT_VAL        0x02
#define HAPI_ESDHC2_IPP_DAT3_IN_SELECT_INPUT_VAL        0x02
#define HAPI_ESDHC2_IPP_DAT4_IN_SELECT_INPUT_VAL        0x01
#define HAPI_ESDHC2_IPP_DAT5_IN_SELECT_INPUT_VAL        0x01
#define HAPI_ESDHC2_IPP_DAT6_IN_SELECT_INPUT_VAL        0x01
#define HAPI_ESDHC2_IPP_DAT7_IN_SELECT_INPUT_VAL        0x01

/****************************************eMMC start *************************************/
/*cmd line configured for gpio*/
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(98)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC1_CMD_DIR   (0xFF)


#define HAPI_GPIO_ESDHC1_CMD_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC1_CMD_PIN   (HAPI_GPIO_PIN_23)
#define HAPI_GPIO_ESDHC1_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC1_CMD_DIR   (0x1)

/*fec line confgured for gpio*/
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(112)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC2_CMD_DIR   (0xFF)


#define HAPI_GPIO_ESDHC2_CMD_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC2_CMD_PIN   (HAPI_GPIO_PIN_5)
#define HAPI_GPIO_ESDHC2_CMD_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC2_CMD_DIR   (0x1)

/* FEC line confgured as cmd line*/
#define HAPI_GPIO_IOMUX_ESDHC2_CMD_PORT     (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_IOMUX_ESDHC2_CMD_PIN      (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_IOMUX_ESDHC2_CMD_SEL      (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 | \
                                            (REG_NUM(112)) |(REG_OFFSET(0)))
#define HAPI_GPIO_IOMUX_ESDHC2_CMD_DIR      (0xFF)


/*DAT0 line configuration */
/*DAT0 line configured for gpio*/
#define HAPI_IOMUX_GPIO_ESDHC1_DAT0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC1_DAT0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC1_DAT0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(100)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC1_DAT0_DIR   (0xFF)


#define HAPI_GPIO_ESDHC1_DAT0_PORT  (HAPI_GPIO_PORT_MCU2)
#define HAPI_GPIO_ESDHC1_DAT0_PIN   (HAPI_GPIO_PIN_25)
#define HAPI_GPIO_ESDHC1_DAT0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC1_DAT0_DIR   (0x0)

#define HAPI_GPIO_IOMUX_ESDHC1_DAT0_PORT     (HAPI_GPIO_PORT_MCU1)
#define HAPI_GPIO_IOMUX_ESDHC1_DAT0_PIN      (HAPI_GPIO_PIN_MAX)
#define HAPI_GPIO_IOMUX_ESDHC1_DAT0_SEL      (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX0 | \
                                            (REG_NUM(100)) |(REG_OFFSET(0)))
#define HAPI_GPIO_IOMUX_ESDHC1_DAT0_DIR      (0xFF)

#define HAPI_IOMUX_GPIO_ESDHC2_DAT0_PORT  (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_GPIO_ESDHC2_DAT0_PIN   (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_GPIO_ESDHC2_DAT0_SEL   (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX5 | \
                                         (REG_NUM(114)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_GPIO_ESDHC2_DAT0_DIR   (0xFF)


#define HAPI_GPIO_ESDHC2_DAT0_PORT  (HAPI_GPIO_PORT_MCU3)
#define HAPI_GPIO_ESDHC2_DAT0_PIN   (HAPI_GPIO_PIN_7)
#define HAPI_GPIO_ESDHC2_DAT0_SEL   (HAPI_GPIO_SEL_GPIO)
#define HAPI_GPIO_ESDHC2_DAT0_DIR   (0x00)


/****************************************END *************************************/

/* Pad strength defines */
#define LOW_DRIVE           0x0
#define HIGH_DRIVE          0x1
#define MAX_DRIVE_1         0x2
#define MAX_DRIVE_2         0x3
#define PAD_STRENGTH_SHIFT  0x1

#define SLEW_SLOW   0x0
#define SLEW_FAST   0x1

/* PU/PD strength defines */
#define PD100KOHM       0x0
#define PU47KOHM        0x1
#define PU100KOHM       0x2
#define PU22KOHM        0x3

#define PUPD_STRENGTH_SHIFT 0x5
#define PUPD_ENABLE         0x80

/*UART defines start*/
/* UART1 Pad Config */
#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART1_RXD_REG (79)
#define HAPI_UART1_RXD_PAD_VALUE (0x00A0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART1_TXD_REG (80)
#define HAPI_UART1_TXD_PAD_VALUE (0x0020)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART1_RTS_REG (81)
#define HAPI_UART1_RTS_PAD_VALUE (0x00E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART1_CTS_REG (82)
#define HAPI_UART1_CTS_PAD_VALUE (0x0060)


 /* UART2 Pad Config */
#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART2_RXD_REG (83)
#define HAPI_UART2_RXD_PAD_VALUE (0x00E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART2_TXD_REG (84)
#define HAPI_UART2_TXD_PAD_VALUE (0x0060)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART2_RTS_REG (85)
#define HAPI_UART2_RTS_PAD_VALUE (0x00E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART2_CTS_REG (86)
#define HAPI_UART2_CTS_PAD_VALUE (0x0060)

/* UART3 Pad Config */
#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART3_RXD_REG (93)
#define HAPI_UART3_RXD_PAD_VALUE (0x00A0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART3_TXD_REG (94)
#define HAPI_UART3_TXD_PAD_VALUE (0x0020)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART3_RTS_REG (95)
#define HAPI_UART3_RTS_PAD_VALUE (0x00E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART3_CTS_REG (96)
#define HAPI_UART3_CTS_PAD_VALUE (0x0060)

/* UART4 Pad Config */
#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART4_RXD_REG (97)
#define HAPI_UART4_RXD_PAD_VALUE (0x00A0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART4_TXD_REG (98)
#define HAPI_UART4_TXD_PAD_VALUE (0x0020)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART4_RTS_REG (99)
#define HAPI_UART4_RTS_PAD_VALUE (0x00A0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART4_CTS_REG (100)
#define HAPI_UART4_CTS_PAD_VALUE (0x0020)

/* UART5 Pad Config */
#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART5_RXD_REG (59)
#define HAPI_UART5_RXD_PAD_VALUE (0x00E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART5_TXD_REG (60)
#define HAPI_UART5_TXD_PAD_VALUE (0x0060)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART5_RTS_REG (61)
#define HAPI_UART5_RTS_PAD_VALUE (0x01E0)

#define HAPI_IOMUX_SW_PAD_CTL_PAD_UART5_CTS_REG (62)
#define HAPI_UART5_CTS_PAD_VALUE (0x0060)

/*UART3 Mux defines */
#define HAPI_IOMUX_UART3_RXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_RXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_RXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(104)) |(REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_RXD_DIR  (0xFF)

#define HAPI_IOMUX_UART3_RXD_MUX_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART3_RXD_IN_REG_SEL 66
#define HAPI_IOMUX_UART_IN_REG_VAL 0x1



#define HAPI_IOMUX_UART3_TXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_TXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_TXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                    (REG_NUM(105)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_TXD_DIR  (0xFF)

#define HAPI_IOMUX_UART3_CTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_CTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_CTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(107)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_CTS_DIR  (0xFF)

#define HAPI_IOMUX_UART3_RTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART3_RTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART3_RTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(106)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART3_RTS_DIR  (0xFF)

#define HAPI_IOMUX_UART3_RTS_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART3_RTS_IN_REG_SEL 65

/*UART4 Mux defines */

#define HAPI_IOMUX_UART4_RXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART4_RXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART4_RXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(108)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART4_RXD_DIR  (0xFF)

#define HAPI_IOMUX_UART4_RXD_MUX_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART4_RXD_MUX_IN_REG_SEL 68


#define HAPI_IOMUX_UART4_TXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART4_TXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART4_TXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(109)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART4_TXD_DIR  (0xFF)

#define HAPI_IOMUX_UART4_CTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART4_CTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART4_CTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(111)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART4_CTS_DIR  (0xFF)

#define HAPI_IOMUX_UART4_RTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART4_RTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART4_RTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(110)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART4_RTS_DIR  (0xFF)

#define HAPI_IOMUX_UART4_RTS_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART4_RTS_IN_REG_SEL 67

/*UART5 Mux defines */

#define HAPI_IOMUX_UART5_RXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART5_RXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART5_RXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                   (REG_NUM(70)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART5_RXD_DIR  (0xFF)

#define HAPI_IOMUX_UART5_RXD_MUX_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART5_RXD_MUX_IN_REG_SEL 70

#define HAPI_IOMUX_UART5_TXD_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART5_TXD_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART5_TXD_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                  (REG_NUM(71)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART5_TXD_DIR  (0xFF)

#define HAPI_IOMUX_UART5_CTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART5_CTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART5_CTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                  (REG_NUM(73)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART5_CTS_DIR  (0xFF)

#define HAPI_IOMUX_UART5_RTS_PORT (HAPI_GPIO_PORT_MCU1)
#define HAPI_IOMUX_UART5_RTS_PIN  (HAPI_GPIO_PIN_MAX)
#define HAPI_IOMUX_UART5_RTS_SEL  (HAPI_GPIO_SEL_IOMUX | IOMUX_OUT_MUX1 |\
                                  (REG_NUM(72)) | (REG_OFFSET(0)))
#define HAPI_IOMUX_UART5_RTS_DIR  (0xFF)


#define HAPI_IOMUX_UART5_RTS_IN_PORT (HAPI_GPIO_PORT_MCU3)
#define HAPI_IOMUX_UART5_RTS_IN_REG_SEL 69

/*UART defines End*/
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
