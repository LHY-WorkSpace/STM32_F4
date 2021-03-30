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
			
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}










FATFS fs;
FIL fils;
u8 Sta;
u32 ss;
char Data[100];
u8 work[512];

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

	
	Sta=f_mkfs("1",FM_FAT|FM_SFD,512,work,sizeof(work));
	Sta=f_mount(&fs,"1:",1);
	Sta=f_open(&fils,"1:/123.txt",FA_READ|FA_WRITE|FA_OPEN_EXISTING);
	Sta=f_read(&fils,Data,5,&ss);
	Sta=f_close(&fils);
	OLED_ShowStrings(0,0,Data,5);
	OLED_UpdateGRAM();
	while(1)
	{	
		Task_List();	

	}





	
}	

	












