#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "CODE_RUN_TIME.h"
//#include "dac.h"
//#include "adc.h"
#include "led.h"
//#include "exti.h"
// #include "sd.h"
#include "sdio_sdcard.h"
#include "i2c.h"
//#include "AT24C08.h"
//#include "MPU6050.h"
//#include "DHT11.h"
//#include "ds18b20.h"
//#include "oled.h"
//#include "GUI.H"
//#include "DMA.h"  
//#include "pwm.h"
//#include "ESP8266.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "RTC.h"
#include "diskio.h"	
//#include "lcd1602.h"
#include "string.h"
//#include "arm_math.h"
//#include "math.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"


float pitch,yaw,roll; 
__align(4) uchar A[512],B[512],C[512],D[512],AA[1024],BB[4096],CC[1024];


#define NUM    0x54


uchar Data_OK;					
uint k=0;	




									
//return error_type;	 添加printf()察看错误信息								
int  main()
{
	 uint i;
//	 SD_error ERR[9];
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	usart_init(115200);
	IIC_Init();

//	oled_init();	
	led_init();
	SD_Init();
 	SD_ShowInfomation();
//	delay_ms(500);
LED1_ON;
	MPU6050_Init();
LED1_OFF;

			
	
	while(1)
	{


	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);
	
		// LED1_OFF;
		// delay_ms(300);
		// LED1_ON;
		// delay_ms(300);



	}



	
	
	
}	

	



void USART1_IRQHandler()
{
	static uint i=0;

	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//  OLED[i]=USART_ReceiveData(USART1);
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
//		SPI_I2S_SendData(SPI2,OLED[i]);
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

	











