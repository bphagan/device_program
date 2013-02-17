/*****************************************************************************
** main.c
**
** Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
**
** This file contains copyrighted material. Use of this file is
** restricted by the provisions of a Freescale Software License
** Agreement, which has either been electronically accepted by
** you or has been expressly executed between the parties.
**
** Description: Explanation for the usage of this file.
**
** Revision History:
** -----------------
*****************************************************************************/

/*!
 * @file main.c
 *
 * @brief main source file
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "debug.h"
#include "type.h"
#include "protocol.h"
#include "flash_lib.h"
#include "fuse_lib.h"
#include "channel.h"
#include "platform.h"

/*****************************************************************************
* <Macros>
*****************************************************************************/
#define BUF_SIZE	(2 * 1024 * 1024)

#ifdef UNIT_TEST
#define CHANNEL		CHAN_UART //CHAN_USB//
#else
#define CHANNEL		*(volatile u32*)(MEM_BASE_ADDR)
#endif

/*****************************************************************************
* <Typedefs>
*****************************************************************************/
/*!
 * RAM Kernel command structure
 */
struct rkl_request {
	u32 addr;	/* NAND: offset address, NOR: physical address */
	u32 param; 	/* flash size or fuse value */
	u32 param1; /* reversed */
	cmd_t cmd;	/* flash or fuse command */
};

/*!
 * RAM Kernel response structure
 */
struct rkl_response {
	u16 ack;	/* response ack value */
	u16 csum;	/* data checksum */
	u32 len;	/* data len */
};

static s32 atk_cmd_receive(struct rkl_request*);
static void atk_cmd_parser(struct rkl_request);
static void atk_response_send(u16 ack, u16 csum, u32 len);
static void atk_dump_send(const u8 *buffer, u16 ack, u16 csum, u32 len);

/*****************************************************************************
* <Global Variables>
*****************************************************************************/
/* usb channel switch hook, 
 * only avaible to mx31&mx32 
 */
usb_sw_fn_t usbchan_switch = NULL;

/* indication for bi swap enable 
 * or not host will send command to 
 * set this flag  
 */ 
BI_SWAP_FLAG flag_bi_swap = BI_SWAP_DISABLE;

/* indication for bbt enable 
 * or not,host will send command 
 * to set this flag  
 */ 
FL_BBT_FLAG flag_fl_bbt = FL_BBT_DISABLE;

/* indication for the follow
 * up operation or not.
 * host will send command to 
 * set this flag  
 */ 
u8 go_on = 0;

/* indication for interleave  
 * or not, define in the main.c
 * host will send command to 
 * set this flag  
 */ 
FL_INTLV_FLAG flag_fl_intlv = FL_INTLV_DISABLE;

/* indication for using logic
 * block address(LBA) or not.
 * Currently wince bsp use the
 * LBA mode, while linux not
 * due to the kernel(MTD) out
 * of our control
 */
 
 u8 flag_lba = 0;  

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

/*!
 * main function to recevice command, parser and response.
 * 
 */
int main(void)
{
	struct rkl_request cmd;
		
	/* setup the channel to HOST */
	atk_channel_init(CHANNEL);

	while (1) {

		/* wait for command and do receive */
		if (atk_cmd_receive(&cmd) == 0) {
			/* parser the recv command */
			atk_cmd_parser(cmd);
		} else {
			/* invalid command */
			atk_response_send(ERROR_COMMAND, 0, 0);
		}

	}

	return 0;
}

/*!
 * Function to receive command from channel,
 * fill the command request structure.
 *
 * @req  command request returned to caller
 * 
 * @return 0 successful, less than 0 error
 */
