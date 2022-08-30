#include "IncludeFile.h"


// __align(4) u8 A[1024],B[2048];   //对齐的部分不能在栈里！！！


__ALIGN_BEGIN 
USB_OTG_CORE_HANDLE USB_OTG_dev 
__ALIGN_END;
USB_OTG_CORE_ID_TypeDef coreID=USB_OTG_FS_CORE_ID;


void USB_Task()
{
	USBD_Init(&USB_OTG_dev,coreID,&USR_desc,&USBD_MSC_cb, &USR_cb);
//           https://blog.csdn.net/zhengnianli/article/details/113931569    LVGL
}



void MPU6050_Test()
{
	float pitch,yaw,roll; 
	char PData[6];
	char YData[6];
	char RData[6];
	MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
	// printf("P:%f Y:%f R:%f\r\n",pitch,yaw,roll);
	sprintf(PData,"%3.2f",pitch);
	sprintf(YData,"%3.2f",yaw);
	sprintf(RData,"%3.2f",roll);

//	OLED_ShowStrings(50,0,PData,6);
//	OLED_ShowStrings(50,1,YData,6); 
//	OLED_ShowStrings(50,2,RData,6);
//	OLED_UpdateGRAM();


}
	

void AT24C08_Test()
{


}	
		
//void SDIO_Test()
//{
//	u16 k;

//	Programe_StartRun();
//	SD_ShowInfomation();
//	Programe_End_Us(0);

//	memset(A,0x5A,sizeof(A));

//	Programe_StartRun();

//	SD_WriteMultiBlocks(A,1024, 512,sizeof(A)/512); 
//	Programe_End_Us(0);	
//	
//	Programe_StartRun();
//	SD_ReadMultiBlocks(B,0, 512, sizeof(B)/512);
//	Programe_End_Us(0);	

//	for(k=0;k<sizeof(B);k++)
//	printf("Data %d : %x \r\n",k,B[k]);

//}

//void RTC_Test()
//{
//		Programe_StartRun();
//		RTC_Get_Time(&STM32_Time);
//		Programe_End_Us(0);
//		printf("Y:%d M:%d D:%d W:%d H:%d M:%d S:%d\r\n",STM32_Time.year,STM32_Time.month,STM32_Time.date,STM32_Time.week,STM32_Time.hour,STM32_Time.minute,STM32_Time.second);

//}

void SD_Test()
{
	u8 Data[20];
	FIL fils;
	DIR dp;
	File_FATFSInit();
	File_MountDisk("1:");
	File_Mkdir("1:/SD");
	File_OpenDir("1:/SD",&dp);
	File_CreateNewFile("1:/SD/Data.c",&fils);
	File_WriteData(&fils,"1:/SD/Data.c",(u8*)"Working!!",10,0);
	File_WriteData(&fils,"1:/SD/Data.c",(u8*)"add Test",9,10);
	File_ReadData(&fils,"1:/SD/Data.c",Data,10,10);
	//File_CloseDir();

}


void RNG_Test()
{







	
}


void Led_Test()
{
	static u8 i=0;

	if(i)
	{
			LED1_OFF;
			Delay_ms(500);
			printf("LED关\r\n");
	}
	else
	{
			LED1_ON;
			Delay_ms(500);
			printf("LED开\r\n");
	}

	i=~i;

}





// void Task_List()
// {

// /*

// 循环里添加各种标志查询，用于后边各种任务置位
// 例如显示状态等，收发状态等

// */

// 			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
// 			{

// 				System_ResetState(Task_TimeFlag,Task_10ms);
// 			}
				
// 			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
// 			{
			

// 				System_ResetState(Task_TimeFlag,Task_30ms);	
// 			}


// 			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
// 			{
				
				
// 				System_ResetState(Task_TimeFlag,Task_50ms);	
// 			}


// 			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
// 			{
				
				
// 				System_ResetState(Task_TimeFlag,Task_100ms);	
// 			}


// 			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
// 			{


