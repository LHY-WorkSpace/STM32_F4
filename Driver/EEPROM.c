#include"IncludeFile.h"



//************************// 
//  功能描述: EEPROM IO 初始化函数
//  
//  参数: 无
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
void EEPROM_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	IIC_SCL_HIGH;
	IIC_SDA_HIGH;//置为总线空闲

	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_OD;                
	GPIO_Init(GPIOB,&GPIO_Initstructure);
}

// SCL - PB0
// SDA - PB1
//72Mhz = 133khz
static void EE_IIC_Delay(u16 nus)
{
	u16 i,k;

	for(k=0; k<nus; k++)
	{
		for(i=0; i<10; i++)
		{
			__NOP();
		}
	}
}

static void EE_Start_IIC(void)
{
	EE_IIC_SDA_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SCL_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SDA_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SCL_LOW;
	EE_IIC_Delay(2);

}

static void EE_IIC_Stop(void)
{
	EE_IIC_SCL_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SDA_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SCL_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SDA_HIGH;
	EE_IIC_Delay(2);

}

static void EE_IIC_Send_Ack(void)
{
	EE_IIC_SCL_LOW;
	EE_IIC_SDA_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SCL_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SCL_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SDA_HIGH;
	EE_IIC_Delay(2);
}

static void EE_IIC_Send_NAck(void)
{
	EE_IIC_SCL_LOW;
	EE_IIC_SDA_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SCL_HIGH;
	EE_IIC_Delay(2);
	EE_IIC_SCL_LOW;
	EE_IIC_Delay(2);
	EE_IIC_SDA_HIGH;
	EE_IIC_Delay(2);
}

static u8 EE_IIC_Wait_Ack_OK(void)
{
	u8 i=0;

	EE_IIC_SCL_HIGH; 
	EE_IIC_Delay(2);                              
	while( EE_IIC_SDA_STATE == HIGH)
	{
			i++;
			if(i>10)
			{
				EE_IIC_Stop();
				return FALSE;
			}
			EE_IIC_Delay(2);	
	}			
	EE_IIC_SCL_LOW;	
	EE_IIC_Delay(2);
	EE_IIC_SDA_HIGH;
	return TRUE;
}

static void EE_IIC_SenddByte(u8 Data)
{

	u8 i=0;
	
	for(i=0;i<8;i++)
	{
		//EE_IIC_Delay(2);
		if(Data&0x80)	
		{
			EE_IIC_SDA_HIGH;
		}
		else
		{
			EE_IIC_SDA_LOW;
		}
		Data<<=1;
		EE_IIC_Delay(2);
		EE_IIC_SCL_HIGH;
		EE_IIC_Delay(2);
		EE_IIC_SCL_LOW;
	}
	EE_IIC_Delay(2);  
	EE_IIC_SDA_HIGH;               
}


static u8 EE_IIC_GetByte(void)
{
	u8 Data=0;
	u8 i=0;
	for(i=0;i<8;i++)
	{		
		Data<<=1;
		EE_IIC_SCL_LOW;
		EE_IIC_Delay(2); 		
		EE_IIC_SCL_HIGH;	
		EE_IIC_Delay(2);
		if( EE_IIC_SDA_STATE == HIGH)	
		{
			Data|=0x01;
		}
	}
 	EE_IIC_SCL_LOW;	
	EE_IIC_Delay(2);
	EE_IIC_SDA_HIGH;
  return Data;
}

//************************// 
//  功能描述: EEPROM 数据写入函数
//  
//  参数: 物理地址，长度，数据指针
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
u8  EEPROMWriteData(u16 addr,u16 length,u8 *data)
{
	u8 k,i;
	u16 PageNum,WR_Len,Offset,LenCount;
	B16_B08 MemAddr;	//绝对地址

	if( addr >= EEPROM_PAGE_SIZE*EEPROM_PAGES)
	{
		return 0XFF;
	}
	
	MemAddr.B16 = addr;

	PageNum = addr/EEPROM_PAGE_SIZE;			//得到页编号
	Offset = addr - PageNum*EEPROM_PAGE_SIZE;	//计算页内偏移
	WR_Len = EEPROM_PAGE_SIZE - Offset;		//计算一页内从偏移位置要写入的字节数
	LenCount = 0;

	if( WR_Len >= length )	//长度小于等于未跨页剩余字节数，则按实际长度写入
	{
		WR_Len = length;
	}

	do
	{
		Start_IIC();
		IIC_SenddByte(EEPROM_ADDRESS | MemAddr.B08[1] <<1);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(MemAddr.B08[0]);
		IIC_Wait_Ack_OK();

		for(k=0;k<WR_Len;k++)
		{
			IIC_SenddByte(data[LenCount]);
			if(IIC_Wait_Ack_OK() == FALSE)
			{
				return FALSE;
			}
			LenCount++;
		}
		Stop_IIC();
		//此处必须延时，等待页写入完成，手册最大5ms
		for ( i = 0; i < 5; i++)
		{
			IIC_Delay(1000);
		}
		
		MemAddr.B16 += WR_Len;

		if( (length - LenCount) >= EEPROM_PAGE_SIZE)
		{
			WR_Len = EEPROM_PAGE_SIZE;
		}
		else
		{
			WR_Len = length - LenCount;
		}

	}while(LenCount != length);

	return TRUE;
}



//************************// 
//  功能描述: EEPROM 数据读取函数
//  
//  参数: 物理地址，长度，数据指针
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
u8 EEPROMReadData(u16 addr,u16 length,u8 *data)
{
	u16 i;
	B16_B08 MemAddr;	//绝对地址

	if( addr >= EEPROM_PAGE_SIZE*EEPROM_PAGES)
	{
		return 0XFF;
	}

	MemAddr.B16=addr;

	Start_IIC();
	IIC_SenddByte(EEPROM_ADDRESS |MemAddr.B08[1]<<1);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(MemAddr.B08[0]);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte(EEPROM_ADDRESS|0X01|MemAddr.B08[1]<<1);//读取操作
    IIC_Wait_Ack_OK();

	for(i=0;i<length;i++)
	{
		data[i]=IIC_GetByte();
		if( i == length-1)
		{
			IIC_Send_NAck();//最后一个字节发送N_ACK
		}
		else
		{
			IIC_Send_Ack();
		}
	}
	Stop_IIC();
	return TRUE;
}












