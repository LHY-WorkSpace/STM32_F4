#ifndef __ILI9341_H
#define __ILI9341_H	
#include "IncludeFile.h"
#include "stdlib.h" 




/*
触摸
PA4--Touch_CS
PA5--SPI_CLK
PA6--MISO
PA7--MOSI

PE3--Touch_IT
PE4--SD_CS
PXX -- RST (低复位，正常高)

PE5--BL
PD 0--D2
PD 1--D3
PD 4--ILI9341_RD
PD 5--ILI9341_WR
PD 8--D13
PD 9--D14
PD 10--D15
PD 14--D0
PD 15--D1
PE 7--D4
PE 8--D5
PE 9--D6
PE 10--D7
PE 11--D8
PE 12--D9
PE 13--D10
PE 14--D11
PE 15--D12
PD 11--ILI9341_RS
PD 7--ILI9341_CS
*/


typedef union
{
	u8 Data_8[4800];   //  5行
	u16 Data_16[2400]; 
}Data_Buff;


//LCD重要参数集
typedef struct  
{										    
	u16 Width;			//LCD 宽度
	u16 Height;			//LCD 高度
	u16 ID;				//LCD ID
	u8  Dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	UpToGRAM;		//开始写gram指令
	u16  Set_X_CMD;			//设置x坐标指令
	u16  Set_Y_CMD;			//设置y坐标指令 
}ILI9341_Dev_t; 	  

//LCD参数
extern ILI9341_Dev_t ILI9341_Dev;	//管理LCD重要参数
//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//竖屏时的参数
#define ILI9341_WIDTH       240
#define ILI9341_HIGH        320 


//显示方向
#define Horizontal      0x01  //横向
#define Vertical 		0x02  //纵向


#define Y_Dir_Bit      		0x07  //Y写入方向控制位
#define X_Dir_Bit 			0x06  //X写入方向控制位
#define XY_Dir_ExchengeBit 	0x05  //XY写入方向交换控制位	


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
// #define	ILI9341_LED PBout(15)  		//LCD背光    		 PB15 	    
//LCD地址结构体
typedef struct
{
	vu16 ILI9341_REG;
	vu16 ILI9341_RAM;
} ILI9341_TypeDef;


typedef enum 
{
	Up_Down,
	Down_Up,
}ILI9341_UpDownMode_n;


typedef enum 
{
	Left_Right,
	Right_Left,
}ILI9341_LeftRightMode_n;

typedef enum 
{
	RGB,
	BGR,
}ILI9341_RGBMode_n;


typedef struct 
{
	ILI9341_UpDownMode_n 	Row_AddrMode; 			//行地址模式
	ILI9341_LeftRightMode_n Col_AddrMode;			//列地址模式
	u8 					RowCol_Exchenge;		//行列顺序交换
	ILI9341_UpDownMode_n 	Ver_ScanMode;			//垂直扫描模式
	ILI9341_RGBMode_n 		RGB_BGR_Mode;			//RGB BGR 模式
	ILI9341_LeftRightMode_n Hor_ScanMode;			//水平扫描模式
	u8 					Pixel_Bit;				//每像素位数
	u16 				ID;
}ILI9341_State_t;






//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E			    
#define ILI9341_BASE        ((u32)(0x60000000 | 0x0001FFFE))
#define LCD             ((ILI9341_TypeDef *) ILI9341_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向



