//############################################################################  
//#                                                                            
//#                    Tortola specific memory map                     
//#                     Motorola Confidential Proprietary                      
//# Purpose:                                                                   
//#   This file is used by the ARM GAS, ARM GCC and verilog Simulator    
//#        to decode the memory map                                                                      
//# Description                                                                
//#   This file list out each individual memory location for decoding          
//#                                                                            
//# Initial version writen By                                                  
//#   Shiri Earon  (shiri.earon@motorola.com) SPS                              
//#                                                                            
//# Date                                                                       
//# 27 Mar 2003                                                                
//#                                                                            
//# Revisions                                                                  
//#                                                                            
//############################################################################  
  
#include "iomuxc_mem_map.h" 
  
#define BASE0		0xC0000000
#define BASE1		0xD0000000
#define BASE2		0xE0000000
#define BASE3		0xF0000000


#define TARGETBOARD0 BASE0
#define TARGETBOARD1 BASE0
  
  
  
  
//#########################################  
//# BOOT ROM                              #  
//# $0000_0000 to $0000_3FFF              #  
//#########################################  
#define BOOTROM1_ADDR_BOT 0x00000000 //  boot rom section 1 bottom address
#define BOOTROM1_PHY_SIZE 0x00008000 //  boot rom section 1 physical size
#define BOOTROM1_ASS_SIZE 0x00004000 //  boot rom section 1 assigned size
  
  
  
  
  
//#########################################  
//# AIPS1                                 #  
//# $43F0_0000 to $43F0_3FFF              #  
//#########################################  
#define AIPS1_BASE_ADDR 0x43F00000 
#define AIPS1_MPROT0_7 (AIPS1_BASE_ADDR+0x00) //  32bit Peripheral Size Reg 0
#define AIPS1_MPROT8_15 (AIPS1_BASE_ADDR+0x04) //  32bit Peripheral Size Reg 1
#define AIPS1_PACR0_7 (AIPS1_BASE_ADDR+0x20) //  32bit Peripheral Access Reg
#define AIPS1_PACR8_15 (AIPS1_BASE_ADDR+0x24) //  32bit Peripheral Access Reg
#define AIPS1_PACR16_23 (AIPS1_BASE_ADDR+0x28) //  32bit Peripheral Access Reg
#define AIPS1_PACR24_31 (AIPS1_BASE_ADDR+0x2C) //  32bit Peripheral Access Reg
#define AIPS1_OPACR0_7 (AIPS1_BASE_ADDR+0x40) //  32bit Peripheral Access Reg
#define AIPS1_OPACR8_15 (AIPS1_BASE_ADDR+0x44) //  32bit Peripheral Access Reg
#define AIPS1_OPACR16_23 (AIPS1_BASE_ADDR+0x48) //  32bit Peripheral Access Reg
#define AIPS1_OPACR24_31 (AIPS1_BASE_ADDR+0x4C) //  32bit Peripheral Access Reg
#define AIPS1_OPACR32_33 (AIPS1_BASE_ADDR+0x50) //  32bit Peripheral Access Reg
  
//#########################################  
//# AIPS Generic   
//# relative addresses            
//#########################################  
  
#define AIPS_MPROT0_7 0x00 //  32bit Peripheral Size Reg 0
#define AIPS_MPROT8_15 0x04 //  32bit Peripheral Size Reg 1
#define AIPS_PACR0_7 0x20 //  32bit Peripheral Access Reg
#define AIPS_PACR8_15 0x24 //  32bit Peripheral Access Reg
#define AIPS_PACR16_23 0x28 //  32bit Peripheral Access Reg
#define AIPS_PACR24_31 0x2C //  32bit Peripheral Access Reg
#define AIPS_OPACR0_7 0x40 //  32bit Peripheral Access Reg
#define AIPS_OPACR8_15 0x44 //  32bit Peripheral Access Reg
#define AIPS_OPACR16_23 0x48 //  32bit Peripheral Access Reg
#define AIPS_OPACR24_31 0x4C //  32bit Peripheral Access Reg
#define AIPS_OPACR32_33 0x50 //  32bit Peripheral Access Reg
  
  
  
  
  
  
  
//#########################################  
//# WDOG                                  #  
//# $53FD_C000 to $53FD_FFFF              #  
//#########################################  
#define WDOG_BASE_ADDR 0x53FDC000 
#define WDOG_WCR (WDOG_BASE_ADDR+0x00) //  16bit watchdog control reg
#define WDOG_WSR (WDOG_BASE_ADDR+0x02) //  16bit watchdog service reg
#define WDOG_WRSR (WDOG_BASE_ADDR+0x04) //  16bit watchdog reset status reg
  
//#########################################  
//# GPT  
//# $53F9_0000 to $53F9_3FFF              #  
//#########################################  
#define GPT_BASE_ADDR 0x53F90000 
#define GPT_GPTCR (GPT_BASE_ADDR+0x00) //  32bit timer 1 control reg
#define GPT_GPTPR (GPT_BASE_ADDR+0x04) //  32bit timer 1 prescaler reg
#define GPT_GPTSR (GPT_BASE_ADDR+0x08) //  32bit timer 1 compare reg
#define GPT_GPTIR (GPT_BASE_ADDR+0x0C) //  32bit timer 1 capture reg
#define GPT_GPTOCR1 (GPT_BASE_ADDR+0x10) //  32bit timer 1 counter reg
#define GPT_GPTOCR2 (GPT_BASE_ADDR+0x14) //  32bit timer 1 status reg
#define GPT_GPTOCR3 (GPT_BASE_ADDR+0x18) 
#define GPT_GPTICR1 (GPT_BASE_ADDR+0x1C) 
#define GPT_GPTICR2 (GPT_BASE_ADDR+0x20) 
#define GPT_GPTCNT (GPT_BASE_ADDR+0x24) 
//#########################################  
//# EPIT1                                  #  
//# $53F9_4000 to $53F9_7FFF              #  
//#########################################  
#define EPIT1_BASE_ADDR 0x53F94000 
#define EPIT1_EPITCR (EPIT1_BASE_ADDR+0x00) //  32bit timer 2 control reg
#define EPIT1_EPITSR (EPIT1_BASE_ADDR+0x04) //  32bit timer 2 prescaler reg
#define EPIT1_EPITLR (EPIT1_BASE_ADDR+0x08) //  32bit timer 2 compare reg
#define EPIT1_EPITCMPR (EPIT1_BASE_ADDR+0x0C) //  32bit timer 2 capture reg
#define EPIT1_EPITCNR (EPIT1_BASE_ADDR+0x10) //  32bit timer 2 counter reg
  
//#########################################  
//# EPIT2                                  #  
//# $53F9_8000 to $53F9_BFFF              #  
//#########################################  
#define EPIT2_BASE_ADDR 0x53F98000 
#define EPIT2_EPITCR (EPIT2_BASE_ADDR+0x00) //  32bit timer 3 control reg
#define EPIT2_EPITSR (EPIT2_BASE_ADDR+0x04) //  32bit timer 3 prescaler reg
#define EPIT2_EPITLR (EPIT2_BASE_ADDR+0x08) //  32bit timer 3 compare reg
#define EPIT2_EPITCMPR (EPIT2_BASE_ADDR+0x0C) //  32bit timer 3 capture reg
#define EPIT2_EPITCNR (EPIT2_BASE_ADDR+0x10) //  32bit timer 3 counter reg
  
//#########################################  
//# EPIT generic   
//# relative addresses  
//#########################################  
  
#define EPIT_EPITCR 0x00 //  32bit timer 3 control reg
#define EPIT_EPITSR 0x04 //  32bit timer 3 prescaler reg
#define EPIT_EPITLR 0x08 //  32bit timer 3 compare reg
#define EPIT_EPITCMPR 0x0C //  32bit timer 3 capture reg
#define EPIT_EPITCNR 0x10 //  32bit timer 3 counter reg
  
//#########################################  
//# PWM                                   #  
//# $53FE_0000 to $53FE_3FFF              #  
//#########################################  
#define PWM_BASE_ADDR 0x53FE0000 
#define PWM_PWMCR (PWM_BASE_ADDR+0x00) //  32bit pwm control reg
#define PWM_PWMSR (PWM_BASE_ADDR+0x04) //  32bit pwm sample reg
#define PWM_PWMIR (PWM_BASE_ADDR+0x08) //  32bit pwm period reg
#define PWM_PWMSAR (PWM_BASE_ADDR+0x0C) //  32bit pwm counter reg
#define PWM_PWMPR (PWM_BASE_ADDR+0x10) //  32bit pwm test reg
#define PWM_PWMCNR (PWM_BASE_ADDR+0x14) 
  
//#########################################  
//# RTC                                   #  
//# $53FD_8000 to $53FD_BFFF              #  
//#########################################  
#define RTC_BASE_ADDR 0x53FD8000 
#define RTC_HOURMIN (RTC_BASE_ADDR+0x00) //  32bit rtc hour/min counter reg
#define RTC_SECOND (RTC_BASE_ADDR+0x04) //  32bit rtc seconds counter reg
#define RTC_ALRM_HM (RTC_BASE_ADDR+0x08) //  32bit rtc alarm hour/min reg
#define RTC_ALRM_SEC (RTC_BASE_ADDR+0x0C) //  32bit rtc alarm seconds reg
#define RTC_RTCCTL (RTC_BASE_ADDR+0x10) //  32bit rtc control reg
#define RTC_RTCISR (RTC_BASE_ADDR+0x14) //  32bit rtc interrupt status reg
#define RTC_RTCIENR (RTC_BASE_ADDR+0x18) //  32bit rtc interrupt enable reg
#define RTC_STPWCH (RTC_BASE_ADDR+0x1C) //  32bit rtc stopwatch min reg
#define RTC_DAYR (RTC_BASE_ADDR+0x20) //  32bit rtc days counter reg
#define RTC_DAYALARM (RTC_BASE_ADDR+0x24) //  32bit rtc day alarm reg
#define RTC_TEST1 (RTC_BASE_ADDR+0x28) //  32bit rtc test reg 1
#define RTC_TEST2 (RTC_BASE_ADDR+0x2C) //  32bit rtc test reg 2
#define RTC_TEST3 (RTC_BASE_ADDR+0x30) //  32bit rtc test reg 3
  
//#########################################  
//# KPP                                   #  
//# $43FA_8000 to $43FA_BFFF           #  
//#########################################  
#define KPP_BASE_ADDR 0x43FA8000 
#define KPP_KPCR (KPP_BASE_ADDR+0x00) //  16bit kpp keypad control reg
#define KPP_KPSR (KPP_BASE_ADDR+0x02) //  16bit kpp keypad status reg
#define KPP_KDDR (KPP_BASE_ADDR+0x04) //  16bit kpp keypad data directon reg
#define KPP_KPDR (KPP_BASE_ADDR+0x06) //  16bit kpp keypad data reg
  
  
  
  
//#########################################  
//# I2C1                                   #  
//# $43F8_0000 to $43F8_3FFF              #  
//#########################################  
#define I2C1_BASE_ADDR 0x43F80000 
#define I2C1_IADR (I2C1_BASE_ADDR+0x00) //  16bit i2c address reg
#define I2C1_IFDR (I2C1_BASE_ADDR+0x04) //  16bit i2c frequency divider reg
#define I2C1_I2CR (I2C1_BASE_ADDR+0x08) //  16bit i2c control reg
#define I2C1_I2SR (I2C1_BASE_ADDR+0x0C) //  16bit i2c status reg
#define I2C1_I2DR (I2C1_BASE_ADDR+0x10) //  16bit i2c data i/o reg

#ifdef FPGA
#define I2CBASE TARGETBOARD0+I2C_BASE
#else
#define I2CBASE I2C1_BASE_ADDR
#endif
  
//#########################################  
//# I2C generic  
//# relative addresses  
//#########################################  
  
#define I2C_IADR 0x00 //  16bit i2c address reg
#define I2C_IFDR 0x04 //  16bit i2c frequency divider reg
#define I2C_I2CR 0x08 //  16bit i2c control reg
#define I2C_I2SR 0x0C //  16bit i2c status reg
#define I2C_I2DR 0x10 //  16bit i2c data i/o reg
  
//#########################################  
//# AIPS2                                 #  
//# $43F0_0000 to $43F0_3FFF              #  
//#########################################  
#define AIPS2_BASE_ADDR 0x53F00000 
#define AIPS2_MPROT0_7 (AIPS2_BASE_ADDR+0x00) //  32bit Peripheral Size Reg 0
#define AIPS2_MPROT8_15 (AIPS2_BASE_ADDR+0x04) //  32bit Peripheral Size Reg 1
#define AIPS2_PACR0_7 (AIPS2_BASE_ADDR+0x20) //  32bit Peripheral Access Reg
#define AIPS2_PACR8_15 (AIPS2_BASE_ADDR+0x24) //  32bit Peripheral Access Reg
#define AIPS2_PACR16_23 (AIPS2_BASE_ADDR+0x28) //  32bit Peripheral Access Reg
#define AIPS2_PACR24_31 (AIPS2_BASE_ADDR+0x2C) //  32bit Peripheral Access Reg
#define AIPS2_OPACR0_7 (AIPS2_BASE_ADDR+0x40) //  32bit Peripheral Access Reg
#define AIPS2_OPACR8_15 (AIPS2_BASE_ADDR+0x44) //  32bit Peripheral Access Reg
#define AIPS2_OPACR16_23 (AIPS2_BASE_ADDR+0x48) //  32bit Peripheral Access Reg
#define AIPS2_OPACR24_31 (AIPS2_BASE_ADDR+0x4C) //  32bit Peripheral Access Reg
#define AIPS2_OPACR32_33 (AIPS2_BASE_ADDR+0x50) //  32bit Peripheral Access Reg
  
  
//#########################################  
//# Clock  Reset (CCM)                   #  
//# System control                        #  
//# $53F8_0000 to $53F8_3FFF              #  
//#########################################  
#define CCM_BASE_ADDR 0x53F80000 
#define CCM_CCMR (CCM_BASE_ADDR+0x00) //  32bit Clock Source Control Reg
#define CCM_PDR0 (CCM_BASE_ADDR+0x04) //  32bit MCU PLL Control Reg
#define CCM_PDR1 (CCM_BASE_ADDR+0x08) //  32bit MCU PLL Control Reg
#define CCM_RCSR (CCM_BASE_ADDR+0x0C) //  32bit MCU PLL Control Reg
#define CCM_MPCTL (CCM_BASE_ADDR+0x10) //  32bit Serial Perpheral PLL Ctrl 0
#define CCM_UPCTL (CCM_BASE_ADDR+0x14) //  32bit Serial Perpheral PLL Ctrl 1
#define CCM_SPCTL (CCM_BASE_ADDR+0x18) //  32bit Serial Perpheral PLL Ctrl 1
#define CCM_COSR (CCM_BASE_ADDR+0x1C) //  32bit Osc 26M register
#define CCM_CGR0 (CCM_BASE_ADDR+0x20) //  32bit Serial Perpheral Clk Div Reg
#define CCM_CGR1 (CCM_BASE_ADDR+0x24) //  32bit Perpheral Clk Control Reg 0
#define CCM_CGR2 (CCM_BASE_ADDR+0x28) //  32bit Perpheral Clk Control Reg 0
#define CCM_WIMR (CCM_BASE_ADDR+0x2C) //  32bit Wake-up Interrupt Mask Reg
#define CCM_LDC (CCM_BASE_ADDR+0x30) // 32bit Latch Divergence Counter Reg
#define CCM_DCVR0 (CCM_BASE_ADDR+0x34) // DPTC Comparator Value Reg 0
#define CCM_DCVR1 (CCM_BASE_ADDR+0x38) // DPTC Comparator Value Reg 1
#define CCM_DCVR2 (CCM_BASE_ADDR+0x3C) // DPTC Comparator Value Reg 2
#define CCM_DCVR3 (CCM_BASE_ADDR+0x40) // DPTC Comparator Value Reg 3
#define CCM_LTR0 (CCM_BASE_ADDR+0x44) // 32bit Load Tracking Reg 0
#define CCM_LTR1 (CCM_BASE_ADDR+0x48) // 32bit Load Tracking Reg 1
#define CCM_LTR2 (CCM_BASE_ADDR+0x4C) // 32bit Load Tracking Reg 2
#define CCM_LTR3 (CCM_BASE_ADDR+0x50) // 32bit Load Tracking Reg 3
#define CCM_LTBR0 (CCM_BASE_ADDR+0x54) // 32bit Load Tracking Buffer Reg 0
#define CCM_LTBR1 (CCM_BASE_ADDR+0x58) // 32bit Load Tracking Buffer Reg 1
#define CCM_PMCR0 (CCM_BASE_ADDR+0x5C) // 32bit Power Management Control Reg 0
#define CCM_PMCR1 (CCM_BASE_ADDR+0x60) // 32bit Power Management Control Reg 1
#define CCM_PDR2 (CCM_BASE_ADDR+0x64) //  32bit MCU PLL Control Reg
  
  
  
//#########################################  
//# FIRI                                  #  
//# $53F8_C000 to $53F8_FFFF              #  
//#########################################  
#define FIRI_BASE_ADDR 0x53F8C000 
#define FIRI_FIRITCR (FIRI_BASE_ADDR+0x00) //  32bit firi tx control reg 
#define FIRI_FIRITCTR (FIRI_BASE_ADDR+0x04) //  32bit firi tx count  reg
#define FIRI_FIRIRCR (FIRI_BASE_ADDR+0x08) //  32bit firi rx control reg
#define FIRI_FIRITSR (FIRI_BASE_ADDR+0x0C) //  32bit firi tx status reg
#define FIRI_FIRIRSR (FIRI_BASE_ADDR+0x10) //  32bit firi rx status reg
#define FIRI_TFIFO (FIRI_BASE_ADDR+0x14) //  32bit firi tx fifo reg
#define FIRI_RFIFO (FIRI_BASE_ADDR+0x18) //  32bit firi rx fifo reg
#define FIRI_FIRICR (FIRI_BASE_ADDR+0x1C) //  32bit firi control reg
  
  
  
  
  
//#########################################  
//# MAX                                   #  
//# $43F0_4000 to $43F0_7FFF               
//#########################################  
#define MAX_BASE_ADDR 0x43F04000 
#define MAX_SLV0_BASE (MAX_BASE_ADDR+0x000) //  base location for slave 0
#define MAX_SLV1_BASE (MAX_BASE_ADDR+0x100) //  base location for slave 1
#define MAX_SLV2_BASE (MAX_BASE_ADDR+0x200) //  base location for slave 2
#define MAX_SLV3_BASE (MAX_BASE_ADDR+0x300) //  base location for slave 3
#define MAX_SLV4_BASE (MAX_BASE_ADDR+0x400) //  base location for slave 3
#define MAX_SLV5_BASE (MAX_BASE_ADDR+0x500) //  base location for slave 3
#define MAX_SLV6_BASE (MAX_BASE_ADDR+0x600) //  base location for slave 3
#define MAX_SLV7_BASE (MAX_BASE_ADDR+0x700) //  base location for slave 3
  
#define MAX_SLV0_MPR0 (MAX_SLV0_BASE+0x00) //  32bit max slv0 master priority reg
#define MAX_SLV0_AMPR0 (MAX_SLV0_BASE+0x04) //  32bit max slv0 alt priority reg
#define MAX_SLV0_SGPCR0 (MAX_SLV0_BASE+0x10) //  32bit max slv0 general ctrl reg
#define MAX_SLV0_ASGPCR0 (MAX_SLV0_BASE+0x14) //  32bit max slv0 alt generl ctrl reg
  
#define MAX_SLV1_MPR1 (MAX_SLV1_BASE+0x00) //  32bit max slv1 master priority reg
#define MAX_SLV1_AMPR1 (MAX_SLV1_BASE+0x04) //  32bit max slv1 alt priority reg
#define MAX_SLV1_SGPCR1 (MAX_SLV1_BASE+0x10) //  32bit max slv1 general ctrl reg
#define MAX_SLV1_ASGPCR1 (MAX_SLV1_BASE+0x14) //  32bit max slv1 alt generl ctrl reg
  
#define MAX_SLV2_MPR2 (MAX_SLV2_BASE+0x00) //  32bit max slv2 master priority reg
#define MAX_SLV2_AMPR2 (MAX_SLV2_BASE+0x04) //  32bit max slv2 alt priority reg
#define MAX_SLV2_SGPCR2 (MAX_SLV2_BASE+0x10) //  32bit max slv2 general ctrl reg
#define MAX_SLV2_ASGPCR2 (MAX_SLV2_BASE+0x14) //  32bit max slv2 alt generl ctrl reg
  
#define MAX_SLV3_MPR3 (MAX_SLV3_BASE+0x00) //  32bit max slv3 master priority reg
#define MAX_SLV3_AMPR3 (MAX_SLV3_BASE+0x04) //  32bit max slv3 alt priority reg
#define MAX_SLV3_SGPCR3 (MAX_SLV3_BASE+0x10) //  32bit max slv3 general ctrl reg
#define MAX_SLV3_ASGPCR3 (MAX_SLV3_BASE+0x14) //  32bit max slv3 alt generl ctrl reg
  
#define MAX_SLV4_MPR4 (MAX_SLV4_BASE+0x00) //  32bit max slv3 master priority reg
#define MAX_SLV4_AMPR4 (MAX_SLV4_BASE+0x04) //  32bit max slv3 alt priority reg
#define MAX_SLV4_SGPCR4 (MAX_SLV4_BASE+0x10) //  32bit max slv3 general ctrl reg
#define MAX_SLV4_ASGPCR4 (MAX_SLV4_BASE+0x14) //  32bit max slv3 alt generl ctrl reg
  
#define MAX_SLV5_MPR5 (MAX_SLV5_BASE+0x00) //  32bit max slv3 master priority reg
#define MAX_SLV5_AMPR5 (MAX_SLV5_BASE+0x04) //  32bit max slv3 alt priority reg
#define MAX_SLV5_SGPCR5 (MAX_SLV5_BASE+0x10) //  32bit max slv3 general ctrl reg
#define MAX_SLV5_ASGPCR5 (MAX_SLV5_BASE+0x14) //  32bit max slv3 alt generl ctrl reg
  
#define MAX_SLV6_MPR6 (MAX_SLV6_BASE+0x00) //  32bit max slv3 master priority reg
#define MAX_SLV6_AMPR6 (MAX_SLV6_BASE+0x04) //  32bit max slv3 alt priority reg
#define MAX_SLV6_SGPCR6 (MAX_SLV6_BASE+0x10) //  32bit max slv3 general ctrl reg
#define MAX_SLV6_ASGPCR6 (MAX_SLV6_BASE+0x14) //  32bit max slv3 alt generl ctrl reg
  
#define MAX_SLV7_MPR7 (MAX_SLV7_BASE+0x00) //  32bit max slv3 master priority reg
#define MAX_SLV7_AMPR7 (MAX_SLV7_BASE+0x04) //  32bit max slv3 alt priority reg
#define MAX_SLV7_SGPCR7 (MAX_SLV7_BASE+0x10) //  32bit max slv3 general ctrl reg
#define MAX_SLV7_ASGPCR7 (MAX_SLV7_BASE+0x14) //  32bit max slv3 alt generl ctrl reg
  
#define MAX_MST0_MGPCR0 (MAX_BASE_ADDR+0x800) //  32bit max mst5 general ctrl reg
#define MAX_MST1_MGPCR1 (MAX_BASE_ADDR+0x900) //  32bit max mst5 general ctrl reg
#define MAX_MST2_MGPCR2 (MAX_BASE_ADDR+0xA00) //  32bit max mst5 general ctrl reg
#define MAX_MST3_MGPCR3 (MAX_BASE_ADDR+0xB00) //  32bit max mst5 general ctrl reg
#define MAX_MST4_MGPCR4 (MAX_BASE_ADDR+0xC00) //  32bit max mst5 general ctrl reg
#define MAX_MST5_MGPCR5 (MAX_BASE_ADDR+0xD00) //  32bit max mst5 general ctrl reg
#define MAX_MST6_MGPCR6 (MAX_BASE_ADDR+0xE00) //  32bit max mst5 general ctrl reg
#define MAX_MST7_MGPCR7 (MAX_BASE_ADDR+0xF00) //  32bit max mst5 general ctrl reg
  
  
  
  
  
