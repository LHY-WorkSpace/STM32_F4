#include"IncludeFile.h"

u16 Run_Time; 


void Programe_Start(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=50000-1;                         //50ms
	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;                   
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=9;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE);
	TIM_ARRPreloadConfig(TIM6,ENABLE);
	TIM6->CNT = 0;
	TIM_Cmd(TIM6,ENABLE);
	

}

u16 Programe_End_Us()
{

return TIM_GetCounter(TIM6);


}

u16 Programe_End_Ms()
{

return TIM_GetCounter(TIM6)/1000;


}





void TIM6_DAC_IRQHandler()
{
	static u16 Times_1ms=0;
	
		if(TIM_GetFlagStatus(TIM6,TIM_IT_Update)==1)
		{
			Run_Time=++Times_1ms;
			TIM_Cmd(TIM6,DISABLE);

		}


TIM_ClearFlag(TIM6,TIM_IT_Update);


}



