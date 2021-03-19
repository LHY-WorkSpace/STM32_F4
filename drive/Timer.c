#include "IncludeFile.h"




u8 Task_Flag=0;



//10ms÷–∂œ“ª¥Œ
void Timer9_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    NVIC_InitTypeDef  NVIC_Initstr;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period=10000;
	TIM_TimeBaseInitStr.TIM_Prescaler=84-1;
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStr);



	NVIC_Initstr.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);




    TIM_ARRPreloadConfig(TIM9,ENABLE);
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM9,ENABLE);
   
}


void TIM1_BRK_TIM9_IRQHandler()
{
    if( TIM_GetFlagStatus(TIM9,TIM_IT_Update) == SET)
    {
        if( Task_Flag < 11 )
        {
            Task_Flag++;
        }
        else
        {
            Task_Flag=0;
        }

    }

    TIM_ClearFlag(TIM9,TIM_IT_Update);
}





































