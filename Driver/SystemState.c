#include "IncludeFile.h"




//�豸״̬�б�˳���� SystemState_n һ��
static volatile u8 DeviceStateList[DEVICES_NUM];



// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
u8 System_GetState(u8 Device,u8 State)
{
	if( State == 0xff )
	{
		return DeviceStateList[Device];
	}

	if( (DeviceStateList[Device]&State) != State )
	{
		return  RESET;
	}
	else
	{
		return  SET;
	}

}


// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
void System_SetState(u8 Device,u8 State)
{

    DeviceStateList[Device] |= State;

}


// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
void System_ResetState(u8 Device,u8 State)
{

    DeviceStateList[Device] &= (~State);
    
}

void SystemDown()
{
	char Data[] ="STM32-USART-Test!!!\r\n";
	while(1)
	{		
		LED1_ON;
		Delay_ms(500);
		LED1_OFF;
		Delay_ms(500);
		DispalyUTF_8Strings();
		//USART_ITSendData(USART1,&USART1_Buffer,(u8 *)Data,sizeof(Data));
	}
}

void SW_Reset()
{
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}














