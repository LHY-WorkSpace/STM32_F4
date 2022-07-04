#include "IncludeFile.h"

//    四路输出           A6        A7        B0       B1


void PWM_Init(u16 Period,u16 PluseWide)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	GPIO_InitTypeDef LED;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitsruc;
	
	LED.GPIO_Pin=GPIO_Pin_5;
	LED.GPIO_Mode=GPIO_Mode_AF;
	LED.GPIO_Speed=GPIO_Speed_50MHz;
	LED.GPIO_OType=GPIO_OType_PP;
	LED.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOE,&LED);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	
	TIM_TimeBaseInitsruc.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitsruc.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitsruc.TIM_Prescaler=168-1;         /////APB1=42Mhz     
	TIM_TimeBaseInitsruc.TIM_Period=2000-1;          //周期20ms
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitsruc);
	
	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM9,&TIM_OCInitTypestuc);

	TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	TIM_Cmd(TIM9,ENABLE);

}



//设置脉宽(us)
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide)
{
	TIMx->CCR1 = PluseWide-1;
}
//设置周期(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod)
{
	TIMx->ARR = PlusePeriod-1;
}



















