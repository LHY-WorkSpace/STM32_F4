#include "IncludeFile.h"

//采样周期：us
#define  SAMPLE_PERIOD   (100)



u16 ADC_Data[1024];
arm_cfft_instance_f32 FFT_Info;




void ADCTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = SAMPLE_PERIOD;
	TIM_TimeBaseInitStr.TIM_Prescaler = 42000-1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);

    TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC2Ref);
	// TIM_GenerateEvent(TIM2,TIM_EventSource_Trigger);
    //TIM_ITConfig(TIM2,TIM_IT_Trigger,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}




void DMA_ConfigInit()
{
	NVIC_InitTypeDef  NVIC_Initstr;
	DMA_InitTypeDef DMA_InitConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_InitConfig.DMA_Memory0BaseAddr = (u32)ADC_Data;	
	DMA_InitConfig.DMA_PeripheralBaseAddr = (u32)&ADCx->DR;
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
	DMA_InitConfig.DMA_Mode = DMA_Mode_Normal;
	DMA_InitConfig.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_Priority = DMA_Priority_Medium;

	DMA_Init(DMA2_Stream0,&DMA_InitConfig);
	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
	
	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream0_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

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
	
	GPIO_InitTypeDef GPIO_Initstruc;
	ADC_InitTypeDef   ADC_InitTypeDefstruct;
	ADC_CommonInitTypeDef   ADC_CommonInitTypeDefstruct;

	GPIO_Initstruc.GPIO_Pin=GPIO_Pin_5;
	GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AN; 
	GPIO_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruc);

	ADC_CommonInitTypeDefstruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitTypeDefstruct.ADC_Prescaler = ADC_Prescaler_Div8;                                   //PLCLK 8分频
	ADC_CommonInitTypeDefstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitTypeDefstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitTypeDefstruct);

	ADC_InitTypeDefstruct.ADC_Resolution = ADC_Resolution_12b;              
	ADC_InitTypeDefstruct.ADC_ScanConvMode = DISABLE;
	ADC_InitTypeDefstruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
	ADC_InitTypeDefstruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);

	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);

}






void FFT_Process(u8 *Data,u16 Length)
{
	arm_cfft_
	arm_cfft_f32(&arm_cfft_sR_f32_len256,ADC_Data);


}


void DMA2_Stream0_IRQHandler()
{
		if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0))
		{
			DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
		}    


}


