#ifndef  _INCLUDE_FILE_H_
#define  _INCLUDE_FILE_H_

//标准文件
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "math.h"
#include "stdio.h"
#include "DataType.h"
#include "SystemState.h"

//芯片驱动层
#include "Timer.h"
#include "usart.h"
#include "CODE_RUN_TIME.h"
#include "dac.h"
#include "adc.h"
#include "led.h"
#include "exti.h"
#include "sdio_sdcard.h"
#include "i2c.h"
#include "RTC.h"
#include "DMA.h"  
#include "pwm.h"
#include "RNG.h"
#include "lcd.h"
#include "XPT2046.h"
#include "KeyPad.h"


//器件驱动层
#include "AT24C08.h"
#include "MPU6050.h"
#include "DHT11.h"
#include "DS18B20.h"
#include "oled.h"
#include "SPI_FLASH.h"
#include "ESP8266.h"
// #include "lcd1602.h"
#include "HC_SR04.h"
#include "lcd.h"
#include "PID.h"
#include "ST7789.h"


// TRUE     使用
// FALSE    不使用
/**************************** RTOS ***************************************/
#define USE_RTOS    TRUE

/**************************** u8g2 ***************************************/
#define USE_U8G2    TRUE

/**************************** LVGL ***************************************/
#define USE_LVGL    TRUE

//应用层
#if (USE_RTOS == TRUE)
#include "../FreeRTOS/include/FreeRTOS.h"
#include "../include/task.h"
#include "../FreeRTOS/include/queue.h"
#include "../FreeRTOS/include/semphr.h"
#include "../FreeRTOS/FreeROS_Communication.h"
#endif

#include "../MPU6050DMP/inv_mpu.h"
#include "../MPU6050DMP/inv_mpu_dmp_motion_driver.h"


#include "../SD/diskio.h"	
#include "../SD/ff.h"	
#include "Protocol.H"
#include "TEST.h"
#include "FileOperate.h"



#include "../USB_lib/usbd_core.h"
#include "../USB_lib/usb_bsp.h"
#include "../USB_lib/usbd_usr.h"
#include "../USB_lib/usbd_msc_core.h"
#include "../USB_lib/usbd_desc.h"


#if (USE_LVGL == TRUE)
#include "../Module/LVGL/lvgl.h"
#include "../Module/LVGL/src/lvgl.h"

#endif

#if (USE_U8G2 == TRUE)
#include "../Module/u8g2_src/u8x8.h"
#include "../Module/u8g2_src/u8g2.h"
#include "../Module/u8g2_src/u8g2_UserGUI.h"
#endif


#include "easyflash.h"
#include "FFT.h"

#endif





















/**************************** extern value  ***************************************/
// extern u8 OLED_GRAM[8][128];























