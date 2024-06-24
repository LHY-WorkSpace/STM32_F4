#ifndef FOC_H
#define FOC_H


// �����ڼ���ֵ  = 168*1000/CLK_DIV/PWM_FRQUENCE
// ���鲻����20khz��������������
#define FOC_TIMER           (TIM1)
#define TIME_CLK            (168)//��ʱ��ʱ��:Mhz
#define CLK_DIV             (2)//�ܱ�72����,
#define PWM_FRQUENCE        (120)//Khz
//���������
#define POLE_PAIR           (7)
//����ѹ
#define VCC_MOTOR	        (10.0f)
//PWM ͨ������3��6·
#define PWM_CHANNEL         (3)

#define SQRT_3      (1.7320508075f)//sqrt(3)/
#define SQRT_3_2    (0.8660254037f)//sqrt(3)/2

#define ValueLimit(Val,Min,Max) ((Val)<(Min)?(Min):((Val)>(Max)?(Max):(Val)))

#define FOC_DISABLE     GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define FOC_ENABLE      GPIO_SetBits(GPIOB,GPIO_Pin_12)


typedef enum
{
    UA_Phase,
    UB_Phase,
    UC_Phase,
    U_PhaseMax,
}U_Phase_e;


void PWM_Init(u16 Period,u16 PluseWide);
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide);  //��������(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod);  //��������(us)


#endif
