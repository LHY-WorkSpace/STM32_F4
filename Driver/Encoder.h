#ifndef ENCODER_H
#define ENCODER_H
// #include "stm32f4xx.h"


typedef enum
{
    Encoder_UP,
    Encoder_DOWN

}Encoder_Dir_e;



typedef struct
{
    Encoder_Dir_e Dir;
    u16 Value;
}EnCoderInfo_t;



void EncoderInit(void);


#endif
