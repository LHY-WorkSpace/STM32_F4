#include"IncludeFile.h"

/*





124





*/





u8 i=0;

char ss[1];


float P,Y,R;



int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	IIC_Init();
	OLED_Init();
	MPU6050_Init();


	MPU6050_Get_DMP_Data(&P,&Y,&R);
	
	printf("P:%f Y:%f R:%f\r\n",P,Y,R);

	OLED_ShowStrings(0,0,ss,1);

	OLED_UpdateGRAM();	


	while(1)
	{	


		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);






	}



	
}	

	












