#include "IncludeFile.h"

//采样周期：ms
#define  SAMPLE_PERIOD   (10)

#define  POINT   (1024)
FFT_Data_t FFT_Data[POINT];
u16 ADC_Data[POINT];

float32_t FFT_R[1024];
u8 PointY[128];

u8 ADC_DataFlag = RESET,ADC_DataFlagA = RESET;

static u8g2_t u8g2_Data;




//  PA1 - ADC1_CH1 -  DMA2_S0_CH0

//目前采用ADC一直连续转换，DMA一直传送数据，没有使用定时器定时采样，可根据DMA中断，判断数据是否完成
void ADCTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
//	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	NVIC_InitTypeDef  NVIC_Initstr;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = SAMPLE_PERIOD-1;
	TIM_TimeBaseInitStr.TIM_Prescaler = 42-1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);

	// TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_Toggle;
	// TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	// TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_Low;
	// TIM_OCInitTypestuc.TIM_Pulse = SAMPLE_PERIOD/2-1;
	// TIM_OC2Init(TIM2,&TIM_OCInitTypestuc);


	NVIC_Initstr.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);


	// TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	// TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC1);
    TIM_ARRPreloadConfig(TIM2,ENABLE);
	// TIM_GenerateEvent(TIM2,TIM_EventSource_Update);
	// // TIM_InternalClockConfig(TIM2);
	// TIM_UpdateDisableConfig(TIM2,DISABLE);
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
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
	
	//NVIC_InitTypeDef  NVIC_Initstr;
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
	ADC_InitTypeDefstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
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
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_56Cycles);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	ADC_SoftwareStartConv(ADC1);

}


void FFT_Init()
{
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2_Data, U8G2_MIRROR_VERTICAL, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay); 
	u8g2_InitDisplay(&u8g2_Data);
	u8g2_SetPowerSave(&u8g2_Data, 0);
    u8g2_ClearDisplay(&u8g2_Data);


	DMA_ConfigInit();
	FFT_ADCInit();
	ADCTimer_Init();
	ADC_DataFlag = RESET;
	ADC_DataFlagA = RESET;

	u8g2_ClearBuffer(&u8g2_Data);
}



void FFTTEasst()
{
	u16 i;
	for ( i = 0; i < 256; i++)
	{
		if((i&0x08) == 8)
		{
			ADC_Data[i]=60;
		}
		else
		{
			ADC_Data[i]=0;
		}
	}
}



// FFT_Data[i].Real = 10*arm_sin_f32(0.01745*i*5);
// FFT_Data[i].Image = 0;
void FFT_Process()
{
	u16 i;

	if( ADC_DataFlag == SET)
	{
		u8g2_ClearBuffer(&u8g2_Data);
		for ( i = 1; i < POINT; i++)
		{
			FFT_Data[i].Real = (float32_t)ADC_Data[i];
			FFT_Data[i].Image = 0;
		}

		arm_cfft_f32(&arm_cfft_sR_f32_len1024,(float32_t *)FFT_Data,0,1);
		arm_cmplx_mag_f32((float32_t *)FFT_Data,FFT_R,POINT);

		for ( i = 1; i < 128; i++)
		{
			FFT_R[i]=2*log(i)*FFT_R[i]/200;

			if( PointY[i] < FFT_R[i] )
			{
				PointY[i] = FFT_R[i];
			}
			else
			{
				PointY[i]-=2;
			}
			u8g2_DrawVLine(&u8g2_Data,i,0,PointY[i]);
			u8g2_DrawPixel(&u8g2_Data,i,PointY[i]+1);
		}

		ADC_DataFlag = RESET;
		u8g2_SendBuffer(&u8g2_Data);
	}
}


void DMA2_Stream0_IRQHandler()
{
	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)  == SET )
	{
		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
		ADC_DataFlag = SET;
	} 
}

















// void ADC_IRQHandler()
// {
// 	if( ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET) 
// 	{
// 		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
// 	}

// }

void TIM2_IRQHandler()
{

    if( TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

		if( ADC_DataFlagA == RESET)
		{
			ADC_DataFlagA = SET;
			LED2_ON;
		}
		else
		{	
			ADC_DataFlagA = RESET;
			LED2_OFF;
		}
    }


}
