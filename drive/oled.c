#include"IncludeFile.h"


												//  PB13-------SCLK          PB15------SDA
												//  PB12-------D/C           PB14------RST 

#define play_speed           100

u8 OLED_GRAM[8][128];

	
/*          8*8                        */
u8 num0[8]={0X00,0X00,0X7F,0X41,0X41,0X41,0X7F,0X00};
u8 num1[8]={0X00,0X00,0X42,0X42,0X7F,0X40,0X00,0X00};
u8 num2[8]={0X00,0X00,0X7B,0X49,0X49,0X49,0X4F,0X00};
u8 num3[8]={0X00,0X00,0X63,0X49,0X49,0X49,0X7F,0X00};
u8 num4[8]={0X00,0X00,0X0F,0X08,0X7E,0X08,0X08,0X00};
u8 num5[8]={0X00,0X00,0X4F,0X49,0X49,0X49,0X79,0X00};
u8 num6[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X79,0X00};
u8 num7[8]={0X00,0X00,0X01,0X01,0X7D,0X03,0X01,0X00};
u8 num8[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X7F,0X00};
u8 num9[8]={0X00,0X00,0X4F,0X49,0X49,0X49,0X7F,0X00};



u8 charA[8]={0X00,0X00,0X7C,0X12,0X11,0X12,0X7C,0X00};
u8 charB[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X36,0X00};
u8 charC[8]={0X00,0X00,0X3E,0X41,0X41,0X41,0X22,0X00};
u8 charD[8]={0X00,0X00,0X7F,0X41,0X41,0X41,0X22,0X1C};
u8 charE[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X49,0X00};
u8 charF[8]={0X00,0X00,0X7F,0X09,0X09,0X09,0X01,0X00};
u8 charG[8]={0X00,0X00,0X3E,0X41,0X59,0X49,0X32,0X00};
u8 charH[8]={0X00,0X00,0X7F,0X08,0X08,0X08,0X7F,0X00};
u8 charI[8]={0X00,0X00,0X41,0X41,0X7F,0X41,0X41,0X00};
u8 charJ[8]={0X00,0X00,0X31,0X41,0X21,0X1F,0X01,0X00};
u8 charK[8]={0X00,0X00,0X7F,0X08,0X14,0X22,0X41,0X00};
u8 charL[8]={0X00,0X00,0X7F,0X40,0X40,0X40,0X40,0X00};
u8 charM[8]={0X00,0X7F,0X02,0X04,0X04,0X02,0X7F,0X00};
u8 charN[8]={0X00,0X7F,0X02,0X04,0X08,0X10,0X7F,0X00};
u8 charO[8]={0X00,0X00,0X3E,0X41,0X41,0X41,0X3E,0X00};
u8 charP[8]={0X00,0X00,0X7F,0X09,0X09,0X09,0X06,0X00};
u8 charQ[8]={0X00,0X3E,0X41,0X41,0X51,0X3E,0X40,0X00};
u8 charR[8]={0X00,0X7F,0X09,0X19,0X29,0X46,0X00,0X00};
u8 charS[8]={0X00,0X4E,0X49,0X49,0X49,0X39,0X00,0X00};
u8 charT[8]={0X00,0X00,0X01,0X01,0X7F,0X01,0X01,0X00};
u8 charU[8]={0X00,0X00,0X3F,0X40,0X40,0X40,0X3F,0X00};
u8 charV[8]={0X00,0X00,0X1F,0X20,0X40,0X20,0X1F,0X00};
u8 charW[8]={0X00,0X3F,0X40,0X20,0X20,0X40,0X3F,0X00};
u8 charX[8]={0X00,0X42,0X24,0X18,0X18,0X24,0X42,0X00};
u8 charY[8]={0X00,0X01,0X02,0X04,0X78,0X04,0X02,0X01};	
u8 charZ[8]={0X00,0X00,0X61,0X51,0X49,0X45,0X43,0X00};																					
u8 charcolom[8]={0X00,0X00,0X00,0X66,0X66,0X00,0X00,0X00};    //冒号
u8 char_tempure[8]={0X03,0X03,0X1C,0X62,0X81,0X81,0X42,0X44};
u8 point[8]={0X00,0X00,0X00,0X60,0X60,0X00,0X00,0X00};	

