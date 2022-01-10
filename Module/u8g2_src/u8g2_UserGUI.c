#include "IncludeFile.h"


static u8g2_t u8g2;

static TaskHandle_t u8g2_iconTask_h;





void u8g2_Init()
{
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
    u8g2_ClearDisplay(&u8g2);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);

}

void Battery_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        //u8g2_FirstPage(&u8g2);
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_battery19_tn);
            u8g2_SetFontDirection(&u8g2, 1);
            u8g2_DrawGlyph(&u8g2,106,8,0x30+k);
            k++;
            if(k==7)
            k=0;
        } while (u8g2_NextPage(&u8g2));
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

}
void Safe_icon()
{
    u8 k=9;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        //u8g2_FirstPage(&u8g2);
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_unifont_t_77);
            u8g2_SetFontDirection(&u8g2, 0);
            u8g2_DrawGlyph(&u8g2,16,16,0x26C0+k);
            if(k==9)
            {
                k=10;
            }
            else
            {
               k=9; 
            }
        } while (u8g2_NextPage(&u8g2));
        vTaskDelayUntil(&Time,300/portTICK_PERIOD_MS);
    }

}
void Dir_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        //u8g2_FirstPage(&u8g2);
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_unifont_t_78_79);
            u8g2_SetFontDirection(&u8g2, 1);
            u8g2_DrawGlyph(&u8g2,0,0,0x27A2+k);
            k++;
            if(k>=3)
            {
                k=0;
            }
        } while (u8g2_NextPage(&u8g2));
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
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











void u8g2_TaskCreate()
{
    xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",200,NULL,7,&u8g2_iconTask_h);
    xTaskCreate( (TaskFunction_t)LED_Task,    "IconTask",200,NULL,10,            NULL);
    xTaskCreate( (TaskFunction_t)Safe_icon,    "IconTask",200,NULL,10,            NULL);
    xTaskCreate( (TaskFunction_t)Dir_icon,    "IconTask",200,NULL,10,            NULL);
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






















