#include "IncludeFile.h"



//***************************************************//
//  功能描述: 看门狗初始化
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 4秒
//  
//***************************************************//
void IWDOG_Init()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetPrescaler(IWDG_Prescaler_32);
    IWDG_SetReload(0xFFFF);

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_Enable();
}


//***************************************************//
//  功能描述: 喂狗
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
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





















