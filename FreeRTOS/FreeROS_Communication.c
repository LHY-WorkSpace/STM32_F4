#include "IncludeFile.h"

//��������
TaskHandle_t Task_H;
void Task( void *Para)
{
	TickType_t Time;
	Time=xTaskGetTickCount();
	while(1)
	{	
        ///
		vTaskDelayUntil(&Time,1500/portTICK_PERIOD_MS);
	}

}
//xTaskCreate( (TaskFunction_t)Task,"Task",500,NULL,9,&Task_H);
// xTaskCreate( (TaskFunction_t)Task,"Task",��ջ��С(Ĭ��4��),����,���ȼ�,���);



//����
QueueHandle_t Queue_H;
BaseType_t Sta;
UBaseType_t MsgNum;
unsigned int Queue_Data;

void Queue_Test()
{
    //��������
    Queue_H = xQueueCreate(3,sizeof(Queue_Data));
    if( Queue_H == NULL)
    {
        //����ʧ��
    }

    //�������ݵ�����
    Sta = xQueueSendToBack(Queue_H,(void *)&Queue_Data,0);
    if( Sta != pdPASS)
    {
         //����ʧ��
    }

    //��ѯ�����е����ݸ���
    MsgNum = uxQueueMessagesWaiting(Queue_H);

    //��ȡ(��ȡ��ɾ��)
    Sta = xQueueReceive(Queue_H,(void *)&Queue_Data,portMAX_DELAY);
    if( Sta != pdPASS)
    {
        printf("RX Err !\n");
    }

/*
    1.��������
    QueueHandle_t xQueueCreate(1, UBaseType_t ����Ԫ�ش�С)
    Ԫ�ظ�������Ϊ1

    2.д������
    BaseType_t xQueueOverwrite(QueueHandle_t ������, const void *����ָ��);

    3.��ȡ����
    BaseType_t xQueuePeek(QueueHandle_t ������, void *pvBuffer, TickType_t xTicksToWait );
    ��ȡ�󲻻�ɾ������

*/
}



TimerHandle_t SW_Timer_H;


void Timer_cb(TimerHandle_t xTimer)
{

}


void SW_Timer()
{
    SW_Timer_H = xTimerCreate("Timer",pdMS_TO_TICKS(500),pdTRUE,(void *)1,Timer_cb);

/*
    2.������ʱ��
    BaseType_t xTimerStart( TimerHandle_t ��ʱ�����, TickType_t �ȴ�ʱ�� );

    3.ֹͣ��ʱ��
    BaseType_t xTimerStop ( TimerHandle_t ��ʱ�����, TickType_t �ȴ�ʱ�� );

    4.��ȡ��ʱ������
    const char * pcTimerGetName( TimerHandle_t ��ʱ�����);

    5.��ȡ��ʱ��ID
    void * pvTimerGetTimerID ( TimerHandle_t ��ʱ�����);

    6.��ʱ���������
    BaseType _t xTimerReset( TimerHandle_t ��ʱ�����, TickType_t �ȴ�ʱ��);
    ������ι��

    7.�޸Ķ�ʱ������
    BaseType_t xTimerChangePeriod( TimerHandle_t ��ʱ�����, TickType_t ����, TickType_t �ȴ�ʱ��);
*/

}











































































