#include "delay.h"
#include "oled.h"
#include "stm32f4xx.h"
#include "ds18b20.h"
#include "RTC.h"
#include "usart.h"
#include "led.h"




												//  PB13-------SCLK          PB15------SDA
												//  PB12-------D/C           PB14------RST 

#define play_speed           100


u8 wen[]={0x00,0x00,0x04,0x20,0x46,0x3C,0x21,0xC4,0x0E,0x04,0x00,0xFC,0x3F,0x84,0x2A,0x84,0x2A,0x7C,0x2A,0x84,0x2A,0x7C,0x2A,0x84,0x3E,0x84,0x00,0xFC,0x00,0x04,0x00,0x00};//温//
u8 du[]={0x00,0x00,0x00,0x08,0x3F,0xF0,0x20,0x00,0x24,0x04,0x24,0x04,0x1F,0x44,0x25,0x68,0x65,0x58,0x25,0x58,0x15,0x68,0x2F,0xC4,0x24,0x04,0x2C,0x04,0x04,0x04,0x00,0x00}; //度//
u8 shi[]={0x00,0x00,0x04,0x00,0x46,0x7C,0x31,0x80,0x0E,0x04,0x00,0x44,0x3E,0x34,0x2A,0x04,0x2B,0xFC,0x2A,0x04,0x2B,0xFC,0x2B,0x14,0x2A,0x24,0x3E,0x44,0x00,0x84,0x00,0x00};//湿//
u8 set_icon[]={0x80,0x90,0xB8,0xF0,0xFE,0xFF,0x7E,0x1F,0x1F,0x1F,
	                0x1E,0x7E,0xFF,0xFE,0xF8,0xF8,0x90,0xC0,0xC0,0x80,
	                0xC0,0xC0,0x00,0x00,0x00,0x00,0x0B,0x1B,0x1F,0x7F,
                  0xFF,0xFE,0x78,0xF8,0xF8,0xF8,0x7E,0xFF,0x7F,0x1F,
                  0x1F,0x3F,0x3F,0x3B,0x71,0x7B,0x1F,0x1F,0x1B,0x00};
u8 tempure_icon[]={0x00,0x00,0x00,0xF8,0xFE,0x06,0x03,0x03,0x03,0x06,0xFE,0xF8,0x20,0x30,0x00,0x00,
	                    0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x18,0x18,0x00,0x00,
	                    0x00,0xC0,0xF0,0x3F,0xDF,0xE0,0xFE,0xFE,0xFE,0xE0,0xDF,0x3F,0xF6,0xC6,0x00,0x00,
                      0x00,0x07,0x0F,0x18,0x37,0x6F,0x6F,0x6F,0x6F,0x6F,0x37,0x18,0x0F,0x07,0x00,0x00};	



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
0X04,0X10,0X00,0X00,0X00,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};




void draw_point(u8 x,u8 y)
{
	u8 temp=0x00;
	
		temp|=(0x01<<(y%8));
		oled_sendorder(0x21);                       //列地址 	
		oled_sendorder(0x00|x);	                    //起始地址 	 0-127
		oled_sendorder(0x00|x);	                    //终止地址   
		oled_sendorder(0x22);	                      //页地址	
		oled_sendorder(0x00|y/8);	                  //起始地址	0-7
		oled_sendorder(0x00|y/8);  
	  	oled_senddata(temp);

}	
	
	
void Vertical_reversal(u32 state)
{
		  oled_sendorder(state); 

}
	
void oled_initMode(u32 oledMode)
{
	
switch(oledMode)
 {	
  	case 0x00 :
		oled_sendorder(0x20);       /*设置显示模式                 参考：  https://blog.csdn.net/gengyuchao/article/details/86608037             */
		oled_sendorder(0x00);	      /*[页地址----10b    水平模式---00b     垂直模式---01b        */
    break;
		
		case 0x02 :
		oled_sendorder(0x20);      
		oled_sendorder(0x02);	     
    break;

		case 0x01 :
		oled_sendorder(0x20);      
		oled_sendorder(0x01);	 
		break;
		
		default:
		break ;
		
	}
}
	
void show_All()
{
				oled_sendorder(0x21);           
				oled_sendorder(0x00);	        
				oled_sendorder(0x7f);	          
				delay_us(50);                     
				oled_sendorder(0x22);	            
				oled_sendorder(0x00);	          	
				oled_sendorder(0x07);           
				delay_us(50);

}



