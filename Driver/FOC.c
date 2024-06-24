#include "IncludeFile.h"


static PID_t PositionPID;
static u16  TIM_PeriodVal = TIME_CLK*1000/CLK_DIV/PWM_FRQUENCE;




// TIMER_1
// CH_1 : ��-PE9	PE8-����
// CH_2 : ��-PE11	PE10-����
// CH_3 : ��-PE13	PE12-����

void FOC_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	GPIO_InitTypeDef FOC_IO;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitsruc;
	TIM_BDTRInitTypeDef TIM_BDTRInit;

	FOC_IO.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;
	FOC_IO.GPIO_Mode=GPIO_Mode_AF;
	FOC_IO.GPIO_Speed=GPIO_Speed_100MHz;
	FOC_IO.GPIO_OType=GPIO_OType_PP;
	FOC_IO.GPIO_PuPd=GPIO_PuPd_NOPULL;

#if(PWM_CHANNEL == 6)
	FOC_IO.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12;
	FOC_IO.GPIO_Mode=GPIO_Mode_AF;
	FOC_IO.GPIO_Speed=GPIO_Speed_100MHz;
	FOC_IO.GPIO_OType=GPIO_OType_PP;
	FOC_IO.GPIO_PuPd=GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
#endif

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	GPIO_Init(GPIOE,&FOC_IO);
	
	TIM_TimeBaseInitsruc.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitsruc.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitsruc.TIM_Prescaler=CLK_DIV-1;	   
	TIM_TimeBaseInitsruc.TIM_Period=TIM_PeriodVal-1;	
	TIM_TimeBaseInit(FOC_TIMER,&TIM_TimeBaseInitsruc);
	
#if(PWM_CHANNEL == 3)
	TIM_OCInitTypestuc.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OutputNState = TIM_OutputNState_Disable;//����ͨ���ر�
	TIM_OCInitTypestuc.TIM_Pulse = 0
	TIM_OCInitTypestuc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypestuc.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypestuc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitTypestuc.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
#else
	TIM_OCInitTypestuc.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OutputNState = TIM_OutputNState_Enable;//����ͨ��ʹ��
	TIM_OCInitTypestuc.TIM_Pulse = 0
	TIM_OCInitTypestuc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitTypestuc.TIM_OCNPolarity = TIM_OCPolarity_High;//��ͬʱΪ��������
	TIM_OCInitTypestuc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitTypestuc.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_BDTRInit.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTRInit.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTRInit.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInit.TIM_DeadTime = 0x40;// ÿ����0x40��ʱ������500ns
	TIM_BDTRInit.TIM_Break = TIM_Break_Disable;
	TIM_BDTRInit.TIM_BreakPolarity = TIM_BreakPolarity_High;//����������ļ���
	TIM_BDTRInit.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(FOC_TIMER,&TIM_BDTRInit);
