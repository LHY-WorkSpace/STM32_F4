#ifndef  _EEPROM_H_
#define  _EEPROM_H_



#define EEPROM_PAGE_SIZE                 (16)   //字节
#define EEPROM_PAGES                     (64)   //页数 内部Ram按页(16 Byte)对齐
#define EEPROM_ADDRESS                   (0xA0)  //AT24C02 设备地址




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


#define EEPROM_ADDR(NUMBER)          ((u16)&(((EEPROM_MAP *)0)->NUMBER))   

void EEPROM_Init(void);
u8  EEPROMWriteData(u16 addr,u16 length,u8 *data);
u8 EEPROMReadData(u16 addr,u16 length,u8 *data);

#endif



