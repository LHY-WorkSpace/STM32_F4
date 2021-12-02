#ifndef  DATATYPE_H
#define  DATATYPE_H

typedef union 
{
    u8  B08[2];
    u16 B16;
}B16_B08;

typedef union 
{
    u8  B08[4];
    u32 B32;
}B32_B08;

typedef union 
{
    u16 B16[2];
    u32 B32;
}B32_B16;


#endif






