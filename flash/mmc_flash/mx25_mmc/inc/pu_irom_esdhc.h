#ifndef ESDHC_H
#define ESDHC_H

/*==================================================================================================
     Header Name: pu_irom_esdhc.h
     General Description: Defines related to eSDHC module.
====================================================================================================


                            Copyright: 2004-2008 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a
                   Freescale Software License Agreement, which has either
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.

Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number         Description of Changes
---------------             -----------    ------------      --------------------------------------------
Chandan Singh               19/May/2008    ENGcm05741         Changes for R1b response and re-arranged the macro defines
Chandan Singh               19/May/2008    ENGcm05724         Modified eSDHC driver funtion to return GPT timeout status.
Chandan Singh               24/Apr/2008    ENGcm05242         eSDHC CRC HW bug fix.
Radhish                     27/Mar/2008    ENGcm05061         Added emmc 4.3 Support
Radhish                     01/Apr/2008    ENGcm05097         Modified the timeout values
Chandan Singh               21/Feb/2008    ENGcm03474         Senna SD card spec version check fix.
Chandan Singh               31/Jan/2008    ENGcm03179         Ported to Senna.
Chandan Singh               29/Jan/2008    ENGcm03109         Changes for eSD boot fix, increase the DTOCV value.
Chandan Singh               11/Jan/2008    ENGcm02841         RTL FIX, ESDHC_OPER_TIMEOUT increased to 6ms from 3ms
Chandan Singh               03/Jan/2008    ENGcm02639         Added time out for CMD1 to support eMMC.
Chandan Singh               20/Dec/2007    ENGcm02497         Initial port for eSDHC support taken from ELVIS
Prabhat Singh               20/Nov/2007    ENGcm01902         eSDHC clock changes
Jameer B Mulani             21/Nov/2007    ENGcm01834         Added MMC/SD/eSD boot support for Elvis
Jameer B Mulani             26/Sep/2007    TLSbo94791         eSD support:Review commments updation.
Sajith P V                  10/Sep/2007    TLSb096207         Changed ESDHC_OPERT_FREQ value from 0x100 to 0x200
Prabhat singh               31/Aug/2007    TLSbo95960         identification /operating frequency divider value modification
Deepak Agarwal              30/Jul/2007    TLSbo94587         CE-ATA, Ported to Ringo.
Prabhat Singh               13/Jul/2007    Tlbso94839         Added eSDHCv2 support for Ringo
Surender Kumar              06/Jul/2007    TLSbo93610         Initial Implementation
-------------------------   ------------    ----------  --------------------------------------------
================================================================================================== */

/*====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
//#include "utility.h"
#include "Common.h"

/*====================================================================================================
                                         Global Variables
==================================================================================================*/

/*==================================================================================================
                                            MACROS
==================================================================================================*/
#define ESDHC_SOFTWARE_RESET_DATA ((UINT32)0x04000000)  /* RSTD bit of eSDHC system control register */
#define ESDHC_SOFTWARE_RESET      ((UINT32)0x01000000)  /* RSTA bit of eSDHC system control register */
#define ESDHC_SOFTWARE_INIT       ((UINT32)0x08000000)  /* INITA bit of eSDHC system control register */
#define ESDHC_LITTLE_ENDIAN_MODE  ((UINT32)0x00000020)  /* Little Endian mode */
#define ESDHC_HW_BIG_ENDIAN_MODE  ((UINT32)0x00000010)  /* Half Word Big Endian mode */
#define ESDHC_BIG_ENDIAN_MODE     ((UINT32)0x00000000)  /* Big Endian mode */
#define ESDHC_ONE_BIT_SUPPORT     ((UINT32)0x00000000)  /* 1 Bit Mode support */
#define ESDHC_FOUR_BIT_SUPPORT    ((UINT32)0x00000002)  /* 4 Bit Mode support */
#define ESDHC_EIGHT_BIT_SUPPORT   ((UINT32)0x00000004)  /* 8 Bit Mode support */
#define ESDHC_CLOCK_ENABLE        ((UINT32)0x00000007)  /* Clock Enable */
#define ESDHC_FREQ_MASK           ((UINT32)0xfff00007)  /* Freq and DTOCV mask */
#define ESDHC_IDENT_FREQ          ((UINT32)0x00008000)  /* SDCLKFS = 0x80 (Divide by 256); DVS = 0x0(Divide by 1) */
#define ESDHC_OPERT_FREQ          ((UINT32)0x00000200)  /* SDCLKFS = 0x02 (Divide by 4)  ; DVS = 0x0(Divide by 1) */
#define ESDHC_INTERRUPT_ENABLE    ((UINT32)0x007f0133)  /* Enable Interrupts */
#define ESDHC_CLEAR_INTERRUPT     ((UINT32)0x117f01ff)  /* Clear all int at eSDHC level */
#define ESDHC_DTOCV_VAL           ((UINT32)0x000E0000)  /* DTOCV = 1110b = SDCLK x 2^27 */
#define ESDHC_IRQSTATEN_DTOESEN   ((UINT32)0x00100000)  /* Data Timeout Error Status Enable Interrupt (DTOESEN) */
#define ESDHC_ENDIAN_MODE_MASK    ((UINT32)0x00000030)  /* Endianness mask */
#define ESDHC_SYSCTRL_RSTC        ((UINT32)0x02000000)  /* SW reset to CMD line */

