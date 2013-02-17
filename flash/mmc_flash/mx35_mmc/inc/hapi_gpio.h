#ifndef HAPI_GPIO_INCLUDE /* To prevent inadvertently including a header twice */
#define HAPI_GPIO_INCLUDE

#ifdef __cplusplus  /* allow #include in a C++ file */
extern "C" {
#endif

/*==================================================================================================

    Header Name: hapi_gpio.h

    General Description:
       Contains function prototypes for IO_GPIO_* functions.

====================================================================================================
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
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Siva Pothireddy             22-Sep-2008     ENGcm07495  Unused functions removal from ROM code
Surender Kumar              07-Jun-07       TLSbo93610   IOMUX for eSDHC
Suresh Kumar                07-May-30       TLSbo93641   Port IOMUX and GPIO for Marley
Lucky Sharma                06-Aug-23       TLSBo76313   Get rid of chipset conditional compilation
Bharat Bhushan              06-06-12        TLSbo68884   Bharat Bhushan Update fot Islay

   04-05-31   rziolkowski CR - LIBee13501
              Updates for SCM-A11
   04-05-10   jvoss       CR - LIBee01069
              Argon+/SCM-A11 gpio support

   02-11-26   Nimrod Klang  CR - LIBbb57777
              Add prototype of hapi_gpio_init_dsp_trace_support()

   00-02-15   sgreasby    CR - CSGce48793
              Move GSM GPIO Code to P2K Vobs
              - Moved file to P2K vobs
              - Renamed all global variables, contants, funtions, etc. to
                reflect their new locations.

   99-10-18   sgreasby    CR - CSGce27318
              Patriot GPIO Changes
              - File Creation

====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

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

/*==================================================================================================
                                            MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

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

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus /* allow #include in a C++ file */
}
#endif
#endif /* end of - prevent inadvertently including a header file twice */

