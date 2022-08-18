#include "IncludeFile.h"

//采样周期：us
#define  SAMPLE_PERIOD   (500)



u16 ADC_Data[1024];
u8 ADC_DataFlag = RESET;
arm_cfft_instance_f32 FFT_Info;

//  PA1 - ADC1_CH1 -  DMA2_S0_CH0

//目前采用ADC一直连续转换，DMA一直传送数据，没有使用定时器定时采样，可根据DMA中断，判断数据是否完成
void ADCTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	NVIC_InitTypeDef  NVIC_Initstr;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = SAMPLE_PERIOD-1;
	TIM_TimeBaseInitStr.TIM_Prescaler = 42-1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OCInitTypestuc.TIM_Pulse = SAMPLE_PERIOD/2-1;
	TIM_OC2Init(TIM2,&TIM_OCInitTypestuc);


	NVIC_Initstr.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);


	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC2Ref);
    TIM_ARRPreloadConfig(TIM2,ENABLE);
	// TIM_GenerateEvent(TIM2,TIM_EventSource_Update);
	// // TIM_InternalClockConfig(TIM2);
	// TIM_UpdateDisableConfig(TIM2,DISABLE);
    // TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}




void DMA_ConfigInit()
{
	NVIC_InitTypeDef  NVIC_Initstr;
	DMA_InitTypeDef DMA_InitConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_InitConfig.DMA_Memory0BaseAddr = (u32)ADC_Data;	
	DMA_InitConfig.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	DMA_InitConfig.DMA_Channel = DMA_Channel_0;
	DMA_InitConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitConfig.DMA_BufferSize = sizeof(ADC_Data)/sizeof(ADC_Data[0]);
  	DMA_InitConfig.DMA_DIR = DMA_DIR_PeripheralToMemory; 
	DMA_InitConfig.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitConfig.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitConfig.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitConfig.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_Mode = DMA_Mode_Circular;
	DMA_InitConfig.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA2_Stream0,&DMA_InitConfig);

	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream0_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA2_Stream0,ENABLE);

}



//***************************************************//
//  功能描述: 电池检测ADC初始化
//  
//  参数: 无
//  
//  返回值:无
//  
//  说明: 无
//  
//***************************************************//
void FFT_ADCInit()
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	
	
	NVIC_InitTypeDef  NVIC_Initstr;
	GPIO_InitTypeDef GPIO_Initstruc;
	ADC_InitTypeDef   ADC_InitTypeDefstruct;
	ADC_CommonInitTypeDef   ADC_CommonInitTypeDefstruct;

	GPIO_Initstruc.GPIO_Pin=GPIO_Pin_1;
	GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AN; 
	GPIO_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruc);

	ADC_CommonInitTypeDefstruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitTypeDefstruct.ADC_Prescaler = ADC_Prescaler_Div6;                                   //PLCLK 8分频
	ADC_CommonInitTypeDefstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitTypeDefstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitTypeDefstruct);

	ADC_InitTypeDefstruct.ADC_Resolution = ADC_Resolution_12b;              
	ADC_InitTypeDefstruct.ADC_ScanConvMode = DISABLE;
	ADC_InitTypeDefstruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
	ADC_InitTypeDefstruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);

	// NVIC_Initstr.NVIC_IRQChannel=ADC_IRQn;
	// NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	// NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	// NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_Init(&NVIC_Initstr);
	// ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
	// ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);

	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_28Cycles);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);





}


void FFT_Init()
{

	DMA_ConfigInit();
	FFT_ADCInit();
	ADCTimer_Init();
	ADC_DataFlag = RESET;
}








void FFT_Process()
{
	if( ADC_DataFlag == SET)
	{
		//arm_cfft_f32(&arm_cfft_sR_f32_len256,(float32_t)ADC_Data,0,1);
		ADC_DataFlag = RESET;
	}
}


void DMA2_Stream0_IRQHandler()
{
		if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)  == SET )
		{
			DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);

				if( ADC_DataFlag == RESET)
				{
					ADC_DataFlag = SET;
					LED1_ON;
				}
				else
				{	
					ADC_DataFlag = RESET;
					LED1_OFF;
				}
		}    
}

















void ADC_IRQHandler()
{
	if( ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET) 
	{

	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}

void TIM2_IRQHandler()
{

    if( TIM_GetITStatus(TIM2,TIM_IT_CC2) == SET)
    {

    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);

}
