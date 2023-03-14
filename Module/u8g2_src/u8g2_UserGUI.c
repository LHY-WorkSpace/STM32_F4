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
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2_Data, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
	u8g2_InitDisplay(&u8g2_Data);
	u8g2_SetPowerSave(&u8g2_Data, 0);
     u8g2_ClearDisplay(&u8g2_Data);
}


void ShowDS18B20TempData(char *Data)
{
    u8g2_ClearBuffer(&u8g2_Data);
    u8g2_SetFont(&u8g2_Data, u8g2_font_10x20_tr);
    u8g2_DrawStr(&u8g2_Data, 1,20,Data);	
    // u8g2_SendBuffer(&u8g2_Data);

}



void ShowTempData(char *Data)
{
    u8g2_SetFont(&u8g2_Data, u8g2_font_10x20_tr);
    u8g2_DrawStr(&u8g2_Data, 1,60,Data);	
    // u8g2_SendBuffer(&u8g2_Data);

}

void ShowHumanityData(char *Data)
{
    // u8g2_ClearBuffer(&u8g2_Data);
    u8g2_SetFont(&u8g2_Data, u8g2_font_10x20_tr);
    u8g2_DrawStr(&u8g2_Data, 1,40,Data);	
    u8g2_SendBuffer(&u8g2_Data);
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

void ClearDisplay()
{
    u8g2_ClearBuffer(&u8g2_Data);
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

void Test_UI()
{
    static s16 x= -150;
     u8g2_ClearBuffer(&u8g2_Data);
	u8g2_SetFont(&u8g2_Data,u8g2_font_open_iconic_app_2x_t);
    u8g2_DrawGlyph(&u8g2_Data,12+2*x,30,69);
    u8g2_DrawGlyph(&u8g2_Data,12+2*x+70,30,72);
    u8g2_DrawGlyph(&u8g2_Data,12+2*x+140,30,65);
    u8g2_DrawGlyph(&u8g2_Data,12+2*x+210,30,70);
    u8g2_DrawGlyph(&u8g2_Data,12+2*x+280,30,71);
	u8g2_SetFont(&u8g2_Data,u8g2_font_sirclivethebold_tr);
	u8g2_DrawStr(&u8g2_Data,18-2*x,50,"RTC");
	u8g2_DrawStr(&u8g2_Data,18-2*x-75,50,"STW");
	u8g2_DrawStr(&u8g2_Data,18-2*x-150,50,"SET");
	u8g2_DrawStr(&u8g2_Data,18-2*x-225,50,"AHRS");
	u8g2_DrawStr(&u8g2_Data,18-2*x-300,50,"GAME");
    u8g2_SendBuffer(&u8g2_Data);
    x++;
}
// #define FAST_SIN_TABLE_SIZE 512
// const float sinTable[FAST_SIN_TABLE_SIZE + 1] = {
// 	0.00000000f, 0.01227154f, 0.02454123f, 0.03680722f, 0.04906767f, 0.06132074f,
// 	0.07356456f, 0.08579731f, 0.09801714f, 0.11022221f, 0.12241068f, 0.13458071f,
// 	0.14673047f, 0.15885814f, 0.17096189f, 0.18303989f, 0.19509032f, 0.20711138f,
// 	0.21910124f, 0.23105811f, 0.24298018f, 0.25486566f, 0.26671276f, 0.27851969f,
// 	0.29028468f, 0.30200595f, 0.31368174f, 0.32531029f, 0.33688985f, 0.34841868f,
// 	0.35989504f, 0.37131719f, 0.38268343f, 0.39399204f, 0.40524131f, 0.41642956f,
// 	0.42755509f, 0.43861624f, 0.44961133f, 0.46053871f, 0.47139674f, 0.48218377f,
// 	0.49289819f, 0.50353838f, 0.51410274f, 0.52458968f, 0.53499762f, 0.54532499f,
// 	0.55557023f, 0.56573181f, 0.57580819f, 0.58579786f, 0.59569930f, 0.60551104f,
// 	0.61523159f, 0.62485949f, 0.63439328f, 0.64383154f, 0.65317284f, 0.66241578f,
// 	0.67155895f, 0.68060100f, 0.68954054f, 0.69837625f, 0.70710678f, 0.71573083f,
// 	0.72424708f, 0.73265427f, 0.74095113f, 0.74913639f, 0.75720885f, 0.76516727f,
// 	0.77301045f, 0.78073723f, 0.78834643f, 0.79583690f, 0.80320753f, 0.81045720f,
// 	0.81758481f, 0.82458930f, 0.83146961f, 0.83822471f, 0.84485357f, 0.85135519f,
// 	0.85772861f, 0.86397286f, 0.87008699f, 0.87607009f, 0.88192126f, 0.88763962f,
// 	0.89322430f, 0.89867447f, 0.90398929f, 0.90916798f, 0.91420976f, 0.91911385f,
// 	0.92387953f, 0.92850608f, 0.93299280f, 0.93733901f, 0.94154407f, 0.94560733f,
// 	0.94952818f, 0.95330604f, 0.95694034f, 0.96043052f, 0.96377607f, 0.96697647f,
// 	0.97003125f, 0.97293995f, 0.97570213f, 0.97831737f, 0.98078528f, 0.98310549f,
// 	0.98527764f, 0.98730142f, 0.98917651f, 0.99090264f, 0.99247953f, 0.99390697f,
// 	0.99518473f, 0.99631261f, 0.99729046f, 0.99811811f, 0.99879546f, 0.99932238f,
// 	0.99969882f, 0.99992470f, 1.00000000f, 0.99992470f, 0.99969882f, 0.99932238f,
// 	0.99879546f, 0.99811811f, 0.99729046f, 0.99631261f, 0.99518473f, 0.99390697f,
// 	0.99247953f, 0.99090264f, 0.98917651f, 0.98730142f, 0.98527764f, 0.98310549f,
// 	0.98078528f, 0.97831737f, 0.97570213f, 0.97293995f, 0.97003125f, 0.96697647f,
// 	0.96377607f, 0.96043052f, 0.95694034f, 0.95330604f, 0.94952818f, 0.94560733f,
// 	0.94154407f, 0.93733901f, 0.93299280f, 0.92850608f, 0.92387953f, 0.91911385f,
// 	0.91420976f, 0.90916798f, 0.90398929f, 0.89867447f, 0.89322430f, 0.88763962f,
// 	0.88192126f, 0.87607009f, 0.87008699f, 0.86397286f, 0.85772861f, 0.85135519f,
// 	0.84485357f, 0.83822471f, 0.83146961f, 0.82458930f, 0.81758481f, 0.81045720f,
// 	0.80320753f, 0.79583690f, 0.78834643f, 0.78073723f, 0.77301045f, 0.76516727f,
// 	0.75720885f, 0.74913639f, 0.74095113f, 0.73265427f, 0.72424708f, 0.71573083f,
// 	0.70710678f, 0.69837625f, 0.68954054f, 0.68060100f, 0.67155895f, 0.66241578f,
// 	0.65317284f, 0.64383154f, 0.63439328f, 0.62485949f, 0.61523159f, 0.60551104f,
// 	0.59569930f, 0.58579786f, 0.57580819f, 0.56573181f, 0.55557023f, 0.54532499f,
// 	0.53499762f, 0.52458968f, 0.51410274f, 0.50353838f, 0.49289819f, 0.48218377f,
// 	0.47139674f, 0.46053871f, 0.44961133f, 0.43861624f, 0.42755509f, 0.41642956f,
// 	0.40524131f, 0.39399204f, 0.38268343f, 0.37131719f, 0.35989504f, 0.34841868f,
// 	0.33688985f, 0.32531029f, 0.31368174f, 0.30200595f, 0.29028468f, 0.27851969f,
// 	0.26671276f, 0.25486566f, 0.24298018f, 0.23105811f, 0.21910124f, 0.20711138f,
// 	0.19509032f, 0.18303989f, 0.17096189f, 0.15885814f, 0.14673047f, 0.13458071f,
// 	0.12241068f, 0.11022221f, 0.09801714f, 0.08579731f, 0.07356456f, 0.06132074f,
// 	0.04906767f, 0.03680722f, 0.02454123f, 0.01227154f, 0.00000000f, -0.01227154f,
// 	-0.02454123f, -0.03680722f, -0.04906767f, -0.06132074f, -0.07356456f,
// 	-0.08579731f, -0.09801714f, -0.11022221f, -0.12241068f, -0.13458071f,
// 	-0.14673047f, -0.15885814f, -0.17096189f, -0.18303989f, -0.19509032f, 
// 	-0.20711138f, -0.21910124f, -0.23105811f, -0.24298018f, -0.25486566f, 
// 	-0.26671276f, -0.27851969f, -0.29028468f, -0.30200595f, -0.31368174f, 
// 	-0.32531029f, -0.33688985f, -0.34841868f, -0.35989504f, -0.37131719f, 
// 	-0.38268343f, -0.39399204f, -0.40524131f, -0.41642956f, -0.42755509f, 
// 	-0.43861624f, -0.44961133f, -0.46053871f, -0.47139674f, -0.48218377f, 
// 	-0.49289819f, -0.50353838f, -0.51410274f, -0.52458968f, -0.53499762f, 
// 	-0.54532499f, -0.55557023f, -0.56573181f, -0.57580819f, -0.58579786f, 
// 	-0.59569930f, -0.60551104f, -0.61523159f, -0.62485949f, -0.63439328f, 
// 	-0.64383154f, -0.65317284f, -0.66241578f, -0.67155895f, -0.68060100f, 
// 	-0.68954054f, -0.69837625f, -0.70710678f, -0.71573083f, -0.72424708f, 
// 	-0.73265427f, -0.74095113f, -0.74913639f, -0.75720885f, -0.76516727f, 
// 	-0.77301045f, -0.78073723f, -0.78834643f, -0.79583690f, -0.80320753f, 
// 	-0.81045720f, -0.81758481f, -0.82458930f, -0.83146961f, -0.83822471f, 
// 	-0.84485357f, -0.85135519f, -0.85772861f, -0.86397286f, -0.87008699f, 
// 	-0.87607009f, -0.88192126f, -0.88763962f, -0.89322430f, -0.89867447f, 
// 	-0.90398929f, -0.90916798f, -0.91420976f, -0.91911385f, -0.92387953f, 
// 	-0.92850608f, -0.93299280f, -0.93733901f, -0.94154407f, -0.94560733f, 
// 	-0.94952818f, -0.95330604f, -0.95694034f, -0.96043052f, -0.96377607f, 
// 	-0.96697647f, -0.97003125f, -0.97293995f, -0.97570213f, -0.97831737f, 
// 	-0.98078528f, -0.98310549f, -0.98527764f, -0.98730142f, -0.98917651f, 
// 	-0.99090264f, -0.99247953f, -0.99390697f, -0.99518473f, -0.99631261f, 
// 	-0.99729046f, -0.99811811f, -0.99879546f, -0.99932238f, -0.99969882f, 
// 	-0.99992470f, -1.00000000f, -0.99992470f, -0.99969882f, -0.99932238f, 
// 	-0.99879546f, -0.99811811f, -0.99729046f, -0.99631261f, -0.99518473f, 
// 	-0.99390697f, -0.99247953f, -0.99090264f, -0.98917651f, -0.98730142f, 
// 	-0.98527764f, -0.98310549f, -0.98078528f, -0.97831737f, -0.97570213f, 
// 	-0.97293995f, -0.97003125f, -0.96697647f, -0.96377607f, -0.96043052f, 
// 	-0.95694034f, -0.95330604f, -0.94952818f, -0.94560733f, -0.94154407f, 
// 	-0.93733901f, -0.93299280f, -0.92850608f, -0.92387953f, -0.91911385f, 
// 	-0.91420976f, -0.90916798f, -0.90398929f, -0.89867447f, -0.89322430f, 
// 	-0.88763962f, -0.88192126f, -0.87607009f, -0.87008699f, -0.86397286f, 
// 	-0.85772861f, -0.85135519f, -0.84485357f, -0.83822471f, -0.83146961f, 
// 	-0.82458930f, -0.81758481f, -0.81045720f, -0.80320753f, -0.79583690f, 
// 	-0.78834643f, -0.78073723f, -0.77301045f, -0.76516727f, -0.75720885f, 
// 	-0.74913639f, -0.74095113f, -0.73265427f, -0.72424708f, -0.71573083f, 
// 	-0.70710678f, -0.69837625f, -0.68954054f, -0.68060100f, -0.67155895f, 
// 	-0.66241578f, -0.65317284f, -0.64383154f, -0.63439328f, -0.62485949f, 
// 	-0.61523159f, -0.60551104f, -0.59569930f, -0.58579786f, -0.57580819f, 
// 	-0.56573181f, -0.55557023f, -0.54532499f, -0.53499762f, -0.52458968f, 
// 	-0.51410274f, -0.50353838f, -0.49289819f, -0.48218377f, -0.47139674f, 
// 	-0.46053871f, -0.44961133f, -0.43861624f, -0.42755509f, -0.41642956f, 
// 	-0.40524131f, -0.39399204f, -0.38268343f, -0.37131719f, -0.35989504f, 
// 	-0.34841868f, -0.33688985f, -0.32531029f, -0.31368174f, -0.30200595f, 
// 	-0.29028468f, -0.27851969f, -0.26671276f, -0.25486566f, -0.24298018f, 
// 	-0.23105811f, -0.21910124f, -0.20711138f, -0.19509032f, -0.18303989f, 
// 	-0.17096189f, -0.15885814f, -0.14673047f, -0.13458071f, -0.12241068f, 
// 	-0.11022221f, -0.09801714f, -0.08579731f, -0.07356456f, -0.06132074f, 
// 	-0.04906767f, -0.03680722f, -0.02454123f, -0.01227154f, -0.00000000f
// };


// float FastSin(float x)
// {
// 	float sinVal, fract, in; // Temporary variables for input, output
// 	unsigned short index; // Index variable
// 	float a, b; // Two nearest output values
// 	int n;
// 	float findex;

// 	// input x is in radians
// 	// Scale the input to [0 1] range from [0 2*PI] , divide input by 2*pi
// 	in = x * 0.159154943092f;

// 	// Calculation of floor value of input
// 	n = (int) in;

// 	// Make negative values towards -infinity
// 	if(x < 0.0f){
// 		n--;
// 	}

// 	// Map input value to [0 1]
// 	in = in - (float) n;

// 	// Calculation of index of the table
// 	findex = (float) FAST_SIN_TABLE_SIZE * in;
// 	index = ((unsigned short)findex) & 0x1ff;

// 	// fractional value calculation
// 	fract = findex - (float) index;

// 	// Read two nearest values of input value from the sin table
// 	a = sinTable[index];
// 	b = sinTable[index+1];

// 	// Linear interpolation process
// 	sinVal = (1.0f-fract)*a + fract*b;

// 	// Return the output value
// 	return (sinVal);
// }

// float FastCos(float x)
// {
// 	float cosVal, fract, in; // Temporary variables for input, output
// 	unsigned short index; // Index variable
// 	float a, b; // Two nearest output values
// 	int n;
// 	float findex;

// 	// input x is in radians
// 	// Scale the input to [0 1] range from [0 2*PI] , divide input by 2*pi, add 0.25 (pi/2) to read sine table
// 	in = x * 0.159154943092f + 0.25f;

// 	// Calculation of floor value of input
// 	n = (int) in;

// 	// Make negative values towards -infinity
// 	if(in < 0.0f){
// 		n--;
// 	}

// 	// Map input value to [0 1]
// 	in = in - (float) n;

// 	// Calculation of index of the table
// 	findex = (float) FAST_SIN_TABLE_SIZE * in;
// 	index = ((unsigned short)findex) & 0x1ff;

// 	// fractional value calculation
// 	fract = findex - (float) index;

// 	// Read two nearest values of input value from the cos table
// 	a = sinTable[index];
// 	b = sinTable[index+1];

// 	// Linear interpolation process
// 	cosVal = (1.0f-fract)*a + fract*b;

// 	// Return the output value
// 	return (cosVal);
// }
// #define RADTODEG(x) ((x) * 57.295779513082320876798154814105f)
// #define DEGTORAD(x) ((x) * 0.01745329251994329576923690768489f)

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


    xTaskCreate( (TaskFunction_t)Battery_icon,"IconTask",200,NULL,10,&u8g2_Battery_T);
    xTaskCreate( (TaskFunction_t)LED_Task,    "IconTask",200,NULL,8,&LED_T);
    // xTaskCreate( (TaskFunction_t)Safe_icon,    "IconTask",200,NULL,10, &u8g2_Safe_T);
    // xTaskCreate( (TaskFunction_t)Dir_icon,    "IconTask",200,NULL,10, &u8g2_Dir_T);
    // xTaskCreate( (TaskFunction_t)Switch_Task,   "IconTask",200,NULL,12, NULL);

    // xTaskCreate( (TaskFunction_t)Streamline_icon,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Shift_icon,    "IconTask",200,NULL,10,            NULL);
//   xTaskCreate( (TaskFunction_t)Round_Task,    "IconTask",200,NULL,10,            NULL);
    // xTaskCreate( (TaskFunction_t)Moon_Task,    "IconTask",200,NULL,10,            NULL);

   //xTaskCreate( (TaskFunction_t)Teat_Task,    "IconTask",200,NULL,10,            NULL);
   //xTaskCreate( (TaskFunction_t)Clear_Task,    "IconTask",200,NULL,10,            NULL);
}


















// ?????è??
//     u8g2_SetFontMode(&u8g2,x); x=1?ò0
//     u8g2_SetDrawColor(&u8g2,2);????????
//      u8g2_SetDrawColor(&u8g2,1);??±?????
//     delay();




