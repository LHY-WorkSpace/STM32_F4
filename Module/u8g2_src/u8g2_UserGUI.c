#include "IncludeFile.h"


static u8g2_t u8g2;

static TaskHandle_t u8g2_iconTask_h;












void u8g2_Init()
{
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
}

void Battery_icon()
{






}





void u8g2_TaskCreate()
{

    xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",200,NULL,7,&u8g2_iconTask_h);





    vTaskDelete(NULL);
}




void u8g2_Task()
{
	TickType_t Time;		

    u8g2_TaskCreate();


	Time=xTaskGetTickCount();
    while (1)
    {


       vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}






















