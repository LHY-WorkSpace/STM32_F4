#ifndef  KEYPAD_H
#define  KEYPAD_H

 
#define KEY_OK  			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define KEY_BACK  		 	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define KEY_UP  			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define KEY_DOWN 			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

typedef enum
{
    OK_KEY = 0,
    BACK_KEY,
    UP_KEY,
    DOWN_KEY,
    MAX_KEY
}Key_ID_e;




void KeyInit(void);
u8 KeyGetID(u8 ID);

#endif



