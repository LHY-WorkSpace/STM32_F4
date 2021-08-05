#include "IncludeFile.h"
#include "lcd.h"
#include "lvgl.h"


typedef struct 
{
	u8 Dev_ID;
	u8 Dev_Data[10];
}QueueBuff_t;

QueueBuff_t QueueBuff[5];
TaskHandle_t  Task_1_Handle;
QueueHandle_t Queue_Handle;












void OLED_Task(void)
{
	//u8 buff[1024];
	// BaseType_t states;
	u16 i=0;
	TickType_t Time;		
	Time=xTaskGetTickCount();
	while(1)
	{

		// states = xQueueReceive(Queue_Handle,buff,100/portTICK_RATE_MS);
		// if( states == pdPASS)
		// {
		// 	OLED_Data2GRAM(buff,sizeof(buff));
		// 	OLED_ShowNumber(0,0,i,8);
		// 	i++;
		// }
		//taskENTER_CRITICAL();
		OLED_ShowNumber(0,2,i,8);
		i++;
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
		//taskEXIT_CRITICAL();

	}
}

void USART_Task_1_()
{

	while(1)
	{
		QueueBuff[0].Dev_ID=1;
		memset(QueueBuff[0].Dev_Data,0x11,sizeof(QueueBuff[0].Dev_Data));
		xQueueSendToBack(Queue_Handle,&QueueBuff[0],0);
		taskENTER_CRITICAL();
		printf("Task_1 \r\n");
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}

void USART_Task_2_()
{

	while(1)
	{
		QueueBuff[1].Dev_ID=2;
		memset(QueueBuff[1].Dev_Data,0x22,sizeof(QueueBuff[1].Dev_Data));
		xQueueSendToBack(Queue_Handle,&QueueBuff[1],0);
		taskENTER_CRITICAL();
		printf("Task_2 \r\n");
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}




void USART_Task_3_()
{

	// TickType_t Time;
	// Time=xTaskGetTickCount();
	// lv_init();
	// lv_port_disp_init();
	// while(1)
	// {
	// 	lv_tick_inc(1);
	// 	vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
	// }


}

void USART_Task_4_()
{
	float pitch,yaw,roll;
	TickType_t Time;

	Time=xTaskGetTickCount();

	while(1)
	{
		taskENTER_CRITICAL();
		MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
		taskEXIT_CRITICAL();
		OLED_ShowNumber(0,2,(u8)pitch,3);
		OLED_ShowNumber(30,2,(u8)yaw,3);
		OLED_ShowNumber(60,2,(u8)roll,3);
		vTaskDelayUntil(&Time,30/portTICK_PERIOD_MS);
	}


}

void USART_Task_5_()
{
	TickType_t Time;

	Time=xTaskGetTickCount();
	while(1)
	{
		// taskENTER_CRITICAL();
		// printf("Task_5 \r\n");
		// taskEXIT_CRITICAL();
		OLED_ClearScreen(0X00);
		vTaskDelayUntil(&Time,30/portTICK_PERIOD_MS);
	}


}

void Queue_Task()
{
// QueueBuff_t QueueTemp;
	u8 buff[1024];
	u16 Frames=0;
	TickType_t Time;
	BaseType_t  SS;
	Time = xTaskGetTickCount();
	while(1)
	{
		SS=xQueueReceive(Queue_Handle,buff,10/portTICK_RATE_MS);
		if(SS == pdPASS)
		{
			OLED_Data2GRAM(buff,sizeof(buff));
			OLED_ShowNumber(0,0,Frames,5);
			Frames++;
			OLED_UpdateGRAM();
		}
		vTaskDelayUntil(&Time,5/portTICK_PERIOD_MS);
	}



	
}
   


void LED_Task(void)
{
	TickType_t Time;

	Time=xTaskGetTickCount();
	while(1)
	{	
		LED1_ON;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_ON;
		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,1500/portTICK_PERIOD_MS);
	}
}




void SDCard_Task()
{
	u8 buff[1024];
	u32 i=0;
	u16 Frames=0;
	TickType_t Time;
	Time = xTaskGetTickCount();

	File_FATFSInit();
	File_MountDisk("1:");
	File_OpenDir("1:/SD");
	while(1)
	{	
		File_ReadData("1:/SD/Data.bin",buff,sizeof(buff),i);
		OLED_Data2GRAM(buff,sizeof(buff));
		//OLED_ShowNumber(0,0,Frames,5);
		i+=sizeof(buff);
		Frames++;
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
	}

//	File_CloseDir();
}





void Clock_Task()
{
	TickType_t Time;
	STM32_Time_t STM32_Time;

	Time=xTaskGetTickCount();

	while (1)
	{
		RTC_Get_Time(&STM32_Time);
		OLED_ShowNumber(60,0,STM32_Time.hour,2);
		OLED_ShowNumber(80,0,STM32_Time.minute,2);
		OLED_ShowNumber(100,0,STM32_Time.second,2);
		OLED_ShowNumber(0,0,STM32_Time.year,2);
		OLED_ShowNumber(20,0,STM32_Time.month,2);
		OLED_ShowNumber(40,0,STM32_Time.date,2);
		OLED_UpdateGRAM();	
		vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
	}
}





void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	// xTaskCreate( (TaskFunction_t)USART_Task_2_,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)OLED_Task,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",20,NULL,11,NULL);
	//xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",4096,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
}








int  main()
{

 	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	// USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	// led_init();
	// OLED_Init();
	// //RTC_ConfigInit();
	// //MPU6050_Init();
	// //File_FATFSInit();
	//USB_Task();
	// //TaskTimer_Init();

	// // Queue_Handle = xQueueCreate(5,1024);
	// Task_Init();

	// vTaskStartScheduler();
	// SystemDown();

 	u16 x=0,y=0;
	Data_Buff DataTemp;				//���LCD ID�ַ���
	u32 P=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//����ϵͳ�ж����ȼ�����2
	Delay_Init();
	File_FATFSInit();
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	// USB_Task();
	led_init();
	POINT_COLOR=RED;      //������ɫ����ɫ
	File_MountDisk("1:");
	File_OpenDir("1:/SD");

	// for(y=0;y<320;y++)
	// {
	// 	File_ReadData("1:/SD/Data.bin",DataTemp.Data_8,480,P);
	// 	P+=480;		
	// 	for(x=0;x<240;x++)
	// 	{
	// 		LCD_Fast_DrawPoint(x,y,DataTemp.Data_16[x]);
	// 	}
	// }	


	LCD_ShowPicture();



  	while(1) 
	{	

	SystemDown();

	} 






}	
	
/*
void Function_list()
{
	�������:
			1.����һ������          				xQueueCreate == xQueueGenericCreate
			2.�������д���� 						xQueueSendToFront(�����) xQueueSendToBack(���β)  ==  xQueueGenericSend(������)
			3.�Ӷ����ж�����            			xQueueReceive(����ɾ��)     xQueuePeek(ֻ������)
			4.��ѯ�����е�ǰ��Ч���ݵ�Ԫ����		 uxSemaphoreGetCount == uxQueueMessagesWaiting  

	�л����:
		1.�����л����񣬵�����������������������̬			taskYIELD()


	��ʱ��أ�
		TickType_t Time;
		Time=xTaskGetTickCount();
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);����ִ��
		vTaskDelay(100);������ִ�У���ʱ���ܱ���϶����±߳�
		
}
*/









