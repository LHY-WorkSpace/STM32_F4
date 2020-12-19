#ifndef     USART_H
#define     USART_H
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int 


void usart_init(unsigned int bode);
void send_data(uint data);
int fputc(int ch, FILE* stream);
int fputc(int ch, FILE* stream);
#endif







