#include "IncludeFile.h"


extern USART_Data_t USART1_Data;


void CreateAllTask(void *pv)
{
	u8g2_TaskCreate();
	vTaskDelete(NULL);
}

u8 Dir = TRUE;


u8 eedata[4096];

void test_env(void)
{
	char wifi_ssid[20] = {0};
	char wifi_passwd[20] = {0};
	size_t len = 0;
	


	/* ��ȡĬ�ϻ�������ֵ */
	//������������δ֪���Ȼ�ȡ Flash �ϴ洢��ʵ�ʳ��� */
	ef_get_env_blob("BT-XXXX", NULL, 0, &len);
	//��ȡ��������
	ef_get_env_blob("BT-XXXX", wifi_ssid, len, NULL);
	//��ӡ��ȡ�Ļ�������ֵ
	printf("BT-XXXX env is:%s\r\n", wifi_ssid);
	
	//������������δ֪���Ȼ�ȡ Flash �ϴ洢��ʵ�ʳ��� */
	ef_get_env_blob("Jack Cooper", NULL, 0, &len);
	//��ȡ��������
	ef_get_env_blob("Jack Cooper", wifi_passwd, len, NULL);
	//��ӡ��ȡ�Ļ�������ֵ
	printf("Jack Cooper env is:%s\r\n", wifi_passwd);


	// // // /* ����������ֵ�ı� */
	// ef_set_env_blob("BT-XXXX", "12345", 5);
	// ef_set_env_blob("Jack Cooper", "54321", 5);


	// memset(wifi_ssid,0x00,sizeof(wifi_ssid));
	// memset(wifi_passwd,0x00,sizeof(wifi_passwd));


	// // /* ��ȡĬ�ϻ�������ֵ */
	// //������������δ֪���Ȼ�ȡ Flash �ϴ洢��ʵ�ʳ��� */
	// ef_get_env_blob("BT-XXXX", NULL, 0, &len);
	// //��ȡ��������
	// ef_get_env_blob("BT-XXXX", wifi_ssid, len, NULL);
	// //��ӡ��ȡ�Ļ�������ֵ
	// printf("BT-XXXX env is:%s\r\n", wifi_ssid);
	
	// //������������δ֪���Ȼ�ȡ Flash �ϴ洢��ʵ�ʳ��� */
	// ef_get_env_blob("Jack Cooper", NULL, 0, &len);
	// //��ȡ��������
	// ef_get_env_blob("Jack Cooper", wifi_passwd, len, NULL);
	// //��ӡ��ȡ�Ļ�������ֵ
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
	//��ȡ��������
	ef_get_env_blob("KFC", eedata, len, NULL);
	//��ӡ��ȡ�Ļ�������ֵ
	eedata[4095]=0;
	printf("KFC env  %d  is:%s\r\n",len, eedata);

	memset(eedata,0,sizeof(eedata));
	ef_get_env_blob("KFC", eedata, sizeof(eedata), NULL);
	//��ӡ��ȡ�Ļ�������ֵ
	eedata[4095]=0;
	printf("sizeof  KFC env is:%s\r\n", eedata);

}
u16 i;

u8 UARTDATA[10];
int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	Flash_IO_Init();
	// Dir = ESP8266_Init();
	led_init();
	
	printf("Power Online\r\n");

	// AT24C08_Init();
	// PWM_Init(0,0);
	// OLED_Init();
	// u8g2_Init();
	// Start_Page();
	// Display_FreeRTOS_Logo();

	//test_env();

	// Set_New();
	// ef_save_env();



	// ef_env_set_default();


	// Flash_Read_Data(0,eedata,500);

	
	// for (i = 0; i < 500; i++)
	// {
	// 	printf("addr:%x  %x  \r\n",i,eedata[i]);
	// }
	

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
				Test_Save();
				ef_save_env();
			}
			if(UARTDATA[0] == 3)
			{
				easyflash_init();
				IWDOG_Init();
			}
			if(UARTDATA[0] == 4)
			{
				GetData();
				test_env();
			}		
			
			
			UARTDATA[0]=0;
		}
		Delay_ms(500);
		LED1_ON;
		Delay_ms(500);
		LED1_OFF;
		IWDOG_Clear();

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


// print("\r\nд��Ķ�������Ϊ:");

//     for(int i = 0;i< 50 ;i++)
//     {
//         //RTC_Get_CounterValue(&clock);
//         //memcpy(k_str,(char *)&clock,4);
//         HexToAscii(i,(unsigned char *)&k_str);
//         //Get_Data_Pack(v_data);
//         //PrintFrameByAscii(v_data,47);
//         print("��");
//         ef_set_env_blob(&k_str,v_data,47);
//         //IncreaseOneHour(&clock);
//     }
    
//     memset(v_data,0,sizeof(v_data));

//     print("\r\n��ȡ�Ķ�������Ϊ:");
//     for(int i = 0;i< 50 ;i++)
//     {
//         HexToAscii(i,(unsigned char *)&k_str);
//         ef_get_env_blob(&k_str,v_data,47,(size_t *)&len);
//         if(len != 0)
//             PrintFrameByAscii((unsigned char *)v_data,47);
//         print("\n");
//         IncreaseOneHour(&clock_t);
//     }


