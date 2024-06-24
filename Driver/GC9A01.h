#ifndef GC9A01_H
#define GC9A01_H


#define  GC9A01_RST_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_4)        //复位关
#define  GC9A01_RST_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_4)      //复位开

#define  GC9A01_DATA      GPIO_SetBits(GPIOA,GPIO_Pin_6)        //数据
#define  GC9A01_CMD       GPIO_ResetBits(GPIOA,GPIO_Pin_6)      //命令

#define  GC9A01_LED_ON    GPIO_SetBits(GPIOA,GPIO_Pin_11)       //背光开
#define  GC9A01_LED_OFF   GPIO_ResetBits(GPIOA,GPIO_Pin_11)     //背光关


#define GC9A01_RED     0xf800
#define GC9A01_GREEN   0x07e0
#define GC9A01_BLUE    0x001f
#define GC9A01_WHITE   0xffff
#define GC9A01_BLACK   0x0000
#define GC9A01_YELLOW  0xFFE0
#define GC9A01_GRAY0   0xEF7D   
#define GC9A01_GRAY1   0x8410      	
#define GC9A01_GRAY2   0x4208 





void GC9A01_Init(void);
void GC9A01_SetArea(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void GC9A01_DrawPoint(u16 color);
void GC9A01_Full(u16 Color);


void GC9A01_DMA_Start(void);
void GC9A01_DMA_SetAddr(u32 StartAddr, u32 Point);
u32 GC9A01_DMA_GetCurrentAddr(void);
void GC9A01_DMA_SetAddr(u32 StartAddr, u32 Point);
u8 GC9A01_DMA_ISR_GetTXComplateFlag(void);
void GC9A01_DMA_Start(void);
void GC9A01_DMA_Stop(void);
void GC9A01_SwapDataForDMA(u16 *Data);
u8 GC9A01_DMA_GetTXState(void);
#endif
