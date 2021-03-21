#include "IncludeFile.h"





void Task_List()
{
		static u16 P=0;
			
			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{

				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				


			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			
				OLED_Test();
				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				
				MPU6050_Test();
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
			

				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
			
			if(P>2500)	
				P=500;
				
				PWM_SetPluseWdie(TIM4,P);
				P+=500;
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}




















int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	RTC_ConfigInit();
	OLED_Init();
	RTC_ConfigInit();
	MPU6050_Init();
	TaskTimer_Init();
	PWM_Init(1,1);

	while(1)
	{	
		Task_List();	
	}





	
}	

	












