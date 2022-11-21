#include "IncludeFile.h"

//转一周多少个信号
#define ENCODER_LINES   (10)

EnCoderInfo_t EnCoderInfo;

// Timer_2
//  D12 D13 
void EncoderInit()
{

	GPIO_InitTypeDef Encoder_GPIO_Init;
	NVIC_InitTypeDef  NVIC_Initstr;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    Encoder_GPIO_Init.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
    Encoder_GPIO_Init.GPIO_Mode = GPIO_Mode_AF;
    Encoder_GPIO_Init.GPIO_PuPd = GPIO_PuPd_UP;
    Encoder_GPIO_Init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&Encoder_GPIO_Init);

	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = ENCODER_LINES*4-1;//4倍频计数;
	TIM_TimeBaseInitStr.TIM_Prescaler =0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStr);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

	NVIC_Initstr.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=8;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

    //T1 T2 均计数(4倍频计数)，IC1 不反相,IC2 不反相
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    TIM_ClearITPendingBit(TIM4,TIM_IT_Update );
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);

}

static void EnCoderUpData()
{
    if( ( TIM4->CR1  ) & 0x10)
    {
        EnCoderInfo.Dir = Encoder_UP;
    }
    else
    {
        EnCoderInfo.Dir = Encoder_DOWN;
    }
    
    EnCoderInfo.Value = TIM4->CNT;
}







void EnCoderSetValue(u16 Data)
{
    TIM4->CNT = Data;
    EnCoderInfo.Value = Data;
}

void EnCoderGetValue()
{
    return EnCoderInfo.Value;
}

u8 EnCoderGetDir()
{
    return EnCoderInfo.Dir;
}


void TIM4_IRQHandler()
{
    if( TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update );
        EnCoderUpData();
    }
}











