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
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
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


	调试相关:
		vTaskList();//用于获取各个任务信息



只会关闭上下文的切换，不关闭中断
临界区执行时间太长时建议使用此操作，而不是使用临界区开关中断的方式
vTaskSuspendAll(); //挂起任务调度器
之间不能有FreeRTOS函数！！！！
xTaskResumeAll();//恢复任务调度器



临界区访问函数只会屏蔽和开启受FreeRTOS管理的中断，
对于高于【configMAX_SYSCALL_INTERRUPT_PRIORITY】中断函数内不能包含FreeRTOS函数
taskENTER_CRITICAL();进入临界区
taskEXIT_CRITICAL();退出临界区





	https://blog.csdn.net/qq_40318498/article/details/97111069?utm_term=tft%E6%98%BE%E7%A4%BA%E9%97%AA%E7%83%81&utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~all~sobaiduweb~default-5-97111069&spm=3001.4430
	https://mp.weixin.qq.com/s/JME3VArPETgPjD0n_cHKNQ
	https://www.waveshare.net/study/article-969-1.html

}
*/





