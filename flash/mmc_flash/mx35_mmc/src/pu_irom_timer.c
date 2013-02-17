/*==================================================================================================
                                                                               
    Module Name:  pu_irom_timer.c

    General Description: General Purpose timer function

====================================================================================================

                         Copyright: 2004,2005, 2006,2007 FREESCALE, INC.
              All Rights Reserved. This file contains copyrighted material.
              Use of this file is restricted by the provisions of a 
              Freescale Software License Agreement, which has either 
              accompanied the delivery of this software in shrink wrap
              form or been expressly executed between the parties.

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Prabhat Singh                  16/08/2007       TLSbo95392  Modified GPT_reset_delay function 
Lucky Sharma                 30/Nov/2006    TLSbo85012   Remove MDOC delay code 
Lucky Sharma                 03/Nov/2006    TLSbo64654   Add OneNAND support to Zappa ROM
Lucky Sharma                 20/Sep/2006    TLSbo78578   Merged following two CRs TLSbo76123 and TLSbo74352 for zappa
Lucky Sharma                 21/Aug/2006    TLSbo76123   GPT init be 2 step proc
ess, disable before programming clock source

Lucky Sharma                 03/Aug/2006    TLSbo74352   Changed the delay value for MDOC boot to 13ms 
Jeethendra Telagu            08/30/2005     TLSbo54020   Added function used to generate user specified 
                                                         delay 
Edward Zhang                 05/09/2005     DSPhl24617   Initial check in 
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "pu_irom_timer.h"

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/
volatile GPT_PERIPH_T *gpt_mcu = 0x53f90000;
                                                      
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/


/*=================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                     LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
FUNCTION:    GPT_reset_delay
DESCRIPTION:
    Generate the required delay required for device out of reset

ARGUMENTS PASSED:
   UINT32 

RETURN VALUE:
   None

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

IMPORTANT NOTES:
   -- The GPT takes a 32K Hz input clock, that limits the resolution to 1/32k = 31.25
           microseconds.
   -- The function overhead is estimated to cause an additional 2 microseconds delay,
           assuming the CPU is at 100M Hz, and AHB bus is at 25 M Hz.

==================================================================================================*/


void
GPT_reset_delay(UINT32 delay_time)
{
    /* Program the required delay in the Output Comparator Register */
    gpt_mcu->gptocr1 = delay_time;

    /* clear all event flags */
    gpt_mcu->gptsr = GPT_OF_ALL_EVENTS;

       /* Disable the timer */
    gpt_mcu->gptcr &= ~GPT_ENABLE;
	   
    /*  Start the timer */
    gpt_mcu->gptcr = GPT_INIT;
	
    /*  Enable the timer after programming for clock source select bits above */
    gpt_mcu->gptcr |= GPT_ENABLE;

    /* Loop until it counts up to the compared value */
    while(!(gpt_mcu->gptsr & GPT_OF1) );

    /* Disable the timer */
    gpt_mcu->gptcr &= ~GPT_ENABLE;

    return;
}


/*==================================================================================================
FUNCTION:    GPT_delay
DESCRIPTION:
	generates delay depending on the input parameter

ARGUMENTS PASSED:
    delay counter

RETURN VALUE:
   None

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None

IMPORTANT NOTES:
   -- The GPT takes a 32K Hz input clock, that limits the resolution to 1/32k = 31.25
           microseconds.
   -- The function overhead is estimated to cause an additional 2 microseconds delay,
           assuming the CPU is at 100M Hz, and AHB bus is at 25 M Hz.

==================================================================================================*/
void
GPT_delay(UINT32 delay)
{
    gpt_mcu->gptocr1 = delay;

    /* clear all event flags */
    gpt_mcu->gptsr = GPT_OF_ALL_EVENTS;

    /*  Disable the timer before programming for clock source select bits below */
    gpt_mcu->gptcr &= ~GPT_ENABLE;

    /*  Start the timer */
    gpt_mcu->gptcr = GPT_INIT;

    /*  Enable the timer after programming for clock source select bits above */
    gpt_mcu->gptcr |= GPT_ENABLE;

    return;
}

/*==================================================================================================
FUNCTION:    GPT_Status
DESCRIPTION:
        returns the timer status and disable the timer if the timer is expired

ARGUMENTS PASSED:
         None

RETURN VALUE:
   returns True if timer has expired

PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None


==================================================================================================*/

BOOL GPT_status(void)
{
  BOOL status = FALSE;
  if(gpt_mcu->gptsr & GPT_OF1)
  {
       status = TRUE;
  }
   return(status);
}


/*==================================================================================================
FUNCTION:    GPT_disable
DESCRIPTION:
        Disable the GPT timer

ARGUMENTS PASSED:
         None

RETURN VALUE:
         None 
PRE-CONDITIONS:
   None

POST-CONDITIONS:
   None


==================================================================================================*/

void GPT_disable(void)
{
     /* Disable the timer */
       gpt_mcu->gptcr &= ~GPT_ENABLE;
}
