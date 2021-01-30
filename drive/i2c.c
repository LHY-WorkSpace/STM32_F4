#include "stm32f4xx.h"
#include "i2c.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int 


/*
IIC_SCL     GPIO_Pin_6                                       
IIC_SDA     GPIO_Pin_7
*/

void IIC_Init()
{

	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(PORT_AHB,ENABLE);
	
	GPIO_Initstructure.GPIO_Pin=IIC_SCL|IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);
	
}


static void Pin_in2out(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);

}


static void Pin_out2in(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;              
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);

}


static void Start_IIC(void)
{
		Pin_in2out();
		IIC_SDA_HIGH;
		IIC_SCL_HIGH;
	 	delay_us(2);
		IIC_SDA_LOW;
	 	delay_us(2);
	  	IIC_SCL_LOW;
		delay_us(2);

}


static void Stop_IIC(void)
{

	Pin_in2out();
	IIC_SCL_LOW;
	delay_us(2);
	IIC_SDA_LOW;
	delay_us(2);
	IIC_SCL_HIGH;
	delay_us(2);
	IIC_SDA_HIGH;
	delay_us(2);
	


}


static void IIC_SenddByte(uchar data)
{

	uchar i=0;
	Pin_in2out();
	IIC_SCL_LOW;	                      //À­µÍSCL

	for(i=0;i<8;i++)
	{
		IIC_SCL_LOW;
		delay_us(2);
			if(data&0x80)	
			{
			IIC_SDA_HIGH;
			}
			else
			{
			IIC_SDA_LOW;
			}
		   data<<=1;
			delay_us(2);
			IIC_SCL_HIGH;
			delay_us(2);
	}
    IIC_SCL_LOW;                     
    delay_us(2);

}


static uchar IIC_GetByte(void)
{
	uchar data=0;
	uchar i=0;

	Pin_out2in();	
	IIC_SDA_HIGH;
	delay_us(2);
	for(i=0;i<8;i++)
	{		
			data<<=1;
			IIC_SCL_LOW;
			delay_us(2); 		
			IIC_SCL_HIGH;	
			delay_us(2);
			if(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)	
			{
      			data|=0x01;
			}

	}
 	IIC_SCL_LOW;	
	delay_us(2);

  return data;
}


static void IIC_Send_Ack(void)
{
	
	IIC_SCL_LOW;
	Pin_in2out();
	delay_us(2);	
	IIC_SDA_LOW;
	delay_us(2);
	IIC_SCL_HIGH;
	delay_us(2);
	IIC_SCL_LOW;
	delay_us(2);
}



static void IIC_Send_NAck(void)
{

	IIC_SCL_LOW;
	Pin_in2out();
	delay_us(2);
	IIC_SDA_HIGH;
	delay_us(2);
	IIC_SCL_HIGH;
	delay_us(2);
	IIC_SCL_LOW;
	delay_us(2);

}


static uchar IIC_Wait_Ack_OK(void)
{
	uchar i=0;

	Pin_out2in();	
	IIC_SDA_HIGH;  
	delay_us(2);
	IIC_SCL_HIGH; 
	delay_us(2);
                                       
		while(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)
		{
				i++;
				if(i>250)
				{
					Stop_IIC();
					return 1;
				}
				
		}
				
	 IIC_SCL_LOW;	
	 delay_us(2);	

	return 0;
}



uchar IIC_Read_Byte(uchar Dev_addr,uchar Data_addr)
{
	uchar DATA=0;
	
	Start_IIC();
	IIC_SenddByte(Dev_addr|0X00);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr);
	IIC_Wait_Ack_OK();
	
	Start_IIC();
	IIC_SenddByte((Dev_addr|0X01));	
    IIC_Wait_Ack_OK();
	DATA=IIC_GetByte();
	IIC_Send_NAck();
	Stop_IIC();
	
	return DATA;
}

void IIC_Write_Byte(uchar Dev_addr,uchar Data_addr,uchar data)
{

	Start_IIC();
	IIC_SenddByte(Dev_addr);        
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(data);	
	IIC_Wait_Ack_OK();
	Stop_IIC();
	delay_ms(5);    
	
}


void IIC_Read_NBytes(uchar Dev_addr,uchar Data_addr,uchar length,uchar *data)
{
	 	 uchar i=0;
    	Start_IIC();
		IIC_SenddByte(Dev_addr);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(Data_addr);
		IIC_Wait_Ack_OK();
	
   		Start_IIC();
		IIC_SenddByte(Dev_addr|0X01);	
		IIC_Wait_Ack_OK();
	
		for(i=0;i<length;i++)
		{
			if(i<(length-1))
			{
				*data=IIC_GetByte();
				IIC_Send_Ack();
			}
			else
			{
				*data=IIC_GetByte();
				IIC_Send_NAck();	
			}
			data++;	
		}
	Stop_IIC();
}

void IIC_Write_NBytes(uchar Dev_addr,uchar Data_addr,uchar length,uchar *data)
{
	uchar i=0;
	
	Start_IIC();
	IIC_SenddByte(Dev_addr|0x00);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr);
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

}




































