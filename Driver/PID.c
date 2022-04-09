#include "IncludeFile.h"


PID_t pid;

void PID_init()
{
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	//�����������ֵ���Ӷ��ﵽ���Ч��
	pid.Kp = 0.1;
	pid.Ki = 0.1; 
	pid.Kd = 0.3;
}

//����ΪĿ��ֵ
float PID_RealTime(float speed)
{
	float incrementSpeed;
	pid.SetSpeed = speed;
	pid.err = pid.SetSpeed - pid.ActualSpeed;
    incrementSpeed = pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);//���������
	pid.ActualSpeed += incrementSpeed;
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	return pid.ActualSpeed;
}
