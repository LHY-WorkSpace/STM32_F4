#ifndef IAP_H
#define IAP_H



//FLASH�ܴ�С  512k
#define FLASH_SIZE             ((u32)0x00080000)

//FLASH����������С
#define SECTOR_0_SIZE      ( (u32) 16*1024 )  
#define SECTOR_1_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_2_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_3_SIZE      ( (u32) 16*1024 ) 

#define SECTOR_4_SIZE      ( (u32) 64*1024 ) 
#define SECTOR_5_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_6_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_7_SIZE      ( (u32) 128*1024 ) 

//����IAP�����������ʼ��ַ
#define BOOTLOADER_BASE_ADDR    ((u32)0x08070000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00010000)   //��С 64K


//Ӧ�ó�����ʼ��ַ
#define USERCODE_BASE_ADDR      ( (vu32) 0x08000000 ) 
#define USERCODE_CODE_SIZE      ( (vu32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //Ӧ�ô�С 448k


#define DATA_BUFFER             ((u16)0x1000)  //���ݻ��� 4kB

#define USART_OVERTIME              20        //���ճ�ʱʱ��( USART_OVERTIME * 50ms ) �������ʱ��USARTδ�յ����ݾ���Ϊ���ݴ������



// #define PLACE_CODE_IN_USER_ROM  __attribute__ ((section("USER_ROM")));//����������������

typedef enum
{
    ACanNotRead,
    ACanRead,
    BCanNotRead,
    BCanRead,
    Busy
}Read_State;



typedef enum
{
    BufferB_Empty,
    BufferA_Empty,
}Buffer_State;



void  UpdateCode_ByUSART(void);
void  UpdateCode_BySD(void);
void  Goto_UserCode(void);












#endif 




