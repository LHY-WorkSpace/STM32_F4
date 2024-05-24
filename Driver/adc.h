#ifndef  ADC_H
#define  ADC_H

/*
            VBAT_MAX
            |
            R1
            |
            <------ VADC
            |
            R0
            |
            ADC_EN
*/

//电池最大电压
#define  VBAT_MAX   (4.2f)

// 参考电压
#define  VREF       (3.3f)

//R0 R1 填写等比例数据即可
#define  R0         (1.0f)  
#define  R1         (0.0f)

#define  BATTERY_CHECK_ENABLE         GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define  BATTERY_CHECK_DISABLE        GPIO_SetBits(GPIOC,GPIO_Pin_8)

void ADC_CTRL_IO_Init(void);
void ADC_UserInit(void);
float BatteryGetVolate(void);

#endif


  
