#include "IncludeFile.h"



static void TFT_IOInit()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_InitTypeDefinsture;
	SPI_InitTypeDef SPI_InitTypeDefinsture;
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;                 
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                        
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_11;                
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);	
	
	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_1Line_Tx;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;  
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

	SPI_Cmd(SPI2 ,ENABLE);

}

static void TFT_SendData(u8 Data)
{
	TFT_DATA;	
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);
	SPI_I2S_SendData(SPI2,Data);		
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);      
}

static void TFT_SetCmd(u8 CMD)
{
	TFT_CMD;	
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
	SPI_I2S_SendData(SPI2,CMD);	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);           
}


void TFT_Init()
{

    TFT_IOInit();

    TFT_RST_OFF;
	Delay_ms(500);
	TFT_RST_ON;
	Delay_ms(500);
    TFT_SetCmd(0x11); 			//Sleep Out
	Delay_ms(120);               //DELAY120ms 

    TFT_SetCmd(0x3A);        //65k mode
    TFT_SendData(0x05);
    TFT_SetCmd(0xC5); 		//VCOM
    TFT_SendData(0x1A);
    TFT_SetCmd(0x36);                 // 屏幕显示方向设置
    TFT_SendData(0x00);
    //-------------ST7789V Frame rate setting-----------//
    TFT_SetCmd(0xb2);		//Porch Setting
    TFT_SendData(0x05);
    TFT_SendData(0x05);
    TFT_SendData(0x00);
    TFT_SendData(0x33);
    TFT_SendData(0x33);

    TFT_SetCmd(0xb7);			//Gate Control
    TFT_SendData(0x05);			//12.2v   -10.43v
    //--------------ST7789V Power setting---------------//
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
    //---------------ST7789V gamma setting-------------//
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
  



