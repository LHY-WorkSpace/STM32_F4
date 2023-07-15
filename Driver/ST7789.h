#ifndef ST7789_H
#define ST7789_H



#define DISP_HOR_RES    320
#define DISP_VER_RES    240


#define  ST7789_RST_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_4)	              //复位关
#define  ST7789_RST_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	          //复位开

#define  ST7789_DATA      GPIO_SetBits(GPIOA,GPIO_Pin_6)	              //数据
#define  ST7789_CMD       GPIO_ResetBits(GPIOA,GPIO_Pin_6)	          //命令

#define  ST7789_LED_ON    GPIO_SetBits(GPIOA,GPIO_Pin_11)	              //背光开
#define  ST7789_LED_OFF   GPIO_ResetBits(GPIOA,GPIO_Pin_11)	          //背光关


#define ST7789_RED     0xf800
#define ST7789_GREEN   0x07e0
#define ST7789_BLUE    0x001f
#define ST7789_WHITE   0xffff
#define ST7789_BLACK   0x0000
#define ST7789_YELLOW  0xFFE0
#define ST7789_GRAY0   0xEF7D   
#define ST7789_GRAY1   0x8410      	
#define ST7789_GRAY2   0x4208 





void ST7789_Init(void);
void ST7789_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void ST7789_DrawPoint(u16 color);
void ST7789_Full(u16 Color);


void ST7789_DMA_Start(void);
void ST7789_DMA_SetAddr(u32 StartAddr, u32 Point);
u32 ST7789_DMA_GetCurrentAddr(void);
void ST7789_DMA_SetAddr(u32 StartAddr, u32 Point);
u8 ST7789_DMA_ISR_GetTXComplateFlag(void);
void ST7789_DMA_Start(void);
void ST7789_DMA_Stop(void);
void ST7789_SwapDataForDMA(u16 *Data);
u8 ST7789_DMA_GetTXState(void);
#endif