//#########################################  
//# AVIC                                  #  
//# $6800_0000 to $6FFF_FFFF              #  
//#########################################  
#define AVIC_BASE_ADDR 0x68000000 
#define AVIC_INTCNTL (AVIC_BASE_ADDR+0x00) //  32bit AVIC int control reg
#define AVIC_NIMASK (AVIC_BASE_ADDR+0x04) //  32bit AVIC int mask reg
#define AVIC_INTENNUM (AVIC_BASE_ADDR+0x08) //  32bit AVIC int enable number reg
#define AVIC_INTDISNUM (AVIC_BASE_ADDR+0x0C) //  32bit AVIC int disable number reg
#define AVIC_INTENABLEH (AVIC_BASE_ADDR+0x10) //  32bit AVIC int enable reg high
#define AVIC_INTENABLEL (AVIC_BASE_ADDR+0x14) //  32bit AVIC int enable reg low
#define AVIC_INTTYPEH (AVIC_BASE_ADDR+0x18) //  32bit AVIC int type reg high
#define AVIC_INTTYPEL (AVIC_BASE_ADDR+0x1C) //  32bit AVIC int type reg low
#define AVIC_NIPRIORITY7 (AVIC_BASE_ADDR+0x20) //  32bit AVIC norm int priority lvl7
#define AVIC_NIPRIORITY6 (AVIC_BASE_ADDR+0x24) //  32bit AVIC norm int priority lvl6
#define AVIC_NIPRIORITY5 (AVIC_BASE_ADDR+0x28) //  32bit AVIC norm int priority lvl5
#define AVIC_NIPRIORITY4 (AVIC_BASE_ADDR+0x2C) //  32bit AVIC norm int priority lvl4
#define AVIC_NIPRIORITY3 (AVIC_BASE_ADDR+0x30) //  32bit AVIC norm int priority lvl3
#define AVIC_NIPRIORITY2 (AVIC_BASE_ADDR+0x34) //  32bit AVIC norm int priority lvl2
#define AVIC_NIPRIORITY1 (AVIC_BASE_ADDR+0x38) //  32bit AVIC norm int priority lvl1
#define AVIC_NIPRIORITY0 (AVIC_BASE_ADDR+0x3C) //  32bit AVIC norm int priority lvl0
#define AVIC_NIVECSR (AVIC_BASE_ADDR+0x40) //  32bit AVIC norm int vector/status
#define AVIC_FIVECSR (AVIC_BASE_ADDR+0x44) //  32bit AVIC fast int vector/status
#define AVIC_INTSRCH (AVIC_BASE_ADDR+0x48) //  32bit AVIC int source reg high
#define AVIC_INTSRCL (AVIC_BASE_ADDR+0x4C) //  32bit AVIC int source reg low
#define AVIC_INTFRCH (AVIC_BASE_ADDR+0x50) //  32bit AVIC int force reg high
#define AVIC_INTFRCL (AVIC_BASE_ADDR+0x54) //  32bit AVIC int force reg low
#define AVIC_NIPNDH (AVIC_BASE_ADDR+0x58) //  32bit AVIC norm int pending high
#define AVIC_NIPNDL (AVIC_BASE_ADDR+0x5C) //  32bit AVIC norm int pending low
#define AVIC_FIPNDH (AVIC_BASE_ADDR+0x60) //  32bit AVIC fast int pending high
#define AVIC_FIPNDL (AVIC_BASE_ADDR+0x64) //  32bit AVIC fast int pending low
  
//#########################################  
//# ROMPATCH                              #  
//# $6000_0000 to $67FF_FFFF              #  
//#########################################  
#define ROMPATCH_BASE_ADDR 0x60000000 
#define ROMPATCH_D15 (ROMPATCH_BASE_ADDR+0x0B4) //  32bit rompatch data reg 15
#define ROMPATCH_D14 (ROMPATCH_BASE_ADDR+0x0B8) //  32bit rompatch data reg 14
#define ROMPATCH_D13 (ROMPATCH_BASE_ADDR+0x0BC) //  32bit rompatch data reg 13
#define ROMPATCH_D12 (ROMPATCH_BASE_ADDR+0x0C0) //  32bit rompatch data reg 12
#define ROMPATCH_D11 (ROMPATCH_BASE_ADDR+0x0C4) //  32bit rompatch data reg 11
#define ROMPATCH_D10 (ROMPATCH_BASE_ADDR+0x0C8) //  32bit rompatch data reg 10
#define ROMPATCH_D9 (ROMPATCH_BASE_ADDR+0x0CC) //  32bit rompatch data reg 9
#define ROMPATCH_D8 (ROMPATCH_BASE_ADDR+0x0D0) //  32bit rompatch data reg 8
#define ROMPATCH_D7 (ROMPATCH_BASE_ADDR+0x0D4) //  32bit rompatch data reg 7
#define ROMPATCH_D6 (ROMPATCH_BASE_ADDR+0x0D8) //  32bit rompatch data reg 6
#define ROMPATCH_D5 (ROMPATCH_BASE_ADDR+0x0DC) //  32bit rompatch data reg 5
#define ROMPATCH_D4 (ROMPATCH_BASE_ADDR+0x0E0) //  32bit rompatch data reg 4
#define ROMPATCH_D3 (ROMPATCH_BASE_ADDR+0x0E4) //  32bit rompatch data reg 3
#define ROMPATCH_D2 (ROMPATCH_BASE_ADDR+0x0E8) //  32bit rompatch data reg 2
#define ROMPATCH_D1 (ROMPATCH_BASE_ADDR+0x0EC) //  32bit rompatch data reg 1
#define ROMPATCH_D0 (ROMPATCH_BASE_ADDR+0x0F0) //  32bit rompatch data reg 0
#define ROMPATCH_CNTL (ROMPATCH_BASE_ADDR+0x0F4) //  32bit rompatch control reg
#define ROMPATCH_ENH (ROMPATCH_BASE_ADDR+0x0F8) //  32bit rompatch enable reg high
#define ROMPATCH_ENL (ROMPATCH_BASE_ADDR+0x0FC) //  32bit rompatch enable reg low
#define ROMPATCH_A0 (ROMPATCH_BASE_ADDR+0x100) //  32bit rompatch addr reg 0
#define ROMPATCH_A1 (ROMPATCH_BASE_ADDR+0x104) //  32bit rompatch addr reg 1
#define ROMPATCH_A2 (ROMPATCH_BASE_ADDR+0x108) //  32bit rompatch addr reg 2
#define ROMPATCH_A3 (ROMPATCH_BASE_ADDR+0x10C) //  32bit rompatch addr reg 3
#define ROMPATCH_A4 (ROMPATCH_BASE_ADDR+0x110) //  32bit rompatch addr reg 4
#define ROMPATCH_A5 (ROMPATCH_BASE_ADDR+0x114) //  32bit rompatch addr reg 5
#define ROMPATCH_A6 (ROMPATCH_BASE_ADDR+0x118) //  32bit rompatch addr reg 6
#define ROMPATCH_A7 (ROMPATCH_BASE_ADDR+0x11C) //  32bit rompatch addr reg 7
#define ROMPATCH_A8 (ROMPATCH_BASE_ADDR+0x120) //  32bit rompatch addr reg 8
#define ROMPATCH_A9 (ROMPATCH_BASE_ADDR+0x124) //  32bit rompatch addr reg 9
#define ROMPATCH_A10 (ROMPATCH_BASE_ADDR+0x128) //  32bit rompatch addr reg 10
#define ROMPATCH_A11 (ROMPATCH_BASE_ADDR+0x12C) //  32bit rompatch addr reg 11
#define ROMPATCH_A12 (ROMPATCH_BASE_ADDR+0x130) //  32bit rompatch addr reg 12
#define ROMPATCH_A13 (ROMPATCH_BASE_ADDR+0x134) //  32bit rompatch addr reg 13
#define ROMPATCH_A14 (ROMPATCH_BASE_ADDR+0x138) //  32bit rompatch addr reg 14
#define ROMPATCH_A15 (ROMPATCH_BASE_ADDR+0x13C) //  32bit rompatch addr reg 15
#define ROMPATCH_A16 (ROMPATCH_BASE_ADDR+0x140) //  32bit rompatch addr reg 16
#define ROMPATCH_A17 (ROMPATCH_BASE_ADDR+0x144) //  32bit rompatch addr reg 17
#define ROMPATCH_A18 (ROMPATCH_BASE_ADDR+0x148) //  32bit rompatch addr reg 18
#define ROMPATCH_A19 (ROMPATCH_BASE_ADDR+0x14C) //  32bit rompatch addr reg 19
#define ROMPATCH_A20 (ROMPATCH_BASE_ADDR+0x150) //  32bit rompatch addr reg 20
#define ROMPATCH_A21 (ROMPATCH_BASE_ADDR+0x154) //  32bit rompatch addr reg 21
#define ROMPATCH_A22 (ROMPATCH_BASE_ADDR+0x158) //  32bit rompatch addr reg 22
#define ROMPATCH_A23 (ROMPATCH_BASE_ADDR+0x15C) //  32bit rompatch addr reg 23
#define ROMPATCH_A24 (ROMPATCH_BASE_ADDR+0x160) //  32bit rompatch addr reg 24
#define ROMPATCH_A25 (ROMPATCH_BASE_ADDR+0x164) //  32bit rompatch addr reg 25
#define ROMPATCH_A26 (ROMPATCH_BASE_ADDR+0x168) //  32bit rompatch addr reg 26
#define ROMPATCH_A27 (ROMPATCH_BASE_ADDR+0x16C) //  32bit rompatch addr reg 27
#define ROMPATCH_A28 (ROMPATCH_BASE_ADDR+0x170) //  32bit rompatch addr reg 28
#define ROMPATCH_A29 (ROMPATCH_BASE_ADDR+0x174) //  32bit rompatch addr reg 29
#define ROMPATCH_A30 (ROMPATCH_BASE_ADDR+0x178) //  32bit rompatch addr reg 30
#define ROMPATCH_A31 (ROMPATCH_BASE_ADDR+0x17C) //  32bit rompatch addr reg 31
#define ROMPATCH_BRPT (ROMPATCH_BASE_ADDR+0x200) //  32bit rompatch 
#define ROMPATCH_BASE (ROMPATCH_BASE_ADDR+0x204) //  32bit rompatch base addr reg
#define ROMPATCH_SR (ROMPATCH_BASE_ADDR+0x208) //  32bit rompatch status reg
#define ROMPATCH_ABSR (ROMPATCH_BASE_ADDR+0x20C) //  32bit rompatch abort status reg
#define ROMPATCH_DADR (ROMPATCH_BASE_ADDR+0x210) //  32bit rompatch d-ahb addr abort
#define ROMPATCH_IADR (ROMPATCH_BASE_ADDR+0x214) //  32bit rompatch i-ahb addr abort
  
//#########################################  
//# $8000_0000 to $8FFF_FFFF (CSD0)        #  
//# $9000_0000 to $9FFF_FFFF (CSD1)        #  
//# $A000_0000 to $A7FF_FFFF (CS0)        #  
//# $A800_0000 to $AFFF_FFFF (CS1)        #  
//# $8000_0000 to $81FF_FFFF (CS2)        #  
//# $8200_0000 to $83FF_FFFF (CS3)        #  
//# $8400_0000 to $85FF_FFFF (CS4)        #  
//# $8600_0000 to $87FF_FFFF (CS5)        #  
//#########################################  
//#########################################  
#define CS0_BASE_ADDR 0xA0000000 //  CS0 (64Mb)
#define CS0_END_ADDR 0xA7FFFFFF 
#define CS1_BASE_ADDR 0xA8000000 //  CS1 (64Mb)
#define CS1_END_ADDR 0xAFFFFFFF 
#define CS2_BASE_ADDR 0xB0000000 //  CS2 (16Mb)
#define CS2_END_ADDR 0xB1FFFFFF 
#define CS3_BASE_ADDR 0xB2000000 //  CS3 (16Mb)
#define CS3_END_ADDR 0xB3FFFFFF 
#define CS4_BASE_ADDR 0xB4000000 //  CS4 (16Mb)
#define CS4_END_ADDR 0xB5FFFFFF 
#define CS5_BASE_ADDR 0xB6000000 //  CS5 (16Mb)
#define CS5_END_ADDR 0xB7FFFFFF 
#define CSD0_BASE_ADDR 0x80000000 //   CSD0
#define CSD0_END_ADDR 0x8FFFFFFF 
#define CSD1_BASE_ADDR 0x90000000 //   CSD1
#define CSD1_END_ADDR 0x9FFFFFFF 
  
//#########################################  
//# WEIM                                  #  
//# $B800_2000 to $B800_2FFF              #  
//#########################################  
#define WEIM_BASE_ADDR 0xB8002000 
#define WEIM_CS0U (WEIM_BASE_ADDR+0x00) 
#define WEIM_CS0L (WEIM_BASE_ADDR+0x04) 
#define WEIM_CS0A (WEIM_BASE_ADDR+0x08) 
#define WEIM_CS1U (WEIM_BASE_ADDR+0x10) 
#define WEIM_CS1L (WEIM_BASE_ADDR+0x14) 
#define WEIM_CS1A (WEIM_BASE_ADDR+0x18) 
#define WEIM_CS2U (WEIM_BASE_ADDR+0x20) 
#define WEIM_CS2L (WEIM_BASE_ADDR+0x24) 
#define WEIM_CS2A (WEIM_BASE_ADDR+0x28) 
#define WEIM_CS3U (WEIM_BASE_ADDR+0x30) 
#define WEIM_CS3L (WEIM_BASE_ADDR+0x34) 
#define WEIM_CS3A (WEIM_BASE_ADDR+0x38) 
#define WEIM_CS4U (WEIM_BASE_ADDR+0x40) 
#define WEIM_CS4L (WEIM_BASE_ADDR+0x44) 
#define WEIM_CS4A (WEIM_BASE_ADDR+0x48) 
#define WEIM_CS5U (WEIM_BASE_ADDR+0x50) 
#define WEIM_CS5L (WEIM_BASE_ADDR+0x54) 
#define WEIM_CS5A (WEIM_BASE_ADDR+0x58) 
#define WEIM_EIM (WEIM_BASE_ADDR+0x60) //  32bit eim configuration reg
  
  
  
  
//#########################################  
//# VRAM                                  #  
//# $1000_0000 to $1FFF_FFFF              #  
//#########################################  
#define VRAM_BASE_ADDR 0x10000000 //  vector ram (256b)
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
// ARM Program Status Register  
//  31  30  29  28  27  .........  7   6   5  4  3  2  1  0  
// ----------------------------------------------------------  
// | N | Z | C | V | Q |         | I | F | T |   M4 - M0    |  
// ----------------------------------------------------------  
  
//#########################################  
//# ARM MODES = {M4, M3, M2, M1, M0}      #  
//#########################################  
#define MODE_USR 0x10 
#define MODE_FIQ 0x11 
#define MODE_IRQ 0x12 
#define MODE_SVC 0x13 
#define MODE_ABT 0x17 
#define MODE_UND 0x1B 
#define MODE_SYS 0x1F 
#define MODE_BITS 0x1F 
  
//#########################################  
//# ARM INTERRUPTS                        #  
//#########################################  
#define INTERRUPT_BITS 0xC0 
#define ENABLE_IRQ 0x0 
#define ENABLE_FIQ 0x0 
#define DISABLE_FIQ 0x40 
#define DISABLE_IRQ 0x80 
  
//#########################################  
//# ARM CONDITION CODE FLAG = {N,Z,C,V,Q} #  
//#########################################  
#define FLAG_BITS 0xF8000000 
#define NFLAG 0x80000000 
#define ZFLAG 0x40000000 
#define CFLAG 0x20000000 
#define VFLAG 0x10000000 
#define QFLAG 0x08000000 
//#########################################  
//# For Stack at SDRAM0                   #  
//# SVC_STACK = C3FFFC00-C3FFFFFF (1kbyte)#  
//# IRQ_STACK = C3FFF800-C3FFFBFF (1kbyte)#  
//# FIQ_STACK = C3FFF400-C3FFF7FF (1kbyte)#  
//# USR_STACK = C3FFF000-C3FFF3FF (1kbyte)#  
//# UND_STACK = C3FFEC00-C3FFEFFF (1kbyte)#  
//#########################################  
#define SDRAM0_STACK 0x1FFFF000 //  stack at bottom os SDRAM0
#define SVC_SDRAM0_STACK SDRAM0_STACK 
#define IRQ_SDRAM0_STACK SDRAM0_STACK-0x0400 
#define FIQ_SDRAM0_STACK SDRAM0_STACK-0x0800 
#define USR_SDRAM0_STACK SDRAM0_STACK-0x0C00 
#define UND_SDRAM0_STACK SDRAM0_STACK-0x1000 
  
//#########################################  
//# For Stack at SDRAM1                   #  
//# SVC_STACK = C7FFFC00-C7FFFFFF (1kbyte)#  
//# IRQ_STACK = C7FFF800-C7FFFBFF (1kbyte)#  
//# FIQ_STACK = C7FFF400-C7FFF7FF (1kbyte)#  
//# USR_STACK = C7FFF000-C7FFF3FF (1kbyte)#  
//# UND_STACK = C7FFEC00-C7FFEFFF (1kbyte)#  
//#########################################  
#define SDRAM1_STACK 0x1FFFE000 //  stack at bottom os SDRAM1
#define SVC_SDRAM1_STACK SDRAM1_STACK 
#define IRQ_SDRAM1_STACK SDRAM1_STACK-0x0400 
#define FIQ_SDRAM1_STACK SDRAM1_STACK-0x0800 
#define USR_SDRAM1_STACK SDRAM1_STACK-0x0C00 
#define UND_SDRAM1_STACK SDRAM1_STACK-0x1000 
  
//#########################################  
//# For Stack at SRAM                     #  
//# SVC_STACK = CFFFFC00-CFFFFFFF (1kbyte)#  
//# IRQ_STACK = CFFFF800-CFFFFBFF (1kbyte)#  
//# FIQ_STACK = CFFFF400-CFFFF7FF (1kbyte)#  
//# USR_STACK = CFFFF000-CFFFF3FF (1kbyte)#  
//# UND_STACK = CFFFEC00-CFFFEFFF (1kbyte)#  
//#########################################  
#define SRAM_STACK 0x1FFFD000 //  stack at bottom os SRAM
#define SVC_SRAM_STACK SRAM_STACK 
#define IRQ_SRAM_STACK SRAM_STACK-0x0400 
#define FIQ_SRAM_STACK SRAM_STACK-0x0800 
#define USR_SRAM_STACK SRAM_STACK-0x0C00 
#define UND_SRAM_STACK SRAM_STACK-0x1000 
#define ABT_SRAM_STACK SRAM_STACK-0x1400 
#define SYS_SRAM_STACK SRAM_STACK-0x1800 
  
  
//#########################################  
//# GPIO  generic  
//# relative addresses  
//#########################################  
  
#define GPIO_DR0 0x00 //  32bit gpio pta data direction reg
#define GPIO_GDIR0 0x04 //  32bit gpio pta output config 1 reg
#define GPIO_PSR0 0x08 //  32bit gpio pta output config 2 reg
#define GPIO_ICR1 0x0C //  32bit gpio pta input config A1 reg
#define GPIO_ICR2 0x10 //  32bit gpio pta input config A2 reg
#define GPIO_IMR 0x14 //  32bit gpio pta input config B1 reg
#define GPIO_ISR 0x18 
  
  
  
//#########################################  
//# GPIO1                                #  
//# $53FCC000to $53FCFFFF             #  
//#########################################  
#define GPIO1_BASE_ADDR 0x53FCC000 
#define GPIO1_DR0 (GPIO1_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define GPIO1_GDIR0 (GPIO1_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define GPIO1_PSR0 (GPIO1_BASE_ADDR+0x08) //  32bit gpio pta output config 2 reg
#define GPIO1_ICR1 (GPIO1_BASE_ADDR+0x0C) //  32bit gpio pta input config A1 reg
#define GPIO1_ICR2 (GPIO1_BASE_ADDR+0x10) //  32bit gpio pta input config A2 reg
#define GPIO1_IMR (GPIO1_BASE_ADDR+0x14) //  32bit gpio pta input config B1 reg
#define GPIO1_ISR (GPIO1_BASE_ADDR+0x18) 
  
  
//#########################################  
//# CSPI   generic  
//# relative addresses  
//#########################################  
  
#define CSPI_RXDATA 0x00 //  32bit CSPI receive data reg
#define CSPI_TXDATA 0x04 //  32bit CSPI transmit data reg
#define CSPI_CONREG 0x08 //  32bit CSPI control reg
#define CSPI_INTREG 0x0C //  32bit CSPI interrupt stat/ctr reg
#define CSPI_DMAREG 0x10 //  32bit CSPI test reg
#define CSPI_STATREG 0x14 //  32bit CSPI sample period ctrl reg
#define CSPI_PERIODREG 0x18 //  32bit CSPI dma ctrl reg
#define CSPI_TESTREG 0x1C //  32bit CSPI soft reset reg
  
  
  
  
  
  
//#########################################  
//# CSPI1                                 #  
//# $43FA_4000 to $43FA_7FFF              #  
//#########################################  
#define CSPI1_BASE_ADDR 0x43FA4000 
#define CSPI1_RXDATA (CSPI1_BASE_ADDR+0x00) //  32bit cspi1 receive data reg
#define CSPI1_TXDATA (CSPI1_BASE_ADDR+0x04) //  32bit cspi1 transmit data reg
#define CSPI1_CONREG (CSPI1_BASE_ADDR+0x08) //  32bit cspi1 control reg
#define CSPI1_INTREG (CSPI1_BASE_ADDR+0x0C) //  32bit cspi1 interrupt stat/ctr reg
#define CSPI1_DMAREG (CSPI1_BASE_ADDR+0x10) //  32bit cspi1 test reg
#define CSPI1_STATREG (CSPI1_BASE_ADDR+0x14) //  32bit cspi1 sample period ctrl reg
#define CSPI1_PERIODREG (CSPI1_BASE_ADDR+0x18) //  32bit cspi1 dma ctrl reg
#define CSPI1_TESTREG (CSPI1_BASE_ADDR+0x1C) //  32bit cspi1 soft reset reg
  
//#########################################  
//# CSPI2                                 #  
//# $5001_0000 to $5001_3FFF              #  
//#########################################  
#define CSPI2_BASE_ADDR 0x50010000 
#define CSPI2_RXDATA (CSPI2_BASE_ADDR+0x00) //  32bit cspi2 receive data reg
#define CSPI2_TXDATA (CSPI2_BASE_ADDR+0x04) //  32bit cspi2 transmit data reg
#define CSPI2_CONREG (CSPI2_BASE_ADDR+0x08) //  32bit cspi2 control reg
#define CSPI2_INTREG (CSPI2_BASE_ADDR+0x0C) //  32bit cspi2 interrupt stat/ctr reg
#define CSPI2_DMAREG (CSPI2_BASE_ADDR+0x10) //  32bit cspi2 test reg
#define CSPI2_STATREG (CSPI2_BASE_ADDR+0x14) //  32bit cspi2 sample period ctrl reg
#define CSPI2_PERIODREG (CSPI2_BASE_ADDR+0x18) //  32bit cspi2 dma ctrl reg
#define CSPI2_TESTREG (CSPI2_BASE_ADDR+0x1C) //  32bit cspi2 soft reset reg
  
  
//#########################################  
//# CSPI3  
//# $53F8_4000 to $53F87FFF  
//#########################################  
#define CSPI3_BASE_ADDR 0x53F84000 
#define CSPI3_RXDATA (CSPI3_BASE_ADDR+0x00) //  32bit cspi3 receive data reg
#define CSPI3_TXDATA (CSPI3_BASE_ADDR+0x04) //  32bit cspi3 transmit data reg
#define CSPI3_CONREG (CSPI3_BASE_ADDR+0x08) //  32bit cspi3 control reg
#define CSPI3_INTREG (CSPI3_BASE_ADDR+0x0C) //  32bit cspi3 interrupt stat/ctr reg
#define CSPI3_DMAREG (CSPI3_BASE_ADDR+0x10) //  32bit cspi3 test reg
#define CSPI3_STATREG (CSPI3_BASE_ADDR+0x14) //  32bit cspi3 sample period ctrl reg
#define CSPI3_PERIODREG (CSPI3_BASE_ADDR+0x18) //  32bit cspi3 dma ctrl reg
#define CSPI3_TESTREG (CSPI3_BASE_ADDR+0x1C) //  32bit cspi3 soft reset reg
  
  
  
  
  
