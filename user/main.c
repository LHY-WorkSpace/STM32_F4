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
// #include "sdio_sdcard.h"
#include "i2c.h"
#include "AT24C08.h"
#include "MPU6050.h"
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
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

float pitch,yaw,roll; 
__align(4) uchar A[512],B[512],C[512],D[512],AA[1024],BB[4096],CC[1024];


#define NUM    0x54


uchar Data_OK;					
uchar k,dataA[100],dataB[100];	




													
int  main()
{
//	 uint i;

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	usart_init(115200);
	IIC_Init();
//	oled_init();	
	led_init();
//	delay_ms(500);
LED1_ON;
	MPU6050_Init();
LED1_OFF;

for(k=0;k<100;k++)
	dataA[k]=0X11;

//  AT24C08Write_NByte(AT24C08_BLOCK1_ADDRESS,0,50, dataA);	
//  AT24C08Read_NByte(AT24C08_BLOCK1_ADDRESS,0,50, dataB);
// 		for(k=0;k<100;k++)
//  	printf("%d EEPROM: %d\r\n",k,dataB[k]);	

	while(1)
	{


	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);


	 AT24C08Write_NByte(AT24C08_ADDRESS,0,100,dataA);
	 
		LED1_OFF;
		delay_ms(500);
		LED1_ON;
		delay_ms(500);


 	AT24C08Read_NByte(AT24C08_ADDRESS,50,100,dataB);

		for(k=0;k<100;k++)
	{
 	printf("EE:%d  \r\n",dataB[k]);	
	//  if(k%9==0)
	// printf("\r\n");
	}
	}



	
	
	
}	

	




	
		
		











