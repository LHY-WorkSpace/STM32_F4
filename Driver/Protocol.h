//***************************************************//
 //  Author: LHY-WorkSpace 2371270263@qq.com
 //  Date: 2022-07-09 22:33:11
 //  LastEditors: LHY-WorkSpace 2371270263@qq.com
 //  LastEditTime: 2022-07-09 22:51:58
 //  FilePath: \STM32_F4\Driver\Protocol.h
 //  Description: 
 //  
 //  Copyright (c) 2022 by LHY-WorkSpace 2371270263@qq.com, All Rights Reserved. 
//***************************************************//
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "DataType.h"


//Э��������
#define   HEAD_ERR   (0x01)
#define   HEAD1_ERR  (0x02)
#define   HEAD2_ERR  (0x03)
#define   HEAD3_ERR  (0x04)





#define   MAX_SIZE  (1024)


// #pragma pack (1)
typedef struct
{
    u16 B16_B08;    //����ID
    u16 DataType;   //����д��ִ��
    u32 DataID;     //����ID
    u32 DataBuff[MAX_SIZE];
    u8 (*ReadData)(u8 *Data);//������
    u8 (*WriteData)(u8 *Data);//д����
    u8 (*ExecuteFun)(u8 *Data);//ִ��
}App_Data_u;
// #pragma pack ()







#endif





