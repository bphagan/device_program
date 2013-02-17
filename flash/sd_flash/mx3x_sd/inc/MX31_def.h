#include "Common.h"
#include "tortola_memory_map_defines.h"





//#*************  
//#   OTG  
//#*************  

#define  USB_OTG_DEVICEADDR (USB_OTG_BASE_ADDR + 0x154) //   USB Device Address
//#define  USB_OTG_ASYNCLISTADDR (USB_OTG_BASE_ADDR + 0x158) //   Next Asynchronous List Address
#define  USB_OTG_ENDPOINTLISTADDR (USB_OTG_BASE_ADDR + 0x158) //   Address at Endpoint list in memory
#define  USB_OTG_ENDPTNAK	(USB_OTG_BASE_ADDR + 0x178)	  // 
#define  USB_OTG_ENDPTSETUPSTAT (USB_OTG_BASE_ADDR + 0x1AC) //   Endpoint Setup Status




//ES  //#########################################
//ES  //# Clock  Reset (CCM)                   #
//ES  //# System control                        #
//ES  //# $53F8_0000 to $53F8_3FFF              #
//ES  //#########################################
//ES  #define CCM_DCVR 	(CCM_BASE_ADDR+0x2C)
//ES  #define CCM_DCR  	(CCM_BASE_ADDR+0x30)
//ES  #define CCM_SUID0	(CCM_BASE_ADDR+0x34)
//ES  #define CCM_SUID1	(CCM_BASE_ADDR+0x38)
//ES  #define CCM_FSR  	(CCM_BASE_ADDR+0x4C)
//ES  #define CCM_HWREV	(CCM_BASE_ADDR+0x50)
                 	


U32 Tuvalu_init(U32 BASE);
