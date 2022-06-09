#include "IncludeFile.h"


//  PB13-------SCLK          PB15------SDA
//  PB12-------D/C           PB14------RST 

#if (USE_U8G2 == FALSE)

u8 OLED_GRAM[8][128];

/*
阴码 列行 顺向 8*16
*/
u8 CharModel[][16]=
{


	{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x00,0x00},/*"!",0*/
	{0x00,0x08,0x30,0x40,0x08,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",1*/
	{0x00,0x02,0x03,0x1E,0x02,0x03,0x1E,0x00,0x00,0x20,0xFC,0x20,0x20,0xFC,0x20,0x00},/*"#",2*/
	{0x00,0x0E,0x11,0x11,0x3F,0x10,0x0C,0x00,0x00,0x18,0x04,0x04,0xFF,0x84,0x78,0x00},/*"$",3*/
	{0x0F,0x10,0x0F,0x01,0x06,0x18,0x00,0x00,0x00,0x8C,0x30,0xC0,0x78,0x84,0x78,0x00},/*"%",4*/
	{0x00,0x0F,0x10,0x11,0x0E,0x00,0x00,0x00,0x78,0x84,0xC4,0x34,0x98,0xE4,0x84,0x08},/*"&",5*/
	{0x00,0x48,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",6*/
	{0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00},/*"(",7*/
	{0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00},/*")",8*/
	{0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00},/*"*",9*/
	{0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xF0,0x80,0x80,0x80},/*"+",10*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x0E,0x00,0x00,0x00,0x00,0x00},/*",",11*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00},/*"-",12*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00},/*".",13*/
	{0x00,0x00,0x00,0x00,0x03,0x1C,0x20,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00},/*"/",14*/


	{0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00,0x00,0xF0,0x08,0x04,0x04,0x08,0xF0,0x00},/*"0",0*/
	{0x00,0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00},/*"1",1*/
	{0x00,0x0E,0x10,0x10,0x10,0x10,0x0F,0x00,0x00,0x0C,0x14,0x24,0x44,0x84,0x0C,0x00},/*"2",2*/
	{0x00,0x0C,0x10,0x10,0x10,0x11,0x0E,0x00,0x00,0x18,0x04,0x84,0x84,0x44,0x38,0x00},/*"3",3*/
	{0x00,0x00,0x01,0x02,0x0C,0x1F,0x00,0x00,0x00,0x60,0xA0,0x24,0x24,0xFC,0x24,0x24},/*"4",4*/
	{0x00,0x1F,0x11,0x11,0x11,0x10,0x10,0x00,0x00,0x98,0x04,0x04,0x04,0x88,0x70,0x00},/*"5",5*/
	{0x00,0x07,0x08,0x11,0x11,0x09,0x00,0x00,0x00,0xF0,0x88,0x04,0x04,0x04,0xF8,0x00},/*"6",6*/
	{0x00,0x18,0x10,0x10,0x11,0x16,0x18,0x00,0x00,0x00,0x00,0x7C,0x80,0x00,0x00,0x00},/*"7",7*/
	{0x00,0x0E,0x11,0x10,0x10,0x11,0x0E,0x00,0x00,0x38,0x44,0x84,0x84,0x44,0x38,0x00},/*"8",8*/
	{0x00,0x0F,0x10,0x10,0x10,0x08,0x07,0x00,0x00,0x80,0x48,0x44,0x44,0x88,0xF0,0x00},/*"9",9*/


	{0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00},/*":",0*/
	{0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00},/*";",1*/
	{0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x00},/*"<",2*/
	{0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00},/*"=",3*/
	{0x00,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x80,0x00},/*">",4*/
	{0x00,0x0E,0x12,0x10,0x10,0x11,0x0E,0x00,0x00,0x00,0x00,0x0C,0xEC,0x00,0x00,0x00},/*"?",5*/
	{0x03,0x0C,0x13,0x14,0x17,0x08,0x07,0x00,0xE0,0x18,0xE4,0x14,0xF4,0x14,0xE8,0x00},/*"@",6*/



	{0x00,0x00,0x03,0x1C,0x07,0x00,0x00,0x00,0x04,0x3C,0xC4,0x40,0x40,0xE4,0x1C,0x04},/*"A",0*/
	{0x10,0x1F,0x11,0x11,0x11,0x0E,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x88,0x70,0x00},/*"B",1*/
	{0x03,0x0C,0x10,0x10,0x10,0x10,0x1C,0x00,0xE0,0x18,0x04,0x04,0x04,0x08,0x10,0x00},/*"C",2*/
	{0x10,0x1F,0x10,0x10,0x10,0x08,0x07,0x00,0x04,0xFC,0x04,0x04,0x04,0x08,0xF0,0x00},/*"D",3*/
	{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x04,0xC4,0x04,0x18,0x00},/*"E",4*/
	{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x00,0xC0,0x00,0x00,0x00},/*"F",5*/
	{0x03,0x0C,0x10,0x10,0x10,0x1C,0x00,0x00,0xE0,0x18,0x04,0x04,0x44,0x78,0x40,0x00},/*"G",6*/
	{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x04,0xFC,0x84,0x80,0x80,0x84,0xFC,0x04},/*"H",7*/
	{0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"I",8*/
	{0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00,0x00},/*"J",9*/
	{0x10,0x1F,0x11,0x03,0x14,0x18,0x10,0x00,0x04,0xFC,0x04,0x80,0x64,0x1C,0x04,0x00},/*"K",10*/
	{0x10,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x04,0x0C,0x00},/*"L",11*/
	{0x10,0x1F,0x1F,0x00,0x1F,0x1F,0x10,0x00,0x04,0xFC,0x80,0x7C,0x80,0xFC,0x04,0x00},/*"M",12*/
	{0x10,0x1F,0x0C,0x03,0x00,0x10,0x1F,0x10,0x04,0xFC,0x04,0x00,0xE0,0x18,0xFC,0x00},/*"N",13*/
	{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00},/*"O",14*/
	{0x10,0x1F,0x10,0x10,0x10,0x10,0x0F,0x00,0x04,0xFC,0x84,0x80,0x80,0x80,0x00,0x00},/*"P",15*/
	{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x14,0x14,0x0C,0x0A,0xF2,0x00},/*"Q",16*/
	{0x10,0x1F,0x11,0x11,0x11,0x11,0x0E,0x00,0x04,0xFC,0x04,0x00,0xC0,0x30,0x0C,0x04},/*"R",17*/
	{0x00,0x0E,0x11,0x10,0x10,0x10,0x1C,0x00,0x00,0x1C,0x04,0x84,0x84,0x44,0x38,0x00},/*"S",18*/
	{0x18,0x10,0x10,0x1F,0x10,0x10,0x18,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"T",19*/
	{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"U",20*/
	{0x10,0x1E,0x11,0x00,0x00,0x13,0x1C,0x10,0x00,0x00,0xE0,0x1C,0x70,0x80,0x00,0x00},/*"V",21*/
	{0x10,0x1F,0x00,0x1F,0x00,0x1F,0x10,0x00,0x00,0xC0,0x7C,0x80,0x7C,0xC0,0x00,0x00},/*"W",22*/
	{0x10,0x18,0x16,0x01,0x01,0x16,0x18,0x10,0x04,0x0C,0x34,0xC0,0xC0,0x34,0x0C,0x04},/*"X",23*/
	{0x10,0x1C,0x13,0x00,0x13,0x1C,0x10,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"Y",24*/
	{0x08,0x10,0x10,0x10,0x13,0x1C,0x10,0x00,0x04,0x1C,0x64,0x84,0x04,0x04,0x18,0x00},/*"Z",25*/

	{0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00},/*"[",0*/
	{0x00,0x20,0x1C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x1C,0x03,0x00},/*"\",1*/
	{0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00},/*"]",2*/
	{0x00,0x00,0x20,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",3*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},/*"_",4*/
	{0x00,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",5*/

	{0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x98,0x24,0x24,0x48,0xFC,0x04,0x00},/*"a",0*/
	{0x08,0x0F,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0xFC,0x88,0x04,0x04,0x88,0x70,0x00},/*"b",1*/
	{0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x70,0x88,0x04,0x04,0x04,0x88,0x00},/*"c",2*/
	{0x00,0x00,0x01,0x01,0x01,0x09,0x0F,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"d",3*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x24,0x24,0x24,0x24,0xE8,0x00},/*"e",4*/
	{0x00,0x01,0x01,0x07,0x09,0x09,0x04,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"f",5*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xD6,0x29,0x29,0x29,0xC9,0x06,0x00},/*"g",6*/
	{0x08,0x0F,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"h",7*/
	{0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"i",8*/
	{0x00,0x00,0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00},/*"j",9*/
	{0x08,0x0F,0x00,0x00,0x01,0x01,0x01,0x00,0x04,0xFC,0x24,0x60,0x94,0x0C,0x04,0x00},/*"k",10*/
	{0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"l",11*/
	{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x04,0xFC,0x04,0x00,0xFC,0x04,0x00,0xFC},/*"m",12*/
	{0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"n",13*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"o",14*/
	{0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x01,0xFF,0x89,0x04,0x04,0x88,0x70,0x00},/*"p",15*/
	{0x00,0x00,0x00,0x01,0x01,0x00,0x01,0x00,0x00,0x70,0x88,0x04,0x04,0x89,0xFF,0x01},/*"q",16*/
	{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x04,0x04,0xFC,0x84,0x04,0x00,0x80,0x00},/*"r",17*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xCC,0x24,0x24,0x24,0x24,0x98,0x00},/*"s",18*/
	{0x00,0x01,0x01,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0xF8,0x04,0x04,0x08,0x00},/*"t",19*/
	{0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"u",20*/
	{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0xC0,0x30,0x0C,0x30,0xC0,0x00,0x00},/*"v",21*/
	{0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x80,0x70,0x0C,0x30,0xE0,0x1C,0x60,0x80},/*"w",22*/
	{0x00,0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x04,0x8C,0x70,0x74,0x8C,0x04,0x00},/*"x",23*/
	{0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x00,0x81,0x61,0x1E,0x18,0x60,0x80,0x00},/*"y",24*/
	{0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x84,0x0C,0x34,0x44,0x84,0x0C,0x00},/*"z",25*/

	{0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02},/*"{",0*/
	{0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00},/*"|",1*/
	{0x40,0x40,0x3F,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00},/*"}",2*/
	{0x00,0x40,0x80,0x40,0x40,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",3*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"空格*/
	{0xFF,0x80,0x9F,0x9F,0x9F,0x9F,0x80,0xFF,0xFF,0x01,0xF1,0xF1,0xF1,0xF1,0x01,0xFF},/*"未知字符*/
};
#endif


	

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
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;  
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

	SPI_Cmd(SPI2 ,ENABLE);



}





void OLED_Init(void)
{

	OLED_SPI_Init();
	OLED_RST_ON;
	Delay_us(5);	
	OLED_RST_OFF;
	Delay_us(5);	

    OLED_SetMode(0xA8);
    OLED_SetMode(0x3F);
    OLED_SetMode(0xD3);
    OLED_SetMode(0x00);
    OLED_SetMode(0x40);
    OLED_SetMode(0xd5);      //设置刷新频率和分频值
    OLED_SetMode(0xf1);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
    OLED_SetMode(0xA0);      //A0--首列对应0      A1------首列对应127
    OLED_SetMode(0xC0);
    OLED_SetMode(0xDA);
    OLED_SetMode(0x12);
    OLED_SetMode(0x81);     //对比度设置
    OLED_SetMode(0xff);     //设置对比度值
    OLED_SetMode(0xD9);
    OLED_SetMode(0xF1);
    OLED_SetMode(0xDB);
    OLED_SetMode(0x30);
    OLED_SetMode(0xA4);       //0xA4-正常      0xA5-全亮
    OLED_SetMode(0xA6);       //0xA6-正常      0xA7-反相
	OLED_SetMode(0x20);       /*设置显示模式                 参考：  https://blog.csdn.net/gengyuchao/article/details/86608037             */
	OLED_SetMode(0x00);	      /*[页地址----10b    水平模式---00b     垂直模式---01b        */	
	OLED_SetMode(0xc0);	     //0xc8---正常      0xc0------垂直反转  
	OLED_SetMode(0xa1);				
	OLED_SetMode(0x23);
	OLED_SetMode(0x00);        //[5:4]--00禁用闪烁或淡出       10使能消退      11使能闪烁                 [3:0]-----0000(8帧)  0001(16帧)     0010(16帧)。。。。1111(128帧)
	OLED_SetMode(0x8D);     //设置电荷泵
	OLED_SetMode(0x14);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0xAf);



#if (USE_U8G2 == FALSE)
	OLED_ClearScreen(0x00);	
#else
	u8 i,j;
	OLED_SetMode(0x22);	            
	OLED_SetMode(0x00);	          	
	OLED_SetMode(0x07);           
	OLED_SetMode(0x21);           
	OLED_SetMode(0x00);	        
	OLED_SetMode(0x7f);
	Delay_us(2);  
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_SendData(0);
		}
	}
#endif

}



void OLED_SendData(u8 Tdata)
{
	OLED_DATA;	
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);
	SPI_I2S_SendData(SPI2,Tdata);		
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);      
}

void OLED_SetMode(u8 Tdata)
{
	OLED_ORDER;	
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
	SPI_I2S_SendData(SPI2,Tdata);	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);           
}

/*
打开显示
只打开显示屏幕的电源，保留GDDRAM
*/
void OLED_TurnON()
{
	OLED_SetMode(0x8D);     //设置电荷泵
	OLED_SetMode(0x14);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0xAF);

}

/*
关闭显示
只关闭显示屏幕的电源，保留GDDRAM
*/
void OLED_TurnOFF()
{
	OLED_SetMode(0x8D);     //设置电荷泵
	OLED_SetMode(0x10);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0xAE);
}



void OLED_ScrollStart()
{

	OLED_SetMode(0x2F);

}
void OLED_ScrollStop()
{

	OLED_SetMode(0x2E);

}

/*
左右滚屏设置
Direction：SCROLL_R[向右]   SCROLL_L[向左] 
FrameFrq：0x00-0x07  多少帧滚动一次
PageStart~PageEnd
*/
void OLED_Scroll_LR(u8 Direction,u8 FrameFrq,u8 PageStart,u8 PageEnd)
{
	OLED_SetMode(0x2E);
    OLED_SetMode(Direction);
    OLED_SetMode(0x00);
    OLED_SetMode(PageStart);
    OLED_SetMode(FrameFrq);
    OLED_SetMode(PageEnd);
    OLED_SetMode(0x00);	
    OLED_SetMode(0xFF);		
	OLED_SetMode(0x2F);

}


/*
垂直滚屏设置：无法单独垂直滚屏，必须带左右移动
Direction：SCROLL_VR[垂直向右]   SCROLL_VL[垂直向左] 
FrameFrq：0x00-0x07  多少帧滚动一次
Offset：垂直偏移[1-63]
PageStart~PageEnd[指左右滚屏的范围]
*/
void OLED_Scroll_Vx(u8 Direction,u8 FrameFrq,u8 Offset,u8 PageStart,u8 PageEnd)
{
	OLED_SetMode(0x2E);
    OLED_SetMode(Direction);
    OLED_SetMode(0x00);
    OLED_SetMode(PageStart);
    OLED_SetMode(FrameFrq);
    OLED_SetMode(PageEnd);
    OLED_SetMode(Offset);		
	OLED_SetMode(0x2F);

}


/*
设置扫描硬件频率：fre/div=越大越快，越小越闪屏
fre:0x00-0xff
div:0x00-0xff
*/
void OLED_SetScanFre(u8 fre,u8 div)    //闪烁设置fre[0-f]  div[0-f] 
{
    OLED_SetMode(0xd5);                 //设置刷新频率和分频值  
    OLED_SetMode(0x00|fre<<4|div);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
}

void OLED_SetChargePre(u8 Data)
{
    OLED_SetMode(0xD9);      //预充电周期设置
    OLED_SetMode(Data);     //设置预充电周期
}

//		0x00
//		0x10
//		0x30
void OLED_SetVcomLevel(u8 Data)
{
    OLED_SetMode(0xDB);      //
    OLED_SetMode(Data);     //
}



/*
设置屏幕对比度(亮度)
value:0x00-0xff
*/
void OLED_SetContrast(u8 value)   
{
    OLED_SetMode(0x81);           //对比度设置
    OLED_SetMode(value);     //设置对比度值
}


/*
设置闪烁模式：
Twink_Mode  闪烁模式
Hidden_Mode 消退模式
0x00        关闭

Speed 0-15   越小越快
*/
void OLED_SetTwinkMode(u8 Mode,u8 Speed)
{

    OLED_SetMode(0x23);             //闪烁设置
    OLED_SetMode(Mode|Speed);     	//设置对比度值

}




#if (USE_U8G2 == FALSE)

void OLED_ClearScreen(u8 Data)
{
	memset(OLED_GRAM,Data,sizeof(OLED_GRAM));
	OLED_UpdateGRAM();
}

void OLED_UpdateGRAM()
{
	u8 i,j;
	OLED_SetMode(0x22);	            
	OLED_SetMode(0x00);	          	
	OLED_SetMode(0x07);           
	OLED_SetMode(0x21);           
	OLED_SetMode(0x00);	        
	OLED_SetMode(0x7f);
	Delay_us(2);  
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_SendData(OLED_GRAM[i][j]);
		}
	}
}

void windows_open(u32 speed)
{
u32 i;
	for(i=0;i<896;i++)
//	OLED_SendData(windows[i]);
	
	//display_position(0,7,16);
	
	for(i=0;i<128;i++)
	{
	OLED_SendData(0xff);
	Delay_ms(speed);        //进度条速度

	}
	OLED_ClearScreen(0x00);

}


void tempure_unit(void)            //   温度单位   .C
{
u8 i;
		for(i=0;i<8;i++)
		{
///	OLED_SendData(char_tempure[i]);
		
		}
}



void OLED_Draw_Point(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;

	if(x>127||y>63)
		return;
	pos=y/8; 
	bx=y%8;     
	temp=1<<bx;
	if(t)
		OLED_GRAM[pos][x]|=temp;  
	else 
		OLED_GRAM[pos][x]&=~temp;        

}


u8 OLED_Get_Point(u8 x,u8 y)
{

	u8 pos,bx,temp=0;
    
	pos=y/8; 
	bx=y%8;     
	temp=1<<bx;

	temp &= OLED_GRAM[pos][x];

	if(temp)
		return 1;
	else 
		return 0;     


}


void OLED_Data2GRAM(u8 *Data,u16 length)
{
	u8 i,j;
	u16 k=0;

	if(length>1024)
	return;

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_GRAM[i][j]=Data[k++];
			if(k>length)
			return;
		}
	}

}

void OLED_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2)
{
	unsigned int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 

	if(delta_x>0)
	{
		incx=1; //设置单步方向 
	}		
	else if(delta_x==0)
	{
		incx=0;//垂直线 
	}
	else 
	{
		incx=-1;delta_x=-delta_x;
	} 

	if(delta_y>0)
	{
		incy=1; 
	}
	else if(delta_y==0)
	{
		incy=0;
	}//水平线 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 

	if( delta_x>delta_y)
	{
		distance=delta_x; //选取基本增量坐标轴 
	}
	else 
	{
		distance=delta_y; 
	}
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		OLED_Draw_Point(uRow,uCol,1);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 



void OLED_Draw_Circle(u8 x0,u8 y0,u8 r) 
{
	u8 x,y;
	for(x = 0;x <= 63;x++)
	{
		y = sqrt(pow(r,2)-pow(x-x0,2))+y0; //圆方程  x,y反置
		OLED_Draw_Point(y,x,1);      //上半圆
		OLED_Draw_Point(63-y,x,1);   //下半圆
	}
}


void OLED_Draw_FullCircle(u16 x0,u16 y0,u8 r)
{
	s16 a,b;
	s16 di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		s16 i = a,p = b;

		while(i>0)
		{		
			OLED_Draw_Point(x0+b,y0-i,1);
			OLED_Draw_Point(x0-i,y0+b,1);
			i--;
		}		
		while(p>0)
		{		
			OLED_Draw_Point(x0-a,y0-p,1);
			OLED_Draw_Point(x0-p,y0-a,1);
			OLED_Draw_Point(x0+a,y0-p,1);
			OLED_Draw_Point(x0-p,y0+a,1);
			OLED_Draw_Point(x0+a,y0+p,1);
			OLED_Draw_Point(x0+p,y0+a,1);
			p--;
		}

		a++;
		//Bresenham算法画圆    
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	OLED_Draw_Point(x0,y0,1); //圆心坐标
}

//六角星
void Boot_Animation(void)
{
		static u8 x=0,y=0;
		for(x = 63;x>=18;x--)
		{
				OLED_Draw_Point(108-0.7*x,x,1);//Draw a diagonal line ≈√3/3
				OLED_Draw_Point(17 +0.7*x,x,1);
				y = 64-x;
				OLED_Draw_Point(64-0.7*y,y,1);
				OLED_Draw_Point(64+0.7*y,y,1);
				Delay_ms(20);
			  	OLED_UpdateGRAM();
		}
		for(x = 30;x <= 94;x++)
		{
				OLED_Draw_Point(125-x,47,1);
				OLED_Draw_Point(x,18,1);
				Delay_ms(20);
				OLED_UpdateGRAM();
		}
		
}



void OLED_ShowChar(u8 x,u8 y,u8* Data)
{
	u8 k,l;
	for(k=0;k<2;k++)
	{
		for(l=0;l<8;l++)
			OLED_GRAM[7-k-y*2][l+x]  = Data[k*8+l];          //或关系待验证
	}

}


/*
 x:0-119 (每个字符8像素宽度，起始坐标超过119无法完整显示一个字符)
 y:0-3 (每个字符高度16像素，最多4行字符)
Length：字符串长度
当显示长度超过一行(最多16个)时，自动换行
单屏最多64个(8*16尺寸的字符)
*/
void OLED_ShowStrings(u8 x,u8 y,char* Data,u8 Length)
{	
	u8 PositionBuff[64];
	u8 i=0;

	if( Length > 64 || Length == 0 )
	 	return;   			

	while( i < Length )
	{
		if( '!' <= Data[i] &&  Data[i] <= '~')
		{
			PositionBuff[i]=Data[i]-'!';
		}
		else if(' ' == Data[i])
		{
			PositionBuff[i]=94; 
		}
		else
		{
			PositionBuff[i]=95;
		}

		i++;
	}

	for(i=0;i<Length;i++)
	{

		if(x>120)
		{
			x=0;
			y++;
			if(y>3)
				y=0; 
		}
		OLED_ShowChar(x,y,&CharModel[PositionBuff[i]][0]);
		x+=8;
	}

}




/*
Bit:数字位数
向右对齐，超出的位数部分不显示
*/
void OLED_ShowNumber(u8 x,u8 y,u16 Num,u8 Bit)
{
	char Temp[8];
	char ShiftTemp[8];
	u8 i;

	sprintf(Temp,"%d",Num);
	memset(ShiftTemp,' ',sizeof(ShiftTemp));
	for(i=0;i<sizeof(Temp);i++)
	{
		if(Temp[i] == '\0' )
		break;
	}
	memcpy(&ShiftTemp[Bit-i],Temp,i);
	OLED_ShowStrings(x,y,ShiftTemp,Bit);
}

//更新某一字符的某一列的数据
//High:字高(BIT)
//p:字符在字模数组中的位置，offset 字符内列数据偏移
void UpdateOneColumn(u8 x,u8 y,u8 High,u8 p,u8 offset)
{
	u8 i;

	for(i=0;i<High/8;i++)
	{
		OLED_GRAM[7-i-y*2][x]  = CharModel[p][offset];        
		offset+=8;
	}
}





void OLED_MoveDisplay(u8 x,u8 y,u8 High,u8 num,u8 *p)
{

	u8 x_Buff=x;
	u8 i=0;
	u8 *Data=p;
	u16 cnt=0,offset = 0;

	while(1)
	{
		for(cnt=0,i=x_Buff;i<128;i++)
		{
//			UpdateOneColumn(i,y,High,(u8)(Data-'!'), cnt++);

			if( cnt % 8 )
			{
				Data++;
			}

			OLED_UpdateGRAM();
			Delay_ms(500);
		}



		x_Buff--;

		if(x_Buff <= 0)
		{
			x_Buff = 0;
			//Data ++;
			cnt++;
		}

		offset++;
		
		//if(offset >= num*High+128)
		if(offset >= num*8+128)
		{
			offset = 0;
			Data=p;
			x_Buff = x;
		}
	}

}

#endif


