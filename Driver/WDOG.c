#include "IncludeFile.h"



//窗口看门狗   4 秒
void IWDOG_Init()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetPrescaler(IWDG_Prescaler_32);
    IWDG_SetReload(0xFFFF);

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_Enable();
}


//喂狗
void IWDOG_Clear()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetReload(0xFFFF);
    IWDG_ReloadCounter();

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
}


//独立看门狗
void WWDOG_Init()
{












    
}





















