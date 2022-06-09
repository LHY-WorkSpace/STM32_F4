#include "IncludeFile.h"


//初始化并使能RNG
void RNG_Init()
{
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);
    RNG_Cmd(ENABLE);
}

//关闭RNG
void RNG_Close()
{
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,DISABLE);
    RNG_Cmd(DISABLE);
}

//获取随机数
u8 RHG_GetRadomData(u32 *Radom)
{
    u8 times;
	while((RNG_GetFlagStatus(RNG_FLAG_DRDY)!=SET)&&(times<10))
    {
        Delay_us(2);
        times++;
    }
    if(times==10)
    {
        return FALSE;
    }
    else
    {
        *Radom = RNG->DR;
        return TRUE;
    }
	
}



