#include "IncludeFile.h"


static EnCoderInfo_t EnCoderInfo;


// Timer_2
// A:D12 
// B:D13 
// Key:B6
void EnCoderInit()
{

	GPIO_InitTypeDef Encoder_GPIO_Init;
	NVIC_InitTypeDef  NVIC_Initstr;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
	GPIO_InitTypeDef Key_Initstruc;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
   	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
   	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    //编码器
    Encoder_GPIO_Init.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
    Encoder_GPIO_Init.GPIO_Mode = GPIO_Mode_AF;
    Encoder_GPIO_Init.GPIO_PuPd = GPIO_PuPd_UP;
    Encoder_GPIO_Init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&Encoder_GPIO_Init);

    //按键
	Key_Initstruc.GPIO_Pin=GPIO_Pin_6;
	Key_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	Key_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	Key_Initstruc.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&Key_Initstruc); 


	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = ENCODER_LINES*4-1;//4倍频计数;
	TIM_TimeBaseInitStr.TIM_Prescaler =0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStr);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

	NVIC_Initstr.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=5;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

    //T1 T2 均计数(4倍频计数)，IC1 不反相,IC2 不反相
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    EnCoderInfo.Dir = Encoder_UP;
    EnCoderInfo.KeyState = Encoder_Release;
    EnCoderInfo.Circle_Cnt = 0;
    EnCoderInfo.Pluse_Cnt = 0;
    EnCoderInfo.CNT_REG = 0;

    TIM4->CNT = 0;

    TIM_ClearITPendingBit(TIM4,TIM_IT_Update );
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);

}

//***************************************************//
//  功能描述: 更新按键状态
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 无
//  
//***************************************************//
void EnCoderUpdateKey()
{
    static u8 count = 0;

    if(count > ENCODER_DELAY)
    {
        if( ENCODER_KEY == SET )
        {
            EnCoderInfo.KeyState = Encoder_Pressed;
        }
        else
        {
            EnCoderInfo.KeyState = Encoder_Release;
        }
        count = 0;
    }
}

//获取按键状态
 Encoder_Key_e EnCoderGetKeyState()
 {
    return EnCoderInfo.KeyState;
 }

//***************************************************//
//  功能描述: 更新编码器旋钮状态
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 无
//  
//***************************************************//
void EnCoderUpdate()
{


	if( ( TIM4->CR1  ) & 0x10)
    {
        EnCoderInfo.Dir = Encoder_DOWN ;
    }
    else
    {
        EnCoderInfo.Dir = Encoder_UP;
    }

    EnCoderInfo.Pluse_Cnt =  EnCoderInfo.Circle_Cnt*ENCODER_LINES + (TIM4->CNT/4);

    EnCoderInfo.CNT_REG = TIM4->CNT;
}


//***************************************************//
//  功能描述: 复位编码器状态
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 无
//  
//***************************************************//
void EnCoderReset()
{
    TIM_Cmd(TIM4,DISABLE);
    memset(&EnCoderInfo,0x00,sizeof(EnCoderInfo));
    TIM4->CNT = 0;
    TIM_Cmd(TIM4,ENABLE);
}


//***************************************************//
//  功能描述: 获取编码器各种数据
//  
//  参数: 无
//  
//  返回值: TRUE / FALSE
//  
//  说明: 调用时自动更新，无需依靠EnCoderUpdate()定时更新
//  
//***************************************************//

//获取总脉冲数
s32 EnCoderGetPluseCNT()
{
    EnCoderInfo.Pluse_Cnt =  EnCoderInfo.Circle_Cnt*ENCODER_LINES + (TIM4->CNT/4);
    return EnCoderInfo.Pluse_Cnt;
}

//获取旋转圈数
s32  EnCoderGetCircleCNT()
{
    return EnCoderInfo.Circle_Cnt;
}

//获取旋转方向
Encoder_Dir_e EnCoderGetDir()
{
    if( ( TIM4->CR1  ) & 0x10)
    {
        EnCoderInfo.Dir = Encoder_UP;
    }
    else
    {
        EnCoderInfo.Dir = Encoder_DOWN;
    }

    return EnCoderInfo.Dir;
}


void TIM4_IRQHandler()
{
    if( TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update );
        //计数溢出中断，计数值超过一圈
        if( ( TIM4->CR1  ) & 0x10)
        {
            EnCoderInfo.Circle_Cnt --;
        }
        else
        {
            EnCoderInfo.Circle_Cnt ++;
        }

    }
}











