#include "IncludeFile.h"

u16 Run_Time; 


void Programe_RunInit(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	// NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=50000-1;                         //最大计数值：50ms
	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;                   
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	// NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	// NVIC_Init(&NVIC_InitStructure);
	
	//TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	//TIM_ClearFlag(TIM6,TIM_IT_Update);
	TIM_ARRPreloadConfig(TIM6,ENABLE);
	TIM6->CNT = 0;
	TIM_Cmd(TIM6,DISABLE);
	
}

void Programe_StartRun()
{
	TIM_Cmd(TIM6,DISABLE);
	TIM6->CNT = 0;
	TIM_Cmd(TIM6,ENABLE);
}







u16  Programe_End_Us(u8 Dev)
{
	if( Dev  == 1)
	{
		printf("Time:%d us\r\n",TIM_GetCounter(TIM6));
	}
	else if(Dev  == 2)
	{	
//		OLED_ShowStrings(0,0,"Time-us ",8);
//		OLED_ShowNumber(70,0,TIM_GetCounter(TIM6),6);
//		OLED_UpdateGRAM();
	}

	return TIM_GetCounter(TIM6);

}

u16  Programe_End_Ms(u8 Dev)
{
	
	if( Dev  == 1)
	{
		printf("Time:%d us\r\n",TIM_GetCounter(TIM6)/1000);
	}
	else if(Dev  == 2)
	{	
//		OLED_ShowStrings(0,0,"Time-ms ",8);
//		OLED_ShowNumber(70,0,TIM_GetCounter(TIM6)/1000,6);
//		OLED_UpdateGRAM();
	}

	return TIM_GetCounter(TIM6)/1000;
}


void TIM6_DAC_IRQHandler()
{
	static u16 Times_1ms=0;
	
		if(TIM_GetFlagStatus(TIM6,TIM_IT_Update)==1)
		{
			Run_Time=(++Times_1ms)*50+(TIM6->CNT/1000);
			TIM_Cmd(TIM6,DISABLE);
		}

	TIM_ClearFlag(TIM6,TIM_IT_Update);

}




u8 FALSH_GetSumData(u32 StartAddr,u32 EndAddr,u32 *Data)
{
	u32 Temp = 0;

	if(StartAddr > EndAddr)
	{
		return FALSE;
	}
	
	while ( StartAddr != EndAddr )
	{
		Temp += *StartAddr;
		StartAddr += 4;
	}
}





