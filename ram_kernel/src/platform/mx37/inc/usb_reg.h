#ifndef USB_REG_INCLUDE /* To prevent inadvertently including a header twice */
#define USB_REG_INCLUDE  

#ifdef __cplusplus  /* allow #include in a C++ file (only put this in .h files) */
extern "C" {
#endif

/* (c) Copyright Motorola 2004, All rights reserved.        
   Motorola Confidential Proprietary
   Contains confidential proprietary information of Motorola, Inc.
   Reverse engineering is prohibited.
   The copyright notice does not imply publication.
  
   DESCRIPTION: 
      This file contains the extern references and typedefs associated with 
      all global variables used in the USB driver. 
 
 ************** REVISION HISTORY **********************************************
  
   Date         Author      Reference
   ==========   ========    ==========================
   15/04/2004   byn016      LIBdd96665 - Argon/SCM-A11 ROM USB support 
   11/06/2004   bss043      LIBee19881 - SCM-A11 ROM USB memory map adjusments
   01/09/2004   bss043      LIBff11691 - USB RTL simulator workarround - W1C registers
                                         are being cleared only if the value in the
                                         register is 1 (in case the value is 0 wrting 
                                         '1' will set the bit in the register) 
   15/11/2004   bss043      DSPhl24627 - Frame number register can no longer use
                                         W1C Macro since it cannot be read.
   29/11/2004   bss043      DSPhl25028 - Toggle register is a write '1' to toggle
   21/12/2004   bss043      DSPhl25323 - Toggle fix (DSPhl25028) introduced enumeration
                                         instabilities that were not root caused yet -
					 ROM pass 2 will not include this fix
   28/12/2004   bss043      DSPhl25185 - a Timing problem with Toggle register set, 
                                         read a '0' condition was added to make sure 
                                         toggle register EP0 IN bit will be set before 
                                         transfer.
   23/Aug/2006   Lucky Sharma  TLSbo76313 -Get rid of chipset conditional compilation 

*/
/************** HEADER FILE INCLUDES ******************************************/
#include "usb_global.h"
/************** CONSTANTS *****************************************************/

/* GLOBAL USB FUNC */
#define USB_GLOBAL_EP0_OUT_MASK         0x00000001
#define USB_GLOBAL_EP0_IN_MASK          0x00000002
#define USB_GLOBAL_EP1_OUT_MASK         0x00000004
#define USB_GLOBAL_EP1_IN_MASK          0x00000008
#define USB_GLOBAL_EP2_OUT_MASK         0x00000010
#define USB_GLOBAL_EP2_IN_MASK          0x00000020


/* Those Macros are for internal use only in this file */
#define USB_GLOBAL_read_bit(reg_addr, bit_mask)              (reg_addr & bit_mask)     /* read the value of a spesific bit in the reg. */
#define USB_GLOBAL_set_bit(reg_addr, bit_mask)               (reg_addr |= bit_mask)    /* write ONE to a spesific bit in the reg. */
#define USB_GLOBAL_clr_bit(reg_addr, bit_mask)               (reg_addr &= ~(bit_mask)) /* write ZERO to a spesific bit in the reg.*/
#define USB_GLOBAL_wrt1toclr_bit(reg_addr, bit_mask)         (((reg_addr & bit_mask) == bit_mask) ? reg_addr = bit_mask : 0)      /* write ONE (only if bit is set (HW workarround)) to a spesific bit in a W1C/RC reg.*/
#define USB_GLOBAL_write_bit(reg_addr, bit_mask)             (reg_addr = bit_mask)    /* write ONE */
#define USB_GLOBAL_toggle_bit(reg_addr, bit_mask)         (((reg_addr & bit_mask) == 0) ? reg_addr = bit_mask : 0)      /* write ONE (only if bit is zero (HW workarround)).*/

/*----------------------------------------*/
/* USB_CORE_REG_BLOCK                     */
/*----------------------------------------*/

/* GLOBAL USB CORE */
#define USB_CORE_CLR_MASK_1          0x00000001
#define USB_CORE_CLR_MASK_2          0x00000003
#define USB_CORE_CLR_MASK_3          0x00000007
#define USB_CORE_CLR_MASK_4          0x0000000F
#define USB_CORE_CLR_MASK_8          0x000000FF
#define USB_CORE_CLR_MASK_16         0x0000FFFF


/* HW_MODE_REG (0x000) */

/* Register Masks */
#define USB_CORE_FUNCREV_MASK        0xFF000000
#define USB_CORE_HSTREV_MASK         0x00FF0000 
#define USB_CORE_TSTMDE_MASK         0x00008000 
#define USB_CORE_ANASDBEN_MASK       0x00004000
#define USB_CORE_OTGXCVR_MASK        0x000000C0
#define USB_CORE_HOSTXCVR_MASK   	 0x00000030
#define USB_CORE_BEMDE_MASK   		 0x00000004
#define USB_CORE_CRECFG_MASK    	 0x00000003

/* Set Core configuration to Function Operation */
#define USB_CORE_CRECFG  2


/* Register Macros */

/* read transceiver properties */
#define USB_CORE_otgxcvr_get()      ((usb_core_regs.hw_mode_reg >> 6) & USB_CORE_CLR_MASK_2 )
/* set transceiver properties */
#define USB_CORE_otgxcvr_set(val)   (usb_core_regs.hw_mode_reg = \
                                    (usb_core_regs.hw_mode_reg & ~(USB_CORE_OTGXCVR_MASK)) | \
								            ((((UINT32)(val)) << 6) & USB_CORE_OTGXCVR_MASK))
