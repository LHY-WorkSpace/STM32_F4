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



date :   19/10/18~19/10/19
note : SDA,SCL�������ŵ�ƽ�ĺ���ˡ�����������
     
ע1���ı�io�������״̬ǰ��������SCL ����ֹSCL�ߵ�ƽ�ڼ���ioģʽ�仯������������ΪΪstart��stop�ź�
ע2��start ��  stop ����������
ע3����ƽת�������п���ʱ�䣬		IIC_SCL_HIGH;
		                            IIC_SDA_HIGH;
																���󣺵�ƽ�任���ڽӽ��������źŴ���(SCL=1��Ҫʱ��.SDA�ȶ�Ҳ��Ҫʱ�䣬���Ա仯�������ʱ�ȴ��ȶ�)


	                             	IIC_SCL_HIGH;
	                              delay_us(2);
		                            IIC_SDA_HIGH;
																��ȷ��(SCL=1��Ҫʱ��.SDA�ȶ�Ҳ��Ҫʱ�䣬���Ա仯�������ʱ�ȴ��ȶ�)

*/







#if (IIC_SOFTWARE ==1)


/*==============================================================================================

Function:   software IIC init
parmart :   NULL
return  :   NULL
      

===============================================================================================*/

void IIC_Init()
{

	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(PORT_AHB,ENABLE);
	
	GPIO_Initstructure.GPIO_Pin=IIC_SCL|IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                //IIC Must be GPIO_OType_OD
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);
	


	
	

}

/*=============================================================================================

Function:   turn IIC_SDA IO Mode   IN->OUT      
parmart :   NULL
return  :   NULL
      

===============================================================================================*/

static void Pin_in2out(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                //IIC Must be GPIO_OType_OD
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);

}

/*=============================================================================================

Function:   turn IIC_SDA IO Mode   OUT->IN      
parmart :   NULL
return  :   NULL
      

===============================================================================================*/

static void Pin_out2in(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                //IIC Must be GPIO_OType_OD
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);


}


/*=============================================================================================

Function:   Start_IIC bus
parmart :   NULL
return  :   NULL
      
===============================================================================================*/

void Start_IIC(void)
{
		IIC_SCL_HIGH;
	  delay_us(2);
		IIC_SDA_HIGH;
		delay_us(2);
		IIC_SDA_LOW;
	  delay_us(2);
	  IIC_SCL_LOW;
		delay_us(2);/////////////////////////////////////////

}


/*=============================================================================================

Function:   Stop_IIC bus
parmart :   NULL
return  :   NULL
      
===============================================================================================*/

void Stop_IIC(void)
{

	IIC_SCL_LOW;
	delay_us(2);
	
	IIC_SDA_LOW;
	delay_us(2);
	
	IIC_SCL_HIGH;

	delay_us(2);
	
	IIC_SDA_HIGH;
	delay_us(2);
	


}



/*=============================================================================================

Function:   IIC Send 1 Byte Data            From: MSB-->LSB(for AT24CXX)
parmart :   8 bit data     /    1 Byte
return  :   NULL
      
===============================================================================================*/


void IIC_SenddByte(uchar data)
{
// 	printf("%x\r\n",data);
	uchar i=0;
	IIC_SCL_LOW;	                      //����SCL
//	Pin_in2out();                       //IO : IN->OUT

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
     IIC_SCL_LOW;                       //����SCL ��ֹSDA�仯�����źŴ���
     delay_us(2);

}


uchar IIC_GetByte(void)
{
	uchar data=0;
	uchar i=0;
	
	
	
	IIC_SCL_LOW;
	delay_us(2);
	Pin_out2in();

	for(i=0;i<8;i++)
	{		
			data<<=1;

		
			delay_us(2); 		
			IIC_SCL_HIGH;	
			delay_us(2);
			if(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)	
			{
      data|=0x01;
			}
			IIC_SCL_LOW;


	}
  IIC_SCL_LOW;
	Pin_in2out();	
	delay_us(2);

	
	
	
	
  return data;
}

/*=============================================================================================

Function:   Send_Ack          
parmart :   NULL
return  :   NULL
						
      
===============================================================================================*/
void IIC_Send_Ack(void)
{
	
	IIC_SCL_LOW;
	delay_us(2);	
	IIC_SDA_LOW;
	delay_us(2);
	IIC_SCL_HIGH;
	delay_us(2);
	IIC_SCL_LOW;
	delay_us(2);
}


/*=============================================================================================

Function:   Send_NAck          
parmart :   NULL
return  :   NULL
						
      
===============================================================================================*/
void IIC_Send_NAck(void)
{

	IIC_SCL_LOW;
	delay_us(2);
	IIC_SDA_HIGH;
	delay_us(2);
	IIC_SCL_HIGH;
	delay_us(2);
	IIC_SCL_LOW;
	delay_us(2);

}



