#include "IncludeFile.h"




void Task_List()
{

			
			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{

				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				

			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			

				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_50ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_100ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
			{


				System_ResetState(Task_TimeFlag,Task_200ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
			{
			
				
				Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
				//OLED_ClearScreen(0x00);
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}

void OLED_Task()
{
	while(1)
	{
		OLED_Test();
		vTaskDelay(100);
	}
}


void LED_Task()
{
	while(1)
	{
		Led_Test();
		vTaskDelay(100);
	}
}


void Task_Init()
{

	xTaskCreate( OLED_Task,"OLED",30,NULL,5,NULL);
	xTaskCreate( LED_Task,"LED",10,NULL,5,NULL);




}





int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	TaskTimer_Init();


	Task_Init();

	vTaskStartScheduler();












/*
	while(1)
	{	
		Task_List();	

	}
*/

}	

	