#define ESDHC_OPER_TIMEOUT        (96)     /* 3ms time out */
#define ESDHC_ACMD41_TIMEOUT      (32000)  /* 1.0 sec =1000 msec delay for ACMD41 cmd */
#define ESDHC_CMD1_TIMEOUT        (32000)  /* 1.0 sec =1000 msec delay for CMD1 cmd */
#define ESDHC_BLOCK_SHIFT         (16)

#define ESDHC_BUS_WIDTH_MASK                    ((UINT32)0x00000006)   /* Bus width mask */
#define ESDHC_DATA_TRANSFER_SHIFT               (4)
#define ESDHC_RESPONSE_FORMAT_SHIFT             (16)
#define ESDHC_DATA_PRESENT_SHIFT                (21)
#define ESDHC_CRC_CHECK_SHIFT                   (19)
#define ESDHC_CMD_INDEX_CHECK_SHIFT             (20)
#define ESDHC_CMD_INDEX_SHIFT                   (24)
#define ESDHC_BLOCK_COUNT_ENABLE_SHIFT          (1)
#define ESDHC_MULTI_SINGLE_BLOCK_SELECT_SHIFT   (5)
#define ESDHC_BLK_LEN                           (512)
#define ESDHC_READ_WATER_MARK_LEVEL_BL_4        ((UINT32)0x1)
#define ESDHC_READ_WATER_MARK_LEVEL_BL_8        ((UINT32)0x2)
#define ESDHC_READ_WATER_MARK_LEVEL_BL_16       ((UINT32)0x4)
#define ESDHC_READ_WATER_MARK_LEVEL_BL_64       ((UINT32)0x00000010)
#define ESDHC_READ_WATER_MARK_LEVEL_BL_512      ((UINT32)0x00000080)

#define ESDHC_WRITE_WATER_MARK_LEVEL_BL_4       ((UINT32)0x00010000)
#define ESDHC_WRITE_WATER_MARK_LEVEL_BL_8       ((UINT32)0x00020000)
#define ESDHC_WRITE_WATER_MARK_LEVEL_BL_16      ((UINT32)0x00040000)
#define ESDHC_WRITE_WATER_MARK_LEVEL_BL_64      ((UINT32)0x00100000)
#define ESDHC_WRITE_WATER_MARK_LEVEL_BL_512     ((UINT32)0x00400000)

/* Present State register bit masks */
#define ESDHC_PRESENT_STATE_CIHB    (0x01)
#define ESDHC_PRESENT_STATE_CDIHB   (0x02)
#define ONE                         (1)
#define ESDHC_FIFO_SIZE             (128)

#define ESDHC_STATUS_END_CMD_RESP_MSK         ((UINT32)0x00000001)
#define ESDHC_STATUS_END_CMD_RESP_TIME_MSK    ((UINT32)0x000F0001) /* CIE|CEBE|CCE|CTOE|CC */
#define ESDHC_STATUS_TIME_OUT_RESP_MSK        ((UINT32)0x00010000)
#define ESDHC_STATUS_RESP_CRC_ERR_MSK         ((UINT32)0x00020000)
#define ESDHC_STATUS_RESP_CMD_INDEX_ERR_MSK   ((UINT32)0x00080000)
#define ESDHC_STATUS_BUF_READ_RDY_MSK         ((UINT32)0x00000020)
#define ESDHC_STATUS_BUF_WRITE_RDY_MSK        ((UINT32)0x00000010)
#define ESDHC_STATUS_DATA_RW_MSK              ((UINT32)0x00700002) /* DEBE|DCE|DTOE|TC */
#define ESDHC_STATUS_TRANSFER_COMPLETE_MSK    ((UINT32)0x00000002) /* TC */
#define ESDHC_STATUS_TIME_OUT_READ_MASK       ((UINT32)0x00100000) /* Mask for DTOE in IRQSTAT */
#define ESDHC_STATUS_READ_CRC_ERR_MSK         ((UINT32)0x00200000) /* Mask for DCE in IRQSTAT */
#define ESDHC_STATUS_RESP_CMD_END_BIT_ERR_MSK ((UINT32)0x00040000) /* Mask for CEBE in IRQSTAT */
#define ESDHC_STATUS_RW_DATA_END_BIT_ERR_MSK  ((UINT32)0x00400000) /* Mask for DEBE in IRQSTAT */

#define ESDHC_STATUS_TIME_OUT_READ  (3200)   /* Delay used in esdhc_poll_cihb_cdihb() */
#define ESDHC_READ_DATA_TIME_OUT    (3200)   /* Delay used 100ms for read buffer ready */
#define ESDHC_WRITE_DATA_TIME_OUT   (8000)   /* Delay used 250ms for write buffer ready */

