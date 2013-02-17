/*==================================================================================================

====================================================================================================

    Module Name:  usb_hwinterface_layer.h

    General Description: This is the header file for HW interface layer .

====================================================================================================
                               Freescale Confidential Proprietary
                       Copyright (c) 2006 Freescale Inc. All Rights Reserved


Revision History:
                            Modification     Tracking
Author                      Date (mm/dd/yy)   Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Prabhat Singh              29/01/2008       Engcm03148          USB lpb flow modification 
Siva Pothireddy             26-Dec-2007   engcm02041   Added additional registers for USBOH3
Mahima Verma                 19/Jul/2007    TLSbo94597   Change in USB address definition. 
Mahima Verma                 06/11/2007     TLSbo93857   Ported to Marley.
Suresh Kumar                 15/Oct/2006    TLSbo80774   Initial Version for Zappa
Bharat Bhushan               08/24/2006     TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               07/20/2006     TLSbo73521   Defines for ULPI Driver added.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).
====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#ifndef USB_HWINTERFACE_LAYER_H
#define USB_HWINTERFACE_LAYER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "su_basictypes.h"

 
#define BIT0 	0x00000001
#define BIT1 	0x00000002
#define BIT2 	0x00000004
#define BIT3 	0x00000008
#define BIT4	0x00000010
#define BIT5 	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9 	0x00000200
#define BIT10 	0x00000400
#define BIT11 	0x00000800
#define BIT12 	0x00001000
#define BIT13 	0x00002000
#define BIT14 	0x00004000
#define BIT15 	0x00008000
#define BIT16 	0x00010000
#define BIT17 	0x00020000
#define BIT18 	0x00040000
#define BIT19 	0x00080000
#define BIT20 	0x00100000
#define BIT21 	0x00200000
#define BIT22 	0x00400000
#define BIT23 	0x00800000
#define BIT24 	0x01000000
#define BIT25 	0x02000000
#define BIT26 	0x04000000
#define BIT27 	0x08000000
#define BIT28 	0x10000000
#define BIT29 	0x20000000
#define BIT30 	0x40000000
#define BIT31 	0x80000000


/* Device Queue Head and Device Transfer Descriptor Related Defination */
#define SIZE_OF_QHD	0x40
#define SIZE_OF_DTD0 	0x20
#define SIZE_OF_DTD1 	0x20
#define dTD_SIZE_EPIN 	(SIZE_OF_DTD0 + SIZE_OF_DTD1)
#define dTD_SIZE_EPOUT 	(SIZE_OF_DTD0 + SIZE_OF_DTD1)

#define BUFFER_USED_PER_EP ((SIZE_OF_QHD + dTD_SIZE_EPIN) +(SIZE_OF_QHD + dTD_SIZE_EPOUT))

#define ZLT_ENABLE	0
#define ZLT_DISABLE 	1

#define IOS_NOTSET	0
#define IOS_SET		1

#define IOC_NOTSET	0
#define IOC_SET		1

#define TERMINATE	1
#define NOT_TERMINATE	0

#define NO_STATUS 0
#define ACTIVE	BIT7

#define EPOUT_COMPLETE  BIT0
#define EPIN_COMPLETE	BIT16
	
#define EPOUT_PRIME	BIT0
#define EPIN_PRIME	BIT16

#define EPOUT_ENABLE	BIT7
#define EPIN_ENABLE     BIT23

#define STALL_RX	0x00000001
#define STALL_TX	0x00010000

/* Buffer size of the buffer used for bulk data transfer */ 

#define	CONTROL_BUFFER_SIZE	0x40
#define BULK_BUFFER_SIZE	0x200
#define NUM_OF_BULK_BUFFER	0x2	
#define TOTAL_DATA_BUFFER_SIZE	((BULK_BUFFER_SIZE * NUM_OF_BULK_BUFFER) + CONTROL_BUFFER_SIZE)

/*  Hash Define for PORTSC1 Register */
/* Defines for USB OTG Interface Speed  */
#define  USB_OTG_INF_SPEED_MASK	0x0C000000
#define  USB_OTG_INF_SPEED_FS	0x00000000
#define  USB_OTG_INF_SPEED_LS	0x04000000
#define  USB_OTG_INF_SPEED_HS	0x08000000
#define  USB_OTG_DEV_ATTACHED   0x00000001 /* State whether the device is attached or not */

