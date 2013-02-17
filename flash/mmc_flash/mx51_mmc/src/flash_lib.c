/*****************************************************************************
** flash_lib.c
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
 * @file flash_lib.c
 *
 * @brief source code for the interfaces of flash lib
 *
 * @ingroup flash
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"
#include "pu_irom_mmc.h"
#include "pu_irom_sd.h"
#include "pu_irom_card.h"
#include "pu_irom_timer.h"
#include "protocol.h"
#include "flash_lib.h"
#include "debug.h"

//#define TY_DBG

static u8 card_status = 0;

extern enum CARD_TYPE nCardType;

/*!
 * Function 
 *
 * @req  command request returned to caller
 * 
 * @return 0 successful, less than 0 error
 */
s16 atk_flash_lib_initial (void)
{
	s16 ret;
	
	ret = card_init(1, 0x70004000);
	
	if ( RET_SUCCESS == ret) {
		card_status = 1;
		return RET_SUCCESS;
	}
	return FLASH_FAILED;
		
}
/*!
 * Function 
 *
 * @req  command request returned to caller
 * 
 * @return 0 successful, less than 0 error
 */
s16 atk_flash_lib_erase (u32 offset, u32 size, response_callback callback)
{
	s16 ret;
	
	if (!card_status) {
		return FLASH_ERROR_INIT;
	}

    switch (nCardType)
    {
        case CARD_MMC:
            ret = mmc_data_erase(offset,size);
            break;
        case CARD_SD:
            ret = sd_data_erase(offset,size);
            break;
        default:
            return FLASH_ERROR_INIT;
            break;
    }
	
	
	if ( RET_SUCCESS == ret)
		return RET_SUCCESS;

	return FLASH_ERROR_ERASE;
}
/*!
 * Function 
 *
 * @req  command request returned to caller
 * 
 * @return 0 successful, less than 0 error
 */
s16 atk_flash_lib_read (u32 offset, u8 *buffer, u32 count,dump_callback callback,u32 bufsize)
{
	s16 ret;
	
	if (!card_status) 
    {
		return FLASH_ERROR_INIT;
	}

    switch (nCardType)
    {
        case CARD_MMC:
            ret = mmc_data_read((U32*)buffer,count,offset,callback);
            break;
        case CARD_SD:
            ret = sd_data_read((U32*)buffer,count,offset,callback);
            break;
        default:
            return FLASH_ERROR_INIT;
            break;
    }

	if ( RET_SUCCESS == ret)
		return RET_SUCCESS;
	else
		return FLASH_ERROR_READ;
}
/*!
 * Function 
 *
 * @req  command request returned to caller
 * 
 * @return 0 successful, less than 0 error
 */
s16 atk_flash_lib_program (u32 offset, const u8 *buffer, u32 *pcount, u16 *pcsum, u8 mode, u8 file_format, response_callback callback)
{
	s16 ret;

	if (!card_status) 
    {
		return FLASH_ERROR_INIT;
	}

    switch (nCardType)
    {
        case CARD_MMC:
            {
                ret = mmc_data_write((U32 *)buffer, *pcount, offset, callback);
  
	            if (RET_SUCCESS != ret)
		            return FLASH_ERROR_PROG;
					
				if (mode) {
					ret = mmc_data_read((U32*)buffer, *pcount, offset, NULL);
		
					if (RET_SUCCESS != ret)
						return FLASH_ERROR_VERIFY;
				}
            }
            break;
        case CARD_SD:
            {
                ret = sd_data_write((U32 *)buffer, *pcount, offset, callback);
  
	            if (RET_SUCCESS != ret)
		            return FLASH_ERROR_PROG;
				
				if (mode) {
					ret = sd_data_read((U32 *)buffer, *pcount, offset, NULL);
		
					if (RET_SUCCESS != ret)
						return FLASH_ERROR_VERIFY;
				}
            }
            break;
        default:
            return FLASH_ERROR_INIT;
            break;
    }

	/* send the verify response to host */
    if (callback && mode) {
	    callback(FLASH_VERIFY, 0, *pcount);
		*pcsum = calculate_checksum(buffer,*pcount);
	}
	
	return RET_SUCCESS;	
}

/*!
 * Function to get device capacity
 * @param	[out] capacity- the device capacity in kbytes
 * @return 	0 successful, less than 0 error
 */
s16 atk_flash_get_capacity(u32 *capacity)
{
    s16 ret;

	if (!card_status) 
    {
		return FLASH_ERROR_INIT;
	}

    switch (nCardType)
    {
        case CARD_MMC:
            ret = mmc_get_capacity(capacity);
            break;
        case CARD_SD:
            ret = sd_get_capacity(capacity);
            break;
        default:
            return FLASH_ERROR_INIT;
            break;
    }

	if ( RET_SUCCESS != ret)
		return FLASH_FAILED;
		
	return RET_SUCCESS;
}

/*
 * Function to get the flash model
 * @param	[out] fmodel- the flash model
 * @param	[out] len		-the len
 * @return 	void
 */
void atk_flash_get_model(u8 *fmodel, u32 *len)
{
	u8 au8MMCModelStr[] = "MMC";
    u8 au8SDModelStr[] = "SD";
    u8 *pu8Mode = NULL;
    u8 u8Len = 0;
	int i;

    switch (nCardType)
    {
        case CARD_MMC:
            pu8Mode = au8MMCModelStr;
            u8Len = sizeof(au8MMCModelStr);
            break;
        case CARD_SD:
            pu8Mode = au8SDModelStr;
            u8Len = sizeof(au8SDModelStr);
            break;
        default:
            break;
    }

	for (i = 0; i < u8Len; ++i)
		fmodel[i] =  pu8Mode[i];

	*len = (u8Len > 1) ? (u8Len - 1) : 0;
}
