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


//协议错误代码
#define   HEAD_ERR  (0x01)
#define   HEAD1_ERR  (0x02)
#define   HEAD2_ERR  (0x03)
#define   HEAD3_ERR  (0x04)





#define   MAX_SIZE  (1024)

typedef struct
{
    u16 B16_B08;    //部件ID
    u8  DataType;   //读，写，执行
    u32 DataID;     //数据ID
    u32 DataBuff[MAX_SIZE];
    u8 (*ReadData)(u8 *Data);//读数据
    u8 (*WriteData)(u8 *Data);//写数据
    u8 (*ExecuteFun)(u8 *Data);//执行
}App_Data_u;









#endif





