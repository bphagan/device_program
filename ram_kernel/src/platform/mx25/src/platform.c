/*****************************************************************************
** platform.c
**
** Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.
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
 * @file platform.c
 *
 * @brief the platform specific functions file
 *
 * @ingroup RAM Kernel
 */

/*****************************************************************************
* <Includes>
*****************************************************************************/
#include "type.h"
#include "platform.h"
#include "sys_mmu.h"
#include <string.h>

/*****************************************************************************
* <Macros>
*****************************************************************************/

/*****************************************************************************
* <Typedefs>
*****************************************************************************/

/*****************************************************************************
* <Global Variables>
*****************************************************************************/

/*****************************************************************************
* <Local Variables>
*****************************************************************************/

/*!
 * Function to reset the MX31
 */
void sys_reset(void)
{
	u16 wdog_conf;
	wdog_conf = (*(volatile u16*)(WDOG_WCR) | 0x1000) & ~0x0018;
	*(volatile u16*)(WDOG_WCR) = wdog_conf;
	wdog_conf |= 0x4;
	*(volatile u16*)(WDOG_WCR) = wdog_conf;
	
	while(1);
	return;
}

u8 sys_get_chip_id(void)
{
	return MX25;
}
u32 __attribute__ ((aligned(0x4000))) ttb[0x1000];

static void __sys_mmu_init(void)
{
	u32 ttb_base = (u32)&ttb[0];
	u32 i;
	
	asm volatile ("mov r0, #0");
	asm volatile ("mcr 15, 0, r0, c7, c7, 0");        /* invalidate I cache and D cache */
	asm volatile ("mcr 15, 0, r0, c8, c7, 0");       /* invalidate TLBs */
	asm volatile ("mcr 15, 0, r0, c7, c10, 4");       /* Drain the write buffer */

	/*
	 * Set the TTB register
	*/
	asm volatile ("mcr  p15,0,%0,c2,c0,0" : : "r"(ttb_base) /*:*/);

	/*
	 * Set the Domain Access Control Register
	 */
	i = ARM_ACCESS_DACR_DEFAULT;
	asm volatile ("mcr  p15,0,%0,c3,c0,0" : : "r"(i) /*:*/);

	/*
	 * First clear all TT entries - ie Set them to Faulting
	 */
	memset((void *)ttb_base, 0, ARM_FIRST_LEVEL_PAGE_TABLE_SIZE);

	/*       Actual   Virtual  Size Attributes 			   */
	/*       Base     Base     MB  cached? buffered? access permissions*/
	/*      xxx00000  xxx00000                                         */
		    
	MMU_SECTION(0x400, 0x400,   0x400, 
	            ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	            
	MMU_SECTION(0x800, 0x800,   0x200, 
		    ARM_CACHEABLE, ARM_BUFFERABLE, ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0xB00, 0xB00,   0x020,  
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0xB20, 0xB20,   0x1E0, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	
    	/* Enable MMU */
    	asm volatile ("mrc p15, 0, r1, c1, c0");
    	
    	/* enable MMU bit */
    	asm volatile ("orr r1, r1, #7");
    	            	
    	asm volatile ("mcr p15, 0, r1, c1, c0");

    	asm volatile ("nop");
    	asm volatile ("nop");
   	asm volatile ("nop");
}

static void __sys_clock_init(void)
{

}

void sys_init(void)
{
	/* do sys clock init in case 
	   ROM code not have the best
	   configuration of clock */ 
	__sys_clock_init();
	
	/* enable mmu + cache for the
	   better performance */
	__sys_mmu_init();	
}
