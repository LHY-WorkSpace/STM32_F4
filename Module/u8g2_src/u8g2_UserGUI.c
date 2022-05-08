#include "IncludeFile.h"


static u8g2_t u8g2_Data;

static TaskHandle_t u8g2_Battery_T;
static TaskHandle_t u8g2_Dir_T;
static TaskHandle_t u8g2_Safe_T;
static TaskHandle_t LED_T;

u8 flag=0;
static unsigned char FreeRTOS_Logo[] =
{
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0XFF,0XFF,0XFF,0X05,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0X00,0X00,0X00,0X00,
0X00,0X20,0X00,0X00,0X00,0X80,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,
0X00,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XE0,0XFF,0XFF,0XFF,0X07,
0X00,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,
0X00,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X38,
0X00,0X0C,0XC0,0X9F,0XFF,0X07,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X38,
0X00,0X0C,0XE0,0X8D,0XFF,0X3F,0XF8,0XFF,0X1F,0XC0,0X1F,0X00,0X00,0X00,0X00,0X38,
0X00,0X0C,0XB0,0XCD,0XFF,0X7F,0XF8,0XFF,0X1F,0XF8,0XFF,0X01,0XC0,0XFF,0X01,0X78,
0X00,0X06,0XB0,0XCF,0XFF,0XFF,0XFC,0XFF,0X1F,0XFE,0XFF,0X07,0XF8,0XFF,0X07,0X78,
0X00,0X06,0XF0,0XE7,0X0F,0XFF,0XF8,0XFF,0X0F,0XFF,0XFF,0X0F,0XFC,0XFF,0X07,0X78,
0X00,0X06,0XE0,0XE3,0X07,0X7E,0X00,0X3F,0X80,0XFF,0XF8,0X0F,0XFE,0XFF,0X03,0X38,
0X00,0X03,0X00,0XE0,0X07,0X7E,0X80,0X3F,0XC0,0X3F,0XE0,0X1F,0XFF,0X81,0X03,0X38,
0X00,0X03,0X70,0XF0,0X07,0X3F,0X80,0X3F,0XE0,0X1F,0XC0,0X1F,0XFF,0X00,0X00,0X38,
0X80,0X01,0X7C,0XF3,0XFF,0X1F,0X80,0X1F,0XE0,0X0F,0XC0,0X1F,0XFF,0X00,0X00,0X38,
0X80,0X01,0X2E,0XF3,0XFF,0X0F,0X80,0X1F,0XF0,0X07,0XC0,0X1F,0XFF,0X03,0X00,0X38,
0X80,0X01,0XB6,0XF9,0XFF,0X07,0XC0,0X1F,0XF0,0X07,0XC0,0X1F,0XFF,0X1F,0X00,0X38,
0XC0,0X00,0XFE,0XF9,0XFF,0X07,0XC0,0X1F,0XF0,0X07,0XC0,0X1F,0XFE,0XFF,0X00,0X3C,
0XC0,0X00,0XFE,0XF8,0XF1,0X07,0XC0,0X0F,0XF0,0X07,0XC0,0X1F,0XFC,0XFF,0X01,0X3C,
0XE0,0X00,0X3D,0XFC,0XE1,0X07,0XE0,0X0F,0XF0,0X07,0XE0,0X1F,0XF0,0XFF,0X03,0X3C,
0X60,0X00,0X03,0XFC,0XE0,0X0F,0XE0,0X0F,0XF0,0X07,0XE0,0X1F,0X00,0XFF,0X07,0X3C,
0X60,0X00,0X03,0XFC,0XE0,0X0F,0XE0,0X0F,0XF0,0X07,0XF0,0X0F,0X00,0XFC,0X07,0X3C,
0X70,0X80,0X7F,0XFE,0XE0,0X0F,0XE0,0X07,0XF0,0X0F,0XF8,0X0F,0X00,0XF8,0X07,0X3C,
0X30,0X80,0X7F,0X7E,0XE0,0X0F,0XF0,0X07,0XF0,0X1F,0XFE,0X87,0X00,0XF8,0X07,0X3C,
0X30,0X18,0X3F,0X7E,0XE0,0X0F,0XF0,0X07,0XE0,0XFF,0XFF,0X83,0X07,0XFC,0X07,0X3C,
0X18,0X1C,0X00,0X00,0XC0,0X0F,0XF0,0X07,0XC0,0XFF,0XFF,0X81,0XFF,0XFF,0X03,0X1C,
0X18,0XCC,0X00,0X00,0X00,0X00,0XE0,0X03,0X80,0XFF,0X7F,0XC0,0XFF,0XFF,0X01,0X1C,
0X1C,0XFC,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0XFC,0X1F,0XC0,0XFF,0XFF,0X00,0X1C,
0X0C,0XFC,0X9F,0XFF,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0X3F,0X00,0X1E,
0X0C,0XF8,0X9F,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X80,0X01,0X00,0X1E,
0X0E,0X30,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0X00,0X00,0X00,0X00,0X00,0X1E,
0X06,0X00,0X00,0X00,0X00,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0X00,0X00,0X00,0X1E,
0X06,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0X00,0X1E,
0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0XFF,0XFF,0XFF,0XFF,0X03,0X1E,
0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0XFF,0XFF,0X03,0X1E,
0XFE,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X03,0X1E,
0XFC,0XFF,0XFF,0X3F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,
0XFC,0XFF,0XFF,0XFF,0XFF,0X3F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0E,
0XE0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0E,
0X00,0X00,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0X00,0X00,0X00,0X00,0X00,0X0E,
0X00,0X00,0X00,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0X00,0X00,0X00,0X0F,
0X00,0X00,0X00,0X00,0X00,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0X00,0X0F,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0XFF,0XFF,0XFF,0XFF,0X01,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF0,0XFF,0XFF,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,

};

