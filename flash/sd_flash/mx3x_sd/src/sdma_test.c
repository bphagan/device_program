#include "sdma_test.h"

channelControlBlock CCB[32];
unsigned long BDCh0[3*33];
unsigned long CTXT_CH_PTR[SDMA_CTXT_SIZE];
WORD sdma_irq_flag = 0;

// ***** FUNCTIONS DECLARATIONS ***** //
//Interrupt Handler routine for SDMA
void sdma_irq_handler(void);
void sdma_wait_for_irq(void);

// ***** FUNCTIONS IMPLEMENTATIONS ***** //
void sdma_init(void) {
	int i;

	reg32_write(SDMA_RESET, 0x1);		// Reset SDMA

	for (i = 0; i < SDMA_CTXT_SIZE; i++)
		CTXT_CH_PTR[i] = 0;

	// MCU channel 0 pointer
	reg32_write(SDMA_COPTR, (unsigned long)&CCB);
	
	// STATIC CONTEXT SWITCHING, set AHB/core clock ratio to 1 
	reg32_write(SDMA_CTXSW_MODE, 0x0);
	
	// CHNPRI_0: channel 0 is of pty 7
	reg32_write(SDMA_CHNPRI_0,0x7);
	//  EO for channel 0
	reg32_write(SDMA_EVTOVR,0x1);	

	// Set bit for Scratch RAM
	reg32_write(SDMA_CHN0ADDR, reg32_read(SDMA_CHN0ADDR) | 0x4000);

	// **** CHANNEL CONTROL BLOCK *** //
	// connect buffer descriptors with channel control block
	CCB[0].baseBDptr = (unsigned long)&BDCh0;
	CCB[0].currentBDptr = (unsigned long)&BDCh0;

	// **** BUFFER DESCRIPTOR *** //
	// setup buffer descriptors for channel 0
	BDCh0[1] = (unsigned long)&CTXT_CH_PTR;

	// Enable SDMA interrupt 34 in AVIC Interrupt Enable Number Reg
	mem32_write(AVIC_INTENNUM, 34);

	// Set priority in AVIC Interrupt Enable Priority reg: 15
	mem32_write(AVIC_NIPRIORITY4, 0xF00);
	
	// Register address of ISR in vector table
	CAPTURE_INTERRUPT(SDMA_INT_ROUTINE, (unsigned long)sdma_irq_handler);
}

void sdma_irq_handler(void) {
	sdma_irq_flag = reg32_read(SDMA_INTR);
	reg32_write(SDMA_INTR, sdma_irq_flag);		// clean up SDMA interrupt
}

void sdma_wait_for_irq(void) {
	int i;
	for (i = 0; i < 100; i++)
		;
/*
	while (0 == sdma_irq_flag) ;
	sdma_irq_flag = 0;
*/
}

#define	CHECK_DOWNLOAD	0
void setup_per_channel(
	unsigned long channel, 
	WORD script_addr, 
	WORD script_size,
	WORD event,	// event to trigger
	WORD peraddr,	// peripheral address
	WORD burst_len	// burst length
) {
#if	CHECK_DOWNLOAD
	BDCh0[1] = (WORD)&CTXT_CH_PTR;	
#endif
	// Prepare to download context
	BDCh0[0] = 0x01850020;  //SET DM - Extended - CONT - DONE
	BDCh0[2] = SDMA_CTXT_BASE_ADDR + channel * SDMA_CTXT_SIZE;

	// Prepare to download script file
//	BDCh0[3] = 0x048B0000 | script_size;  //SET PM - Extended - INT - WRAP - DONE
	BDCh0[3] = 0x04830000 | script_size;  //SET PM - Extended - WRAP - DONE
	BDCh0[4] = SDMA_RAM_BASE_ADDR + 2 * (script_addr - SDMA_SCRIPT_BASE_ADDR);
	BDCh0[5] = script_addr;

	CTXT_CH_PTR[0] = script_addr;
	CTXT_CH_PTR[SDMA_GREG_OFFSET + 1] = (1 << event);	// set event mask
	CTXT_CH_PTR[SDMA_GREG_OFFSET + 6] = peraddr;
	CTXT_CH_PTR[SDMA_GREG_OFFSET + 7] = burst_len;		// wml is burst length
	
	// Now start channel 0 to download context and script
	reg32_write(SDMA_START, 0x1);
  {
	int i;
#if	CHECK_DOWNLOAD
	WORD ctxt[60];
	WORD pgm[60];
	for (i = 0; i < 60; i++)
		ctxt[i] = 0, pgm[i] = 0;
	BDCh0[0] = 0x02850020;  //GET CTXT - Extended - CONT - DONE
	BDCh0[1] = (WORD)&ctxt;
	BDCh0[2] = SDMA_CTXT_BASE_ADDR + channel * SDMA_CTXT_SIZE;
//	BDCh0[3] = 0x088B0000 | script_size;  //GET PM - Extended - INT - WRAP - DONE
	BDCh0[3] = 0x08830000 | script_size;  //GET PM - Extended - WRAP - DONE
	BDCh0[4] = (WORD)&pgm;
	BDCh0[5] = script_addr;
	reg32_write(SDMA_START, 0x1);
	for (i = 0; i < 80; i++)
		;
	for (i = 0; i < 32; i++)
		info_trigger(i, ctxt[i], pgm[i]);
		
#else
	for (i = 0; i < 50; i++)
		;
#endif
  }	
	reg32_write(SDMA_CHNPRI_0 + 4 * channel, 0x3);		// of priority 3
	reg32_write(SDMA_CHENBL_0 + 4 * event, 1 << channel);	// enable event sensitive reg bit
	CCB[channel].baseBDptr = (unsigned long)&(BDCh0[3+3*channel]);
	CCB[channel].currentBDptr = (unsigned long)&(BDCh0[3+3*channel]);
}
#undef	CHECK_DOWNLOAD

void start_per_channel(
	unsigned long channel,
	WORD	mem_addr,
	WORD	dat_cnt		// not support transfer size exceeding 65536 bytes yet
) {
//	BDCh0[3 + 3*channel] = 0xB0000 | (dat_cnt & 0xFFFF); //	- INT - WRAP - DONE
	BDCh0[3 + 3*channel] = 0x30000 | (dat_cnt & 0xFFFF); //	- WRAP - DONE
	BDCh0[4 + 3*channel] = mem_addr;
	 
	do {
		reg32_write(SDMA_START, 1 << channel);
	} while (0 == (reg32_read(SDMA_START) & (1 << channel)));
}

void stop_channel(unsigned long channel) {
	do {
		reg32_write(SDMA_STOP, 1 << channel);
	} while (reg32_read(SDMA_STOP) & (1 << channel));
}

