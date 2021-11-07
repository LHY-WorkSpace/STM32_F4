#include "IncludeFile.h"


typedef struct 
{
	u8 Dev_ID;
	u8 Dev_Data[10];
}QueueBuff_t;

QueueBuff_t QueueBuff[5];
TaskHandle_t  Task_1_Handle;
QueueHandle_t Queue_Handle;

extern u8 USART1_Buffer[1024];

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
		// taskENTER_CRITICAL();
		OLED_ShowNumber(0,2,i,8);
		// OLED_Draw_FullCircle(63,32,i/100);
		i++;
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,5/portTICK_PERIOD_MS);
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
		taskYIELD();
		taskEXIT_CRITICAL();
		taskYIELD();
	}


}

void LCD_Task()
{
	TickType_t Time;

	Time=xTaskGetTickCount();
	while(1)
	{
		//taskENTER_CRITICAL();
		LCD_ShowPicture();
		//taskEXIT_CRITICAL();
		vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
	}


}



// void USART_Task_3_()
// {

// 	TickType_t Time;
// 	Time=xTaskGetTickCount();

// 	while(1)
// 	{
// 		lv_tick_inc(10);
// 		lv_task_handler();
// 		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
// 	}
// }

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



void Queue_Task()
{

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
		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
	}



	
}


void USART_Task_5()
{
	TickType_t Time;
	static u16 Test_Val =0;
	Time=xTaskGetTickCount();
	while(1)
	{
		OLED_ShowNumber(0,0,Test_Val,5);
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,30/portTICK_PERIOD_MS);
	}


}



void LED_Task(void)
{
	TickType_t Time;
	static u16 Test_Val=0;
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
		Test_Val++;
		OLED_ShowNumber(0,3,Test_Val,5);
	}
}




void SDCard_Task()
{
	u8 buff[1024];
	u32 i=0;
	u16 Frames=0;
	TickType_t Time;
	FIL fils;
	Time = xTaskGetTickCount();

	while(1)
	{	


		File_ReadData(&fils,"1:/SD/Data_BadApple.bin",buff,sizeof(buff),i);
		OLED_Data2GRAM(buff,sizeof(buff));
		OLED_ShowNumber(0,0,Frames,5);
		i+=sizeof(buff);
		Frames++;
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
	}

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

void LVGL_Task()
{

	TickType_t Time;
	u8 State=0;
	Time=xTaskGetTickCount();

	while (1)
	{
		taskENTER_CRITICAL();;
		lv_task_handler();
		lv_tick_inc(10);
		taskEXIT_CRITICAL();
		// if(State == 0)
		// {
		// 	OLED_ShowStrings(0,1,"Run ",4);   
		// 	State=1;
		// }
		// else
		// {
		// 	OLED_ShowStrings(0,1,"Stop",4);   
		// 	State=0;
		// }
		// OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
	}


}

void Send_1()
{
	u8 AAA=1;
	while (1)
	{
		printf("Send_1\r\n");
		xQueueSendToBack(Queue_Handle,&AAA,0);
		taskYIELD();
	}
}

void Send_2()
{
	u8 AAA=2;
	while (1)
	{
		printf("Send_2\r\n");
		xQueueSendToBack(Queue_Handle,&AAA,0);
		taskYIELD();
	}
}
void Get_1()
{
	u8 AAA=0;
	BaseType_t states;
	u8 asd=0;
	while (1)
	{
		printf("！！！！  %d  ！！！\r\n",uxQueueMessagesWaiting(Queue_Handle));
		states = xQueueReceive(Queue_Handle,&AAA,200);
		printf("*******  %d  ******\r\n",uxQueueMessagesWaiting(Queue_Handle));
		if( states == pdPASS)
		{
			printf("#%d \r\n",AAA);
		}
	}
}


void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	//xTaskCreate( (TaskFunction_t)LCD_Task,"USART",10240,NULL,12,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)OLED_Task,"USART",100,NULL,10,NULL);
	// xTaskCreate( (TaskFunction_t)LED_Task,"LED",100,NULL,13,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_5,"LED",100,NULL,13,NULL);
	// xTaskCreate( (TaskFunction_t)LVGL_Task,"LVGL",1000,NULL,12,NULL);
	// xTaskCreate( (TaskFunction_t)LCD_Task,"LVGL",3000,NULL,11,NULL);
	//xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",1500,NULL,12,NULL);
	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)Get_1,"LED",100,NULL,14,NULL);
	xTaskCreate( (TaskFunction_t)Send_1,"LED",100,NULL,13,NULL);
	xTaskCreate( (TaskFunction_t)Send_2,"LED",100,NULL,13,NULL);


}