//#########################################  
//# OWIRE                                 #  
//# $43F9_C000 to $43F9_FFFF              #  
//#########################################  
#define OWIRE_BASE_ADDR 0x43F9C000 
#define OWIRE_CTRL (OWIRE_BASE_ADDR+0x00) //  16bit owire control reg
#define OWIRE_TIME_DIV (OWIRE_BASE_ADDR+0x02) //  16bit owire time divider reg
#define OWIRE_RESET (OWIRE_BASE_ADDR+0x04) //  16bit owire reset reg
  
  
  
  
//#########################################  
//# SDHC  generic  
//# relative addresses  
//#########################################  
  
#define SDHC_STR_STP_CLK 0x00 //  32bit SDHC control reg 
#define SDHC_STATUS 0x04 //  32bit SDHC status reg
#define SDHC_CLK_RATE 0x08 //  32bit SDHC clock rate reg
#define SDHC_CMD_DAT_CONT 0x0C //  32bit SDHC cmd/data control reg
#define SDHC_RESPONSE_TO 0x10 //  32bit SDHC response time out reg
#define SDHC_READ_TO 0x14 //  32bit SDHC read time out reg
#define SDHC_BLK_LEN 0x18 //  32bit SDHC block length reg
#define SDHC_NOB 0x1C //  32bit SDHC number of blocks reg
#define SDHC_REV_NO 0x20 //  32bit SDHC revision number reg
#define SDHC_INT_CNTR 0x24 //  32bit SDHC interrupt mask reg
#define SDHC_CMD 0x28 //  32bit SDHC command code reg
#define SDHC_ARG 0x2C //  32bit SDHC argument (high+low) reg
#define SDHC_RES_FIFO 0x34 //  32bit SDHC response fifo reg
#define SDHC_BUFFER_ACCESS 0x38 //  32bit SDHC buffer access reg
#define SDHC_REMAINING_NOB 0x40 //  32bit SDHC remaining NUM reg
#define SDHC_REMAINING_BLK_SIZE 0x44 //  32bit SDHC remaining block bytes  reg
  
  
  
  
//#########################################  
//# SDHC1                                 #  
//# $5000_4000 to $5000_7FFF              #  
//#########################################  
#define SDHC1_BASE_ADDR 0x50004000 
#define SDHC1_STR_STP_CLK (SDHC1_BASE_ADDR+0x00) //  32bit sdhc1 control reg 
#define SDHC1_STATUS (SDHC1_BASE_ADDR+0x04) //  32bit sdhc1 status reg
#define SDHC1_CLK_RATE (SDHC1_BASE_ADDR+0x08) //  32bit sdhc1 clock rate reg
#define SDHC1_CMD_DAT_CONT (SDHC1_BASE_ADDR+0x0C) //  32bit sdhc1 cmd/data control reg
#define SDHC1_RESPONSE_TO (SDHC1_BASE_ADDR+0x10) //  32bit sdhc1 response time out reg
#define SDHC1_READ_TO (SDHC1_BASE_ADDR+0x14) //  32bit sdhc1 read time out reg
#define SDHC1_BLK_LEN (SDHC1_BASE_ADDR+0x18) //  32bit sdhc1 block length reg
#define SDHC1_NOB (SDHC1_BASE_ADDR+0x1C) //  32bit sdhc1 number of blocks reg
#define SDHC1_REV_NO (SDHC1_BASE_ADDR+0x20) //  32bit sdhc1 revision number reg
#define SDHC1_INT_CNTR (SDHC1_BASE_ADDR+0x24) //  32bit sdhc1 interrupt mask reg
#define SDHC1_CMD (SDHC1_BASE_ADDR+0x28) //  32bit sdhc1 command code reg
#define SDHC1_ARG (SDHC1_BASE_ADDR+0x2C) //  32bit sdhc1 argument (high+low) reg
#define SDHC1_RES_FIFO (SDHC1_BASE_ADDR+0x34) //  32bit sdhc1 response fifo reg
#define SDHC1_BUFFER_ACCESS (SDHC1_BASE_ADDR+0x38) //  32bit sdhc1 buffer access reg
#define SDHC1_REMAINING_NOB (SDHC1_BASE_ADDR+0x40) //  32bit sdhc1 remaining NUM reg
#define SDHC1_REMAINING_BLK_SIZE (SDHC1_BASE_ADDR+0x44) //  32bit sdhc1 remaining block bytes  reg
  
//#########################################  
//# SDHC2                                 #  
//# $5000_8000 to $5000_BFFF              #  
//#########################################  
#define SDHC2_BASE_ADDR 0x50008000 
#define SDHC2_STR_STP_CLK (SDHC2_BASE_ADDR+0x00) //  32bit sdhc2 control reg 
#define SDHC2_STATUS (SDHC2_BASE_ADDR+0x04) //  32bit sdhc2 status reg
#define SDHC2_CLK_RATE (SDHC2_BASE_ADDR+0x08) //  32bit sdhc2 clock rate reg
#define SDHC2_CMD_DAT_CONT (SDHC2_BASE_ADDR+0x0C) //  32bit sdhc2 cmd/data control reg
#define SDHC2_RESPONSE_TO (SDHC2_BASE_ADDR+0x10) //  32bit sdhc2 response time out reg
#define SDHC2_READ_TO (SDHC2_BASE_ADDR+0x14) //  32bit sdhc2 read time out reg
#define SDHC2_BLK_LEN (SDHC2_BASE_ADDR+0x18) //  32bit sdhc2 block length reg
#define SDHC2_NOB (SDHC2_BASE_ADDR+0x1C) //  32bit sdhc2 number of blocks reg
#define SDHC2_REV_NO (SDHC2_BASE_ADDR+0x20) //  32bit sdhc2 revision number reg
#define SDHC2_INT_CNTR (SDHC2_BASE_ADDR+0x24) //  32bit sdhc2 interrupt mask reg
#define SDHC2_CMD (SDHC2_BASE_ADDR+0x28) //  32bit sdhc2 command code reg
#define SDHC2_ARG (SDHC2_BASE_ADDR+0x2C) //  32bit sdhc2 argument high reg
#define SDHC2_RES_FIFO (SDHC2_BASE_ADDR+0x34) //  32bit sdhc2 response fifo reg
#define SDHC2_BUFFER_ACCESS (SDHC2_BASE_ADDR+0x38) //  32bit sdhc2 buffer access reg
#define SDHC2_REMAINING_NOB (SDHC2_BASE_ADDR+0x40) //  32bit sdhc2 remaining NUM reg
#define SDHC2_REMAINING_BLK_SIZE (SDHC2_BASE_ADDR+0x44) //  32bit sdhc2 remaining block bytes  reg
  
//#########################################  
//# SIM                                   #  
//# $5001_8000 to $5001_BFFF              #  
//#########################################  
  
  
#define SIM_BASE_ADDR 0x50018000 
#define SIM_PORT1_CNTL (SIM_BASE_ADDR+0x00) 
#define SIM_SETUP (SIM_BASE_ADDR+0x04) 
#define SIM_PORT1_DETECT (SIM_BASE_ADDR+0x08) 
#define SIM_PORT1_XMT_BUF (SIM_BASE_ADDR+0x0C) 
#define SIM_PORT1_RCV_BUF (SIM_BASE_ADDR+0x10) 
#define SIM_PORT0_CNTL (SIM_BASE_ADDR+0x14) 
#define SIM_CNTL (SIM_BASE_ADDR+0x18) 
#define SIM_CLOCK_SELECT (SIM_BASE_ADDR+0x1C) 
#define SIM_RCV_THRESHOLD (SIM_BASE_ADDR+0x20) 
#define SIM_ENABLE (SIM_BASE_ADDR+0x24) 
#define SIM_XMT_STATUS (SIM_BASE_ADDR+0x28) 
#define SIM_RCV_STATUS (SIM_BASE_ADDR+0x2C) 
#define SIM_INT_MASK (SIM_BASE_ADDR+0x30) 
#define SIM_PORT0_XMT_BUF (SIM_BASE_ADDR+0x34) 
#define SIM_PORT0_RCV_BUF (SIM_BASE_ADDR+0x38) 
#define SIM_PORT0_DETECT (SIM_BASE_ADDR+0x3C) 
#define SIM_DATA_FORMAT  (SIM_BASE_ADDR+0x40) 
#define SIM_XMT_THRESHOLD (SIM_BASE_ADDR+0x44) 
#define SIM_GUARD_CNTL (SIM_BASE_ADDR+0x48) 
#define SIM_OD_CONFIG (SIM_BASE_ADDR+0x4C) 
#define SIM_RESET_CNTL (SIM_BASE_ADDR+0x50) 
#define SIM_CHAR_WAIT (SIM_BASE_ADDR+0x54) 
#define SIM_GPCNT (SIM_BASE_ADDR+0x58) 
#define SIM_DIVISOR (SIM_BASE_ADDR+0x5C) 
#define SIM_BWT (SIM_BASE_ADDR+0x60) 
#define SIM_BGT (SIM_BASE_ADDR+0x64) 
#define SIM_BWT_H (SIM_BASE_ADDR+0x68) 
  
  
//#########################################  
//# SSI  generic  
//# relative addresses  
//#########################################  
  
#define SSI_STX0 0x00 //  32bit SSI tx reg 0
#define SSI_STX1 0x04 //  32bit SSI tx reg 1
#define SSI_SRX0 0x08 //  32bit SSI rx reg 0
#define SSI_SRX1 0x0C //  32bit SSI rx reg 1
#define SSI_SCR 0x10 //  32bit SSI control reg
#define SSI_SISR 0x14 //  32bit SSI intr status reg
#define SSI_SIER 0x18 //  32bit SSI intr enable reg
#define SSI_STCR 0x1C //  32bit SSI tx config reg
#define SSI_SRCR 0x20 //  32bit SSI rx config reg
#define SSI_STCCR 0x24 //  32bit SSI tx clock control reg
#define SSI_SRCCR 0x28 //  32bit SSI rx clock control reg
#define SSI_SFCSR 0x2C //  32bit SSI fifo control/status reg
#define SSI_STR 0x30 //  32bit SSI test reg
#define SSI_SOR 0x34 //  32bit SSI option reg
#define SSI_SACNT 0x38 //  32bit SSI ac97 control reg
#define SSI_SACADD 0x3C //  32bit SSI ac97 cmd addr reg
#define SSI_SACDAT 0x40 //  32bit SSI ac97 cmd data reg
#define SSI_SATAG 0x44 //  32bit SSI ac97 tag reg
#define SSI_STMSK 0x48 //  32bit SSI tx time slot mask reg
#define SSI_SRMSK 0x4C //  32bit SSI rx time slot mask reg
  
  
  
  
  
//#########################################  
//# SSI1                                  #  
//# $43FA_0000 to $43FA_3FFF              #  
//#########################################  
#define SSI1_BASE_ADDR 0x43FA0000 
#define SSI1_STX0 (SSI1_BASE_ADDR+0x00) //  32bit ssi1 tx reg 0
#define SSI1_STX1 (SSI1_BASE_ADDR+0x04) //  32bit ssi1 tx reg 1
#define SSI1_SRX0 (SSI1_BASE_ADDR+0x08) //  32bit ssi1 rx reg 0
#define SSI1_SRX1 (SSI1_BASE_ADDR+0x0C) //  32bit ssi1 rx reg 1
#define SSI1_SCR (SSI1_BASE_ADDR+0x10) //  32bit ssi1 control reg
#define SSI1_SISR (SSI1_BASE_ADDR+0x14) //  32bit ssi1 intr status reg
#define SSI1_SIER (SSI1_BASE_ADDR+0x18) //  32bit ssi1 intr enable reg
#define SSI1_STCR (SSI1_BASE_ADDR+0x1C) //  32bit ssi1 tx config reg
#define SSI1_SRCR (SSI1_BASE_ADDR+0x20) //  32bit ssi1 rx config reg
#define SSI1_STCCR (SSI1_BASE_ADDR+0x24) //  32bit ssi1 tx clock control reg
#define SSI1_SRCCR (SSI1_BASE_ADDR+0x28) //  32bit ssi1 rx clock control reg
#define SSI1_SFCSR (SSI1_BASE_ADDR+0x2C) //  32bit ssi1 fifo control/status reg
#define SSI1_STR (SSI1_BASE_ADDR+0x30) //  32bit ssi1 test reg
#define SSI1_SOR (SSI1_BASE_ADDR+0x34) //  32bit ssi1 option reg
#define SSI1_SACNT (SSI1_BASE_ADDR+0x38) //  32bit ssi1 ac97 control reg
#define SSI1_SACADD (SSI1_BASE_ADDR+0x3C) //  32bit ssi1 ac97 cmd addr reg
#define SSI1_SACDAT (SSI1_BASE_ADDR+0x40) //  32bit ssi1 ac97 cmd data reg
#define SSI1_SATAG (SSI1_BASE_ADDR+0x44) //  32bit ssi1 ac97 tag reg
#define SSI1_STMSK (SSI1_BASE_ADDR+0x48) //  32bit ssi1 tx time slot mask reg
#define SSI1_SRMSK (SSI1_BASE_ADDR+0x4C) //  32bit ssi1 rx time slot mask reg
  
  
//#########################################  
//# SSI2                                  #  
//# $5001_4000 to $5001_7FFF              #  
//#########################################  
#define SSI2_BASE_ADDR 0x50014000 
#define SSI2_STX0 (SSI2_BASE_ADDR+0x00) //  32bit ssi2 tx reg 0
#define SSI2_STX1 (SSI2_BASE_ADDR+0x04) //  32bit ssi2 tx reg 1
#define SSI2_SRX0 (SSI2_BASE_ADDR+0x08) //  32bit ssi2 rx reg 0
#define SSI2_SRX1 (SSI2_BASE_ADDR+0x0C) //  32bit ssi2 rx reg 1
#define SSI2_SCR (SSI2_BASE_ADDR+0x10) //  32bit ssi2 control reg
#define SSI2_SISR (SSI2_BASE_ADDR+0x14) //  32bit ssi2 intr status reg
#define SSI2_SIER (SSI2_BASE_ADDR+0x18) //  32bit ssi2 intr enable reg
#define SSI2_STCR (SSI2_BASE_ADDR+0x1C) //  32bit ssi2 tx config reg
#define SSI2_SRCR (SSI2_BASE_ADDR+0x20) //  32bit ssi2 rx config reg
#define SSI2_STCCR (SSI2_BASE_ADDR+0x24) //  32bit ssi2 tx clock control reg
#define SSI2_SRCCR (SSI2_BASE_ADDR+0x28) //  32bit ssi2 rx clock control reg
#define SSI2_SFCSR (SSI2_BASE_ADDR+0x2C) //  32bit ssi2 fifo control/status reg
#define SSI2_STR (SSI2_BASE_ADDR+0x30) //  32bit ssi2 test reg
#define SSI2_SOR (SSI2_BASE_ADDR+0x34) //  32bit ssi2 option reg
#define SSI2_SACNT (SSI2_BASE_ADDR+0x38) //  32bit ssi2 ac97 control reg
#define SSI2_SACADD (SSI2_BASE_ADDR+0x3C) //  32bit ssi2 ac97 cmd addr reg
#define SSI2_SACDAT (SSI2_BASE_ADDR+0x40) //  32bit ssi2 ac97 cmd data reg
#define SSI2_SATAG (SSI2_BASE_ADDR+0x44) //  32bit ssi2 ac97 tag reg
#define SSI2_STMSK (SSI2_BASE_ADDR+0x48) //  32bit ssi2 tx time slot mask reg
#define SSI2_SRMSK (SSI2_BASE_ADDR+0x4C) //  32bit ssi2 rx time slot mask reg
  
//#########################################  
//# UART generic  
//# relative addresses  
//#########################################  
  
#define UART_URXD 0x00 //  32bit UART receiver reg
#define UART_UTXD 0x40 //  32bit UART transmitter reg
#define UART_UCR1 0x80 //  32bit UART control 1 reg
#define UART_UCR2 0x84 //  32bit UART control 2 reg
#define UART_UCR3 0x88 //  32bit UART control 3 reg
#define UART_UCR4 0x8C //  32bit UART control 4 reg
#define UART_UFCR 0x90 //  32bit UART fifo control reg
#define UART_USR1 0x94 //  32bit UART status 1 reg
#define UART_USR2 0x98 //  32bit UART status 2 reg
#define UART_UESC 0x9C //  32bit UART escape char reg
#define UART_UTIM 0xA0 //  32bit UART escape timer reg
#define UART_UBIR 0xA4 //  32bit UART BRM incremental reg
#define UART_UBMR 0xA8 //  32bit UART BRM modulator reg
#define UART_UBRC 0xAC //  32bit UART baud rate count reg
#define UART_ONEMS 0xB0 //  32bit UART one ms reg
#define UART_UTS 0xB4 //  32bit UART test reg
  
  
  
  
  
  
  
//#########################################  
//# UART1                                 #  
//# $43F9_0000 to $43F9_3FFF              #  
//#########################################  
#define UART1_BASE_ADDR 0x43F90000 
#define UART1_URXD_1 (UART1_BASE_ADDR+0x00) //  32bit uart1 receiver reg
#define UART1_UTXD_1 (UART1_BASE_ADDR+0x40) //  32bit uart1 transmitter reg
#define UART1_UCR1_1 (UART1_BASE_ADDR+0x80) //  32bit uart1 control 1 reg
#define UART1_UCR2_1 (UART1_BASE_ADDR+0x84) //  32bit uart1 control 2 reg
#define UART1_UCR3_1 (UART1_BASE_ADDR+0x88) //  32bit uart1 control 3 reg
#define UART1_UCR4_1 (UART1_BASE_ADDR+0x8C) //  32bit uart1 control 4 reg
#define UART1_UFCR_1 (UART1_BASE_ADDR+0x90) //  32bit uart1 fifo control reg
#define UART1_USR1_1 (UART1_BASE_ADDR+0x94) //  32bit uart1 status 1 reg
#define UART1_USR2_1 (UART1_BASE_ADDR+0x98) //  32bit uart1 status 2 reg
#define UART1_UESC_1 (UART1_BASE_ADDR+0x9C) //  32bit uart1 escape char reg
#define UART1_UTIM_1 (UART1_BASE_ADDR+0xA0) //  32bit uart1 escape timer reg
#define UART1_UBIR_1 (UART1_BASE_ADDR+0xA4) //  32bit uart1 BRM incremental reg
#define UART1_UBMR_1 (UART1_BASE_ADDR+0xA8) //  32bit uart1 BRM modulator reg
#define UART1_UBRC_1 (UART1_BASE_ADDR+0xAC) //  32bit uart1 baud rate count reg
#define UART1_ONEMS_1 (UART1_BASE_ADDR+0xB0) //  32bit uart1 one ms reg
#define UART1_UTS_1 (UART1_BASE_ADDR+0xB4) //  32bit uart1 test reg
  
//#########################################  
//# UART2                                 #  
//# $43F9_4000 to $43F9_7FFF              #  
//#########################################  
#define UART2_BASE_ADDR 0x43F94000 
#define UART2_URXD_2 (UART2_BASE_ADDR+0x00) //  32bit uart2 receiver reg
#define UART2_UTXD_2 (UART2_BASE_ADDR+0x40) //  32bit uart2 transmitter reg
#define UART2_UCR1_2 (UART2_BASE_ADDR+0x80) //  32bit uart2 control 1 reg
#define UART2_UCR2_2 (UART2_BASE_ADDR+0x84) //  32bit uart2 control 2 reg
#define UART2_UCR3_2 (UART2_BASE_ADDR+0x88) //  32bit uart2 control 3 reg
#define UART2_UCR4_2 (UART2_BASE_ADDR+0x8C) //  32bit uart2 control 4 reg
#define UART2_UFCR_2 (UART2_BASE_ADDR+0x90) //  32bit uart2 fifo control reg
#define UART2_USR1_2 (UART2_BASE_ADDR+0x94) //  32bit uart2 status 1 reg
#define UART2_USR2_2 (UART2_BASE_ADDR+0x98) //  32bit uart2 status 2 reg
#define UART2_UESC_2 (UART2_BASE_ADDR+0x9C) //  32bit uart2 escape char reg
#define UART2_UTIM_2 (UART2_BASE_ADDR+0xA0) //  32bit uart2 escape timer reg
#define UART2_UBIR_2 (UART2_BASE_ADDR+0xA4) //  32bit uart2 BRM incremental reg
#define UART2_UBMR_2 (UART2_BASE_ADDR+0xA8) //  32bit uart2 BRM modulator reg
#define UART2_UBRC_2 (UART2_BASE_ADDR+0xAC) //  32bit uart2 baud rate count reg
#define UART2_ONEMS_2 (UART2_BASE_ADDR+0xB0) //  32bit uart2 one ms reg
#define UART2_UTS_2 (UART2_BASE_ADDR+0xB4) //  32bit uart2 test reg
  
//#########################################  
//# UART3                                 #  
//# $5000_C000 to $5000_FFFF              #  
//#########################################  
#define UART3_BASE_ADDR 0x5000C000 
#define UART3_URXD_3 (UART3_BASE_ADDR+0x00) //  32bit uart3 receiver reg
#define UART3_UTXD_3 (UART3_BASE_ADDR+0x40) //  32bit uart3 transmitter reg
#define UART3_UCR1_3 (UART3_BASE_ADDR+0x80) //  32bit uart3 control 1 reg
#define UART3_UCR2_3 (UART3_BASE_ADDR+0x84) //  32bit uart3 control 2 reg
#define UART3_UCR3_3 (UART3_BASE_ADDR+0x88) //  32bit uart3 control 3 reg
#define UART3_UCR4_3 (UART3_BASE_ADDR+0x8C) //  32bit uart3 control 4 reg
#define UART3_UFCR_3 (UART3_BASE_ADDR+0x90) //  32bit uart3 fifo control reg
#define UART3_USR1_3 (UART3_BASE_ADDR+0x94) //  32bit uart3 status 1 reg
#define UART3_USR2_3 (UART3_BASE_ADDR+0x98) //  32bit uart3 status 2 reg
#define UART3_UESC_3 (UART3_BASE_ADDR+0x9C) //  32bit uart3 escape char reg
#define UART3_UTIM_3 (UART3_BASE_ADDR+0xA0) //  32bit uart3 escape timer reg
#define UART3_UBIR_3 (UART3_BASE_ADDR+0xA4) //  32bit uart3 BRM incremental reg
#define UART3_UBMR_3 (UART3_BASE_ADDR+0xA8) //  32bit uart3 BRM modulator reg
#define UART3_UBRC_3 (UART3_BASE_ADDR+0xAC) //  32bit uart3 baud rate count reg
#define UART3_ONEMS_3 (UART3_BASE_ADDR+0xB0) //  32bit uart3 one ms reg
#define UART3_UTS_3 (UART3_BASE_ADDR+0xB4) //  32bit uart3 test reg
  
