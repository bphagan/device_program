/*----------------------------------------------------------------------
* FILE:  functions.c
*-----------------------------------------------------------------------
*             (C) Copyright 2001 Metrowerks Corp.
*                 ALL RIGHTS RESERVED .
*
*   THIS IS  CONFIDENTIAL  PROPRIETARY SOURCE CODE OF METROWERKS CORP.
*
*          The copyright notice above does not evidence any
*         actual or intended publication of such source code.
*-----------------------------------------------------------------------
*
* DESCRIPTION: Diagnostic board test on the TORTOLA (i.mx31) board
*              Implementation file for common functions
*
* REFERENCES: 
*      1) TORTOLA spec
*
* HISTORY:
*
* 01 Feb  2005 zeldal	Created
*
*--------------------------------------------------------------------------*/

// #####   HEADER FILE INCLUDES   ################################################### 
#include <stdio.h>
#include "functions.h"
//#include "tortola_memory_map_defines.h"
//#include "verilog_trigger.h"

// #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################### 

// #####    COMMON API  ############################ 

//----------------------------------------------------------------------
//  Verilog testbench Interaction Functions
//----------------------------------------------------------------------

//{{{1

// ===  FUNCTION  ======================================================================
// 
//         Name:  info_trigger
// 
//  Description: sends info message composed of 3 32-bit words to verilog-trigger,
//               may be used to send comparison events to verilog trigger
//               output message format is : 
// "Info ARM Event Triggered : INFO1 : <event> , INFO2 : <exp_data> , INFO3 : <act_data>"
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             event            event number/ID or data word #1
//        in:  WORD             exp_data         expected data / data word #2
//        in:  WORD             act_data         actual data / data word #3
//    in-out:  
//       out:  
//    return: void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 12:05:45 IST
//  Revision:  none
// =====================================================================================
/*
void info_trigger(WORD event,WORD exp_data , WORD act_data)
{ //{{{2
  mem32_write( ARM_PORTHOLE_ADD+0x4 ,event);
  mem32_write( ARM_PORTHOLE_ADD+0x8 ,exp_data);
  mem32_write( ARM_PORTHOLE_ADD+0xc ,act_data);
  mem32_write( ARM_PORTHOLE_ADD , arm_vt_info);

} //2}}}
*/
// ===  FUNCTION  ======================================================================
// 
//         Name:  info_checktest_trigger
// 
//  Description: compares expected and actual data, and sends pass/fail events
//               and information message to verilog trigger
//               output message format is : 
// "CheckTest Info ARM Event Triggered : EVENT : <event>  Expected : <exp_data> Actual : <act_data>"
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              event           event number/ID
//        in: WORD              exp_data        expected data
//        in: WORD              act_data        actual data
//    in-out:  
//       out:  
//    return: void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 12:08:23 IST
//  Revision:  none
// =====================================================================================
//void info_checktest_trigger(WORD event,WORD exp_data , WORD act_data)
//{ //{{{2
//  mem32_write( ARM_PORTHOLE_ADD+0x4 ,event);
//  mem32_write( ARM_PORTHOLE_ADD+0x8 ,exp_data);
//  mem32_write( ARM_PORTHOLE_ADD+0xC ,act_data);
//  mem32_write( ARM_PORTHOLE_ADD , arm_vt_checktest_info);

//} //2}}}

// ===  FUNCTION  ======================================================================
// 
//         Name:  wait_for_gpio_mcu_message 
// 
//  Description:  wait (loop) for certain 4 bit value on 
//                GPIO pads ({GPIO1_3,GPIO1_2,GPIO1_1,GPIO1_0}),
//                by reading PSR register of GPIO1.
//                Those pads are by default in GPIO mode
//                GPIO driver is by default enabled
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             val             value on GPIO to wait for
//    in-out:  
//       out:  
//    return:  void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 12:00:09 IST
//  Revision:  none
// =====================================================================================

void wait_for_gpio_mcu_message (WORD val)
{ //{{{2
	while (!((reg32_read(GPIO1_PSR0)&0xf) == val) );
    return; 
} //2}}}

//1}}}

//----------------------------------------------------------------------
//  Init Functions
//----------------------------------------------------------------------

