#include"IncludeFile.h"



//************************// 
//  ��������: AS5600_ IO ��ʼ������
//  
//  ����: ��
//  
//  ����ֵ: TRUE:�ɹ�  
//          FALSE:ʧ��
//          0xFF:��ַ����Χ
//			
//  ˵��: 
//
//************************//  
void AS5600_Init(void)
{
	IIC_Init();
}

//************************// 
//  ��������: AS5600_ ����д�뺯��
//  
//  ����: �����ַ�����ȣ�����ָ��
//  
//  ����ֵ: TRUE:�ɹ�  
//          FALSE:ʧ��
//          0xFF:��ַ����Χ
//			
//  ˵��: 
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
//  ��������: AS5600_ ���ݶ�ȡ����
//  
//  ����: �����ַ�����ȣ�����ָ��
//  
//  ����ֵ: TRUE:�ɹ�  
//          FALSE:ʧ��
//          0xFF:��ַ����Χ
//			
//  ˵��: 
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
	IIC_SenddByte( (AS5600_ADDRESS << 1) | 0X01 );//��
    IIC_Wait_Ack_OK();

	for(i=0;i<length;i++)
	{
		data[i]=IIC_GetByte();
		if( i == length-1)
		{
			IIC_Send_NAck();//���һ���ֽڷ���N_ACK
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










