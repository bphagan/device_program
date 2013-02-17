
#include "cspi.h"
#include "config_pad_mode.h"

void CSPI2_PORT_init()                          //cspi2 port initial
{

	config_pad_mode(CSPI2_MOSI,func_out,func_in);
	config_pad_mode(CSPI2_MISO,func_out,func_in);
	config_pad_mode(CSPI2_SS0,func_out,func_in);
//	config_pad_mode(CSPI2_SS1,func_out,func_in);
	config_pad_mode(CSPI2_SS2,func_out,func_in);
	config_pad_mode(CSPI2_SCLK,func_out,func_in);
//	config_pad_mode(CSPI2_SPI_RDY,func_out,func_in);

}

void CSPI2_init()
{


//	*(P_U32)CSPI2_CONREG=0x000717b3;          //cspi_ss0, 24bit data, ss high activity,
	*(P_U32)CSPI2_CONREG=0x02071fc3;          //cspi_ss2, 32bit data, ss high activity
//	*(P_U32)CSPI2_CONREG=0x00071fc3;          //cspi_ss0, 32bit data, ss high activity
}

void SPI_write(U32 data)
{
	*(P_U32)CSPI2_TXDATA=data;
	*(P_U32)CSPI2_CONREG|=0x04;
	while((*(P_U32)CSPI2_CONREG&0x04)==0x04)
	{
		wait(1);
	}
//	printf("tra,%d\n",i++);
//	printf("transfer ok\n");
}

U32 SPI_read()
{
	U32 data;
/*	*(P_U32)CSPI2_CONREG|=0x04;
	while((*(P_U32)CSPI2_CONREG&0x04)==0x04)
	{
		wait(5);
		printf("tra\n");
	}*/
	data=*(P_U32)CSPI2_RXDATA;
//	printf("data is 0x%x.\n",data);
	return data;
}












