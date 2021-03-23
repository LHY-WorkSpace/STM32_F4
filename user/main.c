#include "IncludeFile.h"



struct _pid
{
	float SetSpeed;//定义设定值
	float ActualSpeed;//定义实际值
	float err;//定义偏差值
	float err_next;//定义上一个偏差值
	float err_last;//定义最上前的偏差值
	float Kp, Ki, Kd;//定义比例、积分、微分系数
}pid;

void PID_init()
{
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	//可设置下面的值，从而达到最佳效果
	pid.Kp = 0.1;
	pid.Ki = 0.1; 
	pid.Kd = 0.3;
}

//参数为目标值
float PID_realize(float speed)
{
	float incrementSpeed;
	pid.SetSpeed = speed;
	pid.err = pid.SetSpeed - pid.ActualSpeed;
    incrementSpeed = pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);//计算出增量
	pid.ActualSpeed += incrementSpeed;
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	return pid.ActualSpeed;
}


u8 lc=0,i=0;
float pitch,yaw,roll; 
char gg[7];




void Task_List()
{
		static u16 P=0;
			
			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{
				
				
				//lc=(u8)PID_realize(60.0);
				MPU6050_Get_DMP_Data(&pitch,&yaw,&roll);
				// PWM_SetPluseWdie(TIM4,(u16)(1500+10*pitch));
				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				

			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			
				
				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				
				// if(i>127)
				// {
				// 	i=0;
				// 	OLED_ClearScreen(0x00);
				// }
					
				// OLED_Draw_Point(i,(u8)(10+pitch),1);
				// OLED_Draw_Point(i,(u8)(30+yaw),1);
				// OLED_Draw_Point(i++,(u8)(50+roll),1);
				memset(gg,0x00,sizeof(gg));
				sprintf(gg,"%.2f",yaw);
				OLED_ShowStrings(0,0,gg,sizeof(gg));
				 OLED_UpdateGRAM();
				
				System_ResetState(Task_TimeFlag,Task_50ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
			{
				
				//printf("Task_10ms\r\n");
				System_ResetState(Task_TimeFlag,Task_100ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
			{


				System_ResetState(Task_TimeFlag,Task_200ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
			{
			
				//Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
			
				
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}




















int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	RTC_ConfigInit();
	OLED_Init();
	RTC_ConfigInit();
	MPU6050_Init();
	TaskTimer_Init();
	PWM_Init(1,1);
	PID_init();

	while(1)
	{	
		Task_List();	
	}





	
}	

	












