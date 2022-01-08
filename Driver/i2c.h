#ifndef  _I2C_H_
#define  _I2C_H_


 
#define PORT_AHB                  RCC_AHB1Periph_GPIOB                                      //IO总线
#define PORT_GROUP                GPIOB                                                     //IO端口组
#define IIC_SCL                   GPIO_Pin_6                                       
#define IIC_SDA                   GPIO_Pin_7
#define IIC_SCL_LOW  			GPIO_ResetBits(PORT_GROUP,IIC_SCL)
#define IIC_SCL_HIGH  		 	GPIO_SetBits(PORT_GROUP,IIC_SCL)
#define IIC_SDA_LOW  			GPIO_ResetBits(PORT_GROUP,IIC_SDA)
#define IIC_SDA_HIGH 			GPIO_SetBits(PORT_GROUP,IIC_SDA)
#define CPU_NOP                 0x11
#define TIMER                   0x22


//IIC延时类型：定时器/CPU_NOP
#define DELAY_TYPE    CPU_NOP


static void Pin_out2in(void);
static void Pin_in2out(void);


void Stop_IIC(void);
void Start_IIC(void);
void IIC_Send_NAck(void);
void IIC_Send_Ack(void);
u8 IIC_Wait_Ack_OK(void);


void IIC_Init(void);
void IIC_SenddByte(u8 data);
u8 IIC_GetByte(void);


#endif
