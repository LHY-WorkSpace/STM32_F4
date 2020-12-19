#ifndef  OLED_H
#define  OLED_H


#define uchar unsigned char
#define uint unsigned int 
	
#define  OLED_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //��λ��
#define  OLED_RST_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_14)	            //��λ��
#define  OLED_DATA   GPIO_SetBits(GPIOB,GPIO_Pin_12)	            //����
#define  OLED_ORDER   GPIO_ResetBits(GPIOB,GPIO_Pin_12)	           //����

#define  Horizontal_Mode    0x00            
#define  Page_Mode          0x02
#define	 Vertical_Mode      0x01




#define  Vertical_reversal_Disable        0xc8
#define	 Vertical_reversal_Enble          0xc0

void oled_init(void);
void oled_senddata(uchar Tdata);
void oled_sendorder(uchar Tdata);
void Vertical_reversal(uint state);
void display_position(uchar xposition,uchar y,uchar length);
void display_num(uchar i);
void display_char(char alphabet);
void windows_open(uint);
void tempure_unit(void);							//�¶ȵ�λ
void clear_screen(void);
void show_All(void);
void display_str_and_speed(char *word,uint speed);
void oled_spi_configinit(void);
void power_on_check_display(void);
void set_OLED_frequence_div(uchar fre,uchar div);         //value of fre or div:0~f
void set_contrast(uchar value);
void draw_point(uchar x,uchar y);
void  show_picture(uchar x_start,uchar y_start,uchar x_length,uchar y_length,uchar* data);      //���ص�����x_start ��y_start ����x_length,�߶�y_length ͼ������data



#endif






















