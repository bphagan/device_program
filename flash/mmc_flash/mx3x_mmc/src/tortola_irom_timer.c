/*****************************************************************************
** totola_irom_timer.c
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
 * @file totola_irom_timer.c
 *
 * @brief source code for the mmc card operation
 *
 * @ingroup 
 */
 /*================================================================================================
                                        INCLUDE FILES
 ================================================================================================*/
#include "tortola_irom_timer.h"
#include "tortola_registers.h"

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/
volatile GPT_PERIPH_T gpt1;

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/

                                                      
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


/*
 * generates delay depending on the input parameter
 */
void
GPT_delay(UINT32 delay)
{
    gpt1.gptocr1 = delay;

    /* clear all event flags */
    gpt1.gptsr = GPT_OF_ALL_EVENTS;

    /*  Disable the timer before programming for clock source select bits below */
    gpt1.gptcr &= ~GPT_ENABLE;

    /*  Start the timer */
    gpt1.gptcr = GPT_INIT;
    
    /*  Enable the timer after programming for clock source select bits above */
    gpt1.gptcr |= GPT_ENABLE;

    return;
}

/*!
 * returns the timer status and disable the timer if the timer is expired
 */

BOOL GPT_status(void)
{
    if(gpt1.gptsr & GPT_OF1)
    {
        return TRUE;
    }
    return FALSE;
}


/*!
 * Disable the GPT timer
 */

void GPT_disable(void)
{
     /* Disable the timer */
     gpt1.gptcr &= ~GPT_ENABLE;
}
