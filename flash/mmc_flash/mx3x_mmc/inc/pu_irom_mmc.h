#ifndef MMC_H
#define MMC_H
/*==================================================================================================
     Header Name: pu_irom_mmc.h
     General Description: Defines related to MMCSD module. 
====================================================================================================
                                      
                                  Freescale Semiconductor Romania 
                 (c) Copyright Freescale Semiconductor, Inc. 2005, All Rights Reserved
     
Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number    Description of Changes
-------------------------   ------------    ----------  --------------------------------------------
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
#define MMC_OCR_HC_RES 0xC0FF8000
#define MMC_OCR_LC_RES 0x80FF8000
#define MMC_OCR_VALUE_MASK 0x00FF8000
#define BYTE_MODE 0
#define SECT_MODE 1
#define CARD_BUSY_BIT 0x80000000
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

/*==================================================================================================
                                          Global Function 
==================================================================================================*/ 
extern UINT32 mmc_init(UINT32);
extern UINT32 mmc_data_read (UINT32 *,UINT32 ,UINT32,dump_callback callback);
extern UINT32 mmc_data_write (UINT32 *,UINT32 ,UINT32,response_callback callback);
extern UINT32 mmc_data_erase(UINT32,UINT32);
extern UINT32 mmc_voltage_validation (void);
extern UINT32 sd_voltage_validation (void);
extern UINT32 sd_init(UINT32);
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

typedef struct 
{
	UINT32 csd0;
	UINT32 csd1;
	UINT32 csd2;
	UINT32 csd3;
}card_specific_data;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================================*/
#endif  /* MMC_H */