static s32 atk_cmd_receive(struct rkl_request *req)
{
	u8 __attribute__ ((aligned(4))) buffer[RKL_COMMAND_LEN];
	u32 ret;

	/* read from USB or UART */
	ret = atk_channel_recv(buffer, RKL_COMMAND_LEN);
	if (ret) {
		dbg("channel read failed\n");
		return -1;
	}

	/* check magic number */
	if (*((u16*)&buffer[0]) != RKL_COMMAND_MAGIC) {
		dbg("invaild command header magic\n");
		return -2;
	}

	/* fill the buffer data into command struct */
	req->cmd = (cmd_t)(((u16)buffer[2] << 8) | buffer[3]);
	req->addr = ((u32)buffer[4] << 24) | ((u32)buffer[5] << 16) | ((u32)buffer[6] << 8) | (u32)buffer[7];
	req->param = ((u32)buffer[8] << 24) | ((u32)buffer[9] << 16) | ((u32)buffer[10] << 8) | (u32)buffer[11];
	req->param1 = ((u32)buffer[12] << 24) | 
				((u32)buffer[13] << 16) | ((u32)buffer[14] << 8) | (u32)buffer[15];

	return 0;
}

/*!
 * Function to parser the command from host
 * Parser the command, and then call the corresponding functions.
 *
 * @req  command request
 */
