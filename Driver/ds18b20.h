#ifndef   DS18B20_H
#define   DS18B20_H

#define USE_NOP                 0x11
#define USE_TIMER               0x22


#define   DELAY_TYPE    USE_TIMER

#define  DS18B20_HIGH           GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define  DS18B20_LOW            GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define  DS18B20_IO_STATE       GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)

#define  DS18B20_RESOLUTION   (0.0625f)//·Ö±æÂÊ


typedef struct
{
	u8 ID[8];
	u8 TH_Reg;
	u8 TL_Reg;
	u8 Config_Reg;
	u8 Reserved_FFH;
	u8 Reserved;
	u8 Reserved_10H;
	u8 CRC8;

}DS18B20_Info_t;


void DS18B20_GPIO_Init(void);
float DS18B20_Get_Temperature(void);
void DS18B20_GetID(void);

#endif


























