#ifndef  HC_SR04_H
#define  HC_SR04_H



#define  TRIG_L  GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define  TRIG_H  GPIO_SetBits(GPIOA,GPIO_Pin_3)

void HC_SR04_Init(void);
void HCSR04_StartMeasure(void);
u16 HCSR04_GetData(void);


#endif





