/* Read Core configuration */
#define USB_CORE_crecfg_get()       (usb_core_regs.hw_mode_reg & USB_CORE_CLR_MASK_2 )
/* Set Core configuration */
#define USB_CORE_crecfg_set(val)    (usb_core_regs.hw_mode_reg = \
                                    (usb_core_regs.hw_mode_reg & ~(USB_CORE_CRECFG_MASK)) | (((UINT32)(val))& USB_CORE_CRECFG_MASK))								 

/* CORE_INTERRUPT_STATUS_REG (0x004) */

/* Register Masks */
#define USB_CORE_FCINTDSP_MASK  	0x00000040
#define USB_CORE_ASHNPINT_MASK  	0x00000020
#define USB_CORE_ASFCINT_MASK  	    0x00000010
#define USB_CORE_ASHCINT_MASK  	    0x00000008
#define USB_CORE_HNPINT_MASK  	    0x00000004
#define USB_CORE_FCINT_MASK  		0x00000002
#define USB_CORE_HCINT_MASK  		0x00000001


/* CORE_INTERRUPT_ENABLE_REG (0x008) */

/* Register Masks */
#define USB_CORE_FCINTDSPEN_MASK  	0x00000040
#define USB_CORE_ASHNPINTEN_MASK  	0x00000020
#define USB_CORE_ASFCINTEN_MASK  	0x00000010
#define USB_CORE_ASHCINTEN_MASK  	0x00000008
#define USB_CORE_HNPINTEN_MASK  	0x00000004
#define USB_CORE_FCINTEN_MASK  		0x00000002
#define USB_CORE_HCINTEN_MASK  		0x00000001


/* CLOCK_CONTROL_REG (0x00C) */

/* Register's Masks */
#define USB_CORE_FUNCCLK_MASK  	 0x00000004
#define USB_CORE_HSTCLK_MASK  	 0x00000002
#define USB_CORE_MAINCLK_MASK  	 0x00000001

