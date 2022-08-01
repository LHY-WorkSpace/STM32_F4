#include "IncludeFile.h"





u8 eedata[4096];

void test_env(void)
{
	char wifi_ssid[20] = {0};
	char wifi_passwd[20] = {0};
	size_t len = 0;
	


	/* 读取默认环境变量值 */
	//环境变量长度未知，先获取 Flash 上存储的实际长度 */
	ef_get_env_blob("BT-XXXX", NULL, 0, &len);
	//获取环境变量
	ef_get_env_blob("BT-XXXX", wifi_ssid, len, NULL);
	//打印获取的环境变量值
	printf("BT-XXXX env is:%s\r\n", wifi_ssid);
	
	//环境变量长度未知，先获取 Flash 上存储的实际长度 */
	ef_get_env_blob("Jack Cooper", NULL, 0, &len);
	//获取环境变量
	ef_get_env_blob("Jack Cooper", wifi_passwd, len, NULL);
	//打印获取的环境变量值
	printf("Jack Cooper env is:%s\r\n", wifi_passwd);


	// // // /* 将环境变量值改变 */
	// ef_set_env_blob("BT-XXXX", "12345", 5);
	// ef_set_env_blob("Jack Cooper", "54321", 5);


	// memset(wifi_ssid,0x00,sizeof(wifi_ssid));
	// memset(wifi_passwd,0x00,sizeof(wifi_passwd));


	// // /* 读取默认环境变量值 */
	// //环境变量长度未知，先获取 Flash 上存储的实际长度 */
	// ef_get_env_blob("BT-XXXX", NULL, 0, &len);
	// //获取环境变量
	// ef_get_env_blob("BT-XXXX", wifi_ssid, len, NULL);
	// //打印获取的环境变量值
	// printf("BT-XXXX env is:%s\r\n", wifi_ssid);
	
	// //环境变量长度未知，先获取 Flash 上存储的实际长度 */
	// ef_get_env_blob("Jack Cooper", NULL, 0, &len);
	// //获取环境变量
	// ef_get_env_blob("Jack Cooper", wifi_passwd, len, NULL);
	// //打印获取的环境变量值
	// printf("Jack Cooper env is:%s\r\n", wifi_passwd);
	
}


void Test_Save()
{
	char Name[10];
	char Val[10];

	u8 i,k;
	printf("Write======================================\r\n");
	for ( i = 0; i < 10; i++)
	{
		memset(Name,0X00,sizeof(Name));
		memset(Val,0X00,sizeof(Val));
		sprintf(Name,"%d",i);
		sprintf(Val,"%d",i);
		ef_set_env_blob(Name,Val,5);
		for ( k = 0; k < sizeof(Name); k++)
		{
			printf("%c",Name[k]);
		}
		printf(" ");
		for ( k = 0; k < sizeof(Val); k++)
		{
			printf("%c",Val[k]);
		}
			printf("\r\n");

	}
	printf("Read======================================\r\n");
	for ( i = 0; i < 10; i++)
	{
		memset(Name,0X00,sizeof(Name));
		memset(Val,0X00,sizeof(Val));
		sprintf(Name,"%d",i);
		sprintf(Val,"%d",i);
		ef_get_env_blob(Name,Val,5,NULL);

		for ( k = 0; k < sizeof(Name); k++)
		{
			printf("%c",Name[k]);
		}
		printf(" ");
		for ( k = 0; k < sizeof(Val); k++)
		{
			printf("%c",Val[k]);
		}
		printf("\r\n");
	}

}

void GetData()
{


	char Name[10];
	char Val[10];

	u8 i,k;
	printf("Read======================================\r\n");
	for ( i = 0; i < 10; i++)
	{
		memset(Name,0X00,sizeof(Name));
		memset(Val,0X00,sizeof(Val));
		sprintf(Name,"%d",i);
		// sprintf(Val,"%d",i);
		ef_get_env_blob(Name,Val,5,NULL);

		for ( k = 0; k < sizeof(Name); k++)
		{
			printf("%c",Name[k]);
		}
		printf(" ");
		for ( k = 0; k < sizeof(Val); k++)
		{
			printf("%c",Val[k]);
		}
		printf("\r\n");
	}



}







void Set_New()
{

	size_t len = 0;
	printf("=================================\r\n");

	ef_get_env_blob("KFC", NULL, 0, &len);
	eedata[4095]=0;
	printf("KFC env  %d  is:%s\r\n",len, eedata);

	memset(eedata,'A',sizeof(eedata));

	ef_set_env_blob("KFC",eedata ,sizeof(eedata));
	ef_get_env_blob("KFC", NULL, 0, &len);
	//获取环境变量
	ef_get_env_blob("KFC", eedata, len, NULL);
	//打印获取的环境变量值
	eedata[4095]=0;
	printf("KFC env  %d  is:%s\r\n",len, eedata);

	memset(eedata,0,sizeof(eedata));
	ef_get_env_blob("KFC", eedata, sizeof(eedata), NULL);
	//打印获取的环境变量值
	eedata[4095]=0;
	printf("sizeof  KFC env is:%s\r\n", eedata);

}