//	
u8 windows[]=
{0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0X80,0X80,0X80,0X80,
0X80,0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XE0,0XF0,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X00,0X80,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0XC0,0XE0,0XF0,0XF8,0XFC,0X00,
0X02,0X02,0X7E,0X02,0X02,0X00,0X00,0X7E,0X04,0X08,0X04,0X7E,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7F,0X7F,0XBF,0X9F,0XDF,0XEF,0XE7,0XF7,0XFB,0XF7,0XF7,0XF7,
0XF7,0XEF,0XDF,0X9F,0XBF,0X7F,0X7F,0XFF,0XFF,0XFF,0X00,0XFF,0XFF,0XFF,0XFF,0XFE,
0XFE,0XFE,0XFE,0XFE,0XFE,0XFE,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X3F,0X3F,0X3F,0X3F,0X3F,
0X3F,0X3F,0X3F,0X3F,0X7F,0XFF,0XFF,0XFE,0XFE,0XFC,0X00,0XFD,0XFB,0XF7,0XFF,0XEF,
0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0XF7,0XF7,0XF7,0XF3,0XFB,0XFD,0XFD,0XFE,0XFE,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X1F,0X0F,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X07,0X07,0X08,0X1F,0X1F,0X3F,0X3F,0X7F,
0X7F,0X7F,0X7F,0X7F,0X7F,0X7F,0X7F,0X3F,0X3F,0X1F,0X4F,0X0F,0X07,0X03,0X01,0X00,
0X00,0X00,0X40,0X00,0X00,0XE0,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0XC0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,0X00,0XD8,0XD8,0X00,0X00,0X00,0XC0,
0X20,0X10,0X10,0X10,0X10,0X10,0X10,0X20,0XC0,0X00,0X80,0X40,0X20,0X20,0X20,0X20,
0X20,0X20,0X20,0XFE,0X00,0XE0,0X10,0X10,0X10,0X10,0X10,0X10,0X10,0XE0,0X00,0XF0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF0,0X00,0XE0,0X10,0X10,0X10,0X10,
0X10,0X10,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X04,0X10,0X40,0X10,
0X04,0X01,0X00,0X00,0X00,0XFF,0X08,0X08,0X08,0X08,0X08,0X08,0X08,0X07,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X02,0X04,0X08,0X10,0X20,0X20,0X10,0X08,0X02,0X01,0X00,0X01,0X02,0X08,0X10,0X20,
0X20,0X10,0X08,0X04,0X02,0X00,0X00,0X00,0X00,0X00,0X7F,0X7F,0X00,0X00,0X00,0X7F,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X1F,0X20,0X40,0X40,0X40,0X40,
0X40,0X40,0X40,0X3F,0X00,0X3F,0X40,0X40,0X40,0X40,0X40,0X40,0X40,0X3F,0X00,0X0F,
0X10,0X20,0X10,0X08,0X0C,0X08,0X10,0X20,0X10,0X0F,0X00,0X21,0X42,0X42,0X42,0X42,
0X42,0X42,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X04,0X01,0X00,0X01,
0X04,0X10,0X00,0X00,0X00,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};



	


	
void show_All()
{
				OLED_SetMode(0x21);           
				OLED_SetMode(0x00);	        
				OLED_SetMode(0x7f);	          
				delay_us(50);                     
				OLED_SetMode(0x22);	            
				OLED_SetMode(0x00);	          	
				OLED_SetMode(0x07);           
				delay_us(50);

}



void OLED_ClearScreen(u8 Data)
{
	memset(OLED_GRAM,Data,sizeof(OLED_GRAM));
	OLED_UpdateGRAM();
}