void clear_screen()
{
 u32 i;

				oled_sendorder(0x21);           
				oled_sendorder(0x00);	        
				oled_sendorder(0x7f);	          
				delay_us(50);                     
				oled_sendorder(0x22);	            
				oled_sendorder(0x00);	          	
				oled_sendorder(0x07);           
				delay_us(50);
				
				for(i=0;i<1024;i++)
				{
					oled_senddata(0x00);


				}

}

void oled_spi_configinit()
{
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	
//	NVIC_InitTypeDef  NVIC_Initstr;	
	
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
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

	SPI_Cmd(SPI2 ,ENABLE);

  SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_TXE,ENABLE);

//	NVIC_Initstr.NVIC_IRQChannel=SPI2_IRQn;
//	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
//	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;

//	NVIC_Init(&NVIC_Initstr);
//	

//SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_RXNE,ENABLE);

		//SPI_I2S_SendData(SPI2,0X00);
}

void oled_init(void)
{



	
		oled_spi_configinit();
		OLED_RST_ON;
		delay_ms(10);	
		OLED_RST_OFF;
		delay_ms(10);	
		

    oled_sendorder(0XA8);
    oled_sendorder(0X3F);
    oled_sendorder(0XD3);
    oled_sendorder(0X00);
    oled_sendorder(0X40);
    oled_sendorder(0Xd5);      //设置刷新频率和分频值
    oled_sendorder(0Xf1);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
    oled_sendorder(0XA0);      //A0--首列对应0      A1------首列对应127
    oled_sendorder(0XC0);
    oled_sendorder(0XDA);
    oled_sendorder(0X12);
    oled_sendorder(0X81);     //对比度设置
    oled_sendorder(0Xff);     //设置对比度值
    oled_sendorder(0XD9);
    oled_sendorder(0XF1);
    oled_sendorder(0XDB);
    oled_sendorder(0X30);
    oled_sendorder(0XA4);       //0xA4-正常      0XA5-全亮
    oled_sendorder(0XA6);       //0XA6-正常      0XA7-反相
		
		
//		oled_initMode(Horizontal_Mode);	
		oled_sendorder(0x20);       /*设置显示模式                 参考：  https://blog.csdn.net/gengyuchao/article/details/86608037             */
		oled_sendorder(0x00);	      /*[页地址----10b    水平模式---00b     垂直模式---01b        */	
	  oled_sendorder(0xc8);	    //0xc8---正常      0xc0------垂直反转  
		oled_sendorder(0xa1);				
		oled_sendorder(0x23);
		oled_sendorder(0x00);          //[5:4]--00禁用闪烁或淡出       10使能消退      11使能闪烁                 [3:0]-----0000(8帧)  0001(16帧)     0010(16帧)。。。。1111(128帧)
    oled_sendorder(0X8D);     //设置电荷泵
    oled_sendorder(0X14);      //0x14-----开启     0x10----关闭
    oled_sendorder(0XAf);
	
	  clear_screen();	

}





void  display_position(u8 x,u8 y,u8 length)
{

		oled_sendorder(0x21);                       //列地址 	
		oled_sendorder(0x00|x);	                    //起始地址 	 0-127
		oled_sendorder(0x00|(x+length*8)-1);	      //终止地址   
	
		oled_sendorder(0x22);	                      //页地址	
		oled_sendorder(0x00|y);	                    //起始地址	0-7
		oled_sendorder(0x00|y);                     //终止地址
 	

}

void  picture_position(u8 x_start,u8 x_length,u8 y_start,u8 y_length)      //像素的坐标x_start ，y_start 长度x_length,高度y_length
{

		oled_sendorder(0x21);                             //列地址 	
		oled_sendorder(0x00|x_start);	                    //起始地址 	 0-127
		oled_sendorder(0x00|x_length-1);	                      //终止地址   
	
		oled_sendorder(0x22);	                           //页地址	
		oled_sendorder(0x00|y_start);	                   //起始地址	0-7
		oled_sendorder(0x00|y_length-1);                     //终止地址
 	

}




void oled_senddata(u8 Tdata)
{
		OLED_DATA;

		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);             //非中断模式
		SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);		
		delay_us(10);
}

void oled_sendorder(u8 Tdata)
{
	
	OLED_ORDER;	

		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);            //非中断模式
		SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
		delay_us(10);
}


