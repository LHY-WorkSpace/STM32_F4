#include"IncludeFile.h"



u8 USART1_Buffer[200];
u8 RX_Point,TX_Point;


//	PA9-TX1
//	PA10-RX1
void USART1_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	
	GPIO_InitTypeDef USART_GPIO_Init;
	USART_InitTypeDef USART1_Initstruc;
	NVIC_InitTypeDef  NVIC_Initstr;
	
	
	USART_GPIO_Init.GPIO_Pin=GPIO_Pin_9;										
	USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                           
	USART_GPIO_Init.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&USART_GPIO_Init);
	
	USART_GPIO_Init.GPIO_Pin=GPIO_Pin_10;										
	USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                            
	
	GPIO_Init(GPIOA,&USART_GPIO_Init);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);


	USART1_Initstruc.USART_BaudRate=bode;                                  
	USART1_Initstruc.USART_WordLength=DataLength;
	USART1_Initstruc.USART_StopBits=StopBit;
	USART1_Initstruc.USART_Parity=Parity;
	USART1_Initstruc.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART1_Initstruc.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&USART1_Initstruc);
	
	
	NVIC_Initstr.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;

	
	NVIC_Init(&NVIC_Initstr);

	USART_ClearFlag(USART1,0x3ff);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART1,ENABLE);	



	

}

/*

输入参数为浮点数时，速度不宜过快，容易死机 一般在9600

*/

int fputc(int ch, FILE* stream)          
{			
	while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET));
    USART_SendData(USART1, (unsigned char) ch);
	USART_ClearFlag(USART1,USART_FLAG_TC);
    return ch;
}




//void send_data(u32 data)
//{
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET));
//USART_SendData(USART1,data);
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)!=0));	
//}






void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		if( RX_Point > 199 )
			RX_Point = 0;	
		USART1_Buffer[RX_Point] = USART_ReceiveData(USART1);
		RX_Point++;		
	}



USART_ClearITPendingBit(USART1,USART_IT_RXNE|USART_IT_TC);
}
