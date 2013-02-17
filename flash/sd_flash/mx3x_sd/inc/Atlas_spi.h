#ifndef _ATLAS_SPI_H
#define _ATLAS_SPI_H

#include "cspi.h"

// Atlas register MAP
#define INT_STATUS0 0
#define INT_MASK0 1
#define INT_SENSE0 2
#define INT_STATUS1 3
#define INT_MASK1 4
#define INT_SENSE1 5
#define PWR_UP_MODE 6
#define ATLAS_ID 7
#define SEMAPHORE 8
#define ARB_PER_AUDIO 9
#define ARB_SWITCH 10
#define ARB_REGULATOR0 11
#define ARB_REGULATOR1 12
#define PWR_CON0 13
#define PWR_CON1 14
#define PWR_CON2 15
#define REGEN_ASS 16
#define CON_SPR 17
#define MEMORY_A 18
#define MEMORY_B 19
#define RTC_TIM 20
#define RTC_ALARM 21
#define RTC_DAY 22
#define RTC_DAY_ALARM 23
#define SWITCHER_0 24
#define SWITCHER_1 25
#define SWITCHER_2 26
#define SWITCHER_3 27
#define SWITCHER_4 28
#define SWITCHER_5 29
#define REGULATOR_SET_0 30
#define REGULATOR_SET_1 31
#define REGULATOR_MOD_0 32
#define REGULATOR_MOD_1 33
#define PWR_MISC 34
#define PWR_SPR 35
#define AUDIO_RX0 36
#define AUDIO_RX1 37
#define AUDIO_TX 38
#define SSI_NET 39
#define AUDIO_CODEC 40
#define AUDIO_STE_DAC 41
#define AUDIO_SPR 42
#define ADC_0 43
#define ADC_1 44
#define ADC_2 45
#define ADC_3 46
#define ADC_4 47
#define CHAR_0 48
#define USB_0 49
#define USB_1 50
#define LED_CON0 51
#define LED_CON1 52
#define LED_CON2 53
#define LED_CON3 54
#define LED_CON4 55
#define LED_CON5 56
#define SPR1 57
#define TRIM0 58
#define TRIM1 59
#define TEST0 60
#define TEST1 61
#define TEST2 62
#define TEST3 63


//Detail in register


// REG30 regulator setting 0
#define VIOLO_1V2 0x0<<2
#define VIOLO_1V3 0x1<<2
#define VIOLO_1V5 0x2<<2
#define VIOLO_1V8 0x3<<2
#define VDIG_1V2 0x0<<4
#define VDIG_1V3 0x1<<4
#define VDIG_1V5 0x2<<4
#define VDIG_1V8 0x3<<4
#define VGEN_1V2 0x0<<6
#define VGEN_1V3 0x1<<6
#define VGEN_1V5 0x2<<6
#define VGEN_1V8 0x3<<6
#define VGEN_1V1 0x4<<6
#define VGEN_2V0 0x5<<6
#define VGEN_2V775 0x6<<6
#define VGEN_2V4 0x7<<6
#define VRFDIG_1V2 0x0<<9
#define VRFDIG_1V5 0x1<<9
#define VRFDIG_1V8 0x2<<9
#define VRFDIG_1V875 0x3<<9
#define VRFREF_2V475 0x0<<11
#define VRFREF_2V6 0x1<<11
#define VRFREF_2V7 0x2<<11
#define VRFREF_2V775 0x3<<11
#define VRFCP_2V7 0x0<<13
#define VRFCP_2V775 0x1<<13
#define VSIM_1V8 0x0<<14
#define VSIM_2V9 0x1<<14
#define VESIM_1V8 0x0<<15
#define VESIM_2V9 0x1<<15
#define VCAM_1V5 0x0<<16
#define VCAM_1V8 0x1<<16
#define VCAM_2V5 0x2<<16
#define VCAM_2V55 0x3<<16
#define VCAM_2V6 0x4<<16
#define VCAM_2V75 0x5<<16
#define VCAM_2V8 0x6<<16
#define VCAM_3V0 0x7<<16


// REG31, regulator setting 1
#define VIB_1V3 0x0<<0
#define VIB_1V8 0x1<<0
#define VIB_2V0 0x2<<0
#define VIB_3V0 0x3<<0
#define VRF1_1V5 0x0<<2
#define VRF1_1V875 0x1<<2
#define VRF1_2V7 0x2<<2
#define VRF1_2V775 0x3<<2
#define VRF2_1V5 0x0<<4
#define VRF2_1V875 0x01<<4
#define VRF2_2V7 0x2<<4
#define VRF2_2V775 0x3<<4
#define VMMC1_1V6 0x0<<6
#define VMMC1_1V8 0x1<<6
#define VMMC1_2V0 0x2<<6
#define VMMC1_2V6 0x3<<6
#define VMMC1_2V7 0x4<<6
#define VMMC1_2V8 0x5<<6
#define VMMC1_2V9 0x6<<6
#define VMMC1_3V0 0x7<<6
#define VMMC2_1V6 0x0<<9
#define VMMC2_1V8 0x1<<9
#define VMMC2_2V0 0x2<<9
#define VMMC2_2V6 0x3<<9
#define VMMC2_2V7 0x4<<9
#define VMMC2_2V8 0x5<<9
#define VMMC2_2V9 0x6<<9
#define VMMC2_3V0 0x7<<9

