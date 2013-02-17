#ifndef MMC_H
#define MMC_H
/*==================================================================================================
     Header Name: pu_irom_mmc.h
     General Description: Defines related to MMCSD module. 
====================================================================================================

                                      
                                  Freescale Semiconductor Romania 
                 (c) Copyright Freescale Semiconductor, Inc. 2007, All Rights Reserved
     
Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number    Description of Changes
-------------------------   ------------    ----------  --------------------------------------------
Prabhat Singh                      17-July-2007    Tlbso94839  Added support for High capacity SD   
Surender Kumar              06/07/2007     TLSbo93610   Porting for MArley
Surender Kumar	            09/15/2006     TLSbo79133   Initial Implementation
Surender Kumar              21/Feb/2007    TLSbo90953   Support for High Capacity MMC

-------------------------   ------------    ----------  --------------------------------------------


====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Common.h"
#include "type.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                            MACROS
==================================================================================================*/  
#define MMC_OCR_VALUE 0x40FF8000
#define MMC_OCR_VALUE_BAK 0x80FFC000
#define MMC_OCR_HC_RES 0xC0FF8000
#define MMC_OCR_LC_RES 0x80FF8000
#define MMC_OCR_VALUE_MASK 0x00FF8000
#define BYTE_MODE 0
#define SECT_MODE 1
#define CURR_STATE_SHIFT 9
#define MMC_SPEC_VER 0x003C0000
#define MMC_SPEC_VER_SHIFT 18  
#define MMC_R1_SWITCH_ERROR_MASK 0x80
#define SWITCH_ERROR_SHIFT 7
#define BUS_SIZE_SHIFT 2
#define BUS_WIDTH 0x3b700000
#define MMCSD_ACMD13 MMCSD_CMD13

#define MMC_CSD_READ_BL_LEN_MASK         0x000f0000
#define MMC_CSD_READ_BL_LEN_OFFSET       16

#define MMC_CSD_C_SIZE_PART1_MASK   0xc0000000
#define MMC_CSD_C_SIZE_PART1_OFFSET 30
#define MMC_CSD_C_SIZE_PART1_LEN    2
#define MMC_CSD_C_SIZE_PART2_MASK   0x000003ff
#define MMC_CSD_C_SIZE_PART2_OFFSET 0

#define MMC_CSD_C_SIZE_MULT_MASK    0x00038000
#define MMC_CSD_C_SIZE_MULT_OFFSET  15

/* Macros for MMC voltage validation */
#define MMC_HV_HC_OCR_VALUE         ((UINT32)0x40FF8000) /* High capacity high voltage */
#define MMC_OCR_HC_RESP_VAL         ((UINT32)0x40000000)
#define MMC_OCR_HC_BIT_MASK         ((UINT32)0x60000000) /* Access mode mask in OCR, bits[30:29] reg */

/* Macros for MMC bus width selection */
#define MMC_SWITCH_BUS_SIZE_SHIFT   (8)
#define MMC_SWITCH_BUS_WIDTH        ((UINT32)0x03B70001)
#define MMC_CMD_SWITCH_TIMEOUT      (320)        /* 10ms SWITCH command status timeout */

/* MMC High Speed support */
#define MMC_SWITCH_HS_MODE          ((UINT32)0x03B90101)

/* MMC set boot partition */
#define MMC_SWITCH_SET_BOOT_PART1   ((UINT32)0x01B30100)

/* CSD field macros */
#define MMC_CSD_CSD_STRUT_MASK      ((UINT32)0x00C00000)
#define MMC_CSD_CSD_STRUT_SHIFT     ((UINT32)22)
#define MMC_CSD_SPEC_VERS_MASK      ((UINT32)0x003C0000)
#define MMC_CSD_SPEC_VERS_SHIFT     ((UINT32)18)
#define MMC_CSD_TAAC_MASK           ((UINT32)0x0000FF00)
#define MMC_CSD_TAAC_SHIFT          ((UINT32)8)
#define MMC_CSD_NSAC_MASK           ((UINT32)0x000000FF)
#define MMC_CSD_NSAC_SHIFT          ((UINT32)0)
#define MMC_CSD_R2W_FACTOR_MASK     ((UINT32)0x00000000)
#define MMC_CSD_R2W_FACTOR_SHIFT    ((UINT32)18)

