#ifndef ENCODER_H
#define ENCODER_H
// #include "stm32f4xx.h"

//转一周多少个信号
#define ENCODER_LINES   (10)

//按键消抖延时(N*systick*ms)
#define ENCODER_DELAY   (30)

//读按键状态
#define ENCODER_KEY     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)


typedef enum
{
    Encoder_UP,
    Encoder_DOWN

}Encoder_Dir_e;



typedef enum
{
    Encoder_Pressed,
    Encoder_Release
}Encoder_Key_e;



typedef struct
{
    Encoder_Dir_e Dir;
    Encoder_Key_e KeyState;
    u16 Value;

}EnCoderInfo_t;



void EnCoderInit(void);
void EnCoderSetValue(u16 Data);
void EnCoderGetValue(void);
void EnCoderUpdateKey(void);

Encoder_Key_e EnCoderGetKeyState(void);
Encoder_Dir_e EnCoderGetDir(void);

#endif
