#ifndef ENCODER_H
#define ENCODER_H
// #include "stm32f4xx.h"

//转一周多少个脉冲
#define ENCODER_LINES   (3)

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
    u16 CNT_REG;
    s32 Pluse_Cnt;
    s32 Circle_Cnt;

}EnCoderInfo_t;



void EnCoderInit(void);
void EnCoderUpdateKey();
void EnCoderUpdate(void);
void EnCoderReset(void);

s32 EnCoderGetPluseCNT(void);
s32 EnCoderGetCircleCNT(void);
Encoder_Key_e EnCoderGetKeyState(void);
Encoder_Dir_e EnCoderGetDir(void);

#endif
