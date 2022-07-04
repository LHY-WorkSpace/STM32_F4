#ifndef  DHT11_H
#define  DHT11_H
#include "DataType.h"


#define  DHT11_HIGH         GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define  DHT11_LOW          GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define  DHT11_IO_STATE     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)


typedef struct
{
	B16_B08 Tempure;
    B16_B08 Humidity;
	u8 CheckSum;
}DHT11_Data_t;


void DHT11_GPIO_Init(void);
u8 DHT11_Read_Data(DHT11_Data_t *DHT11_Data);

 


#endif



