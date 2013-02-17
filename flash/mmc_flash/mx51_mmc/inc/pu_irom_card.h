#ifndef CARD_H
#define CARD_H
/*==================================================================================================
     Header Name: pu_irom_card.h
     General Description: Defines related to MMC/SD/CE-ATA module. 
====================================================================================================

                                      
                         Copyright: 2004,2005,2006,2007 FREESCALE, INC.
                   All Rights Reserved. This file contains copyrighted material.
                   Use of this file is restricted by the provisions of a 
                   Freescale Software License Agreement, which has either 
                   accompanied the delivery of this software in shrink wrap
                   form or been expressly executed between the parties.
     
Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number    Description of Changes
-------------------------   ------------    ----------  --------------------------------------------
Deepak Agarwal               30/July/2007   TLSbo94587   CE-ATA, Ported to Ringo.
Prabhat singh                 16/07/2007      TLSbo94839   Added CMD8 to support high capcity SD card
Surender Kumar             06/07/2007      TLSbo93610   Porting for MArley
Surender Kumar             09/15/2006      TLSbo79133   Initial Implementation
-------------------------   ------------    ----------  --------------------------------------------


====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "pu_irom_esdhc.h"                        
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                            MACROS
==================================================================================================*/  
#define SUCCESS                         (0)
#define FAIL                            (1)
#define NO_ARG                          (0)
#define ZERO                            (0)
#define ONE                             (1)
#define FOUR                            (4)
#define EIGHT                           (8)
#define TWO_K_SIZE                      (2048)
#define MMCSD_IROM_DATA_HEADER_OFFSET   (0x400)
#define MMCSD_R1_STATUS_CURR_STATE      (0x1E00)
#define CARD_READY_TIMEOUT              (3000)
#define CARD_BUSY_BIT                   ((UINT32)0x80000000)
#define CARD_RCA_SHIFT                  (16)
#define MMCSD_CMD_SEL_CARD_TIMEOUT      (96)     /* 3 ms */

/* Addressing mode supported by SD/MMC card */
#define CARD_SUPPORT_BYTE_MODE          (0)
#define CARD_SUPPORT_SECT_MODE          (1)

/* Build with MMC/SD support */
#define MMCSD_SUPPORT

/*==================================================================================================
                                          Global Variable 
==================================================================================================*/ 
extern UINT32 Card_rca;
extern UINT32 address_mode;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

enum CARD_TYPE 
{
    CARD_NONE,
    CARD_MMC,
    CARD_SD,
};

/* Card CID */
typedef struct
{
    UINT32 cid0;
    UINT32 cid1;
    UINT32 cid2;
    UINT32 cid3;
} card_ident;

typedef struct 
{
	UINT32 csd0;
	UINT32 csd1;
	UINT32 csd2;
	UINT32 csd3;
} card_specific_data;

/* CARD Flash Configuration Parameters Structure */
typedef struct {
    UINT32  length;         /* Length of  data to be read from card */
} CARD_FLASH_CFG_PARMS_T;

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/* Defines the ID for each command */
enum commands
{
	CMD0= 0,
	CMD1= 1,
	CMD2= 2,
	CMD3= 3,
	CMD5= 5,
       CMD6=6,
	ACMD6= 6,
	CMD7= 7,
	CMD8=8,
       CMD9=9,
	CMD12   = 12,
	CMD13   = 13,
    CMD14   = 14,
	CMD16   = 16,
	CMD17   = 17,
	CMD18   = 18,
    CMD19   = 19,
	CMD24   = 24,
	CMD25   = 25,
	CMD26   = 26,
	CMD32   = 32,
	CMD33   = 33,
    CMD34   = 34,
    CMD35   = 35,
    CMD36   = 36,
        CMD37   = 37,
	CMD38   = 38,
       CMD39   = 39,
    CMD40   = 40,
	ACMD41  = 41,
    CMD43   = 43,
	ACMD51  = 51,
	CMD55   = 55,
       CMD60   = 60,
       CMD61   = 61	
};

/* Defines for the states of the card*/
enum states
{
	IDLE,
	READY,
	IDENT,
	STBY,
	TRAN,
	DATA,
	RCV,
	PRG,
    DIS,
    BTST,
    SLP
};

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                          Global Function 
==================================================================================================*/ 
extern UINT32 card_init(UINT32, UINT32);
extern UINT32 card_data_read(UINT32 *, UINT32, UINT32);
extern UINT32 card_software_reset(void);
extern UINT32 card_get_cid(void);
extern UINT32 card_set_data_transfer_mode(void);
extern UINT32 card_check_status(UINT32, UINT32, UINT32);
extern void card_command_config(command_t *, UINT32, UINT32,
                                xfer_type_t, response_format_t,
                                data_present_select, crc_check_enable,
                                cmdindex_check_enable);

extern UINT32 card_send_virtual_read_command(void);

#endif
