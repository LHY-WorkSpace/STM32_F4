#include "IncludeFile.h"


void lvgl_Task()
{
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
		// taskENTER_CRITICAL();
		LVGL_Task();
		// taskYIELD();
		// taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,1/portTICK_PERIOD_MS);
    }
} 

void FFT_Task()
{
    TickType_t Time;	
	// char InfoBuffer[200];
    Time=xTaskGetTickCount();
    while (1)
    {
		// lv_tick_inc(2);
		// vTaskList(InfoBuffer);
		// printf("taskName\ttaskState\ttaskPrio\ttaskStack\ttaskNum\r\n");
		// printf("%s",InfoBuffer);
        vTaskDelayUntil(&Time,2/portTICK_PERIOD_MS);
    }
}




void CreateAllTask()
{
	xTaskCreate( (TaskFunction_t)lvgl_Task,"LVGL",500,NULL,10,NULL);
   	xTaskCreate( (TaskFunction_t)LED_Task,"LED",200,NULL,11,NULL);
	// xTaskCreate( (TaskFunction_t)u8g2_TaskCreate,"FFT",500,NULL,5,NULL);
	vTaskDelete(NULL);
}



int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	// u8g2_Init();
	// AS5600_Init();

	// ILI9341_Init();
	ST7789_Init();
	// printf("Power Online\r\n");
    LVGL_Init();
	// while (1)
	// {
	// // 	LED_Freq();
	// // 	LVGL_Task();
	// 	AS5600_Test();
	// }
	xTaskCreate((TaskFunction_t)CreateAllTask,"StartTask",500,NULL,10,NULL);
	vTaskStartScheduler();
	SystemDown();
}







