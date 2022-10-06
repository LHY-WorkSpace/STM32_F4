#include"IncludeFile.h"




void KeyInit()
{
   	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	// GPIOB_Initstruc.GPIO_OType=GPIO_OType_PP;           
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIOB_Initstruc); 

}


u8 KeyGetID(u8 ID)
{
    u8 id = MAX_KEY;
    switch (ID)
    {
        case OK_KEY:
            if(KEY_OK == RESET)
            {
                id = OK_KEY;
            }
            break;
        case BACK_KEY:
            if(KEY_BACK == RESET)
            {
                id = BACK_KEY;
            }
            break;
        case UP_KEY:
            if(KEY_UP == RESET)
            {
                id = UP_KEY;
            }
            break;
        case DOWN_KEY:
            if(KEY_DOWN == RESET)
            {
                id = DOWN_KEY;
            }
            break;   
        default:
            break;
    }
    return id;

}





















