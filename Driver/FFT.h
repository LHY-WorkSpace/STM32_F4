#ifndef FFT_H_
#define FFT_H_

typedef struct
{
    float32_t Real;
    float32_t Image;
}FFT_Data_t;
 







void FFT_Init(void);
void u8g2_DispalyFFT(u8g2_t *u8g2,u8 Mode);
void FFT_Process(void);
#endif



