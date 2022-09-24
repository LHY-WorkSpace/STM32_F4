#include "IncludeFile.h"


#define POINT_SIZE  (sizeof(u16))
#define DMA_MAX_BUFF  (60000)


static u32 DMA_TXCurrentAddr,DMA_EndAddr;




//***************************************************//
//  功能描述: TFT SPI IO初始化
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 2分频 = 40Mhz
//  PA5-------SCLK          PA7------SDA
//  PA6-------D/C           PA4------RST 
//***************************************************//
static void TFT_IOInit()
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

void ST7789_DMA_Init()
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

  	DMA_InitTypeDef DMA_InitConfig;
	
	NVIC_InitTypeDef  NVIC_Initstr;
	
	DMA_InitConfig.DMA_Memory0BaseAddr=0;	
	   
	DMA_InitConfig.DMA_PeripheralBaseAddr=(u32)&(SPI1->DR);
	
	DMA_InitConfig.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	
	DMA_InitConfig.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	
	DMA_InitConfig.DMA_BufferSize=DMA_MAX_BUFF;//单次传输的大小
	
	DMA_InitConfig.DMA_DIR=DMA_DIR_MemoryToPeripheral; //先试试从内存到外设  
	
	DMA_InitConfig.DMA_Channel=DMA_Channel_3; 
	
	DMA_InitConfig.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitConfig.DMA_Mode=DMA_Mode_Normal; //循环发送 DMA_Mode_Normal(单次)DMA_Mode_Circular
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitConfig.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA2_Stream3,&DMA_InitConfig);

	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream3_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);
	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);	
	DMA_Cmd(DMA2_Stream3,DISABLE);

}


//***************************************************//
//  功能描述: DMA发送数据起始地址和长度
//  
//  参数: 数据地址，点数
//  
//  返回值: TRUE / FALSE
//  
//  说明: 
//  
//***************************************************//
void TFT_DMA_SetAddr(u32 StartAddr, u32 Point)
{
    DMA_TXCurrentAddr = StartAddr;
    DMA_EndAddr = StartAddr + Point*POINT_SIZE;
}

//***************************************************//
//  功能描述: 获取当前发送地址
//  
//  参数: 无
//  
//  返回值: u32
//  
//  说明: 无
//  
//***************************************************//
u32 TFT_DMA_GetCurrentAddr()
{
    return DMA_TXCurrentAddr;
}

//***************************************************//
//  功能描述: 获取DMA发送状态
//  
//  参数: 
//  
//  返回值: TRUE：已完成/ FALSE：未完成
//  
//  说明: 无
//  
//***************************************************//
u8 TFT_DMA_GetTXComplateFlag()
{
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
//  功能描述: 启动传输
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
void TFT_DMA_Start()
{
    u32 Length;

    TFT_DATA;

    Length = (DMA_EndAddr - DMA_TXCurrentAddr);

    if( Length > DMA_MAX_BUFF )
    {
         Length = DMA_MAX_BUFF;
    }

    DMA_Cmd(DMA2_Stream3,DISABLE);
    DMA_MemoryTargetConfig(DMA2_Stream3,DMA_TXCurrentAddr,DMA_Memory_0);
    DMA_SetCurrDataCounter(DMA2_Stream3,Length);
    DMA_Cmd(DMA2_Stream3,ENABLE);
    
    DMA_TXCurrentAddr += Length;

}


void TFT_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream3,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;

}








static void TFT_SendData(u8 Data)
{
	
    TFT_DATA;
	SPI_I2S_SendData(SPI1,Data);		
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET);
}

static void TFT_SetCmd(u8 CMD)
{
    TFT_CMD;	
	SPI_I2S_SendData(SPI1,CMD);	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET); 

}


