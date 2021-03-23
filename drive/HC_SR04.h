#ifndef  HC_SR04_H
#define  HC_SR04_H



#define  TRIG_L  GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define  TRIG_H  GPIO_SetBits(GPIOA,GPIO_Pin_3)

void start_measure(void);
u32 get_distance();



#endfif





