// 				System_ResetState(Task_TimeFlag,Task_200ms);	
// 			}


// 			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
// 			{
			
				
// 				//Led_Test();
// 				System_ResetState(Task_TimeFlag,Task_500ms);	
// 			}

// 			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
// 			{
// 				//OLED_ClearScreen(0x00);
// 				System_ResetState(Task_TimeFlag,Task_1s);	
// 			}


// }







	// XPT2046_Init();
	// LCD_Init();
	
	// File_FATFSInit();
	// LVGL_Init();
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
	// lv_demo_stress();
	// lv_demo_benchmark();
	 //lv_ex_cpicker_1();
		// lv_task_handler();
		// lv_tick_inc(10);
	// Task_Init();

	// vTaskStartScheduler();

	// while (1)
	// { 
	// 	//LCD_ShowString(0,0,240,320,12,USART1_Buffer);
		// lv_task_handler();
		// lv_tick_inc(5);
		// Delay_ms(5);
		
	// 	OLED_ShowStrings(0,0,USART1_Buffer,64);
	// 	// OLED_ShowNumber(16,2,data.point.x,4);
	// 	// OLED_ShowNumber(16,3,data.point.y,4);
	// 	// OLED_UpdateGRAM();

	// 	// lv_task_handler();
	// 	// lv_tick_inc(10);
	// 	// LCD_DrawPoint(data.point.x,data.point.y,0X00);
	// }



// typedef struct 
// {
// 	u8 Dev_ID;
// 	u8 Dev_Data[10];
// }QueueBuff_t;

// QueueBuff_t QueueBuff[5];
// TaskHandle_t  Task_1_Handle;
// QueueHandle_t Queue_Handle;

// extern u8 USART1_Buffer[1024];

// void OLED_Task(void)
// {
// 	//u8 buff[1024];
// 	// BaseType_t states;
// 	u16 i=0;
// 	TickType_t Time;		
// 	Time=xTaskGetTickCount();
// 	while(1)
// 	{

// 		// states = xQueueReceive(Queue_Handle,buff,100/portTICK_RATE_MS);
// 		// if( states == pdPASS)
// 		// {
// 		// 	OLED_Data2GRAM(buff,sizeof(buff));
// 		// 	OLED_ShowNumber(0,0,i,8);
// 		// 	i++;
// 		// }
// 		// taskENTER_CRITICAL();
// 		OLED_ShowNumber(0,2,i,8);
// 		// OLED_Draw_FullCircle(63,32,i/100);
// 		i++;
// 		OLED_UpdateGRAM();
// 		vTaskDelayUntil(&Time,5/portTICK_PERIOD_MS);
// 	}
// }

// void USART_Task_1_()
// {

// 	while(1)
// 	{
// 		QueueBuff[0].Dev_ID=1;
// 		memset(QueueBuff[0].Dev_Data,0x11,sizeof(QueueBuff[0].Dev_Data));
// 		xQueueSendToBack(Queue_Handle,&QueueBuff[0],0);
// 		taskENTER_CRITICAL();
// 		printf("Task_1 \r\n");
// 		taskYIELD();
// 		taskEXIT_CRITICAL();
// 		taskYIELD();
// 	}


// }

// void LCD_Task()
// {
// 	TickType_t Time;

// 	Time=xTaskGetTickCount();
// 	while(1)
// 	{
// 		//taskENTER_CRITICAL();
// 		LCD_ShowPicture();
// 		//taskEXIT_CRITICAL();
// 		vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
// 	}


// }



// // void USART_Task_3_()
// // {

// // 	TickType_t Time;
// // 	Time=xTaskGetTickCount();

// // 	while(1)
// // 	{
// // 		lv_tick_inc(10);
// // 		lv_task_handler();
// // 		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
// // 	}
// // }

// void USART_Task_4_()
// {
// 	float pitch,yaw,roll;
// 	TickType_t Time;

// 	Time=xTaskGetTickCount();

