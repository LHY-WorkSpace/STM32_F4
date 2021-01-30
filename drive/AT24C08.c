#include "stm32f4xx.h"
#include "i2c.h"
#include "AT24C08.h"
#include "delay.h"

/*
This is for AT24C08
  MSB                                  LSB
   x    x    x    x   |   x    x   x    x
   1    0    1    0   |   A2   P1  P0   W/R
*/



/*=============================================================================================

Function:   AT24C08_init
parmart :   NULL
return  :   NULL
      
===============================================================================================*/
void AT24C08_init(void)
{
	IIC_Init();
}





uchar AT24C08Read_Byte(uchar dev_addr,uchar Data_addr)
{
    return IIC_Read_Byte(dev_addr,Data_addr);
}






void AT24C08Write_Byte(uchar dev_addr,uchar Data_addr,uchar data)
{
	IIC_Write_Byte(dev_addr,Data_addr,data);
}







void AT24C08Read_NBytes(uchar dev_addr,uchar Data_addr,uchar length,uchar *data)
{
	uint i;
	for(i=0;i<length;i++)
	{
		data[i]=IIC_Read_Byte(dev_addr,Data_addr+i);
	}
		
}



void AT24C08Write_NBytes(uchar dev_addr,uchar Data_addr,uchar length,uchar *data)
{
	uint i;
	for(i=0;i<length;i++)
	{
		IIC_Write_Byte(dev_addr,Data_addr+i,data[i]);
	}

}

