/* Register's Macros */
/* Handle function clock */
#define USB_CORE_funcclk_get() 	  (USB_GLOBAL_read_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_FUNCCLK_MASK))
#define USB_CORE_funcclk_set() 	  (USB_GLOBAL_set_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_FUNCCLK_MASK))
#define USB_CORE_funcclk_clr() 	  (USB_GLOBAL_clr_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_FUNCCLK_MASK))
/* Handle Host clock */
#define USB_CORE_hstclk_get() 	  (USB_GLOBAL_read_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_HSTCLK_MASK))
#define USB_CORE_hstclk_set() 	  (USB_GLOBAL_set_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_HSTCLK_MASK))
#define USB_CORE_hstclk_clr() 	  (USB_GLOBAL_clr_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_HSTCLK_MASK))
/* Handle Main clock */
#define USB_CORE_mainclk_get() 	  (USB_GLOBAL_read_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_MAINCLK_MASK))
#define USB_CORE_mainclk_set() 	  (USB_GLOBAL_set_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_MAINCLK_MASK))
#define USB_CORE_mainclk_clr() 	  (USB_GLOBAL_clr_bit(usb_core_regs.clock_ctrl_reg,USB_CORE_MAINCLK_MASK))

/* RESET_CONTROL_REG (0x010) */
/* Register's Masks */
#define USB_CORE_RSTCTRL_MASK	 0x00000020
#define USB_CORE_RSTFC_MASK	     0x00000010
#define USB_CORE_RSTFSIE_MASK	 0x00000008
#define USB_CORE_RSTRH_MASK 	 0x00000004
#define USB_CORE_RSTHSIE_MASK    0x00000002
#define USB_CORE_RSTHC_MASK  	 0x00000001

/* Register's Macros */
/* This reg is W only (writing 0 will have no effect). All the bits are self-clearing */
/* set reset control logic */
#define USB_CORE_rstctrl_set() 	  (usb_core_regs.reset_ctrl_reg = USB_CORE_RSTCTRL_MASK)
/* set reset function controler */
#define USB_CORE_rstfc_set() 	     (usb_core_regs.reset_ctrl_reg = USB_CORE_RSTFC_MASK)
/* set reset serial interface engine */
#define USB_CORE_rstfsie_set() 	  (usb_core_regs.reset_ctrl_reg = USB_CORE_RSTFSIE_MASK)

/* FRAME_INTERVAL_REG (0x014) */

/* FRAME_REMAINING_REG (0x018) */

/* HNP_CONTROL_STATUS_REG (0x01C) */

/* HNP_TIMER1_REG (0x020) */

/* HNP_TIMER2_REG (0x024) */

/* HNP_TIMER3_PULSE_CONTROL_REG (0x028) */

/* HNP_INTERRUPT_STATUS_REG (0x02C) */

/* HNP_INTERRUPT_ENABLE_STATUS_REG (0x030) */

/* CPU_EP_SEL_REG (0x034) */

/* DSP_EP_SEL_REG (0x038) */

/* CORE_INTERRUPT_STATUS_ENABLE_CLR_REG (0x03C) */

/* Register's Masks */
#define USB_CORE_FCINTDSPENCLR_MASK  	0x00000040
#define USB_CORE_ASHNPINTENCLR_MASK  	0x00000020
#define USB_CORE_ASFCINTENCLR_MASK  	0x00000010
#define USB_CORE_ASHCINTENCLR_MASK  	0x00000008
#define USB_CORE_HNPINTENCLR_MASK  		0x00000004
#define USB_CORE_FCINTENCLR_MASK  		0x00000002
#define USB_CORE_HCINTENCLR_MASK  		0x00000001



/*--------------------*/
/* USB_FUNC_REG_BLOCK */
/*--------------------*/

/* FUNC_CMD_STATUS_REG (0x040) */

/* Register's Mask*/
#define USB_FUNC_SOFTRESET_MASK  0x00000080
#define USB_FUNC_BADISOAP_MASK   0x00000008 
#define USB_FUNC_SUSPDET_MASK    0x00000004 
#define USB_FUNC_RSMINPROG_MASK  0x00000002
#define USB_FUNC_RESETDET_MASK   0x00000001


