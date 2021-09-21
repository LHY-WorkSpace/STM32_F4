/**
 * @file XPT2046.h
 *
 */

#ifndef XPT2046_H
#define XPT2046_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "IncludeFile.h"
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define LV_DRV_INDEV_INCLUDE     <stdint.h>             /*Dummy include by default*/
#define LV_DRV_INDEV_RST(val)    /*pin_x_set(val)*/     /*Set the reset pin to 'val'*/
#define LV_DRV_INDEV_IRQ_READ    1 /*pn_x_read()*/      /*Read the IRQ pin*/

/*---------
 *  SPI
 *---------*/
#define LV_DRV_INDEV_SPI_CS(val)            XPT2046_CS(val)                 /*spi_cs_set(val)*/     /*Set the SPI's Chip select to 'val'*/
#define LV_DRV_INDEV_SPI_XCHG_BYTE(data)    XPT2046_SendData(data)          /*spi_xchg(val)*/     /*Write 'val' to SPI and give the read value*/



#define XPT2046_SPI_SEL      GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define XPT2046_SPI_NO_SEL   GPIO_ResetBits(GPIOA,GPIO_Pin_4)




/*--------------
 *    XPT2046
 *--------------*/

#  define XPT2046_HOR_RES     240
#  define XPT2046_VER_RES     320

//可能是XY最大和最小的AD值
#  define XPT2046_X_MIN       210
#  define XPT2046_Y_MIN       170
#  define XPT2046_X_MAX       3900
#  define XPT2046_Y_MAX       3800

#  define XPT2046_AVG         5
#  define XPT2046_X_INV       0
#  define XPT2046_Y_INV       0
#  define XPT2046_XY_SWAP     1

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void XPT2046_Init(void);
u8 XPT2046_Read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
void xpt2046_corr(int16_t * x, int16_t * y);
void xpt2046_avg(int16_t * x, int16_t * y);
/**********************
 *      MACROS
 **********************/

#endif /* USE_XPT2046 */

#ifdef __cplusplus
} /* extern "C" */
#endif


