#ifndef CARD_H
#define CARD_H
/*==================================================================================================
     Header Name: pu_irom_card.h
     General Description: Defines related to MMC/SD/CE-ATA module. 
====================================================================================================

                                      
                                  Freescale Semiconductor
                 (c) Copyright Freescale Semiconductor, Inc. 2005, All Rights Reserved
     
Revision History:
                            Modification     Tracking
Author (core ID)                Date          Number    Description of Changes
-------------------------   ------------    ----------  --------------------------------------------
Surender Kumar             09/15/2006      TLSbo79133   Initial Implementation
-------------------------   ------------    ----------  --------------------------------------------


====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "pu_irom_mmc.h"
#include "pu_irom_sdhc_ip.h"                        
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
#define BLK_LEN 512
#define ONE 1
#define FOUR 4
#define EIGHT 8
#define MMCSD_R1_STATUS_CURR_STATE 0x1E00
#define MMCSD_SUPPORT
/*==================================================================================================
                                          Global Variable 
==================================================================================================*/ 
extern UINT32 Card_rca;


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

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
	CMD35   = 35,
	CMD36   = 36,
	CMD38   = 38,
	ACMD41  = 41,
	ACMD51  = 51,
	CMD55   = 55	
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

typedef enum
{
    BIT_MODE_1,
    BIT_MODE_4,
    BIT_MODE_8
}bus_width_t;

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
extern void   card_command_config (command_t *cmd_config,UINT32 index,UINT32 argument,xfer_type_t transfer,response_format_t format, 
                                  data_present_select data,crc_check_enable crc,cmdindex_check_enable cmdindex);


#endif
