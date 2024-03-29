#include"IncludeFile.h"



void DAC_UserInit()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);

	GPIO_InitTypeDef   GPIO_InitTypeDefstruct;
	DAC_InitTypeDef    DAC_InitTypeDefstruct;
		
	GPIO_InitTypeDefstruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitTypeDefstruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitTypeDefstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitTypeDefstruct.GPIO_PuPd=GPIO_PuPd_DOWN;           //输出时配置，输入时无需配置


	GPIO_Init(GPIOA,&GPIO_InitTypeDefstruct);
	
	DAC_InitTypeDefstruct.DAC_Trigger=DAC_Trigger_None;
	DAC_InitTypeDefstruct.DAC_WaveGeneration=DAC_WaveGeneration_None;
	DAC_InitTypeDefstruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitTypeDefstruct.DAC_OutputBuffer=DAC_OutputBuffer_Disable;

	DAC_Init(DAC_Channel_1,&DAC_InitTypeDefstruct);

	DAC_Cmd(DAC_Channel_1,ENABLE);
}



void DAC_Out(float vol)
{
	u16 DAC_Val;
	DAC_Val= (u16)(vol*4096.0f/VCC);
	DAC_SetChannel1Data(DAC_Align_12b_R,DAC_Val);
}




