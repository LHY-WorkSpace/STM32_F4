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


//***************************************************//
//  功能描述: 
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
void u8g2_Init()
{
    OLED_Init();
    #if(OLED_TYPE == SSD1306)
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2_Data, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
    #elif(OLED_TYPE == SH1106)
    u8g2_Setup_sh1106_128x64_noname_f(&u8g2_Data, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
    #else
    #warning "显示设备未适配"
    #endif
	u8g2_InitDisplay(&u8g2_Data);
	u8g2_SetPowerSave(&u8g2_Data, 0);
    u8g2_ClearDisplay(&u8g2_Data);
}





void u8g2_Logo(u8g2_t *u8g2)
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
    u8g2_ClearBuffer(&u8g2_Data);
    u8g2_DrawXBM(&u8g2_Data,0,8,128,48,FreeRTOS_Logo);
    u8g2_SendBuffer(&u8g2_Data);
    Delay_ms(500);
    u8g2_ClearBuffer(&u8g2_Data);
}


void Display_U8g2_Logo()
{

    u8g2_Logo(&u8g2_Data);
    u8g2_SendBuffer(&u8g2_Data); 
    Delay_ms(500);  
    u8g2_ClearBuffer(&u8g2_Data);
}

    #define CIRCLE_SEC_X 60
    #define CIRCLE_SEC_Y 30
    #define CIRCLE_SEC_R 15

// void Clock()
// {
//         int8_t x0,y0;
//       static int8_t  sec=0;


//         // arm_sin_cos_f32();
//              u8g2_ClearBuffer(&u8g2_Data);  
//         u8g2_DrawCircle(&u8g2_Data,CIRCLE_SEC_X,CIRCLE_SEC_Y,CIRCLE_SEC_R,U8G2_DRAW_ALL);
//        x0 = CIRCLE_SEC_X + (int8_t)(FastSin(DEGTORAD(sec*6.0f))*CIRCLE_SEC_R);
//        y0 = CIRCLE_SEC_Y - (int8_t)(CIRCLE_SEC_R*FastCos(DEGTORAD(sec*6.0f)));
//        u8g2_DrawLine(&u8g2_Data,CIRCLE_SEC_X, CIRCLE_SEC_Y, x0, y0);
//        sec++;
//        if(sec == 60)
//         sec=0;
//           u8g2_SendBuffer(&u8g2_Data);
// }








void DispalyUTF_8Strings()
{   
    u8g2_ClearBuffer(&u8g2_Data);
    u8g2_SetFontMode(&u8g2_Data,0);
    u8g2_SetFont(&u8g2_Data, u8g2_font_6x12_tr);
    u8g2_DrawUTF8(&u8g2_Data,10,10,"STM32 U8g2");

    u8g2_DrawButtonUTF8(&u8g2_Data,40,40,U8G2_BTN_HCENTER|U8G2_BTN_BW1|U8G2_BTN_SHADOW1,0,1,1,"OK");
    u8g2_SendBuffer(&u8g2_Data); 
     u8g2_ClearBuffer(&u8g2_Data);
    Delay_ms(500);
    u8g2_DrawButtonUTF8(&u8g2_Data,41,41,U8G2_BTN_HCENTER|U8G2_BTN_BW1,0,1,1,"FreeRTOS");
    u8g2_SendBuffer(&u8g2_Data);   
    Delay_ms(500);
}

void Mov(u16 x,u16 y)
{
    char Data[6];

    // u8g2_ClearBuffer(&u8g2_Data);
    // u8g2_DrawButtonUTF8(&u8g2_Data,40,40,U8G2_BTN_HCENTER|U8G2_BTN_BW1|U8G2_BTN_SHADOW1,0,1,1,"OK");
    u8g2_ClearBuffer(&u8g2_Data);
    memset(Data,0x00,sizeof(Data)-1);
    
    sprintf(Data+1,"%d",x);
    Data[0]='x';
    u8g2_DrawUTF8(&u8g2_Data,x,y+8,Data);
    sprintf(Data+1,"%d",y);
    Data[0]='y';
    u8g2_DrawUTF8(&u8g2_Data,x,y+16,Data);
    u8g2_SendBuffer(&u8g2_Data); 


}




void Battery_icon()
{
    u8 k=0,i=0;
    TickType_t Time;	
    Time=xTaskGetTickCount();
    while (1)
    {
        u8g2_ClearBuffer(&u8g2_Data);
        u8g2_SetMaxClipWindow(&u8g2_Data);
        u8g2_DrawXBM(&u8g2_Data,0,8,128,48,FreeRTOS_Logo);

        u8g2_SetFontMode(&u8g2_Data,0);
        u8g2_SetDrawColor(&u8g2_Data,1);

        u8g2_SetFont(&u8g2_Data, u8g2_font_battery19_tn);
        u8g2_SetFontDirection(&u8g2_Data, 1);
        u8g2_DrawGlyph(&u8g2_Data,-1,50,0x30+k);
        k++;
        if(k==7)
        k=0;

        u8g2_SetClipWindow(&u8g2_Data,0,0,128,40);
        u8g2_SetFontDirection(&u8g2_Data,0);
        u8g2_SetFont(&u8g2_Data, u8g2_font_6x12_tr);
        u8g2_DrawUTF8(&u8g2_Data,i-20,20,"Data");
        u8g2_SetContrast(&u8g2_Data,i);
        i++;
        if(i>=160)
        i=0;
        u8g2_SendBuffer(&u8g2_Data);

        vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
    }

}



void u8g2_TaskCreate()
{


    xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",300,NULL,10,NULL);
    // xTaskCreate( (TaskFunction_t)Safe_icon,    "IconTask",200,NULL,10, &u8g2_Safe_T);
    // xTaskCreate( (TaskFunction_t)Dir_icon,    "IconTask",200,NULL,10, &u8g2_Dir_T);
    // xTaskCreate( (TaskFunction_t)Switch_Task,   "IconTask",200,NULL,12, NULL);

    // xTaskCreate( (TaskFunction_t)Streamline_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Shift_icon,    "IconTask",200,NULL,10,            NULL);
//   xTaskCreate( (TaskFunction_t)Round_Task,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Moon_Task,    "IconTask",200,NULL,10,            NULL);

   //xTaskCreate( (TaskFunction_t)Teat_Task,    "IconTask",200,NULL,10,            NULL);
   //xTaskCreate( (TaskFunction_t)Clear_Task,    "IconTask",200,NULL,10,            NULL);
   	vTaskDelete(NULL);
}





void u8g2_Task()
{
    TickType_t Time;	

    Time=xTaskGetTickCount();

    while (1)
    {
        u8g2_ClearBuffer(&u8g2_Data);







        // taskENTER_CRITICAL();
        u8g2_SendBuffer(&u8g2_Data);
        // taskEXIT_CRITICAL();
        vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}












// ?????è??
//     u8g2_SetFontMode(&u8g2,x); x=1?ò0
//     u8g2_SetDrawColor(&u8g2,2);????????
//      u8g2_SetDrawColor(&u8g2,1);??±?????
//     delay();




