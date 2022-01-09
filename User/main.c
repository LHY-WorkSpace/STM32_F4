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
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
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





