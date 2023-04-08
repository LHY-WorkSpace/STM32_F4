#ifndef   LED_H
#define   LED_H
#include "stm32f4xx.h"


#define  LED1_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define  LED1_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_9)


void led_init(void);
void Led_Test(void);
void LED_Freq(void);
void LED_Task(void);
#endif
