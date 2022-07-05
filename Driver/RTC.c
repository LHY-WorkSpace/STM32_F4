#include "IncludeFile.h"

const u8 STM32_RTCDefault[] = {21, 11, 11, 5, 15, 20, 55};

RTC_Time_t STM32_Time;

void RTC_ConfigInit()
{
	RTC_InitTypeDef RTC_InitStructure;
	u8 retry = 0xFF;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //使能PWR时钟
	PWR_BackupAccessCmd(ENABLE);

	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x5A5A) //未配置过
	{
		RCC_LSEConfig(RCC_LSE_ON); // LSE 开启
		while (retry != RESET)	   //检查指定的RCC标志位设置与否,等待低速晶振就绪
		{
			if (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET)
			{
				break;
			}
			else
			{
				Delay_us(5);
			}
			retry--;
		}
		if (retry == 0)
		{
			return;
		}

		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);				  //设置RTC时钟(RTCCLK),选择LSE作为RTC时钟
		RCC_RTCCLKCmd(ENABLE);								  //使能RTC时钟
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;			  // RTC异步分频系数(1~0X7F)
		RTC_InitStructure.RTC_SynchPrediv = 0xFF;			  // RTC同步分频系数(0~7FFF)
		RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24; // RTC设置为,24小时格式
		RTC_Init(&RTC_InitStructure);
		RTC_Set_Time(STM32_Time); //设置时间
		RTC_Set_Date(STM32_Time); //设置日期
		RTC_WriteBackupRegister(RTC_BKP_DR0, 0x5A5A);
	}
}

void RTC_Set_Time(RTC_Time_t Time)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;

	RTC_TimeTypeDefinit.RTC_Hours = Time.hour;
	RTC_TimeTypeDefinit.RTC_Minutes = Time.minute;
	RTC_TimeTypeDefinit.RTC_Seconds = Time.second;
	RTC_TimeTypeDefinit.RTC_H12 = RTC_H12_PM;

	RTC_SetTime(RTC_Format_BIN, &RTC_TimeTypeDefinit);
}

void RTC_Set_Date(RTC_Time_t Time)
{
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_DateTypeDefinit.RTC_Year = Time.year;
	RTC_DateTypeDefinit.RTC_Month = Time.month;
	RTC_DateTypeDefinit.RTC_Date = Time.date;
	RTC_DateTypeDefinit.RTC_WeekDay = Time.week;

	RTC_SetDate(RTC_Format_BIN, &RTC_DateTypeDefinit);
}

void RTC_Get_Time(RTC_Time_t *Time)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_GetDate(RTC_Format_BIN, &RTC_DateTypeDefinit);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeTypeDefinit);

	Time->hour = RTC_TimeTypeDefinit.RTC_Hours;
	Time->minute = RTC_TimeTypeDefinit.RTC_Minutes;
	Time->second = RTC_TimeTypeDefinit.RTC_Seconds;
	Time->year = RTC_DateTypeDefinit.RTC_Year;
	Time->month = RTC_DateTypeDefinit.RTC_Month;
	Time->date = RTC_DateTypeDefinit.RTC_Date;
	Time->week = RTC_DateTypeDefinit.RTC_WeekDay;
}

/*
void RTC_Set_Alarm(u8* Data,u8 length)
{
u8 SetBit=0;
u8 i;

	if(length>5)
		return;

	for(i=0;i++;i<5)
	{
		if(Data[i]!=0xFF)
		{
			SetBit|=0x01;
		}
		SetBit<<=1;
	}

	if(SetBit&0x10)    //如果日期置位，则忽略星期的闹钟(日期和星期互斥)
	{
		SetBit&=(~0x08);
	}





	for(i=0;i++;i<5)
	{
		SetBit>>=i;
		if(SetBit&0x01)
		{
			switch(i)
			{
				case 0:
				break;

				case 1:
				break;

				case 2:
				break;

				case 3:
				break;

				case 4:
				break;

				case 5:
				break;

				case 6:
				break;

			}
		}

	}





}
*/
