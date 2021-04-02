#ifndef  FILEOPERATE_H
#define  FILEOPERATE_H

//最大支持50字节文件名长度
#define FILE_MAX_NAME_LENGTH        (50)




typedef struct
{
	u8 Length;
	char Name[FILE_MAX_NAME_LENGTH];
}FileName;





void File_ScanIndex();
void File_GetFileNameList();




#endif

