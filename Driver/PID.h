#ifndef PID_H
#define PID_H

typedef struct 
{
	float SetSpeed;//�����趨ֵ
	float ActualSpeed;//����ʵ��ֵ
	float err;//����ƫ��ֵ
	float err_next;//������һ��ƫ��ֵ
	float err_last;//��������ǰ��ƫ��ֵ
	float Kp, Ki, Kd;//������������֡�΢��ϵ��
}PID_t;


void PID_init(void );
float PID_RealTime(float speed);//����ΪĿ��ֵ




#endif






