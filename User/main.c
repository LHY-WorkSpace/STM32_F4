#include "IncludeFile.h"


void lvgl_Task()
{
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
		LVGL_Task();
        vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
    }
} 

void FFT_Task()
{
    TickType_t Time;	
	char InfoBuffer[200];
    Time=xTaskGetTickCount();
    while (1)
    {
		vTaskList(InfoBuffer);
		printf("taskName\ttaskState\ttaskPrio\ttaskStack\ttaskNum\r\n");
		printf("%s",InfoBuffer);
        vTaskDelayUntil(&Time,3000/portTICK_PERIOD_MS);
    }
}


void CreateAllTask()
{
	xTaskCreate( (TaskFunction_t)lvgl_Task,"LVGL",500,NULL,9,NULL);
   	xTaskCreate( (TaskFunction_t)LED_Task,"LED",200,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)FFT_Task,"FFT",500,NULL,9,NULL);
	vTaskDelete(NULL);
}



int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	ST7789_Init();
    LVGL_Init();
	printf("Power Online\r\n");


	xTaskCreate((TaskFunction_t)CreateAllTask,"StartTask",200,NULL,10,NULL);
	vTaskStartScheduler();
	SystemDown();
}







