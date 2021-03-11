#include "IncludeFile.h"




int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	IIC_Init();
	OLED_Init();
	MPU6050_Init();

	MPU6050_Test();
	AT24C08_Test();
	// OLED_ShowStrings(0,0,ss,1);

	// OLED_UpdateGRAM();	


	while(1)
	{	


		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);






	}



	
}	

	












