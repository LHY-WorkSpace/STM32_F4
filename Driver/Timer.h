#ifndef TIMER_H
#define TIMER_H
#include "stm32f4xx.h"

void TickTimer_Init(u16 Period);
void Delay_Init(void);
void Delay_us(u16 nus);//最大65535us=65.535ms
void Delay_ms(u16 nus);//最大2^16ms
u32 GetTick(void);
extern u32 RTOS_DebugTimer;

#endif







