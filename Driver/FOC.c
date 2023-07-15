#include "IncludeFile.h"






// TIMER_1
// CH_1 : PE9
// CH_2 : PE11
// CH_3 : PE12

// TIMER_8
// CH_1 : PE9
// CH_2 : PE11
// CH_3 : PE12



void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);


void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);





void Moter1_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	GPIO_InitTypeDef FOC_IO;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitsruc;
	
	FOC_IO.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;
	FOC_IO.GPIO_Mode=GPIO_Mode_AF;
	FOC_IO.GPIO_Speed=GPIO_Speed_100MHz;
	FOC_IO.GPIO_OType=GPIO_OType_PP;
	FOC_IO.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&FOC_IO);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);

	TIM_TimeBaseInitsruc.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitsruc.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitsruc.TIM_Prescaler=168-1;			// APB2=42Mhz     
	TIM_TimeBaseInitsruc.TIM_Period=50-1;				//周期20ms
	TIM_TimeBaseInit(MOTER_1_TIMER,&TIM_TimeBaseInitsruc);
	

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC3Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OC1PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(MOTER_1_TIMER,ENABLE);
	TIM_Cmd(MOTER_1_TIMER,ENABLE);
}


void Moter2_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	GPIO_InitTypeDef FOC_IO;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitsruc;
	
	FOC_IO.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;
	FOC_IO.GPIO_Mode=GPIO_Mode_AF;
	FOC_IO.GPIO_Speed=GPIO_Speed_100MHz;
	FOC_IO.GPIO_OType=GPIO_OType_PP;
	FOC_IO.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&FOC_IO);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);

	TIM_TimeBaseInitsruc.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitsruc.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitsruc.TIM_Prescaler=168-1;			// APB2=42Mhz     
	TIM_TimeBaseInitsruc.TIM_Period=50-1;				//周期20ms
	TIM_TimeBaseInit(MOTER_1_TIMER,&TIM_TimeBaseInitsruc);
	

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC3Init(MOTER_1_TIMER,&TIM_OCInitTypestuc);

	TIM_OC1PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(MOTER_1_TIMER,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(MOTER_1_TIMER,ENABLE);
	TIM_Cmd(MOTER_1_TIMER,ENABLE);
}






//设置脉宽(us)
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide)
{
	TIMx->CCR1 = PluseWide-1;
}
//设置周期(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod)
{
	TIMx->ARR = PlusePeriod-1;
}


void SetPWMDuty(TIM_TypeDef* TIMx,uint8_t Phase,uint8_t Value)
{
    if( Value > 100)
    {
        return;
    }

	if(Value == 0 )
	{
		Value =1;
	}

	switch (Phase)
	{
		case UA_Phase:
			TIMx->CCR1 = Value-1;
			break;
		case UB_Phase:
			TIMx->CCR1 = Value-1;
			break;
		case UC_Phase:
			TIMx->CCR1 = Value-1;
			break;
		default:
			break;
	}
}



//求电角度
float ElectricalAngle(float shaft_angle, int pole_pairs) 
{
  return (shaft_angle * pole_pairs);
}

//角度归一化
float LimitAngle(float shaft_angle) 
{
  return (float)((int)shaft_angle % 360);
}

//逆变换
void N_Transform(float uq, float ud, float Angle)
{
    float Ua,Ub,Uc;
    float Ualpha,Ubeta; 

    //帕克逆变换
    Ualpha =  -uq*arm_sin_f32(DEGTORAD(Angle)); 
    Ubeta =   uq*arm_cos_f32(DEGTORAD(Angle)); 

    // 克拉克逆变换
    Ua = Ualpha + VCC_MOTOR/2;
    Ub = (sqrt(3)*Ubeta-Ualpha)/2 + VCC_MOTOR/2;
    Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + VCC_MOTOR/2;

    SetPWMDuty(UA_Phase,(uint8_t)(Ua*100/VCC_MOTOR));
    SetPWMDuty(UB_Phase,(uint8_t)(Ub*100/VCC_MOTOR));
    SetPWMDuty(UC_Phase,(uint8_t)(Uc*100/VCC_MOTOR));
    //printf("Angle:%.2f Ia:%d Ib:%d Ic:%d\r\n",Angle,(uint8_t)(Ua*100/VCC_MOTOR),(uint8_t)(Ub*100/VCC_MOTOR),(uint8_t)(Uc*100/VCC_MOTOR));

}


u8 Addval=10;
void Foc_CTL()
{
	static float Angle  = 1.0f;
    TickType_t Time;
    float angtmp;

    Time = xTaskGetTickCount();

    while (1)
    {
		Angle += (float)Addval;
		// Angle = (float)AS5600Angle + 1.0;
        
        angtmp = LimitAngle(Angle);
        angtmp = ElectricalAngle(angtmp,7);
        angtmp = LimitAngle(angtmp);

        N_Transform(Uq,0,angtmp);

		if(Angle >= 360.0f)
		{
			Angle = 0.0f;
		}
		vTaskDelayUntil(&Time,1/portTICK_PERIOD_MS);
    }
	vTaskDelete(NULL);
}

























































































// // 帕克逆变换+克拉克逆变换 公式有误！！！！！
// float IA(float Angle)
// {
// 	float Temp;
// 	Temp = Ud * arm_cos_f32(DEGTORAD(Angle)) + Uq * arm_sin_f32(DEGTORAD(Angle));
// 	return Temp;
// }

// float IB(float Angle)
// {
// 	float Temp;
// 	Temp = Uq *( 0.866f * arm_cos_f32(DEGTORAD(Angle)) + 0.5f * arm_sin_f32(DEGTORAD(Angle)) ) + Ud * (0.866f * arm_sin_f32(DEGTORAD(Angle)) - 0.5f * arm_cos_f32(DEGTORAD(Angle)));
// 	return Temp;
// }

// float IC(float Angle)
// {
// 	float Temp;
// 	Temp = Uq *( 0.5f * arm_sin_f32(DEGTORAD(Angle)) - 0.866f * arm_cos_f32(DEGTORAD(Angle))) + Ud * ( 0.5f * arm_cos_f32(DEGTORAD(Angle)) + 0.866f * arm_sin_f32(DEGTORAD(Angle)) );
// 	return Temp;
// }