static void atk_cmd_parser(struct rkl_request req)
{
	u16 ack, checksum = 0;
	s16 ret = RET_SUCCESS;
	u32 length = 0;
	static __attribute__ ((aligned(4))) u8 buffer[BUF_SIZE];
	static __attribute__ ((aligned(4))) u8 fmodel[FLASH_MODEL_MAX];

	u8 mode = FLASH_PRG_UNBOUNDARY;
	u8 fuse_val = 0;
	u32 size, len;
	u8 file_format = 0;

	switch (req.cmd) 
	{

		case CMD_FLASH_INITIAL:
			ret = atk_flash_lib_initial();
			break;
		case CMD_FLASH_ERASE:
			go_on = 0;
			ret = atk_flash_lib_erase(req.addr, req.param, atk_response_send);
			break;
		case CMD_FLASH_DUMP:
		{
			u32 addr = req.addr;
			size = req.param;
			
			/* follow-up dump */
			go_on = (u8)(req.param1 & 0xff);
			
			/* check parameters */
			if (size <= 0) {
				ret = FLASH_FAILED;
				dbg("Flash dump: invalid parameters\n");
				break;
			}

			ret = atk_flash_lib_read(addr, buffer, size, 
						atk_dump_send, (u32)BUF_SIZE);
			if (ret < 0)
				break;
			return;
		}
		case CMD_FLASH_PRORAM:
			/* we did not support it now */
		case CMD_FLASH_PRORAM_UB:
		{
			size = (u32)req.param;
			file_format = (u8)(req.param1 & 0xff);
			
			go_on = (u8)((req.param1 >> 8) & 0xff);
			
			mode = (u8)((req.param1 >> 16) & 0xff);
			
			/* we return the size back to confirm */
			length = size;
			
			/* check parameters */
			if (size <= 0 || size > BUF_SIZE) {
				ret = FLASH_FAILED;
				dbg("Flash program: invalid parameters\n");
				break;
			} else {
				atk_response_send(RET_SUCCESS, 0, length);
			}

			/* receive data from channel */
			atk_channel_recv(buffer, size);

			ret = atk_flash_lib_program(req.addr, buffer, &size, &checksum, 
					mode, file_format, atk_response_send);

			if (ret < 0) {
				dbg("Flash program: write failed:%d\n", ret);
				break;
			}

			dbg("Flash program: program finish\n");
			ret = RET_SUCCESS;
			length = size;

			break;
		}
		case CMD_FUSE_READ:
			ret = atk_fuse_lib_read(req.addr, &fuse_val);
			if (ret < 0) {
				dbg("Fuse read: read failed:%d\n", ret);
				break;
			}
			/* send response and fuse value */
			atk_response_send(RET_SUCCESS, fuse_val, 0);
			return;
		case CMD_FUSE_SENSE:
			ret = atk_fuse_lib_sense(req.addr, &fuse_val, req.param);
			if (ret < 0) {
				dbg("Fuse read: read failed:%d\n", ret);
				break;
			}
			/* send response and fuse value */
			atk_response_send(RET_SUCCESS, fuse_val, 0);
			return;
		case CMD_FUSE_OVERRIDE:
			ret = atk_fuse_lib_override(req.addr, req.param);
			if (ret < 0) {
				dbg("Fuse override: failed %d\n", ret);
			}
			break;
		case CMD_FUSE_PROGRAM:
			ret = atk_fuse_lib_program(req.addr, req.param);
			if (ret < 0) {
				dbg("Fuse program: failed %d\n", ret);
			}
			break;
		case CMD_GETVER:
			/* get chip id */
			checksum = sys_get_chip_id();
			/* get model name */
			atk_flash_get_model(fmodel, &len);
			/* send response to host */
			atk_response_send(RET_SUCCESS, checksum, len);
			/* send flash model name */
			atk_channel_send(fmodel, len);
			return;
		case CMD_RESET:
			/* reset the mcu */
			sys_reset();
			return;
		case CMD_DOWNLOAD:
			if (req.addr < MEM_BASE_ADDR || req.addr >= MEM_BOTTOM_ADDR || 
					(req.addr + req.param) > MEM_BOTTOM_ADDR) {
				dbg("download address invalid\n");
				ret = INVALID_PARAM;
				break;
			}
			/* receive data from channel */
			atk_channel_recv((u8 *)req.addr, req.param);
			
			break;
		case CMD_EXECUTE:
			if (req.addr < MEM_BASE_ADDR || req.addr >= MEM_BOTTOM_ADDR) {
				dbg("execute address invalid\n");
				return;
			}
			/* execute the image at req.addr */
			((app*)req.addr)();
			break;
		case CMD_COM2USB:
			/* FIXME: mx31 specific command, ugly here */
			if (usbchan_switch != NULL) {
				/* call the hook */
				usbchan_switch();
			}
			return;
		case CMD_SWAP_BI:
			/* set the bi swap flag*/
			flag_bi_swap = (BI_SWAP_FLAG)(req.param & 0xff);
			break;
		case CMD_FL_BBT:
			/* set the flash based bbt flag*/
			if(flag_fl_bbt != (FL_BBT_FLAG)(req.param & 0xff)) {
				flag_fl_bbt = (FL_BBT_FLAG)(req.param & 0xff);
				ret = atk_flash_lib_initial();
			}
			break;
		case CMD_FLASH_GET_CAPACITY:
			ret = atk_flash_get_capacity(&length);
			break;
		case CMD_FL_INTLV:
			/* set the flash based interleave flag*/
			if(flag_fl_intlv != (FL_INTLV_FLAG)(req.param & 0xff)) {
				flag_fl_intlv = (FL_INTLV_FLAG)(req.param & 0xff);
				ret = atk_flash_lib_initial();
			}
			break;
		case CMD_FL_LBA:
			/* set the lba mode flag*/
			flag_lba = (req.param & 0xff);
			break;
		default:
			dbg("Invalid command id\n");
			break;
	}

	if (ret < 0) {
		ack = -ret;
	} else {
		ack = 0;
	}

	atk_response_send(ack, checksum, length);

	return;
}

/*!
 * Function to send response data to host
 * through channel.
 *
 * response protocol:
 *  ----------------------------------------
 * | ack[15:0] | len[15:0] | checksum[15:0] |
 *  ----------------------------------------
 *
 * @ack  response ack value
 * @len  response len value
 * @csum  response checksum value
 *
 */
static void atk_response_send(u16 ack, u16 csum, u32 len)
{
	u8 buffer[RKL_RESPONSE_LEN];

	buffer[0] = (u8)(ack >> 8);
	buffer[1] = (u8)ack;
	buffer[2] = (u8)(csum >> 8);
	buffer[3] = (u8)csum;
	buffer[4] = (u8)(len >> 24);
	buffer[5] = (u8)(len >> 16);
	buffer[6] = (u8)(len >> 8);
	buffer[7] = (u8)len;

	atk_channel_send((u8 *)buffer, RKL_RESPONSE_LEN);

	return;
}

static void atk_dump_send(const u8 *buffer, u16 ack, u16 csum, u32 len)
{
	atk_response_send(ack, csum, len);
	atk_channel_send(buffer, len);
}