static unsigned char NIUNI[] =
{
0x80,0x00,0x88,0x00,0x88,0x00,0x88,0x00,
0xF8,0x1F,0x84,0x00,0x82,0x00,0x80,0x00,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,
};/*"?",0*/

static unsigned char BIII[] =
{
0x00,0x00,0xE4,0x3F,0x08,0x00,0xC8,0x1F,
0x40,0x10,0xC0,0x1F,0x0F,0x00,0xE8,0x3F,
0x28,0x22,0xE8,0x3F,0x28,0x22,0xE8,0x3F,
0x28,0x20,0x14,0x00,0xE2,0x7F,0x00,0x00,
};
/*"?",1*/




void u8g2_Init()
{
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2_Data, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
    u8g2_ClearDisplay(&u8g2_Data);
	u8g2_InitDisplay(&u8g2_Data);
	u8g2_SetPowerSave(&u8g2_Data, 0);




}

void draw(u8g2_t *u8g2)
{
    u8g2_SetFontMode(u8g2, 1);  // Transparent
    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 0, 20, "U");
    
    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(u8g2, 21,8,"8");
        
    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 51,30,"g");
    u8g2_DrawStr(u8g2, 67,30,"\xb2");
    
    u8g2_DrawHLine(u8g2, 2, 35, 47);
    u8g2_DrawHLine(u8g2, 3, 36, 47);
    u8g2_DrawVLine(u8g2, 45, 32, 12);
    u8g2_DrawVLine(u8g2, 46, 33, 12);
  
    u8g2_SetFont(u8g2, u8g2_font_6x10_tr);
    u8g2_DrawStr(u8g2, 1,54,"Design By LHY");	
}



void Display_FreeRTOS_Logo()
{
    u8 Buff[768];
    u8 i;
    memset(Buff,0,sizeof(Buff));
    for ( i = 0; i < 6; i++)
    {
        AT24C08ReadData(128*i,128,Buff+128*i);
        u8g2_DrawXBM(&u8g2_Data,0,8,128,48,Buff);
        u8g2_SendBuffer(&u8g2_Data);
        delay_ms(10);
    }
}


void Display_NIUNI()
{
    u8g2_SetBitmapMode(&u8g2_Data,SET);//????
    u8g2_DrawXBM(&u8g2_Data,0,8,16,16,NIUNI);
    u8g2_SetBitmapMode(&u8g2_Data,RESET);//????
    u8g2_DrawXBM(&u8g2_Data,20,20,16,16,BIII);
    u8g2_SendBuffer(&u8g2_Data);
    delay_ms(10);

}


