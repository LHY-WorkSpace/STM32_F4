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
            GND
*/
//填写等比例数据即可
#define  VBAT_MAX   (4.2f)
#define  R0         (1.0f)  
#define  R1         (0.0f)


void ADC_UserInit(void);
u16 ADC_GetVal(void);
float BatteryGetVolate(void);
#endif


  
