#include "stm32f4xx.h"
#include "delay.h"
#define uchar unsigned char
#define uint unsigned int 



void delay_us(uint nus)         //最大798915us
{
 uint  temp;
 SysTick->LOAD = 21*nus;
 SysTick->VAL=0X00;
 SysTick->CTRL=0X01;
 do
 {
  temp=SysTick->CTRL;
 }while((temp&0x01)&&(!(temp&(1<<16))));
    
		SysTick->CTRL=0x00; 
    SysTick->VAL =0X00;
}



void delay_ms(uint nms)        //最大798ms
{
 uint temp;
 SysTick->LOAD = 21*1000*nms;
 SysTick->VAL=0X00;
 SysTick->CTRL=0X01;
 do
 {
  temp=SysTick->CTRL;
 }while((temp&0x01)&&!(temp&(1<<16)));	
		SysTick->CTRL=0x00;
    SysTick->VAL =0X00; 
}