//void oled_spi_configinit()
//{
//	
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
//	
//	GPIO_InitTypeDef GPIOB_InitTypeDefinsture;
//	SPI_InitTypeDef SPI_InitTypeDefinsture;
//	
//	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;                 
//	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                        
//	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
//	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
//	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;

//	
//	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
//	
//	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;                
//	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
//	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
//	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
//	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
//	
//	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
//	
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);	
//	
//	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
//	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
//	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
//	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
//	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
//	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
//	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;
//	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
//	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

//	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

//	SPI_Cmd(SPI2 ,ENABLE);

//  SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_TXE,ENABLE);

//}

void OLED_SPI_Init()
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
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;                
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);	
	
	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;//32
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

	SPI_Cmd(SPI2 ,ENABLE);



}





void OLED_Init(void)
{

	OLED_SPI_Init();
	OLED_RST_ON;
	delay_ms(2);	
	OLED_RST_OFF;
	delay_ms(2);	

    OLED_SetMode(0XA8);
    OLED_SetMode(0X3F);
    OLED_SetMode(0XD3);
    OLED_SetMode(0X00);
    OLED_SetMode(0X40);
    OLED_SetMode(0Xd5);      //设置刷新频率和分频值
    OLED_SetMode(0Xf1);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
    OLED_SetMode(0XA0);      //A0--首列对应0      A1------首列对应127
    OLED_SetMode(0XC0);
    OLED_SetMode(0XDA);
    OLED_SetMode(0X12);
    OLED_SetMode(0X81);     //对比度设置
    OLED_SetMode(0Xff);     //设置对比度值
    OLED_SetMode(0XD9);
    OLED_SetMode(0XF1);
    OLED_SetMode(0XDB);
    OLED_SetMode(0X30);
    OLED_SetMode(0XA4);       //0xA4-正常      0XA5-全亮
    OLED_SetMode(0XA6);       //0XA6-正常      0XA7-反相
	OLED_SetMode(0x20);       /*设置显示模式                 参考：  https://blog.csdn.net/gengyuchao/article/details/86608037             */
	OLED_SetMode(0x00);	      /*[页地址----10b    水平模式---00b     垂直模式---01b        */	
	OLED_SetMode(0xc0);	    //0xc8---正常      0xc0------垂直反转  
	OLED_SetMode(0xa1);				
	OLED_SetMode(0x23);
	OLED_SetMode(0x00);          //[5:4]--00禁用闪烁或淡出       10使能消退      11使能闪烁                 [3:0]-----0000(8帧)  0001(16帧)     0010(16帧)。。。。1111(128帧)
	OLED_SetMode(0X8D);     //设置电荷泵
	OLED_SetMode(0X14);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0XAf);

	OLED_ClearScreen(0x00);	

}





void  display_position(u8 x,u8 y,u8 length)
{
		OLED_SetMode(0x21);                       //列地址 	
		OLED_SetMode(0x00|x);	                    //起始地址 	 0-127
		OLED_SetMode(0x00|(x+length*8)-1);	      //终止地址   

		OLED_SetMode(0x22);	                      //页地址	
		OLED_SetMode(0x00|y);	                    //起始地址	0-7
		OLED_SetMode(0x00|y);                     //终止地址
 	

}

void show_picture(u8 x_start,u8 y_start,u8 x_length,u8 y_length,u8* data)      //像素的坐标x_start ，y_start 宽度x_length,高度y_length 图像数组data
{

	u8 i=0,j=x_length*(y_length>>3);
	
		OLED_SetMode(0x21);                             //列地址 	
		OLED_SetMode(x_start);	                    //起始地址 	 0-127
		OLED_SetMode(x_length-1+x_start);	                      //终止地址   
	
		OLED_SetMode(0x22);	                           //页地址	
		OLED_SetMode(y_start);	                   //起始地址	0-7
		OLED_SetMode(((y_length>>3)-1)+y_start);                     //终止地址
 	
   for(i=0;i<j;i++)
	  OLED_SendData(data[i]);

	

}





