#ifndef __LCD_H
#define __LCD_H	
#include "IncludeFile.h"
#include "stdlib.h" 




/*
����
PA4--Touch_CS
PA5--SPI_CLK
PA6--MISO
PA7--MOSI

PE3--Touch_IT
PE4--SD_CS
PXX -- RST (�͸�λ��������)

PE5--BL
PD 0--D2
PD 1--D3
PD 4--LCD_RD
PD 5--LCD_WR
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
PD 11--LCD_RS
PD 7--LCD_CS
*/


typedef union
{
	u8 Data_8[4800];   //  5��
	u16 Data_16[2400]; 
}Data_Buff;


//LCD��Ҫ������
typedef struct  
{										    
	u16 Width;			//LCD ���
	u16 Height;			//LCD �߶�
	u16 ID;				//LCD ID
	u8  Dir;			//���������������ƣ�0��������1��������	
	u16	UpToGRAM;		//��ʼдgramָ��
	u16  Set_X_CMD;			//����x����ָ��
	u16  Set_Y_CMD;			//����y����ָ�� 
}LCD_Dev_t; 	  

//LCD����
extern LCD_Dev_t LCD_Dev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//����ʱ�Ĳ���
#define LCD_WIDTH       240
#define LCD_HIGH        320 


//��ʾ����
#define Horizontal      0x01  //����
#define Vertical 		0x02  //����


#define Y_Dir_Bit      		0x07  //Yд�뷽�����λ
#define X_Dir_Bit 			0x06  //Xд�뷽�����λ
#define XY_Dir_ExchengeBit 	0x05  //XYд�뷽�򽻻�����λ	


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
// #define	LCD_LED PBout(15)  		//LCD����    		 PB15 	    
//LCD��ַ�ṹ��
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;


typedef enum 
{
	Up_Down,
	Down_Up,
}LCD_UpDownMode_n;


typedef enum 
{
	Left_Right,
	Right_Left,
}LCD_LeftRightMode_n;

typedef enum 
{
	RGB,
	BGR,
}LCD_RGBMode_n;


typedef struct 
{
	LCD_UpDownMode_n 	Row_AddrMode; 			//�е�ַģʽ
	LCD_LeftRightMode_n Col_AddrMode;			//�е�ַģʽ
	u8 					RowCol_Exchenge;		//����˳�򽻻�
	LCD_UpDownMode_n 	Ver_ScanMode;			//��ֱɨ��ģʽ
	LCD_RGBMode_n 		RGB_BGR_Mode;			//RGB BGR ģʽ
	LCD_LeftRightMode_n Hor_ScanMode;			//ˮƽɨ��ģʽ
	u8 					Pixel_Bit;				//ÿ����λ��
	u16 				ID;
}LCD_State_t;






//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A6��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x60000000 | 0x0001FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��



/* Level 1 Commands */
#define LCD_NOP             	0x00   /* NOP */
#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */ 
#define LCD_PAGE_ADDR           0x2B   /* Page address register */ 
#define LCD_GRAM                0x2C   /* GRAM register */   
#define LCD_RGBSET              0x2D   /* Color SET */   
#define LCD_RAMRD               0x2E   /* Memory Read */   
#define LCD_PLTAR               0x30   /* Partial Area */   
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */   
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */   
#define LCD_TEON                0x35   /* Tearing Effect Line ON */   
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */   
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */   
#define LCD_IDMON               0x39   /* Idle Mode ON */   
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */   
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */   
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */   
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */   
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */   
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */   
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */   
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */   
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */   
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */   
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */




//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)





//����ƿ���
#define LCD_BACK_LIGHT_ON    GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define LCD_BACK_LIGHT_OFF   GPIO_ResetBits(GPIOE,GPIO_Pin_5)



void LCD_IO_Init(void);
void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����									//���ù��
void LCD_DrawPoint(u16 x,u16 y,u16 color);									//����
u16  LCD_ReadPoint(u16 x,u16 y); 											//���� 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);				 			//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//��ʾһ���ַ���,12/16����
void LCD_VerScroll(u16 XStart,u16 Xend,u16 High);



void LCD_Reset(void);
void LCD_GetID(void);
void LCD_ShowPicture(void);
void LCD_GetState(LCD_State_t *LCD_State);
void LCD_SetXY(u16 Xpos, u16 Ypos);
void LCD_SetXY_Area(u16 x_S, u16 y_S,u16 x_E,u16 y_E);
void LCD_WriteData_Dir(u8 Dir);
void LCD_Display_Dir(u8 Dir);
void LCD_Set_Window(u16 sx,u16 sy,u16 Width,u16 Height);


void DMATest(void);
void LCD_WriteCMD(vu16 regval);
void LCD_WriteData(vu16 data);
u16 LCD_ReadData(void);
void LCD_WriteCmdPara(vu16 LCD_Cmd,vu16 LCD_CmdValue);
u16 LCD_ReadID(u16 LCD_Cmd);
void LCD_WriteToRAM(void);
u16 LCD_BGR2RGB(u16 c);
void LCD_Delay(u8 i);
void LCD_Set_BackLight(u8 pwm);

void LCD_DMA_SetAddr(u32 StartAddr, u32 Point);
u32 LCD_DMA_GetCurrentAddr(void);
u8 LCD_DMA_GetTXComplateFlag(void);
void LCD_DMA_Start(void);
void LCD_DMA_Stop(void);

//LCD�ֱ�������
#define SSD_HOR_RESOLUTION		800		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		480		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
	 