//#########################################  
//# UART4                                 #  
//# $43FB_0000 to $43FB_3FFF              #  
//#########################################  
#define UART4_BASE_ADDR 0x43FB0000 
#define UART4_URXD_4 (UART4_BASE_ADDR+0x00) //  32bit uart4 receiver reg
#define UART4_UTXD_4 (UART4_BASE_ADDR+0x40) //  32bit uart4 transmitter reg
#define UART4_UCR1_4 (UART4_BASE_ADDR+0x80) //  32bit uart4 control 1 reg
#define UART4_UCR2_4 (UART4_BASE_ADDR+0x84) //  32bit uart4 control 2 reg
#define UART4_UCR3_4 (UART4_BASE_ADDR+0x88) //  32bit uart4 control 3 reg
#define UART4_UCR4_4 (UART4_BASE_ADDR+0x8C) //  32bit uart4 control 4 reg
#define UART4_UFCR_4 (UART4_BASE_ADDR+0x90) //  32bit uart4 fifo control reg
#define UART4_USR1_4 (UART4_BASE_ADDR+0x94) //  32bit uart4 status 1 reg
#define UART4_USR2_4 (UART4_BASE_ADDR+0x98) //  32bit uart4 status 2 reg
#define UART4_UESC_4 (UART4_BASE_ADDR+0x9C) //  32bit uart4 escape char reg
#define UART4_UTIM_4 (UART4_BASE_ADDR+0xA0) //  32bit uart4 escape timer reg
#define UART4_UBIR_4 (UART4_BASE_ADDR+0xA4) //  32bit uart4 BRM incremental reg
#define UART4_UBMR_4 (UART4_BASE_ADDR+0xA8) //  32bit uart4 BRM modulator reg
#define UART4_UBRC_4 (UART4_BASE_ADDR+0xAC) //  32bit uart4 baud rate count reg
#define UART4_ONEMS_4 (UART4_BASE_ADDR+0xB0) //  32bit uart4 one ms reg
#define UART4_UTS_4 (UART4_BASE_ADDR+0xB4) //  32bit uart4 test reg
  
//#########################################  
//# UART5                                 #  
//# $43FB_4000 to $43FB_7FFF              #  
//#########################################  
#define UART5_BASE_ADDR 0x43FB4000 
#define UART5_URXD_5 (UART5_BASE_ADDR+0x00) //  32bit uart5 receiver reg
#define UART5_UTXD_5 (UART5_BASE_ADDR+0x40) //  32bit uart5 transmitter reg
#define UART5_UCR1_5 (UART5_BASE_ADDR+0x80) //  32bit uart5 control 1 reg
#define UART5_UCR2_5 (UART5_BASE_ADDR+0x84) //  32bit uart5 control 2 reg
#define UART5_UCR3_5 (UART5_BASE_ADDR+0x88) //  32bit uart5 control 3 reg
#define UART5_UCR4_5 (UART5_BASE_ADDR+0x8C) //  32bit uart5 control 4 reg
#define UART5_UFCR_5 (UART5_BASE_ADDR+0x90) //  32bit uart5 fifo control reg
#define UART5_USR1_5 (UART5_BASE_ADDR+0x94) //  32bit uart5 status 1 reg
#define UART5_USR2_5 (UART5_BASE_ADDR+0x98) //  32bit uart5 status 2 reg
#define UART5_UESC_5 (UART5_BASE_ADDR+0x9C) //  32bit uart5 escape char reg
#define UART5_UTIM_5 (UART5_BASE_ADDR+0xA0) //  32bit uart5 escape timer reg
#define UART5_UBIR_5 (UART5_BASE_ADDR+0xA4) //  32bit uart5 BRM incremental reg
#define UART5_UBMR_5 (UART5_BASE_ADDR+0xA8) //  32bit uart5 BRM modulator reg
#define UART5_UBRC_5 (UART5_BASE_ADDR+0xAC) //  32bit uart5 baud rate count reg
#define UART5_ONEMS_5 (UART5_BASE_ADDR+0xB0) //  32bit uart5 one ms reg
#define UART5_UTS_5 (UART5_BASE_ADDR+0xB4) //  32bit uart5 test reg
  
//#########################################  
//# USB_TOP                                #  
//# $43F8_8000 to $43F8_BFFF              #  
//#########################################  
//#**********************  
//#  USB MODULE  
//#**********************  
  
#ifdef FPGA
#define USB_MODULE_BASE_ADDR (TARGETBOARD0+0x7000)
#else
#define  USB_MODULE_BASE_ADDR 0x43F88000 
#endif

#define  USB_OTG_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x000) 
#define  USB_H1_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x200) 
#define  USB_H2_BASE_ADDR (USB_MODULE_BASE_ADDR + 0x400) 
#define  USB_CONTROL_REG (USB_MODULE_BASE_ADDR + 0x600) 
#define  USB_OTG_MIRROR_REG (USB_MODULE_BASE_ADDR + 0x604) 
  
//#**********************  
//# USB HOST 1  
//#**********************  
  
#define  USB_H1_ID (USB_H1_BASE_ADDR +0x000) //   Identification Register                
#define  USB_H1_HWGENERAL (USB_H1_BASE_ADDR +0x004) //   General Hardware Parameters            
#define  USB_H1_HWHOST (USB_H1_BASE_ADDR +0x008) //   Host Hardware Parameters               
#define  USB_H1_HWTXBUF (USB_H1_BASE_ADDR +0x010) //   TX Buffer Hardware Parameters          
#define  USB_H1_HWRXBUF (USB_H1_BASE_ADDR +0x014) //   RX Buffer Hardware Parameters          
#define  USB_H1_CAPLENGTH (USB_H1_BASE_ADDR +0x100) //   Capability Register Length             
#define  USB_H1_HCIVERSION (USB_H1_BASE_ADDR +0x102) //   Host Interface Version Number          
#define  USB_H1_HCSPARAMS (USB_H1_BASE_ADDR +0x104) //   Host Ctrl. Structural Parameters       
#define  USB_H1_HCCPARAMS (USB_H1_BASE_ADDR +0x108) //   Host Ctrl. Capability Parameters       
#define  USB_H1_USBCMD (USB_H1_BASE_ADDR +0x140) //   USB Command                            
#define  USB_H1_USBSTS (USB_H1_BASE_ADDR +0x144) //   USB Status                             
#define  USB_H1_USBINTR (USB_H1_BASE_ADDR +0x148) //   USB Interrupt Enable                   
#define  USB_H1_FRINDEX (USB_H1_BASE_ADDR +0x14C) //   USB Frame Index
#define  USB_H1_PERIODICLISTBASE (USB_H1_BASE_ADDR +0x154) //   Frame List Base Address                
#define  USB_H1_ASYNCLISTADDR (USB_H1_BASE_ADDR +0x158) //   Next Asynchronous List Address         
#define  USB_H1_BURSTSIZE (USB_H1_BASE_ADDR +0x160) //   Programmable Burst Size                
#define  USB_H1_TXFILLTUNING (USB_H1_BASE_ADDR +0x164) //   Host Transmit Pre-Buffer Packet Tuning 
#define  USB_H1_CONFIGFLAG (USB_H1_BASE_ADDR +0x180) //   Configured Flag Register               
#define  USB_H1_PORTSC1 (USB_H1_BASE_ADDR +0x184) //   Port Status/Control                    
#define  USB_H1_USBMODE (USB_H1_BASE_ADDR +0x1A8) //   USB Device Mode                        
  
//#**********************  
//# USB HOST 2  
//#**********************  
  
#define  USB_H2_ID (USB_H2_BASE_ADDR +0x000) //   Identification Register                
#define  USB_H2_HWGENERAL (USB_H2_BASE_ADDR +0x004) //   General Hardware Parameters            
#define  USB_H2_HWHOST (USB_H2_BASE_ADDR +0x008) //   Host Hardware Parameters               
#define  USB_H2_HWTXBUF (USB_H2_BASE_ADDR +0x010) //   TX Buffer Hardware Parameters          
#define  USB_H2_HWRXBUF (USB_H2_BASE_ADDR +0x014) //   RX Buffer Hardware Parameters          
#define  USB_H2_CAPLENGTH (USB_H2_BASE_ADDR +0x100) //   Capability Register Length             
#define  USB_H2_HCIVERSION (USB_H2_BASE_ADDR +0x102) //   Host Interface Version Number          
#define  USB_H2_HCSPARAMS (USB_H2_BASE_ADDR +0x104) //   Host Ctrl. Structural Parameters       
#define  USB_H2_HCCPARAMS (USB_H2_BASE_ADDR +0x108) //   Host Ctrl. Capability Parameters       
#define  USB_H2_USBCMD (USB_H2_BASE_ADDR +0x140) //   USB Command                            
#define  USB_H2_USBSTS (USB_H2_BASE_ADDR +0x144) //   USB Status                             
#define  USB_H2_USBINTR (USB_H2_BASE_ADDR +0x148) //   USB Interrupt Enable                   
#define  USB_H2_FRINDEX (USB_H2_BASE_ADDR +0x14C) //   USB Frame Index
#define  USB_H2_PERIODICLISTBASE (USB_H2_BASE_ADDR +0x154) //   Frame List Base Address                
#define  USB_H2_ASYNCLISTADDR (USB_H2_BASE_ADDR +0x158) //   Next Asynchronous List Address         
#define  USB_H2_BURSTSIZE (USB_H2_BASE_ADDR +0x160) //   Programmable Burst Size                
#define  USB_H2_TXFILLTUNING (USB_H2_BASE_ADDR +0x164) //   Host Transmit Pre-Buffer Packet Tuning 
#define  USB_H2_CONFIGFLAG (USB_H2_BASE_ADDR +0x180) //   Configured Flag Register               
#define  USB_H2_PORTSC1 (USB_H2_BASE_ADDR +0x184) //   Port Status/Control                    
#define  USB_H2_USBMODE (USB_H2_BASE_ADDR +0x1A8) //   USB Device Mode                        
  
//#*************  
//#   OTG  
//#*************  
  
#define  USB_OTG_ID (USB_OTG_BASE_ADDR + 0x000) //   Identification Register
#define  USB_OTG_HWGENERAL (USB_OTG_BASE_ADDR + 0x004) //   General Hardware Parameters
#define  USB_OTG_HWHOST (USB_OTG_BASE_ADDR + 0x008) //   Host Hardware Parameters
#define  USB_OTG_HWDEVICE (USB_OTG_BASE_ADDR + 0x00C) //   Device Hardware Parameters
#define  USB_OTG_HWTXBUF (USB_OTG_BASE_ADDR + 0x010) //   TX Buffer Hardware Parameters
#define  USB_OTG_HWRXBUF (USB_OTG_BASE_ADDR + 0x014) //   RX Buffer Hardware Parameters
#define  USB_OTG_CAPLENGTH (USB_OTG_BASE_ADDR + 0x100) //   Capability Register Length
#define  USB_OTG_HCIVERSION (USB_OTG_BASE_ADDR + 0x102) //   Host Interface Version Number
#define  USB_OTG_HCSPARAMS (USB_OTG_BASE_ADDR + 0x104) //   Host Ctrl. Structural Parameters
#define  USB_OTG_HCCPARAMS (USB_OTG_BASE_ADDR + 0x108) //   Host Ctrl. Capability Parameters
#define  USB_OTG_DCIVERSION (USB_OTG_BASE_ADDR + 0x120) //   Dev. Interface Version Number
#define  USB_OTG_DCCPARAMS (USB_OTG_BASE_ADDR + 0x124) //   Device Ctrl. Capability Parameters
  
#define  USB_OTG_USBCMD (USB_OTG_BASE_ADDR + 0x140) //   USB Command
#define  USB_OTG_USBSTS (USB_OTG_BASE_ADDR + 0x144) //   USB Status
#define  USB_OTG_USBINTR (USB_OTG_BASE_ADDR + 0x148) //   USB Interrupt Enable
#define  USB_OTG_FRINDEX (USB_OTG_BASE_ADDR+ 0x14C) //   USB Frame Index
#define  USB_OTG_PERIODICLISTBASE (USB_OTG_BASE_ADDR + 0x154) //   Frame List Base Address
//#      USB_OTG_Device Addr (USB_OTG_BASE_ADDR + 0x154) //   USB Device Address
#define  USB_OTG_ASYNCLISTADDR (USB_OTG_BASE_ADDR + 0x158) //   Next Asynchronous List Address
//#      USB_OTG_Endpointlist Addr (USB_OTG_BASE_ADDR + 0x158) //   Address at Endpoint list in memory
#define  USB_OTG_BURSTSIZE (USB_OTG_BASE_ADDR + 0x160) //   Programmable Burst Size
#define  USB_OTG_TXFILLTUNING (USB_OTG_BASE_ADDR + 0x164) //   Host Transmit Pre-Buffer Packet Tuning
#define  USB_OTG_CONFIGFLAG (USB_OTG_BASE_ADDR + 0x180) //   Configured Flag Register
#define  USB_OTG_PORTSC1 (USB_OTG_BASE_ADDR + 0x184) //   Port Status/Control  
#define  USB_OTG_OTGSC (USB_OTG_BASE_ADDR + 0x1A4) //   On-The-Go (OTG) Status and Control   
#define  USB_OTG_USBMODE (USB_OTG_BASE_ADDR + 0x1A8) //   USB Device Mode
#define  USB_OTG_ENPDTSETUPSTAT (USB_OTG_BASE_ADDR + 0x1AC) //   Endpoint Setup Status
#define  USB_OTG_ENDPTPRIME (USB_OTG_BASE_ADDR + 0x1B0) //   Endpoint Initialization
#define  USB_OTG_ENDPTFLUSH (USB_OTG_BASE_ADDR + 0x1B4) //   Endpoint De-Initialize
#define  USB_OTG_ENDPTSTATUS (USB_OTG_BASE_ADDR + 0x1B8) //   Endpoint Status
#define  USB_OTG_ENDPTCOMPLETE (USB_OTG_BASE_ADDR + 0x1BC) //   Endpoint Complete
#define  USB_OTG_ENDPTCTRL0 (USB_OTG_BASE_ADDR + 0x1C0) //   Endpoint Control 0
#define  USB_OTG_ENDPTCTRL1 (USB_OTG_BASE_ADDR + 0x1C4) //   Endpoint Control 1
#define  USB_OTG_ENDPTCTRL2 (USB_OTG_BASE_ADDR + 0x1C8) //   Endpoint Control 2
#define  USB_OTG_ENDPTCTRL3 (USB_OTG_BASE_ADDR + 0x1CC) //   Endpoint Control 3
#define  USB_OTG_ENDPTCTRL4 (USB_OTG_BASE_ADDR + 0x1D0) //   Endpoint Control 4
#define  USB_OTG_ENDPTCTRL5 (USB_OTG_BASE_ADDR + 0x1D4) //   Endpoint Control 5
#define  USB_OTG_ENDPTCTRL6 (USB_OTG_BASE_ADDR + 0x1D8) //   Endpoint Control 6
#define  USB_OTG_ENDPTCTRL7 (USB_OTG_BASE_ADDR + 0x1DC) //   Endpoint Control 7
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
//#########################################  
//# RTIC                                #  
//# $53FE_C000 to $53FE_FFFF              #  
//#########################################  
#define RTIC_BASE_ADDR 0x53FEC000 
#define RTIC_STATUS (RTIC_BASE_ADDR+0x000) //  base location for core
#define RTIC_COMMAND (RTIC_BASE_ADDR+0x004) //  base location for function
#define RTIC_CONTROL (RTIC_BASE_ADDR+0x008) //  base location for host
#define RTIC_DELAY_TIMER (RTIC_BASE_ADDR+0x00C) //  base location for dma
#define RTIC_MEMORYA_ADD1 (RTIC_BASE_ADDR+0x010) //  base location for dma
#define RTIC_MEMORYA_LEN1 (RTIC_BASE_ADDR+0x014) //  base location for dma
#define RTIC_MEMORYA_ADD2 (RTIC_BASE_ADDR+0x018) //  base location for dma
#define RTIC_MEMORYA_LEN2 (RTIC_BASE_ADDR+0x01C) //  base location for dma
  
  
#define RTIC_MEMORYB_ADD1 (RTIC_BASE_ADDR+0x030) //  base location for dma
#define RTIC_MEMORYB_LEN1 (RTIC_BASE_ADDR+0x034) //  base location for dma
#define RTIC_MEMORYB_ADD2 (RTIC_BASE_ADDR+0x038) //  base location for dma
#define RTIC_MEMORYB_LEN2 (RTIC_BASE_ADDR+0x03C) //  base location for dma
  
#define RTIC_MEMORYC_ADD1 (RTIC_BASE_ADDR+0x050) //  base location for dma
#define RTIC_MEMORYC_LEN1 (RTIC_BASE_ADDR+0x054) //  base location for dma
#define RTIC_MEMORYC_ADD2 (RTIC_BASE_ADDR+0x058) //  base location for dma
#define RTIC_MEMORYC_LEN2 (RTIC_BASE_ADDR+0x05C) //  base location for dma
  
#define RTIC_MEMORYD_ADD1 (RTIC_BASE_ADDR+0x070) //  base location for dma
#define RTIC_MEMORYD_LEN1 (RTIC_BASE_ADDR+0x074) //  base location for dma
#define RTIC_MEMORYD_ADD2 (RTIC_BASE_ADDR+0x078) //  base location for dma
#define RTIC_MEMORYD_LEN2 (RTIC_BASE_ADDR+0x07C) //  base location for dma
  
#define RTIC_FAULT_ADD (RTIC_BASE_ADDR+0x090) //  base location for dma
#define RTIC_WATCHDOG (RTIC_BASE_ADDR+0x094) //  base location for dma
  
#define RTIC_HASHA_128 (RTIC_BASE_ADDR+0x0A0) //  base location for dma
#define RTIC_HASHA_96 (RTIC_BASE_ADDR+0x0A4) //  base location for dma
#define RTIC_HASHA_64 (RTIC_BASE_ADDR+0x0A8) //  base location for dma
#define RTIC_HASHA_32 (RTIC_BASE_ADDR+0x0AC) //  base location for dma
#define RTIC_HASHA_0 (RTIC_BASE_ADDR+0x0B0) //  base location for dma
  
  
#define RTIC_HASHB_128 (RTIC_BASE_ADDR+0x0C0) //  base location for dma
#define RTIC_HASHB_96 (RTIC_BASE_ADDR+0x0C4) //  base location for dma
#define RTIC_HASHB_64 (RTIC_BASE_ADDR+0x0C8) //  base location for dma
#define RTIC_HASHB_32 (RTIC_BASE_ADDR+0x0CC) //  base location for dma
#define RTIC_HASHB_0 (RTIC_BASE_ADDR+0x0D0) //  base location for dma
  
  
#define RTIC_HASHC_128 (RTIC_BASE_ADDR+0x0E0) //  base location for dma
#define RTIC_HASHC_96 (RTIC_BASE_ADDR+0x0E4) //  base location for dma
#define RTIC_HASHC_64 (RTIC_BASE_ADDR+0x0E8) //  base location for dma
#define RTIC_HASHC_32 (RTIC_BASE_ADDR+0x0EC) //  base location for dma
#define RTIC_HASHC_0 (RTIC_BASE_ADDR+0x0F0) //  base location for dma
  
  
#define RTIC_HASHD_128 (RTIC_BASE_ADDR+0x100) //  base location for dma
#define RTIC_HASHD_96 (RTIC_BASE_ADDR+0x104) //  base location for dma
#define RTIC_HASHD_64 (RTIC_BASE_ADDR+0x108) //  base location for dma
#define RTIC_HASHD_32 (RTIC_BASE_ADDR+0x10C) //  base location for dma
#define RTIC_HASHD_0 (RTIC_BASE_ADDR+0x110) //  base location for dma
  
  
  
//#########################################  
//# RNGA                                  #  
//# $53FB_0000 to $53FB_3FFF              #  
//#########################################  
  
#define RNGA_BASE_ADDR 0x53FB0000 
#define RNGA_CONTROL (RNGA_BASE_ADDR+0x000) //  base location for core
#define RNGA_STATUS (RNGA_BASE_ADDR+0x004) //  base location for core
#define RNGA_ENTROPHY_REG (RNGA_BASE_ADDR+0x008) //  base location for core
#define RNGA_OUTPUT_FIFO (RNGA_BASE_ADDR+0x00C) //  base location for core
#define RNGA_MODE (RNGA_BASE_ADDR+0x010) //  base location for core
#define RNGA_VERIF_CONTROL (RNGA_BASE_ADDR+0x014) //  base location for core
#define RNGA_OSC_CTL_COUNTER (RNGA_BASE_ADDR+0x018) //  base location for core
#define RNGA_OSC1_COUNTER (RNGA_BASE_ADDR+0x01C) //  base location for core
#define RNGA_OSC2_COUNTER (RNGA_BASE_ADDR+0x020) //  base location for core
#define RNGA_COUNTER_STAT (RNGA_BASE_ADDR+0x024) //  base location for core
  
  
//#########################################  
//# SDMA                                  #  
//# $53FD_4000 to $53FD_7FFF              #  
//#########################################  
  
