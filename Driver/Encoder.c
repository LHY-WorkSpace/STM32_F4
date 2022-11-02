#include "IncludeFile.h"

//转一周多少个信号
#define ENCODER_LINES   (10)



// Timer_2
//  D12 D13 
void EncoderInit()
{

	GPIO_InitTypeDef Encoder_GPIO_Init;

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

    //T1 T2 均计数(4倍频计数)，IC1 不反相,IC2 不反相
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    
}





















