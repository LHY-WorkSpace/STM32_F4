#ifndef IAP_H
#define IAP_H



//FLASH总大小  512k
#define FLASH_SIZE             ((u32)0x00080000)

//FLASH各个扇区大小
#define SECTOR_0_SIZE      ( (u32) 16*1024 )  
#define SECTOR_1_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_2_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_3_SIZE      ( (u32) 16*1024 ) 

#define SECTOR_4_SIZE      ( (u32) 64*1024 ) 
#define SECTOR_5_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_6_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_7_SIZE      ( (u32) 128*1024 ) 

//放置IAP程序区域的起始地址
#define BOOTLOADER_BASE_ADDR    ((u32)0x08070000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00010000)   //大小 64K


//应用程序起始地址
#define USERCODE_BASE_ADDR      ( (vu32) 0x08000000 ) 
#define USERCODE_CODE_SIZE      ( (vu32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //应用大小 448k


#define DATA_BUFFER             ((u16)0x1000)  //数据缓冲 4kB

#define USART_OVERTIME              20        //接收超时时间( USART_OVERTIME * 50ms ) 超过这个时间USART未收到数据就认为数据传输完毕



// #define PLACE_CODE_IN_USER_ROM  __attribute__ ((section("USER_ROM")));//放置升级代码区域

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




