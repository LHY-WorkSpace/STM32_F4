#ifndef     USART_H
#define     USART_H
#include "stdio.h"

#define u8 unsigned char
#define u32 unsigned int 


void usart_init(unsigned int bode);
void send_data(u32 data);
int fputc(int ch, FILE* stream);
int fputc(int ch, FILE* stream);
#endif







