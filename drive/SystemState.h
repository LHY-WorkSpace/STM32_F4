#ifndef   SYSTEMSTATE_H
#define   SYSTEMSTATE_H


typedef enum 
{
    F_OLED_Init_Error,
    F_OLED_Option_Error,
    F_OLED_Parameter_Error

}OLEDState_n;


typedef enum 
{
    F_RTC_Init_Error,




}RTCState_n;



typedef struct 
{
    OLEDState_n   OLEDState;
    RTCState_n    RTCState;


}SystemState_t;






void System_GetState(u16 State);
void System_SetState(u16 State);
void System_ResetState(u16 State);

#endif
