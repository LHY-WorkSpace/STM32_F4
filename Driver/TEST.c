#include "IncludeFile.h"


__align(4) u8 A[1024],B[2048];   //对齐的部分不能在栈里！！！


__ALIGN_BEGIN 
USB_OTG_CORE_HANDLE USB_OTG_dev 
__ALIGN_END;
USB_OTG_CORE_ID_TypeDef coreID=USB_OTG_FS_CORE_ID;


void USB_Task()
{
	USBD_Init(&USB_OTG_dev,coreID,&USR_desc,&USBD_MSC_cb, &USR_cb);
//           https://blog.csdn.net/zhengnianli/article/details/113931569    LVGL
}



void MPU6050_Test()
{
	float pitch,yaw,roll; 
	// char PData[6];
	// char YData[6];
	// char RData[6];
	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);
	// sprintf(PData,"%3.2f",pitch);
	// sprintf(YData,"%3.2f",yaw);
	// sprintf(RData,"%3.2f",roll);

	// OLED_ShowStrings(50,0,PData,6);
	// OLED_ShowStrings(50,1,YData,6); 
	// OLED_ShowStrings(50,2,RData,6);
	// OLED_UpdateGRAM();


}
	

void AT24C08_Test()
{
	u8 A[256],B[256];
	u16 k;

	// memset(A,0X12,256);
	// AT24C08WriteData(AT24C08_BLOCK1,0,256,A);
	// memset(A,0X34,256);
	// AT24C08WriteData(AT24C08_BLOCK2,0,256,A);
	// memset(A,0X56,256);
	// AT24C08WriteData(AT24C08_BLOCK3,0,256,A);
	// memset(A,0X78,256);
	// AT24C08WriteData(AT24C08_BLOCK4,0,256,A);

 	// AT24C08ReadData(AT24C08_BLOCK1,0,256,B);
	// for(k=0;k<256;k++)
	// {
 	// printf("%d EE1:%x \r\n",k,B[k]);	
	// }

 	// AT24C08ReadData(AT24C08_BLOCK2,0,256,B);
	// for(k=0;k<256;k++)
	// {
 	// printf("%d EE2:%x \r\n",k,B[k]);	
	// }

	// AT24C08ReadData(AT24C08_BLOCK3,0,256,B);
	// for(k=0;k<256;k++)
	// {
 	// printf("%d EE3:%x \r\n",k,B[k]);	
	// }

	// AT24C08ReadData(AT24C08_BLOCK4,0,256,B);
	// for(k=0;k<256;k++)
	// {
 	// printf("%d EE4:%x \r\n",k,B[k]);	
	// }


}	
		
void SDIO_Test()
{
	u16 k;

	Programe_StartRun();
	SD_ShowInfomation();
	Programe_End_Us(0);

	memset(A,0x5A,sizeof(A));

	Programe_StartRun();
	SD_WriteMultiBlocks(A,1024, 512,sizeof(A)/512); 
	Programe_End_Us(0);	
	
	Programe_StartRun();
	SD_ReadMultiBlocks(B,0, 512, sizeof(B)/512);
	Programe_End_Us(0);	

	for(k=0;k<sizeof(B);k++)
	printf("Data %d : %x \r\n",k,B[k]);

}

void RTC_Test()
{
		Programe_StartRun();
		RTC_Get_Time(&STM32_Time);
		Programe_End_Us(0);
		printf("Y:%d M:%d D:%d W:%d H:%d M:%d S:%d\r\n",STM32_Time.year,STM32_Time.month,STM32_Time.date,STM32_Time.week,STM32_Time.hour,STM32_Time.minute,STM32_Time.second);

}

void SD_Test()
{
	u8 Data[20];
	FIL fils;
	DIR dp;
	File_FATFSInit();
	File_MountDisk("1:");
	File_Mkdir("1:/SD");
	File_OpenDir("1:/SD",&dp);
	File_CreateNewFile("1:/SD/Data.c",&fils);
	File_WriteData(&fils,"1:/SD/Data.c",(u8*)"Working!!",10,0);
	File_WriteData(&fils,"1:/SD/Data.c",(u8*)"add Test",9,10);
	File_ReadData(&fils,"1:/SD/Data.c",Data,10,10);
	//File_CloseDir();

}


void RNG_Test()
{







	
}

void OLED_Test()
{
 static u8  i=0;
	char s[1];

	if(i>=50)
		i=0;
	s[0]='!'+i;
	OLED_ShowStrings(0,1,s,1);
	
	i++;

	OLED_UpdateGRAM();	


}

void Led_Test()
{
	static u8 i=0;

	if(i)
	{
			LED1_OFF;
			delay_ms(500);
			printf("LED关\r\n");
	}
	else
	{
			LED1_ON;
			delay_ms(500);
			printf("LED开\r\n");
	}

	i=~i;

}





void Task_List()
{

/*

循环里添加各种标志查询，用于后边各种任务置位
例如显示状态等，收发状态等

*/

			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{

				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				
			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			

				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_50ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_100ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
			{


				System_ResetState(Task_TimeFlag,Task_200ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
			{
			
				
				//Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
				//OLED_ClearScreen(0x00);
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}











