#ifndef PID_H
#define PID_H

typedef struct 
{
	float SetSpeed;//定义设定值
	float ActualSpeed;//定义实际值
	float err;//定义偏差值
	float err_next;//定义上一个偏差值
	float err_last;//定义最上前的偏差值
	float Kp, Ki, Kd;//定义比例、积分、微分系数
}PID_t;


void PID_init(void );
float PID_RealTime(float speed);//参数为目标值




#endif