void set_OLED_frequence_div(u8 fre,u8 div)              //s闪烁设置
{
    oled_sendorder(0Xd5);                 //设置刷新频率和分频值  
    oled_sendorder(0X00|fre<<4|div);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值

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

void set_contrast(u8 value)    
{
    oled_sendorder(0X81);           //对比度设置
    oled_sendorder(0X00|value);     //设置对比度值
}



void display_num(u8 number)
{

	char i;
switch(number)
		{
	case 0:
						for(i=0;i<8;i++)
						oled_senddata(num0[i]);
						break ;
	
	
	case 1:
						for(i=0;i<8;i++)
						oled_senddata(num1[i]);
						break ;
	
	
	case 2:
						for(i=0;i<8;i++)
						oled_senddata(num2[i]);
						break ;
	
	
	
	case 3:
		
					for(i=0;i<8;i++)
					oled_senddata(num3[i]);
					break ;
	
	
	case  4:
		
					for(i=0;i<8;i++)
					oled_senddata(num4[i]);
					break ;
	
	
	case 5:
						for(i=0;i<8;i++)
						oled_senddata(num5[i]);
						break ;
		
	
	
	case  6:
						for(i=0;i<8;i++)
						oled_senddata(num6[i]);
						break ;	
	
	
	
	case  7:
						for(i=0;i<8;i++)
						oled_senddata(num7[i]);
						break ;
	
	
	
	case 8:
						for(i=0;i<8;i++)
						oled_senddata(num8[i]);
						break ;
	
	
	
	case 9:
						for(i=0;i<8;i++)
						oled_senddata(num9[i]);
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
						oled_senddata(num0[i]);
						break ;
	
	
	case '1':
						for(i=0;i<8;i++)
						oled_senddata(num1[i]);
						break ;
	
	
	case '2':
						for(i=0;i<8;i++)
						oled_senddata(num2[i]);
						break ;
	
	
	
	case '3':
		
					for(i=0;i<8;i++)
					oled_senddata(num3[i]);
					break ;
	
	
	case  '4':
		
					for(i=0;i<8;i++)
					oled_senddata(num4[i]);
					break ;
	
	
	case '5':
						for(i=0;i<8;i++)
						oled_senddata(num5[i]);
						break ;
		
	
	
	case  '6':
						for(i=0;i<8;i++)
						oled_senddata(num6[i]);
						break ;	
	
	
	
	case  '7':
						for(i=0;i<8;i++)
						oled_senddata(num7[i]);
						break ;
	
	
	
	case '8':
						for(i=0;i<8;i++)
						oled_senddata(num8[i]);
						break ;
	
	
	
	case '9':
						for(i=0;i<8;i++)
						oled_senddata(num9[i]);
						break ;			
			
			
			
			
			case 'A':
						for(i=0;i<8;i++)
						oled_senddata(charA [i]);
						break ;



			case 'B':
						for(i=0;i<8;i++)
						oled_senddata(charB [i]);
						break ;				
			
			
			
			case 'C':
						for(i=0;i<8;i++)
						oled_senddata(charC [i]);
						break ;				
			
			
			
			case 'D':
						for(i=0;i<8;i++)
						oled_senddata(charD [i]);
						break ;			
			
			
			case 'E':
						for(i=0;i<8;i++)
						oled_senddata(charE [i]);
						break ;				
			
			
			case 'F':
						for(i=0;i<8;i++)
						oled_senddata(charF [i]);
						break ;				
			
			
			case 'G':
						for(i=0;i<8;i++)
						oled_senddata(charG [i]);
						break ;				
			
			
			case 'H':
						for(i=0;i<8;i++)
						oled_senddata(charH [i]);
						break ;				
			
			
			
			case 'I':
						for(i=0;i<8;i++)
						oled_senddata(charI [i]);
						break ;				
			
			
			case 'J':
						for(i=0;i<8;i++)
						oled_senddata(charJ [i]);
						break ;				
			
			
			
			case 'K':
						for(i=0;i<8;i++)
						oled_senddata(charK [i]);
						break ;				
			
			
			case 'L':
						for(i=0;i<8;i++)
						oled_senddata(charL [i]);
						break ;				
			
			
			
			case 'M':
						for(i=0;i<8;i++)
						oled_senddata(charM [i]);
						break ;				
			
			
			
			case 'N':
						for(i=0;i<8;i++)
						oled_senddata(charN [i]);
						break ;				
			
			
			case 'O':
						for(i=0;i<8;i++)
						oled_senddata(charO [i]);
						break ;				
			
			
			
			case 'P':
						for(i=0;i<8;i++)
						oled_senddata(charP [i]);
						break ;				
			
			case 'Q':
						for(i=0;i<8;i++)
						oled_senddata(charQ [i]);
						break ;				
			
					
			case 'R':
						for(i=0;i<8;i++)
						oled_senddata(charR [i]);
						break ;				
			
			
			case 'S':
						for(i=0;i<8;i++)
						oled_senddata(charS [i]);
						break ;				
			
			
			case 'T':
						for(i=0;i<8;i++)
						oled_senddata(charT [i]);
						break ;				
			
			
			case 'U':
						for(i=0;i<8;i++)
						oled_senddata(charU [i]);
						break ;				
			
			
			
			
			case 'V':
							for(i=0;i<8;i++)
						oled_senddata(charV [i]);
						break ;			
			
			case 'W':
						for(i=0;i<8;i++)
						oled_senddata(charW [i]);
						break ;				
					
			case 'X':
						for(i=0;i<8;i++)
						oled_senddata(charX [i]);
						break ;				
			
			
			
			case 'Y':
						for(i=0;i<8;i++)
						oled_senddata(charY [i]);
						break ;				
			
			case 'Z':
						for(i=0;i<8;i++)
						oled_senddata(charZ [i]);
						break ;	
			
			case ' ':
						for(i=0;i<8;i++)
						oled_senddata(0X00);
						break ;	
			
			case	':' :	                    ////  :
						for(i=0;i<8;i++)
						oled_senddata(charcolom[i]);
						break ;	

			case	'.' :	                    //     .
						for(i=0;i<8;i++)
						oled_senddata(point[i]);
						break ;		
			
			default :
						for(i=0;i<8;i++)
						oled_senddata(point[i]);
				      break;
					
			
		}


}




void windows_open(u32 speed)
{
u32 i;
	for(i=0;i<1024;i++)
	oled_senddata(windows[i]);
	
	display_position(0,7,16);
	
	for(i=0;i<128;i++)
	{
	oled_senddata(0xff);
	delay_ms(speed);        //进度条速度

	}
	clear_screen();

}


void tempure_unit(void)            //   温度单位   .C
{
u8 i;


		for(i=0;i<8;i++)
		{
	oled_senddata(char_tempure[i]);
		
		}
}









void power_on_check_display(void)
{
windows_open(40);                                //进度条速度
delay_ms(500);
delay_ms(500);
clear_screen();
//led_init();	
set_OLED_frequence_div(15,5);		
delay_ms(500);

display_position(40,0,5);
display_str_and_speed("CHECK",play_speed);
delay_ms(200);
	


//从此处开始添加开机检查项目
	
display_position(0,2,6);
display_str_and_speed("18B20:",play_speed);
delay_ms(500);	
display_position(87,2,5);
ds18B20_init(1);	                             //18B20
delay_ms(500);



display_position(0,4,4);
display_str_and_speed("RTC:",play_speed);
delay_ms(500);
display_position(87,4,5);
RTC_configinit();
delay_ms(500);
	
	

display_position(1,7,6);
display_str_and_speed("POWER:",play_speed);
delay_ms(500);
display_position(87,7,2);
display_str_and_speed("OK",play_speed);
delay_ms(500);

clear_screen();	

display_position(0,2,6);
display_str_and_speed("VOICE:",play_speed);
delay_ms(500);
display_position(86,2,2);
display_str_and_speed("OK",play_speed);
delay_ms(500);





display_position(0,4,5);
display_str_and_speed("WIFI:",play_speed);
delay_ms(500);
display_position(87,4,2);
display_str_and_speed("OK",play_speed);
delay_ms(500);



display_position(1,6,7);
display_str_and_speed("SENSOR:",play_speed);
delay_ms(500);
display_position(87,6,2);

display_str_and_speed("OK",play_speed);
delay_ms(500);


display_position(1,8,4);
display_str_and_speed("LED:",play_speed);
delay_ms(500);
display_position(87,8,5);
display_str_and_speed("READY",play_speed);

//delay_ms(500);


clear_screen();	



//<-------此处检查完毕


display_position(1,4,13);
display_str_and_speed("ENTER SYSTEM:",play_speed);
delay_ms(500);
delay_ms(500);
display_position(105,4,2);
display_str_and_speed("..",100);
delay_ms(500);
set_OLED_frequence_div(15,0);		                 
clear_screen();	






}



























