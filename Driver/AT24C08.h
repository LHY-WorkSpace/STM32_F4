#ifndef  _AT24C08_H_
#define  _AT24C08_H_



#define AT24C08_PAGE_SIZE                 (16)   //�ֽ�
#define AT24C08_PAGES                     (64)   //ҳ�� �ڲ�Ram��ҳ(16 Byte)����
#define AT24C08_ADDRESS                   (0xA0)  //AT24C02 �豸��ַ

#define EEPROM_ADDR(TTYPE,NUMBER)          ((u16)&((TYPE *)0)->NUMBER))   


#pragma pack (1)

typedef struct
{
    u8 OLED_Data[10];
    u8 LCD_Data[10];
}EEPROM_Data_t;

typedef union
{
    u8 EEPROM_MEM[1024];
    EEPROM_Data_t EEPROM_Data;
}EEPROM_MAP;

#pragma pack ()

void AT24C08_init(void);
u8 AT24C08Read_Byte(u8 dev_addr,u8 Data_addr);
void AT24C08Write_Byte(u8 dev_addr,u8 Data_addr,u8 data);
// void AT24C08Read_NBytes(u8 dev_addr,u8 addr,u16 length,u8 *data);
u8  AT24C08Write_NBytes(u16 addr,u16 length,u8 *data);
u8 AT24C08Read_NBytes(u16 addr,u16 length,u8 *data);

#endif