/* Register's Macros */
/* SW initaited HW reset*/
/* This bit is W only. Writng 0 to any of theis reg bits leave the HW unchanged */
#define USB_FUNC_softreset_set() (usb_func_regs.func_cmd_status_reg = USB_FUNC_SOFTRESET_MASK)
/* Read USB BUS reset status */
#define USB_FUNC_resetdet_get()  (USB_GLOBAL_read_bit(usb_func_regs.func_cmd_status_reg,USB_FUNC_RESETDET_MASK))
                                  
/* DEV_ADDR_REG (0x044) */ 

/* Register's Mask*/
#define USB_FUNC_DEVADDR_MASK      0x0000007F

/* Register's Macros */
/* Read USB function address */
#define USB_FUNC_devaddr_get()     (usb_func_regs.dev_addr_reg & USB_FUNC_DEVADDR_MASK)
/* Set USB function address */
#define USB_FUNC_devaddr_set(addr) (usb_func_regs.dev_addr_reg = ((addr) & USB_FUNC_DEVADDR_MASK))
                               
/* SYS_INT_STATUS_REG (0x048) */

/* Register's Mask */
#define USB_FUNC_DONEREGINTDSP_MASK  0x00000020
#define USB_FUNC_SOFDETINT_MASK      0x00000010
#define USB_FUNC_DONEREGINT_MASK     0x00000008
#define USB_FUNC_SUSPDETINT_MASK     0x00000004
#define USB_FUNC_RSMFININT_MASK      0x00000002
#define USB_FUNC_RESETINT_MASK       0x00000001

/* Register's Macros */
/* Read reset interrupt */
#define USB_FUNC_resetint_get()      (USB_GLOBAL_read_bit(usb_func_regs.sys_int_status_reg,USB_FUNC_RESETINT_MASK))
/* Clear reset interrupt */
#define USB_FUNC_resetint_clr()      (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.sys_int_status_reg,USB_FUNC_RESETINT_MASK))

/* SYS_INT_EN_REG (0x04C) */

/* Register's Mask */
#define USB_FUNC_DONEREGIENDSP_MASK  0x00000020
#define USB_FUNC_SOFDETIEN_MASK      0x00000010
#define USB_FUNC_DONEREGIEN_MASK     0x00000008
#define USB_FUNC_SUSPDETIEN_MASK     0x00000004
#define USB_FUNC_RSMFINIEN_MASK      0x00000002
#define USB_FUNC_RESETIEN_MASK       0x00000001

/* Register's Macros */
/* Read enable reset interrupt */
#define USB_FUNC_resetien_get()      (USB_GLOBAL_read_bit(usb_func_regs.sys_int_en_reg,USB_FUNC_RESETIEN_MASK))
/* disable reset interrupt */
#define USB_FUNC_resetien_set()      (USB_GLOBAL_set_bit(usb_func_regs.sys_int_en_reg,USB_FUNC_RESETIEN_MASK))
/* Clear this bit is done by setting the corresponding bit in SystemInterruptEnableClr Register (0x14C) */

/* XBUFF_INT_STATUS_REG (0x050) */

/* Register's Macros */
#define USB_FUNC_xbuff_int_status_get(ep_mask) \
                           (USB_GLOBAL_read_bit(usb_func_regs.xbuff_int_status_reg,ep_mask))
#define USB_FUNC_xbuff_int_status_clr(ep_mask) \
                           (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.xbuff_int_status_reg,ep_mask))

/* YBUFF_INT_STATUS_REG (0x054) */

/* Register's Macros */
#define USB_FUNC_ybuff_int_status_get(ep_mask) \
                           (USB_GLOBAL_read_bit(usb_func_regs.ybuff_int_status_reg,ep_mask))
#define USB_FUNC_ybuff_int_status_clr(ep_mask) \
                           (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.ybuff_int_status_reg,ep_mask))

/* XY_INT_EN_REG (0x058) */

/* Register's Macros */
#define USB_FUNC_xy_int_en_get(ep_mask) \
                           (USB_GLOBAL_read_bit(usb_func_regs.xy_int_en_reg,ep_mask))
