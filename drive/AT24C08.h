#ifndef  _AT24C08_H_
#define  _AT24C08_H_

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int



#define AT24C08_ADDRESS                 (0xA0)                                   //AT24C02 device address
#define AT24C08_BLOCK0_ADDRESS          (AT24C08_ADDRESS|0x00)
#define AT24C08_BLOCK1_ADDRESS          (AT24C08_ADDRESS|0x02)
#define AT24C08_BLOCK2_ADDRESS          (AT24C08_ADDRESS|0x04)
#define AT24C08_BLOCK3_ADDRESS          (AT24C08_ADDRESS|0x06)
#define AT24C08_READ_DATA                0x01
#define AT24C08_WRITE_DATA               0x00


void AT24C08_init(void);
u8 AT24C08Read_Byte(u8 dev_addr,u8 Data_addr);
void AT24C08Write_Byte(u8 dev_addr,u8 Data_addr,u8 data);
void AT24C08Read_NBytes(u8 dev_addr,u8 addr,u8 length,u8 *data);
void AT24C08Write_NBytes(u8 dev_addr,u8 addr,u8 length,u8 *data);




#endif



