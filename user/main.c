#include "IncludeFile.h"

extern u8 Task_Flag;


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	led_init();
	RTC_ConfigInit();
	OLED_Init();
	RTC_ConfigInit();
	MPU6050_Init();
	Timer9_Init();
	while(1)
	{	
		switch(Task_Flag)
		{
			case 0:
				LED1_ON;
			break;
			case 1:
				LED1_OFF;
			break;

			case 2:
				RTC_Test();
			break;

			case 3:
				MPU6050_Test();
			break;

			case 4:
				OLED_Test();
			break;

			case 5:
				printf("USART--1\r\n");
			break;

			case 6:
				printf("USART--2\r\n");
			break;

			case 7:
				printf("USART--3\r\n");
			break;

			case 8:
				printf("USART--4\r\n");
			break;

			case 9:
				printf("USART--5\r\n");
			break;

			case 10:
				printf("USART--6\r\n");
			break;

			case 11:
				printf("ERROR!!!!!!\r\n");
			break;


			default:
			  break;
		}




		








	}



	
}	

	












