#include "IncludeFile.h"




void led_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_9;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType=GPIO_OType_PP;           
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);


}


void LED_Freq()
{
    static u8 ms = 0;

	if( ms == 0 )
	{
		LED1_OFF;
		ms = 1;
	}
	else
	{ 
		LED1_ON;
		ms = 0;
	}

}


void LED_Task(void)
{
	TickType_t Time;
	Time=xTaskGetTickCount();
	while(1)
	{	
		LED1_ON;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_ON;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,1500/portTICK_PERIOD_MS);
	}
}



