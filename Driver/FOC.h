#ifndef FOC_H
#define FOC_H








// 7 pair(*2) magnet
// 6 pair(*2) coil
#define POLE_PAIR	(6)
#define Uq          (6.0f)
#define Ud          (0.0f)
#define VCC_MOTOR	(12.0f)
#define PWM_FREQ    (20*1000)//HZ

#define MOTER_1_TIMER    (TIM1)//HZ
#define MOTER_2_TIMER    (TIM8)//HZ



typedef enum
{
    UA_Phase,
    UB_Phase,
    UC_Phase,
    U_PhaseMax,
}U_Phase_e;


void PWM_Init(u16 Period,u16 PluseWide);
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide);  //设置脉宽(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod);  //设置周期(us)


#endif
