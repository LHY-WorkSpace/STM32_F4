#ifndef TIMER_H
#define TIMER_H
#include "stm32f4xx.h"

#if ( configUSE_TRACE_FACILITY == 1 )
    extern u32 RTOS_DebugTimer;
#endif

void LVGL_TimerInit(u16 Period);
u32 LVGL_GetTick(void);
void Delay_Init(void);
void Delay_us(u16 nus);//最大65535us=65.535ms
void Delay_ms(u16 nus);//最大2^16ms
void RTOSDebugTimerInit(void);

#endif







