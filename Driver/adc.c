#include "IncludeFile.h"

//***************************************************//
//  ��������: ��ؼ�⿪��
//  
//  ����: PowerState_n
//  
//  ����ֵ:��
//  
//  ˵��: ����Ϳ�����⣬����߹رռ��
//  
//***************************************************//
void ADC_CTRL_IO_Init()
{
	GPIO_InitTypeDef GPIOB_Initstruc;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIOB_Initstruc.GPIO_Pin = GPIO_Pin_8;                       
	GPIOB_Initstruc.GPIO_Mode = GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType = GPIO_OType_OD;
	GPIOB_Initstruc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&GPIOB_Initstruc);

	BATTERY_CHECK_DISABLE;
}

//***************************************************//
//  ��������: ��ؼ��ADC��ʼ��
//  
//  ����: ��
//  
//  ����ֵ:��
//  
//  ˵��: ��
//  
//***************************************************//
void ADC_UserInit()
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


	ADC_CommonInitTypeDefstruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitTypeDefstruct.ADC_Prescaler=ADC_Prescaler_Div8;                                   //PLCLK 8��Ƶ
	ADC_CommonInitTypeDefstruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitTypeDefstruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	
	ADC_CommonInit(&ADC_CommonInitTypeDefstruct);
	
	ADC_InitTypeDefstruct.ADC_Resolution=ADC_Resolution_12b;              
	ADC_InitTypeDefstruct.ADC_ScanConvMode=DISABLE;
	ADC_InitTypeDefstruct.ADC_ContinuousConvMode=DISABLE;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitTypeDefstruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion=1;
	
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);

	ADC_Cmd(ADC1,ENABLE);
	//ADC_TempSensorVrefintCmd(ENABLE);

}

//***************************************************//
//  ��������: ����ADת��
//  
//  ����: 
//  
//  ����ֵ: u16 ADֵ
//  
//  ˵��: ��
//  
//***************************************************//
static u16 ADC_GetVal()        
{
	u8 time=0;
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);	
	while( !ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) )
	{
		Delay_us(2);
		time++;
		if(time >= 10)
		{
			return 0;
		}
	}
	return ADC_GetConversionValue(ADC1);
}

//***************************************************//
//  ��������: ��ȡ��ص�ѹ
//  
//  ����: ��
//  
//  ����ֵ: float С��
//  
//  ˵��: ��
//  
//***************************************************//
float BatteryGetVolate()
{ 
	float Value,V_ADC;

	BATTERY_CHECK_ENABLE;

	Value = ( VBAT_MAX * R0 )/ ( R0 + R1 );
	V_ADC = ( Value * (float)ADC_GetVal() / 4096.0f );
	Value = V_ADC * ( R0 + R1 ) / R0;

	BATTERY_CHECK_DISABLE;
	
	return	Value;
}


//***************************************************//
//  ��������: �ر�ADC �������й�����
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: Ŀǰδ��ɣ�������������
//  
//***************************************************//
void PowerDown_Battery()
{ 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,DISABLE);
}














