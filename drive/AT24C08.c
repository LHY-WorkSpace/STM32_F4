#include "stm32f4xx.h"
#include "i2c.h"
#include "AT24C08.h"
#include "delay.h"

/*

This is for AT24C08

  MSB                                  LSB

   x    x    x    x   |   x    x   x    x
	 1    0    1    0   |   A2   P1  P0   W/R
	 
	 
	 A2:  devices address, depend on pin A0
	 
	 P1 P0:      00        block  0
	             01        block  1
							 10        block  2
							 11        block  3
							
							
	
	 w/r:      0-----write
	           1-----read

  


连续写入时 注意延时 每个字节写入需要时间

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





/*=============================================================================================

Function:   ReadAT24C08_Byte

parmart :         block:    AT24C08_BLOCK0_ADDRESS            every block =256byte= 16 page *16 byte   
                            AT24C08_BLOCK1_ADDRESS
														AT24C08_BLOCK2_ADDRESS
														AT24C08_BLOCK3_ADDRESS

                  addr:     0x00~0xff (in one bolck)


return  :   get read data(1 byte=8 bit)
      
===============================================================================================*/

uchar AT24C08Read_Byte(uchar block,uchar addr)
{
	
    return IIC_Read_Byte(block,addr);
}




void AT24C08Write_Byte(uchar block,uchar addr,uchar data)
{
	
IIC_Write_Byte(block,addr,data);
	

}


void AT24C08Read_NByte(uchar block,uchar addr,uchar n,uchar *data)
{
	
	IIC_Read_NByte(block,addr,n,data);
		

}



void AT24C08Write_NByte(uchar block,uchar addr,uchar n,uchar *data)
{
	
IIC_Write_NByte(block,addr,n,data);

}

















