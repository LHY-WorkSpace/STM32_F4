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
		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
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
		lv_task_handler();
		lv_tick_inc(5);
		if(State == 0)
		{
			OLED_ShowStrings(0,1,"Run ",4);   
			State=1;
		}
		else
		{
			OLED_ShowStrings(0,1,"Stop",4);   
			State=0;
		}
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,5/portTICK_PERIOD_MS);
	}


}



void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	//xTaskCreate( (TaskFunction_t)LCD_Task,"USART",10240,NULL,12,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)OLED_Task,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",100,NULL,13,NULL);
	//xTaskCreate( (TaskFunction_t)LVGL_Task,"LVGL",1000,NULL,12,NULL);
	xTaskCreate( (TaskFunction_t)LCD_Task,"LVGL",3000,NULL,11,NULL);
	xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",1500,NULL,12,NULL);
	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
}

int  main()
{
	u16 i=0;
	u16 x=500,y=0,clr=0;
	lv_indev_drv_t indev_drv;
	lv_indev_data_t  data;


 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	//MPU6050_Init();
	OLED_Init();
	// XPT2046_Init();
	LCD_Init();
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
	// lv_demo_benchmark();
	 //lv_ex_cpicker_1();


	// Task_Init();

	// vTaskStartScheduler();


	printf("%s","AT+RST\r\n");
	while (1)
	{
		LCD_ShowString(0,0,240,320,12,USART1_Buffer);
		// OLED_ShowStrings(0,0,USART1_Buffer,64);
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





	https://blog.csdn.net/qq_40318498/article/details/97111069?utm_term=tft%E6%98%BE%E7%A4%BA%E9%97%AA%E7%83%81&utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~all~sobaiduweb~default-5-97111069&spm=3001.4430
	https://mp.weixin.qq.com/s/JME3VArPETgPjD0n_cHKNQ
	https://www.waveshare.net/study/article-969-1.html

}
*/











