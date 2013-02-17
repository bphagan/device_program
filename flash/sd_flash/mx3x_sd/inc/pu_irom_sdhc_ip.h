#ifndef SDHC_IP_H
#define SDHC_IP_H
/*==================================================================================================
                                                                               
    Module Name:  pu_irom_sdhc_ip.h

    General Description: External API for SDHC IP.

====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.
  

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Suresh Kumar                 03/Oct/2006    TLSbo79133    Initial Version 
Suresh Kumar                 09/Feb/2007    TLSbo90422    Set loopcount to 3000
                                                          to get timeout period below 5 sec


-------------------------   ------------    ----------   ------------------------------------------- 
Portability: Portable.
References : iMX31 L3 Specifications V1.43

====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "Common.h"

/*==================================================================================================
                                            MACROS
==================================================================================================*/      

/*==================================================================================================
                                            DEFINES 
==================================================================================================*/      
#define MMCSD_RESPONSE_LEN     8     /* 128(16*8) BITS */
#define MMCSD_READY_TIMEOUT    3000  /* ~(3s / (2 * 48 * 10us)) */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

typedef enum 
{
READ = 0,
WRITE = 1,
SD_COMMAND
}xfer_type_t;

typedef enum 
{
    RESPONSE_NONE = 0,
    RESPONSE_48 = 1,
    RESPONSE_136 = 2,
    RESPONSE_48_WITHOUT_CRC = 3,
    RESPONSE_OTHERS = -1
}response_format_t;

typedef enum 
{
    DATA_PRESENT_NONE,
    DATA_PRESENT
}data_present_select;

typedef enum 
{	
    DISABLE,
    ENABLE
}crc_check_enable,cmdindex_check_enable;

typedef enum
{
    OPERATING_FREQ = 20000,   /* in kHz */
    IDENTIFICATION_FREQ = 400   /* in kHz */
}sdhc_freq_t;    

enum sdhc_status
{
    SDHC_STATUS_PASS = 0,
    SDHC_STATUS_FAILURE = 1
};

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* SDHC Command Structure */
/* Command information structure */
/* crc_check and cmdindex_check will be ignored */

typedef struct
{
    UINT32 command;
    UINT32 arg;
    xfer_type_t data_transfer;
    response_format_t response_format;
    data_present_select data_present;
    crc_check_enable crc_check;
    cmdindex_check_enable cmdindex_check;
}command_t;

/* SDHC Response Structure */
typedef struct
{
    response_format_t format;
    UINT32 cmd_rsp0;
    UINT32 cmd_rsp1;
    UINT32 cmd_rsp2;
    UINT32 cmd_rsp3;
}command_response_t;

/*==================================================================================================
                                    EXPORTED FUNCTIONS API
==================================================================================================*/
extern void interface_reset(void);
extern void interface_configure_clock(sdhc_freq_t frequency);
extern U32  interface_read_response(command_response_t *resp);
extern U32  interface_send_cmd_wait_resp(command_t *cmd);
extern void interface_config_block_info(U32 blk_len, U32 nob);
extern U32  interface_data_read(U32 * dest_ptr, U32 blk_len);
extern U32  interface_data_write(U32* dest_ptr, U32 blk_len);
extern void interface_init(U32 base_address);

#endif
