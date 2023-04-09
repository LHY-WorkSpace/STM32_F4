
#include"IncludeFile.h"


 //PC8 --------DATE



DS18B20_Info_t DS18B20_Info;


#if( DELAY_TYPE == USE_TIMER  ) 
static void DS18B20_Delay_us(u16 nus)
{
	Delay_us(nus);
}
#else
static void DS18B20_Delay_us(u16 nus)
{
	 vu16 i,k;
	for(k=0; k<nus; k++)
	{
		for(i=0; i<30; i++)
		{
			__NOP();
			i++;
		}
	}
	i += k;

}
#endif


//************************// 
//  ��������: DS18B20 IO ��ʼ������
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��ʼ������������ͷ�����
//  DHT11 �� DS18B20 ���Թ���һ������
//************************//  
void DS18B20_GPIO_Init()
{
	GPIO_InitTypeDef GPIOB_Initstruc;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIOB_Initstruc.GPIO_Pin = GPIO_Pin_8;                       
	GPIOB_Initstruc.GPIO_Mode = GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType = GPIO_OType_OD;
	GPIOB_Initstruc.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIOB_Initstruc);
	DS18B20_HIGH; //��ʼ����Ϻ������ͷ�����
}


//***************************************************//
//  ��������: DS18B20 дһ���ֽ�����
//  
//  ����: Ҫд������
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
static void DS18B20_Write_Byte(u8 data)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		DS18B20_LOW; 
		DS18B20_Delay_us(15);		
		if((0x01&data)==0)
		{		
			DS18B20_LOW; 
		}
		else
		{		
			DS18B20_HIGH; 
		}
		DS18B20_Delay_us(60);
		DS18B20_HIGH; 
		DS18B20_Delay_us(10);
		data >>= 1;
	}
}
	
//***************************************************//
//  ��������: DS18B20 ��һ���ֽ�����
//  
//  ����: ��
//  
//  ����ֵ: ���ص�����
//  
//  ˵��: ��
//  
//***************************************************//
static u8 DS18B20_Read_Byte()
{
	u8 i,k;
	u8	data=0;
	u8  temp=0;		
	for(i=0;i<8;i++)
	{
		DS18B20_LOW;
		DS18B20_Delay_us(14);
		DS18B20_HIGH;//�ͷ�����

		for(k=0;k<3;k++)//������ȡ3��
		{
			if(DS18B20_IO_STATE==1)
			{
				temp=0x80;
			}
			else
			{
				temp=0x00;
			}
		}

		DS18B20_Delay_us(45);
		DS18B20_HIGH; 
		DS18B20_Delay_us(30);
		data=data|(temp>>(7-i));
	}
	return data;
}

//***************************************************//
//  ��������: DS18B20 ���߸�λ
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
//  
//***************************************************//
static u8 DS18B20_Init()
{
	u8 State,i;

	DS18B20_HIGH;  
	DS18B20_Delay_us(50);   
  	DS18B20_LOW;        //��������		
	DS18B20_Delay_us(500);
	DS18B20_HIGH;      	//�ͷ�����
	DS18B20_Delay_us(50);		//��ʱ���
	
	for(i=0;i<10;i++)
	{
		if(DS18B20_IO_STATE == LOW)        //18b20Ӧ����
		{		
			State = TRUE;
			break;
		}
		else
		{
			State = FALSE;
		}
	}
	DS18B20_HIGH;      		//�ͷ�����
	i=0;
	while( (DS18B20_IO_STATE == LOW ))
	{
		DS18B20_Delay_us(2);
		i++;
		if( i> 5)
		{
			State = FALSE;
			break;
		}
	}
	DS18B20_Delay_us(10);	//��ʱ

	return State;
}

//***************************************************//
//  ��������: ��ȡDS18B20�¶�����
//  
//  ����: ��
//  
//  ����ֵ: float ����
//  
//  ˵��:�ڲ��п���ȫ���жϲ���
//  
//***************************************************//
float DS18B20_Get_Temperature()
{
	B16_B08 Data;
	u16 Buff;
	float TempVal = 0.0;
	
	CLOSE_ALL_IRQ;

	if(DS18B20_Init()==TRUE)
	{
		DS18B20_Write_Byte(0xcc);
		DS18B20_Write_Byte(0x44);

		DS18B20_Init();

		DS18B20_Write_Byte(0xcc);
		DS18B20_Write_Byte(0xbe);

		Data.B08[0]=DS18B20_Read_Byte();
		Data.B08[1]=DS18B20_Read_Byte();

		if( Data.B08[1] & 0xF8 )//���¶�
		{
			Buff = (~Data.B16) & 0x7FF;
		}
		else
		{
			Buff = Data.B16 & 0x7FF;
		}

		TempVal = (float)Buff * DS18B20_RESOLUTION;
	}
	else
	{
		TempVal = 0.00f;
	}
	
	OPEN_ALL_IRQ;

	return TempVal;
}

//***************************************************//
//  ��������: ��ȡDS18B20 �ڲ�ROM ID
//  
//  ����: Ŀ�����ݵ�ַ(8�ֽڳ���)
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void DS18B20_GetID()
{
	u8 i;

	CLOSE_ALL_IRQ;

	if(DS18B20_Init()==TRUE)
	{
		DS18B20_Write_Byte(0x33);
		for(i=0;i<8;i++)
		{
			DS18B20_Info.ID[i]=DS18B20_Read_Byte();
		}

	}
	else
	{
		memset(DS18B20_Info.ID,0x00,sizeof(DS18B20_Info.ID) );
	}

	OPEN_ALL_IRQ;
}

