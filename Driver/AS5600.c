#include"IncludeFile.h"



//************************// 
//  功能描述: AS5600_ IO 初始化函数
//  
//  参数: 无
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
void AS5600_Init(void)
{
	IIC_Init();
}

//************************// 
//  功能描述: AS5600_ 数据写入函数
//  
//  参数: 物理地址，长度，数据指针
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
u8  AS5600_WriteData(u8 addr,u8 length,u8 *data)
{
	u8 i;
	Start_IIC();
	IIC_SenddByte( AS5600_ADDRESS << 1 );
    IIC_Wait_Ack_OK();
	IIC_SenddByte(addr);
	IIC_Wait_Ack_OK();
	for(i=0;i<length;i++)
	{
		IIC_SenddByte(data[i]);
		if(IIC_Wait_Ack_OK() == FALSE)
		{
			return FALSE;
		}
	}
	Stop_IIC();
}



//************************// 
//  功能描述: AS5600_ 数据读取函数
//  
//  参数: 物理地址，长度，数据指针
//  
//  返回值: TRUE:成功  
//          FALSE:失败
//          0xFF:地址超范围
//			
//  说明: 
//
//************************//  
void AS5600_ReadData(u8 addr,u8 length,u8 *data)
{
	u8 i;

	Start_IIC();
	IIC_SenddByte( AS5600_ADDRESS << 1 );
    IIC_Wait_Ack_OK();
	IIC_SenddByte(addr);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte( (AS5600_ADDRESS << 1) | 0X01 );//读
    IIC_Wait_Ack_OK();

	for(i=0;i<length;i++)
	{
		data[i]=IIC_GetByte();
		if( i == length-1)
		{
			IIC_Send_NAck();//最后一个字节发送N_ACK
		}
		else
		{
			IIC_Send_Ack();
		}
	}
	Stop_IIC();

}




void AS5600_Test()
{

	B16_B08 Angle;
	u16 AngleTmp=0;
	
	memset(Angle.B08,0,sizeof(B16_B08));
	AS5600_ReadData(RAW_ANGLE_L_REG,1,&Angle.B08[0]);
	Delay_ms(5);
	AS5600_ReadData(RAW_ANGLE_H_REG,1,&Angle.B08[1]);
	Delay_ms(5);
	AngleTmp = Angle.B16*360/4096;
	printf("Angle_ADC:%d    Angle:%d\r\n",Angle.B16,AngleTmp);
	Delay_ms(10);
}