//REG 32, regulator mode 0
#define VAUDIO_EN 0x1<<0
#define VAUDIO_DIS 0x0<<0
#define VAUDIOSTBY_EN 0x1<<1
#define VAUDIOSTBY_DIS 0x0<<1
#define VAUDIOMODE_LOW 0x1<<2
#define VAUDIOMODE_ON 0x0<<2
#define VIOHI_EN 0x1<<3
#define VIOHI_DIS 0x0<<3
#define VIOHISTBY_EN 0x1<<4
#define VIOHISTBY_DIS 0x0<<4
#define VIOHIMODE_LOW 0x1<<5
#define VIOHIMODE_ON 0x0<<5
#define VIOLO_EN 0x1<<6
#define VIOLO_DIS 0x0<<6
#define VIOLOSTBY_EN 0x1<<7
#define VIOLOSTBY_DIS 0x0<<7
#define VIOLOMODE_LOW 0x1<<8
#define VIOLOMODE_ON 0x0<<8
#define VDIG_EN 0x1<<9
#define VDIG_DIS 0x0<<9
#define VDIGSTBY_EN 0x1<<10
#define VDIGSTBY_DIS 0x0<<10
#define VDIGMODE_LOW 0x1<<11
#define VDIGMODE_ON 0x0<<11
#define VGEN_EN 0x1<<12
#define VGEN_DIS 0x0<<12
#define VGENSTBY_EN 0x1<<13
#define VGENSTBY_DIS 0x0<<13
#define VGENMODE_LOW 0x1<<14
#define VGENMODE_ON 0x0<<14
#define VRFDIG_EN 0x1<<15
#define VRFDIG_DIS 0x0<<15
#define VRFDIGSTBY_EN 0x1<<16
#define VRFDIGSTBY_DIS 0x0<<16
#define VRFDIGMODE_LOW 0x1<<17
#define VRFDIGMODE_ON 0x0<<17
#define VRFREF_EN 0x1<<18
#define VRFREF_DIS 0x0<<18
#define VRFREFSTBY_EN 0x1<<19
#define VRFREFSTBY_DIS 0x0<<19
#define VRFREFMODE_LOW 0x1<<20
#define VRFREFMODE_ON 0x0<<20
#define VRFCP_EN 0x1<<21
#define VRFCP_DIS 0x0<<21
#define VRFCPSTBY_EN 0x1<<22
#define VRFCPSTBY_DIS 0x0<<22
#define VRFCPMODE_LOW 0x1<<23
#define VRFCPMODE_ON 0x0<<23

// REG33, regulator mode 1
#define VSIM_EN 0x1<<0
#define VSIM_DIS 0x0<<0
#define VSIMSTBY_EN 0x1<<1
#define VSIMSTBY_DIS 0x0<<1
#define VSIMMODE_LOW 0x1<<2
#define VSIMMODE_ON 0x0<<2
#define VESIM_EN 0x1<<3
#define VESIM_DIS 0x0<<3
#define VESIMSTBY_EN 0x1<<4
#define VESIMSTBY_DIS 0x0<<4
#define VESIMMODE_LOW 0x1<<5
#define VESIMMODE_ON 0x0<<5
#define VCAM_EN 0x1<<6
#define VCAM_DIS 0x0<<6
#define VCAMSTBY_EN 0x1<<7
#define VCAMSTBY_DIS 0x0<<7
#define VCAMMODE_LOW 0x1<<8
#define VCAMMODE_ON 0x0<<8
#define VRFBG_EN 0x1<<9
#define VRFBG_DIS 0x0<<9
#define VRFBGSTBY_EN 0x1<<10
#define VRFBGSTBY_DIS 0x0<<10
#define VVIB_EN 0x1<<11
#define VVIB_DIS 0x0<<11
#define VRF1_EN 0x1<<12
#define VRF1_DIS 0x0<<12
#define VRF1STBY_EN 0x1<<13
#define VRF1STBY_DIS 0x0<<13
#define VRF1MODE_LOW 0x1<<14
#define VRF1MODE_ON 0x0<<14
#define VRF2_EN 0x1<<15
#define VRF2_DIS 0x0<<15
#define VRF2STBY_EN 0x1<<16
#define VRF2STBY_DIS 0x0<<16
#define VRF2MODE_LOW 0x1<<17
#define VRF2MODE_ON 0x0<<17
#define VMMC1_EN 0x1<<18
#define VMMC1_DIS 0x0<<18
#define VMMC1STBY_EN 0x1<<19
#define VMMC1STBY_DIS 0x0<<19
#define VMMC1MODE_LOW 0x1<<20
#define VMMC1MODE_ON 0x0<<20
#define VMMC2_EN 0x1<<21
#define VMMC2_DIS 0x0<<21
#define VMMC2STBY_EN 0x1<<22
#define VMMC2STBY_DIS 0x0<<22
#define VMMC2MODE_LOW 0x1<<23
#define VMMC2MODE_ON 0x0<<23

// REG34, power misc 
#define GPO1_EN 0x1<<6
#define GPO1_DIS 0x0<<6
#define GPO2_EN 0x1<<8
#define GPO2_DIS 0x0<<8
#define GPO3_EN 0x1<<10
#define GPO3_DIS 0x0<<10
#define GPO4_EN 0x1<<12
#define GPO4_DIS 0x0<<12



void Atlas_spi_init(void);
U32 Atlas_read_reg(U32 reg_num);
void Atlas_write_reg(U32 reg_num, U32 data);





#endif
