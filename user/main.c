#include "IncludeFile.h"


u16 P=100;

int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	//led_init();
	RTC_ConfigInit();
	PWM_Init(1,1);

	 PWM_SetPlusePeriod(TIM4,5000);


	while(1)
	{	


		// LED1_OFF;
		// delay_ms(200);
		// LED1_ON;
	delay_ms(200);
	PWM_SetPluseWdie(TIM4,P);
	P+=100;
		








	}



	
}	

	












