#include "IncludeFile.h"
#include "TEST.h"

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

void RTC_ConfigInit()
{
		Programe_Start();
		RTC_Get_Date(&STM32_Time);
		RTC_Get_Time(&STM32_Time);
		printf("Run Time: %d us\r\n",Programe_End_Us());
		printf("Y:%d M:%d D:%d W:%d H:%d M:%d S:%d\r\n",STM32_Time.year,STM32_Time.month,STM32_Time.date,STM32_Time.week,STM32_Time.hour,STM32_Time.minute,STM32_Time.second);

}
void RNG_Test()
{







	
}
