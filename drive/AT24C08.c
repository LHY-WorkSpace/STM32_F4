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

/*
	//分页的话会覆盖的问题！！！！待解决
	uchar i=0;
	Start_IIC();
	IIC_SenddByte(dev_addr|0x00);
	IIC_Wait_Ack_OK();
	IIC_SenddByte((Data_addr>>8)&0xFF);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr&0xFF);
	IIC_Wait_Ack_OK();
	for(i=0;i<length;i++)
	{
		IIC_SenddByte(*data);
		if(IIC_Wait_Ack_OK()==1)
		{
			Stop_IIC();
			return;
		}
		data++;
	}
 	Stop_IIC();
	delay_ms(2);

*/












