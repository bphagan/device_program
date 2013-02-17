/*==================================================================================================

    Module Name:  bl_transreceiver.c

    General Description: This file contains the Transreceiver initalisation.

====================================================================================================
    Copyright (C) 2006,2007,2008 Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Siva Pothireddy              07-Jul-2008    ENGcm06427   STP pull high routine was removed and the OTG_EXT_CLK_ENB bit was set.
Siva Pothireddy               07-May-2008  ENGcm05563    STP pull high routine was added.
Siva Pothireddy               06/05/2008     ENGcm05551   Setting of PFSC,Mode select has to be done
                                                                                         before R/S bit getting set
Suresh Kumar                 10-Sep-2007    ENGcm00389   UART/USB polling design change.
Mahima Verma                 20-Aug-2007    TLSbo95872   Iomux changes.
Mahima Verma                 11-Jun-2007    TLSbo93857   Ported to Marley.
Suresh Kumar                 18-Oct-2006    TLSbo80774   Porting to Zappa.
Bharat Bhushan               24-Aug-2006    TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               20/07/2006     TLSbo73521   New Boot ROM Design Support for USB/UART
                                                         Serial Downloader
Bharat Bhushan               28/06/2006     TLSbo72164   Moana 6-Wrie Serial Interface Support.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
-------------------------   ------------    ----------   -------------------------------------------
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#include "suapi.h"
#include "bl_transreceiver.h"
#include "usb_tl_al_extern.h"
#include "usb_ipl_al_extern.h"
#include "usb_hwinterface_layer.h"
#include "usb_transaction_layer.h"
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/
UINT8 __attribute__((section("usb_buffer_no_init"))) usb_buffer[BUFFER_SIZE];
/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/
/*=================================================================================================
                                 GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/

void usb_otg_interface_init(void);
void usb_utmi_interface_enable(void);

/*==================================================================================================

                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                     GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================

FUNCTION: usb_init

DESCRIPTION: Initialize the usb interface and usb OTG

ARGUMENTS PASSED:
   None

RETURN VALUE:
   None

PRE-CONDITIONS:
   USB path is being followed.

POST-CONDITIONS:
   None

IMPORTANT NOTES:

==================================================================================================*/
#define hapi_clock_dpll3_addr               (0xe3f88000)
#define hapi_clock_dpll3_reg_dp_ctl         (hapi_clock_dpll3_addr)
#define hapi_clock_dpll3_reg_dp_op          (hapi_clock_dpll3_addr + 2 * 4)
#define hapi_clock_dpll3_reg_dp_mfd         (hapi_clock_dpll3_addr + 3 * 4)
#define hapi_clock_dpll3_reg_dp_mfn         (hapi_clock_dpll3_addr + 4 * 4)

#define hapi_clock_reg_addr                 (0xe3f8c000)
#define hapi_clock_reg_csr                  (hapi_clock_reg_addr + 2 * 4)
#define hapi_clock_reg_cscmr1               (hapi_clock_reg_addr + 13 * 4)

#define DP_CTL_LRF_MASK                     (0x00000001)
#define DP_CTL_PLM_MASK                     (0x00000004)
#define DP_CTL_RCP_MASK                     (0x00000008)
#define DP_CTL_RST_MASK                     (0x00000010)
#define DP_CTL_UPEN_MASK                    (0x00000020)
#define DP_CTL_REF_CLK_SEL_MASK             (0x00000300)
#define DP_CTL_REF_CLK_SEL_SHIFT            (8)

#define DP_USB_OP_PDF_MASK                  (0x0000000F)
#define DP_USB_OP_PDF_VAL                   (0x00000003)

#define DP_USB_MFD_VAL                      (0x0098967F)   /* 999999 */
#define DP_USB_OP_MFI_MASK                  (0x000000F0)
#define DP_USB_OP_MFI_VAL                   (0x00000060)   /* 6 -defined for dpll3 to gen. 216MHz */

#define DP_USB_MFN_VAL                      (0x005A4D10)   /* 5917968 -defined for dpll3 to gen. 216MHz */


void usb_init(void)
{
    /* initialise the interface ( UTMI) */
    usb_otg_interface_init();
}

/*==================================================================================================

FUNCTION: usb_otg_interface_init

DESCRIPTION: Initialize the transreceiver .

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
void usb_otg_interface_init(void)
{
    usb_plat_config_data_t config_data_ptr;

    /* IP Layer Initialisation */
    config_data_ptr.buffer_address = (UINT32)usb_buffer;
    config_data_ptr.buffer_size  = BUFFER_SIZE;

    ipl_init(&config_data_ptr);
    /* Enable the UTMI interface */
    usb_utmi_interface_enable();
}

/*==================================================================================================

FUNCTION: usb_utmi_interface_enable

DESCRIPTION: Initialize and enable the utmi interface of communication.

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
void usb_utmi_interface_enable(void)
{
    U32 temp;

    /* set it to be utmi interface */
    temp  = *(VP_U32)USB_OTG_PORTSC1;
    temp &= ~USB_OTG_TRANS_MASK;
    temp |= USB_OTG_TRANS_UTMI;
    temp &= ~USB_OTG_FS_ONLY;
    temp |= USB_OTG_TRANS_WIDTH;

    *(VP_U32)USB_OTG_PORTSC1 = temp;
}
