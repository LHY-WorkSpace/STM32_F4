/**
  ******************************************************************************
  * @file    usbd_usr.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   This file includes the user application layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "usbd_usr.h"
#include <stdio.h>
#include "IncludeFile.h"
/** @addtogroup USBD_USER
  * @{
  */

/** @addtogroup USBD_MSC_DEMO_USER_CALLBACKS
  * @{
  */

/** @defgroup USBD_USR 
  * @brief    This file includes the user application layer
  * @{
  */

/** @defgroup USBD_USR_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_USR_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_USR_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_USR_Private_Variables
  * @{
  */
/* Points to the DEVICE_PROP structure of current device */
/* The purpose of this register is to speed up the execution */

USBD_Usr_cb_TypeDef USR_cb = {
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,

  USBD_USR_DeviceConnected,
  USBD_USR_DeviceDisconnected,
};

/**
  * @}
  */

/** @defgroup USBD_USR_Private_Constants
  * @{
  */

#define USER_INFORMATION1  (uint8_t*)"INFO : Single Lun configuration"
#define USER_INFORMATION2  (uint8_t*)"INFO : microSD is used"
/**
  * @}
  */



/** @defgroup USBD_USR_Private_FunctionPrototypes
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_USR_Private_Functions
  * @{
  */

/**
* @brief  Displays the message on LCD on device lib initialization
* @param  None
* @retval None
*/
void USBD_USR_Init(void)
{
//   /* Initialize LEDs */
//   STM_EVAL_LEDInit(LED1);
//   STM_EVAL_LEDInit(LED2);
//   STM_EVAL_LEDInit(LED3);
//   STM_EVAL_LEDInit(LED4);

//   /* Initialize the LCD */
// #if defined (USE_STM322xG_EVAL)
//   STM322xG_LCD_Init();
// #elif defined(USE_STM324xG_EVAL)
//   STM324xG_LCD_Init();

// #elif defined(USE_STM324x9I_EVAL)

//   LCD_Init();
//   LCD_LayerInit();

//   /* Enable The Display */
//   LCD_DisplayOn();
//   /* Connect the Output Buffer to LCD Background Layer */
//   LCD_SetLayer(LCD_FOREGROUND_LAYER);

//   /* Clear the Background Layer */
//   LCD_Clear(LCD_COLOR_WHITE);

// #elif defined (USE_STM3210C_EVAL)
//   STM3210C_LCD_Init();
// #else
// #error "Missing define: Evaluation board (ie. USE_STM322xG_EVAL)"
// #endif

//   LCD_LOG_Init();

// #ifdef USE_USB_OTG_HS
//   #ifdef USE_EMBEDDED_PHY
//   LCD_LOG_SetHeader((uint8_t *) " USB OTG HS_IN_FS MSC Device");
//   #else
//   LCD_LOG_SetHeader((uint8_t *) " USB OTG HS MSC Device");
//   #endif
// #else
//   LCD_LOG_SetHeader((uint8_t *) " USB OTG FS MSC Device");
// #endif
//   LCD_UsrLog("> USB device library started.\n");
//   LCD_LOG_SetFooter((uint8_t *) "     USB Device Library V1.2.1");


//   /* Information panel */
//   LCD_SetTextColor(Green);
//   LCD_DisplayStringLine(LCD_PIXEL_HEIGHT - 42, USER_INFORMATION1);
//   LCD_DisplayStringLine(LCD_PIXEL_HEIGHT - 30, USER_INFORMATION2);
//   LCD_SetTextColor(LCD_LOG_DEFAULT_COLOR);
char SS[]="USB FS MSC Device";
OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();
}

/**
* @brief  Displays the message on LCD on device reset event
* @param  speed : device speed
* @retval None
*/
void USBD_USR_DeviceReset(uint8_t speed)
{
  // switch (speed)
  // {
  // case USB_OTG_SPEED_HIGH:
  //   LCD_LOG_SetFooter((uint8_t *) "     USB Device Library V1.2.1  [HS]");
  //   break;

  // case USB_OTG_SPEED_FULL:
  //   LCD_LOG_SetFooter((uint8_t *) "     USB Device Library V1.2.1  [FS]");
  //   break;
  // default:
  //   LCD_LOG_SetFooter((uint8_t *) "     USB Device Library V1.2.1  [??]");

  // }
char SS[]="USB Device Library V1.2.1";
OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();


}


/**
* @brief  Displays the message on LCD on device config event
* @param  None
* @retval Status
*/
void USBD_USR_DeviceConfigured(void)
{
 // LCD_UsrLog("> MSC Interface started.\n");
char SS[]="MSC Interface started";
OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();

}

/**
* @brief  Displays the message on LCD on device suspend event 
* @param  None
* @retval None
*/
void USBD_USR_DeviceSuspended(void)
{
 // LCD_UsrLog("> Device In suspend mode.\n");
 char SS[]="Device In suspend mode";
 OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();
}


/**
* @brief  Displays the message on LCD on device resume event
* @param  None
* @retval None
*/
void USBD_USR_DeviceResumed(void)
{

}

/**
* @brief  USBD_USR_DeviceConnected
*         Displays the message on LCD on device connection Event
* @param  None
* @retval Status
*/
void USBD_USR_DeviceConnected(void)
{
 // LCD_UsrLog("> USB Device Connected.\n");
  char SS[]="USB Device Connected";
OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();
}


/**
* @brief  USBD_USR_DeviceDisonnected
*         Displays the message on LCD on device disconnection Event
* @param  None
* @retval Status
*/
void USBD_USR_DeviceDisconnected(void)
{
 /// LCD_UsrLog("> USB Device Disconnected.\n");
char SS[]="USB Device Disconnected";
OLED_ClearScreen(0x00);
OLED_ShowStrings(0,0,SS,strlen(SS));
OLED_UpdateGRAM();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
