#include "IncludeFile.h"


static u8g2_t u8g2;

static TaskHandle_t u8g2_iconTask_h;

u8 flag=0;



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
        taskENTER_CRITICAL();
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_battery19_tn);
            u8g2_SetFontDirection(&u8g2, 1);
            u8g2_DrawGlyph(&u8g2,106,8,0x30+k);
            k++;
            if(k==7)
            k=0;
        } while (u8g2_NextPage(&u8g2));
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

}




void Safe_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
         taskENTER_CRITICAL();
         u8g2_SetFontMode(&u8g2,0);
        do
        {	if(flag==0)
            u8g2_SetDrawColor(&u8g2,2);
            else
            u8g2_SetDrawColor(&u8g2,1);
            u8g2_SetFont(&u8g2, u8g2_font_unifont_t_77);
            u8g2_SetFontDirection(&u8g2, 0);
            u8g2_DrawGlyph(&u8g2,16,16,0x26C9);
        } while (u8g2_NextPage(&u8g2));
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

}
void Dir_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
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
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
    }

}

void Streamline_icon()
{
    u8 k=0,p=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_streamline_all_t);
            u8g2_SetFontDirection(&u8g2, 0);
            u8g2_DrawGlyph(&u8g2,0,60,0x30+(k+1));
            u8g2_DrawGlyph(&u8g2,22,60,0x30+(k+2));
            u8g2_DrawGlyph(&u8g2,44,60,0x30+(k+3));
            u8g2_DrawGlyph(&u8g2,66,60,0x30+(k+4));
            u8g2_DrawGlyph(&u8g2,88,60,0x30+(k+5));
            k++;
        } while (u8g2_NextPage(&u8g2));
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
    }
}

void Shift_icon()
{
    u8 k=127,p=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_streamline_all_t);
            u8g2_SetFontDirection(&u8g2, 0);
            u8g2_DrawGlyph(&u8g2,k,40,0x29D);
            k--;
            if(k==0)
            k=127;
        } while (u8g2_NextPage(&u8g2));
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
    }
}

void Moon_Task()
{
    TickType_t Time;
    u8 i=0;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
        do
        {	
            u8g2_SetFont(&u8g2, u8g2_font_unifont_t_weather);
            u8g2_SetFontDirection(&u8g2, 0);
            u8g2_DrawGlyph(&u8g2,32,16,0x22+i);
        } while (u8g2_NextPage(&u8g2));
        i++;
        if(i >=7)
        {
            i=0;
        }
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
    }
}

void Round_Task()
{
    TickType_t Time;
    u8 i=0;	
    u8 x0=21,y0=21;
    u8 x,y;
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
        u8g2_SetFontMode(&u8g2,1);
        do
        {	


            switch (i)
            {
                case 0:
                    x=x0,y=y0;
                    break;
                case 1:
                    x=x0,y=y0-21;
                    break;
                case 2:
                    x=x0+21,y=y0-21;
                    break;
                case 3:
                    x=x0+21,y=y0;
                    break;
                default:
                    break;
            }

            // u8g2_SetDrawColor(&u8g2,0);
            // u8g2_DrawBox(&u8g2,20,22,22,22);


            u8g2_SetDrawColor(&u8g2,1);
            u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
            u8g2_SetFontDirection(&u8g2, i);
            u8g2_DrawGlyph(&u8g2,x,y,0x36);
            i++;
            if(i >=4)
            {
                i=0;
            }
        } while (u8g2_NextPage(&u8g2));

        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }
}




void Clear_Task()
{
    TickType_t Time;	
    Time=xTaskGetTickCount();

    while (1)
    {
        //u8g2_FirstPage(&u8g2);
        u8g2_SendBuffer(&u8g2);
        // u8g2_ClearBuffer(&u8g2);
    }
    vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
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
        if(flag==1)
        flag=0;
        else
        flag=1;

	}
}


void Teat_Task()
{

	TickType_t Time;
	Time=xTaskGetTickCount();
    while (1)
    {
        u8g2_SetFontMode(&u8g2,0);
            u8g2_SetDrawColor(&u8g2,0);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,0,21,0x36);
            u8g2_SetDrawColor(&u8g2,1);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,21,21,0x36);
            u8g2_SetDrawColor(&u8g2,2);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,42,21,0x36);
       u8g2_SetFontMode(&u8g2,1);
            u8g2_SetDrawColor(&u8g2,0);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,0,45,0x36);
            u8g2_SetDrawColor(&u8g2,1);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,21,45,0x36);
            u8g2_SetDrawColor(&u8g2,2);
                u8g2_SetFont(&u8g2, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2,42,45,0x36);              
        u8g2_SendBuffer(&u8g2);
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);

    }
    


}








void u8g2_TaskCreate()
{
    // xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",200,NULL,10,&u8g2_iconTask_h);
    xTaskCreate( (TaskFunction_t)LED_Task,    "IconTask",200,NULL,10,            NULL);
    xTaskCreate( (TaskFunction_t)Safe_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Dir_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Streamline_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Shift_icon,    "IconTask",200,NULL,10,            NULL);
  // xTaskCreate( (TaskFunction_t)Round_Task,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Moon_Task,    "IconTask",200,NULL,10,            NULL);

   //xTaskCreate( (TaskFunction_t)Teat_Task,    "IconTask",200,NULL,10,            NULL);
   //xTaskCreate( (TaskFunction_t)Clear_Task,    "IconTask",200,NULL,10,            NULL);
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
















// …¡À∏…Ë÷√
//     u8g2_SetFontMode(&u8g2,x); x=1ªÚ0
//     u8g2_SetDrawColor(&u8g2,2);∆Ù”√…¡À∏
//      u8g2_SetDrawColor(&u8g2,1);πÿ±’…¡À∏
//     delay();




