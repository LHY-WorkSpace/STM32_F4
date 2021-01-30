#ifndef  _AT24C08_H_
#define  _AT24C08_H_
//#include "stm32f4xx.h"
////#define u8unsigned char
//#define u16 unsigned short
////#define u32 unsigned int

#define AT24C08_ADDRESS                 (0xA0)                                   //AT24C02 device address

void AT24C08_init(void);
u8 AT24C08Read_Byte(u8 dev_addr,u16 Data_addr);
void AT24C08Write_Byte(u8 dev_addr,u16 Data_addr,u8 data);
void AT24C08Read_NBytes(u8 dev_addr,u16 addr,u16 length,u8 *data);
void AT24C08Write_NBytes(u8 dev_addr,u16 addr,u16 length,u8 *data);


#endif