#define  usb_base_address 0x73F80000

#define  USB_OTG_BASE_ADDR ((UINT32)usb_base_address + 0x000) 
#define  USB_H1_BASE_ADDR (usb_base_address + 0x200) 
#define  USB_H2_BASE_ADDR (usb_base_address + 0x400) 
#define  USB_CONTROL_REG ((UINT32)usb_base_address + 0x800) 
#define  USB_OTG_MIRROR_REG ((UINT32)usb_base_address + 0x804) 
#define  USB_PHY_CTRL_0_REG ((UINT32)usb_base_address + 0x808) 
#define  USB_PHY_CTRL_1_REG ((UINT32)usb_base_address + 0x80c) 
#define  USB_CTRL_1_REG ((UINT32)usb_base_address + 0x810) 

#define USB_PHY_CTRL_0_CHRGERDETON_MASK 0x00800000
#define USB_PHY_CTRL_0_CHRGERDETON_VAL    0x00800000
#define USB_PHY_CTRL_0_CHRGERDETEN_MASK  0x01000000 
#define USB_PHY_CTRL_0_CHRGERDETEN_VAL     0x01000000
#define USB_PHY_CTRL_0_CHRGERDET_MASK       0x00000004

#define USB_PHY_CTRL_0_CHRGERDETON_SET()    *(VP_U32)USB_PHY_CTRL_0_REG =((*(VP_U32)USB_PHY_CTRL_0_REG & ~ USB_PHY_CTRL_0_CHRGERDETON_MASK) \
											| USB_PHY_CTRL_0_CHRGERDETON_VAL)
#define USB_PHY_CTRL_0_CHRGERDETEN_SET()    *(VP_U32)USB_PHY_CTRL_0_REG =((*(VP_U32)USB_PHY_CTRL_0_REG & ~ USB_PHY_CTRL_0_CHRGERDETEN_MASK) \
											| USB_PHY_CTRL_0_CHRGERDETEN_VAL)
 

/*Hash Defines for PHY_CTRL_REG_1*/
#define  USB_PHY_CTRL_PLLDIVVALUE_MASK  0x00000003
#define  USB_PHY_CTRL_PLLDIVVALUE_19_2_MHZ  0x00000000
#define  USB_PHY_CTRL_PLLDIVVALUE_24_MHZ  0x00000001
#define  USB_PHY_CTRL_PLLDIVVALUE_26_MHZ  0x00000002
#define  USB_PHY_CTRL_PLLDIVVALUE_27_MHZ  0x00000003

  
/*
#**************#  
# USB HOST 1   #
#**************#  
*/
#define  USB_H1_ID (USB_H1_BASE_ADDR +0x000) 		/*   Identification Register */               
#define  USB_H1_HWGENERAL (USB_H1_BASE_ADDR +0x004) 	/*   General Hardware Parameters*/            
#define  USB_H1_HWHOST (USB_H1_BASE_ADDR +0x008) 	/*   Host Hardware Parameters       */        
#define  USB_H1_HWTXBUF (USB_H1_BASE_ADDR +0x010) 	/* TX Buffer Hardware Parameters  */        
#define  USB_H1_HWRXBUF (USB_H1_BASE_ADDR +0x014) 	/*   RX Buffer Hardware Parameters   */       
#define  USB_H1_CAPLENGTH (USB_H1_BASE_ADDR +0x100) 	/*   Capability Register Length     */        
#define  USB_H1_HCIVERSION (USB_H1_BASE_ADDR +0x102) 	/*   Host Interface Version Number  */        
#define  USB_H1_HCSPARAMS (USB_H1_BASE_ADDR +0x104) 	/*   Host Ctrl. Structural Parameters */      
#define  USB_H1_HCCPARAMS (USB_H1_BASE_ADDR +0x108) 	/*   Host Ctrl. Capability Parameters  */     
#define  USB_H1_USBCMD (USB_H1_BASE_ADDR +0x140) 	/*   USB Command            */ 
#define  USB_H1_USBSTS (USB_H1_BASE_ADDR +0x144) 	/*   USB Status             */ 
#define  USB_H1_USBINTR (USB_H1_BASE_ADDR +0x148) 	/*   USB Interrupt Enable   */
#define  USB_H1_FRINDEX (USB_H1_BASE_ADDR +0x14C) 	/*   USB Frame Index  */
#define  USB_H1_PERIODICLISTBASE (USB_H1_BASE_ADDR +0x154) /*   Frame List Base Address */ 
#define  USB_H1_ASYNCLISTADDR (USB_H1_BASE_ADDR +0x158) /*   Next Asynchronous List Address */        
#define  USB_H1_BURSTSIZE (USB_H1_BASE_ADDR +0x160) 	/*   Programmable Burst Size*/                
#define  USB_H1_TXFILLTUNING (USB_H1_BASE_ADDR +0x164) 	/*   Host Transmit Pre-Buffer Packet Tuning */
#define  USB_H1_CONFIGFLAG (USB_H1_BASE_ADDR +0x180) 	/*   Configured Flag Register*/               
#define  USB_H1_PORTSC1 (USB_H1_BASE_ADDR +0x184) 	/*   Port Status/Control */                   
#define  USB_H1_USBMODE (USB_H1_BASE_ADDR +0x1A8) 	/*   USB Device Mode */                       
 
