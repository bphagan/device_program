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
Terry Lv (r65388)           09/15/2006                  Initial Implementation
-------------------------   ------------    ----------  --------------------------------------------


====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "pu_irom_sd.h"
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
enum sd_commands
{
	CMD0    = 0,  /* Resets all cards to idle state */
	CMD1    = 1,  /* Reserved. */
    CMD2    = 2,  /* Asks any card to send the CID numbers on the CMD line (any card that is connected to the host will respond) */
    CMD3    = 3,  /* Ask the card to publish a new relative address (RCA). */
    CMD4    = 4,  /* Programs the DSR of all cards. */
	CMD5    = 5,  /* Reserved for I/O Mode (refer to the "SDIO Card Specification") */
    ACMD6   = 6,  /* Defines the data bus width (¡¯00¡¯=1bit or ¡¯10¡¯=4 bits bus) to be used for data transfer. The allowed data bus widths are given in SCR register. */
    CMD7    = 7,  /* Command toggles a card between the stand-by and transfer states or between the programming and disconnect states. 
                     In both cases, the card is selected by its own relative address and gets deselected by any other address; address 0 deselects all. 
                     In the case that the RCA equals 0, then the host may do one of the following: 
                     - Use other RCA number to perform card deselection. 
                     - Re-send CMD3 to change its RCA number to other than 0 and then use CMD7with RCA=0 for card deselection. */
	CMD8    = 8,  /* Sends SD Memory Card interface condition, which includes host supply voltage information and asks the card whether card supports voltage. */
    CMD9    = 9,  /* Addressed card sends its card-specific data (CSD) on the CMD line. */
    CMD10   = 10, /* Addressed card sends its card identification (CID) on CMD the line. */
    CMD11   = 11, /* Reserved. */
	CMD12   = 12, /* Forces the card to stop transmission. */
	CMD13   = 13, /* Addressed card sends its status register. */
    ACMD13  = 13, /* Send the SD Status. The status fields are given in Table 4-38. */
    CMD14   = 14, /* Reserved. */
    CMD15   = 15, /* Sends an addressed card into the Inactive State. This command is used when the host explicitly wants to deactivate a card. Reserved bits shall be set to '0'. */
	CMD16   = 16, /* In the case of a Standard Capacity SD Memory Card, this command sets the block length (in bytes) for all following block commands (read, write, lock). 
                     Default block length is fixed to 512 Bytes. 
                     Set length is valid for memory access commands only if partial block read operation are allowed in CSD. 
                     In the case of a High Capacity SD Memory Card, block length set by CMD16 command does not affect the memory read and write commands. Always 512 Bytes fixed block length is used. 
                     This command is effective for LOCK_UNLOCK command. 
                     In both cases, if block length is set larger than 512Bytes, the card sets the BLOCK_LEN_ERROR bit. */
	CMD17   = 17, /* In the case of a Standard Capacity SD. Memory Card, this command, this command reads a block of the size selected by the SET_BLOCKLEN command. 
                     In the case of a High Capacity Card, block length is fixed 512 Bytes regardless of the SET_BLOCKLEN command. Block length is specified the same as READ_SINGLE_BLOCK command. */
    ACMD17  = 17, /* Reserved. */
	CMD18   = 18, /* Continuously transfers data blocks from card to host until interrupted by a STOP_TRANSMISSION command. Block length is specified the same as READ_SINGLE_BLOCK command. */
	ACMD18  = 18, /* Reserved for SD security applications */
    ACMD22  = 22, /* Send the numbers of the written (without errors) blocks. Responds with 32-bit+CRC data block. 
                     If WRITE_BL_PARTIAL='0', the unit of ACMD22 is always 512 byte. 
                     If WRITE_BL_PARTIAL='1', the unit of ACMD22 is a block length which was used when the write command was executed.*/
    ACMD23  = 23, /* Set the number of write blocks to be pre-erased before writing (to be used for faster Multiple Block WR command). ¡°1¡±=default (one wr block). */
	CMD24   = 24, /* In the case of a Standard Capacity SD Memory Card, this command writes a block of the size selected by the SET_BLOCKLEN command. 
                     In the case of a High Capacity Card, block length is fixed 512 Bytes regardless of the SET_BLOCKLEN command. */
	CMD25   = 25, /* Continuously writes blocks of data until a STOP_TRANSMISSION follows. Block length is specified the same as WRITE_BLOCK command. */
    ACMD25  = 25, /* Reserved for SD security applications */
    CMD26   = 26, /* Reserved For Manufacturer */
    ACMD26  = 26, /* Reserved for SD security applications */
    CMD27   = 27, /* Programming of the programmable bits of the CSD. */
	CMD28   = 28, /* If the card has write protection features, this command sets the write protection bit of the addressed group. The properties of write protection are coded in the card specific data (WP_GRP_SIZE). A High Capacity Card does not support this command. */
    CMD29   = 29, /* If the card has write protection features, this command clears the write protection bit of the addressed group. A High Capacity Card does not support this command. */
    CMD30   = 30, /* If the card has write protection features, this command asks the card to send the status of the write protection bits.6 A High Capacity Card does not support this command */
    CMD31   = 31, /* Reserved */
	CMD32   = 32, /* Sets the address of the first write block to be erased. */
	CMD33   = 33, /* Sets the address of the last write block of the continuous range to be erased. */
    CMD34   = 34, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */
    CMD35   = 30, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */
	CMD36   = 32, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */
	CMD37   = 33, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */	
    CMD38   = 38, /* Erases all previously selected write blocks */
    ACMD38  = 38, /* Reserved for SD security applications */
    CMD39   = 39, /* Reserved */
    CMD40   = 40, /* Not valid in SD Memory Card - Reserved for MultiMediaCard I/O mode */
    CMD41   = 41, /* Reserved */
    ACMD41  = 41, /* Sends host capacity support information (HCS) and asks the accessed card to send its operating condition register (OCR) content in the response on the CMD line. HCS is effective when card receives SEND_IF_COND command. Reserved bit shall be set to ¡®0¡¯. */
    CMD42   = 42, /* Used to Set/Reset the Password or lock/unlock the card. A transferred data block includes all the command details - refer to Chapter 4.3.7. The size of the Data Block is defined with SET_BLOCK_LEN command. */
    ACMD42  = 42, /* Connect[1]/Disconnect[0] the 50 KOhm pull-up resistor on CS (pin 1) of the card. The pull-up may be used for card detection. */
    CMD43   = 43, /* Reserved */
    ACMD43  = 43, /* Reserved for SD security applications */
    CMD44   = 44, /* Reserved */
    ACMD44  = 44, /* Reserved for SD security applications */
    CMD45   = 45, /* Reserved */
    ACMD45  = 45, /* Reserved for SD security applications */
    CMD46   = 46, /* Reserved */
    ACMD46  = 46, /* Reserved for SD security applications */
    CMD47   = 47, /* Reserved */
    ACMD47  = 47, /* Reserved for SD security applications */
    CMD48   = 48, /* Reserved */
    ACMD48  = 48, /* Reserved for SD security applications */
    CMD49   = 49, /* Reserved */
    ACMD49  = 49, /* Reserved for SD security applications */
    CMD50   = 50, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */
    CMD51   = 51, /* Reserved */
    ACMD51  = 51, /* Reads the SD Configuration Register (SCR) */
    CMD52   = 52, /* Reserved for I/O Mode (refer to the "SDIO Card Specification") */
    CMD53   = 53, /* Reserved for I/O Mode (refer to the "SDIO Card Specification") */
    CMD54   = 54, /* Reserved for I/O Mode (refer to the "SDIO Card Specification") */
	CMD55   = 55, /* Indicates to the card that the next com-command is an application specific command rather than a standard command */
    CMD56   = 56, /* Used either to transfer a Data Block to the card or to get a Data Block from the card for general purpose/application specific commands. 
                     In the case of Standard Capacity SD Memory Cards, the size of the Data Block shall be defined with SET_BLOCK_LEN command. 
                     In the case of a High Capacity SD Memory Cards, the size of the data block is fixed to 512 byte. The host sets RD/WR=1 for reading data from the card and sets to 0 for writing data to the card. */
    CMD57   = 57, /* Reserved for each command system set by switch function command (CMD6). Refer to each command system specification for more detail. */
    CMD58   = 58, /* Reserved. */
    CMD59   = 59, /* Reserved */
    CMD60   = 60, /* Reserved For Manufacturer */
    CMD61   = 61, /* Reserved For Manufacturer */
    CMD62   = 62, /* Reserved For Manufacturer */
    CMD63   = 63  /* Reserved For Manufacturer */
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
extern UINT32 card_multiple_voltage_support(void);
extern UINT32 card_get_cid (void);
extern UINT32 card_set_data_transfer_mode(void);
extern void   card_command_config (command_t *cmd_config,UINT32 index,UINT32 argument,xfer_type_t transfer,response_format_t format, 
                                  data_present_select data,crc_check_enable crc,cmdindex_check_enable cmdindex);
extern UINT32 card_config_iomax(void);


#endif
