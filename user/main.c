#include "IncludeFile.h"





u8 lc=0,i=0;
float pitch,yaw,roll,Dis; 
char gg[7];




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










FATFS fs;
FIL fils;
u8 Sta;
u32 ss;
u8 Data[1024];
u8 work[512];
DIR dp;		
FILINFO fno;
char asd[]="Build By STM32";
char tt[]="SD-RW!";

int  main()
{


	memset(Data,0x00,sizeof(Data));
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	TaskTimer_Init();
	disk_initialize(DEV_SD);

	
	//Sta=f_mkfs("1",FM_FAT|FM_SFD,512,work,sizeof(work));
	Sta=f_mount(&fs,"1:",1);
	Sta=f_opendir(&dp,"1:");
	for(u8 i=0;i<5;i++)
	{
		Sta=f_readdir(&dp,&fno); 
		OLED_ShowStrings(0,i,fno.fname,16);
		OLED_ShowStrings(0,7,(char*)('0'+Sta),2);
	}


	Sta=f_open(&fils,"1:/STM32.txt",FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);
	if(Sta==FR_EXIST)
	{
		Sta=f_open(&fils,"1:/STM32.txt",FA_READ|FA_WRITE|FA_OPEN_EXISTING);
			if(Sta==FR_OK)
			{
				Sta=f_write(&fils,asd,sizeof(asd),&ss);
				Sta=f_write(&fils,tt,sizeof(tt),&ss);
			}
	}
	Sta=f_close(&fils);
	Sta=f_open(&fils,"1:/STM32.txt",FA_READ|FA_WRITE|FA_OPEN_EXISTING);
	Sta=f_read(&fils,Data,30,&ss);
	Sta=f_close(&fils);
	OLED_ShowStrings(0,0,(char *)Data,sizeof(asd)+sizeof(tt));
	OLED_UpdateGRAM();
	
	while(1)
	{	
		Task_List();	

	}





	
}	

	












