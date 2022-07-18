#include "IncludeFile.h"


//�û��Զ���CRC�ؼ���
 #define USER_KEY (0x12345678)


void SystemDown()
{
	//char Data[] ="STM32-USART-Test!!!\r\n";
	while(1)
	{		
		LED1_ON;
		Delay_ms(500);
		LED1_OFF;
		Delay_ms(500);
	}
}

//************************// 
//  ��������: ��λ
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//
//************************//  
void SW_Reset()
{
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}

//************************// 
//  ��������: ����CRC32
//  
//  ����: ���ݵ�ַ�����ݳ���
//  
//  ����ֵ: CRCֵ
//  
//  ˵��: ��
//
//************************//  
u32 CRC32_GetValue(u32 *pBuffer, u32 BufferLength)
{
	u32 index = 0;

	CRC->CR = CRC_CR_RESET;//��λCRC

	for(index = 0; index < BufferLength; index++)
	{
		CRC->DR = pBuffer[index];
	}

	CRC->DR = (u32)USER_KEY;
	
	return (CRC->DR);
}

//************************// 
//  ��������: ��ȡROM��ָ�������Sumֵ
//  
//  ����: ��ʼ��ַ��������ַ
//  
//  ����ֵ: ��
//  
//  ˵��: ��ַ�����4�ֽڶ��룬��ǿ�����¶��룬�����2λ
//
//************************//  
u32 GetROMCheckSum(u32 StartAddr,u32 EndtAddr)
{
	u32 Temp = 0,i;

	if( (StartAddr < ROM_BASE_ADDR) || (EndtAddr > ROM_END_ADDR))
	{
		return 0;
	}
	else
	{
		//��ַȡ4��������
		StartAddr &= 0xFFFFFFFC;
		EndtAddr  &= 0xFFFFFFFC;
	}
	
	while ( (StartAddr + i ) <= EndtAddr)
	{
		Temp += *((u32 *)(StartAddr + i));
		i += 4;
	}
	
	return Temp;
}


u8 Power_GetState()
{



	return 0;
}





























