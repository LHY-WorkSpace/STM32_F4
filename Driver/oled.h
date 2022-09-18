#ifndef  OLED_H
#define  OLED_H


	
#define  OLED_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //复位关
#define  OLED_RST_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14)	          //复位开
#define  OLED_DATA      GPIO_SetBits(GPIOB,GPIO_Pin_12)	              //数据
#define  OLED_ORDER     GPIO_ResetBits(GPIOB,GPIO_Pin_12)	          //命令




#define Twink_Mode    0x30      //闪烁模式
#define Hidden_Mode   0x20      //消退模式



//左右滚屏
#define  SCROLL_L          0x27            
#define  SCROLL_R          0x26
//左右和垂直向上滚屏
#define  SCROLL_VR          0x29            
#define  SCROLL_VL          0x2A








void OLED_Init(void);
void OLED_SetScanFre(u8 fre,u8 div);   
void OLED_SetContrast(u8 value); 
void OLED_SetTwinkMode(u8 Mode,u8 Speed);
void OLED_TurnON(void);
void OLED_TurnOFF(void);
void OLED_Scroll_LR(u8 Direction,u8 FrameFrq,u8 PageStart,u8 PageEnd);
void OLED_Scroll_Vx(u8 Direction,u8 FrameFrq,u8 Offset,u8 PageStart,u8 PageEnd);
void OLED_ClearScreen(u8 Data);
void OLED_UpdateGRAM(void);

#if (USE_U8G2 == FALSE)
void OLED_Data2GRAM(u8 *Data,u16 length); 
void OLED_ShowChar(u8 x,u8 y,u8* Data);
void OLED_ShowStrings(u8 x,u8 y,char* Data,u8 Length);
void OLED_ShowNumber(u8 x,u8 y,u16 Num,u8 Bit);
void OLED_MoveDisplay(u8 x,u8 y,u8 High,u8 num,u8 *p);
void UpdateOneColumn(u8 x,u8 y,u8 High,u8 p,u8 offset);


void OLED_Draw_Point(u8 x,u8 y,u8 t);
u8   OLED_Get_Point(u8 x,u8 y);
void OLED_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2);
void OLED_Draw_Circle(u8 x0,u8 y0,u8 r);
void OLED_Draw_FullCircle(u16 x0,u16 y0,u8 r);
void Boot_Animation(void);
void windows_open(u32);
void tempure_unit(void);							//温度单位
 void Test(void); 
 #endif

#endif






















