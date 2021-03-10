#include"IncludeFile.h"

/*





124





*/





u8 i=0;

char ss[1];






int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	OLED_Init();



//show_All();

	while(1)
	{	


		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);
	OLED_ShowStrings(0,0,ss,1);
	OLED_UpdateGRAM();	
	ss[0]='!'+(i++);



	}



	
}	

	












