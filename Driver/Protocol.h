#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "DataType.h"


//Э��������
#define   HEAD_ERR  (0x01)
#define   HEAD_ERR  (0x02)
#define   HEAD_ERR  (0x03)
#define   HEAD_ERR  (0x04)





#define   MAX_SIZE  (1024)

typedef struct
{
    u16 B16_B08;    //����ID
    u8  DataType;   //����д��ִ��
    u32 DataID;     //����ID
    u32 DataBuff[MAX_SIZE];
    u8 (*ReadData)(u8 *Data);//������
    u8 (*WriteData)(u8 *Data);//д����
    u8 (*ExecuteFun)(u8 *Data);//ִ��
}App_Data_u;









#endif





