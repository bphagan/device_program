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
 * Function to reset the MX53
 */
void sys_reset(void)
{
	u16 wdog_conf;
	
	wdog_conf = (__REG16(WDOG_WCR) | 0x1000) & ~0x0018;
	__REG16(WDOG_WCR) = wdog_conf;
	
	wdog_conf |= 0x4;
	__REG16(WDOG_WCR) = wdog_conf;
	
	while(1);
	
	return;
}

u8 sys_get_chip_id(void)
{
	return MX53;
}

u32 __attribute__ ((aligned(0x4000))) ttb[0x1000];

static void __sys_mmu_init(void)
{
	u32 ttb_base = (u32)&ttb[0];
	u32 i;
	
	asm volatile ("mrc 15, 0, r0, c1, c0, 1");
    	asm volatile ("bic r0, r0, #0x2");
    	asm volatile ("mcr 15, 0, r0, c1, c0, 1");

	/* explicitly disable L2 cache */
    	/* reconfigure L2 cache aux control reg */
    	/* tag RAM */
    	asm volatile ("mov r0, #0xC0");
	    
	/* data RAM */             
   	asm volatile ("add r0, r0, #0x4");
    	
    	/* disable write allocate delay */
    	asm volatile ("orr r0, r0, #(1 << 24)");
	
	/* disable write allocate combine */
    	asm volatile ("orr r0, r0, #(1 << 23)");
	
	/* disable write allocate */     
    	asm volatile ("orr r0, r0, #(1 << 22)");
	
	/* disable write combine for TO 2 and lower revs */
        asm volatile ("orr r0, r0, #(1 << 25)");      

    	asm volatile ("mcr 15, 1, r0, c9, c0, 2");

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
	
	MMU_SECTION(0x000, 0x000,   0x010, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
		     
	MMU_SECTION(0x070, 0x070,   0x010,
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0x100, 0x100,   0x040,
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
        
        MMU_SECTION(0x400, 0x400,   0x300,
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW);
	
	/* SDRAM */	    
	MMU_SECTION(0x700, 0x700,   0x400, 
		    ARM_CACHEABLE,   ARM_BUFFERABLE,   ARM_ACCESS_PERM_RW_RW);
		    
        MMU_SECTION(0xB00, 0xB00,   0x400, 
		    ARM_CACHEABLE,   ARM_BUFFERABLE,   ARM_ACCESS_PERM_RW_RW);
		    
	MMU_SECTION(0xF00, 0xF00,   0x100, 
		    ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW); 

	/* Workaround for arm errata #709718 */
    	/* Setup PRRR so device is always mapped to non-shared */
    	/* Read Primary Region Remap Register */
   	asm volatile ("mrc p15, 0, r1, c10, c2, 0"); 
    	asm volatile ("bic r1, #(3 << 16)");
    	
    	/* Write Primary Region Remap Register */
    	asm volatile ("mcr p15, 0, r1, c10, c2, 0"); 

    	/* Enable MMU */
    	asm volatile ("mrc p15, 0, r1, c1, c0");
    	
    	/* enable MMU bit */
    	asm volatile ("orr r1, r1, #7");
    	
	/* enable z bit */
    	asm volatile ("orr r1, r1, #0x800");
    	
	/* Enable TEX remap */                  
    	asm volatile ("orr r1, r1, #(1 << 28)");              	
    	asm volatile ("mcr p15, 0, r1, c1, c0");

    	/* Workaround for arm errata #621766 */
    	asm volatile ("mrc p15, 0, r1, c1, c0, 1");
    	
    	/* enable L1NEON bit */
    	asm volatile ("orr r1, r1, #(1 << 5)");              
    	asm volatile ("mcr p15, 0, r1, c1, c0, 1");
    	
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
	/* for better performance, user can add code here
	 * to configure the CPU CLK/NFC CLK/DDR CLK...
	 * For the sake of stable is better than performance
	 * ATK will use the safe configuration for considering
	 * different board will have different DDR issue.
	 */   

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
