/*****************************************************************************
** flash_lib.c
**
** Copyright 2010 Freescale Semiconductor, Inc. All Rights Reserved.
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
#include "protocol.h"
#include "flash_lib.h"
#include "mmc.h"

struct mmc *mmc;

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
	
	ret = mmc_initialize(&mmc);
	
	if ( RET_SUCCESS == ret) {
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
	
        int blklen, startblk, endblk;
        
        if (!mmc)
                return FLASH_ERROR_INIT;
                               
        blklen = mmc->read_bl_len;
	startblk = offset / mmc->read_bl_len;	
	endblk = (offset + size - 1) / mmc->read_bl_len;
	
        mmc_init(mmc);
        ret = mmc_erase(0, startblk, endblk);
                
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
s16 atk_flash_lib_read(u32 offset, u8 *buffer, u32 count, dump_callback callback, u32 bufsize)
{
        s16 ret;
        int blklen, startblk;
        int blkcnt, endblk;
        
        if (!mmc)
                return FLASH_ERROR_INIT;
                               
        blklen = mmc->read_bl_len;
        
	startblk = offset / mmc->read_bl_len;	
	endblk = (offset + count - 1) / mmc->read_bl_len;
	blkcnt = endblk - startblk + 1;
	
        mmc_init(mmc);		
        ret =  mmc->block_dev.block_read(0, startblk, blkcnt, buffer);
         
	if (blkcnt != ret)
	       return FLASH_ERROR_READ;
               	
        if (callback) {
                s16 csum;
                csum = calculate_checksum(buffer, count);
                callback(buffer, FLASH_PARTLY, csum, count);
        }
                      
        return RET_SUCCESS;        
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
	int blklen, startblk;
        int blkcnt, endblk;
        
        if (!mmc)        
                return FLASH_ERROR_INIT;

        blklen = mmc->read_bl_len;
	startblk = offset / mmc->read_bl_len;
	endblk = (offset + *pcount - 1) / mmc->read_bl_len;
	blkcnt = endblk - startblk + 1;
	
	mmc_init(mmc);
        
        ret = mmc->block_dev.block_write(0, startblk, blkcnt, buffer);
          
	if (blkcnt != ret)
                return FLASH_ERROR_PROG;
        
        if (callback)
                callback(FLASH_PARTLY, offset, *pcount);        
					
	if (mode) {
                ret = mmc->block_dev.block_read(0, startblk, blkcnt, buffer);
                
                if (blkcnt != ret)
                        return FLASH_ERROR_VERIFY;
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

        if (!mmc) 
                return FLASH_ERROR_INIT;
                
        *capacity = mmc->capacity >> 10;
		
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

        if (IS_SD(mmc)) {
                pu8Mode = au8SDModelStr;
                u8Len = sizeof(au8SDModelStr);
        } else {
                pu8Mode = au8MMCModelStr;
                u8Len = sizeof(au8MMCModelStr);
        }

	for (i = 0; i < u8Len; ++i)
		fmodel[i] =  pu8Mode[i];

	*len = (u8Len > 1) ? (u8Len - 1) : 0;
}
