#ifndef  DHT11_H
#define  DHT11_H

#define uchar unsigned char
#define uint unsigned int 



uchar DHT11_Init(void);


void DHT11_Read_Data(uchar *temp,uchar *humi);//��ȡ��ʪ��
uchar DHT11_Read_Byte(void);//����һ���ֽ�
 
void DHT11_IO_IN(void);
void DHT11_IO_OUT(uchar DHT11_IO_CMD);


#endif



