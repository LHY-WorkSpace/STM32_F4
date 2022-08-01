#include "IncludeFile.h"




//***************************************************//
//  功能描述: SPI初始化
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: PA6-MISO
//  	  PA7-MOSI 
//		  PA5-CLK
//		  PA4-CS
//***************************************************//
void Flash_IO_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);


	GPIO_InitTypeDef GPIO_InitTypeDefinsture;
	SPI_InitTypeDef SPI_InitTypeDefinsture;


	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_6;                
	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                     
	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_4;                
	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;

	SPI_FLASH_DISABLE;

	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
	

	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI1,&SPI_InitTypeDefinsture);
    SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE|SPI_I2S_FLAG_TXE);
	SPI_Cmd(SPI1,ENABLE);

}




//***************************************************//
//  功能描述: 发送并读取1字节数据
//  
//  参数: 发送数
//  
//  返回值: 读取值
//  
//  说明: 无
//  
//***************************************************//
static u8 FLASH_SendData(u8 Tdata)
{
    u8 Temp=0;

	SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_TXE);	
	SPI_I2S_SendData(SPI1,Tdata);	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);            


	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);            
	Temp = SPI_I2S_ReceiveData(SPI1);			
	SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE);

    return Temp;

}

//***************************************************//
//  功能描述:读状态寄存器
//  
//  参数: 寄存器地址
//  
//  返回值: 读取的值
//  
//  说明:无
//  
//***************************************************//
static u8 Flash_ReadStateReg(u8 CMD)
{
	u8 Temp = 0;

	SPI_FLASH_ENABLE; 

	FLASH_SendData(CMD);

	Temp = FLASH_SendData(0);

	SPI_FLASH_DISABLE;

	return Temp;

}

//***************************************************//
//  功能描述:写状态寄存器
//  
//  参数: 寄存器地址，数据
//  
//  返回值: 无
//  
//  说明:无
//  
//***************************************************//
static void Flash_WriteStateReg(u8 CMD,u8 Data)
{

	SPI_FLASH_ENABLE; 

	FLASH_SendData(CMD);
	
	FLASH_SendData(Data);

	SPI_FLASH_DISABLE;
}

//***************************************************//
//  功能描述:发送地址
//  
//  参数: 读写地址
//  
//  返回值: 无
//  
//  说明:无
//  
//***************************************************//
static void Flash_SendAddr(u32 Addr)
{
	u8 i;
	B32_B08 AddrTemp;

	AddrTemp.B32 = Addr;

	for ( i = 0; i < 3; i++)
	{
		FLASH_SendData(AddrTemp.B08[2 -i]);
	}
}




//***************************************************//
//  功能描述: 写使能
//  
//  参数: 无
//  
//  返回值:无
//  
//  说明: 无
//  
//***************************************************//
static void Flash_WR_Enable()
{
	SPI_FLASH_ENABLE; 

	FLASH_SendData(FLASH_WREN);

	SPI_FLASH_DISABLE;
}

//***************************************************//
//  功能描述: 开始扇区擦除
//  
//  参数: 起始地址
//  
//  返回值:无
//  
//  说明: 无
//  
//***************************************************//
static void Flash_Start_Erase(u32 Addr)
{

	SPI_FLASH_ENABLE; 

	FLASH_SendData(FLASH_SECTOR_ERASE);

	Flash_SendAddr(Addr);

	SPI_FLASH_DISABLE;

}


//***************************************************//
//  功能描述: 获取Flash状态
//  
//  参数: 无
//  
//  返回值:BUSY  ILDE
//  
//  说明: 无
//  
//***************************************************//
static u8 Flash_GetBusyState()
{
	if ( Flash_ReadStateReg(FLASH_READ_STATE_REG0) & 0x01)
	{
		return BUSY;
	}
	else
	{
		return ILDE;
	}
}

//***************************************************//
//  功能描述: 扇区擦除函数
//  
//  参数: 地址或扇区号，模式
//  
//  返回值: TRUE / FALSE
//  
//  说明: 地址模式时，未对齐的地址会强制向低地址4K对齐
//  
//***************************************************//
u8 Flash_Sector_Erase(u32 Addr,u8 Type)
{

	B32_B08 AddrTemp;
	u8 i;

	if( ERASE_MODE_ADDR == Type )
	{
		AddrTemp.B32 = Addr & 0xFFFFF000;
	}
	else
	{
		if( Addr >= FLASH_SIZE/FLASH_SECTOR_SIZE)
		{
			return FALSE;
		}
		AddrTemp.B32 =  FLASH_SECTOR_SIZE * Addr;
	}

	Flash_WR_Enable();

	Flash_Start_Erase(AddrTemp.B32);

	i = 0;
	do
	{
		i++;
		Delay_ms(10);
		if ( i >= 35)
		{
			return OVER_TIME;
		}

	} while ( Flash_GetBusyState() == BUSY );

	return TRUE;
}

