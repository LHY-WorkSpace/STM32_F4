#include"IncludeFile.h"

__align(4) u8 A[1024],B[1024];   //对齐的部分不能在栈里！！！

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
	memset(A,0x51,sizeof(A));

		Programe_Start();
 		SD_WriteMultiBlocks(A,0, 512,sizeof(A)/512); 
		printf("Times:%d us ",Programe_End_Us());	

		Programe_Start();
 		SD_ReadMultiBlocks(B,0, 512, sizeof(B)/512);//块数参数不能为1 
		printf("Times:%d us ",Programe_End_Us());	

	for(k=0;k<sizeof(B);k++)
	printf("Data %d : %x \r\n",k,B[k]);

}





int  main()
{


 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	SD_Init();
	// IIC_Init();
	// // MPU6050_Init();






	// AT24C08_Test();
	 SDIO_Test();
	

	while(1)
	{	
		// Programe_Start();
		// MPU6050_Test();
		// printf("Times:%d ms ",Programe_End()/1000);	
		LED1_OFF;
		delay_ms(100);
		LED1_ON;
		delay_ms(100);

	}



	
}	

	












