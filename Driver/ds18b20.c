
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
//  功能描述: DS18B20 IO 初始化函数
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 初始化后必须立即释放总线
//  DHT11 和 DS18B20 可以共用一个总线
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
	DS18B20_HIGH; //初始化完毕后立即释放总线
}


//***************************************************//
//  功能描述: DS18B20 写一个字节数据
//  
//  参数: 要写入数据
//  
//  返回值: 无
//  
//  说明: 无
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
//  功能描述: DS18B20 读一个字节数据
//  
//  参数: 无
//  
//  返回值: 读回的数据
//  
//  说明: 无
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
		DS18B20_HIGH;//释放总线

		for(k=0;k<3;k++)//连续读取3次
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
//  功能描述: DS18B20 总线复位
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
static u8 DS18B20_Init()
{
	u8 State,i;

	DS18B20_HIGH;  
	DS18B20_Delay_us(50);   
  	DS18B20_LOW;        //拉低总线		
	DS18B20_Delay_us(500);
	DS18B20_HIGH;      	//释放总线
	DS18B20_Delay_us(50);		//延时检测
	
	for(i=0;i<10;i++)
	{
		if(DS18B20_IO_STATE == LOW)        //18b20应答检测
		{		
			State = TRUE;
			break;
		}
		else
		{
			State = FALSE;
		}
	}
	DS18B20_HIGH;      		//释放总线
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
	DS18B20_Delay_us(10);	//延时

	return State;
}

//***************************************************//
//  功能描述: 获取DS18B20温度数据
//  
//  参数: 无
//  
//  返回值: float 数据
//  
//  说明:内部有开关全局中断操作
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

		if( Data.B08[1] & 0xF8 )//负温度
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
//  功能描述: 获取DS18B20 内部ROM ID
//  
//  参数: 目的数据地址(8字节长度)
//  
//  返回值: 无
//  
//  说明: 无
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

