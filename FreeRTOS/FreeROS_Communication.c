#include "IncludeFile.h"



extern QueueHandle_t USART1_TaskHandle;
TaskHandle_t A_LED_Handle;
TaskHandle_t B_LED_Handle;

void USART_Task()
{
    TickType_t xTicksToWait = 100/portTICK_PERIOD_MS;
    BaseType_t  State;
    u8 Data;

    USART1_TaskHandle = xQueueCreate(10,sizeof(u8));

    if( USART1_TaskHandle == NULL)
    {
    }

    while (1)
    {
        State = xQueueReceive(USART1_TaskHandle,&Data,portMAX_DELAY);

        if( State == pdPASS)
        {

            switch (Data)
            {
            case 1:
               vTaskSuspend(A_LED_Handle);
                break;
            case 2:
               vTaskResume(A_LED_Handle);
                break;
            case 3:
               vTaskSuspend(B_LED_Handle);
                break;
            case 4:
               vTaskResume(B_LED_Handle);
                break;          
            default:
                break;
            }
        }

    }

}


void LED_Task_A()
{
	TickType_t Time;
 	Time = xTaskGetTickCount();

    while (1)
    {
        LED1_ON;
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
        LED1_OFF;
        vTaskDelayUntil(&Time,80/portTICK_PERIOD_MS);
        LED1_ON;
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
        LED1_OFF;
        vTaskDelayUntil(&Time,2000/portTICK_PERIOD_MS);
    }

}

void LED_Task_B()
{
	TickType_t Time;
 	Time = xTaskGetTickCount();
    while (1)
    {
        LED1_ON;
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
        LED1_OFF;
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

}


void Create_Task()
{
    xTaskCreate( (TaskFunction_t)LED_Task_A,"LED_A",100,NULL,11,&A_LED_Handle);
    xTaskCreate( (TaskFunction_t)LED_Task_B,"LED_B",100,NULL,12,&B_LED_Handle);
    xTaskCreate( (TaskFunction_t)USART_Task,"UART",100,NULL,13,NULL);
}










































































