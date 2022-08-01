#include "IncludeFile.h"




//***************************************************//
//  ��������: SPI��ʼ��
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: PA6-MISO
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
//  ��������: ���Ͳ���ȡ1�ֽ�����
//  
//  ����: ������
//  
//  ����ֵ: ��ȡֵ
//  
//  ˵��: ��
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
//  ��������:��״̬�Ĵ���
//  
//  ����: �Ĵ�����ַ
//  
//  ����ֵ: ��ȡ��ֵ
//  
//  ˵��:��
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
//  ��������:д״̬�Ĵ���
//  
//  ����: �Ĵ�����ַ������
//  
//  ����ֵ: ��
//  
//  ˵��:��
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
//  ��������:���͵�ַ
//  
//  ����: ��д��ַ
//  
//  ����ֵ: ��
//  
//  ˵��:��
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
//  ��������: дʹ��
//  
//  ����: ��
//  
//  ����ֵ:��
//  
//  ˵��: ��
//  
//***************************************************//
static void Flash_WR_Enable()
{
	SPI_FLASH_ENABLE; 

	FLASH_SendData(FLASH_WREN);

	SPI_FLASH_DISABLE;
}

//***************************************************//
//  ��������: ��ʼ��������
//  
//  ����: ��ʼ��ַ
//  
//  ����ֵ:��
//  
//  ˵��: ��
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
//  ��������: ��ȡFlash״̬
//  
//  ����: ��
//  
//  ����ֵ:BUSY  ILDE
//  
//  ˵��: ��
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
//  ��������: ������������
//  
//  ����: ��ַ�������ţ�ģʽ
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��ַģʽʱ��δ����ĵ�ַ��ǿ����͵�ַ4K����
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
//  ��������: Flash�����ݺ���
//  
//  ����: ��ַ������ָ�룬����
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
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
//  ��������: Flashд���ݺ���
//  
//  ����: ��ַ������ָ�룬����
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: �ڲ��п�ҳ��������û�в����ж�
//  
//***************************************************//
u8 Flash_Write_Data(u32 Addr,u8 *Data,u32 Length)
{
	u16 i;
	u8 State;
	u32 PageNum,WR_Len,Offset,LenCount;
	u32 MemAddr;	//���Ե�ַ

	if( Addr >= FLASH_SIZE)
	{
		return FALSE;
	}
	
	MemAddr = Addr;

	PageNum = Addr/FLASH_PAGE_SIZE;			//�õ�ҳ���
	Offset = Addr - PageNum*FLASH_PAGE_SIZE;	//����ҳ��ƫ��
	WR_Len = FLASH_PAGE_SIZE - Offset;		//����һҳ�ڴ�ƫ��λ��Ҫд����ֽ���
	LenCount = 0;

	if( WR_Len >= Length )	//����С�ڵ���δ��ҳʣ���ֽ�������ʵ�ʳ���д��
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
//  ��������: Flashд���ݺ���(�����ַ�����ⳤ��)
//  
//  ����: ��ַ������ָ�룬����
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ���Զ�������д��
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

		//��ȡ������������
		Flash_Read_Data( (WriteAddr / FLASH_SECTOR_SIZE)*FLASH_SECTOR_SIZE ,SectorBufff,FLASH_SECTOR_SIZE);
		Offset = WriteAddr % FLASH_SECTOR_SIZE;
		WR_Len = FLASH_SECTOR_SIZE - Offset;//������ʣ��ռ�
		
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

		if( k < WR_Len )//��Ҫ����
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

