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
			OLED_ShowNumber(0,0,i,8);
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

void USB_Task()
{
	USB_OTG_CORE_HANDLE pdev;
	USB_OTG_CORE_ID_TypeDef coreID=USB_OTG_FS_CORE_ID;
	USBD_DEVICE pDevice;                 
	USBD_Class_cb_TypeDef class_cb;
	USBD_Usr_cb_TypeDef usr_cb;

	USBD_Init(&pdev,coreID,&pDevice,&class_cb, &usr_cb);
//           https://blog.csdn.net/zhengnianli/article/details/113931569  
}



void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	// xTaskCreate( (TaskFunction_t)USART_Task_2_,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_5_,"USART",100,NULL,12,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",20,NULL,11,NULL);
	xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",4096,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
}








int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	//RTC_ConfigInit();
	//MPU6050_Init();
	File_FATFSInit();
	//TaskTimer_Init();

	Queue_Handle = xQueueCreate(5,1024);
	Task_Init();

	vTaskStartScheduler();
	SystemDown();


}	
	
/*
void Function_list()
{
	队列相关:
			1.创建一个队列          				xQueueCreate == xQueueGenericCreate
			2.向队列中写数据 						xQueueSendToFront(向队首) xQueueSendToBack(向队尾)  ==  xQueueGenericSend(带参数)
			3.从队列中读数据            			xQueueReceive(读后删除)     xQueuePeek(只读数据)
			4.查询队列中当前有效数据单元个数		 uxSemaphoreGetCount == uxQueueMessagesWaiting  

	切换相关:
		1.立即切换任务，调用这个函数的任务会进入就绪态			taskYIELD()


	延时相关：
		TickType_t Time;
		Time=xTaskGetTickCount();
		vTaskDelayUntil(&Time,100/portTICK_PERIOD_MS);周期执行
		vTaskDelay(100);非周期执行，延时可能被打断而导致边长
		
}
*/









