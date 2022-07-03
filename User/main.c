#include "IncludeFile.h"


float DACC = 1.2;
float ADCC;


void CreateAllTask(void *pv)
{
	u8g2_TaskCreate();
	vTaskDelete(NULL);
}

DHT11_Data_t DHT11_Data;
char T[6];
char H[6];
char tempchar[6];
float temp;
int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	led_init();
	// DAC_UserInit();
	// ADC_UserInit();
	// DHT11_GPIO_Init();
	DS18B20_GPIO_Init();
	// AT24C08_init();
	// XPT2046_Init();
	OLED_Init();
	u8g2_Init();
	// Start_Page();
	// Display_FreeRTOS_Logo();
	// USB_Task();
	

	while (1)
	{
		temp =	DS18B20_Get_Temperature();
		DHT11_Read_Data(&DHT11_Data);
		sprintf(T,"%2d",DHT11_Data.Tempure.B08[1]);
		sprintf(&T[3],"%2d",DHT11_Data.Tempure.B08[0]);
		sprintf(H,"%2d",DHT11_Data.Humidity.B08[1]);
		sprintf(&H[3],"%2d",DHT11_Data.Humidity.B08[0]);
		T[2] = '.';
		H[2] = '.';

		sprintf(tempchar,"%4.2f",temp);
		ShowDS18B20TempData(tempchar);
		ShowTempData(T);
		ShowHumanityData(H);
		// DAC_Out(DACC);
		// Delay_ms(50);
		// ADCC=BatteryGetVolate();
		Delay_ms(500);
		Delay_ms(500);
		LED1_OFF;
		DS18B20_GetID();
		Delay_ms(500);
		Delay_ms(500);
		LED1_ON;
		


	}





	// 	XPT2046_Read(&NoUse, &TouchData);
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





