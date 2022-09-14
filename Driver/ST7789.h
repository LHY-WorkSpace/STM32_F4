#ifndef ST7789_H
#define ST7789_H


#define  TFT_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //复位关
#define  TFT_RST_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14)	          //复位开
#define  TFT_DATA      GPIO_SetBits(GPIOB,GPIO_Pin_12)	              //数据
#define  TFT_CMD       GPIO_ResetBits(GPIOB,GPIO_Pin_12)	          //命令
#define  TFT_LED_ON    GPIO_SetBits(GPIOB,GPIO_Pin_11)	              //背光开
#define  TFT_LED_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_11)	          //背光关


void TFT_Init(void);
void TFT_full(u16 color);

#endif