/*	
#**********************  
# USB HOST 2  
#**********************  
*/
#define  USB_H2_ID (USB_H2_BASE_ADDR +0x000) 		/*   Identification Register  */
#define  USB_H2_HWGENERAL (USB_H2_BASE_ADDR +0x004) 	/*   General Hardware Parameters  */
#define  USB_H2_HWHOST (USB_H2_BASE_ADDR +0x008) 	/*   Host Hardware Parameters   */
#define  USB_H2_HWTXBUF (USB_H2_BASE_ADDR +0x010) 	/*   TX Buffer Hardware Parameters   */
#define  USB_H2_HWRXBUF (USB_H2_BASE_ADDR +0x014) 	/*   RX Buffer Hardware Parameters   */
#define  USB_H2_CAPLENGTH (USB_H2_BASE_ADDR +0x100) 	/*   Capability Register Length    */
#define  USB_H2_HCIVERSION (USB_H2_BASE_ADDR +0x102) 	/*   Host Interface Version Number  */ 
#define  USB_H2_HCSPARAMS (USB_H2_BASE_ADDR +0x104) 	/*   Host Ctrl. Structural Parameters */   
#define  USB_H2_HCCPARAMS (USB_H2_BASE_ADDR +0x108) 	/*   Host Ctrl. Capability Parameters  */      
#define  USB_H2_USBCMD (USB_H2_BASE_ADDR +0x140) 	/*   USB Command  */            
#define  USB_H2_USBSTS (USB_H2_BASE_ADDR +0x144) 	/*   USB Status   */               
#define  USB_H2_USBINTR (USB_H2_BASE_ADDR +0x148) 	/*   USB Interrupt Enable */                   
#define  USB_H2_FRINDEX (USB_H2_BASE_ADDR +0x14C) 	/*   USB Frame Index */
#define  USB_H2_PERIODICLISTBASE (USB_H2_BASE_ADDR +0x154) /*   Frame List Base Address  */               
#define  USB_H2_ASYNCLISTADDR (USB_H2_BASE_ADDR +0x158) /*   Next Asynchronous List Address */         
#define  USB_H2_BURSTSIZE (USB_H2_BASE_ADDR +0x160) 	/*   Programmable Burst Size   */              
#define  USB_H2_TXFILLTUNING (USB_H2_BASE_ADDR +0x164) 	/*   Host Transmit Pre-Buffer Packet Tuning  */
#define  USB_H2_CONFIGFLAG (USB_H2_BASE_ADDR +0x180) 	/*   Configured Flag Register */               
#define  USB_H2_PORTSC1 (USB_H2_BASE_ADDR +0x184) 	/*   Port Status/Control  */                   
#define  USB_H2_USBMODE (USB_H2_BASE_ADDR +0x1A8) 	/*   USB Device Mode */                        
 
