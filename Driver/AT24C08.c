#include"IncludeFile.h"







void AT24C08_init(void)
{
	IIC_Init();
}
//��д����145Khz
u8 AT24C08Read_Byte(u8 dev_addr,u8 Data_addr)
{
	u8 DATA=0;
	Start_IIC();
	IIC_SenddByte(dev_addr|0X00);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr&0XFF);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte(dev_addr|0X01);	
    IIC_Wait_Ack_OK();
	DATA=IIC_GetByte();
	IIC_Send_Ack();
	Stop_IIC();

	return DATA;

}


void AT24C08Write_Byte(u8 dev_addr,u8 Data_addr,u8 data)
{
	Start_IIC();
	IIC_SenddByte(dev_addr);        
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr&0XFF);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(data);	
	IIC_Wait_Ack_OK();
	Stop_IIC();
	delay_us(2);  
}


// void AT24C08Read_NBytes(u8 dev_addr,u8 Data_addr,u16 length,u8 *data)
// {
// 	u16 i;
// 	for(i=0;i<length;i++)
// 	{
// 		data[i]=AT24C08Read_Byte(dev_addr,Data_addr+i);
// 	}
// }
	

u8  AT24C08Write_NBytes(u16 addr,u16 length,u8 *data)
{
	u8 i,k;
	u8 Pages;
	u16 PageNum,WR_Len=,Offset;
	B16_B08 MemAddr;	//���Ե�ַ

	if( addr >= AT24C08_PAGE_SIZE*AT24C08_PAGES)
	{
		return 0XFF;
	}
	MemAddr.B16 = addr;

	PageNum = addr/AT24C08_PAGE_SIZE;			//�õ�ҳ���
	Offset = addr - PageNum*AT24C08_PAGE_SIZE;	//����ҳ��ƫ��
	WR_Len = AT24C08_PAGE_SIZE - Offset;		//����һҳ�ڴ�ƫ��λ��Ҫд����ֽ���


	if( length/AT24C08_PAGE_SIZE == 0)
	{
		Pages = 1;
	}
	else
	{
		if( length%AT24C08_PAGE_SIZE == 0)
		{
			
		}
		else
		{
			
		}
	}




	if(length > AT24C08_PAGE_SIZE)
	{
		
		PageSize = AT24C08_PAGE_SIZE;

		if( length%AT24C08_PAGE_SIZE != 0)
		{
			Pages += 1;
		}
	}
	else
	{
		Pages = 1;
		PageSize = length;
	}


	for(i=0;i<Pages;i++)
	{

		Start_IIC();
		IIC_SenddByte(AT24C08_ADDRESS | MemAddr.B08[1] <<1);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(MemAddr.B08[0]);
		IIC_Wait_Ack_OK();

		for(k=0;k<WR_Len;k++)
		{
			IIC_SenddByte(data[len]);
			if(IIC_Wait_Ack_OK() == FALSE)
			{
				return FALSE;
			}
			len++;
		}
		Stop_IIC();
		delay_ms(2);//�ȴ�д�����

		MemAddr.B16 += AT24C08_PAGE_SIZE;

		if( i != Pages-1)//�ж��Ƿ����һҳ
		{
			PageSize = AT24C08_PAGE_SIZE;		  //�����������ҳд
		}
		else
		{
			PageSize = length/AT24C08_PAGE_SIZE;  //����д�벻��һҳ������
		}
	}
	return TRUE;

}




u8 AT24C08Read_NBytes(u16 addr,u16 length,u8 *data)
{
	u16 PageNum,offset,i;
	B16_B08 MemAddr;	//���Ե�ַ

	if( addr >= AT24C08_PAGE_SIZE*AT24C08_PAGES)
	{
		return 0XFF;
	}

	MemAddr.B16=addr;

	Start_IIC();
	IIC_SenddByte(AT24C08_ADDRESS |MemAddr.B08[1]<<1);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(MemAddr.B08[0]);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte(AT24C08_ADDRESS|0X01|MemAddr.B08[1]<<1);//��ȡ����
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


//void AT24C08Write_NBytes(u16 dev_addr,u16 length,u8 *data)
//{
//	
//	
//}





/*
	u8 i=0;
	Start_IIC();
	IIC_SenddByte(dev_addr|0x00);
	IIC_Wait_Ack_OK();
	IIC_SenddByte((Data_addr>>8)&0xFF);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(Data_addr&0xFF);
	IIC_Wait_Ack_OK();
	for(i=0;i<length;i++)
	{
		IIC_SenddByte(*data);
		if(IIC_Wait_Ack_OK()==1)
		{
			Stop_IIC();
			return;
		}
		data++;
	}
 	Stop_IIC();
	delay_ms(2);

*/