void Start_Page()
{
    u8 i=0;
    draw(&u8g2_Data);
    u8g2_SendBuffer(&u8g2_Data);
    AT24C08WriteData(0,768,FreeRTOS_Logo);
    for ( i = 0; i < 15; i++)
    {
        delay_ms(100);
    }
    u8g2_ClearBuffer(&u8g2_Data);
    
}




void Battery_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
        u8g2_SetFontMode(&u8g2_Data,0);
        u8g2_SetDrawColor(&u8g2_Data,1);

            u8g2_SetFont(&u8g2_Data, u8g2_font_battery19_tn);
            u8g2_SetFontDirection(&u8g2_Data, 1);
            u8g2_DrawGlyph(&u8g2_Data,106,8,0x30+k);
            k++;
            if(k==7)
            k=0;
       u8g2_SendBuffer(&u8g2_Data);
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
    }

}




void Safe_icon()
{
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
         taskENTER_CRITICAL();
         u8g2_SetFontMode(&u8g2_Data,0);
            if(flag==0)
            u8g2_SetDrawColor(&u8g2_Data,2);
            else
            u8g2_SetDrawColor(&u8g2_Data,1);
            u8g2_SetFont(&u8g2_Data, u8g2_font_unifont_t_77);
            u8g2_SetFontDirection(&u8g2_Data, 0);
            u8g2_DrawGlyph(&u8g2_Data,16,16,0x26C9);
            u8g2_SendBuffer(&u8g2_Data);
        if(flag==1)
            flag=0;
        else
            flag=1;
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
        u8g2_SetFontMode(&u8g2_Data,0);
        u8g2_SetDrawColor(&u8g2_Data,1);

            u8g2_SetFont(&u8g2_Data, u8g2_font_unifont_t_78_79);
            u8g2_SetFontDirection(&u8g2_Data, 1);
            u8g2_DrawGlyph(&u8g2_Data,0,0,0x27A2+k);
            k++;
            if(k>=3)
            {
                k=0;
            }
       u8g2_SendBuffer(&u8g2_Data);
        u8g2_SetFontDirection(&u8g2_Data, 0);
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
    }

}

void Streamline_icon()
{
    u8 k=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();

            u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_all_t);
            u8g2_SetFontDirection(&u8g2_Data, 0);
            u8g2_DrawGlyph(&u8g2_Data,0,60,0x30+(k+1));
            u8g2_DrawGlyph(&u8g2_Data,22,60,0x30+(k+2));
            u8g2_DrawGlyph(&u8g2_Data,44,60,0x30+(k+3));
            u8g2_DrawGlyph(&u8g2_Data,66,60,0x30+(k+4));
            u8g2_DrawGlyph(&u8g2_Data,88,60,0x30+(k+5));
            k++;
        u8g2_SendBuffer(&u8g2_Data);
        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
    }
}

void Shift_icon()
{
    u8 k=127;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();

            u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_all_t);
            u8g2_SetFontDirection(&u8g2_Data, 0);
            u8g2_DrawGlyph(&u8g2_Data,50,40,0x29D);
            k--;
            if(k==0)
            k=127;
        u8g2_SendBuffer(&u8g2_Data);
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
        u8g2_SetFont(&u8g2_Data, u8g2_font_unifont_t_weather);
        u8g2_SetFontDirection(&u8g2_Data, 0);
        u8g2_DrawGlyph(&u8g2_Data,32,16,0x22+i);
        u8g2_SendBuffer(&u8g2_Data);
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
    u8 i=3;	
    u8 x0=60,y0=50;
    u8 x,y;
    Time=xTaskGetTickCount();
    while (1)
    {
        taskENTER_CRITICAL();
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
            u8g2_SetFontMode(&u8g2_Data,0);
            u8g2_SetDrawColor(&u8g2_Data,1);
            u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
            u8g2_SetFontDirection(&u8g2_Data, i);
            u8g2_DrawGlyph(&u8g2_Data,x,y,0x36);
            if(i ==0)
            {
                i=4;
            }
            i--;
        u8g2_SendBuffer(&u8g2_Data);

        taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,200/portTICK_PERIOD_MS);
    }
}




