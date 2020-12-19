#ifndef  _I2C_H_
#define  _I2C_H_



#define uchar unsigned char
#define uint unsigned int 




#define IIC_SOFTWARE              1                                                         //是否启用软件/硬件IIC选择
 


#define PORT_AHB                  RCC_AHB1Periph_GPIOB                                      //IO总线
#define PORT_GROUP                GPIOB                                                     //IO端口组
#define IIC_SCL                   GPIO_Pin_6                                       
#define IIC_SDA                   GPIO_Pin_7
#define IIC_SCL_LOW  			 				GPIO_ResetBits(PORT_GROUP,IIC_SCL)
#define IIC_SCL_HIGH  		 				GPIO_SetBits(PORT_GROUP,IIC_SCL)
#define IIC_SDA_LOW  			 				GPIO_ResetBits(PORT_GROUP,IIC_SDA)
#define IIC_SDA_HIGH 			 				GPIO_SetBits(PORT_GROUP,IIC_SDA)




static void Pin_out2in(void);
static void Pin_in2out(void);

void IIC_Init(void);
void Stop_IIC(void);
void Start_IIC(void);
void IIC_SenddByte(uchar data);
uchar IIC_GetByte(void);
void IIC_Send_NAck(void);
void IIC_Send_Ack(void);
uchar IIC_Wait_Ack_OK(void);
void IIC_Write_Byte(uchar ADDR,uchar REG,uchar data);
uchar IIC_Read_Byte(uchar ADDR,uchar REG);
void IIC_Write_NByte(uchar dev_addr,uchar reg,uchar length,uchar *data);
void IIC_Read_NByte(uchar dev_addr,uchar reg,uchar length,uchar *data);









#endif
