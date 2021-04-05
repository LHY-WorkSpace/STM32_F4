#include "IncludeFile.h"





u8 lc=0,i=0;
float pitch,yaw,roll,Dis; 
char gg[7];


u8 Sta;
u32 ss;
u8 Data[1024];


char asd[]="创建 By STM32";
char tt[]="SD-RW!";
u16 times=0;




void Task_List()
{

			
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
				
				// if(times>=8758)
				// {
				// 	Sta=f_close(&fils);
				// }
				// Sta=f_read(&fils,Data,1024,&ss);
				// OLED_Data2GRAM(Data,1024);
				// OLED_UpdateGRAM();
				// times++;
				
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
			
				
				Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
				//OLED_ClearScreen(0x00);
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}

u32 size;



int  main()
{


	memset(Data,0x00,sizeof(Data));
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	TaskTimer_Init();
	File_FATFSInit();
	File_MountDisk("1:");
	File_OpenDir("1:/SD");
	File_CreateNewFile("1:/SD/Data.c");
	File_WriteData("1:/SD/Data.c",(u8*)"Working!!",9);
	File_ReadData("1:/SD/Data.c",Data,9);
	size=File_GetFileSize("1:/STM32.c");
	OLED_ShowStrings(0,0,(char *)Data,12);
	OLED_UpdateGRAM();


	/*
	
	Sta=f_mount(&fs,"1:",1);
	Sta=
	f_mkdir("1:/.STM32");
	// for(u8 i=0;i<5;i++)
	// {
	// Sta=f_readdir(&dp,&fno); 
	// 	OLED_ShowStrings(0,i,fno.fname,16);
	// 	OLED_ShowStrings(0,7,(char*)('0'+Sta),2);
	// }

	f_unmount();
	f_rmdir();
	f_rmdir();
	Sta=f_open(&fils,"1:/STM32.txt",FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);
	if(Sta==FR_EXIST)
	{
		Sta=f_open(&fils,"1:/STM32.txt",FA_READ|FA_WRITE|FA_OPEN_EXISTING);
			if(Sta==FR_OK)
			{
				Sta=f_write(&fils,asd,sizeof(asd),&ss);
				//Sta=f_write(&fils,tt,sizeof(tt),&ss);
			}
	}
	Sta=f_close(&fils);
	Sta=f_open(&fils,"1:/STM32.txt",FA_READ|FA_WRITE|FA_OPEN_EXISTING);
	Sta=f_read(&fils,Data,30,&ss);
	Sta=f_close(&fils);

	

	*/
	while(1)
	{	
		Task_List();	

	}





	
}	

	