#define USB_FUNC_xy_int_enable(ep_mask) \
                           (USB_GLOBAL_set_bit(usb_func_regs.xy_int_en_reg,ep_mask))
/* Clear this bit(disable) is done by setting the corresponding bit in XYInterruptEnableClr Register (0x158) */
                           
/* XFILLED_STATUS_REG (0x05C) */

/* Register's Macros */
#define USB_FUNC_xfilled_status_out_get(ep_mask) \
                                   (USB_GLOBAL_read_bit(usb_func_regs.xfilled_status_reg,ep_mask)) 
/* This bit is S only. Write 0 to this reg will have no effects. */
#define USB_FUNC_xfilled_status_in_set(ep_mask) \
                                   (usb_func_regs.xfilled_status_reg = ep_mask)
#define USB_FUNC_xfilled_status_out_clr(ep_mask) \
                                   (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.xfilled_status_reg,ep_mask))

/* YFILLED_STATUS_REG (0x060) */

/* Register's Macros */
#define USB_FUNC_yfilled_status_out_get(ep_mask) \
                                   (USB_GLOBAL_read_bit(usb_func_regs.yfilled_status_reg,ep_mask)) 
/* This bit is S only. Write 0 to this reg will have no effects. */
#define USB_FUNC_yfilled_status_in_set(ep_mask) \
                                   (usb_func_regs.yfilled_status_reg = ep_mask) 
#define USB_FUNC_yfilled_status_out_clr(ep_mask) \
                                   (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.yfilled_status_reg,ep_mask)) 

/* EP_EN_REG (0x064) */

/* Register's Macros */
#define USB_FUNC_ep_en_get(ep_mask) \
                           (USB_GLOBAL_read_bit(usb_func_regs.ep_en_reg,ep_mask))
#define USB_FUNC_ep_enable(ep_mask) \
                           (USB_GLOBAL_set_bit(usb_func_regs.ep_en_reg,ep_mask))
/* Clear this bit(disable) is done by setting the corresponding bit in EndpointEnableClr Register (0x164) */

/* EP_READY_REG (0x068) */

/* Register's Macros */
#define USB_FUNC_ep_ready_get(ep_mask) \
                          (USB_GLOBAL_read_bit(usb_func_regs.ep_ready_reg,ep_mask))
#define USB_FUNC_set_ep_ready(ep_mask) \
                          (USB_GLOBAL_set_bit(usb_func_regs.ep_ready_reg,ep_mask))
/* Clear this bit(not ready) is done by setting the corresponding bit in FrameNumber(EprdyClear) Register (0x07C) */

/* IMMEDIATE_INT_REG (0x06C) */

/* EP_DONE_STATUS_REG (0x070) */

/* Register's Macros */
#define USB_FUNC_ep_done_status_get(ep_mask) \
                                   (USB_GLOBAL_read_bit(usb_func_regs.ep_done_status_reg,ep_mask)) 
#define USB_FUNC_ep_done_status_clr(ep_mask) \
                                   (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.ep_done_status_reg,ep_mask))

/* EP_DONE_EN_REG (0x074) */

/* Register's Macros */
#define USB_FUNC_ep_done_en_get(ep_mask) \
                               (USB_GLOBAL_read_bit(usb_func_regs.ep_done_en_reg,ep_mask))
#define USB_FUNC_ep_done_enable(ep_mask) \
                               (USB_GLOBAL_set_bit(usb_func_regs.ep_done_en_reg,ep_mask))
/* Clear this bit(disable) is done by setting the corresponding bit in EndpointDoneEnableClr Register (0x174) */

/* EP_TOG_BITS_REG (0x078) */

/* Register's Macros  - Toggle register is a write '1' to clear */
#define USB_FUNC_ep_tog_bits_set(ep_mask) \
                                (USB_GLOBAL_toggle_bit(usb_func_regs.ep_tog_bits_reg,ep_mask)) 

/* FRAME_NUM_REG (0x07C) */

/* Register's Macros */
#define USB_FUNC_FRAMENUMB_MASK  0x000007FF