#define SDMA_BASE_ADDR 0x53FD4000 
#define SDMA_COPTR (SDMA_BASE_ADDR+0x000) //  base location for core
#define SDMA_INTR (SDMA_BASE_ADDR+0x004) //  base location for core
#define SDMA_STOP (SDMA_BASE_ADDR+0x008) //  base location for core
#define SDMA_START (SDMA_BASE_ADDR+0x00C) //  base location for core
#define SDMA_EVTOVR (SDMA_BASE_ADDR+0x010) //  base location for core
#define SDMA_DSPOVR (SDMA_BASE_ADDR+0x014) 
#define SDMA_HOSTOVR (SDMA_BASE_ADDR+0x018) //  base location for core
#define SDMA_EVTPEND (SDMA_BASE_ADDR+0x01C) //  base location for core
#define SDMA_DSPENBL (SDMA_BASE_ADDR+0x020) 
#define SDMA_RESET (SDMA_BASE_ADDR+0x024) //  base location for core
#define SDMA_EVTERR (SDMA_BASE_ADDR+0x028) //  base location for core
#define SDMA_INTRMASK (SDMA_BASE_ADDR+0x02C) //  base location for core
#define SDMA_PSW (SDMA_BASE_ADDR+0x030) //  base location for core
#define SDMA_EVTERRDBG (SDMA_BASE_ADDR+0x034) //  base location for core
#define SDMA_CTXSW_MODE (SDMA_BASE_ADDR+0x038) //  base location for core
#define SDMA_ONCE_ENB (SDMA_BASE_ADDR+0x040) //  base location for core
#define SDMA_ONCE_DATA (SDMA_BASE_ADDR+0x044) //  base location for core
#define SDMA_ONCE_INSTR (SDMA_BASE_ADDR+0x048) //  base location for core
#define SDMA_ONCE_STAT (SDMA_BASE_ADDR+0x04C) //  base location for core
#define SDMA_ONCE_CMD (SDMA_BASE_ADDR+0x050) //  base location for core
#define SDMA_EVENTS (SDMA_BASE_ADDR+0x054) //  base location for core
#define SDMA_ILLINSTADDR (SDMA_BASE_ADDR+0x058) //  base location for core
#define SDMA_CHN0ADDR (SDMA_BASE_ADDR+0x05C) //  base location for core
#define SDMA_ONCE_RTB (SDMA_BASE_ADDR+0x060) 
#define SDMA_ONCE_TB (SDMA_BASE_ADDR+0x064) 
#define SDMA_CHENBL_0 (SDMA_BASE_ADDR+0x080) 
#define SDMA_CHENBL_1 (SDMA_BASE_ADDR+0x084) //  base location for core
#define SDMA_CHENBL_2 (SDMA_BASE_ADDR+0x088) //  base location for core
#define SDMA_CHENBL_3 (SDMA_BASE_ADDR+0x08C) //  base location for core
#define SDMA_CHENBL_4 (SDMA_BASE_ADDR+0x090) //  base location for core
#define SDMA_CHENBL_5 (SDMA_BASE_ADDR+0x094) //  base location for core
#define SDMA_CHENBL_6 (SDMA_BASE_ADDR+0x098) //  base location for core
#define SDMA_CHENBL_7 (SDMA_BASE_ADDR+0x09C) //  base location for core
#define SDMA_CHENBL_8 (SDMA_BASE_ADDR+0x0A0) //  base location for core
#define SDMA_CHENBL_9 (SDMA_BASE_ADDR+0x0A4) 
#define SDMA_CHENBL_10 (SDMA_BASE_ADDR+0x0A8) 
#define SDMA_CHENBL_11 (SDMA_BASE_ADDR+0x0AC) 
#define SDMA_CHENBL_12 (SDMA_BASE_ADDR+0x0B0) 
#define SDMA_CHENBL_13 (SDMA_BASE_ADDR+0x0B4) 
#define SDMA_CHENBL_14 (SDMA_BASE_ADDR+0x0B8) 
#define SDMA_CHENBL_15 (SDMA_BASE_ADDR+0x0BC) 
#define SDMA_CHENBL_16 (SDMA_BASE_ADDR+0x0C0) 
#define SDMA_CHENBL_17 (SDMA_BASE_ADDR+0x0C4) 
#define SDMA_CHENBL_18 (SDMA_BASE_ADDR+0x0C8) 
#define SDMA_CHENBL_19 (SDMA_BASE_ADDR+0x0CC) 
#define SDMA_CHENBL_20 (SDMA_BASE_ADDR+0x0D0) 
#define SDMA_CHENBL_21 (SDMA_BASE_ADDR+0x0D4) 
#define SDMA_CHENBL_22 (SDMA_BASE_ADDR+0x0D8) 
#define SDMA_CHENBL_23 (SDMA_BASE_ADDR+0x0DC) 
#define SDMA_CHENBL_24 (SDMA_BASE_ADDR+0x0E0) 
#define SDMA_CHENBL_25 (SDMA_BASE_ADDR+0x0E4) 
#define SDMA_CHENBL_26 (SDMA_BASE_ADDR+0x0E8) 
#define SDMA_CHENBL_27 (SDMA_BASE_ADDR+0x0EC) 
#define SDMA_CHENBL_28 (SDMA_BASE_ADDR+0x0F0) 
#define SDMA_CHENBL_29 (SDMA_BASE_ADDR+0x0F4) 
#define SDMA_CHENBL_30 (SDMA_BASE_ADDR+0x0F8) 
#define SDMA_CHENBL_31 (SDMA_BASE_ADDR+0x0FC) 
#define SDMA_CHNPRI_0 (SDMA_BASE_ADDR+0x100) 
#define SDMA_CHNPRI_1 (SDMA_BASE_ADDR+0x104) 
#define SDMA_CHNPRI_2 (SDMA_BASE_ADDR+0x108) 
#define SDMA_CHNPRI_3 (SDMA_BASE_ADDR+0x10C) 
#define SDMA_CHNPRI_4 (SDMA_BASE_ADDR+0x110) 
#define SDMA_CHNPRI_5 (SDMA_BASE_ADDR+0x114) 
#define SDMA_CHNPRI_6 (SDMA_BASE_ADDR+0x118) 
#define SDMA_CHNPRI_7 (SDMA_BASE_ADDR+0x11C) 
#define SDMA_CHNPRI_8 (SDMA_BASE_ADDR+0x120) 
#define SDMA_CHNPRI_9 (SDMA_BASE_ADDR+0x124) 
#define SDMA_CHNPRI_10 (SDMA_BASE_ADDR+0x128) 
#define SDMA_CHNPRI_11 (SDMA_BASE_ADDR+0x12C) 
#define SDMA_CHNPRI_12 (SDMA_BASE_ADDR+0x130) 
#define SDMA_CHNPRI_13 (SDMA_BASE_ADDR+0x134) 
#define SDMA_CHNPRI_14 (SDMA_BASE_ADDR+0x138) 
#define SDMA_CHNPRI_15 (SDMA_BASE_ADDR+0x13C) 
#define SDMA_CHNPRI_16 (SDMA_BASE_ADDR+0x140) 
#define SDMA_CHNPRI_17 (SDMA_BASE_ADDR+0x144) 
#define SDMA_CHNPRI_18 (SDMA_BASE_ADDR+0x148) 
#define SDMA_CHNPRI_19 (SDMA_BASE_ADDR+0x14C) 
#define SDMA_CHNPRI_20 (SDMA_BASE_ADDR+0x150) 
#define SDMA_CHNPRI_21 (SDMA_BASE_ADDR+0x154) 
#define SDMA_CHNPRI_22 (SDMA_BASE_ADDR+0x158) 
#define SDMA_CHNPRI_23 (SDMA_BASE_ADDR+0x15C) 
#define SDMA_CHNPRI_24 (SDMA_BASE_ADDR+0x160) 
#define SDMA_CHNPRI_25 (SDMA_BASE_ADDR+0x164) 
#define SDMA_CHNPRI_26 (SDMA_BASE_ADDR+0x168) 
#define SDMA_CHNPRI_27 (SDMA_BASE_ADDR+0x16C) 
#define SDMA_CHNPRI_28 (SDMA_BASE_ADDR+0x170) 
#define SDMA_CHNPRI_29 (SDMA_BASE_ADDR+0x174) 
#define SDMA_CHNPRI_30 (SDMA_BASE_ADDR+0x178) 
#define SDMA_CHNPRI_31 (SDMA_BASE_ADDR+0x17C) 
#define SDMA_ONCE_COUNT (SDMA_BASE_ADDR+0x200) 
#define SDMA_ONCE_ECTL (SDMA_BASE_ADDR+0x204) 
#define SDMA_ONCE_EAA (SDMA_BASE_ADDR+0x208) 
#define SDMA_ONCE_EAB (SDMA_BASE_ADDR+0x20C) 
#define SDMA_ONCE_EAM (SDMA_BASE_ADDR+0x210) 
#define SDMA_ONCE_ED (SDMA_BASE_ADDR+0x214) 
#define SDMA_ONCE_EDM (SDMA_BASE_ADDR+0x218) 
#define SDMA_ONCE_PCMATCH (SDMA_BASE_ADDR+0x21C) 
  
//#########################################  
//# Interrupt List  
//#                                                                            
//#########################################  
  
#define RESERVED1_INT 0 
#define RESERVED2_INT 1 
#define RESERVED3_INT 2 
#define I2C3_INT 3 
#define I2C2_INT 4 
#define MPEG4_INT 5 
#define RTIC_INT 6 
#define FIRI_INT 7 
#define SDHC2_INT 8 
#define SDHC1_INT 9 
#define I2C1_INT 10 
#define SSI2_INT 11 
#define SSI1_INT 12 
#define CSPI2_INT 13 
#define CSPI1_INT 14 
#define ATA_INT 15 
#define MBX_INT 16 
#define CSPI3_INT 17 
#define UART3_ANDED_INT 18 
#define IIM_INT 19 
#define SIM_IPB_INT 20 
#define SIM_DATA_INT 21 
#define RNG_INT 22 
#define EVTMON_INT 23 
#define KPP_INT 24 
#define RTC_INT 25 
#define PWM_INT 26 
#define EPIT2_INT 27 
#define EPIT1_INT 28 
#define GPT_INT 29 
#define RESERVED9_INT 30 
#define RESERVED8_INT 31 
#define UART2_ANDED_INT 32 
#define NFC_INT 33 
#define SDMA_INT 34 
#define USBH1_INT 35 
#define USBH2_INT 36 
#define USBOTG_INT 37 
#define RESERVED4_INT 38 
#define MSHC1_INT 39 
#define MSHC2_INT 40 
#define IPU_ERROR_INT 41 
#define IPU_FUNC_INT 42 
#define RESERVED7_INT 43 
#define RESERVED6_INT 44 
#define UART1_ANDED_INT 45 
#define UART4_ANDED_INT 46 
#define UART5_ANDED_INT 47 
#define ECT_INT 48 
#define SCM_INT 49 
#define SMN_INT 50 
#define GPIO2_INT 51 
#define GPIO1_INT 52 
#define CCM_INT 53 
#define PCMCIA_INT 54 
#define WDOG_INT 55 
#define GPIO3_INT 56 
#define RESERVED5_INT 57 
#define PMIC_INT 58 
#define EXT_INT4_INT 59 
#define EXT_INT3_INT 60 
#define EXT_INT2_INT 61 
#define EXT_INT1_INT 62 
#define EXT_INT0_INT 63 
  
  
  
  
  
  
  
  
  
  
  
  
//#########################################  
//# AVIC_IVR                                 #  
//# $1FFFFEDC to $1FFFFDE0              #  
//#########################################  
  
#define AVIC_IVR 0x1FFFFEDC 
#define RESERVED1_INT_ROUTINE 0x1FFFFEDC 
#define RESERVED2_INT_ROUTINE 0x1FFFFED8 
#define RESERVED3_INT_ROUTINE 0x1FFFFED4 
#define I2C3_INT_ROUTINE 0x1FFFFED0 
#define I2C2_INT_ROUTINE 0x1FFFFECC 
#define MPEG4_INT_ROUTINE 0x1FFFFEC8 
#define RTIC_INT_ROUTINE 0x1FFFFEC4 
#define FIRI_INT_ROUTINE 0x1FFFFEC0 
#define SDHC2_INT_ROUTINE 0x1FFFFEBC 
#define SDHC1_INT_ROUTINE 0x1FFFFEB8 
#define I2C1_INT_ROUTINE 0x1FFFFEB4 
#define SSI2_INT_ROUTINE 0x1FFFFEB0 
#define SSI1_INT_ROUTINE 0x1FFFFEAC 
#define CSPI2_INT_ROUTINE 0x1FFFFEA8 
#define CSPI1_INT_ROUTINE 0x1FFFFEA4 
#define ATA_INT_ROUTINE 0x1FFFFEA0 
#define MBX_INT_ROUTINE 0x1FFFFE9C 
#define CSPI3_INT_ROUTINE 0x1FFFFE98 
#define UART3_ANDED_INT_ROUTINE 0x1FFFFE94 
#define IIM_INT_ROUTINE 0x1FFFFE90 
#define SIM_IPB_INT_ROUTINE 0x1FFFFE8C 
#define SIM_DATA_INT_ROUTINE 0x1FFFFE88 
#define RNG_INT_ROUTINE 0x1FFFFE84 
#define EVTMON_INT_ROUTINE 0x1FFFFE80 
#define KPP_INT_ROUTINE 0x1FFFFE7C 
#define RTC_INT_ROUTINE 0x1FFFFE78 
#define PWM_INT_ROUTINE 0x1FFFFE74 
#define EPIT2_INT_ROUTINE 0x1FFFFE70 
#define EPIT1_INT_ROUTINE 0x1FFFFE6C 
#define GPT_INT_ROUTINE 0x1FFFFE68 
#define RESERVED9_INT_ROUTINE 0x1FFFFE64 
#define RESERVED8_INT_ROUTINE 0x1FFFFE60 
#define UART2_ANDED_INT_ROUTINE 0x1FFFFE5C 
#define NFC_INT_ROUTINE 0x1FFFFE58 
#define SDMA_INT_ROUTINE 0x1FFFFE54 
#define USBH1_INT_ROUTINE 0x1FFFFE50 
#define USBH2_INT_ROUTINE 0x1FFFFE4C 
#define USBOTG_INT_ROUTINE 0x1FFFFE48 
#define RESERVED4_INT_ROUTINE 0x1FFFFE44 
#define MSHC1_INT_ROUTINE 0x1FFFFE40 
#define MSHC2_INT_ROUTINE 0x1FFFFE3C 
#define IPU_ERROR_INT_ROUTINE 0x1FFFFE38 
#define IPU_FUNC_INT_ROUTINE 0x1FFFFE34 
#define RESERVED7_INT_ROUTINE 0x1FFFFE30 
#define RESERVED6_INT_ROUTINE 0x1FFFFE2C 
#define UART1_ANDED_INT_ROUTINE 0x1FFFFE28 
#define UART4_ANDED_INT_ROUTINE 0x1FFFFE24 
#define UART5_ANDED_INT_ROUTINE 0x1FFFFE20 
#define ECT_INT_ROUTINE 0x1FFFFE1C 
#define SCM_INT_ROUTINE 0x1FFFFE18 
#define SMN_INT_ROUTINE 0x1FFFFE14 
#define GPIO2_INT_ROUTINE 0x1FFFFE10 
#define GPIO1_INT_ROUTINE 0x1FFFFE0C 
#define CCM_INT_ROUTINE 0x1FFFFE08 
#define PCMCIA_INT_ROUTINE 0x1FFFFE04 
#define WDOG_INT_ROUTINE 0x1FFFFE00 
#define GPIO3_INT_ROUTINE 0x1FFFFDFC 
#define RESERVED5_INT_ROUTINE 0x1FFFFDF8 
#define PMIC_INT_ROUTINE 0x1FFFFDF4 
#define EXT_INT4_INT_ROUTINE 0x1FFFFDF0 
#define EXT_INT3_INT_ROUTINE 0x1FFFFDEC 
#define EXT_INT2_INT_ROUTINE 0x1FFFFDE8 
#define EXT_INT1_INT_ROUTINE 0x1FFFFDE4 
#define EXT_INT0_INT_ROUTINE 0x1FFFFDE0 
  
  
  
  
//#########################################  
//# AVIC_FVR                                 #  
//# $1FFFFEDC to $1FFFFDE0              #  
//#########################################  
  
#define AVIC_FVR 0x1FFFFDDC 
#define RESERVED1_FAST_ROUTINE 0x1FFFFDDC 
#define RESERVED2_FAST_ROUTINE 0x1FFFFDD8 
#define RESERVED3_FAST_ROUTINE 0x1FFFFDD4 
#define I2C3_FAST_ROUTINE 0x1FFFFDD0 
#define I2C2_FAST_ROUTINE 0x1FFFFDCC 
#define MPEG4_FAST_ROUTINE 0x1FFFFDC8 
#define RTIC_FAST_ROUTINE 0x1FFFFDC4 
#define FIRI_FAST_ROUTINE 0x1FFFFDC0 
#define SDHC2_FAST_ROUTINE 0x1FFFFDBC 
#define SDHC1_FAST_ROUTINE 0x1FFFFDB8 
#define I2C1_FAST_ROUTINE 0x1FFFFDB4 
#define SSI2_FAST_ROUTINE 0x1FFFFDB0 
#define SSI1_FAST_ROUTINE 0x1FFFFDAC 
#define CSPI2_FAST_ROUTINE 0x1FFFFDA8 
#define CSPI1_FAST_ROUTINE 0x1FFFFDA4 
#define ATA_FAST_ROUTINE 0x1FFFFDA0 
#define MBX_FAST_ROUTINE 0x1FFFFD9C 
#define CSPI3_FAST_ROUTINE 0x1FFFFD98 
#define UART3_ANDED_FAST_ROUTINE 0x1FFFFD94 
#define IIM_FAST_ROUTINE 0x1FFFFD90 
#define SIM_IPB_FAST_ROUTINE 0x1FFFFD8C 
#define SIM_DATA_FAST_ROUTINE 0x1FFFFD88 
#define RNG_FAST_ROUTINE 0x1FFFFD84 
#define EVTMON_FAST_ROUTINE 0x1FFFFD80 
#define KPP_FAST_ROUTINE 0x1FFFFD7C 
#define RTC_FAST_ROUTINE 0x1FFFFD78 
#define PWM_FAST_ROUTINE 0x1FFFFD74 
#define EPIT2_FAST_ROUTINE 0x1FFFFD70 
#define EPIT1_FAST_ROUTINE 0x1FFFFD6C 
#define GPT_FAST_ROUTINE 0x1FFFFD68 
#define RESERVED9_FAST_ROUTINE 0x1FFFFD64 
#define RESERVED8_FAST_ROUTINE 0x1FFFFD60 
#define UART2_ANDED_FAST_ROUTINE 0x1FFFFD5C 
#define NFC_FAST_ROUTINE 0x1FFFFD58 
#define SDMA_FAST_ROUTINE 0x1FFFFD54 
#define USBH1_FAST_ROUTINE 0x1FFFFD50 
#define USBH2_FAST_ROUTINE 0x1FFFFD4C 
#define USBOTG_FAST_ROUTINE 0x1FFFFD48 
#define RESERVED4_FAST_ROUTINE 0x1FFFFD44 
#define MSHC1_FAST_ROUTINE 0x1FFFFD40 
#define MSHC2_FAST_ROUTINE 0x1FFFFD3C 
#define IPU_ERROR_FAST_ROUTINE 0x1FFFFD38 
#define IPU_FUNC_FAST_ROUTINE 0x1FFFFD34 
#define RESERVED7_FAST_ROUTINE 0x1FFFFD30 
#define RESERVED6_FAST_ROUTINE 0x1FFFFD2C 
#define UART1_ANDED_FAST_ROUTINE 0x1FFFFD28 
#define UART4_ANDED_FAST_ROUTINE 0x1FFFFD24 
#define UART5_ANDED_FAST_ROUTINE 0x1FFFFD20 
#define ECT_FAST_ROUTINE 0x1FFFFD1C 
#define SCM_FAST_ROUTINE 0x1FFFFD18 
#define SMN_FAST_ROUTINE 0x1FFFFD14 
#define GPIO2_FAST_ROUTINE 0x1FFFFD10 
#define GPIO1_FAST_ROUTINE 0x1FFFFD0C 
#define CCM_FAST_ROUTINE 0x1FFFFD08 
#define PCMCIA_FAST_ROUTINE 0x1FFFFD04 
#define WDOG_FAST_ROUTINE 0x1FFFFD00 
#define GPIO3_FAST_ROUTINE 0x1FFFFCFC 
#define RESERVED5_FAST_ROUTINE 0x1FFFFCF8 
#define PMIC_FAST_ROUTINE 0x1FFFFCF4 
#define EXT_INT4_FAST_ROUTINE 0x1FFFFCF0 
#define EXT_INT3_FAST_ROUTINE 0x1FFFFCEC 
#define EXT_INT2_FAST_ROUTINE 0x1FFFFCE8 
#define EXT_INT1_FAST_ROUTINE 0x1FFFFCE4 
#define EXT_INT0_FAST_ROUTINE 0x1FFFFCE0 
  
  
  
//#########################################  
//# MPEG4_ENC                               #  
//# $53FC_8000 to $53FC_BFFF              #  
//#########################################  
#define MPEG4_ENC_BASE 0x53FC8000 
#define MP4ENC_BASE_ADDR 0x53FC8000 
#define MP4ENC_ENCREG0 (MP4ENC_BASE_ADDR+0x00) 
#define MP4ENC_ENCREG1 (MP4ENC_BASE_ADDR+0x04) 
#define MP4ENC_ENCREG2 (MP4ENC_BASE_ADDR+0x08) 
#define MP4ENC_STREAMLIMITREG (MP4ENC_BASE_ADDR+0x0C) 
#define MP4ENC_INTERRUPTREG (MP4ENC_BASE_ADDR+0x10) 
#define MP4ENC_RESULTBASEREG (MP4ENC_BASE_ADDR+0x14) 
#define MP4ENC_NBBASEREG (MP4ENC_BASE_ADDR+0x18) 
#define MP4ENC_NBCBBASEREG (MP4ENC_BASE_ADDR+0x1C) 
#define MP4ENC_NBCRBASEREG (MP4ENC_BASE_ADDR+0x20) 
#define MP4ENC_STREAMINGREG (MP4ENC_BASE_ADDR+0x24) 
#define MP4ENC_REMAINDERREG (MP4ENC_BASE_ADDR+0x28) 
#define MP4ENC_STREAM1BASEREG (MP4ENC_BASE_ADDR+0x2C) 
#define MP4ENC_STREAM2BASEREG (MP4ENC_BASE_ADDR+0x30) 
#define MP4ENC_STREAM3BASEREG (MP4ENC_BASE_ADDR+0x34) 
#define MP4ENC_SALUMBASEREG (MP4ENC_BASE_ADDR+0x38) 
#define MP4ENC_SACHREADBASEREG (MP4ENC_BASE_ADDR+0x3C) 
#define MP4ENC_SACHWRITEBASEREG (MP4ENC_BASE_ADDR+0x40) 
#define MP4ENC_CIRREG (MP4ENC_BASE_ADDR+0x44) 
#define MP4ENC_CHECKPOINTREG0 (MP4ENC_BASE_ADDR+0x48) 
#define MP4ENC_CHECKPOINTREG1 (MP4ENC_BASE_ADDR+0x4C) 
#define MP4ENC_CHECKPOINTREG2 (MP4ENC_BASE_ADDR+0x50) 
#define MP4ENC_CHECKPOINTREG3 (MP4ENC_BASE_ADDR+0x54) 
#define MP4ENC_CHECKPOINTREG4 (MP4ENC_BASE_ADDR+0x58) 
#define MP4ENC_TARGETREG0 (MP4ENC_BASE_ADDR+0x5C) 
#define MP4ENC_TARGETREG1 (MP4ENC_BASE_ADDR+0x60) 
#define MP4ENC_TARGETREG2 (MP4ENC_BASE_ADDR+0x64) 
#define MP4ENC_TARGETREG3 (MP4ENC_BASE_ADDR+0x68) 
#define MP4ENC_TARGETREG4 (MP4ENC_BASE_ADDR+0x6C) 
#define MP4ENC_ERRORREG0 (MP4ENC_BASE_ADDR+0x70) 
#define MP4ENC_ERRORREG1 (MP4ENC_BASE_ADDR+0x74) 
#define MP4ENC_ERRORREG2 (MP4ENC_BASE_ADDR+0x78) 
#define MP4ENC_DELTAQPREG (MP4ENC_BASE_ADDR+0x7C) 
#define MP4ENC_BITLIMITREG (MP4ENC_BASE_ADDR+0x80) 
#define MP4ENC_GOBPLACEREG (MP4ENC_BASE_ADDR+0x84) 
#define MP4ENC_IDREG (MP4ENC_BASE_ADDR+0x88) 
  
  
  
  
  
//#########################################  
//# SCC                               #  
//# $53FA_C000 to $53FA_FFFF              #  
//#########################################  
#define SCC_BASE_ADDR 0x53FAC000 
#define SCM_BASE_ADDR 0x53FAE000 
#define SMN_BASE_ADDR 0x53FAF000 
#define SCM_RED_START (SCM_BASE_ADDR+0x00) 
#define SCM_BLACK_START (SCM_BASE_ADDR+0x04) 
#define SCM_LENGTH (SCM_BASE_ADDR+0x08) 
#define SCM_CONTROL (SCM_BASE_ADDR+0x0C) 
#define SCM_STATUS (SCM_BASE_ADDR+0x10) 
#define SCM_ERROR (SCM_BASE_ADDR+0x14) 
#define SCM_INT_CONTROL (SCM_BASE_ADDR+0x18) 
#define SCM_CONFIGURATION (SCM_BASE_ADDR+0x1C) 
#define SCM_INIT_VECTOR0 (SCM_BASE_ADDR+0x20) 
#define SCM_INIT_VECTOR1 (SCM_BASE_ADDR+0x24) 
  
