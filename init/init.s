/*****************************************************************************
** init.s
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
 * @file init.s
 *
 * @brief the start up code for the ram kernel
 *
 * @ingroup flash
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
 
.section .init, "x"

.global Begin

Begin:
	/* clear the bss section*/
	ldr	r0, _bss_start		
	ldr	r1, _bss_end		
	mov	r2, #0x00000000			

clbss_l:str	r2, [r0]		
	add	r0, r0, #4
	cmp	r0, r1
	bne	clbss_l	
	
	/* set up the stack*/
	ldr sp, _top_of_stacks

	/* jump to main function*/
	BL       main 

.global _top_of_stacks
_top_of_stacks:    
.word    __bss_end__  + 0x400000

.globl _bss_start
_bss_start:
	.word __bss_start__

.globl _bss_end
_bss_end:
	.word __bss_end__	

