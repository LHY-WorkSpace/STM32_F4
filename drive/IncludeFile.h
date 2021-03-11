#ifndef  _INCLUDE_FILE_H_
#define  _INCLUDE_FILE_H_

//标准文件
#include "stm32f4xx.h"
#include "string.h"
#include "stdint.h"
#include "arm_math.h"
#include "math.h"
#include "stdio.h"
#include "SystemState.h"


//驱动层
#include "delay.h"
#include "usart.h"
#include "CODE_RUN_TIME.h"
#include "dac.h"
#include "adc.h"
#include "led.h"
#include "exti.h"
// #include "sd.h"
#include "sdio_sdcard.h"
#include "i2c.h"
#include "RTC.h"
#include "AT24C08.h"
#include "MPU6050.h"
#include "DHT11.h"
#include "ds18b20.h"
#include "oled.h"
#include "DMA.h"  
#include "pwm.h"
#include "RNG.h"
//#include "ESP8266.h"
#include "lcd1602.h"

//应用层
#include "FreeRTOS.h"
#include "task.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "diskio.h"	
#include "GUI.H"

#include "TEST.h"

#endif

extern u8 OLED_GRAM[8][128];
extern u32 Radom;
extern STM32_Time_t STM32_Time;