SemaphoreHandle_t xSemaphore;

void vATask( void * pvParameters )
{
    /* Attempt to create a semaphore. */
    xSemaphore = xSemaphoreCreateBinary();

    if( xSemaphore == NULL )
    {
        /* There was insufficient FreeRTOS heap available for the semaphore to
        be created successfully. */
    }
    else
    {
        /* The semaphore can now be used. Its handle is stored in the
        xSemahore variable.  Calling xSemaphoreTake() on the semaphore here
        will fail until the semaphore has first been given. */
    }




//	//获取信号量，如果无效，则阻塞Times时长来等待信号量有效
//	if( xSemaphoreTake( xSemaphore, ( TickType_t ) Times ) )
//	{
//		//获取信号量成功！！
//	}

//void __interrupt __far vExampleInterruptHandler( void ) 
//{ 
//	static portBASE_TYPE xHigherPriorityTaskWoken; 
//	xHigherPriorityTaskWoken = pdFALSE; //初始状态设置为FALSE
//	
//	// xHigherPriorityTaskWoken 用于指示【被中断的函数】 和 【被信号量阻塞的任务】的优先级比较结果
//	// 当【被信号量解除阻塞的任务优先级】 高于 【被中断的函数】 的任务时， xHigherPriorityTaskWoken 会被设置为TURE
//	xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken ); 

//	if( xHigherPriorityTaskWoken == pdTRUE ) 
//	{ 
//		/* 给出信号量以使得等待此信号量的任务解除阻塞。如果解出阻塞的任务的优先级高于当前任务的优先
//		级 – 强制进行一次任务切换，以确保中断直接返回到解出阻塞的任务(优选级更高)。
//		*/ 
//		vTaskSwitchContext(); 
//	} 
//} 


}











int  main()
{
	u16 i=0;
	u16 x=500,y=0,clr=0;
	lv_indev_drv_t indev_drv;
	lv_indev_data_t  data;


 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	//USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	Queue_Handle = xQueueCreate(5,1);
	// XPT2046_Init();
	// LCD_Init();
	
	// File_FATFSInit();
	//LVGL_Init();


	//RTC_ConfigInit();
	//MPU6050_Init();

	//USB_Task();
	//TaskTimer_Init();

	// lv_init();
	// lv_port_disp_init();
	// lv_port_indev_init();

	// lv_ex_img_1();
	//lv_ex_img_2();
	//lv_ex_keyboard_1();
	//lv_demo_widgets();
	//lv_demo_stress();
	//lv_demo_benchmark();
	 //lv_ex_cpicker_1();

	Task_Init();

	vTaskStartScheduler();

	while (1)
	{ 
		//LCD_ShowString(0,0,240,320,12,USART1_Buffer);
		lv_task_handler();
		lv_tick_inc(5);
		delay_ms(5);
		
		OLED_ShowStrings(0,0,USART1_Buffer,64);
		// OLED_ShowNumber(16,2,data.point.x,4);
		// OLED_ShowNumber(16,3,data.point.y,4);
		// OLED_UpdateGRAM();

		// lv_task_handler();
		// lv_tick_inc(10);
		// LCD_DrawPoint(data.point.x,data.point.y,0X00);
	}

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





