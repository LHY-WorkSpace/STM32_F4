#include"IncludeFile.h"





int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	RTC_Init();









	while(1)
	{	


		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);


	}



	
}	

	












