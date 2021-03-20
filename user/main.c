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
		switch(System_GetState(Task_TimeFlag,0xFF))
		{

			case Task_10ms:
			{
			printf("Task_10ms\r\n");	

			}
			System_ResetState(Task_TimeFlag,Task_10ms);	
			break;

			case Task_30ms|Task_10ms:
			{
			

			}
			System_ResetState(Task_TimeFlag,Task_30ms);	
			break;

			case Task_50ms|Task_10ms:
			{
				

			}
			System_ResetState(Task_TimeFlag,Task_50ms);	
			break;

			case Task_100ms|Task_10ms:
			{
				

			}
			System_ResetState(Task_TimeFlag,Task_100ms);	
			break;

			case Task_200ms|Task_10ms:
			{
				
			}
			System_ResetState(Task_TimeFlag,Task_200ms);	
			break;

			case Task_500ms|Task_10ms:
			{
			

			}
			System_ResetState(Task_TimeFlag,Task_500ms);	
			default:
			
			  	break;
		}



	}





	
}	

	












