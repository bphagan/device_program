
#include "Atlas_spi.h"



void Atlas_spi_init()
{

	CSPI2_PORT_init();
	CSPI2_init();

} 


U32 Atlas_read_reg(U32 reg_num) 
{
	U32 read_data=0;
	U32 read_inst;

	// building the reading word
	read_inst=0x00000000;
	read_inst= (read_inst | (reg_num << 25));
	
	// reading from atlas
 	SPI_write(read_inst);	  
	read_data=SPI_read();
	
	return read_data;
}

void Atlas_write_reg(U32 reg_num, U32 data) 
{
	U32 read_data=0;
	U32 read_inst;

	// the data is only 24 bits (ATLAS)
	data=0x00FFFFFF & data;
	

	// building the reading word
	read_inst=0x00000000;
	read_inst= (read_inst | (reg_num << 25));
	read_inst=(read_inst | 0x80000000);
	read_inst=(read_inst | data);

	// writing to atlas
	SPI_write(read_inst);
	read_data=SPI_read();//flush the rec FIFO
}