//{{{1
// ===  FUNCTION  ======================================================================
// 
//         Name:  InitArray
// 
//  Description:  Initializes 2 arrays (real and expected results) 
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             *exp_val        expected results array
//        in:  WORD             *res_val        real results array
//        in:  int              num_of_res      number of results (array size)
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 12:01:19 IST
//  Revision:  none
// =====================================================================================
void InitArray(WORD *exp_val, WORD *res_val, int num_of_res)
{ //{{{2
   int i; 
   for (i=0; i<num_of_res; i++){
       exp_val[i] = 1; 
       res_val[i] = 0; 
   }
   return; 
} //2}}}


// ===  FUNCTION  ======================================================================
// 
//         Name:  configure_iomuxc_for_gpio_message_mcu 
// 
//  Description:  configure GPIO pads, so gpio message mechanism will work 
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: void 
//    in-out:  
//       out:  
//    return: void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/02/04 14:19:28 IST
//  Revision:  none
// =====================================================================================
/*
void configure_iomuxc_for_gpio_message_mcu (void) {
    // need to be on GPIO mode
    reg32_write_mask(SW_MUX_CTL_GPIO1_0_GPIO1_1_GPIO1_2_GPIO1_3,0x01010101,0xffffffff);
//  reg32_write_mask(SW_MUX_CTL_UART_CTS2_B_GPIO0_GPIO1_GPIO2,0x00121212,0x00ffffff);
//   reg32_write_mask(SW_MUX_CTL_GPIO3_GPIO4_GPIO5_UART_TXD1,0x24000000,0xff000000);
}
*/
//1}}}

//----------------------------------------------------------------------
//  Check Test Functions
//----------------------------------------------------------------------

//{{{1

// ===  FUNCTION  ======================================================================
// 
//         Name:  CheckTest
// 
//  Description: Main CheckTest routine. compares 2 arrays, gives pass/fail results,
//               sends events to verilog trigger, and finishes test on current processor
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             *exp_val        expected results array
//        in:  WORD             *res_val        real results array
//        in:  int              num_of_res      number of results (array size)
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 12:11:52 IST
//  Revision:  none
// =====================================================================================
int CheckTest(WORD *exp_val, WORD *res_val, int num_of_res)
{ //{{{2
   WORD var; 
   int rc;
   
//   var = reg32_read(GPIO1_PSR0); 
//   var &= 0x00000080; 
//   if (var==0x00000080) 
//      rc = IntCheckTest(exp_val,res_val,num_of_res);
//   else  
   	rc = ExtCheckTest(exp_val,res_val,num_of_res);
   // After CheckTest - test should end !
//   verilog_trigger(arm_vt_finish); 
	return rc;
} //2}}}

// ===  FUNCTION  ======================================================================
// 
//         Name:  ExtCheckTest
// 
//  Description: Compares 2 arrays (expected Vs. real results) and outputs
//               pass/fail events through verilog_trigger,  
//
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              *exp_val          expected values array
//        in: WORD              *res_val          real results array
//        in: int               num_of_res        number of results (array size) 
//    in-out:  
//       out: 
//    return: void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 11:57:03 IST
//  Revision:  none
// =====================================================================================
int ExtCheckTest(WORD *exp_val, WORD *res_val, int num_of_res) 
{ //{{{2
int rc;

  rc = compare_array(exp_val,res_val,num_of_res);
  return rc;
} //2}}}

// ===  FUNCTION  ======================================================================
// 
//         Name:  IntCheckTest
// 
//  Description: Compares 2 arrays (expected Vs. real results) and outputs
//               pass/fail events through verilog_trigger, and uses GPIO 
//               messaging.
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              *exp_val          expected values array
//        in: WORD              *res_val          real results array
//        in: int               num_of_res        number of results (array size) 
//    in-out:  
//       out: 
//    return: void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 11:57:03 IST
//  Revision:  none
// =====================================================================================
int IntCheckTest(WORD *exp_val, WORD *res_val, int num_of_res) 
{//{{{2
    int i; 
    int error=0; 
    int rc = 0;
    
    for (i=0 ; i < num_of_res ; i++){
//        info_checktest_trigger(i,exp_val[i],res_val[i]);
        if (exp_val[i] == res_val[i]){ 
//            verilog_trigger(arm_vt_pass); 
			;
        }else{ 
            error++; 
//            verilog_trigger(arm_vt_fail); 
			rc = 1;
        }
    }
    if (error != 0) { 
        reg32_write(GPIO1_DR0, 0x00000010);
    }else{
        reg32_write(GPIO1_DR0, 0x00000000);
    }
    for (i=0 ; i < 32 ; i++); 
	
	reg32_write(GPIO1_DR0, 0x00000020);
    
    return rc;
} //2}}}



//1}}}