void OLED_SendData(u8 Tdata)
{
		OLED_DATA;
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);             //非中断模式
		SPI_I2S_SendData(SPI2,Tdata);			
    	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);		
//		delay_us(5);

}

void OLED_SetMode(u8 Tdata)
{
	OLED_ORDER;	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);            //非中断模式
	SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
//	delay_us(5);

}

/*
设置扫描硬件频率：fre/div=越大越快，越小越闪屏
fre:0x00-0xff
div:0x00-0xff
*/
void OLED_SetScanFre(u8 fre,u8 div)    //闪烁设置fre[0-f]  div[0-f] 
{
    OLED_SetMode(0Xd5);                 //设置刷新频率和分频值  
    OLED_SetMode(0X00|fre<<4|div);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
}



/*
设置屏幕对比度(亮度)
value:0x00-0xff
*/
void OLED_CetContrast(u8 value)   
{
    OLED_SetMode(0X81);           //对比度设置
    OLED_SetMode(0X00|value);     //设置对比度值
}




void display_str_and_speed(char *word,u32 speed)
{

	while(*word!='\0')
	{	
	display_char(*word);
	word++;
	if(speed!=0)
	delay_ms(speed);	
	else 
		;
	}

}







void display_num(u8 number)
{

	char i;
switch(number)
		{
	case 0:
						for(i=0;i<8;i++)
						OLED_SendData(num0[i]);
						break ;
	
	
	case 1:
						for(i=0;i<8;i++)
						OLED_SendData(num1[i]);
						break ;
	
	
	case 2:
						for(i=0;i<8;i++)
						OLED_SendData(num2[i]);
						break ;
	
	
	
	case 3:
		
					for(i=0;i<8;i++)
					OLED_SendData(num3[i]);
					break ;
	
	
	case  4:
		
					for(i=0;i<8;i++)
					OLED_SendData(num4[i]);
					break ;
	
	
	case 5:
						for(i=0;i<8;i++)
						OLED_SendData(num5[i]);
						break ;
		
	
	
	case  6:
						for(i=0;i<8;i++)
						OLED_SendData(num6[i]);
						break ;	
	
	
	
	case  7:
						for(i=0;i<8;i++)
						OLED_SendData(num7[i]);
						break ;
	
	
	
	case 8:
						for(i=0;i<8;i++)
						OLED_SendData(num8[i]);
						break ;
	
	
	
	case 9:
						for(i=0;i<8;i++)
						OLED_SendData(num9[i]);
						break ;
	
	

		}
			  delay_us(50);	
}


