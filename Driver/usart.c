#include "IncludeFile.h"



USART_Data_t USART1_Data;
USART_Data_t USART2_Data;



//使用中断方式发送数据时，应先将数据发送到寄存器中，然后再开启中断，发送完毕后应在中断函数里关闭发送中断！！！！！！！
// sendBuffer(Data);
// USART_IT(enbale);
//IDLE空闲中断指对接收有效，对发送无效


/*
	USART1_MODE_A : PA9-TX1 
	         		PA10-RX1

	USART1_MODE_B : PB6-TX1 
	        		PB7-RX1	
*/
void USART1_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity)
{
	
	GPIO_InitTypeDef USART_GPIO_Init;
	USART_InitTypeDef USART1_Initstruc;
	NVIC_InitTypeDef  NVIC_Initstr;


	if(DataLength==USART_DATA_8bit )
	{
		if(Parity!=USART_PARTYT_NO)
		{
			Parity=USART_PARTYT_NO;
            //8位数据必须无校验，9位数据任意校验
		}
	}

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	#ifdef USART1_MODE_A
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		USART_GPIO_Init.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	#elif defined USART1_MODE_B
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		USART_GPIO_Init.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	#endif

		USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                           
		USART_GPIO_Init.GPIO_PuPd=GPIO_PuPd_UP;
		USART_GPIO_Init.GPIO_Speed=GPIO_Speed_50MHz;

	#ifdef USART1_MODE_A
		GPIO_Init(GPIOA,&USART_GPIO_Init);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	#elif defined USART1_MODE_B
		GPIO_Init(GPIOB,&USART_GPIO_Init);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
	#endif	


	USART1_Initstruc.USART_BaudRate=bode;                                  
	USART1_Initstruc.USART_WordLength=DataLength;
	USART1_Initstruc.USART_StopBits=StopBit;
	USART1_Initstruc.USART_Parity=Parity;
	USART1_Initstruc.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART1_Initstruc.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART1_Initstruc);
	
	NVIC_Initstr.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=5;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	USART_ClearFlag(USART1,0x3ff);

	USART_ITConfig(USART1,USART_IT_RXNE ,ENABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE);//不支持或（ | ）操作

	USART_Cmd(USART1,ENABLE);	
}


/*
	USART2_MODE_A : PD5-TX2 
	         		PD6-RX2

	USART2_MODE_B : PA2-TX2 
	        		PA3-RX2	
*/
void USART2_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity)
{
		GPIO_InitTypeDef USART_GPIO_Init;
		USART_InitTypeDef USART2_Initstruc;
		NVIC_InitTypeDef  NVIC_Initstr;

	if(DataLength==USART_DATA_8bit )
	{
		if(Parity!=USART_PARTYT_NO)
		{
			Parity=USART_PARTYT_NO;
			//return;                   //8位数据必须无校验，9位数据任意校验
		}
			
	}

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	#ifdef USART2_MODE_A
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		USART_GPIO_Init.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	#elif defined USART2_MODE_B
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		USART_GPIO_Init.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	#endif

		USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                           
		USART_GPIO_Init.GPIO_PuPd=GPIO_PuPd_UP;
		USART_GPIO_Init.GPIO_Speed=GPIO_Speed_50MHz;

	#ifdef USART2_MODE_A
		GPIO_Init(GPIOD,&USART_GPIO_Init);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	#elif defined USART2_MODE_B
		GPIO_Init(GPIOA,&USART_GPIO_Init);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	#endif	
	

	USART2_Initstruc.USART_BaudRate=bode;                                  
	USART2_Initstruc.USART_WordLength=DataLength;
	USART2_Initstruc.USART_StopBits=StopBit;
	USART2_Initstruc.USART_Parity=Parity;
	USART2_Initstruc.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART2_Initstruc.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART2,&USART2_Initstruc);
	
	NVIC_Initstr.NVIC_IRQChannel=USART2_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=6;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	USART_ClearFlag(USART2,0x3ff);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);	
}





int fputc(int ch, FILE* stream)          
{		
	u8 i=0;
	while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET) && ( i < 10))
	{
		Delay_us(2);
	}
	USART_SendData(USART1, (unsigned char) ch);	
	USART_ClearFlag(USART1,USART_FLAG_TC);
    return ch;
}


void USART1_IRQHandler()
{
	USARTx_ITHandle(USART1,&USART1_Data);
}

void USART2_IRQHandler()
{
	USARTx_ITHandle(USART2,&USART2_Data);
}

void USARTx_ITHandle(USART_TypeDef* USARTx,USART_Data_t *USART_Data)
{
	//接收中断
	if(USART_GetITStatus(USARTx,USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USARTx,USART_IT_RXNE);
		USART_Data->RX_Data[USART_Data->RX_Pointer] = USART_ReceiveData(USARTx);
		USART_Data->RX_Pointer++;
		USART_Data->RX_Pointer %= BUFFER_SIZE;
	}

	//发送完成中断
	if(USART_GetITStatus(USARTx,USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USARTx,USART_IT_TC);
		USART_SendData(USARTx,USART_Data->TX_Data[USART_Data->TX_Pointer]);
		USART_Data->TX_Pointer++;
		USART_Data->TX_Pointer %= BUFFER_SIZE;

		if( USART_Data->TX_Pointer >= USART_Data->TX_Length)
		{
			USART_ITConfig(USARTx,USART_IT_TC,DISABLE);
		}

	}

	//接收空闲中断
	if(USART_GetITStatus(USARTx,USART_IT_IDLE) != RESET)
	{
		USART_ClearITPendingBit(USARTx,USART_IT_IDLE);
		USART_Data->RX_Pointer = 0;
	}
}

// 启动中断发送
u8 USART_ITSendData(USART_TypeDef* USARTx,USART_Data_t *USART_Data,u8 *Data,u16 Length)
{
	if(Length > BUFFER_SIZE)
	{
		return FALSE;
	}

	// if( USART_Data->TX_Pointer != 0)//正在发送数据
	// {
	// 	return BUSY;
	// }

	memcpy(USART_Data->TX_Data,Data,Length);
	USART_Data->TX_Pointer = 0;
	USART_Data->TX_Length = Length;
	USART_ITConfig(USARTx,USART_IT_TC,ENABLE);
	return TRUE;
}

//非中断方式
// USART_TypeDef* USARTx
// USART_Data_t *USART_Data 
// u8 *Data
// u16  Length
u8 USART_PollingSendData(USART_TypeDef* USARTx,USART_Data_t *USART_Data,u8 *Data,u16 Length)
{
	u16 i;
	for ( i = 0; i < Length; i++)
	{
		USART_ClearFlag(USARTx,USART_FLAG_TC);
		USART_SendData(USARTx, *(Data+i));
		while ((USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET));
	}
	return TRUE;
}


u8 USART_ReceiceData(USART_TypeDef* USARTx,USART_Data_t *USART_Data,u8 *Data,u16 Length)
{
	if(Length > BUFFER_SIZE)
	{
		return FALSE;
	}

	if( USART_Data->RX_Pointer != 0)//正在接收数据
	{
		return BUSY;
	}



	return TRUE;



}



















