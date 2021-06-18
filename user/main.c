#include "IncludeFile.h"



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


void LED_Task(void)
{
// static 
u8 i=0;

	while(1)
	{

		if(i)
		{
			LED1_OFF;
			vTaskDelay(500);
			printf("LED关\r\n");
		}
		else
		{
			LED1_ON;
			vTaskDelay(500);
			printf("LED开\r\n");
		}

		i=~i;
	}
}



void USART_Task_1_()
{

	while(1)
	{
		printf("Task_1 \r\n");
	}


}

void USART_Task_2_()
{

	while(1)
	{
		printf("Task_2 \r\n");
	}


}

void USART_Task_3_()
{

	while(1)
	{
		printf("Task_3 \r\n");
	}


}

void USART_Task_4_()
{

	while(1)
	{
		printf("Task_4 \r\n");
	}


}
void USART_Task_5_()
{

	while(1)
	{
		printf("Task_5 \r\n");
	}


}








void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",30,NULL,5,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_2_,"USART",30,NULL,5,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",30,NULL,5,NULL);
	xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",200,NULL,5,NULL);
	xTaskCreate( (TaskFunction_t)USART_Task_5_,"USART",200,NULL,5,NULL);

	xTaskCreate( (TaskFunction_t)LED_Task,"LED",10,NULL,5,NULL);

}


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	//TaskTimer_Init();


	Task_Init();



	vTaskStartScheduler();


	// while(1)
	// {	
	// 	Task_List();	

	// }


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
		
}
*/









