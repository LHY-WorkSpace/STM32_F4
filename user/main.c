#include "IncludeFile.h"




int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_EVEN);
	led_init();
	OLED_Init();
	OLED_SetScanFre(15,0);
	OLED_SetTwinkMode(Twink_Mode,0);
	OLED_ShowStrings(0,0,"0123456789098765ABCDEFGHIJKLMNOPabcdefghijklmnop~!@#$%^&*()_+{}|",64);
	OLED_UpdateGRAM();
	while(1)
	{	


		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);







	}



	
}	

	












