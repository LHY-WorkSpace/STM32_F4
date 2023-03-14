#include "IncludeFile.h"


//����������ݵĴ�С
#define POINT_SIZE  (sizeof(u16))

//DMA ������������
#define DMA_MAX_BUFF  (60000)

//DMA������Ʋ���
static u32 DMA_TXCurrentAddr,DMA_EndAddr,Length;
static u8 TX_Flag;


//***************************************************//
//  ��������: TFT SPI IO��ʼ��
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: 2��Ƶ = 42Mhz
//  PA5-------SCLK          PA7------SDA
//  PA6-------D/C           PA4------RST 
//***************************************************//
static void ST7789_IOInit()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIOB_InitTypeDefinsture;
	SPI_InitTypeDef SPI_InitTypeDefinsture;
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;                 
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                        
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOA,&GPIOB_InitTypeDefinsture);
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_6;                
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIOB_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);	
	
	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_1Line_Tx;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;  
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI1,&SPI_InitTypeDefinsture);
    SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
	SPI_Cmd(SPI1 ,ENABLE);
}

//***************************************************//
//  ��������: 7789 DMA��ʼ��
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
//  
//***************************************************//
void ST7789_DMA_Init()
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

  	DMA_InitTypeDef DMA_InitConfig;
	NVIC_InitTypeDef  NVIC_Initstr;

    DMA_Cmd(DMA2_Stream3,DISABLE);
	DMA_InitConfig.DMA_Memory0BaseAddr = 0;	
	DMA_InitConfig.DMA_PeripheralBaseAddr=(u32)&(SPI1->DR);
	DMA_InitConfig.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitConfig.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitConfig.DMA_BufferSize = DMA_MAX_BUFF;
	DMA_InitConfig.DMA_DIR=DMA_DIR_MemoryToPeripheral;  
	DMA_InitConfig.DMA_Channel=DMA_Channel_3; 
	DMA_InitConfig.DMA_Mode=DMA_Mode_Normal;
	DMA_InitConfig.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitConfig.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitConfig.DMA_Priority=DMA_Priority_VeryHigh;
	DMA_InitConfig.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream3,&DMA_InitConfig);

	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream3_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=5;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);
	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);	
	DMA_Cmd(DMA2_Stream3,DISABLE);

}


//***************************************************//
//  ��������: �������������
//  
//  ����: ����
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
//  
//***************************************************//
static void ST7789_SendData(u8 Data)
{
	
    u8 OverTime;
    ST7789_DATA;
	SPI_I2S_SendData(SPI1,Data);		
    OverTime = 0xFF;
	while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET ) || (OverTime--) ); 
    OverTime = 0xFF;
    while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET ) || (OverTime--) ); 
}

static void ST7789_SetCmd(u8 CMD)
{
    u8 OverTime;
    ST7789_CMD;	
	SPI_I2S_SendData(SPI1,CMD);	
    OverTime = 0xFF;
	while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET ) || (OverTime--) ); 
    OverTime = 0xFF;
    while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET ) || (OverTime--) ); 

}

//***************************************************//
//  ��������: ST7789 ���ó�ʼ��
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void ST7789_Init()
{

    ST7789_IOInit();
    ST7789_DMA_Init();

	ST7789_RST_ON;
	Delay_ms(10);
    ST7789_RST_OFF;
	Delay_ms(10);

    ST7789_SetCmd(0x11); 			//Sleep Out
	Delay_ms(120);               //DELAY120ms 
    ST7789_SetCmd(0x3A);        //65k mode
    ST7789_SendData(0x05);
    ST7789_SetCmd(0xC5); 		//VCOM
    ST7789_SendData(0x1A);

    ST7789_SetCmd(0x36);                 // ��Ļ��ʾ��������
    ST7789_SendData(0x00);              // 0x00������0x60����


    ST7789_SetCmd(0xb2);		//Porch Setting
    ST7789_SendData(0x05);
    ST7789_SendData(0x05);
    ST7789_SendData(0x00);
    ST7789_SendData(0x33);
    ST7789_SendData(0x33);
    ST7789_SetCmd(0xb7);			//Gate Control
    ST7789_SetCmd(0xBB);//VCOM
    ST7789_SendData(0x3F);
    ST7789_SetCmd(0xC0); //Power control
    ST7789_SendData(0x2c);
    ST7789_SetCmd(0xC2);		//VDV and VRH Command Enable
    ST7789_SendData(0x01);
    ST7789_SetCmd(0xC3);			//VRH Set
    ST7789_SendData(0x0F);		//4.3+( vcom+vcom offset+vdv)
    ST7789_SetCmd(0xC4);			//VDV Set
    ST7789_SendData(0x20);				//0v
    ST7789_SetCmd(0xC6);				//Frame Rate Control in Normal Mode
    ST7789_SendData(0X00);			//111Hz
    ST7789_SetCmd(0xd0);				//Power Control 1
    ST7789_SendData(0xa4);
    ST7789_SendData(0xa1);
    ST7789_SetCmd(0xE8);				//Power Control 1
    ST7789_SendData(0x03);
    ST7789_SetCmd(0xE9);				//Equalize time control
    ST7789_SendData(0x09);
    ST7789_SendData(0x09);
    ST7789_SendData(0x08);
    ST7789_SetCmd(0xE0); //Set Gamma
    ST7789_SendData(0xD0);
    ST7789_SendData(0x05);
    ST7789_SendData(0x09);
    ST7789_SendData(0x09);
    ST7789_SendData(0x08);
    ST7789_SendData(0x14);
    ST7789_SendData(0x28);
    ST7789_SendData(0x33);
    ST7789_SendData(0x3F);
    ST7789_SendData(0x07);
    ST7789_SendData(0x13);
    ST7789_SendData(0x14);
    ST7789_SendData(0x28);
    ST7789_SendData(0x30);
    ST7789_SetCmd(0XE1); //Set Gamma
    ST7789_SendData(0xD0);
    ST7789_SendData(0x05);
    ST7789_SendData(0x09);
    ST7789_SendData(0x09);
    ST7789_SendData(0x08);
    ST7789_SendData(0x03);
    ST7789_SendData(0x24);
    ST7789_SendData(0x32);
    ST7789_SendData(0x32);
    ST7789_SendData(0x3B);
    ST7789_SendData(0x14);
    ST7789_SendData(0x13);
    ST7789_SendData(0x28);
    ST7789_SendData(0x2F);
    ST7789_SetCmd(0x21); 		//����
    ST7789_SetCmd(0x29);         //������ʾ 
    // ST7789_Full(0x0000);

    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
    Length =0;
    TX_Flag = FALSE;
}


