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
static void GC9A01_IOInit()
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
void GC9A01_DMA_Init()
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
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=9;
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
static void GC9A01_SendData(u8 Data)
{
	
    u8 OverTime;
    GC9A01_DATA;
	SPI_I2S_SendData(SPI1,Data);		
    OverTime = 0xFF;
	while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET ) || (OverTime--) ); 
    OverTime = 0xFF;
    while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET ) || (OverTime--) ); 
}

static void GC9A01_SetCmd(u8 CMD)
{
    u8 OverTime;
    GC9A01_CMD;	
	SPI_I2S_SendData(SPI1,CMD);	
    OverTime = 0xFF;
	while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET ) || (OverTime--) ); 
    OverTime = 0xFF;
    while( ( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET ) || (OverTime--) ); 

}

//***************************************************//
//  ��������: GC9A01 ���ó�ʼ��
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void GC9A01_Init()
{

    GC9A01_IOInit();
    GC9A01_DMA_Init();

	GC9A01_RST_ON;
	Delay_ms(10);
    GC9A01_RST_OFF;
	Delay_ms(10);

    GC9A01_SetCmd(0xEF);
    GC9A01_SetCmd(0xEB);
    GC9A01_SendData(0x14);
    GC9A01_SetCmd(0xFE);
    GC9A01_SetCmd(0xEF);
    GC9A01_SetCmd(0xEB);
    GC9A01_SendData(0x14);
    GC9A01_SetCmd(0x84);
    GC9A01_SendData(0x40);
    GC9A01_SetCmd(0x85);
    GC9A01_SendData(0xFF);
    GC9A01_SetCmd(0x86);
    GC9A01_SendData(0xFF);
    GC9A01_SetCmd(0x87);
    GC9A01_SendData(0xFF);
    GC9A01_SetCmd(0x88);
    GC9A01_SendData(0x0A);
    GC9A01_SetCmd(0x89);
    GC9A01_SendData(0x21);
    GC9A01_SetCmd(0x8A);
    GC9A01_SendData(0x00);
    GC9A01_SetCmd(0x8B);
    GC9A01_SendData(0x80);
    GC9A01_SetCmd(0x8C);
    GC9A01_SendData(0x01);
    GC9A01_SetCmd(0x8D);
    GC9A01_SendData(0x01);
    GC9A01_SetCmd(0x8E);
    GC9A01_SendData(0xFF);
    GC9A01_SetCmd(0x8F);
    GC9A01_SendData(0xFF);
    GC9A01_SetCmd(0xB6);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x20);   

    GC9A01_SetCmd(0x3A);
    GC9A01_SendData(0x05);
    GC9A01_SetCmd(0x90);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x08);
    GC9A01_SetCmd(0xBD);
    GC9A01_SendData(0x06);
    GC9A01_SetCmd(0xBC);
    GC9A01_SendData(0x00);
    GC9A01_SetCmd(0xFF);
    GC9A01_SendData(0x60);
    GC9A01_SendData(0x01);
    GC9A01_SendData(0x04);
    GC9A01_SetCmd(0xC3);
    GC9A01_SendData(0x13);
    GC9A01_SetCmd(0xC4);
    GC9A01_SendData(0x13);
    GC9A01_SetCmd(0xC9);
    GC9A01_SendData(0x22);
    GC9A01_SetCmd(0xBE);
    GC9A01_SendData(0x11);
    GC9A01_SetCmd(0xE1);
    GC9A01_SendData(0x10);
    GC9A01_SendData(0x0E);
    GC9A01_SetCmd(0xDF);
    GC9A01_SendData(0x21);
    GC9A01_SendData(0x0C);
    GC9A01_SendData(0x02);
    GC9A01_SetCmd(0xF0);
    GC9A01_SendData(0x45);
    GC9A01_SendData(0x09);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x26);
    GC9A01_SendData(0x2A);
    GC9A01_SetCmd(0xF1);
    GC9A01_SendData(0x43);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x72);
    GC9A01_SendData(0x36);
    GC9A01_SendData(0x37);
    GC9A01_SendData(0x6F);
    GC9A01_SetCmd(0xF2);
    GC9A01_SendData(0x45);
    GC9A01_SendData(0x09);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x08);
    GC9A01_SendData(0x26);
    GC9A01_SendData(0x2A);
    GC9A01_SetCmd(0xF3);
    GC9A01_SendData(0x43);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x72);
    GC9A01_SendData(0x36);
    GC9A01_SendData(0x37);
    GC9A01_SendData(0x6F);
    GC9A01_SetCmd(0xED);
    GC9A01_SendData(0x1B);
    GC9A01_SendData(0x0B);
    GC9A01_SetCmd(0xAE);
    GC9A01_SendData(0x77);
    GC9A01_SetCmd(0xCD);
    GC9A01_SendData(0x63);
    GC9A01_SetCmd(0x70);
    GC9A01_SendData(0x07);
    GC9A01_SendData(0x07);
    GC9A01_SendData(0x04);
    GC9A01_SendData(0x0E);
    GC9A01_SendData(0x0F);
    GC9A01_SendData(0x09);
    GC9A01_SendData(0x07);
    GC9A01_SendData(0X08);
    GC9A01_SendData(0x03);
    GC9A01_SetCmd(0xE8);
    GC9A01_SendData(0x34);
    GC9A01_SetCmd(0x62);
    GC9A01_SendData(0x18);
    GC9A01_SendData(0x0D);
    GC9A01_SendData(0x71);
    GC9A01_SendData(0xED);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x18);
    GC9A01_SendData(0X0F);
    GC9A01_SendData(0x71);
    GC9A01_SendData(0xEF);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x70);


    GC9A01_SetCmd(0x63);
    GC9A01_SendData(0x18);
    GC9A01_SendData(0x11);
    GC9A01_SendData(0x71);
    GC9A01_SendData(0xF1);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x18);
    GC9A01_SendData(0X13);
    GC9A01_SendData(0x71);
    GC9A01_SendData(0xF3);
    GC9A01_SendData(0x70);
    GC9A01_SendData(0x70);
    GC9A01_SetCmd(0x64);
    GC9A01_SendData(0x28);
    GC9A01_SendData(0x29);
    GC9A01_SendData(0xF1);
    GC9A01_SendData(0x01);
    GC9A01_SendData(0xF1);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x07);
    GC9A01_SetCmd(0x66);
    GC9A01_SendData(0x3C);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0xCD);
    GC9A01_SendData(0x67);
    GC9A01_SendData(0x45);
    GC9A01_SendData(0x45);
    GC9A01_SendData(0x10);
    GC9A01_SendData(0X00);
    GC9A01_SendData(0X00);
    GC9A01_SendData(0X00);
    GC9A01_SetCmd(0x67);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x3C);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x01);
    GC9A01_SendData(0x54);
    GC9A01_SendData(0X10);
    GC9A01_SendData(0x32);
    GC9A01_SendData(0x98);

    GC9A01_SetCmd(0x74);
    GC9A01_SendData(0x10);
    GC9A01_SendData(0x85);
    GC9A01_SendData(0x80);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x00);
    GC9A01_SendData(0x4E);
    GC9A01_SendData(0x00);

    GC9A01_SetCmd(0x98);
    GC9A01_SendData(0x3E);
    GC9A01_SendData(0x07);

    GC9A01_SetCmd(0x35);
    GC9A01_SetCmd(0x21);

    GC9A01_SetCmd(0x11);
    Delay_ms(100);  
    GC9A01_SetCmd(0x29);
    Delay_ms(100); 

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
void GC9A01_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{	

	GC9A01_SetCmd(0x2a);
	GC9A01_SendData(x_start>>8);
	GC9A01_SendData(x_start&0xFF);
	GC9A01_SendData(x_end>>8);
	GC9A01_SendData(x_end&0xFF);

	GC9A01_SetCmd(0x2b);
	GC9A01_SendData(y_start>>8);
	GC9A01_SendData(y_start&0xFF);
	GC9A01_SendData(y_end>>8);
	GC9A01_SendData(y_end&0xFF);	
	GC9A01_SetCmd(0x2c);
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
void GC9A01_DrawPoint(u16 color)
{
    GC9A01_SendData(color>>8);
    GC9A01_SendData(color);
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
void GC9A01_Full(u16 color)
{
    u32 ROW;
    GC9A01_SetCmd(0x2a);     //Column address set
    GC9A01_SendData(0x00);    //start column
    GC9A01_SendData(0x00); 
    GC9A01_SendData(0x00);    //end column
    GC9A01_SendData(0xF0);

    GC9A01_SetCmd(0x2b);     //Row address set
    GC9A01_SendData(0x00);    //start row
    GC9A01_SendData(0x00); 
    GC9A01_SendData(0x00);    //end row
    GC9A01_SendData(0x00);
    GC9A01_SetCmd(0xF0);     //Memory write
    for(ROW=0;ROW<240*240;ROW++)             //ROW loop
    { 
        GC9A01_SendData(color>>8);
        GC9A01_SendData(color);
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
void GC9A01_SwapDataForDMA(u16 *Data)
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
void GC9A01_DMA_SetAddr(u32 StartAddr, u32 Point)
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
u8 GC9A01_DMA_ISR_GetTXComplateFlag()
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
u8 GC9A01_DMA_GetTXState()
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
//  ˵��: ����DMA����ʱ�ȵ��� GC9A01_DMA_SetAddr(),ȷ��������ʼ��ַ�ͳ���
//        �ж���ֱ�ӵ���
//***************************************************//
void GC9A01_DMA_Start()
{

    GC9A01_DATA;

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
void GC9A01_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream3,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
    TX_Flag = TRUE;
}



