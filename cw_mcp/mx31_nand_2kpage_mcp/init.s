        AREA    Init, CODE, READONLY

; --- Standard definitions of mode bits and interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UNDEF      EQU     0x1B
Mode_SYS        EQU     0x1F ; available on ARM Arch 4 and later

I_Bit           EQU     0x80 ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40 ; when F bit is set, FIQ is disabled

; --- Amount of memory (in bytes) allocated for stacks

Len_FIQ_Stack    EQU     1024
Len_IRQ_Stack    EQU     1024
Len_ABT_Stack    EQU     1024
Len_UND_Stack    EQU     1024
Len_SVC_Stack    EQU     1024
Len_USR_Stack    EQU     1024


; Add lengths >0 for FIQ_Stack, ABT_Stack, UND_Stack if you need them.
; Offsets will be loaded as immediate values.
; Offsets must be 8 byte aligned.

Offset_FIQ_Stack         EQU     0
Offset_IRQ_Stack         EQU     Offset_FIQ_Stack + Len_FIQ_Stack
Offset_ABT_Stack         EQU     Offset_IRQ_Stack + Len_IRQ_Stack
Offset_UND_Stack         EQU     Offset_ABT_Stack + Len_ABT_Stack
Offset_SVC_Stack         EQU     Offset_UND_Stack + Len_UND_Stack
Offset_USR_Stack         EQU     Offset_SVC_Stack + Len_SVC_Stack

        ENTRY

        EXPORT  Reset_Handler

Reset_Handler

; --- Initialize stack pointer registers

; Enter each mode in turn and set up the stack pointer

       IMPORT  top_of_stacks       ; defined in stack.s and located by scatter file
       LDR     r0, =top_of_stacks

       MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit ; No interrupts
       SUB     sp, r0, #Offset_FIQ_Stack

       MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit ; No interrupts
       SUB     sp, r0, #Offset_IRQ_Stack

       MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit ; No interrupts
       SUB     sp, r0, #Offset_ABT_Stack

;       MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit ; No interrupts
;       SUB     sp, r0, #Offset_UND_Stack

       MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit ; No interrupts
       SUB     sp, r0, #Offset_SVC_Stack

; --- Initialize memory system

; --- Initialize critical IO devices

; --- Now change to User mode and set up User mode stack, if needed
;        MSR     CPSR_c, #Mode_USR:OR:I_Bit:OR:F_Bit ; No interrupts
;        SUB     sp, r0, #Offset_USR_Stack

; AHB-Lite IP Interface
;		LDR		r2, =0x10000000
;		LDR		r1, =0x00040304 		
;		STR		r1, [r2]
;		LDR		r2, =0x10020000
;		LDR		r1, =0x00000000 
;		STR		r1, [r2] 
;		LDR		r2, =0x10000004
;		LDR		r1, =0xFFFBFCFB
;		STR		r1, [r2]
;		LDR		r2, =0x10020004
;		LDR		r1, =0xFFFFFFFF 
;		STR		r1, [r2]
;		LDR		r2, =0x10027020 
;		LDR		r1, =0x31084003 
;		STR		r1, [r2]

        IMPORT  __main

; --- Now enter the C code
        B       __main   ; note use B not BL, because an application will never return this way

        END