#define SMN_STATUS (SMN_BASE_ADDR+0x00) 
#define SMN_COMMAND (SMN_BASE_ADDR+0x04) 
#define SMN_SEQSTART (SMN_BASE_ADDR+0x08) 
#define SMN_SEQEND (SMN_BASE_ADDR+0x0C) 
#define SMN_SEQCHK (SMN_BASE_ADDR+0x10) 
#define SMN_BITCNT (SMN_BASE_ADDR+0x14) 
#define SMN_INCSIZE (SMN_BASE_ADDR+0x18) 
#define SMN_BBDEC (SMN_BASE_ADDR+0x1C) 
#define SMN_COMPSIZE (SMN_BASE_ADDR+0x20) 
#define SMN_PTCHK (SMN_BASE_ADDR+0x24) 
#define SMN_CTCHK (SMN_BASE_ADDR+0x28) 
#define SMN_TIMERIV (SMN_BASE_ADDR+0x2C) 
#define SMN_TIMERCTL (SMN_BASE_ADDR+0x30) 
#define SMN_DDSTATUS (SMN_BASE_ADDR+0x34) 
#define SMN_TIMER (SMN_BASE_ADDR+0x38) 
  
  
//#########################################  
//# PCMCIA                              #  
//# $B800_4000 to $B800_4FFF              #  
//#########################################  
#define PCMCIA_BASE_ADDR 0xB8004000 
#define PCMCIA_PIPR (PCMCIA_BASE_ADDR+0x00) 
#define PCMCIA_PSCR (PCMCIA_BASE_ADDR+0x04) 
#define PCMCIA_PER (PCMCIA_BASE_ADDR+0x08) 
#define PCMCIA_PBR0 (PCMCIA_BASE_ADDR+0x0C) 
#define PCMCIA_PBR1 (PCMCIA_BASE_ADDR+0x10) 
#define PCMCIA_PBR2 (PCMCIA_BASE_ADDR+0x14) 
#define PCMCIA_PBR3 (PCMCIA_BASE_ADDR+0x18) 
#define PCMCIA_PBR4 (PCMCIA_BASE_ADDR+0x1C) 
#define PCMCIA_PBR5 (PCMCIA_BASE_ADDR+0x20) 
#define PCMCIA_PBR6 (PCMCIA_BASE_ADDR+0x24) 
#define PCMCIA_POR0 (PCMCIA_BASE_ADDR+0x28) 
#define PCMCIA_POR1 (PCMCIA_BASE_ADDR+0x2C) 
#define PCMCIA_POR2 (PCMCIA_BASE_ADDR+0x30) 
#define PCMCIA_POR3 (PCMCIA_BASE_ADDR+0x34) 
#define PCMCIA_POR4 (PCMCIA_BASE_ADDR+0x38) 
#define PCMCIA_POR5 (PCMCIA_BASE_ADDR+0x3C) 
#define PCMCIA_POR6 (PCMCIA_BASE_ADDR+0x40) 
#define PCMCIA_POFR0 (PCMCIA_BASE_ADDR+0x44) 
#define PCMCIA_POFR1 (PCMCIA_BASE_ADDR+0x48) 
#define PCMCIA_POFR2 (PCMCIA_BASE_ADDR+0x4C) 
#define PCMCIA_POFR3 (PCMCIA_BASE_ADDR+0x50) 
#define PCMCIA_POFR4 (PCMCIA_BASE_ADDR+0x54) 
#define PCMCIA_POFR5 (PCMCIA_BASE_ADDR+0x58) 
#define PCMCIA_POFR6 (PCMCIA_BASE_ADDR+0x5C) 
#define PCMCIA_PGCR (PCMCIA_BASE_ADDR+0x60) 
#define PCMCIA_PGSR (PCMCIA_BASE_ADDR+0x64) 
  
//#########################################  
//# PCMCF                             #  
//# $BC00_0000 to $BFFF_FFFF              #  
//#########################################  
  
  
#define PCMCF_BASE_ADDR 0xBC000000 
#define PCMCF_END_ADDR 0xBFFFFFFF 
  
  
  
  
  
//#########################################  
//# AUDMUX                             #  
//# $53FC_4000 to $53FC_7FFF              #  
//#########################################  
#define AUDMUX_BASE_ADDR 0x53FC4000 
#define AUDMUX_HPCR1 (AUDMUX_BASE_ADDR+0x00) //   Host Port Control Register 1
#define AUDMUX_HPDCR1 (AUDMUX_BASE_ADDR+0x04) //   Host Port Data Control Register 1 
#define AUDMUX_HPCR2 (AUDMUX_BASE_ADDR+0x08) //   Host Port Control Register 2
#define AUDMUX_HPDCR2 (AUDMUX_BASE_ADDR+0x0C) //   Host Port Data Control Register 2
#define AUDMUX_HPCR3 (AUDMUX_BASE_ADDR+0x10) //   Host Port Control Register 3
#define AUDMUX_HPDCR3 (AUDMUX_BASE_ADDR+0x14) //   Host Port Data Control Register 3
#define AUDMUX_PPCR1 (AUDMUX_BASE_ADDR+0x18) //   Peripheral Port Control Register 1
#define AUDMUX_PPDCR1 (AUDMUX_BASE_ADDR+0x1C) //   Peripheral Port Control Register 2
#define AUDMUX_PPCR2 (AUDMUX_BASE_ADDR+0x20) //   Peripheral Port Control Register 3
#define AUDMUX_PPDCR2 (AUDMUX_BASE_ADDR+0x24) //   Peripheral Port Control Register 4
#define AUDMUX_PPCR3 (AUDMUX_BASE_ADDR+0x28) //   Peripheral Port Data Control Register 1
#define AUDMUX_PPDCR3 (AUDMUX_BASE_ADDR+0x2C) //   Peripheral Port Data Control Register 2
#define AUDMUX_PPCR4 (AUDMUX_BASE_ADDR+0x30) //   Peripheral Port Data Control Register 3
#define AUDMUX_PPDCR4 (AUDMUX_BASE_ADDR+0x34) //   Peripheral Port Data Control Register 4
#define AUDMUX_CNMCR (AUDMUX_BASE_ADDR+0x38) //   CE Bus Control Register 
  
  
  
//#########################################  
//# M3IF                             #  
//# $B800_3000 to $B800_3FFF              #  
//#########################################  
#define M3IF_BASE_ADDR 0xB8003000 
#define M3IF_CTL (M3IF_BASE_ADDR+0x00) 
#define M3IF_WCFG0 (M3IF_BASE_ADDR+0x04) 
#define M3IF_WCFG1 (M3IF_BASE_ADDR+0x08) 
#define M3IF_WCFG2 (M3IF_BASE_ADDR+0x0C) 
#define M3IF_WCFG3 (M3IF_BASE_ADDR+0x10) 
#define M3IF_WCFG4 (M3IF_BASE_ADDR+0x14) 
#define M3IF_WCFG5 (M3IF_BASE_ADDR+0x18) 
#define M3IF_WCFG6 (M3IF_BASE_ADDR+0x1C) 
#define M3IF_WCFG7 (M3IF_BASE_ADDR+0x20) 
#define M3IF_WCSR (M3IF_BASE_ADDR+0x24) 
#define M3IF_SCFG0 (M3IF_BASE_ADDR+0x28) 
#define M3IF_SCFG1 (M3IF_BASE_ADDR+0x2C) 
#define M3IF_SCFG2 (M3IF_BASE_ADDR+0x30) 
#define M3IF_SSR0 (M3IF_BASE_ADDR+0x34) 
#define M3IF_SSR1 (M3IF_BASE_ADDR+0x38) 
  
//#########################################  
//# NFC                             #  
//# $B800_0000 to $B800_0FFF              #  
//#########################################  
#define NFC_BASE_ADDR 0xB8000000 
#define NFC_REG_BASE_ADDR (NFC_BASE_ADDR+0xE00) 
#define NFC_BUFSIZE (NFC_REG_BASE_ADDR +0x00) 
#define NFC_BLK_ADD_LOCK (NFC_REG_BASE_ADDR +0x02) 
#define NFC_RAM_BUF_ADDR (NFC_REG_BASE_ADDR +0x04) 
#define NFC_NAND_FLASH_ADDR (NFC_REG_BASE_ADDR +0x06) 
#define NFC_NAND_FLASH_CMD (NFC_REG_BASE_ADDR +0x08) 
#define NFC_CONFIGURATION (NFC_REG_BASE_ADDR +0x0A) 
#define NFC_ECC_STAT_RES (NFC_REG_BASE_ADDR +0x0C) 
#define NFC_ECC_RSLT_MA (NFC_REG_BASE_ADDR +0x0E) 
#define NFC_ECC_RSLT_SA (NFC_REG_BASE_ADDR +0x10) 
#define NFC_NF_WR_PROT (NFC_REG_BASE_ADDR +0x12) 
#define NFC_ULOCK_START_BLK (NFC_REG_BASE_ADDR +0x14) 
#define NFC_ULOCK_END_BLK (NFC_REG_BASE_ADDR +0x16) 
#define NFC_NF_WR_PROT_STAT (NFC_REG_BASE_ADDR +0x18) 
#define NFC_NF_CONFIG1 (NFC_REG_BASE_ADDR +0x1A) 
#define NFC_NF_CONFIG2 (NFC_REG_BASE_ADDR +0x1C) 
  
//#########################################  
//# ESDCTL and MDDR  
//# $B800_1000 to $B800_1FFF              #  
//#########################################  
#define ESDCTL_BASE_ADDR 0xB8001000 
#define ESD_ESDCTL0  (ESDCTL_BASE_ADDR+0x00) 
#define ESD_ESDCFG0 (ESDCTL_BASE_ADDR+0x04) 
#define ESD_ESDCTL1 (ESDCTL_BASE_ADDR+0x08) 
#define ESD_ESDCFG1 (ESDCTL_BASE_ADDR+0x0C) 
#define ESD_ESDMISC (ESDCTL_BASE_ADDR+0x10) 
#define CONFIG_DATA_MDDR1 (ESDCTL_BASE_ADDR+0x20) 
#define CONFIG_DATA_MDDR2 (ESDCTL_BASE_ADDR+0x24) 
#define CONFIG_DATA_MDDR3 (ESDCTL_BASE_ADDR+0x28) 
#define CONFIG_DATA_MDDR4 (ESDCTL_BASE_ADDR+0x2C) 
#define CONFIG_DATA_MDDR5 (ESDCTL_BASE_ADDR+0x30) 
#define DEL_CYCL_LEN_MDDR (ESDCTL_BASE_ADDR+0x34) 
#define CONFIG_DATA_MDDR6 (ESDCTL_BASE_ADDR+0x38) 
  
  
  
  
  
  
//#########################################  
//# GPIO2                                #  
//# $53FD0000to $53FD3FFF             #  
//#########################################  
#define GPIO2_BASE_ADDR 0x53FD0000 
#define GPIO2_DR0 (GPIO2_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define GPIO2_GDIR0 (GPIO2_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define GPIO2_PSR0 (GPIO2_BASE_ADDR+0x08) //  32bit gpio pta output config 2 reg
#define GPIO2_ICR1 (GPIO2_BASE_ADDR+0x0C) //  32bit gpio pta input config A1 reg
#define GPIO2_ICR2 (GPIO2_BASE_ADDR+0x10) //  32bit gpio pta input config A2 reg
#define GPIO2_IMR (GPIO2_BASE_ADDR+0x14) //  32bit gpio pta input config B1 reg
#define GPIO2_ISR (GPIO2_BASE_ADDR+0x18) 
  
  
//#########################################  
//# SPBA                                #  
//# $50000000to $5003FFFF             #  
//#########################################  
#define SPBA_BASE_ADDR 0x50000000 
#define SPBA_PER0_START_ADDR (SPBA_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define SPBA_PER1_START_ADDR (SPBA_BASE_ADDR+0x4000) //  32bit gpio pta output config 1 reg
#define SPBA_PER2_START_ADDR (SPBA_BASE_ADDR+0x8000) //  32bit gpio pta output config 2 reg
#define SPBA_PER3_START_ADDR (SPBA_BASE_ADDR+0xC000) 
#define SPBA_PER4_START_ADDR (SPBA_BASE_ADDR+0x10000) 
#define SPBA_PER5_START_ADDR (SPBA_BASE_ADDR+0x14000) 
#define SPBA_PER6_START_ADDR (SPBA_BASE_ADDR+0x18000) 
#define SPBA_PER7_START_ADDR (SPBA_BASE_ADDR+0x1C000) 
#define SPBA_PER8_START_ADDR (SPBA_BASE_ADDR+0x20000) 
#define SPBA_PER9_START_ADDR (SPBA_BASE_ADDR+0x24000) 
#define SPBA_PER10_START_ADDR (SPBA_BASE_ADDR+0x28000) 
#define SPBA_PER11_START_ADDR (SPBA_BASE_ADDR+0x2C000) 
#define SPBA_PER12_START_ADDR (SPBA_BASE_ADDR+0x30000) 
#define SPBA_PER13_START_ADDR (SPBA_BASE_ADDR+0x34000) 
#define SPBA_PER14_START_ADDR (SPBA_BASE_ADDR+0x38000) 
#define SPBA_REG_ADDR (SPBA_BASE_ADDR+0x3C000) 
  
#define SPBA_PRR0 (SPBA_REG_ADDR+0x00) 
#define SPBA_PRR1 (SPBA_REG_ADDR+0x04) 
#define SPBA_PRR2 (SPBA_REG_ADDR+0x08) 
#define SPBA_PRR3 (SPBA_REG_ADDR+0x0C) 
#define SPBA_PRR4 (SPBA_REG_ADDR+0x10) 
#define SPBA_PRR5 (SPBA_REG_ADDR+0x14) 
#define SPBA_PRR6 (SPBA_REG_ADDR+0x18) 
#define SPBA_PRR7 (SPBA_REG_ADDR+0x1C) 
#define SPBA_PRR8 (SPBA_REG_ADDR+0x20) 
#define SPBA_PRR9 (SPBA_REG_ADDR+0x24) 
#define SPBA_PRR10 (SPBA_REG_ADDR+0x28) 
#define SPBA_PRR11 (SPBA_REG_ADDR+0x2C) 
#define SPBA_PRR12 (SPBA_REG_ADDR+0x30) 
#define SPBA_PRR13 (SPBA_REG_ADDR+0x34) 
#define SPBA_PRR14 (SPBA_REG_ADDR+0x38) 
  
//#########################################  
//# CLKCTL                                #  
//# $43F0C000  to $43F0FFFF           #  
//#########################################  
#define CTL_BASE_ADDR 0x43F0C000 
#define CTL_GP_CTRL (CTL_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define CTL_GP_SER (CTL_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define CTL_GP_CER (CTL_BASE_ADDR+0x08) 
#define CTL_GP_STAT (CTL_BASE_ADDR+0x0C) 
  
//#########################################  
//# EVTMON                                #  
//# $43F08000  to $43F0BFFF           #  
//#########################################  
#define EVTMON_BASE_ADDR 0x43F08000 
#define EVTMON_EMMC (EVTMON_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define EVTMON_EMCS (EVTMON_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define EVTMON_EMCC0 (EVTMON_BASE_ADDR+0x08) 
#define EVTMON_EMCC1 (EVTMON_BASE_ADDR+0x0C) 
#define EVTMON_EMCC2 (EVTMON_BASE_ADDR+0x10) 
#define EVTMON_EMCC3 (EVTMON_BASE_ADDR+0x14) 
#define EVTMON_EMC0 (EVTMON_BASE_ADDR+0x18) 
#define EVTMON_EMC1 (EVTMON_BASE_ADDR+0x1C) 
#define EVTMON_EMC2 (EVTMON_BASE_ADDR+0x20) 
#define EVTMON_EMC3 (EVTMON_BASE_ADDR+0x24) 
  
  
//#########################################  
//# ETB                                #  
//# $43F1000  to $43F13FFF           #  
//#########################################  
#define ETB_BASE_ADDR 0x43F10000 
#define ETB_ID (ETB_BASE_ADDR+0x00) //  Identification Register
#define ETB_RAM_DEPTH (ETB_BASE_ADDR+0x04) //  RAM Depth Register
#define ETB_RAM_WIDTH (ETB_BASE_ADDR+0x08) //  RAM Width Register
#define ETB_STATUS (ETB_BASE_ADDR+0x0C) //  Status Register
#define ETB_RAM_W_PTR (ETB_BASE_ADDR+0x18) //  RAM Write Pointer Register
#define ETB_TRG_CNT (ETB_BASE_ADDR+0x1C) //  Trigger Counter Register
#define ETB_CTL (ETB_BASE_ADDR+0x20) //  Control Register
  
//#########################################  
//# L2CC                               #  
//# $43F08000  to $43F0BFFF           #  
//#########################################  
#define L2_BASE_ADDR 0x30000000 
#define L2_CASH_ID (L2_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define L2_CASH_TYPE (L2_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define L2_CONTROL (L2_BASE_ADDR+0x100) 
#define L2_AUX_CONTROL (L2_BASE_ADDR+0x104) 
#define L2_CASH_SYNC (L2_BASE_ADDR+0x730) 
#define L2_INVALID_BY_WAY (L2_BASE_ADDR+0x77C) 
#define L2_INVALID_LINE_BY_PA (L2_BASE_ADDR+0x770) 
#define L2_CLEAN_LINE_BY_WAY (L2_BASE_ADDR+0x7B8) 
#define L2_CLEAN_BY_WAY (L2_BASE_ADDR+0x7BC) 
#define L2_CLEAN_BY_PA (L2_BASE_ADDR+0x7B0) 
#define L2_CLEAN_INV_LINE_BY_WAY (L2_BASE_ADDR+0x7F8) 
#define L2_CLEAN_INV_BY_WAY (L2_BASE_ADDR+0x7FC) 
#define L2_CLEAN_INV_LINE_BY_PA (L2_BASE_ADDR+0x7F0) 
#define L2_LOCKDOWN_DSIDE (L2_BASE_ADDR+0x900) 
#define L2_LOCKDOWN_ISIDE (L2_BASE_ADDR+0x904) 
#define L2_TEST_OPERATION (L2_BASE_ADDR+0xF00) 
#define L2_LINE_DATA (L2_BASE_ADDR+0xF10) 
#define L2_LINE_TAG (L2_BASE_ADDR+0xF30) 
#define L2_DEBUG_CONTROL (L2_BASE_ADDR+0xF40) 
  
  
  
//#########################################  
//# I2C2                                   #  
//# $43F9_8000 to $43F9_BFFF              #  
//#########################################  
#define I2C2_BASE_ADDR 0x43F98000 
#define I2C2_IADR (I2C2_BASE_ADDR+0x00) 
#define I2C2_IFDR (I2C2_BASE_ADDR+0x04) 
#define I2C2_I2CR (I2C2_BASE_ADDR+0x08) 
#define I2C2_I2SR (I2C2_BASE_ADDR+0x0C) 
#define I2C2_I2DR (I2C2_BASE_ADDR+0x10) 
  
  
  
  
  
  
  
  
//#########################################  
//# I2C3                                  #  
//# $43F8_4000 to $43F8_7FFF              #  
//#########################################  
#define I2C3_BASE_ADDR 0x43F84000 
#define I2C3_IADR (I2C3_BASE_ADDR+0x00) 
#define I2C3_IFDR (I2C3_BASE_ADDR+0x04) 
#define I2C3_I2CR (I2C3_BASE_ADDR+0x08) 
#define I2C3_I2SR (I2C3_BASE_ADDR+0x0C) 
#define I2C3_I2DR (I2C3_BASE_ADDR+0x10) 
  
  
  
  
  
//#########################################  
//# ATA                                 #  
//# $43F8_C000 to $43F8_FFFF              #  
//#########################################  
#define ATA_BASE_ADDR 0x43F8C000 
#define ATA_TIME_CONFIG0 (ATA_BASE_ADDR+0x00) 
#define ATA_TIME_CONFIG1 (ATA_BASE_ADDR+0x04) 
#define ATA_TIME_CONFIG2 (ATA_BASE_ADDR+0x08) 
#define ATA_TIME_CONFIG3 (ATA_BASE_ADDR+0x0C) 
#define ATA_TIME_CONFIG4 (ATA_BASE_ADDR+0x10) 
#define ATA_TIME_CONFIG5 (ATA_BASE_ADDR+0x14) 
#define ATA_FIFO_DATA_32 (ATA_BASE_ADDR+0x18) 
#define ATA_FIFO_DATA_16 (ATA_BASE_ADDR+0x1C) 
#define ATA_FIFO_FILL (ATA_BASE_ADDR+0x20) 
#define ATA_CONTROL (ATA_BASE_ADDR+0x24) 
#define ATA_INT_PENDING (ATA_BASE_ADDR+0x28) 
#define ATA_INT_ENABLE (ATA_BASE_ADDR+0x2C) 
#define ATA_INT_CLEAR (ATA_BASE_ADDR+0x30) 
#define FIFO_ALARM (ATA_BASE_ADDR+0x34) 
#define ATA_DCTR (ATA_BASE_ADDR+0xD8) // drive control register (w), alt. stat reg (r)
#define ATA_DDTR (ATA_BASE_ADDR+0xA0) // drive data register (rw)
#define ATA_DFTR (ATA_BASE_ADDR+0xA4) // drive features regi (w), error reg (r)
#define ATA_DSCR (ATA_BASE_ADDR+0xA8) //  drive sector count reg
#define ATA_DSNR (ATA_BASE_ADDR+0xAC) //  drive sector number reg
#define ATA_DCLR (ATA_BASE_ADDR+0xB0) // drive cylinder low reg
#define ATA_DCHR (ATA_BASE_ADDR+0xB4) //  drive cylinder high reg 
#define ATA_DDHR (ATA_BASE_ADDR+0xB8) //  drive device head reg
#define ATA_DCDR (ATA_BASE_ADDR+0xBC) //  drive command reg (w), status reg (r)
  
//#########################################  
//# ECT1                                #  
//# $43FB_8000 to $43FB_BFFF              #  
//#########################################  
#define ECT1_BASE_ADDR 0x43FB8000 
#define ECT1_CTICONTROL (ECT1_BASE_ADDR+0x0) //  CTI Control Register
#define ECT1_CTISTATUS (ECT1_BASE_ADDR+0x4) //  CTI Status Register
#define ECT1_CTILOCK (ECT1_BASE_ADDR+0x8) //  CTI Lock Enable Register
#define ECT1_CTIPROTECTION (ECT1_BASE_ADDR+0x00C) //  CTI Protection Enable Register
#define ECT1_CTIINTACK (ECT1_BASE_ADDR+0x10) //  CTI Interrupt Acknowledge Register
#define ECT1_CTIAPPTEST (ECT1_BASE_ADDR+0x14) //  CTI Application Trigger Set Register
#define ECT1_CTIAPPCLEAR (ECT1_BASE_ADDR+0x18) //  CTI Application Trigger Clear Register
#define ECT1_CTIAPPPULSE (ECT1_BASE_ADDR+0x1C) //  CTI Application Pulse Register
#define ECT1_CTIINEN0 (ECT1_BASE_ADDR+0x20) //  CTI Trigger to Channel Enable Register
#define ECT1_CTIINEN1 (ECT1_BASE_ADDR+0x24) 
#define ECT1_CTIINEN2 (ECT1_BASE_ADDR+0x28) 
#define ECT1_CTIINEN3 (ECT1_BASE_ADDR+0x02C) 
#define ECT1_CTIINEN4 (ECT1_BASE_ADDR+0x30) 
#define ECT1_CTIINEN5 (ECT1_BASE_ADDR+0x34) 
#define ECT1_CTIINEN6 (ECT1_BASE_ADDR+0x38) 
#define ECT1_CTIINEN7 (ECT1_BASE_ADDR+0x03C) 
#define ECT1_CTIOUTEN0 (ECT1_BASE_ADDR+0x0A0) //  CTI Channel to Trigger Enable Regier
#define ECT1_CTIOUTEN1 (ECT1_BASE_ADDR+0x0A4) 
#define ECT1_CTIOUTEN2 (ECT1_BASE_ADDR+0x0A8) 
#define ECT1_CTIOUTEN3 (ECT1_BASE_ADDR+0x0AC) 
#define ECT1_CTIOUTEN4 (ECT1_BASE_ADDR+0x0B0) 
#define ECT1_CTIOUTEN5 (ECT1_BASE_ADDR+0x0B4) 
#define ECT1_CTIOUTEN6 (ECT1_BASE_ADDR+0x0B8) 
#define ECT1_CTIOUTEN7 (ECT1_BASE_ADDR+0x0BC) 
#define ECT1_CTITRIGINSTATUS (ECT1_BASE_ADDR+0x130) //  CTI Trigger In Status Register
#define ECT1_CTITRIGOUTSTATUS (ECT1_BASE_ADDR+0x134) //  CTI Trigger Out Status Register
#define ECT1_CTICHINSTATUS (ECT1_BASE_ADDR+0x138) //  CTI Channel In Status Register
#define ECT1_CTICHOUTSTATUS (ECT1_BASE_ADDR+0x13C) //  CTI Channel Out Status Register
#define ECT1_CTIITCR (ECT1_BASE_ADDR+0x200) //  CTI Test Control Register
#define ECT1_CTIITIP0 (ECT1_BASE_ADDR+0x204) //  CTI Input Test Register 0
#define ECT1_CTIITIP1 (ECT1_BASE_ADDR+0x208) //  CTI Input Test Register 1
#define ECT1_CTIITIP2 (ECT1_BASE_ADDR+0x20C) //  CTI Input Test Register 2
#define ECT1_CTIITIP3 (ECT1_BASE_ADDR+0x210) //  CTI Input Test Register 3
#define ECT1_CTITIOP0 (ECT1_BASE_ADDR+0x214) //  CTI Output Test Register 0
#define ECT1_CTITIOP1 (ECT1_BASE_ADDR+0x218) //  CTI Output Test Register 1
#define ECT1_CTITIOP2 (ECT1_BASE_ADDR+0x21C) //  CTI Output Test Register 2
#define ECT1_CTITIOP3 (ECT1_BASE_ADDR+0x220) //  CTI Output Test Register 3
#define ECT1_CTIPERIPHID0 (ECT1_BASE_ADDR+0xFE0) //  CTI Peripheral Identification Register 0
#define ECT1_CTIPERIPHID1 (ECT1_BASE_ADDR+0xFE4) //  CTI Peripheral Identification Register 1
#define ECT1_CTIPERIPHID2 (ECT1_BASE_ADDR+0xFE8) //  CTI Peripheral Identification Register 2
#define ECT1_CTIPERIPHID3 (ECT1_BASE_ADDR+0xFEC) //  CTI Peripheral Identification Register 3
#define ECT1_CTIPCELLID0 (ECT1_BASE_ADDR+0xFF0) //  CTI Identification Register 0
#define ECT1_CTIPCELLID1 (ECT1_BASE_ADDR+0xFF4) //  CTI Identification Register 1
#define ECT1_CTIPCELLID2 (ECT1_BASE_ADDR+0xFF8) //  CTI Identification Register 2
#define ECT1_CTIPCELLID3 (ECT1_BASE_ADDR+0xFFC) //  CTI Identification Register 3
  
  
  
