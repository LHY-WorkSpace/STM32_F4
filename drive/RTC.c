#include "IncludeFile.h"


STM32_Time_t STM32_Time;
 
 


void RTC_Config()
{
	RTC_InitTypeDef RTC_InitStructure;	
	u8 retry=0xFF; 
	u8 i;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//使能PWR时钟
	PWR_BackupAccessCmd(ENABLE);
 
	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x5A5A)  //未配置过
	{	
		RCC_LSEConfig(RCC_LSE_ON);//LSE 开启  
		while (retry!=RESET)	//检查指定的RCC标志位设置与否,等待低速晶振就绪	
		{		
			if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET)
			{
				break;
			}
			else
			{
				delay_ms(2);	
			}	
			retry--;	
		}		
		if(retry==0)
		  return;
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟   
		RCC_RTCCLKCmd(ENABLE);                  	//使能RTC时钟  	
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC异步分频系数(1~0X7F)	
		RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTC同步分频系数(0~7FFF)	
		RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC设置为,24小时格式	
		RTC_Init(&RTC_InitStructure); 	
		RTC_Set_Time(17,56,48);	        //设置时间	
		RTC_Set_Date(18,10,16,2);		//设置日期 	
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x5A5A);
		
	} 
		

}

void RTC_Set_Time(u8 hour,u8 minute,u8 second)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;
	
	RTC_TimeTypeDefinit.RTC_Hours=hour;
	RTC_TimeTypeDefinit.RTC_Minutes=minute ;
	RTC_TimeTypeDefinit.RTC_Seconds=second ;
	RTC_TimeTypeDefinit.RTC_H12=RTC_H12_PM;
	
	RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeDefinit);

}


void RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_DateTypeDefinit.RTC_Year=year;
	RTC_DateTypeDefinit.RTC_Month=month;
	RTC_DateTypeDefinit.RTC_Date=date;
	RTC_DateTypeDefinit.RTC_WeekDay=week ;	

	RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeDefinit);

}



void RTC_Get_Time(STM32_Time_t* STM32_Time)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;

	RTC_GetTime(RTC_Format_BIN,&RTC_TimeTypeDefinit);
	
	STM32_Time->hour=RTC_TimeTypeDefinit.RTC_Hours;
	STM32_Time->minute=RTC_TimeTypeDefinit.RTC_Minutes;
	STM32_Time->second=RTC_TimeTypeDefinit.RTC_Seconds;
}



void RTC_Get_Date(STM32_Time_t* STM32_Time)
{
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_GetDate(RTC_Format_BIN,&RTC_DateTypeDefinit);
	
	STM32_Time->year=RTC_DateTypeDefinit.RTC_Year;
	STM32_Time->month=RTC_DateTypeDefinit.RTC_Month;
	STM32_Time->date=RTC_DateTypeDefinit.RTC_Date;
	STM32_Time->date=RTC_DateTypeDefinit.RTC_WeekDay;
}



//	RTC_GetTime(RTC_Format_BIN,&RTC_TimeTypeDefttt);
//	RTC_GetDate(RTC_Format_BIN,&RTC_DateTypeDefddd);


//	display_position(36,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Year)/10);
//	display_position(44,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Year)%10);      //15
//	
//	display_position(52,1,1);
//	display_char('.');
//	
//	display_position(60,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Month)/10);
//	display_position(68,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Month)%10);      //月	
//	
//	display_position(76,1,1);
//	display_char('.');
//	
//	
//	display_position(84,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Date)/10);
//	display_position(92,1,1);
//	display_num(((int)RTC_DateTypeDefddd.RTC_Date)%10);	      //日
//	
//	
//	display_position(25,3,8);
//	display_str_and_speed("weekday:",1); 
//	display_position(89,3,1);
//	display_num((int)RTC_DateTypeDefddd.RTC_WeekDay);	  //星期
//	

//	
//	display_position (30,5,1);	
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Hours)/10);
//	display_position (38,5,1);
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Hours)%10);	//时
//	
//	display_position (46,5,1);
//	display_char(':');
//	
//	display_position (54,5,1);	
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Minutes)/10);
//	display_position (62,5,1);
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Minutes)%10);       //分
//	
//	
//	display_position (70,5,1);
//	display_char(':');
//	
//	display_position (78,5,1);	
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Seconds)/10);
//	display_position (86,5,1);
//	display_num(((int)RTC_TimeTypeDefttt.RTC_Seconds)%10);       //	秒	
















