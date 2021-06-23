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
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
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









