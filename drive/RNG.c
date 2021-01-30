#include "stm32f4xx.h"
#include "RNG.h"


void rng_init()
{
RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);
RNG_Cmd(ENABLE);
	
//		u32 radom;
//	while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==1)
//	 radom=(RNG_GetRandomNumber()&0x0f)%10;
	
	
}

