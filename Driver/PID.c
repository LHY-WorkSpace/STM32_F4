#include "IncludeFile.h"




static PID_t pid;


//***************************************************//
//  ��������: PID������ʼ��
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void PID_Init(PID_t *PID_Data)
{
	PID_Data->SetValue = 0.0;
	PID_Data->ActualValue = 0.0;
	PID_Data->err = 0.0;
	PID_Data->err_last = 0.0;
	PID_Data->err_next = 0.0;
	//�����������ֵ���Ӷ��ﵽ���Ч��
	PID_Data->Kp = 0.1;
	PID_Data->Ki = 0.1; 
	PID_Data->Kd = 0.3;
}

//***************************************************//
//  ��������: �޸�PIDϵ��
//  
//  ����: P I D ϵ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
void PID_Change_Kp(PID_t *PID_Data, float k)
{
	PID_Data->Kp = k;
}

void PID_Change_Ki(PID_t *PID_Data, float k)
{
	PID_Data->Ki = k; 
}

void PID_Change_Kd(PID_t *PID_Data, float k)
{
	PID_Data->Kd = k;
}

//***************************************************//
//  ��������: PID������
//  
//  ����:�趨ֵ
//  
//  ����ֵ: ��ǰֵ
//  
//  ˵��: ��
//  
//***************************************************//
float PID_Process(PID_t *PID_Data,float Target)
{
	float incrementValue;

	PID_Data->SetValue = Target;
	PID_Data->err = PID_Data->SetValue - PID_Data->ActualValue;
    incrementValue = PID_Data->Kp*(PID_Data->err - PID_Data->err_next) + PID_Data->Ki*PID_Data->err + PID_Data->Kd*(PID_Data->err - 2 * PID_Data->err_next + PID_Data->err_last);//���������
	PID_Data->ActualValue += incrementValue;
	PID_Data->err_last = PID_Data->err_next;
	PID_Data->err_next = PID_Data->err;
	return PID_Data->ActualValue;
}
