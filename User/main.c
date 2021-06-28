#include "IncludeFile.h"



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
u8 buff[1024];
BaseType_t states;
u16 i=0;
	while(1)
	{

		//OLED_Test();

		states = xQueueReceive(Queue_Handle,buff,100/portTICK_RATE_MS);
		if( states == pdPASS)
		{
			OLED_Data2GRAM(buff,sizeof(buff));
			OLED_ShowNumber(0,0,i);
			OLED_UpdateGRAM();
			i++;
		}
		//taskENTER_CRITICAL();
		
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

	while(1)
	{
		QueueBuff[2].Dev_ID=3;
		memset(QueueBuff[2].Dev_Data,0x33,sizeof(QueueBuff[2].Dev_Data));
		xQueueSendToBack(Queue_Handle,&QueueBuff[2],0);
		taskENTER_CRITICAL();
		printf("Task_3 \r\n");
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}

void USART_Task_4_()
{

	while(1)
	{
		taskENTER_CRITICAL();
		printf("Task_4 \r\n");
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}
void USART_Task_5_()
{
TickType_t Time;
	while(1)
	{
		taskENTER_CRITICAL();
		printf("Task_5 \r\n");
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}

void Queue_Task()
{
QueueBuff_t QueueTemp;

	while(1)
	{

		xQueueReceive(Queue_Handle,&QueueTemp,100/portTICK_RATE_MS);
		taskENTER_CRITICAL();
		printf("Task %d   Data %x\r\n", QueueTemp.Dev_ID , QueueTemp.Dev_Data[0]);
		taskEXIT_CRITICAL();
		taskYIELD();
		
	}



	
}



void LED_Task(void)
{

TickType_t Time;
u16 i=0;

	Time=xTaskGetTickCount();
	while(1)
	{
		
		LED1_ON;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_ON;
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);
		LED1_OFF;
		vTaskDelayUntil(&Time,1000/portTICK_PERIOD_MS);

		// k++;
		// memset(Data,0x12,sizeof(Data));
		// xQueueSendToBack(Queue_Handle,Data,10);
		// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	}
}

void SDCard_Task()
{
	u8 buff[1024];
	u32 i=0;
	u16 Frames=0;
	TickType_t Time;

	Time=xTaskGetTickCount();

	File_FATFSInit();
	File_MountDisk("1:");
	File_OpenDir("1:/SD");
	while(1)
	{
		File_ReadData("1:/SD/Data.bin",buff,sizeof(buff),i);
		OLED_Data2GRAM(buff,sizeof(buff));
		OLED_ShowNumber(0,0,Frames);
		OLED_UpdateGRAM();
		i+=sizeof(buff);
		Frames++;
		vTaskDelayUntil(&Time,20/portTICK_PERIOD_MS);
	}

	File_CloseDir();


}







void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	// xTaskCreate( (TaskFunction_t)USART_Task_2_,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_5_,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",2048,NULL,11,NULL);
}


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(128000,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	led_init();
	OLED_Init();
	File_FATFSInit();
	//TaskTimer_Init();



	Queue_Handle = xQueueCreate(5,1024);
	Task_Init();


	vTaskStartScheduler();


	while(1)
	{	
		//Task_List();	
		// LED1_ON;
		// delay_us(2);
		// LED1_OFF;
		// delay_us(2);
		// LED1_ON;
		// delay_ms(100);
		// LED1_OFF;
		// delay_ms(200);
		// delay_ms(500);
		// delay_ms(500);
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