// 	while(1)
// 	{
// 		taskENTER_CRITICAL();
// 		MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
// 		taskEXIT_CRITICAL();
// 		OLED_ShowNumber(0,2,(u8)pitch,3);
// 		OLED_ShowNumber(30,2,(u8)yaw,3);
// 		OLED_ShowNumber(60,2,(u8)roll,3);
// 		vTaskDelayUntil(&Time,30/portTICK_PERIOD_MS);
// 	}


// }



// void Queue_Task()
// {

// 	u8 buff[1024];
// 	u16 Frames=0;
// 	TickType_t Time;
// 	BaseType_t  SS;
// 	Time = xTaskGetTickCount();
// 	while(1)
// 	{
// 		SS=xQueueReceive(Queue_Handle,buff,10/portTICK_RATE_MS);
// 		if(SS == pdPASS)
// 		{
// 			OLED_Data2GRAM(buff,sizeof(buff));
// 			OLED_ShowNumber(0,0,Frames,5);
// 			Frames++;
// 			OLED_UpdateGRAM();
// 		}
// 		vTaskDelayUntil(&Time,50/portTICK_PERIOD_MS);
// 	}



	
// }


// void USART_Task_5()
// {
// 	TickType_t Time;
// 	static u16 Test_Val =0;
// 	Time=xTaskGetTickCount();
// 	while(1)
// 	{
// 		OLED_ShowNumber(0,0,Test_Val,5);
// 		OLED_UpdateGRAM();
// 		vTaskDelayUntil(&Time,30/portTICK_PERIOD_MS);
// 	}


// }



// void LED_Task(void)
// {
// 	TickType_t Time;
// 	static u16 Test_Val=0;
// 	Time=xTaskGetTickCount();
// 	while(1)
// 	{	
// 		LED1_ON;
// 		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
// 		LED1_OFF;
// 		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
// 		LED1_ON;
// 		vTaskDelayUntil(&Time,150/portTICK_PERIOD_MS);
// 		LED1_OFF;
// 		vTaskDelayUntil(&Time,1500/portTICK_PERIOD_MS);
// 		Test_Val++;
// 		OLED_ShowNumber(0,3,Test_Val,5);
// 	}
// }




// void SDCard_Task()
// {
// 	u8 buff[1024];
// 	u32 i=0;
// 	u16 Frames=0;
// 	TickType_t Time;
// 	FIL fils;
// 	Time = xTaskGetTickCount();

// 	while(1)
// 	{	


// 		File_ReadData(&fils,"1:/SD/Data_BadApple.bin",buff,sizeof(buff),i);
// 		OLED_Data2GRAM(buff,sizeof(buff));
// 		OLED_ShowNumber(0,0,Frames,5);
// 		i+=sizeof(buff);
// 		Frames++;
// 		OLED_UpdateGRAM();
// 		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
// 	}

// }





// void Clock_Task()
// {
// 	TickType_t Time;
// 	STM32_Time_t STM32_Time;

// 	Time=xTaskGetTickCount();

// 	while (1)
// 	{
// 		RTC_Get_Time(&STM32_Time);
// 		OLED_ShowNumber(60,0,STM32_Time.hour,2);
// 		OLED_ShowNumber(80,0,STM32_Time.minute,2);
// 		OLED_ShowNumber(100,0,STM32_Time.second,2);
// 		OLED_ShowNumber(0,0,STM32_Time.year,2);
// 		OLED_ShowNumber(20,0,STM32_Time.month,2);
// 		OLED_ShowNumber(40,0,STM32_Time.date,2);
// 		OLED_UpdateGRAM();	
// 		vTaskDelayUntil(&Time,500/portTICK_PERIOD_MS);
// 	}
// }

// void LVGL_Task()
// {

// 	TickType_t Time;
// 	u8 State=0;
// 	Time=xTaskGetTickCount();

