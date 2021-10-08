#include "IncludeFile.h"



u8 USART1_Buffer[1024];
u16 RX_Point,TX_Point;
extern QueueHandle_t Queue_Handle;

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
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=7;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	USART_ClearFlag(USART1,0x3ff);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
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




/*
输入参数为浮点数时，速度不宜过快，容易死机 一般在9600
*/
int fputc(int ch, FILE* stream)          
{		

	while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET))
	{
	}
	USART_SendData(USART1, (unsigned char) ch);	
	USART_ClearFlag(USART1,USART_FLAG_TC);
    return ch;
}



void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		USART1_Buffer[RX_Point] = USART_ReceiveData(USART1);
		RX_Point++;	
		if(RX_Point == 1024)
		{
			xQueueSendFromISR(Queue_Handle,USART1_Buffer,NULL);
			RX_Point = 0;
		}
//		RX_Point=RX_Point%DATA_BUFFER; //自动转圈
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}


	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}

}







void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
		USART1_Buffer[RX_Point] = USART_ReceiveData(USART2);
		RX_Point++;	
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}

	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_TC);
	}

}

















