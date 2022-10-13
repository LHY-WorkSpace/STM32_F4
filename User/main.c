#include "IncludeFile.h"

void LED_Tasssk(void)
{
	TickType_t Time;
	Time=xTaskGetTickCount();
	while(1)
	{	
		LED1_ON;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_ON;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,1000/portTICK_PERIOD_MS);

	}
}

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



void CreateAllTask()
{
	xTaskCreate( (TaskFunction_t)lvgl_Task,"LVGL",500,NULL,9,NULL);
    xTaskCreate( (TaskFunction_t)LED_Tasssk,"LVGL",200,NULL,10,NULL);
	vTaskDelete(NULL);
}



int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	XPT2046_Init();
   // KeyInit();
	TickTimer_Init(1);
	// ST7789_Init();
	LCD_Init();

	printf("Power Online\r\n");

    LVGL_Init();
	while (1)
	{
	// lv_tick_inc(1);
	// DMATest();
	// Delay_ms(100);
	LVGL_Task();
	}
	

	// xTaskCreate((TaskFunction_t)CreateAllTask,"StartTask",200,NULL,10,NULL);
	// vTaskStartScheduler();
	SystemDown();
}