#define USB_FUNC_framenumb_get() (usb_func_regs.frame_num_reg & USB_FUNC_FRAMENUMB_MASK)
/* Setting this bit Clear(not ready) the corresponding bit in EP_READY_REG (0x068) */
#define USB_FUNC_set_ep_not_ready(ep_mask) \
                                (USB_GLOBAL_write_bit(usb_func_regs.frame_num_reg,ep_mask)) 

/* SYS_INT_EN_CLR_REG (0x14C) */

/* Register's Masks */
#define USB_FUNC_DONEREGIENCLRDSP_MASK  0x00000020
#define USB_FUNC_SOFDETIENCLR_MASK      0x00000010
#define USB_FUNC_DONEREGIENCLR_MASK     0x00000008
#define USB_FUNC_SUSPDETIENCLR_MASK     0x00000004
#define USB_FUNC_RSMFINIENCLR_MASK      0x00000002
#define USB_FUNC_RESETIENCLR_MASK       0x00000001

/* Register's Macros */
/* read system interrupt reset enable */
#define USB_FUNC_resetienclr_get()      (USB_GLOBAL_read_bit(usb_func_regs.sys_int_en_clr_reg,USB_FUNC_RESETIENCLR_MASK))
/* set system interrupt reset enable */
/* Setting this bit clears the corresponding bit in SystemInterruptEnable Register (0x04C) */
#define USB_FUNC_resetienclr_set()      (USB_GLOBAL_set_bit(usb_func_regs.sys_int_en_clr_reg,USB_FUNC_RESETIENCLR_MASK))

/* XY_INT_EN_CLR_REG (0x158) */

/* Register's Macros */
/* Setting this bit clears(disable) the corresponding bit in XYInterruptEnable Register (0x058) */
#define USB_FUNC_xy_int_disable(ep_mask) \
                              (USB_GLOBAL_write_bit(usb_func_regs.xy_int_en_clr_reg,ep_mask))

/* EP_EN_CLR_REG (0x164) */

/* Register's Macros */
#define USB_FUNC_ep_enable_clr_get(ep_mask) \
                               (USB_GLOBAL_read_bit(usb_func_regs.ep_en_clr_reg,ep_mask))
/* Setting this bit clears(disable) the corresponding bit in EndpointEnable Register (0x064) */
#define USB_FUNC_ep_disable(ep_mask) \
                               (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.ep_en_clr_reg,ep_mask))

/* IMMEDIATE_INT_CLR_REG (0x16C) */

/* EP_DONE_EN_CLR_REG (0x174) */

/* Register's Macros */
#define USB_FUNC_ep_done_enable_clr_get(ep_mask) \
                               (USB_GLOBAL_read_bit(usb_func_regs.ep_done_en_clr_reg,ep_mask))
/* Setting this bit clears(disable) the corresponding bit in EndpointDoneEnable Register (0x074) */
#define USB_FUNC_ep_done_disable(ep_mask) \
                               (USB_GLOBAL_wrt1toclr_bit(usb_func_regs.ep_done_en_clr_reg,ep_mask))

/*--------------------*/
/* USB_CTRL_REG_BLOCK */
/*--------------------*/

/* USB_CTRL_REG */

/* Register's Masks */
#define USB_CTRL_I2CWUINTSTAT_MASK      0x08000000
#define USB_CTRL_OTGWUINTSTAT_MASK      0x04000000
#define USB_CTRL_HOSTWUINTSTAT_MASK     0x02000000
#define USB_CTRL_FNTWUINTSTAT_MASK      0x01000000
#define USB_CTRL_I2CWUINTEN_MASK        0x00080000
#define USB_CTRL_OTGWUINTEN_MASK        0x00040000
#define USB_CTRL_HOSTWUINTEN_MASK       0x00020000
#define USB_CTRL_FNTWUINTEN_MASK        0x00010000
#define USB_CTRL_OTGBYPVAL_MASK         0x00000C00 
#define USB_CTRL_HOST1BYPVAL_MASK       0x00000300 
#define USB_CTRL_OTGPWRMASK_MASK        0x00000040 
#define USB_CTRL_HOST1PWRMASK_MASK      0x00000020 
#define USB_CTRL_HOST2PWRMASK_MASK      0x00000010 
#define USB_CTRL_USBBYP_MASK            0x00000004 
#define USB_CTRL_HOST1TXENOE_MASK       0x00000002
#define USB_CTRL_CLOCKEN_MASK           0x00000001 