//***************************************************//
//  ��������: ���û�ͼ����
//  
//  ����: ��ʼ�ͽ�������
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void ST7789_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{	

	ST7789_SetCmd(0x2a);
	ST7789_SendData(0x00);
	ST7789_SendData(x_start);
	ST7789_SendData(0x00);
	ST7789_SendData(x_end);

	ST7789_SetCmd(0x2b);
	ST7789_SendData(0x00);
	ST7789_SendData(y_start);
	ST7789_SendData(0x00);
	ST7789_SendData(y_end);	
	ST7789_SetCmd(0x2c);
}


//***************************************************//
//  ��������: ����
//  
//  ����: ��ɫֵ
//  
//  ����ֵ: 
//  
//  ˵��: ����ǰ��ָ����ͼ��Χ
//  
//***************************************************//
void ST7789_DrawPoint(u16 color)
{
    ST7789_SendData(color>>8);
    ST7789_SendData(color);
}


//***************************************************//
//  ��������: ����
//  
//  ����: ��ɫֵ
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
//  
//***************************************************//
void ST7789_Full(u16 color)
{
    u32 ROW;
    ST7789_SetCmd(0x2a);     //Column address set
    ST7789_SendData(0x00);    //start column
    ST7789_SendData(0x00); 
    ST7789_SendData(0x00);    //end column
    ST7789_SendData(0xF0);

    ST7789_SetCmd(0x2b);     //Row address set
    ST7789_SendData(0x00);    //start row
    ST7789_SendData(0x00); 
    ST7789_SendData(0x00);    //end row
    ST7789_SendData(0xF0);
    ST7789_SetCmd(0x2C);     //Memory write
    for(ROW=0;ROW<240*240;ROW++)             //ROW loop
    { 
        ST7789_SendData(color>>8);
        ST7789_SendData(color);
    }
}


//***************************************************//
//  ��������: �������ݸߵ��ֽ�
//  
//  ����: u16 ( RGB565 )
//  
//  ����ֵ: ��
//  
//  ˵��: ������Ϊ BGR 565  ,7789�Ƚ��ո��ֽ�����
//  
//***************************************************//
void ST7789_SwapDataForDMA(u16 *Data)
{
    u16 Buf;

    Buf = *Data;

    *Data >>= 8;

    *Data |= (Buf&0xFF)<<8;

}

//***************************************************//
//  ��������: DMA����������ʼ��ַ�ͳ���
//  
//  ����: ���ݵ�ַ������
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: 
//  
//***************************************************//
void ST7789_DMA_SetAddr(u32 StartAddr, u32 Point)
{
    DMA_TXCurrentAddr = StartAddr;
    DMA_EndAddr = StartAddr + Point*POINT_SIZE;
    Length =0;
}

//***************************************************//
//  ��������: �жϿ��ƻ�ȡDMA����״̬
//  
//  ����: 
//  
//  ����ֵ: TRUE�������/ FALSE��δ���
//  
//  ˵��:
//  
//***************************************************//
u8 ST7789_DMA_ISR_GetTXComplateFlag()
{
    DMA_TXCurrentAddr += Length;

    if( DMA_TXCurrentAddr < DMA_EndAddr )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//***************************************************//
//  ��������:��ȡDMA����״̬
//  
//  ����: 
//  
//  ����ֵ: TRUE�������/ FALSE��δ���
//  
//  ˵��:
//  
//***************************************************//
u8 ST7789_DMA_GetTXState()
{
    return TX_Flag;
}


//***************************************************//
//  ��������: ����DMA����
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ����DMA����ʱ�ȵ��� ST7789_DMA_SetAddr(),ȷ��������ʼ��ַ�ͳ���
//        �ж���ֱ�ӵ���
//***************************************************//
void ST7789_DMA_Start()
{

    ST7789_DATA;

    Length = (DMA_EndAddr - DMA_TXCurrentAddr);

    if( Length > DMA_MAX_BUFF )
    {
         Length = DMA_MAX_BUFF;
    }

    DMA_Cmd(DMA2_Stream3,DISABLE);
    DMA_MemoryTargetConfig(DMA2_Stream3,DMA_TXCurrentAddr,DMA_Memory_0);
    DMA_SetCurrDataCounter(DMA2_Stream3,Length);
    DMA_Cmd(DMA2_Stream3,ENABLE);
    TX_Flag = FALSE;
    
}

//***************************************************//
//  ��������: ֹͣDMA
//  
//  ����: ��
//  
//  ����ֵ: 
//  
//  ˵��: ���ݴ��䵽���趨���Ⱥ�ֹͣDMA
//  
//***************************************************//
void ST7789_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream3,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
    TX_Flag = TRUE;
}



