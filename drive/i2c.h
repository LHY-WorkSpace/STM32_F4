#ifndef  _I2C_H_
#define  _I2C_H_

#define uchar unsigned char
#define uint unsigned int 
 
#define PORT_AHB                  RCC_AHB1Periph_GPIOB                                      //IO总线
#define PORT_GROUP                GPIOB                                                     //IO端口组
#define IIC_SCL                   GPIO_Pin_6                                       
#define IIC_SDA                   GPIO_Pin_7
#define IIC_SCL_LOW  			GPIO_ResetBits(PORT_GROUP,IIC_SCL)
#define IIC_SCL_HIGH  		 	GPIO_SetBits(PORT_GROUP,IIC_SCL)
#define IIC_SDA_LOW  			GPIO_ResetBits(PORT_GROUP,IIC_SDA)
#define IIC_SDA_HIGH 			GPIO_SetBits(PORT_GROUP,IIC_SDA)



static void Pin_out2in(void);
static void Pin_in2out(void);

static void Stop_IIC(void);
static void Start_IIC(void);
static void IIC_SenddByte(uchar data);
static uchar IIC_GetByte(void);
static void IIC_Send_NAck(void);
static void IIC_Send_Ack(void);
static uchar IIC_Wait_Ack_OK(void);

void IIC_Init(void);
void IIC_Write_Byte(uchar Dev_addr,uchar Data_addr,uchar data);
uchar IIC_Read_Byte(uchar Dev_addr,uchar Data_addr);
// void IIC_Write_NBytes(uchar Dev_addr,uchar Data_addr,uchar length,uchar *data);
// void IIC_Read_NBytes(uchar Dev_addr,uchar Data_addr,uchar length,uchar *data);









#endif