void Clear_Task()
{
    TickType_t Time;	
    Time=xTaskGetTickCount();

    while (1)
    {
        u8g2_SendBuffer(&u8g2_Data);
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


void Teat_Task()
{

	TickType_t Time;
	Time=xTaskGetTickCount();
    while (1)
    {
        u8g2_SetFontMode(&u8g2_Data,0);
            u8g2_SetDrawColor(&u8g2_Data,0);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,0,21,0x36);
            u8g2_SetDrawColor(&u8g2_Data,1);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,21,21,0x36);
            u8g2_SetDrawColor(&u8g2_Data,2);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,42,21,0x36);
       u8g2_SetFontMode(&u8g2_Data,1);
            u8g2_SetDrawColor(&u8g2_Data,0);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,0,45,0x36);
            u8g2_SetDrawColor(&u8g2_Data,1);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,21,45,0x36);
            u8g2_SetDrawColor(&u8g2_Data,2);
                u8g2_SetFont(&u8g2_Data, u8g2_font_streamline_interface_essential_action_t);
                u8g2_DrawGlyph(&u8g2_Data,42,45,0x36);              
        u8g2_SendBuffer(&u8g2_Data);
        vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);

    }
    
}




void Switch_Task()
{
    u8 Data=0;
    u8 ID,Num;
    char Char[3];

    while (1)
    {
        if( xQueueReceive(USART1_TaskHandle,&Data,1) == pdPASS )
        {
            ID = Data>>4;
            Num = Data&0x0F;
            switch (ID)
            {
            case 1:
               if ( Num == 0)
                {
                    vTaskSuspend(LED_T);
                }
                else
                {
                    vTaskResume(LED_T);
                }
                break;
             case 2:
               if ( Num == 0)
                {
                    vTaskSuspend(u8g2_Safe_T);
                }
                else
                {
                    vTaskResume(u8g2_Safe_T);
                }
                break;
            case 3:
               if ( Num == 0)
                {
                    vTaskSuspend(u8g2_Dir_T);
                }
                else
                {
                    vTaskResume(u8g2_Dir_T);
                }
                break;
            case 4:
               if ( Num == 0)
                {
                    vTaskSuspend(u8g2_Battery_T);
                }
                else
                {
                    vTaskResume(u8g2_Battery_T);
                }
                break;          
            default:
                break;
            }
            sprintf(Char,"%x",Data);

            u8g2_SetFontMode(&u8g2_Data,0);
            u8g2_SetDrawColor(&u8g2_Data,1);
            u8g2_SetFont(&u8g2_Data, u8g2_font_5x7_tr);
            u8g2_DrawStr(&u8g2_Data, 1,54,Char);
        u8g2_SendBuffer(&u8g2_Data);

        }
        taskYIELD();
    }

}






void u8g2_TaskCreate()
{

    USART1_TaskHandle = xQueueCreate(10,sizeof(u8));

    if( USART1_TaskHandle == NULL)
    {
        vTaskDelete(NULL);
    }

    xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",200,NULL,10,&u8g2_Battery_T);
    xTaskCreate( (TaskFunction_t)LED_Task,    "IconTask",200,NULL,8,&LED_T);
    xTaskCreate( (TaskFunction_t)Safe_icon,    "IconTask",200,NULL,10, &u8g2_Safe_T);
    xTaskCreate( (TaskFunction_t)Dir_icon,    "IconTask",200,NULL,10, &u8g2_Dir_T);
    xTaskCreate( (TaskFunction_t)Switch_Task,   "IconTask",200,NULL,12, NULL);

    // xTaskCreate( (TaskFunction_t)Streamline_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Shift_icon,    "IconTask",200,NULL,10,            NULL);
  xTaskCreate( (TaskFunction_t)Round_Task,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Moon_Task,    "IconTask",200,NULL,10,            NULL);

   //xTaskCreate( (TaskFunction_t)Teat_Task,    "IconTask",200,NULL,10,            NULL);
   //xTaskCreate( (TaskFunction_t)Clear_Task,    "IconTask",200,NULL,10,            NULL);
}


















// …¡À∏…Ë÷√
//     u8g2_SetFontMode(&u8g2,x); x=1ªÚ0
//     u8g2_SetDrawColor(&u8g2,2);∆Ù”√…¡À∏
//      u8g2_SetDrawColor(&u8g2,1);πÿ±’…¡À∏
//     delay();