void display_char(char alphabet)
{
	u8 i;

switch(alphabet)
		{

	case '0':
						for(i=0;i<8;i++)
						OLED_SendData(num0[i]);
						break ;
	
	
	case '1':
						for(i=0;i<8;i++)
						OLED_SendData(num1[i]);
						break ;
	
	
	case '2':
						for(i=0;i<8;i++)
						OLED_SendData(num2[i]);
						break ;
	
	
	
	case '3':
		
					for(i=0;i<8;i++)
					OLED_SendData(num3[i]);
					break ;
	
	
	case  '4':
		
					for(i=0;i<8;i++)
					OLED_SendData(num4[i]);
					break ;
	
	
	case '5':
						for(i=0;i<8;i++)
						OLED_SendData(num5[i]);
						break ;
		
	
	
	case  '6':
						for(i=0;i<8;i++)
						OLED_SendData(num6[i]);
						break ;	
	
	
	
	case  '7':
						for(i=0;i<8;i++)
						OLED_SendData(num7[i]);
						break ;
	
	
	
	case '8':
						for(i=0;i<8;i++)
						OLED_SendData(num8[i]);
						break ;
	
	
	
	case '9':
						for(i=0;i<8;i++)
						OLED_SendData(num9[i]);
						break ;			
			
			
			
			
			case 'A':
						for(i=0;i<8;i++)
						OLED_SendData(charA [i]);
						break ;



			case 'B':
						for(i=0;i<8;i++)
						OLED_SendData(charB [i]);
						break ;				
			
			
			
			case 'C':
						for(i=0;i<8;i++)
						OLED_SendData(charC [i]);
						break ;				
			
			
			
			case 'D':
						for(i=0;i<8;i++)
						OLED_SendData(charD [i]);
						break ;			
			
			
			case 'E':
						for(i=0;i<8;i++)
						OLED_SendData(charE [i]);
						break ;				
			
			
			case 'F':
						for(i=0;i<8;i++)
						OLED_SendData(charF [i]);
						break ;				
			
			
			case 'G':
						for(i=0;i<8;i++)
						OLED_SendData(charG [i]);
						break ;				
			
			
			case 'H':
						for(i=0;i<8;i++)
						OLED_SendData(charH [i]);
						break ;				
			
			
			
			case 'I':
						for(i=0;i<8;i++)
						OLED_SendData(charI [i]);
						break ;				
			
			
			case 'J':
						for(i=0;i<8;i++)
						OLED_SendData(charJ [i]);
						break ;				
			
			
			
			case 'K':
						for(i=0;i<8;i++)
						OLED_SendData(charK [i]);
						break ;				
			
			
			case 'L':
						for(i=0;i<8;i++)
						OLED_SendData(charL [i]);
						break ;				
			
			
			
			case 'M':
						for(i=0;i<8;i++)
						OLED_SendData(charM [i]);
						break ;				
			
			
			
			case 'N':
						for(i=0;i<8;i++)
						OLED_SendData(charN [i]);
						break ;				
			
			
			case 'O':
						for(i=0;i<8;i++)
						OLED_SendData(charO [i]);
						break ;				
			
			
			
			case 'P':
						for(i=0;i<8;i++)
						OLED_SendData(charP [i]);
						break ;				
			
			case 'Q':
						for(i=0;i<8;i++)
						OLED_SendData(charQ [i]);
						break ;				
			
					
			case 'R':
						for(i=0;i<8;i++)
						OLED_SendData(charR [i]);
						break ;				
			
			
			case 'S':
						for(i=0;i<8;i++)
						OLED_SendData(charS [i]);
						break ;				
			
			
			case 'T':
						for(i=0;i<8;i++)
						OLED_SendData(charT [i]);
						break ;				
			
			
			case 'U':
						for(i=0;i<8;i++)
						OLED_SendData(charU [i]);
						break ;				
			
			
			
			
			case 'V':
							for(i=0;i<8;i++)
						OLED_SendData(charV [i]);
						break ;			
			
			case 'W':
						for(i=0;i<8;i++)
						OLED_SendData(charW [i]);
						break ;				
					
			case 'X':
						for(i=0;i<8;i++)
						OLED_SendData(charX [i]);
						break ;				
			
			
			
			case 'Y':
						for(i=0;i<8;i++)
						OLED_SendData(charY [i]);
						break ;				
			
			case 'Z':
						for(i=0;i<8;i++)
						OLED_SendData(charZ [i]);
						break ;	
			
			case ' ':
						for(i=0;i<8;i++)
						OLED_SendData(0X00);
						break ;	
			
			case	':' :	                    ////  :
						for(i=0;i<8;i++)
						OLED_SendData(charcolom[i]);
						break ;	

			case	'.' :	                    //     .
						for(i=0;i<8;i++)
						OLED_SendData(point[i]);
						break ;		
			
			default :
						for(i=0;i<8;i++)
						OLED_SendData(point[i]);
				      break;
					
			
		}


}





void windows_open(u32 speed)
{
u32 i;
	for(i=0;i<896;i++)
	OLED_SendData(windows[i]);
	
	display_position(0,7,16);
	
	for(i=0;i<128;i++)
	{
	OLED_SendData(0xff);
	delay_ms(speed);        //进度条速度

	}
	OLED_ClearScreen(0x00);

}