#define USB_CTRL_OTGBYPVAL_CLR_MASK     0x00000003 
#define USB_CTRL_HOST1BYPVAL_CLR_MASK   0x00000003 


/*--------------------*/
/* USB_EP_DESC_BLOCK  */
/*--------------------*/
/* DWORD0 */
/* Register's Masks */
#define USB_EP_DESC_STALL_MASK        0x80000000
#define USB_EP_DESC_SETUP_MASK        0x40000000
#define USB_EP_DESC_OVERRUN_MASK      0x20000000
#define USB_EP_DESC_AUTOISO_MASK      0x10000000
#define USB_EP_DESC_FORMAT_MASK       0x0000C000
#define USB_EP_DESC_MAXPKTSIZ_MASK    0x03FF0000

/* Register's Macros */
#define USB_EP_DESC_stall_get(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 & USB_EP_DESC_STALL_MASK)
#define USB_EP_DESC_stall_set(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 |= USB_EP_DESC_STALL_MASK)
#define USB_EP_DESC_stall_clear(ep_num)           (usb_ep_desc[ep_num].ep_desc_dword0 &= ~(USB_EP_DESC_STALL_MASK))

#define USB_EP_DESC_setup_get(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 & USB_EP_DESC_SETUP_MASK)
#define USB_EP_DESC_setup_set(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 |= USB_EP_DESC_SETUP_MASK)
#define USB_EP_DESC_setup_clear(ep_num)           (usb_ep_desc[ep_num].ep_desc_dword0 &= ~(USB_EP_DESC_SETUP_MASK))

#define USB_EP_DESC_overrun_get(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 & USB_EP_DESC_OVERRUN_MASK)
#define USB_EP_DESC_overrun_set(ep_num)             (usb_ep_desc[ep_num].ep_desc_dword0 |= USB_EP_DESC_OVERRUN_MASK)
#define USB_EP_DESC_overrun_clear(ep_num)           (usb_ep_desc[ep_num].ep_desc_dword0 &= ~(USB_EP_DESC_OVERRUN_MASK))

/* DWORD1 */

/* Register's Masks */
#define USB_EP_DESC_XYBUFSRTAD_MASK   0x0000FFFF 

/* USB module address*/
#define OTG_BASE_ADDR (UINT32 *) &usb_core_regs
#define OTG_EP_BASE   OTG_BASE_ADDR + 0x0400


/* Register's Macros */
/* get X/Y buffer physical address */
/* USB DATA memory for SCM is defined 0x50028000 , the USBOTG HW will use a 0x1000 offset frpm USB base address (0x500284000)*/
#define USB_EP_DESC_xbuf_addr_get(ep_num)         ((UINT32 *)((UINT32)OTG_BASE_ADDR + (UINT32)0x3000 + (UINT32)(usb_ep_desc[ep_num].ep_desc_dword1 & USB_EP_DESC_XYBUFSRTAD_MASK)))
#define USB_EP_DESC_ybuf_addr_get(ep_num)         ((UINT32 *)((UINT32)OTG_BASE_ADDR + (UINT32)0x3000 + (UINT32)((usb_ep_desc[ep_num].ep_desc_dword1 >> 16 ) & USB_EP_DESC_XYBUFSRTAD_MASK)))


/* DWORD3 */

/* Register's Masks */
#define USB_EP_DESC_TTLBTECNT_MASK    0x001FFFFF 
#define USB_EP_DESC_BUFSIZE_MASK      0xFFE00000 

