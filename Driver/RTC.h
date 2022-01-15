#ifndef RTC_H
#define RTC_H

typedef struct
{
    u8 year;
    u8 month;
    u8 date;
    u8 week;
    u8 hour;
    u8 minute;
    u8 second;

} RTC_Time_t;

void RTC_ConfigInit(void);
void RTC_Set_Date(RTC_Time_t Time);
void RTC_Set_Time(RTC_Time_t Time);
void RTC_Get_Time(RTC_Time_t *Time);
void RTC_Get_Date(RTC_Time_t* Date);
#endif
