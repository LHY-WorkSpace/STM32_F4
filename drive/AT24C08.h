#ifndef  _AT24C08_H_
#define  _AT24C08_H_

#define uchar unsigned char
#define uint unsigned int


#define AT24C08_ADDRESS                 (0xA0)                                   //AT24C02 device address
#define AT24C08_BLOCK0_ADDRESS          (AT24C08_ADDRESS|0x00)
#define AT24C08_BLOCK1_ADDRESS          (AT24C08_ADDRESS|0x02)
#define AT24C08_BLOCK2_ADDRESS          (AT24C08_ADDRESS|0x04)
#define AT24C08_BLOCK3_ADDRESS          (AT24C08_ADDRESS|0x06)
#define AT24C08_READ_DATA                0x01
#define AT24C08_WRITE_DATA               0x00


void AT24C08_init(void);
uchar AT24C08Read_Byte(uchar dev_addr,uchar Data_addr);
void AT24C08Write_Byte(uchar dev_addr,uchar Data_addr,uchar data);
void AT24C08Read_NBytes(uchar dev_addr,uchar addr,uchar length,uchar *data);
void AT24C08Write_NBytes(uchar dev_addr,uchar addr,uchar length,uchar *data);




#endif



