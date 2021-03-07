#include"IncludeFile.h"



u8 i=1;

int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	OLED_Init();


while(i<120)
{
OLED_Draw_Point(i,i/5+1,1);
i++;
}
		OLED_UpdateGRAM();
// Boot_Animation();
// delay_ms(500);
// OLED_Scroll_Vx(SCROLL_VR,0,0X01,0X00,0X04);


i=1;
	
	while(1)
	{	


		LED1_OFF;
		delay_ms(100);
		LED1_ON;
		delay_ms(100);

OLED_Draw_Point(i-1,(i-1)/5+1,0);
		OLED_UpdateGRAM();
		i++;


	}



	
}	

	












