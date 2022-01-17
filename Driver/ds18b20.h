#ifndef   DS18B20_H
#define   DS18B20_H


#define  DS18B20_HIGH   GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define  DS18B20_LOW    GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define  IO_STATE       GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

void DS18B20_Write_Byte(u8 Data);
u8 DS18B20_Read_Byte(void);
u8 DS18B20_Init(void);


#endif


























