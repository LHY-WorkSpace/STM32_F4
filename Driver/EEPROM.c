#include"IncludeFile.h"



//************************// 
//  ��������: EEPROM IO ��ʼ������
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
void EEPROM_Init(void)
{
	IIC_Init();
}

//************************// 
//  ��������: EEPROM ����д�뺯��
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
u8  EEPROMWriteData(u16 addr,u16 length,u8 *data)
{
	u8 k,i;
	u16 PageNum,WR_Len,Offset,LenCount;
	B16_B08 MemAddr;	//���Ե�ַ

	if( addr >= EEPROM_PAGE_SIZE*EEPROM_PAGES)
	{
		return 0XFF;
	}
	
	MemAddr.B16 = addr;

	PageNum = addr/EEPROM_PAGE_SIZE;			//�õ�ҳ���
	Offset = addr - PageNum*EEPROM_PAGE_SIZE;	//����ҳ��ƫ��
	WR_Len = EEPROM_PAGE_SIZE - Offset;		//����һҳ�ڴ�ƫ��λ��Ҫд����ֽ���
	LenCount = 0;

	if( WR_Len >= length )	//����С�ڵ���δ��ҳʣ���ֽ�������ʵ�ʳ���д��
	{
		WR_Len = length;
	}

	do
	{
		Start_IIC();
		IIC_SenddByte(EEPROM_ADDRESS | MemAddr.B08[1] <<1);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(MemAddr.B08[0]);
		IIC_Wait_Ack_OK();

		for(k=0;k<WR_Len;k++)
		{
			IIC_SenddByte(data[LenCount]);
			if(IIC_Wait_Ack_OK() == FALSE)
			{
				return FALSE;
			}
			LenCount++;
		}
		Stop_IIC();
		//�˴�������ʱ���ȴ�ҳд����ɣ��ֲ����5ms
		for ( i = 0; i < 5; i++)
		{
			IIC_Delay(1000);
		}
		
		MemAddr.B16 += WR_Len;

		if( (length - LenCount) >= EEPROM_PAGE_SIZE)
		{
			WR_Len = EEPROM_PAGE_SIZE;
		}
		else
		{
			WR_Len = length - LenCount;
		}

	}while(LenCount != length);

	return TRUE;
}



//************************// 
//  ��������: EEPROM ���ݶ�ȡ����
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
u8 EEPROMReadData(u16 addr,u16 length,u8 *data)
{
	u16 i;
	B16_B08 MemAddr;	//���Ե�ַ

	if( addr >= EEPROM_PAGE_SIZE*EEPROM_PAGES)
	{
		return 0XFF;
	}

	MemAddr.B16=addr;

	Start_IIC();
	IIC_SenddByte(EEPROM_ADDRESS |MemAddr.B08[1]<<1);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(MemAddr.B08[0]);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte(EEPROM_ADDRESS|0X01|MemAddr.B08[1]<<1);//��ȡ����
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
	return TRUE;
}












