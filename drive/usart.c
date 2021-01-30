#include "stm32f4xx.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"

//#define u8unsigned char
//#define u32 unsigned int 


void usart_init(unsigned int bode)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	
	
	GPIO_InitTypeDef USART_GPIO_Init;
	USART_InitTypeDef USART1_Initstruc;
	NVIC_InitTypeDef  NVIC_Initstr;
	
	
	USART_GPIO_Init.GPIO_Pin=GPIO_Pin_9;										//	PA9-TX1-------------RX_USB
	USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                           
//	USART_GPIO_Init.GPIO_Speed=GPIO_Speed_50MHz;
//	USART_GPIO_Init.GPIO_OType=GPIO_OType_PP;
	USART_GPIO_Init.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&USART_GPIO_Init);
	
	USART_GPIO_Init.GPIO_Pin=GPIO_Pin_10;										//	PA10-RX1------------TX_USB
	USART_GPIO_Init.GPIO_Mode=GPIO_Mode_AF;                            
	
	GPIO_Init(GPIOA,&USART_GPIO_Init);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);


	USART1_Initstruc.USART_BaudRate=bode;                                   //AP
	USART1_Initstruc.USART_WordLength=USART_WordLength_8b;
	USART1_Initstruc.USART_StopBits=USART_StopBits_1;
	USART1_Initstruc.USART_Parity=USART_Parity_No;
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
		//while ((USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=0));
    //USART_SendData(USART1, (uint8_t)ch);
	USART_ClearFlag(USART1,USART_FLAG_TC);
    return ch;
}




//void send_data(u32 data)
//{
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET));
//USART_SendData(USART1,data);
//while ((USART_GetFlagStatus(USART1,USART_FLAG_TC)!=0));	
//}




//void USART1_IRQHandler()
//{

//	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
//	{

//	temp=USART_ReceiveData(USART1);

//	}
//}



// void USART1_IRQHandler()
// {
// 	static u32 i=0;

// 	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
// 	{
// 	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
// //  OLED[i]=USART_ReceiveData(USART1);
// 	i++;		
// 	}

// 	if(i==1024)
// 	{
// 		//OLED_FULL=1;
// 		i=0;

// 	}


// }
