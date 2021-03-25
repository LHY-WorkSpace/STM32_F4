#include "IncludeFile.h"


u16 Distance;

void HC_SR04_Init()
{


		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

		GPIO_InitTypeDef GPIO_InitTypeDefinit;
	
	
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_3;                           //trig--------PA3
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;	
		GPIO_Init(GPIOA,&GPIO_InitTypeDefinit);



/*	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
		GPIO_InitTypeDef GPIO_InitTypeDefinit;
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
	
		TIM_ICInitTypeDef TIM_ICInitTypeDefinit;
	
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_3;                           //trig--------PA3
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;	
		GPIO_Init(GPIOA,&GPIO_InitTypeDefinit);
		
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_2;                           //echo--------PA2-CH3
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;		
		GPIO_Init(GPIOA,&GPIO_InitTypeDefinit);	
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
	
		TIM_TimeBaseInitStr.TIM_Prescaler=8400-1;           //0.1ms
		TIM_TimeBaseInitStr.TIM_Period=60000;
		TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);
	
		TIM_ICInitTypeDefinit.TIM_Channel=TIM_Channel_3;
		TIM_ICInitTypeDefinit.TIM_ICPolarity=TIM_ICPolarity_Rising;
		TIM_ICInitTypeDefinit.TIM_ICSelection=TIM_ICSelection_DirectTI;
		TIM_ICInitTypeDefinit.TIM_ICPrescaler=TIM_ICPSC_DIV1;
		TIM_ICInitTypeDefinit.TIM_ICFilter=0x00;

		TIM_ICInit(TIM2,&TIM_ICInitTypeDefinit);

		TIM_ARRPreloadConfig(TIM2,DISABLE);
		TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);
		TIM_Cmd(TIM2,ENABLE);

		System_ResetState(Dev_HCSR04,F_HCSR04_HIGH);
*/


}


// TIM_SelectInputTrigger(TIM2,);





void HCSR04_StartMeasure()
{

	TRIG_H;
	delay_ms(10);
	TRIG_L;
	System_ResetState(Dev_HCSR04,F_HCSR04_DataReady);

}

// unit : cm
u16 HCSR04_GetData()
{
	if (System_GetState(Dev_HCSR04,F_HCSR04_DataReady) == SET )
	{

	return 3*Distance;	

	}
	else
	{


		return 0xFFFF;

	}



}











void TIM2_IRQHandler()
{

	if(	
		System_GetState(Dev_HCSR04,F_HCSR04_DataReady) == SET  || 
	    TIM_GetITStatus(TIM2,TIM_IT_Update) == SET
	   )
	{
		TIM2->CNT=0;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		return;
	}

	if(System_GetState(Dev_HCSR04,F_HCSR04_HIGH) != SET)      //Now is Low Voltage , So Capture  Rising   
	{
		if( TIM_GetITStatus(TIM2,TIM_IT_CC1) != RESET )
		{

			TIM_OC1PolarityConfig(TIM2,TIM_OCPolarity_Low);
			TIM2->CNT=0;
			System_SetState(Dev_HCSR04,F_HCSR04_HIGH);
		}
		
	}
	else
	{
		if( TIM_GetITStatus(TIM2,TIM_IT_CC1) != RESET )
		{

			TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);
			Distance=TIM2->CNT;
			System_ResetState(Dev_HCSR04,F_HCSR04_HIGH);
			System_SetState(Dev_HCSR04,F_HCSR04_DataReady);
		}
		
	}

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update|TIM_IT_CC1);
}



























