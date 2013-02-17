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
#include "pu_irom_mmc.h"
#include "pu_irom_esdhc.h"                        
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                            MACROS
==================================================================================================*/  
#define SUCCESS 0
#define FAIL 1
#define MMC 0
#define SD 1
#define NO_ARG 0
#define RCA_SHIFT 16
#define ZERO  (0)
//#define ONE 1
#define FOUR 4
#define EIGHT 8
#define TWO_K_SIZE 2048
#define MMCSD_IROM_DATA_HEADER_OFFSET 0x400
#define MMCSD_R1_STATUS_CURR_STATE 0x1E00
#define MMCSD_READY_TIMEOUT    3000  /* ~(3s / (2 * 48 * 10us)) */
#define MMCSD_SUPPORT

#define CARD_RCA_SHIFT                  (16)

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

typedef struct 
{
	UINT32 csd0;
	UINT32 csd1;
	UINT32 csd2;
	UINT32 csd3;
}card_specific_data;

/* Defines the id for each command */
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
	CMD16   = 16,
	CMD17   = 17,
	CMD18   = 18,
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
	DIS	
};

typedef struct
{
	UINT32 cid0;
	UINT32 cid1;
	UINT32 cid2;
	UINT32 cid3;	
}card_ident;


/* CARD Flash Configuration Parameters Structure */
typedef struct {
    UINT32  length;         /* Length of Card data to read */
} CARD_FLASH_CFG_PARMS_T;

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                          Global Function 
==================================================================================================*/ 
extern UINT32 card_init (UINT32 bus_width, UINT32 base_address);
extern UINT32 card_data_read (UINT32* dest_ptr,UINT32 len,UINT32 offset);
extern UINT32 card_software_reset (void);
extern UINT32 card_get_cid (void);
extern UINT32 card_set_data_transfer_mode(void);
extern UINT32 card_check_status(UINT32, UINT32, UINT32);
extern void   card_command_config (command_t *cmd_config,UINT32 index,UINT32 argument,xfer_type_t transfer,response_format_t format, 
                                  data_present_select data,crc_check_enable crc,cmdindex_check_enable cmdindex);


#endif
