#ifndef TORTOLA_IROM_TIMER_H
#define TORTOLA_IROM_TIMER_H
/*==================================================================================================
                                                                               
     Header Name: tortola_irom_timer.h

     General Description: define GPT register structure and function prototype
 
====================================================================================================

                         Copyright: 2005 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a 
              Freescale Software License Agreement, which has either 
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.   

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Mahima Verma                15.06.2006      TLSbo58037   Added for Multiple Nand Flash support(BONO 2.0)
Mahima Verma                01.12.2006      TLSbo52480   Added GPT for Multiple nand flash (Ported from BONO 2.0 to i.MX32)

====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Common.h"
//#include "su_basictypes.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* GPT controller register bits definition*/
#define GPT_ENABLE                0x00000001
#define GPT_COUNTER_CLEAR         0x00000002
#define GPT_32K_CLOCK_SELECT      0x00000100

/* Output compare channel 1 Flag */
#define GPT_OF1                   0x00000001
#define GPT_OF_ALL_EVENTS         0x0000003F

/* Define  GPT initial configuration */
#define GPT_INIT                  GPT_COUNTER_CLEAR | GPT_32K_CLOCK_SELECT
 
/*The GPT refrence clock is 32K Hz, and the required delay is 3 milliseconds, so the GPT Output
  Comparator should have a value : 3 *32 = 96
*/
#define NAND_FLASH_OPER_TIMEOUT  96
 

/*==================================================================================================
                                            MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
extern void GPT_delay(UINT32 delay);
extern BOOL GPT_status(void);
extern void GPT_disable(void);
/*================================================================================================*/


#endif