/*	
#*************  
#   OTG  
#*************  
*/
#define  USB_OTG_ID (USB_OTG_BASE_ADDR + 0x000) 	/*   Identification Register */
#define  USB_OTG_HWGENERAL (USB_OTG_BASE_ADDR + 0x004) 	/*   General Hardware Parameters */
#define  USB_OTG_HWHOST (USB_OTG_BASE_ADDR + 0x008) 	/*   Host Hardware Parameters */
#define  USB_OTG_HWDEVICE (USB_OTG_BASE_ADDR + 0x00C) 	/*   Device Hardware Parameters */
#define  USB_OTG_HWTXBUF (USB_OTG_BASE_ADDR + 0x010) 	/*   TX Buffer Hardware Parameters */
#define  USB_OTG_HWRXBUF (USB_OTG_BASE_ADDR + 0x014) 	/*   RX Buffer Hardware Parameters */
#define  USB_OTG_CAPLENGTH (USB_OTG_BASE_ADDR + 0x100) 	/*   Capability Register Length */
#define  USB_OTG_HCIVERSION (USB_OTG_BASE_ADDR + 0x102) /*   Host Interface Version Number */
#define  USB_OTG_HCSPARAMS (USB_OTG_BASE_ADDR + 0x104) 	/*   Host Ctrl. Structural Parameters */
#define  USB_OTG_HCCPARAMS (USB_OTG_BASE_ADDR + 0x108) 	/*   Host Ctrl. Capability Parameters */
#define  USB_OTG_DCIVERSION (USB_OTG_BASE_ADDR + 0x120) /*   Dev. Interface Version Number */
#define  USB_OTG_DCCPARAMS (USB_OTG_BASE_ADDR + 0x124) 	/*   Device Ctrl. Capability Parameters */
  
#define  USB_OTG_USBCMD (USB_OTG_BASE_ADDR + 0x140) 	/*   USB Command */
#define  USB_OTG_USBSTS (USB_OTG_BASE_ADDR + 0x144) 	/*   USB Status */
#define  USB_OTG_USBINTR (USB_OTG_BASE_ADDR + 0x148) 	/*   USB Interrupt Enable */
#define  USB_OTG_FRINDEX (USB_OTG_BASE_ADDR+ 0x14C) 	/*   USB Frame Index */
#define  USB_OTG_PERIODICLISTBASE (USB_OTG_BASE_ADDR + 0x154) /*   Frame List Base Address */
#define  USB_OTG_DEVICEADDR  USB_OTG_PERIODICLISTBASE  	/*   USB Device Address */
#define  USB_OTG_ASYNCLISTADDR (USB_OTG_BASE_ADDR + 0x158) /*   Next Asynchronous List Address */
#define  USB_OTG_ENDPOINTLISTADDR USB_OTG_ASYNCLISTADDR	/*   Next Asynchronous List Address */
#define  USB_OTG_BURSTSIZE (USB_OTG_BASE_ADDR + 0x160) 	/*   Programmable Burst Size */
#define  USB_OTG_TXFILLTUNING (USB_OTG_BASE_ADDR + 0x164) /*   Host Transmit Pre-Buffer Packet Tuning */
#define  USB_OTG_VIEWPORT (USB_OTG_BASE_ADDR + 0x170)   /* ULPI Register */
#define  USB_OTG_CONFIGFLAG (USB_OTG_BASE_ADDR + 0x180) /*   Configured Flag Register */
#define  USB_OTG_PORTSC1 (USB_OTG_BASE_ADDR + 0x184) 	/*   Port Status/Control   */
#define  USB_OTG_OTGSC (USB_OTG_BASE_ADDR + 0x1A4) 	/*   On-The-Go (OTG) Status and Control  */  
#define  USB_OTG_USBMODE (USB_OTG_BASE_ADDR + 0x1A8) 	/*   USB Device Mode */
#define  USB_OTG_ENDPTSETUPSTAT (USB_OTG_BASE_ADDR + 0x1AC) /*   Endpoint Setup Status */
#define  USB_OTG_ENDPTPRIME (USB_OTG_BASE_ADDR + 0x1B0) /*   Endpoint Initialization */
#define  USB_OTG_ENDPTFLUSH (USB_OTG_BASE_ADDR + 0x1B4) /*   Endpoint De-Initialize */
#define  USB_OTG_ENDPTSTATUS (USB_OTG_BASE_ADDR + 0x1B8) /*   Endpoint Status */
#define  USB_OTG_ENDPTCOMPLETE (USB_OTG_BASE_ADDR + 0x1BC) /*   Endpoint Complete */
#define  USB_OTG_ENDPTCTRL0 (USB_OTG_BASE_ADDR + 0x1C0) /*   Endpoint Control 0 */
#define  USB_OTG_ENDPTCTRL1 (USB_OTG_BASE_ADDR + 0x1C4) /*   Endpoint Control 1 */
#define  USB_OTG_ENDPTCTRL2 (USB_OTG_BASE_ADDR + 0x1C8) /*   Endpoint Control 2 */
#define  USB_OTG_ENDPTCTRL3 (USB_OTG_BASE_ADDR + 0x1CC) /*   Endpoint Control 3 */
#define  USB_OTG_ENDPTCTRL4 (USB_OTG_BASE_ADDR + 0x1D0) /*   Endpoint Control 4 */
#define  USB_OTG_ENDPTCTRL5 (USB_OTG_BASE_ADDR + 0x1D4) /*   Endpoint Control 5 */
#define  USB_OTG_ENDPTCTRL6 (USB_OTG_BASE_ADDR + 0x1D8) /*   Endpoint Control 6 */
#define  USB_OTG_ENDPTCTRL7 (USB_OTG_BASE_ADDR + 0x1DC) /*   Endpoint Control 7 */

