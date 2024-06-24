#ifndef  EEPROM_H
#define  EEPROM_H


#define EEPROM_SIZE                 (32 * 1024) // 字节
#define EEPROM_PAGE_SIZE            (64)    // 字节
#define EEPROM_PAGES                (EEPROM_SIZE / EEPROM_PAGE_SIZE) // 页数 内部Ram按页(EEPROM_PAGE_SIZE Byte)对齐
#define EEPROM_ADDRESS              (0xA0)  //设备地址

//SCL
#define EE_IIC_SCL_LOW  			GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define EE_IIC_SCL_HIGH  		 	GPIO_SetBits(GPIOB,GPIO_Pin_0)
//SDA
#define EE_IIC_SDA_LOW  			GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define EE_IIC_SDA_HIGH 			GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define EE_IIC_SDA_STATE            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)



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



