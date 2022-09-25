#ifndef ST7789_H
#define ST7789_H


#define  TFT_RST_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_4)	              //复位关
#define  TFT_RST_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	          //复位开

#define  TFT_DATA      GPIO_SetBits(GPIOA,GPIO_Pin_6)	              //数据
#define  TFT_CMD       GPIO_ResetBits(GPIOA,GPIO_Pin_6)	          //命令

#define  TFT_LED_ON    GPIO_SetBits(GPIOA,GPIO_Pin_11)	              //背光开
#define  TFT_LED_OFF   GPIO_ResetBits(GPIOA,GPIO_Pin_11)	          //背光关


#define TFT_RED  		0xf800
#define TFT_GREEN		0x07e0
#define TFT_BLUE 		0x001f
#define TFT_WHITE		0xffff
#define TFT_BLACK		0x0000
#define TFT_YELLOW  0xFFE0
#define TFT_GRAY0   0xEF7D   
#define TFT_GRAY1   0x8410      	
#define TFT_GRAY2   0x4208 





void TFT_Init(void);
void TFT_full(u16 color);
void ST7789_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void ST7789_DrawPoint(u16 color);
void TFT_DMA_Start(void);
void TFT_full_DMA(u16 Color);
void TFT_SwapDataForDMA(u16 *Data);
#endif
