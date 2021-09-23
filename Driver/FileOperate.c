#include "IncludeFile.h"



static FATFS fs;









//��ʼ���ļ�ϵͳ
u8 File_FATFSInit()
{
    
    GPIO_InitTypeDef GPIOA_Initstruc;
    DIR dp;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

    GPIOA_Initstruc.GPIO_Pin=GPIO_Pin_8;
    GPIOA_Initstruc.GPIO_Mode=GPIO_Mode_IN;
    GPIOA_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
    GPIOA_Initstruc.GPIO_OType=GPIO_OType_PP; 
    GPIOA_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;           
    GPIO_Init(GPIOA,&GPIOA_Initstruc);


    disk_initialize(DEV_SD);

	File_MountDisk("1:");
	File_OpenDir("1:/SD",&dp);

    return 0;
}

//�����豸��   "1:"
u8 File_MountDisk(const char* Path)
{
	 
    u8 Sta;
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    Sta = f_mount(&fs,Path,1);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

    return Sta;
}

//ж���豸
u8 File_UmountDiak(const char* Path)
{

    u8 Sta;
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    Sta = f_mount(0,Path,0);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

    return Sta;

}

//�����ļ�ϵͳ
u8 File_CreateFAT()
{
    u8 work[512];
    u8 Sta;
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    Sta = f_mkfs("1",FM_FAT|FM_SFD,512,work,sizeof(work));

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

    return Sta;

}



//Directory Operate �ļ��в���
//���ļ���
u8 File_OpenDir(const char* Path,DIR *dp)
{
    u8 Sta;
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    Sta = f_opendir(dp,Path);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 


    return Sta;
}

//�ر��ļ���
void File_CloseDir(FIL *fils)
{
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    f_close(fils);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 


}

//�����ļ���
u8 File_Mkdir(const char * Path)
{
 u8 Sta;
 #if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    Sta = f_mkdir(Path);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 


    return Sta;
}



u8 File_ScanIndex(const char* Path,u8* Num ,FileName NameList)
{


return 0;

}




//File Operate   �ļ�����
//�������ļ�,����Ѵ��ڣ���ɾ�����´���
u8 File_CreateNewFile(const char* Path,FIL *fils)
{
    u8 sta;

#if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    sta = f_open(fils,Path,FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);

    if( sta == FR_EXIST)
    {
        sta = f_unlink(Path);
        sta = f_open(fils,Path,FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);
    }
    f_close(fils);	


#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

    return sta;
}


//��ȡ����
u8 File_ReadData(FIL *fils,const char* Path,u8* Data,u32 Length,u32 Offset)
{
    u8 sta;
    u32 DataPointer;

#if USE_RTOS
    taskENTER_CRITICAL();
#endif 


    sta=f_open(fils,Path,FA_READ|FA_OPEN_EXISTING);

    if( Offset != 0)
    {
        f_lseek(fils,Offset);
    }

    if( sta == FR_OK)
    {
        sta=f_read(fils,Data,Length,&DataPointer);
    }
    f_close(fils);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

     return sta;
}


//д������
u8 File_WriteData(FIL *fils,const char* Path,u8* Data,u32 Length,u32 Offset)
{
    u8 sta;
    u32 DataPointer;

#if USE_RTOS
    taskENTER_CRITICAL();
#endif 

    sta=f_open(fils,Path,FA_WRITE|FA_OPEN_EXISTING);
     
    if( Offset != 0)
    {
        f_lseek(fils,Offset);
    }

    if( sta == FR_OK)
    {
        sta =f_write(fils,Data,Length,&DataPointer);
    }
    f_close(fils);

#if USE_RTOS
    taskEXIT_CRITICAL();
#endif 

    return sta;

}




//ֻ�ܻ�ȡ�ļ��Ĵ�С���޷���ȡ�ļ��еĴ�С
u32 File_GetFileSize(const char* Path)
{
    u8 sta;
    FILINFO fno;

    sta=f_stat(Path,&fno);

    if( sta != FR_OK)
    {
        return sta;
    }
    else
    {   
        return (u32)fno.fsize;
    }
}






void File_GetFileNameList(void)
{




}


//�޸��ļ���
u8 File_Rename(const char* path_old, const char* path_new)
{
    return f_rename( path_old, path_new);
}


//ɾ���ļ�
u8 File_Delete(const char* path)
{
    return f_unlink(path);
}





