void Write_Test()
{
	static u16 K=0;
	u8 i;
	size_t len = 0;
	u8 V_Data[50];
	char K_Data[10];

	memcpy(K_Data,"BT-",3);
	sprintf(K_Data+3,"%d",K++);

	memset(V_Data,0x72,sizeof(V_Data));

	ef_set_env_blob(K_Data,V_Data ,sizeof(V_Data));
	ef_get_env_blob(K_Data, NULL, 0, &len);
	//获取环境变量
	ef_get_env_blob(K_Data, V_Data, len, NULL);

	for ( i = 0; i < sizeof(K_Data); i++)
	{
		printf("%c ",K_Data[i]);
	}
	printf("  :  ");
	for ( i = 0; i < sizeof(K_Data); i++)
	{
		printf("%x ",V_Data[i]);
	}
	printf("\r\n");
	
}


void Read_Data()
{
	static u16 K=0;
	u8 i;
	size_t len = 0;
	u16 j; 
	u8 V_Data[50];
	char K_Data[10];

	for ( j = 0; j < 5000; j++)
	{
		memcpy(K_Data,"BT-",3);
		sprintf(K_Data+3,"%d",K++);

		ef_get_env_blob(K_Data, NULL, 0, &len);
		//获取环境变量
		ef_get_env_blob(K_Data, V_Data, len, NULL);

		for ( i = 0; i < sizeof(K_Data); i++)
		{
			printf("%c ",K_Data[i]);
		}
		printf("  :  ");
		for ( i = 0; i < sizeof(K_Data); i++)
		{
			printf("%x ",V_Data[i]);
		}
		printf("\r\n");
		IWDOG_Clear();
	}
}














u16 i;

u8 UARTDATA[10];

void CreateAllTask()
{
	//u8g2_TaskCreate();
	Create_Task();
	vTaskDelete(NULL);
}



int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	Flash_IO_Init();
	// AT24C08_Init();
	// PWM_Init(0,0);
	// OLED_Init();
	// u8g2_Init();
	// Start_Page();
	// Display_FreeRTOS_Logo();



	printf("Power Online\r\n");



	// xTaskCreate((TaskFunction_t)CreateAllTask,"StartTask",100,NULL,10,NULL);
	// vTaskStartScheduler();


	while (1)
	{	


		if( USART_GetData(&USART1_Data,sizeof(UARTDATA),UARTDATA,&i) == TRUE)
		{
			if(UARTDATA[0] == 1)
			{
				ef_env_set_default();
				printf("ReBoot\r\n", eedata);
				IWDOG_Init();
				SW_Reset();
			}
			if(UARTDATA[0] == 2)
			{
				Write_Test();
				ef_save_env();
			}
			if(UARTDATA[0] == 3)
			{
				easyflash_init();
				IWDOG_Init();
			}
			if(UARTDATA[0] == 4)
			{
				Read_Data();
			}
			UARTDATA[0]=0;
		}
		Delay_ms(10);
		LED1_ON;
		Delay_ms(10);
		LED1_OFF;
		IWDOG_Clear();

	}

}
	// XPT2046_Read(&NoUse, &TouchData);
	// 	Mov(TouchData.point.x,TouchData.point.y);
	// 	Delay_ms(10);
	//Test_UI();
	// Clock();
	// Delay_ms(10);
	// SystemDown();

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


// print("\r\n写入的冻结数据为:");

//     for(int i = 0;i< 50 ;i++)
//     {
//         //RTC_Get_CounterValue(&clock);
//         //memcpy(k_str,(char *)&clock,4);
//         HexToAscii(i,(unsigned char *)&k_str);
//         //Get_Data_Pack(v_data);
//         //PrintFrameByAscii(v_data,47);
//         print("。");
//         ef_set_env_blob(&k_str,v_data,47);
//         //IncreaseOneHour(&clock);
//     }
    
//     memset(v_data,0,sizeof(v_data));

//     print("\r\n读取的冻结数据为:");
//     for(int i = 0;i< 50 ;i++)
//     {
//         HexToAscii(i,(unsigned char *)&k_str);
//         ef_get_env_blob(&k_str,v_data,47,(size_t *)&len);
//         if(len != 0)
//             PrintFrameByAscii((unsigned char *)v_data,47);
//         print("\n");
//         IncreaseOneHour(&clock_t);
//     }


