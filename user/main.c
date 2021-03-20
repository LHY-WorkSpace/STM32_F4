#include "IncludeFile.h"

extern u8 Task_Flag;


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Timer10_Init();
	led_init();
	RTC_ConfigInit();
	OLED_Init();
	RTC_ConfigInit();
	MPU6050_Init();
	Timer9_Init();

	while(1)
	{	



			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{
					
				MPU6050_Test();
				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				


			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			
				OLED_Test();
				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				

				System_ResetState(Task_TimeFlag,Task_50ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
			{
				
				printf("Task_10ms\r\n");
				System_ResetState(Task_TimeFlag,Task_100ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
			{
				RTC_Test();
				System_ResetState(Task_TimeFlag,Task_200ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
			{
			
				Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
			
				
				System_ResetState(Task_TimeFlag,Task_1s);	
			}
		


	}





	
}	

	