//#########################################  
//# ECT2                                #  
//# $43FB_C000 to $43FB_FFFF              #  
//#########################################  
#define ECT2_BASE_ADDR 0x43FBC000 
#define ECT2_CTICONTROL (ECT2_BASE_ADDR+0x0) //  CTI Control Register
#define ECT2_CTISTATUS (ECT2_BASE_ADDR+0x4) //  CTI Status Register
#define ECT2_CTILOCK (ECT2_BASE_ADDR+0x8) //  CTI Lock Enable Register
#define ECT2_CTIPROTECTION (ECT2_BASE_ADDR+0x00C) //  CTI Protection Enable Register
#define ECT2_CTIINTACK (ECT2_BASE_ADDR+0x10) //  CTI Interrupt Acknowledge Register
#define ECT2_CTIAPPTEST (ECT2_BASE_ADDR+0x14) //  CTI Application Trigger Set Register
#define ECT2_CTIAPPCLEAR (ECT2_BASE_ADDR+0x18) //  CTI Application Trigger Clear Register
#define ECT2_CTIAPPPULSE (ECT2_BASE_ADDR+0x1C) //  CTI Application Pulse Register
#define ECT2_CTIINEN0 (ECT2_BASE_ADDR+0x20) //  CTI Trigger to Channel Enable Register
#define ECT2_CTIINEN1 (ECT2_BASE_ADDR+0x24) 
#define ECT2_CTIINEN2 (ECT2_BASE_ADDR+0x28) 
#define ECT2_CTIINEN3 (ECT2_BASE_ADDR+0x02C) 
#define ECT2_CTIINEN4 (ECT2_BASE_ADDR+0x30) 
#define ECT2_CTIINEN5 (ECT2_BASE_ADDR+0x34) 
#define ECT2_CTIINEN6 (ECT2_BASE_ADDR+0x38) 
#define ECT2_CTIINEN7 (ECT2_BASE_ADDR+0x03C) 
#define ECT2_CTIOUTEN0 (ECT2_BASE_ADDR+0x0A0) //  CTI Channel to Trigger Enable Regier
#define ECT2_CTIOUTEN1 (ECT2_BASE_ADDR+0x0A4) 
#define ECT2_CTIOUTEN2 (ECT2_BASE_ADDR+0x0A8) 
#define ECT2_CTIOUTEN3 (ECT2_BASE_ADDR+0x0AC) 
#define ECT2_CTIOUTEN4 (ECT2_BASE_ADDR+0x0B0) 
#define ECT2_CTIOUTEN5 (ECT2_BASE_ADDR+0x0B4) 
#define ECT2_CTIOUTEN6 (ECT2_BASE_ADDR+0x0B8) 
#define ECT2_CTIOUTEN7 (ECT2_BASE_ADDR+0x0BC) 
#define ECT2_CTITRIGINSTATUS (ECT2_BASE_ADDR+0x130) //  CTI Trigger In Status Register
#define ECT2_CTITRIGOUTSTATUS (ECT2_BASE_ADDR+0x134) //  CTI Trigger Out Status Register
#define ECT2_CTICHINSTATUS (ECT2_BASE_ADDR+0x138) //  CTI Channel In Status Register
#define ECT2_CTICHOUTSTATUS (ECT2_BASE_ADDR+0x13C) //  CTI Channel Out Status Register
#define ECT2_CTIITCR (ECT2_BASE_ADDR+0x200) //  CTI Test Control Register
#define ECT2_CTIITIP0 (ECT2_BASE_ADDR+0x204) //  CTI Input Test Register 0
#define ECT2_CTIITIP1 (ECT2_BASE_ADDR+0x208) //  CTI Input Test Register 1
#define ECT2_CTIITIP2 (ECT2_BASE_ADDR+0x20C) //  CTI Input Test Register 2
#define ECT2_CTIITIP3 (ECT2_BASE_ADDR+0x210) //  CTI Input Test Register 3
#define ECT2_CTITIOP0 (ECT2_BASE_ADDR+0x214) //  CTI Output Test Register 0
#define ECT2_CTITIOP1 (ECT2_BASE_ADDR+0x218) //  CTI Output Test Register 1
#define ECT2_CTITIOP2 (ECT2_BASE_ADDR+0x21C) //  CTI Output Test Register 2
#define ECT2_CTITIOP3 (ECT2_BASE_ADDR+0x220) //  CTI Output Test Register 3
#define ECT2_CTIPERIPHID0 (ECT2_BASE_ADDR+0xFE0) //  CTI Peripheral Identification Register 0
#define ECT2_CTIPERIPHID1 (ECT2_BASE_ADDR+0xFE4) //  CTI Peripheral Identification Register 1
#define ECT2_CTIPERIPHID2 (ECT2_BASE_ADDR+0xFE8) //  CTI Peripheral Identification Register 2
#define ECT2_CTIPERIPHID3 (ECT2_BASE_ADDR+0xFEC) //  CTI Peripheral Identification Register 3
#define ECT2_CTIPCELLID0 (ECT2_BASE_ADDR+0xFF0) //  CTI Identification Register 0
#define ECT2_CTIPCELLID1 (ECT2_BASE_ADDR+0xFF4) //  CTI Identification Register 1
#define ECT2_CTIPCELLID2 (ECT2_BASE_ADDR+0xFF8) //  CTI Identification Register 2
#define ECT2_CTIPCELLID3 (ECT2_BASE_ADDR+0xFFC) //  CTI Identification Register 3
  
//#########################################  
//# ARMP_ECT                                #  
//# $43F1_8000 to $43F1_BFFF              #  
//#########################################  
#define ARMP_ECT_BASE_ADDR 0x43F18000 
#define ARMP_ECT_CTICONTROL (ARMP_ECT_BASE_ADDR+0x0) //  CTI Control Register
#define ARMP_ECT_CTISTATUS (ARMP_ECT_BASE_ADDR+0x4) //  CTI Status Register
#define ARMP_ECT_CTILOCK (ARMP_ECT_BASE_ADDR+0x8) //  CTI Lock Enable Register
#define ARMP_ECT_CTIPROTECTION (ARMP_ECT_BASE_ADDR+0x00C) //  CTI Protection Enable Register
#define ARMP_ECT_CTIINTACK (ARMP_ECT_BASE_ADDR+0x10) //  CTI Interrupt Acknowledge Register
#define ARMP_ECT_CTIAPPTEST (ARMP_ECT_BASE_ADDR+0x14) //  CTI Application Trigger Set Register
#define ARMP_ECT_CTIAPPCLEAR (ARMP_ECT_BASE_ADDR+0x18) //  CTI Application Trigger Clear Register
#define ARMP_ECT_CTIAPPPULSE (ARMP_ECT_BASE_ADDR+0x1C) //  CTI Application Pulse Register
#define ARMP_ECT_CTIINEN0 (ARMP_ECT_BASE_ADDR+0x20) //  CTI Trigger to Channel Enable Register
#define ARMP_ECT_CTIINEN1 (ARMP_ECT_BASE_ADDR+0x24) 
#define ARMP_ECT_CTIINEN2 (ARMP_ECT_BASE_ADDR+0x28) 
#define ARMP_ECT_CTIINEN3 (ARMP_ECT_BASE_ADDR+0x02C) 
#define ARMP_ECT_CTIINEN4 (ARMP_ECT_BASE_ADDR+0x30) 
#define ARMP_ECT_CTIINEN5 (ARMP_ECT_BASE_ADDR+0x34) 
#define ARMP_ECT_CTIINEN6 (ARMP_ECT_BASE_ADDR+0x38) 
#define ARMP_ECT_CTIINEN7 (ARMP_ECT_BASE_ADDR+0x03C) 
#define ARMP_ECT_CTIOUTEN0 (ARMP_ECT_BASE_ADDR+0x0A0) //  CTI Channel to Trigger Enable Regier
#define ARMP_ECT_CTIOUTEN1 (ARMP_ECT_BASE_ADDR+0x0A4) 
#define ARMP_ECT_CTIOUTEN2 (ARMP_ECT_BASE_ADDR+0x0A8) 
#define ARMP_ECT_CTIOUTEN3 (ARMP_ECT_BASE_ADDR+0x0AC) 
#define ARMP_ECT_CTIOUTEN4 (ARMP_ECT_BASE_ADDR+0x0B0) 
#define ARMP_ECT_CTIOUTEN5 (ARMP_ECT_BASE_ADDR+0x0B4) 
#define ARMP_ECT_CTIOUTEN6 (ARMP_ECT_BASE_ADDR+0x0B8) 
#define ARMP_ECT_CTIOUTEN7 (ARMP_ECT_BASE_ADDR+0x0BC) 
#define ARMP_ECT_CTITRIGINSTATUS (ARMP_ECT_BASE_ADDR+0x130) //  CTI Trigger In Status Register
#define ARMP_ECT_CTITRIGOUTSTATUS (ARMP_ECT_BASE_ADDR+0x134) //  CTI Trigger Out Status Register
#define ARMP_ECT_CTICHINSTATUS (ARMP_ECT_BASE_ADDR+0x138) //  CTI Channel In Status Register
#define ARMP_ECT_CTICHOUTSTATUS (ARMP_ECT_BASE_ADDR+0x13C) //  CTI Channel Out Status Register
#define ARMP_ECT_CTIITCR (ARMP_ECT_BASE_ADDR+0x200) //  CTI Test Control Register
#define ARMP_ECT_CTIITIP0 (ARMP_ECT_BASE_ADDR+0x204) //  CTI Input Test Register 0
#define ARMP_ECT_CTIITIP1 (ARMP_ECT_BASE_ADDR+0x208) //  CTI Input Test Register 1
#define ARMP_ECT_CTIITIP2 (ARMP_ECT_BASE_ADDR+0x20C) //  CTI Input Test Register 2
#define ARMP_ECT_CTIITIP3 (ARMP_ECT_BASE_ADDR+0x210) //  CTI Input Test Register 3
#define ARMP_ECT_CTITIOP0 (ARMP_ECT_BASE_ADDR+0x214) //  CTI Output Test Register 0
#define ARMP_ECT_CTITIOP1 (ARMP_ECT_BASE_ADDR+0x218) //  CTI Output Test Register 1
#define ARMP_ECT_CTITIOP2 (ARMP_ECT_BASE_ADDR+0x21C) //  CTI Output Test Register 2
#define ARMP_ECT_CTITIOP3 (ARMP_ECT_BASE_ADDR+0x220) //  CTI Output Test Register 3
#define ARMP_ECT_CTIPERIPHID0 (ARMP_ECT_BASE_ADDR+0xFE0) //  CTI Peripheral Identification Register 0
#define ARMP_ECT_CTIPERIPHID1 (ARMP_ECT_BASE_ADDR+0xFE4) //  CTI Peripheral Identification Register 1
#define ARMP_ECT_CTIPERIPHID2 (ARMP_ECT_BASE_ADDR+0xFE8) //  CTI Peripheral Identification Register 2
#define ARMP_ECT_CTIPERIPHID3 (ARMP_ECT_BASE_ADDR+0xFEC) //  CTI Peripheral Identification Register 3
#define ARMP_ECT_CTIPCELLID0 (ARMP_ECT_BASE_ADDR+0xFF0) //  CTI Identification Register 0
#define ARMP_ECT_CTIPCELLID1 (ARMP_ECT_BASE_ADDR+0xFF4) //  CTI Identification Register 1
#define ARMP_ECT_CTIPCELLID2 (ARMP_ECT_BASE_ADDR+0xFF8) //  CTI Identification Register 2
#define ARMP_ECT_CTIPCELLID3 (ARMP_ECT_BASE_ADDR+0xFFC) //  CTI Identification Register 3
  
  
//#########################################  
//# ECT generic  
//# relative addresses  
//#########################################  
  
