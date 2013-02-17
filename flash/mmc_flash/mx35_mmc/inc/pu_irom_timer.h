#ifndef PU_IROM_TIMER_H
#define PU_IROM_TIMER_H
/*==================================================================================================
                                                                               
     Header Name: pu_irom_timer.h

     General Description: define GPT register structure and function prototype
 
====================================================================================================

                         Copyright: 2005, 2006 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a 
              Freescale Software License Agreement, which has either 
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.   

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Lucky Sharma                 30/Nov/2006    TLSbo85012   Remove MDOC delay function reference
Lucky Sharma                 03/Nov/2006    TLSbo64654   Add OneNAND support to Zappa
Lucky Sharma                 20/Sep/2006    TLSbo78578   Merged CR TLSbo76123 for zappa
Lucky Sharma                 21/Aug/2006    TLSbo76123   GPT init be 2 step process, disable before programming clock source
Jeethendra Telagu            09/14/2005     TLSbo54020   Added prototype for generating general purpose delay
Edward Zhang                 05/12/2005     DSPhl24617   Add GPT for MDOC support, initial check in

====================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include "Common.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* GPT controller register bits definition*/
#define GPT_ENABLE                0x00000001
#define GPT_MODE_RESET_COUNTER    0x00000002
#define GPT_32K_CLOCK_SELECT      0x00000100
/* Output compare channel 1 Flag */
#define GPT_OF1                   0x00000001
#define GPT_OF_ALL_EVENTS         0x0000003F

/* Define  GPT initial configuration */
#define GPT_INIT                  GPT_MODE_RESET_COUNTER | GPT_32K_CLOCK_SELECT
 
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
   typedef struct 
   {
      UINT32 gptcr;
      UINT32 gptpr;
      UINT32 gptsr;
      UINT32 gptir;
      UINT32 gptocr1;
      UINT32 gptocr2;
      UINT32 gptocr3;
      UINT32 gpticr1;
      UINT32 gpticr2;
      UINT32 gptcnt;
     
   }GPT_PERIPH_T;


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
extern void GPT_MDOC_delay(void);
extern void GPT_reset_delay(UINT32);
extern void GPT_delay(UINT32 delay);
extern BOOL GPT_status(void);
extern void GPT_disable(void);
/*================================================================================================*/


#endif
