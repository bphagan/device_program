#ifndef SD_H
#define SD_H
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
Terry Lv (r65388)	        13/05/2008                  Initial Implementation

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
#define SD_OCR_VALUE_HV_LC     ((UINT32)0x00ff8000)
#define SD_OCR_VALUE_HV_HC     ((UINT32)0x40ff8000)
#define SD_OCR_VALUE_LV_HC     ((UINT32)0x40000080)
#define SD_OCR_HC_RES          ((UINT32)0x40000000)
#define SD_IF_HV_COND_ARG      ((UINT32)0x000001AA)
#define SD_IF_LV_COND_ARG      ((UINT32)0x000002AA)

#define SD_OCR_VALUE_COUNT     (3)
#define SD_IF_CMD_ARG_COUNT    (2)

#define SD_CSD_CSD_STRUCTURE_MASK       ((UINT32)0xc0000000)
#define SD_CSD_CSD_STRUCTURE_OFFSET     ((UINT32)30)

#define SD_CSD_READ_BL_LEN_MASK         ((UINT32)0x000f0000)
#define SD_CSD_READ_BL_LEN_OFFSET       ((UINT32)16)

#define SD_CSD_VER1_C_SIZE_PART1_MASK   ((UINT32)0xc0000000)
#define SD_CSD_VER1_C_SIZE_PART1_OFFSET ((UINT32)30)
#define SD_CSD_VER1_C_SIZE_PART1_LEN    ((UINT32)2)
#define SD_CSD_VER1_C_SIZE_PART2_MASK   ((UINT32)0x000003ff)
#define SD_CSD_VER1_C_SIZE_PART2_OFFSET ((UINT32)0)

#define SD_CSD_C_SIZE_MULT_MASK    ((UINT32)0x00038000)
#define SD_CSD_C_SIZE_MULT_OFFSET  ((UINT32)15)

#define SD_CSD_VER2_C_SIZE_PART1_MASK   ((UINT32)0xffff0000)
#define SD_CSD_VER2_C_SIZE_PART1_OFFSET ((UINT32)16)
#define SD_CSD_VER2_C_SIZE_PART1_LEN    ((UINT32)16)
#define SD_CSD_VER2_C_SIZE_PART2_MASK   ((UINT32)0x0000003f)
#define SD_CSD_VER2_C_SIZE_PART2_OFFSET ((UINT32)0)

/*==================================================================================================
                                          Global Function 
==================================================================================================*/ 
extern UINT32 sd_init(UINT32);
extern UINT32 sd_data_read (UINT32 *,UINT32 ,UINT32,dump_callback callback);
extern UINT32 sd_data_write (UINT32 *,UINT32 ,UINT32,response_callback callback);
extern UINT32 sd_data_erase(UINT32,UINT32);
extern UINT32 sd_voltage_validation (void);
extern UINT32 sd_init(UINT32);
extern UINT32 sd_get_capacity(UINT32 *capacity);
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================================*/
#endif  /* MMC_H */

