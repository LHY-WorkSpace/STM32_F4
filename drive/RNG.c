#include"IncludeFile.h"

u32 Radom;


void Rng_Init()
{
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);
    RNG_Cmd(ENABLE);
	
}


u32 Rng_GetRadomData()
{
	while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==SET)
	return RNG_GetRandomNumber();
}



