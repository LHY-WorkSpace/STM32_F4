#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "CODE_RUN_TIME.h"
//#include "dac.h"
//#include "adc.h"
#include "led.h"
//#include "exti.h"
#include "sd.h"
//#include "i2c.h"
//#include "AT24C08.h"
//#include "MPU6050.h"
//#include "DHT11.h"
//#include "ds18b20.h"
#include "oled.h"
#include "GUI.H"
//#include "DMA.h"  
//#include "pwm.h"
//#include "ESP8266.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "RTC.h"
//#include "diskio.h"	
//#include "lcd1602.h"
#include "string.h"
//#include "arm_math.h"
//#include "math.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"


extern float pitch,yaw,roll; 
__align(4) uchar OLED[2560],TTTS[2560],TTTSA[512];


uchar Data_OK;					
uint k=0;	




									
										
int  main()
{
	 uint i;
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	usart_init(115200);
//	oled_init();	
	led_init();
//	windows_open(10);
//	DMA1_ConfigInit();
//	DMA2_ConfigInit();
//	DMA2_Start();	
	delay_ms(500);

	
	
	
	
	SD_CARD_Init();

// 	memset(OLED,0x11,sizeof(OLED));
// SD_Write_Block((uint*)OLED,512);

// 	memset(OLED,0x22,sizeof(OLED));
// SD_Write_Block((uint*)OLED,1024);

// 	memset(OLED,0x33,sizeof(OLED));
// SD_Write_Block((uint*)OLED,1536);

// 	memset(OLED,0x44,sizeof(OLED));
// SD_Write_Block((uint*)OLED,2048);

// 	memset(OLED,0x55,sizeof(OLED));
// SD_Write_Block((uint*)OLED,2560);



	// memset(OLED,0xAA,sizeof(OLED));
	// SD_Write_Block((uint*)OLED,1024);

	// SD_Read_Block((uint*)TTTS,1024);
	// SD_Read_Block((uint*)TTTSA,512);
	// for(i=0;i<512;i++)	
	// {
	// printf("%4d:0x%2x   ",i,(uchar*)TTTSA[i]);
	// 	if(i%10==0)
	// 		printf("\r\n");
	// }
//	for(i=0;i<1024;i++)	
//	{
//		OLED[i]=i;
//	}

	//memset(OLED,0x55,sizeof(OLED));
//	delay_ms(300);
	// SD_Write_MultiBlocks((uint*)OLED,512,5);
	// delay_ms(300);
//	SD_Read_MultiBlocks((uint*)TTTS,512,5);
//	SD_Read_Block((uint*)TTTS,512);
//	delay_ms(300);
//	 SD_Read_Block((uint*)TTTS[512],1024);
	// SD_Read_Block((uint*)TTTS[1024],1536);
	// SD_Read_Block((uint*)TTTS[1536],2048);
	// SD_Read_Block((uint*)TTTS[2048],2560);




	for(i=0;i<512;i++)	
	{
	printf("%4d:0x%2x   ",i,(uchar*)TTTS[i]);
		if(i%10==0)
			printf("\r\n");
	}


			
	
	while(1)
	{


		LED1_OFF;
		delay_ms(300);

	//	DMA1_Start();
		LED1_ON;
		delay_ms(300);

//	DMA2_Start();
		//clear_screen();

	}



	
	
	
}	

	



void USART1_IRQHandler()
{
	static uint i=0;

	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  OLED[i]=USART_ReceiveData(USART1);
	i++;		
	}

	if(i==1024)
	{
		//OLED_FULL=1;
		i=0;

	}


}


void SPI2_IRQHandler()
{
	static uint i=0;

	if(SPI_I2S_GetITStatus(SPI2,SPI_I2S_IT_TXE)==SET)
	{
		SPI_I2S_SendData(SPI2,OLED[i]);
		SPI_I2S_ClearITPendingBit(SPI2,SPI_I2S_IT_TXE);
		i++;
	}
	if(i==1024)
	{
		i=0;
	}




}
	
		
		
		
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET));
//USART_SendData(USART1,temp);
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)!=0));	

	











