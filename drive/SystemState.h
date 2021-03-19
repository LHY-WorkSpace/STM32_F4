#ifndef   _SYSTEMSTATE_H_
#define   _SYSTEMSTATE_H_


//�豸������20��
#define DEVICES_NUM       20


/*
�豸״̬ö���б�ÿ���豸���֧��8���Զ���״̬
*/
typedef enum 
{
    F_OLED_Init_OK,
    F_OLED_Option_OK,
    F_OLED_Parameter_OK,
    F_OLED_DataReady_OK

}Dev_OLEDState_n;

typedef enum 
{
    F_RTC_Init_OK,
    F_RTC_GetTime_OK,
    F_RTC_GetDate_OK,
    F_RTC_SetTime_OK,
    F_RTC_SetDate_OK,

}Dev_RTCState_n;

typedef enum 
{
    F_SD_Init_OK,
    F_SD_WriteData_OK,
    F_SD_ReadData_OK,

}Dev_SDState_n;

typedef enum 
{
    F_AT24C_Init_OK,
    F_AT24C_WriteData_OK,
    F_AT24C_ReadData_OK,

}Dev_AT24CState_n;

typedef enum 
{
    F_MPU6050_Init_OK,
    F_MPU6050_WriteData_OK,
    F_MPU6050_ReadData_OK,

}Dev_MPU6050State_n;




/*
�豸ö���б��������� DEVICES_NUM ʱ�����޸� DEVICES_NUM ��ֵ
*/
typedef enum 
{
    Dev_OLED,
    Dev_RTC,
    Dev_SD,
    Dev_AT24C,
    Dev_MPU6050,
        

}SystemState_n;





u8   System_GetState(u8 Device,u8 State);
void System_SetState(u8 Device,u8 State);
void System_ResetState(u8 Device,u8 State);


#endif
