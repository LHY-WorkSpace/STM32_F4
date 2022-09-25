#ifndef USART_H
#define USART_H



#define  USART_DATA_8bit     USART_WordLength_8b
#define  USART_DATA_9bit     USART_WordLength_9b


#define  USART_STOP_1bit      USART_StopBits_1
#define  USART_STOP_0_5bit    USART_StopBits_0_5
#define  USART_STOP_2bit      USART_StopBits_2
#define  USART_STOP_1_5bit    USART_StopBits_1_5


#define  USART_PARTYT_NO     USART_Parity_No
#define  USART_PARTYT_ODD    USART_Parity_Odd
#define  USART_PARTYT_EVEN   USART_Parity_Even


#define USART1_MODE_A
#define USART2_MODE_B   



#define BUFFER_SIZE      (1024)

typedef struct 
{
    u16 RX_Pointer;//已接收数据指针
    u16 TX_Pointer;//已发送数据指针
    u16 RX_Length;//已接收的数据长度
    u16 TX_Length;//要发送的数据长度
    u8 RX_Data[BUFFER_SIZE]; 
    u8 TX_Data[BUFFER_SIZE];
}USART_Data_t;


extern USART_Data_t USART1_Data;
extern USART_Data_t USART2_Data;

void USART1_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);   
void USART2_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);
void USARTx_ITHandle(USART_TypeDef* USARTx,USART_Data_t *USART_Data);
u8 USART_ITSendData(USART_TypeDef* USARTx,USART_Data_t *USART_Data,u16 Length,u8 *Data);
u8 USART_GetData(USART_Data_t *USART_Data,u16 Buffsize,u8 *Data,u16 *Length);
u8 USART_PollingSendData(USART_TypeDef* USARTx,USART_Data_t *USART_Data,u8 *Data,u16 Length);
int fputc(int ch, FILE* stream);
u8 Enocde_Data(void);

#endif







