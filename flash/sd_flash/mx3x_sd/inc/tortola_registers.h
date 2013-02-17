#ifndef TORTOLA_REGISTERS_H
#define TORTOLA_REGISTERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                                                               
     Header Name: tortola_registers.h

     General Description: Tortola register & external memory declarations

====================================================================================================

                              Motorola Confidential Proprietary
                              Global Software Group - Australia
                  Copyright (c) 2004 Motorola Inc. All Rights Reserved

                         Copyright: 2006 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a
              Freescale Software License Agreement, which has either
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Stephane Danielian          11-Feb-2004     N/A          INITIAL version. Copied from Tahiti.
Stephane Danielian          05-Mar-2004     AUSfe14884   Updated with new IIM fuses definitions.
Rodney Lorrimar             23-Dec-2004     DSPhl25321   Added mask value for IIM BOOT_INT fuse.
Suresh Kumar                09-Oct-2006     TLSbo79133   Added Boot support from MMC/SD.
Mahima Verma                01-Dec-2006     TLSbo52480   Multiple nand flash
Suresh Kumar                22-Dec-2006     TLSbo86816   Increase boot buffer size to 4k bytes

====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

//#include "su_basictypes.h"     /* for basic ATSO data types */
#include "pu_irom_sdhc_ipp.h"
#include "type.h"
#include "Common.h"
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* BOOT buffer size (4k bytes) */
#define BOOT_BUFFER_SIZE (0x1000)

/* NAND Flash controller spare buffer size (bytes) */
#define NANDFC_SPARE_SIZE (0x40)

/* NAND Flash controller reserved area size (bytes) */
#define NANDFC_RESERVED_SIZE (0x5C0)

/* NAND Flash Config 2 register INT bit mask */
#define NANDFC_CFG_2_INT_MASK ((UINT16)0x00008000)

/* GPIO PSR bit 10 (NFWE_B for MDOC READY) bit mask */
#define GPIO_PSR_10_MASK ((UINT32)0x00000400)
    
/* RCSR BOOT pins Mask */
#define RCSR_BOOT_MASK ((UINT32)0x0F800000)

/* RCSR BOOT Mask Shift */
#define RCSR_BOOT_SHIFT ((UINT32)23)

/* CGR0 RNGA enable mask */
#define CGR0_RNGA_EN_MASK ((UINT32)3 << 20)

/* SCC disable fuse mask */
#define SCC_DIS_MASK    ((UINT32)0x00000008)

/* Customer/Product code fuses mask */
#define HAB_CUS_MASK   ((UINT32)0x00000070)

/* Customer/Product code fuses offset in bits */
#define HAB_CUS_SHIFT ((UINT32)4)

/* Super root key selection fuses mask */
#define HAB_SRS_MASK   ((UINT32)0x0000001F)

/* TYPE fuses mask */
#define HAB_TYPE_MASK   ((UINT32)0x00000007)

/* BOOT_INT is bit[4] in the IIM HWV1 */
#define BOOT_INT_MASK ((UINT32)0x00000010)

/*==================================================================================================
                                            MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/* NANDFC register set */
typedef struct {
    UINT8  buffer[BOOT_BUFFER_SIZE / 2];  /* Main buffers (16-bit access) */
    UINT8  spare[NANDFC_SPARE_SIZE];    /* Spare buffers(16-bit access) */
    const UINT8  reserved1[NANDFC_RESERVED_SIZE];
    const UINT16 nfc_bufsize;           /* Internal SRAM size */
    UINT16 reserved2;                    /* Reserved */
    UINT16 ram_buffer_address;          /* Transfer buffer number */
    UINT16 nand_flash_add;              /* NAND flash address */
    UINT16 nand_flash_cmd;              /* NAND flash command */
    UINT16 nfc_configuration;           /* Internal buffer control */
    const UINT16 ecc_status_result;     /* Controller status */
    const UINT16 ecc_rslt_main_area;    /* ECC error position */
    const UINT16 ecc_rslt_spare_area;   /* ECC error position */
    UINT16 nf_wr_prot;                  /* Write protection command */
    UINT16 unlock_start_blk_add;        /* Write protection unlock start */
    UINT16 unlock_end_blk_add;          /* Write protection unlock end */
    const UINT16 nand_flash_wr_pr_st;   /* Write protection status */
    UINT16 nand_flash_config1;          /* Operation configuration */
    UINT16 nand_flash_config2;          /* Operation configuration */
} NANDFC_REGS;


/* CCM register set */
typedef struct {
    UINT32 ccmr;                      /* Control register */
    UINT32 pdr0;                      /* Post divider register 0 */
    UINT32 pdr1;                      /* Post divider register 1 */
    UINT32 rcsr;                      /* Reset Control and Source register */
    UINT32 mpctl;                     /* MCU PLL Control register */
    UINT32 upctl;                     /* USB PLL Control register */
    UINT32 srpctl;                    /* Serial PLL Control register */
    UINT32 cosr;                      /* Clock Out Source register */
    UINT32 cgr0;                      /* Clock Gating Register 0 */
    /* Remaining registers not required */
} CCM_REGS;
    
/* IC Identification module Fuse bank 0 register set */
typedef struct {
    const UINT32 fbac0;           /* FB0 access control register */
    const UINT32 jac;             /* JTAG Access Control register */
    const UINT32 hw1;             /* HW-visible register 1*/
    const UINT32 hw2;             /* HW-visible register 2*/
    const UINT32 hab0;            /* HAB0 register */
    const UINT32 hab1;            /* HAB1 register */
    const UINT32 prev;            /* Product Revision register */
    const UINT32 srev;            /* Silicon Revision register */
    const UINT32 uid[8];          /* Unique ID register */
     /* Remaining registers not required */
} FB0_REGS;

/* GPIO register set */
typedef struct {
    UINT32 dr;                          /* GPIO Data register */
    UINT32 gdir;                        /* GPIO Direction register */
    UINT32 psr;                         /* GPIO Pad Status register */
   
    /* Remaining registers not required */
} GPIO_REGS;  


/* GPT Register set */ 
 typedef struct
   {
      UINT32 gptcr;
      UINT32 gptpr;
      UINT32 gptsr;
      UINT32 gptir;
      UINT32 gptocr1;
      UINT32 gptocr2;
      UINT32 gptocr3;
      UINT32 gpticr1;
      UINT32 gpticr2;
      UINT32 gptcnt;  
	

   }GPT_PERIPH_T;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/* GPT Register set */
extern volatile GPT_PERIPH_T gpt1;

/* NANDFC register set */
extern volatile NANDFC_REGS nandfc;

/* ESDCTL register set */
extern volatile UINT32 esdctl;

/* WEIM register set */
extern volatile UINT32 weim;

/* CCM register set */
extern volatile CCM_REGS ccm;

/* FB0 register set */
extern volatile FB0_REGS fb0;
    
/* GPIO register set */
extern volatile GPIO_REGS gpio1;
    
/* Base of MDOC Flash */
extern UINT8 mdoc_flash[];         

/* Base of conventional flash */
extern UINT8 conventional_flash[];

/* Base of SDRAM 0 */
extern UINT8 sdram0[];

/* Base of SDRAM 1 */
extern UINT8 sdram1[];

/* Base of CS1 */
extern UINT8 cs1[];

/* Base of CS2 */
extern UINT8 cs2[];

/* Base of CS3 */
extern UINT8 cs3[];

/* Base of CS4 */
extern UINT8 cs4[];

/* Base of CS5 */
extern UINT8 cs5[];    

/* SDHC register set */
extern volatile sdhc_t sdhc1;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* TORTOLA_REGISTERS_H */