//----------------------------------------------------------------------
//  Data Compare Functions
//----------------------------------------------------------------------

//{{{1

// ===  FUNCTION  ======================================================================
// 
//         Name:  compare_array
// 
//  Description:  compare 2 arrays (expected values and real results),
//                and trigger pass/fail event for each comparison
//                uses info_checktest_trigger
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              *exp_val        expected values array
//        in: WORD              *res_val        real results array
//        in: int               num_of_res      number of results (array size)
//    in-out:  
//       out:  
//    return: void              
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:41:53 IST
//  Revision:  none
// =====================================================================================
int compare_array(WORD *exp_val, WORD *res_val, int num_of_res) 
{ //{{{2
  int i; 
  int rc=0;
  int err = 0;

  for (i=0 ; i < num_of_res ; i++) 
  {
//     info_checktest_trigger(i,exp_val[i],res_val[i]);		  
//     if (exp_val[i] == res_val[i]) {
//       verilog_trigger(arm_vt_pass); }
//     else {verilog_trigger(arm_vt_fail);}
     if (exp_val[i] != res_val[i]) 
     {
     	rc = 1;
		#ifdef PRINT_ERR
			printf("Error receive : word num = %d sent 0x%lx, received 0x%lx\n", i, exp_val[i], res_val[i]);
		#endif
     	if (err++ >= 5)
     	{
     		printf("Error :err numm > 5\n");
     		break; 
     	}
     }
  }
  return rc;
} //2}}}


// ===  FUNCTION  ======================================================================
// 
//         Name:  compare_results
// 
//  Description:  compare 2 data words (expected value and real result)
//                and trigger pass/fail event.
//                uses info_trigger. returns pass/fail indication
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              reg_addr       data word, used for the info message
//        in: WORD              exp_val        expected value
//        in: WORD              res_val        real result
//    in-out:  
//       out:  
//    return: int               flag            pass(0)/fail(1)
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:41:53 IST
//  Revision:  none
// =====================================================================================
int compare_results(WORD reg_addr,WORD exp_val, WORD res_val) 
{ //{{{2
   int flag;
   
//   info_trigger(reg_addr,exp_val,res_val);
   if (exp_val == res_val) {
//      verilog_trigger(arm_vt_pass);
      flag=0;
   } else {
//		 verilog_trigger(arm_vt_fail);
 		 printf ("Error receive data: Sent 0x%08%x Received 0x%08%x\n", exp_val, res_val);
         flag=1;
   }
   return flag;		 
} //2}}}



// ===  FUNCTION  ======================================================================
// 
//         Name:  word_data_compare 
// 
//  Description:  compare 2 data half words, and trigger pass/fail event
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              worda           first word to compare 
//        in: WORD              wordb           second word to compare
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:34:44 IST
//  Revision:  none
// =====================================================================================
int word_data_compare (WORD worda , WORD wordb)
{ //{{{2
int rc;

//  info_checktest_trigger(DUMMY_INFO,worda,wordb);		
  if (worda != wordb )    
  	rc = 1;
//  	verilog_trigger(arm_vt_fail);
  else              
	rc = 0;
//       verilog_trigger(arm_vt_pass);
	return rc;
} //2}}}

// ===  FUNCTION  ======================================================================
// 
//         Name:  hw_data_compare
// 
//  Description:  compare 2 data half words, and trigger pass/fail event
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: HALF              hworda          first half word to compare 
//        in: HALF              hwordb          second half word to compare
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:34:44 IST
//  Revision:  none
// =====================================================================================
int hw_data_compare (HALF hworda , HALF hwordb)
{ //{{{2
int rc;
 
//  info_checktest_trigger(DUMMY_INFO,hworda,hwordb);		
  if(hworda != hwordb )  
	rc = 1;
//  	verilog_trigger(arm_vt_fail);
  else     
	rc = 0;
//        verilog_trigger(arm_vt_pass);
	return rc;
} //2}}}


// ===  FUNCTION  ======================================================================
// 
//         Name:  byte_data_compare
// 
//  Description:  compare 2 data bytes, and trigger pass/fail event
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: HALF              bytea           first byte to compare 
//        in: HALF              byteb           second byte to compare
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:34:44 IST
//  Revision:  none
// =====================================================================================

int byte_data_compare (BYTE bytea , BYTE byteb)
{ //{{{2
int rc;

//  info_checktest_trigger(DUMMY_INFO,bytea,byteb);		
  if (bytea != byteb )    
	rc = 1;
//  verilog_trigger(arm_vt_fail);
  else     
	rc = 0;
//                verilog_trigger(arm_vt_pass);
	return rc;
} //2}}}