void TFT_Init()
{

    TFT_IOInit();
    ST7789_DMA_Init();

	TFT_RST_ON;
	Delay_ms(10);
    TFT_RST_OFF;
	Delay_ms(10);

    TFT_SetCmd(0x11); 			//Sleep Out
	Delay_ms(120);               //DELAY120ms 
    TFT_SetCmd(0x3A);        //65k mode
    TFT_SendData(0x05);
    TFT_SetCmd(0xC5); 		//VCOM
    TFT_SendData(0x1A);
    TFT_SetCmd(0x36);                 // 屏幕显示方向设置
    TFT_SendData(0x00);
    TFT_SetCmd(0xb2);		//Porch Setting
    TFT_SendData(0x05);
    TFT_SendData(0x05);
    TFT_SendData(0x00);
    TFT_SendData(0x33);
    TFT_SendData(0x33);
    TFT_SetCmd(0xb7);			//Gate Control
    TFT_SetCmd(0xBB);//VCOM
    TFT_SendData(0x3F);
    TFT_SetCmd(0xC0); //Power control
    TFT_SendData(0x2c);
    TFT_SetCmd(0xC2);		//VDV and VRH Command Enable
    TFT_SendData(0x01);
    TFT_SetCmd(0xC3);			//VRH Set
    TFT_SendData(0x0F);		//4.3+( vcom+vcom offset+vdv)
    TFT_SetCmd(0xC4);			//VDV Set
    TFT_SendData(0x20);				//0v
    TFT_SetCmd(0xC6);				//Frame Rate Control in Normal Mode
    TFT_SendData(0X01);			//111Hz
    TFT_SetCmd(0xd0);				//Power Control 1
    TFT_SendData(0xa4);
    TFT_SendData(0xa1);
    TFT_SetCmd(0xE8);				//Power Control 1
    TFT_SendData(0x03);
    TFT_SetCmd(0xE9);				//Equalize time control
    TFT_SendData(0x09);
    TFT_SendData(0x09);
    TFT_SendData(0x08);
    TFT_SetCmd(0xE0); //Set Gamma
    TFT_SendData(0xD0);
    TFT_SendData(0x05);
    TFT_SendData(0x09);
    TFT_SendData(0x09);
    TFT_SendData(0x08);
    TFT_SendData(0x14);
    TFT_SendData(0x28);
    TFT_SendData(0x33);
    TFT_SendData(0x3F);
    TFT_SendData(0x07);
    TFT_SendData(0x13);
    TFT_SendData(0x14);
    TFT_SendData(0x28);
    TFT_SendData(0x30);
    TFT_SetCmd(0XE1); //Set Gamma
    TFT_SendData(0xD0);
    TFT_SendData(0x05);
    TFT_SendData(0x09);
    TFT_SendData(0x09);
    TFT_SendData(0x08);
    TFT_SendData(0x03);
    TFT_SendData(0x24);
    TFT_SendData(0x32);
    TFT_SendData(0x32);
    TFT_SendData(0x3B);
    TFT_SendData(0x14);
    TFT_SendData(0x13);
    TFT_SendData(0x28);
    TFT_SendData(0x2F);
    TFT_SetCmd(0x21); 		//反显
    TFT_SetCmd(0x29);         //开启显示 

}


void TFT_full(u16 color)
{
    u32 ROW,column;
    TFT_SetCmd(0x2a);     //Column address set
    TFT_SendData(0x00);    //start column
    TFT_SendData(0x00); 
    TFT_SendData(0x00);    //end column
    TFT_SendData(0xF0);

    TFT_SetCmd(0x2b);     //Row address set
    TFT_SendData(0x00);    //start row
    TFT_SendData(0x00); 
    TFT_SendData(0x00);    //end row
    TFT_SendData(0xF0);
    TFT_SetCmd(0x2C);     //Memory write
    for(ROW=0;ROW<240;ROW++)             //ROW loop
    { 
        for(column=0;column<240 ;column++) //column loop
        {
            TFT_SendData(color>>8);
            TFT_SendData(color);
        }
    }
}
  

void ST7789_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{	

	TFT_SetCmd(0x2a);
	TFT_SendData(0x00);
	TFT_SendData(x_start);
	TFT_SendData(0x00);
	TFT_SendData(x_end);

	TFT_SetCmd(0x2b);
	TFT_SendData(0x00);
	TFT_SendData(y_start);
	TFT_SendData(0x00);
	TFT_SendData(y_end);	
	TFT_SetCmd(0x2c);
}

void ST7789_DrawPoint(u16 color)
{
    TFT_SendData(color>>8);
    TFT_SendData(color);
}


void TFT_full_DMA(u16 Color)
{
    u8 Data[480];
    u16 i;
    TFT_SetCmd(0x2a);     //Column address set
    TFT_SendData(0x00);    //start column
    TFT_SendData(0x00); 
    TFT_SendData(0x00);    //end column
    TFT_SendData(0xF0);

    TFT_SetCmd(0x2b);     //Row address set
    TFT_SendData(0x00);    //start row
    TFT_SendData(0x00); 
    TFT_SendData(0x00);    //end row
    TFT_SendData(0xF0);
    TFT_SetCmd(0x2C);     //Memory write

    for ( i = 0; i < 240; i++)
    {
       Data[i*2]=Color>>8;
       Data[i*2+1]=Color&0xff;
    }
    TFT_DATA;
    for ( i = 0; i < 240; i++)
    {
        TFT_DMA_Start((u32)Data,240*2);
    }

}

void TFT_SwapDataForDMA(u16 *Data)
{
    u16 Buf;

    Buf = *Data;

    *Data >>= 8;

    *Data |= (Buf&0xFF)<<8;

}