/*
 * MMC status in R1, for native mode (SPI bits are different)
 * Type
 *   e : error bit
 *   s : status bit
 *   r : detected and set for the actual command response
 *   x : detected and set during command execution. the host must poll
 *       the card by sending status command in order to read these bits.
 * Clear condition
 *   a : according to the card state
 *   b : always related to the previous command. Reception of
 *       a valid command will clear it (with a delay of one command)
 *   c : clear by read
 */

#define R1_OUT_OF_RANGE         (((UINT32)1) << 31)   /* er, c */
#define R1_ADDRESS_ERROR        (((UINT32)1) << 30)   /* erx, c */
#define R1_BLOCK_LEN_ERROR      (((UINT32)1) << 29)   /* er, c */
#define R1_ERASE_SEQ_ERROR      (((UINT32)1) << 28)   /* er, c */
#define R1_ERASE_PARAM          (((UINT32)1) << 27)   /* ex, c */
#define R1_WP_VIOLATION         (((UINT32)1) << 26)   /* erx, c */
#define R1_CARD_IS_LOCKED       (((UINT32)1) << 25)   /* sx, a */
#define R1_LOCK_UNLOCK_FAILED   (((UINT32)1) << 24)   /* erx, c */
#define R1_COM_CRC_ERROR        (((UINT32)1) << 23)   /* er, b */
#define R1_ILLEGAL_COMMAND      (((UINT32)1) << 22)   /* er, b */
#define R1_CARD_ECC_FAILED      (((UINT32)1) << 21)   /* ex, c */
#define R1_CC_ERROR             (((UINT32)1) << 20)   /* erx, c */
#define R1_ERROR                (((UINT32)1) << 19)   /* erx, c */
#define R1_UNDERRUN             (((UINT32)1) << 18)   /* ex, c */
#define R1_OVERRUN              (((UINT32)1) << 17)   /* ex, c */
#define R1_CID_CSD_OVERWRITE    (((UINT32)1) << 16)   /* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP        (((UINT32)1) << 15)   /* sx, c */
#define R1_CARD_ECC_DISABLED    (((UINT32)1) << 14)   /* sx, a */
#define R1_ERASE_RESET          (((UINT32)1) << 13)   /* sr, c */
#define R1_STATUS(x)            ((UINT32)(x & 0xFFFFE000))
#define R1_CURRENT_STATE(x)     ((UINT32)((x & 0x00001E00) >> 9)) /* sx, b (4 bits) */
#define R1_READY_FOR_DATA       (((UINT32)1) << 8)    /* sx, a */
#define R1_SWITCH_ERROR         (((UINT32)1) << 7)    /* sx, a */
#define R1_APP_CMD              (((UINT32)1) << 5)    /* sr, c */

/*==================================================================================================
                                          Global Function 
==================================================================================================*/ 
extern UINT32 mmc_init(UINT32);
extern UINT32 mmc_data_read (UINT32 *, UINT32, UINT32, dump_callback callback);
extern UINT32 mmc_data_write (UINT32 *,UINT32 ,UINT32,response_callback callback);
extern UINT32 mmc_data_erase(UINT32,UINT32);
extern UINT32 mmc_voltage_validation (void);
extern UINT32 sd_voltage_validation (void);
extern UINT32 sd_init(UINT32);
extern UINT32 mmc_get_capacity(UINT32 *capacity);
/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/* MMC card spec versions allocated by MMCA */
typedef enum
{
    MMC_SPEC_VER_0_X, /* Version 1.0 - 1.2 */
    MMC_SPEC_VER_1_X, /* Version 1.4 */
    MMC_SPEC_VER_2_X, /* Version 2.0 - 2.2 */
    MMC_SPEC_VER_3_X, /* Version 3.1 - 3.2 */
    MMC_SPEC_VER_4_X  /* Version 4.1 ?4.2 ?4.3 */
} mmc_spec_ver_t;

/* BUS WIDTH supported by MMC cards */
typedef enum
{
    MMC_BUS_WIDTH_1BIT,
    MMC_BUS_WIDTH_4BIT,
    MMC_BUS_WIDTH_8BIT
} mmc_bus_width_t;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* CSD structure for MMC cards */
typedef struct
{
    UINT32 csd_struture;
    UINT32 spec_vers;
    UINT32 taac;
    UINT32 nsac;
    UINT32 r2w_factor;
} mmc_csd_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================================*/
#endif  /* MMC_H */

