#include "IncludeFile.h"




void CreateAllTask()
{
	//u8g2_TaskCreate();
	//Create_Task();
	vTaskDelete(NULL);
}








int  main()
{
	u16 i=0;
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	// USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	led_init();

	TickTimer_Init(1);


	TFT_Init();

	printf("Power Online\r\n");

	lv_init();
	lv_port_disp_init();
	// lv_port_indev_init();

	// lv_ex_img_1();
	// lv_ex_img_2();
	// lv_ex_keyboard_1();
	// lv_demo_stress();
	lv_demo_benchmark();
	// lv_example_gif_1();
	// xTaskCreate((TaskFunction_t)CreateAllTask,"StartTask",100,NULL,10,NULL);
	// vTaskStartScheduler();
	// lv_demo_keypad_encoder();

	while (1)
	{	
		lv_task_handler();
		// lv_tick_inc(10);
		// Delay_ms(20);

		// TFT_full(TFT_RED);
		// Delay_ms(500);
		// ST7789_SetArea(50,50,100,100);
		// for ( i = 0; i < sizeof(MemAddr)/sizeof(MemAddr[0]); i++)
		// {
		// 	MemAddr[i]=TFT_BLUE;
		// }
		// TFT_DMA_Start((u32)&MemAddr[0],2500*2);
		// Delay_ms(100);
		// ST7789_SetArea(100,50,150,100);
		// for ( i = 0; i < 2500; i++)
		// {
		// 	ST7789_DrawPoint(TFT_BLUE);
		// }
		// Delay_ms(100);

		// ST7789_SetArea(0,0,240,240);
		// Colour = TFT_RED;
		// TFT_DMA_Start((u32)&Colour,240*240);
		// Delay_ms(300);

		// ST7789_SetArea(0,0,240,240);
		// Colour = TFT_GREEN;
		// TFT_DMA_Start((u32)&Colour,240*240);
		// Delay_ms(300);


		// ST7789_SetArea(0,0,240,240);
		// Colour = TFT_BLUE;
		// TFT_DMA_Start((u32)&Colour,240*240);
		// Delay_ms(300);

		// TFT_full(TFT_RED);
		// Delay_ms(300);
		// TFT_full_DMA(TFT_BLUE);
		// Delay_ms(300);


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


