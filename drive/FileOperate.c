#include "IncludeFile.h"



static FATFS fs;
static FIL fils;
static DIR dp;		
static FILINFO fno;
static u32 DataPointer;

u8 File_FATFSInit()
{
    return disk_initialize(DEV_SD);
}



u8 File_MountDisk(const char* Path)
{
	return f_mount(&fs,Path,1);
}



u8 File_UmountDiak(const char* Path)
{
    return f_mount(0,Path,0);
}



u8 File_CreateFAT()
{
    u8 work[512];
    return f_mkfs("1",FM_FAT|FM_SFD,512,work,sizeof(work));
}



//Directory Operate 文件夹操作
u8 File_OpenDir(const char* Path)
{
    return f_opendir(&dp,Path);
}




void File_CloseDir()
{
    f_close(&fils);
}





u8 File_ScanIndex(const char* Path,u8* Num ,FileName NameList)
{


return 0;

}



u8 File_Mkdir(const char * Path)
{
    return f_mkdir(Path);
}



//File Operate   文件操作
u8 File_CreateNewFile(const char* Path)
{
    u8 sta;

    sta=f_open(&fils,Path,FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);

    if( sta == FR_OK)
    {
        f_close(&fils);	
			
    }
    return sta;
}



u8 File_ReadData(const char* Path,u8* Data,u16 Length)
{
    u8 sta;

    sta=f_open(&fils,Path,FA_READ|FA_OPEN_EXISTING);

    if( sta == FR_OK)
    {
        sta=f_read(&fils,Data,Length,&DataPointer);
    }
    f_close(&fils);
     return sta;
}



u8 File_WriteData(const char* Path,u8* Data,u16 Length)
{
    u8 sta;

    sta=f_open(&fils,Path,FA_WRITE|FA_OPEN_EXISTING);

    if( sta == FR_OK)
    {
        sta =f_write(&fils,Data,Length,&DataPointer);
    }
    f_close(&fils);
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





void File_Delete()
{




    
}





























