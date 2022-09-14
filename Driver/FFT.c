#include "IncludeFile.h"


//��Ļ����
#define  SCREEN_LENGTH   (128)
//��������
#define  POINT   		(512)

u16 ADC_Data[POINT];
FFT_Data_t FFT_Data[POINT];
float32_t FFT_Display[SCREEN_LENGTH];
u8 PointY[SCREEN_LENGTH];//��¼�ϴεĵ�λ��
u8 DMADataReady = RESET;
u8 ADC_DataFlag = RESET;
static u8g2_t u8g2_Data;


//  PA1 - ADC1_CH1 -  DMA2_S0_CH0
//	10us ����һ��
void ADCTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period = 10-1;
	TIM_TimeBaseInitStr.TIM_Prescaler = 84-1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStr);

    TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
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
//  ��������: FFT ADC��ʼ��
//  
//  ����: ��
//  
//  ����ֵ:��
//  
//  ˵��: ����ģʽ��DMA����
//  
//***************************************************//
void FFT_ADCInit()
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	
	
	// NVIC_InitTypeDef  NVIC_Initstr;
	GPIO_InitTypeDef GPIO_Initstruc;
	ADC_InitTypeDef   ADC_InitTypeDefstruct;
	ADC_CommonInitTypeDef   ADC_CommonInitTypeDefstruct;

	GPIO_Initstruc.GPIO_Pin=GPIO_Pin_1;
	GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AN; 
	GPIO_Initstruc.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruc);

	ADC_CommonInitTypeDefstruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitTypeDefstruct.ADC_Prescaler = ADC_Prescaler_Div2;                                   //PLCLK 8��Ƶ
	ADC_CommonInitTypeDefstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitTypeDefstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitTypeDefstruct);

	ADC_InitTypeDefstruct.ADC_Resolution = ADC_Resolution_12b;              
	ADC_InitTypeDefstruct.ADC_ScanConvMode = DISABLE;
	ADC_InitTypeDefstruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitTypeDefstruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);


	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_15Cycles);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	// ADC_SoftwareStartConv(ADC1);

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

	DMADataReady = RESET;
}


//***************************************************//
//  ��������: ��ʾģʽ 1
//  
//  ˵��: 128�㣬���߿��㽵��
//  
//***************************************************//
void DisplayMode_1(u8g2_t *u8g2_Data)
{
	u16 i;
	u8 High;

	for ( i = 0; i < SCREEN_LENGTH; i++)
	{
		//�����ԷŴ���Ҫ�Ŵ��Ƶ����
		High = (u8)(log10(i+3)*FFT_Display[i+1]/500);

		if( PointY[i] < High)
		{
			PointY[i] = High;

			if( PointY[i] > 63)
			{
				PointY[i] = 62;
			}
		}
		else
		{
			if(PointY[i]>=1)
			{
				PointY[i] -= 1;
			}
			else
			{
				PointY[i] = 0;
			}
		}
		u8g2_DrawVLine(u8g2_Data,i,0,High);
		u8g2_DrawPixel(u8g2_Data,i,PointY[i]);
	}
}

//***************************************************//
//  ��������: ��ʾģʽ 2
//  
//  ˵��: 64�㣬˫�߿��㽵��
//  
//***************************************************//
void DisplayMode_2(u8g2_t *u8g2_Data)
{
	u16 i;
	u8 High;

	for ( i = 0; i < SCREEN_LENGTH/2; i++)
	{
		//�����ԷŴ���Ҫ�Ŵ��Ƶ����
		// if(i<10)
		// {
		// 	High = (u8)(FFT_Display[i+1]/800);
		// }
		// else
		{
			High = (u8)(log10(i+3)*FFT_Display[i+1]/500);
		}

		if( PointY[i] < High)
		{
			PointY[i] = High;

			if( PointY[i] > 63)
			{
				PointY[i] = 62;
			}
		}
		else
		{
			if(PointY[i]>=1)
			{
				PointY[i] -=1;
			}
			else
			{
				PointY[i] =0;
			}
		}

		u8g2_DrawVLine(u8g2_Data,i*2,0,High);
		u8g2_DrawVLine(u8g2_Data,i*2+1,0,High);
		u8g2_DrawPixel(u8g2_Data,i*2,PointY[i]);
		u8g2_DrawPixel(u8g2_Data,i*2+1,PointY[i]);
	}
}

