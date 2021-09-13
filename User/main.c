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
		taskENTER_CRITICAL();
		LCD_ShowPicture();
		taskEXIT_CRITICAL();
		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
	}


}

//static void btn_event_cb(lv_obj_t * btn, lv_event_t event)
//{
//    if(event == LV_EVENT_CLICKED) {
//        static uint8_t cnt = 0;
//        cnt++;

//        /*Get the first child of the button which is the label and change its text*/
//        lv_obj_t * label = lv_obj_get_child(btn, NULL);
//        lv_label_set_text_fmt(label, "Button: %d", cnt);
//    }
//}

// void lvgl_first_demo_start(void)
// {
    // lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 10, 10);                          /*Set its size*/
    // lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

    // lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
    // lv_label_set_text(label, "Button");                     /*Set the labels text*/


	// lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	// lv_label_set_text(label1, "Hello world!"); 
	// lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_LEFT, 2, 0);
	// lv_obj_align(btn, label1, LV_ALIGN_IN_TOP_LEFT, 0, 10);



	// lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
	// lv_obj_set_size(bar1, 10, 10);
	// lv_obj_align(bar1, NULL, LV_ALIGN_CENTER, 0, 0);
	// lv_bar_set_anim_time(bar1, 10);
	// lv_bar_set_value(bar1, 50, LV_ANIM_ON);



//  static lv_point_t line_points[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60}, {240, 10} };
//  /*Create new style (thick dark blue)*/
//  static lv_style_t style_line;
//  lv_style_copy(&style_line, &lv_style_plain);
//  style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
//  style_line.line.width = 3;
//  style_line.line.rounded = 1;



//  /*Copy the previous line and apply the new style*/
//  lv_obj_t * line1;
//  line1 = lv_line_create(lv_scr_act(), NULL);
//  lv_line_set_points(line1, line_points, 5);     /*Set the points*/
//  lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
//  lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);




// }

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
	Time = xTaskGetTickCount();

	File_FATFSInit();
	File_MountDisk("1:");
	File_OpenDir("1:/SD");
	while(1)
	{	
		File_ReadData("1:/SD/Data_BadApple.bin",buff,sizeof(buff),i);
		OLED_Data2GRAM(buff,sizeof(buff));
		OLED_ShowNumber(0,0,Frames,5);
		i+=sizeof(buff);
		Frames++;
		OLED_UpdateGRAM();
		vTaskDelayUntil(&Time,38/portTICK_PERIOD_MS);
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





void Task_Init()
{
	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
	//xTaskCreate( (TaskFunction_t)LCD_Task,"USART",10240,NULL,12,NULL);
	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)OLED_Task,"USART",100,NULL,10,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",20,NULL,11,NULL);
	xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",4096,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
}





int  main()
{
	u8 i=0;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	LCD_Init();
	// File_FATFSInit();
	// File_MountDisk("1:");
	// File_OpenDir("1:/SD");
	// LCD_Init();           //初始化LCD FSMC接口
	//RTC_ConfigInit();
	//MPU6050_Init();

	//USB_Task();
	//TaskTimer_Init();
	// lv_init();
	// lv_port_disp_init();
	// lvgl_first_demo_start();

    // GUI_Init();
    
    // // GUI_SetColor(GUI_RED);
    // // GUI_SetBkColor(GUI_BLUE);
    // GUI_SetFont(&GUI_Font8_ASCII);
    // GUI_Clear();
    // GUI_DispStringAt("Hello World",10,10); 
	//LCD_ShowPicture();
	// OLED_MoveDisplay(127,0,16,5,"12345");
	// Queue_Handle = xQueueCreate(5,1024);
	// Task_Init();
	// vTaskStartScheduler();
	// 	OLED_ShowNumber(20,2,5,2);

	// while (1)
	// {
	// 	UpdateOneColumn(50+i,0,16,(u8)('5'-'!'),i);
	// 	OLED_UpdateGRAM();
	// 	i++;
	// 	delay_ms(500);
	// }


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









