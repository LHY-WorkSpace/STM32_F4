#include "IncludeFile.h"



u16 ADC_Data[1024];





void ADCTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    NVIC_InitTypeDef  NVIC_Initstr;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = Period;
	TIM_TimeBaseInitStr.TIM_Prescaler = 168000-1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);

	NVIC_Initstr.NVIC_IRQChannel = RCC_APB1Periph_TIM2;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority = 3;
	NVIC_Initstr.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Initstr);

    TIM_ARRPreloadConfig(TIM2,ENABLE);
    TIM_ITConfig(TIM2,TIM_IT_Trigger,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}




void DMA1_ConfigInit()
{
	NVIC_InitTypeDef  NVIC_Initstr;
	DMA_InitTypeDef DMA_InitConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);

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
	DMA_InitConfig.DMA_Mode = DMA_Mode_Normal; //循环发送 DMA_Mode_Normal(单次)DMA_Mode_Circular
	DMA_InitConfig.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Stream4,&DMA_InitConfig);
	DMA_ITConfig(DMA1_Stream4,DMA_IT_TC,ENABLE);
	
	NVIC_Initstr.NVIC_IRQChannel=DMA1_Stream4_IRQn;
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
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitTypeDefstruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);

	ADC_Cmd(ADC1,ENABLE);
	//ADC_TempSensorVrefintCmd(ENABLE);

}








