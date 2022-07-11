#include"IncludeFile.h"

void AT24C08_Init(void)
{
	IIC_Init();
}

u8  AT24C08WriteData(u16 addr,u16 length,u8 *data)
{
	u8 k,i;
	u16 PageNum,WR_Len,Offset,LenCount;
	B16_B08 MemAddr;	//绝对地址

	if( addr >= AT24C08_PAGE_SIZE*AT24C08_PAGES)
	{
		return 0XFF;
	}
	
	MemAddr.B16 = addr;

	PageNum = addr/AT24C08_PAGE_SIZE;			//得到页编号
	Offset = addr - PageNum*AT24C08_PAGE_SIZE;	//计算页内偏移
	WR_Len = AT24C08_PAGE_SIZE - Offset;		//计算一页内从偏移位置要写入的字节数
	LenCount = 0;

	if( WR_Len >= length )	//长度小于等于未跨页剩余字节数，则按实际长度写入
	{
		WR_Len = length;
	}

	do
	{
		Start_IIC();
		IIC_SenddByte(AT24C08_ADDRESS | MemAddr.B08[1] <<1);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(MemAddr.B08[0]);
		IIC_Wait_Ack_OK();

		for(k=0;k<WR_Len;k++)
		{
			IIC_SenddByte(data[LenCount]);
			if(IIC_Wait_Ack_OK() == FALSE)
			{
				return FALSE;
			}
			LenCount++;
		}
		Stop_IIC();
		//此处必须延时，等待页写入完成，手册最大5ms
		for ( i = 0; i < 5; i++)
		{
			IIC_Delay(1000);
		}
		
		MemAddr.B16 += WR_Len;

		if( (length - LenCount) >= AT24C08_PAGE_SIZE)
		{
			WR_Len = AT24C08_PAGE_SIZE;
		}
		else
		{
			WR_Len = length - LenCount;
		}

	}while(LenCount != length);

	return TRUE;
}




u8 AT24C08ReadData(u16 addr,u16 length,u8 *data)
{
	u16 i;
	B16_B08 MemAddr;	//绝对地址

	if( addr >= AT24C08_PAGE_SIZE*AT24C08_PAGES)
	{
		return 0XFF;
	}

	MemAddr.B16=addr;

	Start_IIC();
	IIC_SenddByte(AT24C08_ADDRESS |MemAddr.B08[1]<<1);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(MemAddr.B08[0]);
	IIC_Wait_Ack_OK();

	Start_IIC();
	IIC_SenddByte(AT24C08_ADDRESS|0X01|MemAddr.B08[1]<<1);//读取操作
    IIC_Wait_Ack_OK();

	for(i=0;i<length;i++)
	{
		data[i]=IIC_GetByte();
		if( i == length-1)
		{
			IIC_Send_NAck();//最后一个字节发送N_ACK
		}
		else
		{
			IIC_Send_Ack();
		}
	}
	Stop_IIC();
	return TRUE;
}












