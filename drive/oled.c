#include"IncludeFile.h"



												//  PB13-------SCLK          PB15------SDA
												//  PB12-------D/C           PB14------RST 





#define play_speed           100














	
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
u8 charcolom[8]={0X00,0X00,0X00,0X66,0X66,0X00,0X00,0X00};    //ð��
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

void oled_spi_configinit()
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

  //SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_TXE,ENABLE);

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
    oled_sendorder(0Xd5);      //����ˢ��Ƶ�ʺͷ�Ƶֵ
    oled_sendorder(0Xf1);      //����λ(��λ=8)-ˢ��Ƶ��   ����λ(��λ=1)---��Ƶֵ
    oled_sendorder(0XA0);      //A0--���ж�Ӧ0      A1------���ж�Ӧ127
    oled_sendorder(0XC0);
    oled_sendorder(0XDA);
    oled_sendorder(0X12);
    oled_sendorder(0X81);     //�Աȶ�����
    oled_sendorder(0Xff);     //���öԱȶ�ֵ
    oled_sendorder(0XD9);
    oled_sendorder(0XF1);
    oled_sendorder(0XDB);
    oled_sendorder(0X30);
    oled_sendorder(0XA4);       //0xA4-����      0XA5-ȫ��
    oled_sendorder(0XA6);       //0XA6-����      0XA7-����
		
		
//		oled_initMode(Horizontal_Mode);	
		oled_sendorder(0x20);       /*������ʾģʽ                 �ο���  https://blog.csdn.net/gengyuchao/article/details/86608037             */
		oled_sendorder(0x00);	      /*[ҳ��ַ----10b    ˮƽģʽ---00b     ��ֱģʽ---01b        */	
	  oled_sendorder(0xc8);	    //0xc8---����      0xc0------��ֱ��ת  
		oled_sendorder(0xa1);				
		oled_sendorder(0x23);
		oled_sendorder(0x00);          //[5:4]--00������˸�򵭳�       10ʹ������      11ʹ����˸                 [3:0]-----0000(8֡)  0001(16֡)     0010(16֡)��������1111(128֡)
    oled_sendorder(0X8D);     //���õ�ɱ�
    oled_sendorder(0X14);      //0x14-----����     0x10----�ر�
    oled_sendorder(0XAf);
	
	  clear_screen();	

}





void  display_position(u8 x,u8 y,u8 length)
{

		oled_sendorder(0x21);                       //�е�ַ 	
		oled_sendorder(0x00|x);	                    //��ʼ��ַ 	 0-127
		oled_sendorder(0x00|(x+length*8)-1);	      //��ֹ��ַ   
	
		oled_sendorder(0x22);	                      //ҳ��ַ	
		oled_sendorder(0x00|y);	                    //��ʼ��ַ	0-7
		oled_sendorder(0x00|y);                     //��ֹ��ַ
 	

}

void show_picture(u8 x_start,u8 y_start,u8 x_length,u8 y_length,u8* data)      //���ص�����x_start ��y_start ���x_length,�߶�y_length ͼ������data
{

	u8 i=0,j=x_length*(y_length>>3);
	
		oled_sendorder(0x21);                             //�е�ַ 	
		oled_sendorder(x_start);	                    //��ʼ��ַ 	 0-127
		oled_sendorder(x_length-1+x_start);	                      //��ֹ��ַ   
	
		oled_sendorder(0x22);	                           //ҳ��ַ	
		oled_sendorder(y_start);	                   //��ʼ��ַ	0-7
		oled_sendorder(((y_length>>3)-1)+y_start);                     //��ֹ��ַ
 	
   for(i=0;i<j;i++)
	  oled_senddata(data[i]);

	

}





void oled_senddata(u8 Tdata)
{
		OLED_DATA;

		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);             //���ж�ģʽ
		SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);		
		delay_us(10);

}

void oled_sendorder(u8 Tdata)
{
	
	OLED_ORDER;	

		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);            //���ж�ģʽ
		SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
		delay_us(10);

}


void set_OLED_frequence_div(u8 fre,u8 div)              //��˸����fre[0-f]  div[0-f] 
{
    oled_sendorder(0Xd5);                 //����ˢ��Ƶ�ʺͷ�Ƶֵ  
    oled_sendorder(0X00|fre<<4|div);      //����λ(��λ=8)-ˢ��Ƶ��   ����λ(��λ=1)---��Ƶֵ

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

void set_contrast(u8 value)    //value[00-ff]
{
    oled_sendorder(0X81);           //�Աȶ�����
    oled_sendorder(0X00|value);     //���öԱȶ�ֵ
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
	for(i=0;i<896;i++)
	oled_senddata(windows[i]);
	
	display_position(0,7,16);
	
	for(i=0;i<128;i++)
	{
	oled_senddata(0xff);
	delay_ms(speed);        //�������ٶ�

	}
	clear_screen();

}


void tempure_unit(void)            //   �¶ȵ�λ   .C
{
u8 i;
		for(i=0;i<8;i++)
		{
	oled_senddata(char_tempure[i]);
		
		}
}








void power_on_check_display(void)
{
windows_open(10);                                //�������ٶ�
delay_ms(500);

clear_screen();

set_OLED_frequence_div(15,6);		
delay_ms(500);

//display_position(40,0,5);
//display_str_and_speed("CHECK",play_speed);
//delay_ms(200);
	


//�Ӵ˴���ʼ��ӿ��������Ŀ
	
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

//clear_screen();	

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

//clear_screen();

//display_position(1,8,4);
//display_str_and_speed("LED:",play_speed);
//delay_ms(500);
//display_position(87,8,5);
//display_str_and_speed("READY",play_speed);

////delay_ms(500);


clear_screen();	



//<-------�˴�������


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



























