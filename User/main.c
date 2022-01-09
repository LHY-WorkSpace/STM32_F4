#include "IncludeFile.h"







void draw(u8g2_t *u8g2)
{
	static u8 k=0,i=0;
    // u8g2_SetFontMode(u8g2, 1);  // Transparent
    // u8g2_SetFontDirection(u8g2, 0);
    // u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    // u8g2_DrawStr(u8g2, 0, 20, "U");
    
    // u8g2_SetFontDirection(u8g2, 1);
    // u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    // u8g2_DrawStr(u8g2, 21,8,"8");
        
    // u8g2_SetFontDirection(u8g2, 0);
    // u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    // u8g2_DrawStr(u8g2, 51,30,"g");
    // u8g2_DrawStr(u8g2, 67,30,"\xb2");
    
    // u8g2_DrawHLine(u8g2, 2, 35, 47);
    // u8g2_DrawHLine(u8g2, 3, 36, 47);
    // u8g2_DrawVLine(u8g2, 45, 32, 12);
    // u8g2_DrawVLine(u8g2, 46, 33, 12);
  
    // u8g2_SetFont(u8g2, u8g2_font_5x7_tr);
    // u8g2_DrawStr(u8g2, 1,54,"github.com/olikraus/u8g2");


	//u8g2_SetupBitmap();
	u8g2_SetFontDirection(u8g2, 0);
	u8g2_SetFont(u8g2, u8g2_font_open_iconic_www_2x_t);
	u8g2_DrawGlyph(u8g2,16*i,16,0x40+i);
	u8g2_SetFont(u8g2, u8g2_font_open_iconic_embedded_2x_t);
	u8g2_DrawGlyph(u8g2,16*i,32,0x40+i);
	u8g2_SetFont(u8g2, u8g2_font_streamline_all_t);
	u8g2_DrawGlyph(u8g2,21*i,52,0x220+i);




	u8g2_SetFont(u8g2, u8g2_font_battery19_tn);
	u8g2_SetFontDirection(u8g2, 1);
	u8g2_DrawGlyph(u8g2,19,52,0x30+k);
	k++;
	i++;
	if(k==7)
		k=0;
	if(i==6)
	{
		u8g2_FirstPage(u8g2);	
		i=0;
	}
	
		
	
	
	// u8g2_SetBitmapMode(u8g2,1);
	// u8g2_DrawXBM(u8g2,0,0,8,8,&u8g2_font_open_iconic_www_1x_t[0]);


}



static u8 P=0;

int  main()
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	//USART2_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	led_init();
	OLED_Init();









  while (1)
  {
    
    do
    {
    	draw(&u8g2);
    } while (u8g2_NextPage(&u8g2));
	delay_ms(10);
	//u8g2_SetContrast(&u8g2,P);
	P++;
  }

//   while (1)
//   {
//     u8g2_FirstPage(&u8g2);
//     do
//     {
//       u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
//       u8g2_DrawStr(&u8g2, 0, 15, "Hello World!");
//       u8g2_DrawCircle(&u8g2, 64, 40, 10, U8G2_DRAW_ALL);
//     } while (u8g2_NextPage(&u8g2));
//   }



	SystemDown();

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





