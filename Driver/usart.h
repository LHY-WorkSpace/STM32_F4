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



#define BUFFER_SIZE      (512)

typedef struct 
{
    u16 RX_Pointer;//已接收数据指针
    u16 TX_Pointer;//已发送数据指针
    u16 RX_ReadLength; //要读数据长度
    u16 TX_WriteLength;//要写数据长度
    u8 RX_Data[BUFFER_SIZE]; 
    u8 TX_Data[BUFFER_SIZE];  
}USART_Data_t;






typedef struct
{
    u8 Length;
    
     
}App_Data_u;

typedef struct 
{
    u8 ID_Head[6];
    App_Data_u App_Data;
    u8 ID_End[6];
}FrameData_t;


typedef union
{
    USART_Data[BUFFER_SIZE];
    FrameData_t  FrameData; 
}USART_FrameData_u;


void USART1_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);   
void USART2_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);

int fputc(int ch, FILE* stream);
#endif







