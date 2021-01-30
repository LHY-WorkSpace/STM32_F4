#ifndef  _AT24C08_H_
#define  _AT24C08_H_


#define AT24C08_ADDRESS                (0xA0)    //AT24C02 device address
#define AT24C08_BLOCK1                 (AT24C08_ADDRESS|0x00)                                   
#define AT24C08_BLOCK2                 (AT24C08_ADDRESS|0x02)                                 
#define AT24C08_BLOCK3                 (AT24C08_ADDRESS|0x04)                                    
#define AT24C08_BLOCK4                 (AT24C08_ADDRESS|0x06)                                  

void AT24C08_init(void);
u8 AT24C08Read_Byte(u8 dev_addr,u8 Data_addr);
void AT24C08Write_Byte(u8 dev_addr,u8 Data_addr,u8 data);
void AT24C08Read_NBytes(u8 dev_addr,u8 addr,u16 length,u8 *data);
void AT24C08Write_NBytes(u8 dev_addr,u8 addr,u16 length,u8 *data);


#endif