// 	while (1)
// 	{
// 		taskENTER_CRITICAL();;
// 		lv_task_handler();
// 		lv_tick_inc(10);
// 		taskEXIT_CRITICAL();
// 		// if(State == 0)
// 		// {
// 		// 	OLED_ShowStrings(0,1,"Run ",4);   
// 		// 	State=1;
// 		// }
// 		// else
// 		// {
// 		// 	OLED_ShowStrings(0,1,"Stop",4);   
// 		// 	State=0;
// 		// }
// 		// OLED_UpdateGRAM();
// 		vTaskDelayUntil(&Time,10/portTICK_PERIOD_MS);
// 	}


// }

// void Send_1()
// {
// 	u8 AAA=1;
// 	while (1)
// 	{
// 		printf("Send_1\r\n");
// 		xQueueSendToBack(Queue_Handle,&AAA,0);
// 		taskYIELD();
// 	}
// }

// void Send_2()
// {
// 	u8 AAA=2;
// 	while (1)
// 	{
// 		printf("Send_2\r\n");
// 		xQueueSendToBack(Queue_Handle,&AAA,0);
// 		taskYIELD();
// 	}
// }
// void Get_1()
// {
// 	u8 AAA=0;
// 	BaseType_t states;
// 	u8 asd=0;
// 	while (1)
// 	{
// 		printf("！！！！  %d  ！！！\r\n",uxQueueMessagesWaiting(Queue_Handle));
// 		states = xQueueReceive(Queue_Handle,&AAA,200);
// 		printf("*******  %d  ******\r\n",uxQueueMessagesWaiting(Queue_Handle));
// 		if( states == pdPASS)
// 		{
// 			printf("#%d \r\n",AAA);
// 		}
// 	}
// }


// void Task_Init()
// {
// 	// xTaskCreate( (TaskFunction_t)USART_Task_1_,"USART",100,NULL,10,&Task_1_Handle);
// 	//xTaskCreate( (TaskFunction_t)LCD_Task,"USART",10240,NULL,12,NULL);
// 	// xTaskCreate( (TaskFunction_t)USART_Task_3_,"USART",100,NULL,10,NULL);
// 	//xTaskCreate( (TaskFunction_t)USART_Task_4_,"USART",100,NULL,10,NULL);
// 	//xTaskCreate( (TaskFunction_t)OLED_Task,"USART",100,NULL,10,NULL);
// 	// xTaskCreate( (TaskFunction_t)LED_Task,"LED",100,NULL,13,NULL);
// 	// xTaskCreate( (TaskFunction_t)USART_Task_5,"LED",100,NULL,13,NULL);
// 	// xTaskCreate( (TaskFunction_t)LVGL_Task,"LVGL",1000,NULL,12,NULL);
// 	// xTaskCreate( (TaskFunction_t)LCD_Task,"LVGL",3000,NULL,11,NULL);
// 	//xTaskCreate( (TaskFunction_t)SDCard_Task,"Queue",1500,NULL,12,NULL);
// 	//xTaskCreate( (TaskFunction_t)Clock_Task,"Clock",100,NULL,10,NULL);
// 	//xTaskCreate( (TaskFunction_t)Queue_Task,"USART",2048,NULL,10,NULL);
// 	xTaskCreate( (TaskFunction_t)Get_1,"LED",100,NULL,14,NULL);
// 	xTaskCreate( (TaskFunction_t)Send_1,"LED",100,NULL,13,NULL);
// 	xTaskCreate( (TaskFunction_t)Send_2,"LED",100,NULL,13,NULL);


// }





// SemaphoreHandle_t xSemaphore;

// void vATask( void * pvParameters )
// {
    /* Attempt to create a semaphore. */
    // xSemaphore = xSemaphoreCreateBinary();

    // if( xSemaphore == NULL )
    // {
    //     /* There was insufficient FreeRTOS heap available for the semaphore to
    //     be created successfully. */
    // }
    // else
    // {
    //     /* The semaphore can now be used. Its handle is stored in the
    //     xSemahore variable.  Calling xSemaphoreTake() on the semaphore here
    //     will fail until the semaphore has first been given. */
    // }




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


//}
// */