/*=============================================================================================

Function:   Wait_Ack_OK          
parmart :   NULL
return  :   0-----------ACK-OK
						1-----------ACK-FALSE
      
===============================================================================================*/
uchar IIC_Wait_Ack_OK(void)
{
	
	uchar i=0;
	IIC_SCL_LOW;	                                             //�ȴ�SDA�仯
	delay_us(2);
	IIC_SDA_HIGH;                                              //�ͷ�SDA�ȴ�����		
  Pin_out2in();	
	delay_us(2);	                                             //SDA�仯
	IIC_SCL_HIGH;                                              //����SCL ��ȡSDA
	delay_us(2);
		while(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)
		{
				i++;
				if(i>250)
				{
					Pin_in2out();
					Stop_IIC();
					//printf("ACK_ERROR\r\n");
					return 1;
				}
				
		
		}
				
 //  printf("ACK-----OK\r\n");	
	 IIC_SCL_LOW;	
	 delay_us(2);		
   Pin_in2out();	
	 delay_us(2);

	return 0;
	
}



uchar IIC_Read_Byte(uchar ADDR,uchar REG)
{
	
		uchar DATA=0;
	
		Start_IIC();
	  IIC_SenddByte(ADDR|0X00);
    IIC_Wait_Ack_OK();
		IIC_SenddByte(REG);
	  IIC_Wait_Ack_OK();
	
		Start_IIC();
	  IIC_SenddByte((ADDR|0X01));	
    IIC_Wait_Ack_OK();
		DATA=IIC_GetByte();
	  IIC_Send_NAck();
	  Stop_IIC();
	
	return DATA;
}

void IIC_Write_Byte(uchar ADDR,uchar REG,uchar data)
{
	

		Start_IIC();
	  IIC_SenddByte(ADDR|0X00);        
    IIC_Wait_Ack_OK();
		IIC_SenddByte(REG);
	  IIC_Wait_Ack_OK();
	  IIC_SenddByte(data);	
		IIC_Wait_Ack_OK();
	  Stop_IIC();
	  delay_ms(2);                                   //д����Ҫʱ��
	
}



void IIC_Read_NByte(uchar dev_addr,uchar reg,uchar length,uchar *data)
{
	  uchar i=0;
    Start_IIC();
		IIC_SenddByte(dev_addr|0X00);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(reg);
		IIC_Wait_Ack_OK();
	
    Start_IIC();
		IIC_SenddByte(dev_addr|0X01);	
		IIC_Wait_Ack_OK();
	
		for(i=0;i<length;i++)
			{
				
				if(i<(length-1))
				{
				*data=IIC_GetByte();
				 IIC_Send_Ack();
				}else
				{
				*data=IIC_GetByte();
				 IIC_Send_NAck();	
				}
				
				
				data++;	
			}
	Stop_IIC();
}

void IIC_Write_NByte(uchar dev_addr,uchar reg,uchar length,uchar *data)
{
	uchar i=0;
	
	Start_IIC();
	IIC_SenddByte(dev_addr|0x00);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(reg);
	IIC_Wait_Ack_OK();
	for(i=0;i<length;i++)
	{
	IIC_SenddByte(*data);
	IIC_Wait_Ack_OK();
  data++;
	}
  Stop_IIC();
	delay_ms(2);

}




#else

void IIC_Init()
{
	
	GPIO_InitTypeDef GPIO_Initstructure;
	I2C_InitTypeDef i2c_struc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	
	GPIO_Initstructure.GPIO_Pin=IIC_SCL|IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_I2C1);	
	
	
  i2c_struc.I2C_Mode=I2C_Mode_I2C;
	i2c_struc.I2C_DutyCycle=I2C_DutyCycle_2;
	i2c_struc.I2C_OwnAddress1=0x3FF;                                           //STM32�����ַ�� ��I2C_AcknowledgedAddress���õĳ���һ��
	i2c_struc.I2C_Ack=I2C_Ack_Enable;
	i2c_struc.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_10bit;           //���� I2C_OwnAddress1 �ĳ���
	i2c_struc.I2C_ClockSpeed=400000;                                           //I2C�ٶ�-----
  
  I2C_Init(I2C1,&i2c_struc);	
	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C1,ENABLE);

}



/*=============================================================================================

Function:   Start_IIC bus
parmart :   NULL
return  :   NULL
      
===============================================================================================*/

void Start_IIC(void)
{


}


/*=============================================================================================

Function:   Stop_IIC bus
parmart :   NULL
return  :   NULL
      
===============================================================================================*/

void Stop_IIC(void)
{

}



/*=============================================================================================

Function:   IIC Send 1 Byte Data            From: LSB-->MSB
parmart :   8 bit data     /    1 Byte
return  :   NULL
      
===============================================================================================*/

void IIC_SenddByte(uchar data)
{
 


}




uchar IIC_GetByte(void)
{

 
}

/*=============================================================================================

Function:   Send_Ack          
parmart :   NULL
return  :   NULL
						
      
===============================================================================================*/
void IIC_Send_Ack(void)
{
	


}


/*=============================================================================================

Function:   Send_NAck          
parmart :   NULL
return  :   NULL
						
      
===============================================================================================*/
void IIC_Send_NAck(void)
{



}



/*=============================================================================================

Function:   Wait_Ack_OK          
parmart :   NULL
return  :   0-----------ACK-OK
						1-----------ACK-FALSE
      
===============================================================================================*/
uchar IIC_Wait_Ack_OK(void)
{
		
	
}







#endif









