//1}}}


//----------------------------------------------------------------------
//  Write With Mask (write only certain bits)
//----------------------------------------------------------------------

//{{{1

// ===  FUNCTION  ======================================================================
// 
//         Name:  regN_write_mask
// 
//  Description:  Write value to a register using bit mask.
//                N=8,16,32
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              addr            address to access
//        in: BYTE/HALF/WORD    wdata           data to write, size depends on N
//        in: BYTE/HALF/WORD    mask            bit mask for writing, size depends on N
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/02/04 14:00:05 IST
//  Revision:  none
// =====================================================================================
void reg8_write_mask(WORD addr , BYTE wdata , BYTE mask)
{//{{{2
   BYTE	masked_wdata,rdata;

   rdata=reg8_read(addr);
   masked_wdata=(((~mask)&rdata)|(mask&wdata));
   reg8_write(addr,masked_wdata);
} //2}}}		


void reg16_write_mask(WORD addr , HALF wdata , HALF mask)
{//{{{2
   HALF	masked_wdata,rdata;

   rdata=reg16_read(addr);
   masked_wdata=(((~mask)&rdata)|(mask&wdata));
   reg16_write(addr,masked_wdata);
}//2}}}

void reg32_write_mask(WORD addr , WORD wdata , WORD mask) 
{ //{{{2
   WORD	masked_wdata,rdata;

   rdata=reg32_read(addr);
   masked_wdata=(((~mask)&rdata)|(mask&wdata));
   reg32_write(addr,masked_wdata);
} //2}}}

//1}}}

//----------------------------------------------------------------------
//  Read/Write Compare Functions
//----------------------------------------------------------------------

//{{{1

// ===  FUNCTION  ======================================================================
// 
//         Name:  regN_rw_test
// 
//  Description:  write value to register, read it back and compare to expected value.
//                and trigger pass/fail event (uses regN_read_tst)
//                size is N=8,16,32
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD             addr             addr to access
//        in: BYTE/HALF/WORD   wdata            data to write, size depends on N
//        in: WORD             exp_rdata        expected value
//    in-out:  
//       out:  
//    return: void 
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 16:41:28 IST
//  Revision:  none
// =====================================================================================
void reg8_rw_test(WORD addr, BYTE wdata, BYTE exp_rdata) 
{ //{{{2
   reg8_write(addr,wdata);
   reg8_read_tst(addr,exp_rdata,0xff);
} //2}}}

void reg16_rw_test(WORD addr, HALF wdata, HALF exp_rdata) 
{ //{{{2
   reg16_write(addr,wdata);
   reg16_read_tst(addr,exp_rdata,0xffff);
} //2}}}

void reg32_rw_test(WORD addr, WORD wdata, WORD exp_rdata) 
{ //{{{2
   reg32_write(addr,wdata);
   reg32_read_tst(addr,exp_rdata,0xffffffff);
} //2}}}

 

//1}}}

// #####    Project Specific API  ############################ 

//----------------------------------------------------------------------
//  Tortola/Argon Specific Function (Not Common API)
//----------------------------------------------------------------------

//{{{1
// ===  FUNCTION  ======================================================================
// 
//         Name: release_spba 
// 
//  Description:  release spba from ARM ownership
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: void 
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  09/06/04 15:22:20 IDT
//  Revision:  none
// =====================================================================================


void release_spba(void){ //{{{2

  reg32_write( SPBA_PRR0 , 0x0);
  reg32_write( SPBA_PRR1 , 0x0);
  reg32_write( SPBA_PRR2 , 0x0);
  reg32_write( SPBA_PRR3 , 0x0);
  reg32_write( SPBA_PRR4 , 0x0);
  reg32_write( SPBA_PRR5 , 0x0);
  reg32_write( SPBA_PRR6 , 0x0);
  reg32_write( SPBA_PRR7 , 0x0);
  reg32_write( SPBA_PRR8 , 0x0);
  reg32_write( SPBA_PRR9 , 0x0);
  reg32_write( SPBA_PRR10 , 0x0);
  reg32_write( SPBA_PRR11 , 0x0);
  reg32_write( SPBA_PRR12 , 0x0);
  reg32_write( SPBA_PRR13 , 0x0);
  reg32_write( SPBA_PRR14 , 0x0);
   
} //2}}}

//1}}}
//
