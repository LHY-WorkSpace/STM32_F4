/**
  ******************************************************************************
  * @file    usbd_storage_msd.c
  * @author  MCD application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   This file provides the disk operations functions.
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
#include "usbd_msc_mem.h"
#include "sdio_sdcard.h"
#include "usbd_storage_msd.h"



#define STORAGE_LUN_NBR                  1

/* USB Mass storage Standard Inquiry Data */
const int8_t STORAGE_Inquirydata[] = {  // 36

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (USBD_STD_INQUIRY_LENGTH - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'm', 'i', 'c', 'r', 'o', 'S', 'D', ' ', /* Product : 16 Bytes */
  'F', 'l', 'a', 's', 'h', ' ', ' ', ' ',
  '1', '.', '0', '0',           /* Version : 4 Bytes */
};


// int8_t STORAGE_Init(uint8_t lun);

// int8_t STORAGE_GetCapacity(uint8_t lun,
//                            uint32_t * block_num, uint32_t * block_size);

// int8_t STORAGE_IsReady(uint8_t lun);

// int8_t STORAGE_IsWriteProtected(uint8_t lun);

// int8_t STORAGE_Read(uint8_t lun,
//                     uint8_t * buf, uint32_t blk_addr, uint16_t blk_len);

// int8_t STORAGE_Write(uint8_t lun,
//                      uint8_t * buf, uint32_t blk_addr, uint16_t blk_len);

// int8_t STORAGE_GetMaxLun(void);


USBD_STORAGE_cb_TypeDef USBD_MICRO_SDIO_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  (int8_t *) STORAGE_Inquirydata,
};

USBD_STORAGE_cb_TypeDef *USBD_STORAGE_fops = &USBD_MICRO_SDIO_fops;

extern SD_CardInfo SDCardInfo;

__IO uint32_t count = 0;
/**
  * @}
  */


/** @defgroup STORAGE_Private_Functions
  * @{
  */


/**
  * @brief  Initialize the storage medium
  * @param  lun : logical unit number
  * @retval Status
  */

int8_t STORAGE_Init(uint8_t lun)
{
  if (SD_Init() != 0)
  {
    return (-1);
  }

  return (0);

}

/**
  * @brief  return medium capacity and block size
  * @param  lun : logical unit number
  * @param  block_num :  number of physical block
  * @param  block_size : size of a physical block
  * @retval Status
  */
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num,uint32_t * block_size)
{

  SD_GetCardInfo(&SDCardInfo);

  // if (SD_GetState() != 0)
  // {
  //   return (-1);
  // }

  *block_size = 512;
  *block_num = SDCardInfo.CardCapacity / 512;

  return (0);

}

/**
  * @brief  check whether the medium is ready
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t STORAGE_IsReady(uint8_t lun)
{

  static int8_t last_status = 0;

  if (last_status < 0)
  {
    SD_Init();
    last_status = 0;
  }

  // if (SD_GetState() != 0)
  // {
  //   last_status = -1;
  //   return (-1);
  // }
  return (0);
}

/**
  * @brief  check whether the medium is write-protected
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t STORAGE_IsWriteProtected(uint8_t lun)
{
  return 0;
}

/**
  * @brief  Read data from the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to save data
  * @param  blk_addr :  address of 1st block to be read
  * @param  blk_len : nmber of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Read(uint8_t lun,
                    uint8_t * buf, uint32_t blk_addr, uint16_t blk_len)
{

  if (SD_ReadMultiBlocks(buf, blk_addr * 512, 512, blk_len) != 0)
  {
    return -1;
  }
  //while (SD_GetState() != SD_CARD_TRANSFER);

  return 0;
}

/**
  * @brief  Write data to the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to write from
  * @param  blk_addr :  address of 1st block to be written
  * @param  blk_len : nmber of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Write(uint8_t lun,
                     uint8_t * buf, uint32_t blk_addr, uint16_t blk_len)
{

  if (SD_WriteMultiBlocks(buf, blk_addr * 512, 512, blk_len) != 0)
  {
    return -1;
  }
 // while (SD_GetState() != SD_CARD_TRANSFER);

  return (0);
}

/**
  * @brief  Return number of supported logical unit
  * @param  None
  * @retval number of logical unit
  */

int8_t STORAGE_GetMaxLun(void)
{
  return (STORAGE_LUN_NBR - 1);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
