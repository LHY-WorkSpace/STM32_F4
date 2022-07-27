#ifndef SPI_FLASH_H
#define SPI_FLASH_H


#define FLASH_SIZE              (4096*1024)
#define FLASH_BLOCK_SIZE        (16*4096)
#define FLASH_SECTOR_SIZE       (4096)
#define FLASH_PAGE_SIZE         (256)


#define FLASH_READ              (0x03)
#define FLASH_FAST_READ         (0x0B)
#define FLASH_WRDI              (0x04)//д�ر�
#define FLASH_WREN              (0x06)//д����
#define FLASH_PAGE_WRITE        (0x02)
#define FLASH_SECTOR_ERASE      (0x20)

//��״̬�Ĵ���
#define FLASH_READ_STATE_REG0      (0x05)
#define FLASH_READ_STATE_REG1      (0x35)
#define FLASH_READ_STATE_REG2      (0x15)
//д״̬�Ĵ���
#define FLASH_WRITE_STATE_REG0      (0x01)
#define FLASH_WRITE_STATE_REG1      (0x31)
#define FLASH_WRITE_STATE_REG2      (0x11)

//��������ģʽ����ַ����
#define ERASE_MODE_NUM       (0x12)
#define ERASE_MODE_ADDR      (0x34)

    
#define SPI_FLASH_DISABLE      GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define SPI_FLASH_ENABLE       GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void Flash_IO_Init(void);
void Flash_GetID(void);
u8 Flash_Read_Data(u32 Addr,u8 *Data,u32 Length);
u8 Flash_Sector_Erase(u32 Addr,u8 Type);
u8 Flash_Write_Data(u32 Addr,u8 *Data,u32 Length);

#endif

