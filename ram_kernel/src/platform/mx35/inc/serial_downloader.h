#ifndef SERIAL_DOWNLOADER_H
#define SERIAL_DOWNLOADER_H  

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                                                               
     Header Name: serial_downloader.h

     General Description: Serial Downloader header file 
 
====================================================================================================
Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.

This file contains copyrighted material. Use of this file is
restricted by the provisions of a Freescale Software License
Agreement, which has either been electronically accepted by
you or has been expressly executed between the parties.
   

Revision History:
====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
                                      FUNCTION PROTOTYPES
==================================================================================================*/

#include "su_basictypes.h"
#include "usb_common.h"
	
extern void serial_downloader_usb(void);

#ifdef __cplusplus
}
#endif /* extern C++ */

#endif /* SERIAL_DOWNLOADER_H */
