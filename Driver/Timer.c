#include "IncludeFile.h"



// 84Mhz:T1,T8,T9,T10,T11
// 42Mhz:除84之外的


//  Timer_10: Delay计数
//  Timer_9:  Tick计数


static u32 TickCount;
u32 RTOS_DebugTimer;
//************************// 
//  功能描述: Tick计数函数
//  
//  参数: Period中断周期(ms)
//  
//  返回值: 无
//			
//  说明: LVGL 计时器
// 
//************************//  
void TickTimer_Init(u16 Period)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    NVIC_InitTypeDef  NVIC_Initstr;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = Period*10;
	TIM_TimeBaseInitStr.TIM_Prescaler = 16800-1;
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStr);

	NVIC_Initstr.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=8;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

    RTOS_DebugTimer=0;

    TIM_ARRPreloadConfig(TIM9,ENABLE);
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM9,ENABLE);
   
}

//************************// 
//  功能描述: Delay计数函数
//  
//  参数: 无
//  
//  返回值: 无
//
//  说明: 
// 
//************************//  
void Delay_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = 0xFFFFFFFF;
	TIM_TimeBaseInitStr.TIM_Prescaler = 168-1;
    TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStr);
    TIM_ARRPreloadConfig(TIM10,DISABLE);
}

//************************// 
//  功能描述: Delay_us函数
//  
//  参数: 无
//  
//  返回值: 无
//
//  说明: 65535us=65.535ms
// 
//************************//  
void Delay_us(u16 nus)
{
    TIM10->CNT = 0;
    TIM_Cmd(TIM10,ENABLE);
    while (TIM10->CNT < nus);
    TIM_Cmd(TIM10,DISABLE);

}

//************************// 
//  功能描述: Delay_ms函数
//  
//  参数: 无
//  
//  返回值: 无
//
//  说明: 最大65535ms
// 
//************************//  
void Delay_ms(u16 nus)
{
    u16 i; 

    for(i=0;i<nus;i++)
    {   
        TIM10->CNT = 0;
        TIM_Cmd(TIM10,ENABLE);
        while (TIM10->CNT < 1000); 
        TIM_Cmd(TIM10,DISABLE);
    }

}

u32 GetTick()
{
    return TickCount;
}



void TIM1_BRK_TIM9_IRQHandler()
{
    if( TIM_GetFlagStatus(TIM9,TIM_IT_Update) == SET)
    {
        TickCount++;
        //RTOS_DebugTimer++;
        // EnCoderUpdate();
    }
    
    TIM_ClearFlag(TIM9,TIM_IT_Update);
}



	

