#endif

	TIM_OC1Init(FOC_TIMER,&TIM_OCInitTypestuc);
	TIM_OC2Init(FOC_TIMER,&TIM_OCInitTypestuc);
	TIM_OC3Init(FOC_TIMER,&TIM_OCInitTypestuc);

	TIM_OC1PreloadConfig(FOC_TIMER,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(FOC_TIMER,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(FOC_TIMER,TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(FOC_TIMER,ENABLE);
	TIM_ARRPreloadConfig(FOC_TIMER,ENABLE);
	TIM_Cmd(FOC_TIMER,ENABLE);
}



//��������(us)
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide)
{
	TIMx->CCR1 = PluseWide-1;
}
//��������(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod)
{
	TIMx->ARR = PlusePeriod-1;
}


// ����ռ�ձ�(%)
// PluseWide = 10 : 10%
// Ч������ʱ���ɵ��� Ux��CCRx�Ķ�Ӧ��ϵ
void PWM_SetDuty(u8 Phase ,u8 PluseWide)
{
    switch (Phase)
    {
        case UA_Phase:
            FOC_TIMER->CCR1 = TIM_PeriodVal/100*PluseWide-1;
            break;
         case UB_Phase:
            FOC_TIMER->CCR2 = TIM_PeriodVal/100*PluseWide-1;
            break;
        case UC_Phase:
            FOC_TIMER->CCR3 = TIM_PeriodVal/100*PluseWide-1;
            break;       
        default:
            break;
    }
}

//���Ƕ�
float ElectricalAngle(float shaft_angle, int pole_pairs) 
{
  return (shaft_angle * (float)pole_pairs);
}

//�Ƕȹ�һ��
// ���ƽǶ�[0 - 360]
float AngleLimit(float Input) 
{
    float Tmp;
    Tmp = fmod(Input,360.0);
    if( Tmp < 0.0)
    {
       Tmp += 360.0;
    }
    return Tmp;
}


void SIN_CTL(float Uq,float Ud, float angle_el) 
{
    float Ua,Ub,Uc;
    float Ualpha,Ubeta;
    float SinVal,CosVal;

    // ��0��360��֮��ĽǶȹ�һ��
    // ֻ����ʹ�� _sin�� _cos ���ƺ���ʱ����Ҫ
    angle_el = AngleLimit(angle_el);
    // ����PWM����
    // ���ɿ�+�����˱任
    SinVal = FastSin(DEGTORAD(angle_el));
    CosVal = FastCos(DEGTORAD(angle_el));

    // ���ɿ˱�
    Ualpha = Ud * CosVal - Uq * SinVal; 
    Ubeta =  Ud * SinVal + Uq * CosVal; 

    // �����˱任
    Ua = Ualpha + VCC_MOTOR/2;
    Ub = -0.5 * Ualpha  + SQRT_3_2 * Ubeta + VCC_MOTOR/2;
    Uc = -0.5 * Ualpha - SQRT_3_2 * Ubeta + VCC_MOTOR/2;

    PWM_SetDuty(UA_Phase,(uint8_t)(Ua*100/VCC_MOTOR));
    PWM_SetDuty(UB_Phase,(uint8_t)(Ub*100/VCC_MOTOR));
    PWM_SetDuty(UC_Phase,(uint8_t)(Uc*100/VCC_MOTOR));
}


void SVPWM_CTL(float Uq, float Ud,float angle_el) 
{
    float Uout;
    float Ua,Ub,Uc;
	if(Ud)
	{ 
		Uout = _sqrt(Ud*Ud + Uq*Uq) / VCC_MOTOR;
		angle_el = AngleLimit(angle_el + atan2(Uq, Ud));
	}
	else
	{
		Uout = Uq / VCC_MOTOR;
		angle_el = AngleLimit(angle_el + 90.0f);
	}

      // �ҵ�����Ŀǰ����������
      int sector = floor(angle_el / 60.0f) + 1;
      // ����ռ�ձ�
      float T1 = SQRT_3*FastSin(DEGTORAD(sector*60.0f - angle_el))* Uout;
      float T2 = SQRT_3*FastSin(DEGTORAD(angle_el - (sector-1.0)*60.0f)) * Uout;
      // �����汾
      // �Ե�ѹ��ԴΪ����/2
      float T0 = 1 - T1 - T2;
      // �͵�Դ��ѹ������0
      //float T0 = 0;

      // ����ռ�ձȣ�ʱ�䣩
      float Ta,Tb,Tc; 
      switch(sector)
      {
        case 1:
          Ta = T1 + T2 + T0/2;
          Tb = T2 + T0/2;
          Tc = T0/2;
          break;
        case 2:
          Ta = T1 +  T0/2;
          Tb = T1 + T2 + T0/2;
          Tc = T0/2;
          break;
        case 3:
          Ta = T0/2;
          Tb = T1 + T2 + T0/2;
          Tc = T2 + T0/2;
          break;
        case 4:
          Ta = T0/2;
          Tb = T1+ T0/2;
          Tc = T1 + T2 + T0/2;
          break;
        case 5:
          Ta = T2 + T0/2;
          Tb = T0/2;
          Tc = T1 + T2 + T0/2;
          break;
        case 6:
          Ta = T1 + T2 + T0/2;
          Tb = T0/2;
          Tc = T1 + T0/2;
          break;
        default:
         // ���ܵĴ���״̬
          Ta = 0;
          Tb = 0;
          Tc = 0;
      }

    // �������ѹ������
    Ua = Ta*VCC_MOTOR;
    Ub = Tb*VCC_MOTOR;
    Uc = Tc*VCC_MOTOR;

    PWM_SetDuty(UA_Phase,(uint8_t)(Ua*100/VCC_MOTOR));
    PWM_SetDuty(UB_Phase,(uint8_t)(Ub*100/VCC_MOTOR));
    PWM_SetDuty(UC_Phase,(uint8_t)(Uc*100/VCC_MOTOR));
}

void FocOpenLoop_Speed(float Speed)
{
  float UqVal = 1.0;
  static float angtmp = 0.0f;
  angtmp = AngleLimit(angtmp+Speed);  
  SIN_CTL(UqVal,0,ElectricalAngle(angtmp,POLE_PAIR));
  Delay_ms(5);
}

float G_P = 0.03;
float G_I = 0.0;
float Tarang = 0.0;
float G_D = 0.0;
float MAX = 2.0;
void FocCloseLoop_Position(float Target)
{
  float angtmp = 0.0f;
  float Angle = 0.0f;  
  float UqTmp;
  float DIR = 1.0;


    PID_Change_Kp(&PositionPID,G_P);
    PID_Change_Ki(&PositionPID,G_I);
    PID_Change_Kd(&PositionPID,G_D);
    PID_SetTarget(&PositionPID,Target);




  Angle = AS5600_Angle(ANGLE_TURN_MODE);
  printf("FOC:%.1f,%.1f\n",Target,Angle);
  angtmp = AngleLimit(Angle);

  Angle = PID_Process(&PositionPID,Angle);


  Angle =  ValueLimit(Angle,-MAX,MAX);
  UqTmp = ElectricalAngle(angtmp,POLE_PAIR)*DIR;
  UqTmp = AngleLimit(UqTmp);

  SIN_CTL(Angle,0,UqTmp);
  // SVPWM_CTL(Angle,0,UqTmp);
}


void Foc_CTL()
{
    TickType_t Time;
    Time = xTaskGetTickCount();

    while (1)
    {
		FocCloseLoop_Position(Tarang);
		// FocOpenLoop_Speed(Tarang);
		vTaskDelayUntil(&Time,5/portTICK_PERIOD_MS);
    }
	vTaskDelete(NULL);
}

























































































// // ������任+��������任 ��ʽ���󣡣�������
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


