#ifndef ST7789_H
#define ST7789_H


#define  TFT_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //��λ��
#define  TFT_RST_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14)	          //��λ��
#define  TFT_DATA      GPIO_SetBits(GPIOB,GPIO_Pin_12)	              //����
#define  TFT_CMD       GPIO_ResetBits(GPIOB,GPIO_Pin_12)	          //����
#define  TFT_LED_ON    GPIO_SetBits(GPIOB,GPIO_Pin_11)	              //���⿪
#define  TFT_LED_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_11)	          //�����


void TFT_Init(void);
void TFT_full(u16 color);

#endif