#define ESDHC_CONFIG_BLOCK_512      (0x00000200)  /* 512 byte block size */
#define ESDHC_CONFIG_BLOCK_64       (0x00000040)  /* 64 byte block size */
#define ESDHC_CONFIG_BLOCK_8        (0x00000008)  /* 8 byte block size */
#define ESDHC_CONFIG_BLOCK_4        (0x00000004)  /* 4 byte block size */

#define ESDHC_DTOCV_MASK            ((UINT32)0x000F0000)  /*DTOCV mask*/
#define ESDHC_DTOCV_1S_VAL          ((UINT32)0x00050000)  /*DTOCV value to set a timeout value of app 1.31 sec*/
#define ESDHC_DTOE_SET              ((UINT32)0x00100000)  /*DTOE set mask*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
typedef enum
{
    ESDHC1,
    ESDHC2
} esdhc_num_t;

typedef enum
{
    WRITE,
    READ
} xfer_type_t;

typedef enum
{
    RESPONSE_NONE,
    RESPONSE_136,
    RESPONSE_48,
    RESPONSE_48_CHECK_BUSY
} response_format_t;


typedef enum
{
    DATA_PRESENT_NONE,
    DATA_PRESENT
} data_present_select;

typedef enum
{
    DISABLE,
    ENABLE
} crc_check_enable, cmdindex_check_enable, block_count_enable;

typedef enum
{
    SINGLE,
    MULTIPLE
} multi_single_block_select;

typedef enum
{
    BIG_ENDIAN,
    HALF_WORD_BIG_ENDIAN,
    LITTLE_ENDIAN
} endian_mode_t;

typedef enum
{
    OPERATING_FREQ = 20000,     /* in kHz */
    IDENTIFICATION_FREQ = 400   /* in kHz */
} sdhc_freq_t;


enum esdhc_data_status
{
    ESDHC_DATA_ERR = 3,
    ESDHC_DATA_OK = 4
};

enum esdhc_int_cntr_val
{
    ESDHC_INT_CNTR_END_CD_RESP = 0x4,
    ESDHC_INT_CNTR_BUF_WR_RDY = 0x8
};

enum esdhc_reset_status
{
    ESDHC_WRONG_RESET = 0,
    ESDHC_CORRECT_RESET = 1
};

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* eSDHC register set */
typedef struct
{
    volatile UINT32 dma_system_address;
    volatile UINT32 block_attributes;
    volatile UINT32 command_argument;
    volatile UINT32 command_transfer_type;
    volatile UINT32 command_response0;
    volatile UINT32 command_response1;
    volatile UINT32 command_response2;
    volatile UINT32 command_response3;
    volatile UINT32 data_buffer_access;
    volatile UINT32 present_state;
    volatile UINT32 protocol_control;
    volatile UINT32 system_control;
    volatile UINT32 interrupt_status;
    volatile UINT32 interrupt_status_enable;
    volatile UINT32 interrupt_signal_enable;
    volatile UINT32 autocmd12_status;
    volatile UINT32 host_controller_capabilities;
    volatile UINT32 watermark_level;
    UINT32 reserved1[2];
    volatile UINT32 force_event;
    volatile UINT32 adma_error_status_register;
    volatile UINT32 adma_system_address;
    UINT32 reserved2[40];
    volatile UINT32 host_controller_version;
} ESDHC_t, *pESDHC_t;

/* eSDHC command format */
typedef struct
{
    UINT32 command;
    UINT32 arg;
    xfer_type_t data_transfer;
    response_format_t response_format;
    data_present_select data_present;
    crc_check_enable crc_check;
    cmdindex_check_enable cmdindex_check;
    block_count_enable block_count_enable_check;
    multi_single_block_select  multi_single_block;
} command_t;

/* Response from card to eSDHC CMDRSP register */
typedef struct
{
    response_format_t format;
    UINT32 cmd_rsp0;
    UINT32 cmd_rsp1;
    UINT32 cmd_rsp2;
    UINT32 cmd_rsp3;
} command_response_t;

/* Structure to backup affected eSDHC register durring RSTD */
typedef struct
{
    UINT32 dma_system_address;
    UINT32 block_attributes;
    UINT32 protocol_control;
    UINT32 watermark_level;
    UINT32 adma_system_address;
} esdhc_reg_bkp_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/* eSDHC base address */
extern pESDHC_t esdhc_base_pointer;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
extern UINT32 interface_reset(UINT32, UINT32);
extern void interface_set_bus_width_endianess(UINT32 , UINT32);
extern void interface_configure_clock(sdhc_freq_t);
extern void interface_read_response(command_response_t *);
extern UINT32 interface_send_cmd_wait_resp(command_t *);
extern UINT32 interface_data_read(UINT32 *, UINT32);
extern UINT32 interface_data_write(UINT32 *, UINT32);
extern void interface_config_block_info(UINT32, UINT32, UINT32);
extern void interface_init(UINT32);
extern void interface_clear_interrupt(void);
extern void interface_reset_cmd_line(void);

/*================================================================================================*/
#endif  /* ESDHC_H */

