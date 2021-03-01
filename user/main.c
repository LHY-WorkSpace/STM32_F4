#include"IncludeFile.h"

__align(4) u8 A[512],B[2048];   //对齐的部分不能在栈里！！！

void MPU6050_Test()
{
	float pitch,yaw,roll; 
	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);
}
	

void AT24C08_Test()
{
	u8 A[256],B[256];
	u16 k;

	memset(A,0X12,256);
	AT24C08Write_NBytes(AT24C08_BLOCK1,0,256,A);
	memset(A,0X34,256);
	AT24C08Write_NBytes(AT24C08_BLOCK2,0,256,A);
	memset(A,0X56,256);
	AT24C08Write_NBytes(AT24C08_BLOCK3,0,256,A);
	memset(A,0X78,256);
	AT24C08Write_NBytes(AT24C08_BLOCK4,0,256,A);

 	AT24C08Read_NBytes(AT24C08_BLOCK1,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE1:%d \r\n",k,B[k]);	
	}

 	AT24C08Read_NBytes(AT24C08_BLOCK2,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE2:%d \r\n",k,B[k]);	
	}

	AT24C08Read_NBytes(AT24C08_BLOCK3,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE3:%d \r\n",k,B[k]);	
	}

	AT24C08Read_NBytes(AT24C08_BLOCK4,0,256,B);
	for(k=0;k<256;k++)
	{
 	printf("%d EE4:%d \r\n",k,B[k]);	
	}


}	
		
void SDIO_Test()
{
	u16 k;
	SD_ShowInfomation();
	memset(A,0x22,sizeof(A));

		Programe_Start();
 		SD_WriteMultiBlocks(A,512, 512,sizeof(A)/512); 
		printf("Times:%d us \r\n",Programe_End_Us());	
		
		Programe_Start();
 		SD_ReadMultiBlocks(B,0, 512, sizeof(B)/512);
		printf("Times:%d us \r\n",Programe_End_Us());	

	for(k=0;k<sizeof(B);k++)
	printf("Data %d : %x \r\n",k,B[k]);

}





int  main()
{
 
u8 x=0,y=0,x1=0,y1=0;
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	//SD_Init();
	OLED_Init();
	Rng_Init();
	//IIC_Init();
	//MPU6050_Init();
	//windows_open(100);


// Programe_Start();
// // Rng_GetRadomData();
//  OLED_ClearScreen(0x00);
// printf("Run Time: %d us",Programe_End_Us());





	//OLED_Draw_Line(0, 0, 10,10);
	Test();
	//OLED_Draw_FullCircle(30,31,15);
	Boot_Animation();
	OLED_UpdateGRAM();

	while(1)
	{	

		// memset(qq,x,sizeof(qq));
		// OLED_Data2GRAM(qq,1024);
		// OLED_UpdateGRAM();
		// OLED_Draw_Point(x,y,0);
		// OLED_UpdateGRAM();
		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);

		// // OLED_Draw_FullCircle(x,31,30);
		// OLED_Draw_Line(0, 31, 127,31);
		// OLED_Draw_Line(63, 0, 63,63);	
		// y1=Rng_GetRadomData()%64;
		// x1=x+5;
		// // OLED_Draw_Point(x,y,1);
		// OLED_Draw_Line(x, y, x1,y1);
		// OLED_UpdateGRAM();
 


		// if(y)
		// {
		// 	x--;
		// 	if(x==0)
		// 		y=0;
		// }
		// else
		// {
		// 	x++;
		// 	if(x==0xff)
		// 		y=1;
		// }
	//	printf("C %d\r\n",x);




		

	}



	
}	

	












