#include "IncludeFile.h"



static FATFS fs;









//初始化文件系统
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

//挂载设备：   "1:"
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

//卸载设备
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

//创建文件系统
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



//Directory Operate 文件夹操作
//打开文件夹
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

//关闭文件夹
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

//创建文件夹
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




//File Operate   文件操作
//创建新文件,如果已存在，则删除重新创建
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


//读取数据
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


//写入数据
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




//只能获取文件的大小，无法获取文件夹的大小
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


//修改文件名
u8 File_Rename(const char* path_old, const char* path_new)
{
    return f_rename( path_old, path_new);
}


//删除文件
u8 File_Delete(const char* path)
{
    return f_unlink(path);
}





