typedef struct dqh_setup_t{
	U32 dqh_word0;	
	U32 dqh_word1;	
	U32 dqh_word2;	
	U32 dqh_word3;	
	U32 dqh_word4;	
	U32 dqh_word5;	
	U32 dqh_word6;	
	U32 dqh_word7;	
	U32 dqh_word8;	
	U32 dqh_word9;	
	U32 dqh_word10;	
	U32 dqh_word11;	
} dqh_setup_t;

typedef struct dtd_setup_t {
	U32 dtd_word0;	
	U32 dtd_word1;	
	U32 dtd_word2;	
	U32 dtd_word3;	
	U32 dtd_word4;	
	U32 dtd_word5;	
	U32 dtd_word6;	
	U32 dtd_word7;	
} dtd_setup_t;


typedef struct dqh_t {
    U32 dqh_base;
    U32 next_link_ptr;
    U32 buffer_ptr0; 
    U32 buffer_ptr1; 
    U32 buffer_ptr2; 
    U32 buffer_ptr3; 
    U32 buffer_ptr4;
    U16 total_bytes;
    U16 mps;
    U16 current_offset;
    U8 zlt; 
    U8 ios;
    U8 terminate;
    U8 ioc;
    U8 status; 
}dqh_t;

typedef struct dtd_t {
	U32 dtd_base; 
	U32 next_link_ptr;
	U32 buffer_ptr0; 
   	U32 buffer_ptr1; 
	U32 buffer_ptr2;
   	U32 buffer_ptr3;
   	U32 buffer_ptr4;
   	U16 total_bytes;
	U16 current_offset;
   	U8 terminate;
   	U8 ioc;
   	U8 status;
}dtd_t;

typedef struct {
    U32 ep_dqh_base_addrs;	/* Base Address of Queue Header */
    U32 ep_dtd_base_addrs;	/* Base Address of Transfer Descriptor */
    U32 ep0_buffer_addrs ;   	/* Buffer Addres for EP0 IN  */
    U32 buffer1_address;	/* Buffer1 address for bulk transfer */
    U32 buffer1_status;		/* Status of Buffer1 */
    U32 buffer2_address;	/* Buffer2 address for bulk transfer */
    U32 buffer2_status;		/* Status of Buffer2 */
}buffer_map_t;

/* Status of the buffer used for bulk transfer */
enum {
    BUFFER_FREE,
    BUFFER_IN_USE
};


#ifdef __cplusplus
}
#endif

#endif /* USB_HWINTERFACE_LAYER_H */
