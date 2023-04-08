#include "IncludeFile.h"


// 16λ:T3,T4,T9 - T14
// 32λ:T2,T5

// 84Mhz:T1,T8,T9,T10,T11
// 42Mhz:��84֮���


//  Timer_10: Delay����
//  Timer_9:  LVGL_Tick����
//  Timer_3:  RTOS debug��Ϣ����

static u32 LVGL_TickCount;
//************************// 
//  ��������: LVGL_Tick��������
//  
//  ����: Period�ж�����(ms)
//  
//  ����ֵ: ��
//			
//  ˵��: LVGL ��ʱ��
// 
//************************//  
void LVGL_TimerInit(u16 Period)
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

//***************************************************//
//  ��������: LVGL��ȡ����ֵ
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: ��
//  
//***************************************************//
u32 LVGL_GetTick()
{
    return LVGL_TickCount;
}

void TIM1_BRK_TIM9_IRQHandler()
{
    if( TIM_GetFlagStatus(TIM9,TIM_IT_Update) == SET)
    {
        LVGL_TickCount++;
    }

    TIM_ClearFlag(TIM9,TIM_IT_Update);
}

//************************// 
//  ��������: Delay��������
//  
//  ����: ��
//  
//  ����ֵ: ��
//
//  ˵��: 
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
//  ��������: Delay_us����
//  
//  ����: ��
//  
//  ����ֵ: ��
//
//  ˵��: 65535us=65.535ms
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
//  ��������: Delay_ms����
//  
//  ����: ��
//  
//  ����ֵ: ��
//
//  ˵��: ���65535ms
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


//***************************************************//
//  ��������: RTOS���������Ϣ��ʱ��
//  
//  ����: ��
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: 50 us
//  
//***************************************************//
#if ( configUSE_TRACE_FACILITY == 1 )

u32 RTOS_DebugTimer;

void RTOSDebugTimerInit()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    NVIC_InitTypeDef  NVIC_Initstr;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = 50;
	TIM_TimeBaseInitStr.TIM_Prescaler = 84-1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStr);

	NVIC_Initstr.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

    RTOS_DebugTimer=0;

    TIM_ARRPreloadConfig(TIM3,ENABLE);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
   
}

void TIM3_IRQHandler()
{
    if( TIM_GetFlagStatus(TIM3,TIM_IT_Update) == SET)
    {
        TIM_ClearFlag(TIM3,TIM_IT_Update);
        //RTOS_DebugTimer++;
    }
    
}

#endif
	

































