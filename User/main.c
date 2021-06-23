#include "IncludeFile.h"




TaskHandle_t  Task_1_Handle;
QueueHandle_t Queue_Handle;


void OLED_Task(void)
{
static u8  i=0;
char s[1];

	while(1)
	{
			if(i>=50)
				i=0;
			s[0]='!'+i;
			OLED_ShowStrings(0,1,s,1);
			i++;
			OLED_UpdateGRAM();	
			vTaskDelay(500);
	}
}






void USART_Task_1_()
{
u8 DataR[15];
u8 i;
	while(1)
	{
		taskENTER_CRITICAL();
		printf("Task_1 Delate \r\n");
		taskEXIT_CRITICAL();
		// xQueueReceive(Queue_Handle,DataR,10);
		// vPortEnterCritical();
		// for(i=0;i<sizeof(DataR);i++)
		// {
		// 	printf("Receive %d: %x \r\n",i,DataR[i]);
		// }
		// vPortExitCritical();
		// vTaskDelete(NULL);
		taskYIELD();
	}


}

void USART_Task_2_()
{

	while(1)
	{
		printf("Task_2 \r\n");
		//vTaskDelay(100);
		taskYIELD();
	}


}

void USART_Task_3_()
{

	while(1)
	{
		printf("Task_3 \r\n");
		//vTaskDelay(100);
		taskYIELD();
	}


}

void USART_Task_4_()
{

	while(1)
	{
		printf("Task_4 \r\n");
		//vTaskDelay(100);
		taskYIELD();
	}


}
void USART_Task_5_()
{
TickType_t Time;
UBaseType_t pro;
	Time=xTaskGetTickCount();
	while(1)
	{
		pro=uxTaskPriorityGet(Task_1_Handle);
		taskENTER_CRITICAL();
		printf("Task_5 == %d\r\n",pro);
		taskEXIT_CRITICAL();
		//vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
		taskYIELD();
	}


}





void LED_Task(void)
{
// static 
// u8 i=0;
// u8 k=0;
// u8 Data[15];
TickType_t Time;

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
		vTaskDelayUntil(&Time,1500/portTICK_PERIOD_MS);



		// k++;
		// memset(Data,0x12,sizeof(Data));
		// xQueueSendToBack(Queue_Handle,Data,10);
		// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	}
}




void Task_Init()
{
	xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	xTaskCreate( (TaskFunction_t)USART_Task_2_,"USART",100,NULL,9,NULL);
	xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,8,NULL);
	xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,7,NULL);
	xTaskCreate( (TaskFunction_t)USART_Task_5_,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",100,NULL,10,NULL);

}


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	//TaskTimer_Init();



	// Queue_Handle = xQueueCreate(10,10);
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









