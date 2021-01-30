#include "CODE_RUN_TIME.h"
#include "stm32f4xx.h"
#include "led.h"


extern u8 Set_Time; 


void Programe_Start(void)
{
	
	    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		  NVIC_InitTypeDef NVIC_InitStructure;
	
	
	
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
			TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStruct.TIM_Period=10000-1;                         //10ms
			TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;                   
	    TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=9;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_ARRPreloadConfig(TIM6,ENABLE);
	TIM_Cmd(TIM6,DISABLE);
	

}

u32 Programe_End()
{

return TIM_GetCounter(TIM6);


}


void TIM6_DAC_IRQHandler()
{
	
	static u32 water_times=0,fan_time=0;
	
		if(TIM_GetFlagStatus(TIM6,TIM_IT_Update)==1)
		{
		water_times++;
		fan_time++;	
			if(water_times>(Set_Time*100))
			{
//			printf("%d\r\n",times);
			WATER_OFF;
			water_times=0;
			TIM_Cmd(TIM6,DISABLE);
			}



		}


TIM_ClearFlag(TIM6,TIM_IT_Update);


}



