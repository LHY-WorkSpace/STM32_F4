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
//#include "diskio.h"	
//#include "lcd1602.h"
#include "string.h"
//#include "arm_math.h"
//#include "math.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"


extern float pitch,yaw,roll; 
__align(4) uchar A[512],B[512],C[512],D[512],AA[2048],BB[4096],CC[5120];


#define NUM    0x10


uchar Data_OK;					
uint k=0;	




									
//return error_type;	 添加printf()察看错误信息								
int  main()
{
	 uint i;
	 SD_error ERR[9];
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	usart_init(115200);
	IIC_Init();
//	oled_init();	
	led_init();
//	windows_open(10);
//	DMA1_ConfigInit();
//	DMA2_ConfigInit();
//	DMA2_Start();	
	delay_ms(500);

	
	memset(A,NUM+1,sizeof(A));

	IIC_Write_NByte(0,0,10,A);

	IIC_Read_NByte(0,0,10,B);
	for(i=0;i<10;i++)	
	{
	printf("%4d:0x%2x   ",i,B[i]);

	}




	
	
	
// 	SD_CARD_Init();



// 	memset(BB,NUM+5,sizeof(BB));

// // for (uchar i = 1; i < 11; i++)
// // {
// // SD_Write_Block((uint*)A,512*i);
// // }

// // SD_Write_Block((uint*)A,512);
// // SD_Write_Block((uint*)B,1024);
// // SD_Write_Block((uint*)C,1536);
// // SD_Write_Block((uint*)D,2048);
// // SD_Write_Block((uint*)A,2560);
// // SD_Write_Block((uint*)B,3072);
// // SD_Write_Block((uint*)C,3584);
// // SD_Write_Block((uint*)D,4096);







// 	 ERR[0]=SD_Write_MultiBlocks((uint*)BB,512,8);


// 	// SD_Read_MultiBlocks((uint*)AA,512,8);
// 	// for(i=0;i<4096;i++)	
// 	// {
// 	// printf("%4d:0x%2x   ",i,(uchar*)AA[i]);
// 	// 	if(i%10==0)
// 	// 		printf("\r\n");
// 	// }


// 	ERR[1]=SD_Read_Block((uint*)A,512);
// 	ERR[2]=SD_Read_Block((uint*)B,1024);
// 	ERR[3]=SD_Read_Block((uint*)C,1536);
// 	ERR[4]=SD_Read_Block((uint*)D,2048);

// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)A[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)B[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)C[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)D[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}

// 	ERR[5]=SD_Read_Block((uint*)A,2560);
// 	ERR[6]=SD_Read_Block((uint*)B,3072);
// 	ERR[7]=SD_Read_Block((uint*)C,3584);
// 	ERR[8]=SD_Read_Block((uint*)D,4096);

// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)A[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)B[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)C[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}
// 	for(i=0;i<512;i++)	
// 	{
// 	printf("%4d:0x%2x   ",i,(uchar*)D[i]);
// 		if(i%10==0)
// 			printf("\r\n");
// 	}


// 	for(i=0;i<9;i++)	
// 	{
// 	printf("%d   ",ERR[i]);
// 	}









			
	
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

	











