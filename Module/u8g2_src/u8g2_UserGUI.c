#include "IncludeFile.h"


static u8g2_t u8g2;














void u8g2_Init()
{
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
}






void u8g2_Task()
{
	TickType_t Time;		
	Time=xTaskGetTickCount();

    while (1)
    {




       vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}






















