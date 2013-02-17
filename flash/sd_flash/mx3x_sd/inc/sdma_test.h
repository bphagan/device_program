#ifndef		CHIP_LEVEL_VERIFICATION_SDMA_RELATED
#define		CHIP_LEVEL_VERIFICATION_SDMA_RELATED

	#include "functions.h"
	#define	SDMA_CTXT_BASE_ADDR	0x800
	#define	SDMA_CTXT_SIZE		32
	#define SDMA_SCRIPT_BASE_ADDR	0x1800
	#define	SDMA_RAM_BASE_ADDR	0xB6F10000
	#define	SDMA_GREG_OFFSET	2

// ***** VARIABLES DECLARATIONS ***** //
typedef struct dummyCCB {
  unsigned long baseBDptr;
  unsigned long currentBDptr;
  unsigned long status;
  unsigned long channelDescriptor;
} channelControlBlock;

void sdma_irq_handler(void);
void sdma_wait_for_irq(void);
void sdma_init(void);
void setup_per_channel(
	unsigned long channel, 
	WORD script_addr, 
	WORD script_size,
	WORD event,	// event to trigger
	WORD peraddr,	// peripheral address
	WORD burst_len	// burst length
);
void start_per_channel(
	unsigned long channel,
	WORD	mem_addr,
	WORD	dat_cnt		// not support transfer size exceeding 65536 bytes yet
) ;
void stop_channel(unsigned long channel);


//	#undef	SDMA_CTXT_BASE_ADDR
//	#undef	SDMA_CTXT_SIZE
//	#undef	SDMA_SCRIPT_BASE_ADDR
//	#undef	SDMA_RAM_BASE_ADDR
//	#undef	SDMA_GREG_OFFSET
#endif

