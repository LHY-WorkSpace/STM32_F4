#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "CODE_RUN_TIME.h"
#include "dac.h"
#include "adc.h"
#include "led.h"
#include "exti.h"
#include "sd.h"
#include "sdio_sdcard.h"
#include "i2c.h"
#include "AT24C08.h"
#include "MPU6050.h"
#include "DHT11.h"
#include "ds18b20.h"
#include "oled.h"
#include "GUI.H"
#include "DMA.h"  
#include "pwm.h"
#include "ESP8266.h"
#include "FreeRTOS.h"
#include "task.h"
#include "RTC.h"
#include "diskio.h"	
#include "lcd1602.h"
#include "string.h"
#include "arm_math.h"
#include "math.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

float pitch,yaw,roll; 
__align(4) u8 A[256],B[256],C[512],D[512],AA[1024],BB[4096],CC[1024];


#define NUM    0x54

u8 Data_OK;					
u16 k,dataA[100],dataB[100];	


													
int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	usart_init(115200);
	IIC_Init();
//	oled_init();	
	led_init();
//	delay_ms(500);

	MPU6050_Init();


	LED1_ON;
	memset(A,0X12,256);
	AT24C08Write_NBytes(AT24C08_BLOCK1,0,256,A);
	memset(A,0X34,256);
	AT24C08Write_NBytes(AT24C08_BLOCK2,0,256,A);
	memset(A,0X56,256);
	AT24C08Write_NBytes(AT24C08_BLOCK3,0,256,A);
	memset(A,0X78,256);
	AT24C08Write_NBytes(AT24C08_BLOCK4,0,256,A);






 	AT24C08Read_NBytes(AT24C08_BLOCK1,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE1:%d \r\n",k,B[k]);	
	}

 	AT24C08Read_NBytes(AT24C08_BLOCK2,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE2:%d \r\n",k,B[k]);	
	}

	AT24C08Read_NBytes(AT24C08_BLOCK3,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE3:%d \r\n",k,B[k]);	
	}

	AT24C08Read_NBytes(AT24C08_BLOCK4,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE4:%d \r\n",k,B[k]);	
	}


	LED1_OFF;

	while(1)
	{



	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);
		// LED1_OFF;
		// delay_ms(500);
		// LED1_ON;
		// delay_ms(500);



	}



	
	
	
}	

	




	
		
		










