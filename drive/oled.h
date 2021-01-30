#ifndef  OLED_H
#define  OLED_H


#define u8 unsigned char
#define u32 unsigned int 
	
#define  OLED_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //复位关
#define  OLED_RST_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_14)	            //复位开
#define  OLED_DATA   GPIO_SetBits(GPIOB,GPIO_Pin_12)	            //数据
#define  OLED_ORDER   GPIO_ResetBits(GPIOB,GPIO_Pin_12)	           //命令

#define  Horizontal_Mode    0x00            
#define  Page_Mode          0x02
#define	 Vertical_Mode      0x01




#define  Vertical_reversal_Disable        0xc8
#define	 Vertical_reversal_Enble          0xc0

void oled_init(void);
void oled_senddata(u8 Tdata);
void oled_sendorder(u8 Tdata);
void Vertical_reversal(u32 state);
void display_position(u8 xposition,u8 y,u8 length);
void display_num(u8 i);
void display_char(char alphabet);
void windows_open(u32);
void tempure_unit(void);							//温度单位
void clear_screen(void);
void show_All(void);
void display_str_and_speed(char *word,u32 speed);
void oled_spi_configinit(void);
void power_on_check_display(void);
void set_OLED_frequence_div(u8 fre,u8 div);         //value of fre or div:0~f
void set_contrast(u8 value);
void draw_point(u8 x,u8 y);
void  show_picture(u8 x_start,u8 y_start,u8 x_length,u8 y_length,u8* data);      //像素的坐标x_start ，y_start 长度x_length,高度y_length 图像数组data



#endif






















