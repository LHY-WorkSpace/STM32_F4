#include"IncludeFile.h"





//#define u8unsigned char
//#define u32 unsigned int 

void hcsr_gpio_init()
{
	
	
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
		GPIO_InitTypeDef GPIO_InitTypeDefinit;
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInit;
	
		TIM_ICInitTypeDef TIM_ICInitTypeDefinit;
	
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_5;                           //trig--------PC5
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;	

		GPIO_Init(GPIOB,&GPIO_InitTypeDefinit);
		
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_6;                           //echo--------PC6
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
	//	GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;		
		
		GPIO_Init(GPIOB,&GPIO_InitTypeDefinit);	
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	
	
		TIM_TimeBaseInit.TIM_Prescaler=84-1;
		TIM_TimeBaseInit.TIM_Period=	
		TIM_TimeBaseInit.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1;

		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInit);
	
		TIM_ICInitTypeDefinit.TIM_Channel=TIM_Channel_1;
		TIM_ICInitTypeDefinit.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
		TIM_ICInitTypeDefinit.TIM_ICSelection=TIM_ICSelection_DirectTI;
		TIM_ICInitTypeDefinit.TIM_ICPrescaler=TIM_ICPSC_DIV1;
		TIM_ICInitTypeDefinit.TIM_ICFilter=0x00;

		TIM_ICInit(TIM3,&TIM_ICInitTypeDefinit);
	




	
	
	



}








void start_measure(void)
{

	
	
	









}



























