#include "IncludeFile.h"


//用户自定义CRC关键字
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
//  功能描述: 软复位
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 无
//
//************************//  
void SW_Reset()
{
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}

//************************// 
//  功能描述: 计算CRC32
//  
//  参数: 数据地址，数据长度
//  
//  返回值: CRC值
//  
//  说明: 无
//
//************************//  
u32 CRC32_GetValue(u32 *pBuffer, u32 BufferLength)
{
	u32 index = 0;

	CRC->CR = CRC_CR_RESET;//复位CRC

	for(index = 0; index < BufferLength; index++)
	{
		CRC->DR = pBuffer[index];
	}

	CRC->DR = (u32)USER_KEY;
	
	return (CRC->DR);
}

//************************// 
//  功能描述: 获取ROM中指定区域的Sum值
//  
//  参数: 起始地址，结束地址
//  
//  返回值: 无
//  
//  说明: 地址如果非4字节对齐，则强制向下对齐，舍掉低2位
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
		//地址取4的整数倍
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





























