#ifndef SERIAL_DOWNLOADER_H
#define SERIAL_DOWNLOADER_H  

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                                                               
     Header Name: serial_downloader.h

     General Description: Serial Downloader header file 
 
====================================================================================================
    Copyright (C) 2006, Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.
   

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Bharat Bhushan               28/06/2006     TLSbo72164   Defines For buffer Address moved to other file.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).

====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
                                      FUNCTION PROTOTYPES
==================================================================================================*/

#include "su_basictypes.h"
#include "usb_common.h"
	
extern void serial_downloader_usb(void);
extern void serial_downloader_uart(void);

#ifdef __cplusplus
}
#endif /* extern C++ */

#endif /* SERIAL_DOWNLOADER_H */
