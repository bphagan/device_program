/*----------------------------------------------------------------------
* FILE:  functions.h
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
*              Defines file for common functions
*
* REFERENCES: 
*      1) TORTOLA spec
*
* HISTORY:
*
* 01 Feb  2005 zeldal	Created
*
*--------------------------------------------------------------------------*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #####   EXPORTED MACROS   ########################################################### {{{1


//----------------------------------------------------------------------
//  Some Genaral Macros
//----------------------------------------------------------------------
#define FALSE		0
#define TRUE		1

#define DUMMY_INFO 0xf00f00


//----------------------------------------------------------------------
//  Basic Read/Write Macros
//----------------------------------------------------------------------
//{{{2
// ===  MACRO ======================================================================
// 
//         Name:  regN_read(addr)
// 
//  Description:  Basic Register Read/Write Macros -returns register value
//                N = 8,16,32 - access size
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              addr 
//    in-out:  
//       out: BYTE/HALF/WORD                    value returned by macro, type depends on
//                                              N
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:37:12 IST
//  Revision:  none
// =====================================================================================
#define reg8_read(addr)       *((BYTE *)(addr))
#define reg16_read(addr)      *((HALF *)(addr))
#define reg32_read(addr)      *(WORD *)((addr))

// ===  MACRO  ======================================================================
// 
//         Name:  regN_write(addr,val)
// 
//  Description:  Basic Register Read/Write Macros - writes val to addr
//                N = 8,16,32 - access size
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             addr            address to access
//        in:  BYTE/HALF/WORD   val             value to write,  Type depends on N       
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:38:31 IST
//  Revision:  none
// =====================================================================================
#define reg8_write(addr,val)  *((BYTE *)(addr)) = (val)
#define reg16_write(addr,val) *((HALF *)(addr)) = (val)
#define reg32_write(addr,val) *((WORD *)(addr)) = (val)


// ===  MACRO ======================================================================
// 
//         Name:  memN_read(addr)
// 
//  Description:  Basic Memory Read/Write Macros - returns memory value
//                N = 8,16,32 - access size
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              addr 
//    in-out:  
//       out: BYTE/HALF/WORD                    value returned by macro, type depends on
//                                              N
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:37:12 IST
//  Revision:  none
// =====================================================================================
#define mem8_read(addr)       *((BYTE *)(addr))
#define mem16_read(addr)      *((HALF *)(addr))
#define mem32_read(addr)      *(WORD *)((addr))

// ===  MACRO  ======================================================================
// 
//         Name:  memN_write(addr,val)
// 
//  Description:  Basic Memory Read/Write Macros - writes val to addr
//                N = 8,16,32 - access size
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             addr            address to access
//        in:  BYTE/HALF/WORD   val             value to write,  Type depends on N       
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:38:31 IST
//  Revision:  none
// =====================================================================================
#define mem8_write(addr,val)  *((BYTE *)(addr)) = (val)
#define mem16_write(addr,val) *((HALF *)(addr)) = (val)
#define mem32_write(addr,val) *((WORD *)(addr)) = (val)

//2}}}

//----------------------------------------------------------------------
//  Read and Compare Macros
//----------------------------------------------------------------------
//{{{2
// ===  MACRO     ======================================================================
// 
//         Name:  regN_read_tst
// 
//  Description:  Read data from a given register,and check Vs. expected value.
//                N=8,16,32
//         
//    Examples:  reg8_read_tst(OWIRE_TIME_DIV,0x12,0ff)
//               Here we read 8 bits from an 8-bit register OWIRE_TIME_DIV of OWIRE, 
//               and expect all 8 bits to be equal to 0x12
//
//               reg16_read_tst(WDOG_WSR,0x1212,0x00ff)
//               Here we read 16 bits from a 16-bit register WDOG_WSR of WDOG,
//               and expect only the lower 8 bits to be equal to 0x12
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              reg_addr        address of register
//        in: BYTE/HALF/WORD    expect_val      expected value, type depends on N
//        in: BYTE/HALF/WORD    mask            bit mask, select bits to compare,
//                                              type depends on N
//    in-out:  
//       out:  
//    return: int                               pass(0)/fail(1) value   
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:55:41 IST
//  Revision:  none
// =====================================================================================
#define reg8_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg8_read(reg_addr) & mask))
#define reg16_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg16_read(reg_addr) & mask))
#define reg32_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg32_read(reg_addr) & mask))


// ===  MACRO     ======================================================================
// 
//         Name:  memN_read_tst
// 
//  Description: Identical to regN_read_tst, used for memory read and compare 
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              reg_addr        address to accedd
//        in: BYTE/HALF/WORD    expect_val      expected value, type depends on N
//        in: BYTE/HALF/WORD    mask            bit mask, select bits to compare,
//                                              type depends on N
//    in-out:  
//       out:  
//    return: int                               pass(0)/fail(1) value   
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:56:04 IST
//  Revision:  none
// =====================================================================================
#define mem8_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg8_read(reg_addr) & mask))
#define mem16_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg16_read(reg_addr) & mask))
#define mem32_read_tst(reg_addr,expect_val,mask) (compare_results(reg_addr,expect_val & mask,reg32_read(reg_addr) & mask))

//2}}}

//----------------------------------------------------------------------
//  Specific bits manipulation Macros
//----------------------------------------------------------------------
//{{{2
// ===  MACRO     ======================================================================
// 
//         Name:  regNsetbit
// 
//  Description:  Set specific bit in a register
//                N=8,16,32
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             addr            register address
//        in:  unsigned         bitpos          position of bit to set [0..N-1]
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 14:12:30 IST
//  Revision:  none
// =====================================================================================
#define  reg8setbit(addr,bitpos) \
         reg8_write((addr),(reg8_read((addr)) | (1<<(bitpos))))

#define  reg16setbit(addr,bitpos) \
         reg16_write((addr),(reg16_read((addr)) | (1<<(bitpos))))

#define  reg32setbit(addr,bitpos) \
         reg32_write((addr),(reg32_read((addr)) | (1<<(bitpos))))


// ===  MACRO     ======================================================================
// 
//         Name:  regNclrbit
// 
//  Description:  Clear specific bit in a register
//                N=8,16,32
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             addr            register address
//        in:  unsigned         bitpos          position of bit to clear [0..N-1]
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 14:16:03 IST
//  Revision:  none
// =====================================================================================
#define  reg8clrbit(addr,bitpos) \
         reg8_write((addr),(reg8_read((addr)) & (0xFF ^ (1<<(bitpos)))))

#define  reg16clrbit(addr,bitpos) \
         reg16_write((addr),(reg16_read((addr)) & (0xFFFF ^ (1<<(bitpos)))))

#define  reg32clrbit(addr,bitpos) \
         reg32_write((addr),(reg32_read((addr)) & (0xFFFFFFFF ^ (1<<(bitpos)))))

//2}}}

//----------------------------------------------------------------------
//  Interrupts Handling
//----------------------------------------------------------------------
//{{{2    
// ===  MACRO     ======================================================================
// 
//         Name: CAPTURE_INTERRUPT 
// 
//  Description:  assign a user handler routine to specific IRQ,
//                and override default routine
//                by default all interrupts are enabled, and will produce an 
//                error event
//  example: CAPTURE_INTERRUPT(GPT_INT_ROUTINE,my_int_handler)
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             irq_addr           default irq handler address
//        in:  function name    handler_routine    user supplied handler
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:45:53 IST
//  Revision:  none
// =====================================================================================
#define CAPTURE_INTERRUPT(irq_addr,handler_routine) mem32_write((irq_addr),(WORD)(handler_routine))



// ===  MACRO     ======================================================================
// 
//         Name:  setup_irq_hdler
// 
//  Description:  Bind  handler routine to certain FIQ (Fast IRQ),
//                by using interrupt number, or name (macro).
//                (while CAPTURE_INTERRUPT - uses handler routine address to override)
//                recommendation: use the name macro, and NOT the absolute number
//                
//
//      Examples: setup_irq_hdler(29,my_int_handler)  or, 
//                setup_irq_hdler(GPT_INT,my_int_handler)
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              int_name        interrupt number (or macro name) 
//        in: WORD              func_ptr        function name
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:19:53 IST
//  Revision:  none
// =====================================================================================
#define setup_irq_hdler(int_name,func_ptr) reg32_write(((WORD*) AVIC_IVR-(4*int_name)),(WORD) func_ptr )

    
// ===  MACRO     ======================================================================
// 
//         Name:  setup_fiq_hdler
// 
//  Description:  Bind  handler routine to certain FIQ (Fast IRQ)
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              int_name        interrupt number (or macro name) 
//        in: WORD              func_ptr        function name
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:20:09 IST
//  Revision:  none
// =====================================================================================
#define setup_fiq_hdler(int_name,func_ptr) reg32_write(((WORD*) AVIC_FVR-(4*int_name)),(WORD) func_ptr )

// ===  MACRO     ======================================================================
// 
//         Name:  enable_hdler
// 
//  Description:  Enabled triggering of specific IRQ
// 
//     Example :  enable_hdler(GPT_INT)
//
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD              int_name        IRQ to enable
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:20:37 IST
//  Revision:  none
// =====================================================================================
#define enable_hdler( int_name ) reg32_write(AVIC_INTENNUM, int_name )

// ===  MACRO     ======================================================================
// 
//         Name:  disable_hdler
// 
//  Description: Disable triggering of specific IRQ 
//
//      Example: disable_hdler(GPT_INT)
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in: WORD             int_name         IRQ to disable
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 15:20:48 IST
//  Revision:  none
// =====================================================================================
#define disable_hdler( int_name )  reg32_write(AVIC_INTDISNUM, int_name )


//2}}}

//----------------------------------------------------------------------
//  Exceptions Handling
//----------------------------------------------------------------------
//{{{2    
// ===  MACRO     ======================================================================
// 
//         Name:  CAPTURE_EXCEPTION 
// 
//  Description:  assign a user handler routine to specific Exception,
//                and override default routine
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             handle          Exception handler address
//        in:  function name    routine         user supplied routine
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:49:18 IST
//  Revision:  none
// =====================================================================================
#define CAPTURE_EXCEPTION(excep_addr,handler_routine) mem32_write((excep_addr),(WORD)(handler_routine))
//2}}}
//----------------------------------------------------------------------
//  Verilog testbench Interaction Macros
//----------------------------------------------------------------------
//{{{2
// ===  MACRO     ======================================================================
// 
//         Name:  verilog_trigger 
// 
//  Description:  trigger events in verilog_trigger module, event codes can be found in
//                verilog_trigger.h
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             trigger_code    Event code to trigger
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:51:43 IST
//  Revision:  none
// =====================================================================================
//#define verilog_trigger(trigger_code) mem32_write((ARM_PORTHOLE_ADD) , (trigger_code) )



// ===  MACRO     ======================================================================
// 
//         Name:  wait_for_gpio_message
// 
//  Description: wait for certain i4 bit value to appear on GPIO pads 
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  WORD             val             value to wait for. only 4 LSB are checked
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/02/04 14:30:04 IST
//  Revision:  none
// =====================================================================================
#define wait_for_gpio_message(val) wait_for_gpio_mcu_message(val)

//2}}}

//----------------------------------------------------------------------
//  Assembler Instructions macros
//----------------------------------------------------------------------
//{{{2    
// ===  MACRO     ======================================================================
// 
//         Name: nop 
// 
//  Description:  Execute "nop" assembler instruction
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  
//    in-out:  
//       out:  
//    return:  
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  03/01/04 13:54:11 IST
//  Revision:  none
// =====================================================================================
#define nop() asm ( "nop" );


//2}}}

    
//1}}}

// #####   EXPORTED TYPE DEFINITIONS   ################################################# {{{1

typedef volatile unsigned long WORD;
typedef volatile unsigned short HALF;
typedef volatile unsigned char BYTE;

//1}}}

// #####   HEADER FILE INCLUDES   ################################################### {{{1

//#include "argon_memory_map_defines.h"
#include "tortola_memory_map_defines.h"

//#include "verilog_trigger.h"
//#include "ccm_low_power_modes.h"
//#include "int_obs_function.h"
//#include "rwlib.h"
//#include "config_pad_mode.h"


//1}}}

// #####   EXPORTED FUNCTION DECLARATIONS   ############################################ {{{1


// #####   FUNCTION DECLARATIONS  - COMMON API ############################################ 


//----------------------------------------------------------------------
//  Verilog testbench Interaction Functions
//----------------------------------------------------------------------

//{{{2

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
//void info_trigger(WORD event ,WORD exp_data , WORD act_data);


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
void info_checktest_trigger(WORD event ,WORD exp_data , WORD act_data);

// ===  FUNCTION  ======================================================================
// 
//         Name:  wait_for_gpio_mcu_message 
// 
//  Description:  waits for certain value on GPIO mcu pins
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
void wait_for_gpio_mcu_message (WORD val);

//2}}}


//----------------------------------------------------------------------
//  Init Functions
//----------------------------------------------------------------------

//{{{2

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
void InitArray(WORD *exp_val, WORD *res_val, int num_of_res);

// ===  FUNCTION  ======================================================================
// 
//         Name:  configure_iomuxc_for_gpio_message_mcu 
// 
//  Description:  configure GPIO pads, so gpio message mechanism can work 
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
void configure_iomuxc_for_gpio_message_mcu(void);
//2}}}


//----------------------------------------------------------------------
//  Check Test Functions
//----------------------------------------------------------------------

//{{{2

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
int CheckTest(WORD *exp_val, WORD *res_val, int num_of_res);

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
int ExtCheckTest(WORD *exp_val, WORD *res_val, int num_of_res);

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
int IntCheckTest(WORD *exp_val, WORD *res_val, int num_of_res); 


//2}}}

//----------------------------------------------------------------------
//  Data Compare Functions
//----------------------------------------------------------------------

//{{{2

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
int compare_array(WORD *exp_val,WORD *res_val, int num_of_res);

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
int compare_results(WORD reg_addr,WORD exp_val,WORD res_val);



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
int word_data_compare (WORD worda , WORD wordb);

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
int hw_data_compare (HALF worda , HALF wordb);

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
int byte_data_compare (BYTE worda , BYTE wordb);

//2}}}
//----------------------------------------------------------------------
//  Write With Mask (write only certain bits)
//----------------------------------------------------------------------

//{{{2
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
void reg8_write_mask( WORD addr , BYTE wdata , BYTE mask);
void reg16_write_mask(WORD addr , HALF wdata , HALF mask);
void reg32_write_mask(WORD addr , WORD wdata , WORD mask);



//2}}}

//----------------------------------------------------------------------
//  Read/Write Compare Functions
//----------------------------------------------------------------------

//{{{2

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

void reg32_rw_test(WORD addr, WORD wdata, WORD exp_rdata);
void reg16_rw_test(WORD addr, HALF wdata, HALF exp_rdata);
void reg8_rw_test(WORD addr, BYTE wdata, BYTE exp_rdata);

//2}}}

// #####   FUNCTION DECLARATIONS  - NON COMMON API ############################################ 

//----------------------------------------------------------------------
//  Tortola/Argon project specific functions
//----------------------------------------------------------------------

//{{{2

// ===  FUNCTION  ======================================================================
// 
//         Name:  release_spba
// 
//  Description:  release spba from being mastered by ARM
// 
// - PARAMETER -------------------------------------------------------------------------
//      Mode   Type             Name            Description
// -------------------------------------------------------------------------------------
//        in:  void
//    in-out:  
//       out:  
//    return:  void
// -------------------------------------------------------------------------------------
//    Author:  
//   Created:  09/07/04 17:34:57 IDT
//  Revision:  none
// =====================================================================================

void release_spba(void);
//2}}}

//1}}}

#endif //FUNCTIONS_H


