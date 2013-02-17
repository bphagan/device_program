#include "config_pad_mode.h"

// ###########################################################
// # Functions : 'config_pad_mode' , 'config_pad_settings' . #
// ###########################################################

//  SW_MUX_CTL configuration
// **************************

// The function 'config_pad_mode',configures the iomux/iomuxc
// of a specific pad to a desired mode. 
// Meaning it determines the IN and OUT controls to the iomux so that 
// The proper signal will be routed in/out.
// The input and output mode are independent of each other,
// and therfore are configured seperately.
// For instance , if we would like to configure pad 'I2C_CLK' as 'functional'
// in the output mode and 'alternate1' in the input mode we would simply give the following command :

// config_pad_mode(I2C_CLK,func_out,alt1_in);

// Moreover , there's a possibility to configure a pad to route an input signal 
// to several modes in parallel. 
// This can be done using one of the defines in 'functions.h', as the input mode: 





WORD get_mixed_mode (WORD byte_in_reg,WORD output_mode,WORD input_mode) {
   WORD mixed_mode;

   switch (byte_in_reg) {
      case  0:mixed_mode=(input_mode+output_mode);
			  break;
      case  1:mixed_mode=(input_mode+output_mode)*0x100;
			  break;
      case  2:mixed_mode=(input_mode+output_mode)*0x10000; 
   	 	      break;
      case  3:mixed_mode=(input_mode+output_mode)*0x1000000; 
			  break;
   }  
   return mixed_mode;
}		



void config_pad_mode(WORD pad_name,WORD output_mode,WORD input_mode) {
   WORD wdata,reg_addr,offset;
   int pad_offset;

   pad_offset=(328-pad_name)/4;
   offset=pad_offset*4;
   reg_addr=IOMUXC_BASE_ADDR+offset+0xc;
   
   switch (pad_name%4) {
	  case 0: wdata=get_mixed_mode(0,output_mode,input_mode);
              reg32_write_mask(reg_addr,wdata,BYTE0_MASK);
			  break;
	  case 1: wdata=get_mixed_mode(3,output_mode,input_mode);
              reg32_write_mask(reg_addr,wdata,BYTE3_MASK);
			  break;
	  case 2: wdata=get_mixed_mode(2,output_mode,input_mode);
              reg32_write_mask(reg_addr,wdata,BYTE2_MASK);
			  break;
	  case 3: wdata=get_mixed_mode(1,output_mode,input_mode);
              reg32_write_mask(reg_addr,wdata,BYTE1_MASK);
			  break;
      default : 
	break;
//verilog_trigger(arm_vt_error);
   }
}

//############################################################################


//  SW_PAD_CTL configuration
// **************************
// The 'config_pad_settings' function configures a pad's physical settings
// such as : open drain , pull up/down , schmidt trigger etc.
// by writing to the appropriate 10 bits of a specific 
// 32-bit 'SW_PAD_CTL' register in the iomuxc.
// The activation of this function is done as follows :

// config_pad_settings(<pad_name>,<data_to_write);

// Here the user must know excatly which bit of the 10 bits controls which feature.
// This information is listed below :

// # fast/slow buffer enable (slew rate)  
// ipp_sre - 0
// # drive strength          
// ipp_dse0 - 1
// ipp_dse1 - 2
// # open drain enable        
// ipp_ode - 3
// # hysteresis enable        
// ipp_hys - 4
// # sw pull up/down configurat
// ipp_pus1 - 5
// ipp_pus0 - 6
// # pull up/down enable       
// ipp_pue - 7
// # pull/keep select          
// ipp_pke - 8
// # loop back
// sw_input_on - 9 


void config_pad_settings(WORD pad_name,WORD wdata) {
   WORD shifted_wdata,offset,reg_addr;
   int pad_offset;
   
   pad_offset=(330-pad_name)/3;
   offset=pad_offset*4;
   reg_addr=IOMUXC_BASE_ADDR+offset+0x154;
   switch (pad_name%3) {
	  case 0: shifted_wdata=wdata;
              reg32_write_mask(reg_addr,shifted_wdata,PAD0_MASK);
       	      break;
      case 1: shifted_wdata=wdata*0x100000;
              reg32_write_mask(reg_addr,shifted_wdata,PAD2_MASK);
       	      break;
      case 2: shifted_wdata=wdata*0x400;
              reg32_write_mask(reg_addr,shifted_wdata,PAD1_MASK);
       	      break;
      default : 
       	      break;

//verilog_trigger(arm_vt_error);
   }
}