/* Register's Macros */
#define USB_EP_DESC_ttlbtecnt_get(ep_num)         (usb_ep_desc[ep_num].ep_desc_dword3 & USB_EP_DESC_TTLBTECNT_MASK)     
#define USB_EP_DESC_ttlbtecnt_set(ep_num,val)     (usb_ep_desc[ep_num].ep_desc_dword3 =\
                                                              ((usb_ep_desc[ep_num].ep_desc_dword3 & ~USB_EP_DESC_TTLBTECNT_MASK)|\
															   (val & USB_EP_DESC_TTLBTECNT_MASK)))     


/************** STRUCTURES, ENUMS, AND TYPEDEFS *******************************/


typedef struct {
UINT32 hw_mode_reg;
UINT32 core_int_status_reg;
UINT32 core_int_en_reg;
UINT32 clock_ctrl_reg;
UINT32 reset_ctrl_reg;
UINT32 frame_interval_reg;      /* not used */
UINT32 frame_remaining_reg;     /* not used */
UINT32 hnp_ctrl_status_reg;     /* not used */
UINT32 hnp_timer1_reg;          /* not used */
UINT32 hnp_timer2_reg;          /* not used */
UINT32 hnp_timer3_plus_ctrl_reg;/* not used */
UINT32 hnp_int_status_reg;      /* not used */
UINT32 hnp_int_ena_status_reg;  /* not used */
UINT32 cpu_ep_sel_reg;
UINT32 dsp_ep_sel_reg;
UINT32 core_int_status_en_clr_reg;
} USB_CORE_REG_BLOCK;

typedef struct {
UINT32 func_cmd_status_reg;
UINT32 dev_addr_reg;
UINT32 sys_int_status_reg;
UINT32 sys_int_en_reg;
UINT32 xbuff_int_status_reg;
UINT32 ybuff_int_status_reg;
UINT32 xy_int_en_reg;
UINT32 xfilled_status_reg;
UINT32 yfilled_status_reg;
UINT32 ep_en_reg;
UINT32 ep_ready_reg;
UINT32 immediate_int_reg;
UINT32 ep_done_status_reg;
UINT32 ep_done_en_reg;
UINT32 ep_tog_bits_reg;
UINT32 frame_num_reg;
UINT32 empty_space1[51];     /* filler */
UINT32 sys_int_en_clr_reg;
UINT32 empty_space2[2];      /* filler */
UINT32 xy_int_en_clr_reg;
UINT32 empty_space3[2];      /* filler */
UINT32 ep_en_clr_reg;
UINT32 empty_space4[1];      /* filler */
UINT32 immediate_int_clr_reg;
UINT32 empty_space5[1];      /* filler */
UINT32 ep_done_en_clr_reg;
} USB_FUNC_REG_BLOCK;

typedef struct {
UINT32 usb_ctrl_reg;
} USB_CTRL_REG_BLOCK;

typedef struct {
UINT32 ep_desc_dword0;
UINT32 ep_desc_dword1;
UINT32 ep_desc_dword2;
UINT32 ep_desc_dword3;
} USB_EP_DESC_BLOCK;

enum {
USB_EP0_OUT,
USB_EP0_IN,
USB_EP1_OUT,
USB_EP1_IN,
USB_EP2_OUT,
USB_EP2_IN,
};
typedef UINT8 USB_ENDPOINT_NUM;

/************** FUNCTION PROTOTYPES *******************************************/


/************** MACROS ********************************************************/

/************** CLASS DEFINITIONS *********************************************/

/************** GLOBAL VARIABLES **********************************************/
extern volatile USB_CORE_REG_BLOCK usb_core_regs;
extern volatile USB_FUNC_REG_BLOCK usb_func_regs;

/* 32 Endpoints Descriptors */
extern volatile USB_EP_DESC_BLOCK usb_ep_desc[6];

#ifdef __cplusplus /* allow #include in a C++ file (only put this in .h files) */
}
#endif
#endif /* end of - prevent inadvertently including a header file twice */



