#include "IncludeFile.h"



//���ڿ��Ź�   4 ��
void IWDOG_Init()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetPrescaler(IWDG_Prescaler_32);
    IWDG_SetReload(0xFFFF);

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_Enable();
}


//ι��
void IWDOG_Clear()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetReload(0xFFFF);
    IWDG_ReloadCounter();

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
}


//�������Ź�
void WWDOG_Init()
{












    
}





