#define ECT_CTICONTROL 0x0 //  CTI Control Register
#define ECT_CTISTATUS 0x4 //  CTI Status Register
#define ECT_CTILOCK 0x8 //  CTI Lock Enable Register
#define ECT_CTIPROTECTION 0x00C //  CTI Protection Enable Register
#define ECT_CTIINTACK 0x10 //  CTI Interrupt Acknowledge Register
#define ECT_CTIAPPTEST 0x14 //  CTI Application Trigger Set Register
#define ECT_CTIAPPCLEAR 0x18 //  CTI Application Trigger Clear Register
#define ECT_CTIAPPPULSE 0x1C //  CTI Application Pulse Register
#define ECT_CTIINEN0 0x20 //  CTI Trigger to Channel Enable Register
#define ECT_CTIINEN1 0x24 
#define ECT_CTIINEN2 0x28 
#define ECT_CTIINEN3 0x02C 
#define ECT_CTIINEN4 0x30 
#define ECT_CTIINEN5 0x34 
#define ECT_CTIINEN6 0x38 
#define ECT_CTIINEN7 0x03C 
#define ECT_CTIOUTEN0 0x0A0 //  CTI Channel to Trigger Enable Regier
#define ECT_CTIOUTEN1 0x0A4 
#define ECT_CTIOUTEN2 0x0A8 
#define ECT_CTIOUTEN3 0x0AC 
#define ECT_CTIOUTEN4 0x0B0 
#define ECT_CTIOUTEN5 0x0B4 
#define ECT_CTIOUTEN6 0x0B8 
#define ECT_CTIOUTEN7 0x0BC 
#define ECT_CTITRIGINSTATUS 0x130 //  CTI Trigger In Status Register
#define ECT_CTITRIGOUTSTATUS 0x134 //  CTI Trigger Out Status Register
#define ECT_CTICHINSTATUS 0x138 //  CTI Channel In Status Register
#define ECT_CTICHOUTSTATUS 0x13C //  CTI Channel Out Status Register
#define ECT_CTIITCR 0x200 //  CTI Test Control Register
#define ECT_CTIITIP0 0x204 //  CTI Input Test Register 0
#define ECT_CTIITIP1 0x208 //  CTI Input Test Register 1
#define ECT_CTIITIP2 0x20C //  CTI Input Test Register 2
#define ECT_CTIITIP3 0x210 //  CTI Input Test Register 3
#define ECT_CTITIOP0 0x214 //  CTI Output Test Register 0
#define ECT_CTITIOP1 0x218 //  CTI Output Test Register 1
#define ECT_CTITIOP2 0x21C //  CTI Output Test Register 2
#define ECT_CTITIOP3 0x220 //  CTI Output Test Register 3
#define ECT_CTIPERIPHID0 0xFE0 //  CTI Peripheral Identification Register 0
#define ECT_CTIPERIPHID1 0xFE4 //  CTI Peripheral Identification Register 1
#define ECT_CTIPERIPHID2 0xFE8 //  CTI Peripheral Identification Register 2
#define ECT_CTIPERIPHID3 0xFEC //  CTI Peripheral Identification Register 3
#define ECT_CTIPCELLID0 0xFF0 //  CTI Identification Register 0
#define ECT_CTIPCELLID1 0xFF4 //  CTI Identification Register 1
#define ECT_CTIPCELLID2 0xFF8 //  CTI Identification Register 2
#define ECT_CTIPCELLID3 0xFFC //  CTI Identification Register 3
  
  
  
  
  
  
//#########################################  
//# IIM     
//# $5001_C000 to $5001_FFFF              #  
//#########################################  
#define IIM_BASE_ADDR 0x5001C000 
#define IIM_STAT (IIM_BASE_ADDR+0x0000) 
#define IIM_STATM (IIM_BASE_ADDR+0x0004) 
#define IIM_ERR (IIM_BASE_ADDR+0x0008) 
#define IIM_EMASK (IIM_BASE_ADDR+0x000C) 
#define IIM_FCTL (IIM_BASE_ADDR+0x0010) 
#define IIM_UA (IIM_BASE_ADDR+0x0014) 
#define IIM_LA (IIM_BASE_ADDR+0x0018) 
#define IIM_SDAT (IIM_BASE_ADDR+0x001C) 
#define IIM_PREV (IIM_BASE_ADDR+0x0020) 
#define IIM_SREV (IIM_BASE_ADDR+0x0024) 
#define IIM_PRG_P (IIM_BASE_ADDR+0x0028) 
#define IIM_SCS0 (IIM_BASE_ADDR+0x002C) 
#define IIM_SCS1 (IIM_BASE_ADDR+0x0030) 
#define IIM_SCS2 (IIM_BASE_ADDR+0x0034) 
#define IIM_SCS3 (IIM_BASE_ADDR+0x0038) 
#define IIM_FBAC0 (IIM_BASE_ADDR+0x0800) 
#define IIM_JAC_HWV0 (IIM_BASE_ADDR+0x0804) 
#define IIM_HWV1 (IIM_BASE_ADDR+0x0808) 
#define IIM_HWV2 (IIM_BASE_ADDR+0x080C) 
#define IIM_HAB0 (IIM_BASE_ADDR+0x0810) 
#define IIM_HAB1 (IIM_BASE_ADDR+0x0814) 
#define IIM_PREV_FUSE (IIM_BASE_ADDR+0x0818) 
#define IIM_SREV_FUSE (IIM_BASE_ADDR+0x081C) 
#define IIM_SJC_CHALL_0 (IIM_BASE_ADDR+0x0820) 
#define IIM_SJC_CHALL_1 (IIM_BASE_ADDR+0x0824) 
#define IIM_SJC_CHALL_2 (IIM_BASE_ADDR+0x0828) 
#define IIM_SJC_CHALL_3 (IIM_BASE_ADDR+0x082C) 
#define IIM_SJC_CHALL_4 (IIM_BASE_ADDR+0x0830) 
#define IIM_SJC_CHALL_5 (IIM_BASE_ADDR+0x0834) 
#define IIM_SJC_CHALL_6 (IIM_BASE_ADDR+0x0838) 
#define IIM_SJC_CHALL_7 (IIM_BASE_ADDR+0x083C) 
#define IIM_FB0UC17 (IIM_BASE_ADDR+0x0840) 
#define IIM_FB0UC255 (IIM_BASE_ADDR+0x0BFC) 
#define IIM_FBAC1 (IIM_BASE_ADDR+0x0C00) 
#define IIM_KEY0 (IIM_BASE_ADDR+0x0C04) 
#define IIM_KEY1 (IIM_BASE_ADDR+0x0C08) 
#define IIM_KEY2 (IIM_BASE_ADDR+0x0C0C) 
#define IIM_KEY3 (IIM_BASE_ADDR+0x0C10) 
#define IIM_KEY4 (IIM_BASE_ADDR+0x0C14) 
#define IIM_KEY5 (IIM_BASE_ADDR+0x0C18) 
#define IIM_KEY6 (IIM_BASE_ADDR+0x0C1C) 
#define IIM_KEY7 (IIM_BASE_ADDR+0x0C20) 
#define IIM_KEY8 (IIM_BASE_ADDR+0x0C24) 
#define IIM_KEY9 (IIM_BASE_ADDR+0x0C28) 
#define IIM_KEY10 (IIM_BASE_ADDR+0x0C2C) 
#define IIM_KEY11 (IIM_BASE_ADDR+0x0C30) 
#define IIM_KEY12 (IIM_BASE_ADDR+0x0C34) 
#define IIM_KEY13 (IIM_BASE_ADDR+0x0C38) 
#define IIM_KEY14 (IIM_BASE_ADDR+0x0C3C) 
#define IIM_KEY15 (IIM_BASE_ADDR+0x0C40) 
#define IIM_KEY16 (IIM_BASE_ADDR+0x0C44) 
#define IIM_KEY17 (IIM_BASE_ADDR+0x0C48) 
#define IIM_KEY18 (IIM_BASE_ADDR+0x0C4C) 
#define IIM_KEY19 (IIM_BASE_ADDR+0x0C50) 
#define IIM_KEY20 (IIM_BASE_ADDR+0x0C54) 
#define IIM_SJC_RESP_0 (IIM_BASE_ADDR+0x0C58) 
#define IIM_SJC_RESP_1 (IIM_BASE_ADDR+0x0C5C) 
#define IIM_SJC_RESP_2 (IIM_BASE_ADDR+0x0C60) 
#define IIM_SJC_RESP_3 (IIM_BASE_ADDR+0x0C64) 
#define IIM_SJC_RESP_4 (IIM_BASE_ADDR+0x0C68) 
#define IIM_SJC_RESP_5 (IIM_BASE_ADDR+0x0C6C) 
#define IIM_SJC_RESP_6 (IIM_BASE_ADDR+0x0C70) 
#define IIM_SJC_RESP_7 (IIM_BASE_ADDR+0x0C74) 
#define IIM_FB2UC30 (IIM_BASE_ADDR+0x0C78) 
#define IIM_FB2UC255 (IIM_BASE_ADDR+0x0FFC) 
#define IIM_FBAC2 (IIM_BASE_ADDR+0x1000) 
#define IIM_XCORD (IIM_BASE_ADDR+0x1004) 
#define IIM_YCORD (IIM_BASE_ADDR+0x1008) 
#define IIM_FAB (IIM_BASE_ADDR+0x100C) 
#define IIM_WAFER (IIM_BASE_ADDR+0x1010) 
#define IIM_LOT0 (IIM_BASE_ADDR+0x1014) 
#define IIM_LOT1 (IIM_BASE_ADDR+0x1018) 
#define IIM_LOT2 (IIM_BASE_ADDR+0x101C) 
#define IIM_PROB (IIM_BASE_ADDR+0x1020) 
#define IIM_FT (IIM_BASE_ADDR+0x1024) 
#define IIM_FB1UC10 (IIM_BASE_ADDR+0x1028) 
#define IIM_FB1UC255 (IIM_BASE_ADDR+0x13FC) 
#define IIM_FBAC3 (IIM_BASE_ADDR+0x1400) 
#define IIM_FB3UC1 (IIM_BASE_ADDR+0x1404) 
#define IIM_FB3UC255 (IIM_BASE_ADDR+0x17FC) 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
//#########################################  
//# GPIO3                               #  
//# $53FA4000to $53FA7FFF             #  
//#########################################  
#define GPIO3_BASE_ADDR 0x53FA4000 
#define GPIO3_DR0 (GPIO3_BASE_ADDR+0x00) //  32bit gpio pta data direction reg
#define GPIO3_GDIR0 (GPIO3_BASE_ADDR+0x04) //  32bit gpio pta output config 1 reg
#define GPIO3_PSR0 (GPIO3_BASE_ADDR+0x08) //  32bit gpio pta output config 2 reg
#define GPIO3_ICR1 (GPIO3_BASE_ADDR+0x0C) //  32bit gpio pta input config A1 reg
#define GPIO3_ICR2 (GPIO3_BASE_ADDR+0x10) //  32bit gpio pta input config A2 reg
#define GPIO3_IMR (GPIO3_BASE_ADDR+0x14) //  32bit gpio pta input config B1 reg
#define GPIO3_ISR (GPIO3_BASE_ADDR+0x18) 
  
  
//#########################################  
//# IPU                               #  
//# $53FC0000 to $53FC3FFF             #  
//#########################################  
#define IPU_BASE_ADDR 0x53FC0000 
#define IPU_CONF (IPU_BASE_ADDR+0x000) 
#define IPU_CHA_BUF0_RDY (IPU_BASE_ADDR+0x004) 
#define IPU_CHA_BUF1_RDY (IPU_BASE_ADDR+0x008) 
#define IPU_CHA_DB_MODE_SEL (IPU_BASE_ADDR+0x00C) 
#define IPU_CHA_CUR_BUF (IPU_BASE_ADDR+0x010) 
#define IPU_FS_PROC_FLOW (IPU_BASE_ADDR+0x014) 
#define IPU_FS_DISP_FLOW (IPU_BASE_ADDR+0x018) 
#define IPU_TASKS_STAT (IPU_BASE_ADDR+0x01C) 
#define IPU_IMA_ADDR (IPU_BASE_ADDR+0x020) 
#define IPU_IMA_DATA (IPU_BASE_ADDR+0x024) 
#define IPU_INT_CTRL_1 (IPU_BASE_ADDR+0x028) 
#define IPU_INT_CTRL_2 (IPU_BASE_ADDR+0x02C) 
#define IPU_INT_CTRL_3 (IPU_BASE_ADDR+0x030) 
#define IPU_INT_CTRL_4 (IPU_BASE_ADDR+0x034) 
#define IPU_INT_CTRL_5 (IPU_BASE_ADDR+0x038) 
#define IPU_INT_STAT_1 (IPU_BASE_ADDR+0x03C) 
#define IPU_INT_STAT_2 (IPU_BASE_ADDR+0x040) 
#define IPU_INT_STAT_3 (IPU_BASE_ADDR+0x044) 
#define IPU_INT_STAT_4 (IPU_BASE_ADDR+0x048) 
#define IPU_INT_STAT_5 (IPU_BASE_ADDR+0x04C) 
#define IPU_BRK_CTRL_1 (IPU_BASE_ADDR+0x050) 
#define IPU_BRK_CTRL_2 (IPU_BASE_ADDR+0x054) 
#define IPU_BRK_STAT (IPU_BASE_ADDR+0x058) 
#define IPU_DIAGB_CTRL (IPU_BASE_ADDR+0x05C) 
#define IPU_CSI_SENS_CONF (IPU_BASE_ADDR+0x060) 
#define IPU_CSI_SENS_FRM_SIZE (IPU_BASE_ADDR+0x064) 
#define IPU_CSI_ACT_FRM_SIZE (IPU_BASE_ADDR+0x068) 
#define IPU_CSI_OUT_FRM_CTRL (IPU_BASE_ADDR+0x06C) 
#define IPU_CSI_TST_CTRL (IPU_BASE_ADDR+0x070) 
#define IPU_CSI_CCIR_CODE_1 (IPU_BASE_ADDR+0x074) 
#define IPU_CSI_CCIR_CODE_2 (IPU_BASE_ADDR+0x078) 
#define IPU_CSI_CCIR_CODE_3  (IPU_BASE_ADDR+0x07C) 
#define IPU_CSI_FLASH_STROBE_1 (IPU_BASE_ADDR+0x080) 
#define IPU_CSI_FLASH_STROBE_2 (IPU_BASE_ADDR+0x084) 
#define IPU_IC_CONF (IPU_BASE_ADDR+0x088) 
#define IPU_IC_PRP_ENC_RSC (IPU_BASE_ADDR+0x08C) 
#define IPU_IC_PRP_VF_RSC (IPU_BASE_ADDR+0x090) 
#define IPU_IC_PP_RSC (IPU_BASE_ADDR+0x094) 
#define IPU_IC_CMBP_1 (IPU_BASE_ADDR+0x098) 
#define IPU_IC_CMBP_2 (IPU_BASE_ADDR+0x09C) 
#define IPU_PF_CONF (IPU_BASE_ADDR+0x0A0) 
#define IPU_IDMAC_CONF (IPU_BASE_ADDR+0x0A4) 
#define IPU_IDMAC_CHA_EN (IPU_BASE_ADDR+0x0A8) 
#define IPU_IDMAC_CHA_PRI (IPU_BASE_ADDR+0x0AC) 
#define IPU_IDMAC_CHA_BUSY (IPU_BASE_ADDR+0x0B0) 
#define IPU_SDC_COM_CONF (IPU_BASE_ADDR+0x0B4) 
#define IPU_SDC_GRAPH_WIND_CTRL (IPU_BASE_ADDR+0x0B8) 
#define IPU_SDC_FG_POS (IPU_BASE_ADDR+0x0BC) 
#define IPU_SDC_BG_POS (IPU_BASE_ADDR+0x0C0) 
#define IPU_SDC_CUR_POS (IPU_BASE_ADDR+0x0C4) 
#define IPU_SDC_CUR_BLINK_PWM_CTRL (IPU_BASE_ADDR+0x0C8) 
#define IPU_SDC_CUR_MAP (IPU_BASE_ADDR+0x0CC) 
#define IPU_SDC_HOR_CONF (IPU_BASE_ADDR+0x0D0) 
#define IPU_SDC_VER_CONF (IPU_BASE_ADDR+0x0D4) 
#define IPU_SDC_SHARP_CONF_1 (IPU_BASE_ADDR+0x0D8) 
#define IPU_SDC_SHARP_CONF_2 (IPU_BASE_ADDR+0x0DC) 
#define IPU_ADC_CONF (IPU_BASE_ADDR+0x0E0) 
#define IPU_ADC_SYSCHA1_SA (IPU_BASE_ADDR+0x0E4) 
#define IPU_ADC_SYSCHA2_SA (IPU_BASE_ADDR+0x0E8) 
#define IPU_ADC_PRPCHAN_SA (IPU_BASE_ADDR+0x0EC) 
#define IPU_ADC_PPCHAN_SA (IPU_BASE_ADDR+0x0F0) 
#define IPU_ADC_DISP0_CONF (IPU_BASE_ADDR+0x0F4) 
#define IPU_ADC_DISP0_RD_AP (IPU_BASE_ADDR+0x0F8) 
#define IPU_ADC_DISP0_RDM (IPU_BASE_ADDR+0x0FC) 
#define IPU_ADC_DISP0_SS (IPU_BASE_ADDR+0x100) 
#define IPU_ADC_DISP1_CONF (IPU_BASE_ADDR+0x104) 
#define IPU_ADC_DISP1_RD_AP (IPU_BASE_ADDR+0x108) 
#define IPU_ADC_DISP1_RDM (IPU_BASE_ADDR+0x10C) 
#define IPU_ADC_DISP12_SS (IPU_BASE_ADDR+0x110) 
#define IPU_ADC_DISP2_CONF (IPU_BASE_ADDR+0x114) 
#define IPU_ADC_DISP2_RD_AP (IPU_BASE_ADDR+0x118) 
#define IPU_ADC_DISP2_RDM (IPU_BASE_ADDR+0x11C) 
#define IPU_ADC_DISP_VSYNC (IPU_BASE_ADDR+0x120) 
#define IPU_DI_DISP_IF_CONF (IPU_BASE_ADDR+0x124) 
#define IPU_DI_DISP_SIG_POL (IPU_BASE_ADDR+0x128) 
#define IPU_DI_SER_DISP1_CONF (IPU_BASE_ADDR+0x12C) 
#define IPU_DI_SER_DISP2_CONF (IPU_BASE_ADDR+0x130) 
#define IPU_DI_HSP_CLK_PER (IPU_BASE_ADDR+0x134) 
#define IPU_DI_DISP0_TIME_CONF_1 (IPU_BASE_ADDR+0x138) 
#define IPU_DI_DISP0_TIME_CONF_2 (IPU_BASE_ADDR+0x13C) 
#define IPU_DI_DISP0_TIME_CONF_3 (IPU_BASE_ADDR+0x140) 
#define IPU_DI_DISP1_TIME_CONF_1 (IPU_BASE_ADDR+0x144) 
#define IPU_DI_DISP1_TIME_CONF_2 (IPU_BASE_ADDR+0x148) 
#define IPU_DI_DISP1_TIME_CONF_3 (IPU_BASE_ADDR+0x14C) 
#define IPU_DI_DISP2_TIME_CONF_1 (IPU_BASE_ADDR+0x150) 
#define IPU_DI_DISP2_TIME_CONF_2 (IPU_BASE_ADDR+0x154) 
#define IPU_DI_DISP2_TIME_CONF_3 (IPU_BASE_ADDR+0x158) 
#define IPU_DI_DISP3_TIME_CONF (IPU_BASE_ADDR+0x15C) 
#define IPU_DI_DISP0_DB0_MAP (IPU_BASE_ADDR+0x160) 
#define IPU_DI_DISP0_DB1_MAP (IPU_BASE_ADDR+0x164) 
#define IPU_DI_DISP0_DB2_MAP (IPU_BASE_ADDR+0x168) 
#define IPU_DI_DISP0_CB0_MAP (IPU_BASE_ADDR+0x16C) 
#define IPU_DI_DISP0_CB1_MAP (IPU_BASE_ADDR+0x170) 
#define IPU_DI_DISP0_CB2_MAP (IPU_BASE_ADDR+0x174) 
#define IPU_DI_DISP1_DB0_MAP (IPU_BASE_ADDR+0x178) 
#define IPU_DI_DISP1_DB1_MAP (IPU_BASE_ADDR+0x17C) 
#define IPU_DI_DISP1_DB2_MAP (IPU_BASE_ADDR+0x180) 
#define IPU_DI_DISP1_CB0_MAP (IPU_BASE_ADDR+0x184) 
#define IPU_DI_DISP1_CB1_MAP (IPU_BASE_ADDR+0x188) 
#define IPU_DI_DISP1_CB2_MAP (IPU_BASE_ADDR+0x18C) 
#define IPU_DI_DISP2_DB0_MAP (IPU_BASE_ADDR+0x190) 
#define IPU_DI_DISP2_DB1_MAP (IPU_BASE_ADDR+0x194) 
#define IPU_DI_DISP2_DB2_MAP (IPU_BASE_ADDR+0x198) 
#define IPU_DI_DISP2_CB0_MAP (IPU_BASE_ADDR+0x19C) 
#define IPU_DI_DISP2_CB1_MAP (IPU_BASE_ADDR+0x1A0) 
#define IPU_DI_DISP2_CB2_MAP (IPU_BASE_ADDR+0x1A4) 
#define IPU_DI_DISP3_B0_MAP (IPU_BASE_ADDR+0x1A8) 
#define IPU_DI_DISP3_B1_MAP (IPU_BASE_ADDR+0x1AC) 
#define IPU_DI_DISP3_B2_MAP (IPU_BASE_ADDR+0x1B0) 
#define IPU_DI_DISP_ACC_CC (IPU_BASE_ADDR+0x1B4) 
#define IPU_DI_DISP_LLA_CONF (IPU_BASE_ADDR+0x1B8) 
#define IPU_DI_DISP_LLA_DATA (IPU_BASE_ADDR+0x1BC) 
  
  
//#########################################  
//# MSHC generic  
//# relative addresses  
//#########################################  
  
#define MSHC_COMMAND_REG 0x00 
#define MSHC_DATA_REG 0x08 
#define MSHC_STATUS_REG 0x10 
#define MSHC_SYSTEM_REG 0x18 
  
  
  
  
  
  
  
  
  
//#########################################  
//# MSHC1                          #  
//# $5002_4000 to $5002_7FFF  
//#########################################  
  
#define MSHC1_BASE_ADDR 0x50024000 
#define MSHC1_COMMAND_REG (MSHC1_BASE_ADDR+0x00) 
#define MSHC1_DATA_REG (MSHC1_BASE_ADDR+0x08) 
#define MSHC1_STATUS_REG (MSHC1_BASE_ADDR+0x10) 
#define MSHC1_SYSTEM_REG (MSHC1_BASE_ADDR+0x18) 
  
  
//#########################################  
//# MSHC2                          #  
//# $5002_8000 to $5002_BFFF  
//#########################################  
  
#define MSHC2_BASE_ADDR 0x50028000 
#define MSHC2_COMMAND_REG (MSHC2_BASE_ADDR+0x00) 
#define MSHC2_DATA_REG (MSHC2_BASE_ADDR+0x08) 
#define MSHC2_STATUS_REG (MSHC2_BASE_ADDR+0x10) 
#define MSHC2_SYSTEM_REG (MSHC2_BASE_ADDR+0x18) 
  
  
//#########################################  
//# MBX  
//# $C000_0000 to $C0FF_FFFF           
//#########################################  
  
  
#define MBX1_BASE_ADDR 0xC0000000 
#define MBX1_3DDATA_BASE_ADDR 0xC0800000 
#define MBX1_2DDATA_BASE_ADDR 0xC0A00000 
#define MBX1_TATERMINATE_BASE_ADDR 0xC0C00000 
#define MBX1GLOBREGSWRESET (MBX1_BASE_ADDR+0x0080) 
#define MBX1_GLOBREG_CLK_RATIO (MBX1_BASE_ADDR+0x0090) 
#define MBX1_GLOBREG_IDLE_COUNT (MBX1_BASE_ADDR+0x0100) 
#define MBX1_GLOBREG_ACTIVITY_COUNT (MBX1_BASE_ADDR+0x0104) 
#define MBX1_GLOBREG_GPO (MBX1_BASE_ADDR+0x0108) 
#define MBX1_GLOBREG_INT_STATUS (MBX1_BASE_ADDR+0x012c) 
#define MBX1_GLOBREG_INT_ENAB (MBX1_BASE_ADDR+0x0130) 
#define MBX1_GLOBREG_INT_CLEAR (MBX1_BASE_ADDR+0x0134) 
#define MBX1_GLOBREG_MEMPAGE_SIZE (MBX1_BASE_ADDR+0x0140) 
#define MBX1_GLOBREG_RGNBASE (MBX1_BASE_ADDR+0x0608) 
#define MBX1_GLOBREG_OBJBASE (MBX1_BASE_ADDR+0x060c) 
#define MBX1_GLOBREG_ZLOADSTORE (MBX1_BASE_ADDR+0x0610) 
#define MBX1_GLOBREG_FPUPERPVAL (MBX1_BASE_ADDR+0x0614) 
#define MBX1_GLOBREG_FPUCULLVAL (MBX1_BASE_ADDR+0x0618) 
#define MBX1_GLOBREG_3DPIXSAMP (MBX1_BASE_ADDR+0x061c) 
#define MBX1_GLOBREG_CK1 (MBX1_BASE_ADDR+0x0624) 
#define MBX1_GLOBREG_CK2 (MBX1_BASE_ADDR+0x0628) 
#define MBX1_GLOBREG_CKUV (MBX1_BASE_ADDR+0x062c) 
#define MBX1_GLOBREG_CKMASK (MBX1_BASE_ADDR+0x0630) 
#define MBX1_GLOBREG_FOGCOLTABLE (MBX1_BASE_ADDR+0x0638) 
#define MBX1_GLOBREG_FOGCOLVERT (MBX1_BASE_ADDR+0x063c) 
#define MBX1_GLOBREG_VERTFOGSTATUS (MBX1_BASE_ADDR+0x0640) 
#define MBX1_GLOBREG_SCALERCTL (MBX1_BASE_ADDR+0x0644) 
#define MBX1_GLOBREG_BLENDCTL (MBX1_BASE_ADDR+0x0648) 
#define MBX1_GLOBREG_ARGBSUM (MBX1_BASE_ADDR+0x064c) 
#define MBX1_GLOBREG_FBCTL (MBX1_BASE_ADDR+0x0650) 
#define MBX1_GLOBREG_FBXCLIP (MBX1_BASE_ADDR+0x0654) 
#define MBX1_GLOBREG_FBYCLIP (MBX1_BASE_ADDR+0x0658) 
#define MBX1_GLOBREG_FBSTART (MBX1_BASE_ADDR+0x065c) 
#define MBX1_GLOBREG_FBLINESTRIDE (MBX1_BASE_ADDR+0x0660) 
#define MBX1_GLOBREG_LATENCYCOUNT (MBX1_BASE_ADDR+0x0664) 
#define MBX1_GLOBREG_ENDIANCTL (MBX1_BASE_ADDR+0x0668) 
#define MBX1_GLOBREG_ZBASEADDR (MBX1_BASE_ADDR+0x0674) 
#define MBX1_GLOBREG_STARTRENDER (MBX1_BASE_ADDR+0x0680) 
#define MBX1_GLOBREG_3DFLATSHADEDCS (MBX1_BASE_ADDR+0x06d0) 
#define MBX1_GLOBREG_3D_ZL_BACKGROUND_TAG (MBX1_BASE_ADDR+0x06d8) 
#define MBX1_GLOBREG_3D_ZL_BACKGROUND_DEPTH (MBX1_BASE_ADDR+0x06dc) 
#define MBX1_GLOBREG_1BPP_BACKGROUND_COLOUR (MBX1_BASE_ADDR+0x06e0) 
#define MBX1_GLOBREG_1BPP_FOREGROUND_COLOUR (MBX1_BASE_ADDR+0x06e4) 
#define MBX1_GLOBREG_USE_1BPP_REGS_CTL (MBX1_BASE_ADDR+0x06e8) 
#define MBX1_GLOBREG_3D_RENDER_ID (MBX1_BASE_ADDR+0x06ec) 
#define MBX1_GLOBREG_3D_TEX_DECIM (MBX1_BASE_ADDR+0x06f0) 
#define MBX1_TAGLOBREG_START (MBX1_BASE_ADDR+0x0800) 
#define MBX1_TAGLOBREG_RESTART (MBX1_BASE_ADDR+0x0804) 
#define MBX1_TAGLOBREG_ABORT (MBX1_BASE_ADDR+0x0808) 
#define MBX1_TAGLOBREG_RENDER_ID (MBX1_BASE_ADDR+0x0810) 
#define MBX1_TAGLOBREG_CONTEXT_LOAD (MBX1_BASE_ADDR+0x0814) 
#define MBX1_TAGLOBREG_CONTEXT_STORE (MBX1_BASE_ADDR+0x0818) 
#define MBX1_TAGLOBREG_CONTEXT_RESET (MBX1_BASE_ADDR+0x081c) 
#define MBX1_TAGLOBREG_CONTEXT_BASE (MBX1_BASE_ADDR+0x0820) 
#define MBX1_TAGLOBREG_EVM_PAGETBL_BASE (MBX1_BASE_ADDR+0x0824) 
#define MBX1_TAGLOBREG_EVM_LIST_START (MBX1_BASE_ADDR+0x0828) 
#define MBX1_TAGLOBREG_EVM_LIST_END (MBX1_BASE_ADDR+0x082c) 
#define MBX1_TAGLOBREG_EVM_RENDER_TIMEOUT (MBX1_BASE_ADDR+0x0830) 
#define MBX1_TAGLOBREG_EVM_TA_TIMEOUT (MBX1_BASE_ADDR+0x0834) 
#define MBX1_TAGLOBREG_EVM_INIT (MBX1_BASE_ADDR+0x0838) 
#define MBX1_TAGLOBREG_OBJDATABASE (MBX1_BASE_ADDR+0x083c) 
#define MBX1_TAGLOBREG_TAILPTRBASE (MBX1_BASE_ADDR+0x0840) 
#define MBX1_TAGLOBREG_REGION_BASE (MBX1_BASE_ADDR+0x0844) 
#define MBX1_TAGLOBREG_GLOBAL_LIST_CTRL (MBX1_BASE_ADDR+0x0848) 
#define MBX1_TAGLOBREG_XCLIP (MBX1_BASE_ADDR+0x084c) 
#define MBX1_TAGLOBREG_YCLIP (MBX1_BASE_ADDR+0x0850) 
#define MBX1_TAGLOBREG_RHWCLAMP (MBX1_BASE_ADDR+0x0854) 
#define MBX1_TAGLOBREG_RHWCOMP (MBX1_BASE_ADDR+0x0858) 
#define MBX1_TAGLOBREG_CONFIG (MBX1_BASE_ADDR+0x085c) 
#define MBX1_TAGLOBREG_EVM_CONTEXT_FLUSH_ADDR (MBX1_BASE_ADDR+0x0864) 
#define MBX1_ISP_SIG (MBX1_BASE_ADDR+0x0cc4) 
#define MBX1_TSP_SIG (MBX1_BASE_ADDR+0x0ccc) 
#define MBX1_DIAG_EN (MBX1_BASE_ADDR+0x0ce0) 
#define MBX1_GLOBREG_CORE_ID (MBX1_BASE_ADDR+0x0f00) 
#define MBX1_GLOBREG_REVISION (MBX1_BASE_ADDR+0x0f10) 
#define MBX1_GLOBREG_MMU_PAGE0_ADDR (MBX1_BASE_ADDR+0x1000) 
#define MBX1_GLOBREG_MMU_PAGE1_ADDR (MBX1_BASE_ADDR+0x1004) 
#define MBX1_GLOBREG_MMU_PAGE2_ADDR (MBX1_BASE_ADDR+0x1008) 
#define MBX1_GLOBREG_MMU_PAGE3_ADDR (MBX1_BASE_ADDR+0x100c) 
#define MBX1_GLOBREG_MMU_PAGE4_ADDR (MBX1_BASE_ADDR+0x1010) 
#define MBX1_GLOBREG_MMU_PAGE5_ADDR (MBX1_BASE_ADDR+0x1014) 
#define MBX1_GLOBREG_MMU_PAGE6_ADDR (MBX1_BASE_ADDR+0x1018) 
#define MBX1_GLOBREG_MMU_PAGE7_ADDR (MBX1_BASE_ADDR+0x101c) 
#define MBX1_GLOBREG_MMU_ENABLE (MBX1_BASE_ADDR+0x1020) 
#define MBX1_GLOBREG_MMU_IDX_INVAL (MBX1_BASE_ADDR+0x1024) 
#define MBX1_GLOBREG_MMU_PHYSADD_INVAL (MBX1_BASE_ADDR+0x1028) 
#define MBX1_BIST_STATUS (MBX1_BASE_ADDR+0x4000) 
#define MBX1_BIST_TARGET (MBX1_BASE_ADDR+0x4010) 
#define MBX1_BIST_RESULT_0 (MBX1_BASE_ADDR+0x4020) 
#define MBX1_BIST_RESULT_1 (MBX1_BASE_ADDR+0x4030) 
#define MBX1_BIST_FAILADDRESS (MBX1_BASE_ADDR+0x4060) 
#define MBX1_BIST_DATA_0 (MBX1_BASE_ADDR+0x4070) 
#define MBX1_BIST_DATA_1 (MBX1_BASE_ADDR+0x4080) 
#define MBX1_BIST_DATA_2 (MBX1_BASE_ADDR+0x4090) 
#define MBX1_BIST_DATA_3 (MBX1_BASE_ADDR+0x40a0) 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
