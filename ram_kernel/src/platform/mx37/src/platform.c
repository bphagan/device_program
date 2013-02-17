/*****************************************************************************
** platform.c
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
 * Function to reset the MX37
 */
void sys_reset(void)
{
	u16 wdog_conf;
	
	wdog_conf = (__REG16(WDOG_WCR) | 0x1000) & ~0x0018;
	__REG16(WDOG_WCR) = wdog_conf;
	
	wdog_conf |= 0x4;
	__REG32(WDOG_WCR) = wdog_conf;
	
	while(1);
	return;
}

u8 sys_get_chip_id(void)
{
	return MX37;
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

	/* Also setup the Peripheral Port Remap register inside the core */
	asm volatile ("mov r0, #0x80000016");
	asm volatile ("mcr p15, 0, r0, c15, c2, 4");

	/*** L2 Cache setup/invalidation/disable ***/
	/* Disable L2 cache first */
	asm volatile ("mov r0, #0xB0000000");
	asm volatile ("mov r2, #0");
	asm volatile ("str r2, [r0, #0x100]");
	/*
	 * Configure L2 Cache:
	 * - 128k size(16k way)
	 * - 8-way associativity
	 * - 0 ws TAG/VALID/DIRTY
	 * - 4 ws DATA R/W
	 */
	asm volatile ("mov r2, #0xFF000000");
	asm volatile ("add r2, r2, #0x00F00000");
	asm volatile ("ldr r1, [r0, #0x104]");
	asm volatile ("and r1, r1, r2");
	asm volatile ("mov r2, #0x00030000");
	asm volatile ("add r2, r2, #0x0000001B");
	asm volatile ("orr r1, r1, r2");
	asm volatile ("str r1, [r0, #0x104]");

    	/* Invalidate L2 */
	asm volatile ("mov r1, #0xFF");
	asm volatile ("str r1, [r0, #0x77C]");
	asm volatile ("L2_loop:");
	/* Poll Invalidate By Way register */
	asm volatile ("ldr r2, [r0, #0x77C]");
	asm volatile ("ands r2, r2, #0xFF");
	asm volatile ("bne L2_loop");
	/*** End of L2 operations ***/

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
	
	MMU_SECTION(0x000, 0x000,   0x200, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0x100, 0x100,   0x001, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	            
	MMU_SECTION(0x400, 0x400,   0x080, 
		    ARM_CACHEABLE, ARM_BUFFERABLE, ARM_ACCESS_PERM_RW_RW);

	MMU_SECTION(0x7ff, 0x7ff,   0x001, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	/* SDRAM */	    
	MMU_SECTION(0x800, 0x800,   0x020, 
		    ARM_UNCACHEABLE,   ARM_UNBUFFERABLE,   ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0x900, 0x900,   0x100, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW); 
		    
	MMU_SECTION(0xB00, 0xB00,   0x400,  
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	
    	/* Enable MMU */
    	asm volatile ("mrc p15, 0, r1, c1, c0");
    	
    	/* enable MMU bit */
    	asm volatile ("orr r1, r1, #7");
    	
	/* enable z bit */
    	asm volatile ("orr r1, r1, #0x800");
    	            	
    	asm volatile ("mcr p15, 0, r1, c1, c0");
    	
    	/* enable d-cache */
	asm volatile ("mrc p15, 0, r0, c1, c0, 1");
	asm volatile ("orr r0, r0, #0x2");            
	asm volatile ("mcr p15, 0, r0, c1, c0, 1");

	/* enable i-cache */
	asm volatile ("mrc p15, 0, r1, c1, c0, 0");
	asm volatile ("orr r1, r1, #0x1000");
	
	/* enable ICache (also ensures   */
	/* that MMU and alignment faults */
	/* are enabled) */
	asm volatile ("orr r1, r1, #0x0003");  
                                                  
	asm volatile ("mcr p15, 0, r1, c1, c0, 0");

    	asm volatile ("nop");
    	asm volatile ("nop");
   	asm volatile ("nop");
}

static void __sys_clock_init(void)
{
	/* Setup PLL */
	__REG32(0xE3F80004) = 0x00000000;
	__REG32(0xE3F84004) = 0x00000000;
	__REG32(0xE3F88004) = 0x00000000;
	
	__REG32(0xE3F80000) = 0x00001222;
	__REG32(0xE3F80008) = 0x00000050;
	__REG32(0xE3F8000C) = 500000;
	__REG32(0xE3F80010) = 270833;
	
	__REG32(0xE3F84000) = 0x00001222;
	__REG32(0xE3F84008) = 0x00000060;
	__REG32(0xE3F8400C) = 1000000;
	__REG32(0xE3F84010) = 927083;
	
	__REG32(0xE3F88000) = 0x00000222;
	__REG32(0xE3F88008) = 0x00000091;
	__REG32(0xE3F8800C) = 0x00000000;
	__REG32(0xE3F88010) = 0x00000000;
	
	
	//Step 1: Switch to step clock
	__REG32(0xE3F8C00C) = 0x00000104;
	__REG32(0xE3F80000) = 0x00001232;
	__REG32(0xE3F88000) = 0x00000232;
	__REG32(0xE3F8C02C) = 0x0000001c;
	__REG32(0xE3F8C004) = 0x00000001;
	__REG32(0xE3F8C00C) = 0x00000100;
	__REG32(0xE3F8C030) = 0x00000800;
	
	__REG32(0xE3F84000) = 0x00001232;
	__REG32(0xE3F8C030) = 0x00001800;
	
	__REG32(0xE3F80004) = 0x00000002;
	__REG32(0xE3F84004) = 0x00000002;
	__REG32(0xE3F88004) = 0x00000002;
	__REG32(0xb0404018) = 0x77713;

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
