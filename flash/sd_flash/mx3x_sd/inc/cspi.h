#ifndef _CSPI_H
#define _CSPI_H

#include "Common.h"
#include "tortola_memory_map_defines.h"
#include "config_pad_mode.h"
#include "wait.h"


void CSPI2_PORT_init(void);
void CSPI2_init(void);
void SPI_write(U32 data);
U32 SPI_read(void);



#endif