/* Level 1 Commands */
#define ILI9341_NOP             	0x00   /* NOP */
#define ILI9341_SWRESET             0x01   /* Software Reset */
#define ILI9341_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define ILI9341_RDDST               0x09   /* Read Display Status */
#define ILI9341_RDDPM               0x0A   /* Read Display Power Mode */
#define ILI9341_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define ILI9341_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define ILI9341_RDDIM               0x0D   /* Read Display Image Format */
#define ILI9341_RDDSM               0x0E   /* Read Display Signal Mode */
#define ILI9341_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define ILI9341_SPLIN               0x10   /* Enter Sleep Mode */
#define ILI9341_SLEEP_OUT           0x11   /* Sleep out register */
#define ILI9341_PTLON               0x12   /* Partial Mode ON */
#define ILI9341_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define ILI9341_DINVOFF             0x20   /* Display Inversion OFF */
#define ILI9341_DINVON              0x21   /* Display Inversion ON */
#define ILI9341_GAMMA               0x26   /* Gamma register */
#define ILI9341_DISPLAY_OFF         0x28   /* Display off register */
#define ILI9341_DISPLAY_ON          0x29   /* Display on register */
#define ILI9341_COLUMN_ADDR         0x2A   /* Colomn address register */ 
#define ILI9341_PAGE_ADDR           0x2B   /* Page address register */ 
#define ILI9341_GRAM                0x2C   /* GRAM register */   
#define ILI9341_RGBSET              0x2D   /* Color SET */   
#define ILI9341_RAMRD               0x2E   /* Memory Read */   
#define ILI9341_PLTAR               0x30   /* Partial Area */   
#define ILI9341_VSCRDEF             0x33   /* Vertical Scrolling Definition */   
#define ILI9341_TEOFF               0x34   /* Tearing Effect Line OFF */   
#define ILI9341_TEON                0x35   /* Tearing Effect Line ON */   
#define ILI9341_MAC                 0x36   /* Memory Access Control register*/
#define ILI9341_VSCRSADD            0x37   /* Vertical Scrolling Start Address */   
#define ILI9341_IDMOFF              0x38   /* Idle Mode OFF */   
#define ILI9341_IDMON               0x39   /* Idle Mode ON */   
#define ILI9341_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define ILI9341_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */   
#define ILI9341_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */   
#define ILI9341_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */   
#define ILI9341_GET_SCANLINE        0x45   /* Get Scanline */   
#define ILI9341_WDB                 0x51   /* Write Brightness Display register */
#define ILI9341_RDDISBV             0x52   /* Read Display Brightness */   
#define ILI9341_WCD                 0x53   /* Write Control Display register*/
#define ILI9341_RDCTRLD             0x54   /* Read CTRL Display */   
#define ILI9341_WRCABC              0x55   /* Write Content Adaptive Brightness Control */   
#define ILI9341_RDCABC              0x56   /* Read Content Adaptive Brightness Control */   
#define ILI9341_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */   
#define ILI9341_READ_CABC           0x5F   /* Read CABC Minimum Brightness */   
#define ILI9341_READ_ID1            0xDA   /* Read ID1 */
#define ILI9341_READ_ID2            0xDB   /* Read ID2 */
#define ILI9341_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define ILI9341_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define ILI9341_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define ILI9341_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define ILI9341_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define ILI9341_INVTR               0xB4   /* Display Inversion Control */
#define ILI9341_BPC                 0xB5   /* Blanking Porch Control register */
#define ILI9341_DFC                 0xB6   /* Display Function Control register */
#define ILI9341_ETMOD               0xB7   /* Entry Mode Set */
#define ILI9341_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define ILI9341_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define ILI9341_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define ILI9341_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define ILI9341_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define ILI9341_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define ILI9341_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define ILI9341_POWER1              0xC0   /* Power Control 1 register */
#define ILI9341_POWER2              0xC1   /* Power Control 2 register */
#define ILI9341_VCOM1               0xC5   /* VCOM Control 1 register */
#define ILI9341_VCOM2               0xC7   /* VCOM Control 2 register */
#define ILI9341_NVMWR               0xD0   /* NV Memory Write */
#define ILI9341_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define ILI9341_RDNVM               0xD2   /* NV Memory Status Read */
#define ILI9341_READ_ID4            0xD3   /* Read ID4 */
#define ILI9341_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define ILI9341_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define ILI9341_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define ILI9341_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define ILI9341_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define ILI9341_POWERA               0xCB   /* Power control A register */
#define ILI9341_POWERB               0xCF   /* Power control B register */
#define ILI9341_DTCA                 0xE8   /* Driver timing control A */
#define ILI9341_DTCB                 0xEA   /* Driver timing control B */
#define ILI9341_POWER_SEQ            0xED   /* Power on sequence register */
#define ILI9341_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define ILI9341_PRC                  0xF7   /* Pump ratio control register */




//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)





//背光灯控制
#define ILI9341_BACK_LIGHT_ON    GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define ILI9341_BACK_LIGHT_OFF   GPIO_ResetBits(GPIOE,GPIO_Pin_5)



void ILI9341_IO_Init(void);
void ILI9341_Init(void);													   	//初始化
void ILI9341_DisplayOn(void);													//开显示
void ILI9341_DisplayOff(void);													//关显示
void ILI9341_Clear(u16 Color);	 												//清屏									//设置光标
void ILI9341_DrawPoint(u16 x,u16 y,u16 color);									//画点
u16  ILI9341_ReadPoint(u16 x,u16 y); 											//读点 
void ILI9341_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);				 			//画圆
void ILI9341_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);							//画线
void ILI9341_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);   				//画矩形
void ILI9341_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充单色
void ILI9341_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//填充指定颜色
void ILI9341_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//显示一个字符
void ILI9341_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//显示一个数字
void ILI9341_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//显示 数字
void ILI9341_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//显示一个字符串,12/16字体
void ILI9341_VerScroll(u16 XStart,u16 Xend,u16 High);



void ILI9341_Reset(void);
void ILI9341_GetID(void);
void ILI9341_ShowPicture(void);
void ILI9341_GetState(ILI9341_State_t *ILI9341_State);
void ILI9341_SetXY(u16 Xpos, u16 Ypos);
void ILI9341_SetXY_Area(u16 x_S, u16 y_S,u16 x_E,u16 y_E);
void ILI9341_WriteData_Dir(u8 Dir);
void ILI9341_Display_Dir(u8 Dir);
void ILI9341_Set_Window(u16 sx,u16 sy,u16 Width,u16 Height);


void DMATest(void);
void ILI9341_WriteCMD(vu16 regval);
void ILI9341_WriteData(vu16 data);
u16 ILI9341_ReadData(void);
void ILI9341_WriteCmdPara(vu16 ILI9341_Cmd,vu16 ILI9341_CmdValue);
u16 ILI9341_ReadID(u16 ILI9341_Cmd);
void ILI9341_WriteToRAM(void);
u16 ILI9341_BGR2RGB(u16 c);
void ILI9341_Delay(u8 i);
void ILI9341_Set_BackLight(u8 pwm);

void ILI9341_DMA_SetAddr(u32 StartAddr, u32 Point);
u32 ILI9341_DMA_GetCurrentAddr(void);
u8 ILI9341_DMA_GetTXComplateFlag(void);
void ILI9341_DMA_Start(void);
void ILI9341_DMA_Stop(void);

//LCD分辨率设置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		1		//水平脉宽
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		1		//垂直脉宽
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下几个参数，自动计算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
	 



