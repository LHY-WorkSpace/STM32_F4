#include "IncludeFile.h"


//PC8-----------DATA//


//************************// 
//  ��������: DHT11 IO ��ʼ������
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��ʼ������������ͷ�����
//  DHT11 �� DS18B20 ���Թ���һ������
//************************//  
void DHT11_GPIO_Init()
{
	GPIO_InitTypeDef GPIOB_Initstruc;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIOB_Initstruc.GPIO_Pin = GPIO_Pin_8;                       
	GPIOB_Initstruc.GPIO_Mode = GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType = GPIO_OType_OD;
	GPIOB_Initstruc.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIOB_Initstruc);
	DHT11_HIGH;	  //��ʼ����Ϻ������ͷ�����
}


static u8 DHT11_Init(void)
{
	u8 i=0;

	DHT11_HIGH;
	Delay_ms(5);
	DHT11_LOW;	            //��������20ms,���Ϳ�ʼ�ź�
	Delay_ms(20);
	DHT11_HIGH;	            //����40us.�ȴ�Ӧ��
	Delay_us(40);

	if(DHT11_IO_STATE == HIGH)
	{
		return FALSE;
	}
     
	while( (DHT11_IO_STATE == LOW )&&( i < 50) )
	{
		i++;
		Delay_us(2);
	}

	i=0;

	while( (DHT11_IO_STATE == HIGH )&&( i < 50) )
	{
		i++;
		Delay_us(2);
	}

	return TRUE;
}


static u8 DHT11_Read_Byte(void)
{
	u8 Byte_Data=0,i,k;
	
	for(i=0;i<8;i++)
	{
		k=0;
		while( (DHT11_IO_STATE == LOW )&&( k < 50) )
		{
			k++;
			Delay_us(2);
		}
		Delay_us(30);

		Byte_Data <<= 1;
		if(DHT11_IO_STATE==HIGH)
		{
			Byte_Data |= 1;
			k=0;
			while( (DHT11_IO_STATE == HIGH )&&( k < 50) )
			{
				k++;
				Delay_us(2);
			}
		}
		else
		{
			Byte_Data |= 0;
		}

	}

	return Byte_Data;
}

//***************************************************//
//  ��������: ��ȡ�¶Ⱥ�ʪ������
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��ȡ��ʪ�ȼ���������1s�����ֽ�Ϊ���������ֽ�ΪС��
//  0x1234 = 0x12 . 0x34  = 18.52 
//***************************************************//
u8 DHT11_Read_Data(DHT11_Data_t *DHT11_Data)
{
	u8 CheckSum;

	if ( DHT11_Init() == FALSE)
	{
		DHT11_Data->Tempure.B08[1] = 0;
		DHT11_Data->Tempure.B08[0] = 0;
		DHT11_Data->Humidity.B08[1] = 0;
		DHT11_Data->Humidity.B08[0] = 0;	
		return FALSE;
	}

	DHT11_Data->Humidity.B08[1] = DHT11_Read_Byte();
	DHT11_Data->Humidity.B08[0] = DHT11_Read_Byte();
	DHT11_Data->Tempure.B08[1] =  DHT11_Read_Byte();
	DHT11_Data->Tempure.B08[0] =  DHT11_Read_Byte();
	DHT11_Data->CheckSum =	DHT11_Read_Byte(); 

	CheckSum =  DHT11_Data->Tempure.B08[0];
	CheckSum += DHT11_Data->Tempure.B08[1];
	CheckSum += DHT11_Data->Humidity.B08[0];
	CheckSum += DHT11_Data->Humidity.B08[1];

	if( CheckSum != DHT11_Data->CheckSum)
	{
		DHT11_Data->Tempure.B08[1] = 0;
		DHT11_Data->Tempure.B08[0] = 0;
		DHT11_Data->Humidity.B08[1] = 0;
		DHT11_Data->Humidity.B08[0] = 0;	
		return DATA_ERR;
	}

	return TRUE;
}
 