//***************************************************//
//  ��������: ��ʾģʽ 3
//  
//  ˵��: ָ����ʼλ�ã����߿��޵�
//  
//***************************************************//
void DisplayMode_3(u8g2_t *u8g2,u8 x)
{
	u16 i;
	u8 High;

	if(x >= SCREEN_LENGTH)
	{
		return;
	}

	for ( i = x; i < SCREEN_LENGTH ; i++)
	{
		//�����ԷŴ���Ҫ�Ŵ��Ƶ����
		High = (u8)log10(i-x)*FFT_Display[i-x]/500;
		u8g2_DrawVLine(u8g2,i,0,High);
	}
}


//***************************************************//
//  ��������: ��ʾģʽ 4
//  
//  ˵��: 128�㣬˫�߿�ˮƽ���ĶԳ�
//  
//***************************************************//
void DisplayMode_4(u8g2_t *u8g2)
{
	u16 i;
	u8 High;
	const u8 Wide = 3;

	for ( i = 0; i < SCREEN_LENGTH/Wide; i++)
	{

		High = (u8)(log(i+3)*FFT_Display[i+1]/500);

		if( PointY[i] < High)
		{
			PointY[i] = High;

			if( PointY[i] > 63)
			{
				PointY[i] = 62;
			}
		}
		else
		{
			if(PointY[i]>=1)
			{
				PointY[i] -=1;
			}
			else
			{
				PointY[i] = 0;
			}
		}

		u8g2_DrawVLine(u8g2,i*Wide,0,High);
		u8g2_DrawVLine(u8g2,i*Wide+1,0,High);
		u8g2_DrawVLine(u8g2,i*Wide+2,0,High);		
		u8g2_DrawPixel(u8g2,i*Wide,PointY[i]);
		u8g2_DrawPixel(u8g2,i*Wide+1,PointY[i]);
		u8g2_DrawPixel(u8g2,i*Wide+2,PointY[i]);
	}
}


//***************************************************//
//  ��������: ADC����FFT����
//  
//  ����: ��
//  
//  ����ֵ:��
//  
//  ˵��: ��
//  
//***************************************************//
void FFT_Process()
{
	u16 i;

	if( DMADataReady == SET)
	{
		//ת���ɸ�����ʽ,���ʵ��
		for ( i = 0; i < POINT; i++)
		{
			FFT_Data[i].Real = (float32_t)ADC_Data[i];
			FFT_Data[i].Image = 0;
		}

		//1024��FFT����
		arm_cfft_f32(&arm_cfft_sR_f32_len512,(float32_t *)FFT_Data,0,1);

		//ȡ��ֵ
		arm_cmplx_mag_f32((float32_t *)FFT_Data,FFT_Display,SCREEN_LENGTH);

		u8g2_DispalyFFT(&u8g2_Data,2);

	}
}


//***************************************************//
//  ��������: u8g2  FFT��ʾ
//  
//  ����: u8g2ָ��,��ʾģʽ
//  
//  ����ֵ:��
//  
//  ˵��: ��
//  
//***************************************************//
void u8g2_DispalyFFT(u8g2_t *u8g2,u8 Mode)
{
	if( DMADataReady == SET)
	{
		u8g2_ClearBuffer(u8g2);
		switch (Mode)
		{
			case 1:
				DisplayMode_1(u8g2);
				break;
			case 2:
				DisplayMode_2(u8g2);				
				break;
			case 3:
				DisplayMode_3(u8g2,60);				
				break;
			case 4:
				DisplayMode_4(u8g2);				
				break;		
			default:
				DisplayMode_1(u8g2);
				break;
		}
		DMADataReady = RESET;
		u8g2_SendBuffer(u8g2);
	}
}


void DMA2_Stream0_IRQHandler()
{
	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)  == SET )
	{
		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
		DMADataReady = SET;







	}
}

void TIM2_IRQHandler()
{
    if( TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

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
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);





	}
}
