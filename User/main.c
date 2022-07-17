#include "IncludeFile.h"


extern USART_Data_t USART1_Data;


void CreateAllTask(void *pv)
{
	u8g2_TaskCreate();
	vTaskDelete(NULL);
}
u32 chk=0;
u16 i;
u8 Dir = TRUE;
DHT11_Data_t DHT11_Data;
u8 T[6];
char H[6];
char tempchar[6];
float temp;
char Data[] = "STM32 NB!!";

u8 eedata[1024];

int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	Dir = ESP8266_Init();
	led_init();
	PWM_Init(0,0);
	OLED_Init();
	u8g2_Init();
	Start_Page();
	Display_FreeRTOS_Logo();

	while (1)
	{	

		if( USART_GetData(&USART2_Data,sizeof(eedata),eedata,&i) == TRUE)
		{
			USART_ITSendData(USART1,&USART1_Data,i,eedata);
		}
		if( USART_GetData(&USART1_Data,sizeof(eedata),eedata,&i) == TRUE)
		{
			USART_ITSendData(USART2,&USART2_Data,i,eedata);
		}

	if( Dir == TRUE)
	{
			Delay_ms(100);
			LED1_ON;
			Delay_ms(100);
			LED1_OFF;
	}

	}
	// XPT2046_Read(&NoUse, &TouchData);
	// 	Mov(TouchData.point.x,TouchData.point.y);
	// 	Delay_ms(10);
	//Test_UI();
	// Clock();
	// Delay_ms(10);
	// SystemDown();
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


	�������:
		vTaskList();//���ڻ�ȡ����������Ϣ



ֻ��ر������ĵ��л������ر��ж�
�ٽ���ִ��ʱ��̫��ʱ����ʹ�ô˲�����������ʹ���ٽ��������жϵķ�ʽ
vTaskSuspendAll(); //�������������
֮�䲻����FreeRTOS������������
xTaskResumeAll();//�ָ����������



�ٽ������ʺ���ֻ�����κͿ�����FreeRTOS������жϣ�
���ڸ��ڡ�configMAX_SYSCALL_INTERRUPT_PRIORITY���жϺ����ڲ��ܰ���FreeRTOS����
taskENTER_CRITICAL();�����ٽ���
taskEXIT_CRITICAL();�˳��ٽ���





	https://blog.csdn.net/qq_40318498/article/details/97111069?utm_term=tft%E6%98%BE%E7%A4%BA%E9%97%AA%E7%83%81&utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~all~sobaiduweb~default-5-97111069&spm=3001.4430
	https://mp.weixin.qq.com/s/JME3VArPETgPjD0n_cHKNQ
	https://www.waveshare.net/study/article-969-1.html

}
*/





