#include "IncludeFile.h"

//创建任务
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
// xTaskCreate( (TaskFunction_t)Task,"Task",堆栈大小(默认4倍),参数,优先级,句柄);



//队列
QueueHandle_t Queue_H;
BaseType_t Sta;
UBaseType_t MsgNum;
unsigned int Queue_Data;

void Queue_Test()
{
    //创建队列
    Queue_H = xQueueCreate(3,sizeof(Queue_Data));
    if( Queue_H == NULL)
    {
        //创建失败
    }

    //发送数据到队列
    Sta = xQueueSendToBack(Queue_H,(void *)&Queue_Data,0);
    if( Sta != pdPASS)
    {
         //操作失败
    }

    //查询队列中的数据个数
    MsgNum = uxQueueMessagesWaiting(Queue_H);

    //获取(读取后删除)
    Sta = xQueueReceive(Queue_H,(void *)&Queue_Data,portMAX_DELAY);
    if( Sta != pdPASS)
    {
        printf("RX Err !\n");
    }

/*
    1.创建邮箱
    QueueHandle_t xQueueCreate(1, UBaseType_t 单个元素大小)
    元素个数必须为1

    2.写入邮箱
    BaseType_t xQueueOverwrite(QueueHandle_t 邮箱句柄, const void *数据指针);

    3.读取邮箱
    BaseType_t xQueuePeek(QueueHandle_t 邮箱句柄, void *pvBuffer, TickType_t xTicksToWait );
    读取后不会删除数据

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
    2.启动定时器
    BaseType_t xTimerStart( TimerHandle_t 定时器句柄, TickType_t 等待时间 );

    3.停止定时器
    BaseType_t xTimerStop ( TimerHandle_t 定时器句柄, TickType_t 等待时间 );

    4.获取定时器名称
    const char * pcTimerGetName( TimerHandle_t 定时器句柄);

    5.获取定时器ID
    void * pvTimerGetTimerID ( TimerHandle_t 定时器句柄);

    6.定时器清零计数
    BaseType _t xTimerReset( TimerHandle_t 定时器句柄, TickType_t 等待时间);
    类似于喂狗

    7.修改定时器周期
    BaseType_t xTimerChangePeriod( TimerHandle_t 定时器句柄, TickType_t 周期, TickType_t 等待时间);
*/

}











































