void tempure_unit(void)            //   温度单位   .C
{
u8 i;
		for(i=0;i<8;i++)
		{
	OLED_SendData(char_tempure[i]);
		
		}
}








void power_on_check_display(void)
{
windows_open(10);                                //进度条速度
delay_ms(500);

OLED_ClearScreen(0x00);

OLED_SetScanFre(15,6);		
delay_ms(500);

//display_position(40,0,5);
//display_str_and_speed("CHECK",play_speed);
//delay_ms(200);
	


//从此处开始添加开机检查项目
	
//display_position(0,2,6);
//display_str_and_speed("18B20:",play_speed);
//delay_ms(500);	
//display_position(87,2,5);
//ds18B20_init(1);	                             //18B20
//delay_ms(500);



//display_position(0,4,4);
//display_str_and_speed("RTC:",play_speed);
//delay_ms(500);
//display_position(87,4,5);
//RTC_configinit();
//delay_ms(500);
//	
//	

//display_position(1,7,6);
//display_str_and_speed("POWER:",play_speed);
//delay_ms(500);
//display_position(87,7,2);
//display_str_and_speed("OK",play_speed);
//delay_ms(500);

//OLED_ClearScreen();	

//display_position(0,2,6);
//display_str_and_speed("VOICE:",play_speed);
//delay_ms(500);
//display_position(86,2,2);
//display_str_and_speed("OK",play_speed);
//delay_ms(500);





//display_position(0,4,5);
//display_str_and_speed("WIFI:",play_speed);
//delay_ms(500);
//display_position(87,4,2);
//display_str_and_speed("OK",play_speed);
//delay_ms(500);



//display_position(1,6,7);
//display_str_and_speed("SENSOR:",play_speed);
//delay_ms(500);
//display_position(87,6,2);

//display_str_and_speed("OK",play_speed);
//delay_ms(500);

//OLED_ClearScreen();

//display_position(1,8,4);
//display_str_and_speed("LED:",play_speed);
//delay_ms(500);
//display_position(87,8,5);
//display_str_and_speed("READY",play_speed);

////delay_ms(500);


// OLED_ClearScreen();	



//<-------此处检查完毕

display_position(1,4,13);
display_str_and_speed("ENTER SYSTEM:",play_speed);
delay_ms(500);
delay_ms(500);
display_position(105,4,2);
display_str_and_speed("..",100);
delay_ms(500);
OLED_SetScanFre(15,0);		                 
//OLED_ClearScreen();	

}


















void OLED_Draw_Point(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)
		return;
	pos=7-y/8; 
	bx=y%8;     
	temp=1<<(7-bx); 
	if(t)
		OLED_GRAM[pos][x]|=temp;  
	else 
		OLED_GRAM[pos][x]&=~temp;        

}




void OLED_UpdateGRAM()
{
	u8 i,j;
	OLED_SetMode(0x21);           
	OLED_SetMode(0x00);	        
	OLED_SetMode(0x7f);	          
	delay_us(5);                     
	OLED_SetMode(0x22);	            
	OLED_SetMode(0x00);	          	
	OLED_SetMode(0x07);           
	delay_us(5);

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_SendData(OLED_GRAM[i][j]);
		}
	}
}





//六角星
void Boot_Animation(void)
{
		static u8 x=0,y=0;
		for(x = 63;x>=18;x--){
				OLED_Draw_Point(108-0.7*x,x,1);//Draw a diagonal line ≈√3/3
				OLED_Draw_Point(17 +0.7*x,x,1);
				y = 64-x;
				OLED_Draw_Point(64-0.7*y,y,1);
				OLED_Draw_Point(64+0.7*y,y,1);
				delay_ms(2);
			  	OLED_UpdateGRAM();
		}
		
		for(x = 30;x <= 94;x++){
				OLED_Draw_Point(125-x,47,1);
				OLED_Draw_Point(x,18,1);
				delay_ms(2);
				OLED_UpdateGRAM();
		}
		delay_ms(100);
		
}


