//***************************************************//
//  功能描述: Flash读数据函数
//  
//  参数: 地址，数据指针，长度
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
u8 Flash_Read_Data(u32 Addr,u8 *Data,u32 Length)
{
	u32 i;

	SPI_FLASH_ENABLE; 

	FLASH_SendData(FLASH_READ);

	Flash_SendAddr(Addr);

	for ( i = 0; i < Length; i++ )
	{
		Data[i] = FLASH_SendData(0x00);
	}

	SPI_FLASH_DISABLE;

	return TRUE;
}

//***************************************************//
//  功能描述: Flash写数据函数
//  
//  参数: 地址，数据指针，长度
//  
//  返回值: TRUE / FALSE
//  
//  说明: 内部有跨页处理，但是没有擦除判断
//  
//***************************************************//
u8 Flash_Write_Data(u32 Addr,u8 *Data,u32 Length)
{
	u16 i;
	u8 State;
	u32 PageNum,WR_Len,Offset,LenCount;
	u32 MemAddr;	//绝对地址

	if( Addr >= FLASH_SIZE)
	{
		return FALSE;
	}
	
	MemAddr = Addr;

	PageNum = Addr/FLASH_PAGE_SIZE;			//得到页编号
	Offset = Addr - PageNum*FLASH_PAGE_SIZE;	//计算页内偏移
	WR_Len = FLASH_PAGE_SIZE - Offset;		//计算一页内从偏移位置要写入的字节数
	LenCount = 0;

	if( WR_Len >= Length )	//长度小于等于未跨页剩余字节数，则按实际长度写入
	{
		WR_Len = Length;
	}

	do
	{

		Flash_WR_Enable();

		SPI_FLASH_ENABLE; 

		FLASH_SendData(FLASH_PAGE_WRITE);

		Flash_SendAddr(MemAddr);

		for ( i = 0; i < WR_Len; i++)
		{
			FLASH_SendData(Data[i]);
			LenCount++;
		}

		SPI_FLASH_DISABLE;

		i = 0;
		do
		{
			i++;
			Delay_ms(2);
			State = Flash_ReadStateReg(FLASH_READ_STATE_REG0) & 0x01;
			if ( i >= 5)
			{
				return OVER_TIME;
			}

		} while ( State );
		
		MemAddr += WR_Len;

		if( (Length - LenCount) >= FLASH_PAGE_SIZE)
		{
			WR_Len = FLASH_PAGE_SIZE;
		}
		else
		{
			WR_Len = Length - LenCount;
		}

	}while(LenCount != Length);

	return TRUE;

}


//***************************************************//
//  功能描述: Flash写数据函数(任意地址，任意长度)
//  
//  参数: 地址，数据指针，长度
//  
//  返回值: TRUE / FALSE
//  
//  说明: 带自动擦除的写入
//  
//***************************************************//
u8 Flash_AnyAddr_Write_Data(u32 Addr,u8 *Data,u32 Length)
{
	u8 *Data_Point = NULL;
	u32 i,k;
	u32 EndAddr,Offset,WR_Len;
	u32 WriteAddr;
	u8 SectorBufff[FLASH_SECTOR_SIZE];

	Data_Point = Data;
	WriteAddr = Addr;
	EndAddr = Addr + Length;

	if( ( Addr >= FLASH_SIZE )  || (  EndAddr > FLASH_SIZE ) )
	{
		return FALSE;
	}

	while(1)
	{

		//读取整个扇区数据
		Flash_Read_Data( (WriteAddr / FLASH_SECTOR_SIZE)*FLASH_SECTOR_SIZE ,SectorBufff,FLASH_SECTOR_SIZE);
		Offset = WriteAddr % FLASH_SECTOR_SIZE;
		WR_Len = FLASH_SECTOR_SIZE - Offset;//该扇区剩余空间
		
		if( WR_Len >= Length) 
		{
			WR_Len = Length;
		}

		for(k=0; k < WR_Len; k++)
		{
			if( SectorBufff[Offset+k] != 0xFF)
			{
				break;
			}
		}

		if( k < WR_Len )//需要擦除
		{
			WriteAddr = (WriteAddr / FLASH_SECTOR_SIZE)*FLASH_SECTOR_SIZE;
			Flash_Sector_Erase(WriteAddr,ERASE_MODE_ADDR);
			Offset = 0;
			WR_Len = FLASH_SECTOR_SIZE;
		}

		memcpy((SectorBufff + Offset),Data_Point,WR_Len);

		Flash_Write_Data( WriteAddr,(SectorBufff + Offset),WR_Len);

		WriteAddr += WR_Len;
		Data_Point += WR_Len;
		Length -= WR_Len;

		if( WriteAddr >= (EndAddr) )
		{
			break;
		}
	}
	return TRUE;
}


 u8 FLASH_ID[20];
void Flash_GetID()
{
	u8 i;
	FLASH_SendData(0x90);
	for ( i = 0; i < 3; i++)
	{
		FLASH_SendData(0x00);
	}

	for ( i = 0; i < 16; i++)
	{
		FLASH_ID[i] = FLASH_SendData(0x00);
	}
}

