/*
  
  u8x8_display.c
  
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
  
  Abstraction layer for the graphics controller.
  Main goal is the placement of a 8x8 pixel block (tile) on the display.
  
*/

#include "IncludeFile.h"
#include "u8x8.h"


/*==========================================*/
/* internal library function */

/*
  this is a helper function for the U8X8_MSG_DISPLAY_SETUP_MEMORY function.
  It can be called within the display callback function to carry out the usual standard tasks.
  
*/
void u8x8_d_helper_display_setup_memory(u8x8_t *u8x8, const u8x8_display_info_t *display_info)
{
      /* 1) set display info struct */
      u8x8->display_info = display_info;
      u8x8->x_offset = u8x8->display_info->default_x_offset;
}

/*
  this is a helper function for the U8X8_MSG_DISPLAY_INIT function.
  It can be called within the display callback function to carry out the usual standard tasks.
  
*/
void u8x8_d_helper_display_init(u8x8_t *u8x8)
{
      /* 2) apply port directions to the GPIO lines and apply default values for the IO lines*/
      u8x8_gpio_Init(u8x8);
      u8x8_cad_Init(u8x8);

      /* 3) do reset */
      u8x8_gpio_SetReset(u8x8, 1);
      u8x8_gpio_Delay(u8x8, U8X8_MSG_DELAY_MILLI, u8x8->display_info->reset_pulse_width_ms);
      u8x8_gpio_SetReset(u8x8, 0);
      u8x8_gpio_Delay(u8x8, U8X8_MSG_DELAY_MILLI, u8x8->display_info->reset_pulse_width_ms);
      u8x8_gpio_SetReset(u8x8, 1);
      u8x8_gpio_Delay(u8x8, U8X8_MSG_DELAY_MILLI, u8x8->display_info->post_reset_wait_ms);
}    

/*==========================================*/
/* official functions */

uint8_t u8x8_DrawTile(u8x8_t *u8x8, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr)
{
  u8x8_tile_t tile;
  tile.x_pos = x;
  tile.y_pos = y;
  tile.cnt = cnt;
  tile.tile_ptr = tile_ptr;
  return u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_DRAW_TILE, 1, (void *)&tile);
}

/* should be implemented as macro */
void u8x8_SetupMemory(u8x8_t *u8x8)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_SETUP_MEMORY, 0, NULL);  
}

void u8x8_InitDisplay(u8x8_t *u8x8)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_INIT, 0, NULL);  
}

void u8x8_SetPowerSave(u8x8_t *u8x8, uint8_t is_enable)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_SET_POWER_SAVE, is_enable, NULL);  
}

void u8x8_SetFlipMode(u8x8_t *u8x8, uint8_t mode)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_SET_FLIP_MODE, mode, NULL);  
}

void u8x8_SetContrast(u8x8_t *u8x8, uint8_t value)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_SET_CONTRAST, value, NULL);  
}

void u8x8_RefreshDisplay(u8x8_t *u8x8)
{
  u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_REFRESH, 0, NULL);  
}

void u8x8_ClearDisplayWithTile(u8x8_t *u8x8, const uint8_t *buf)
{
  u8x8_tile_t tile;
  uint8_t h;

  tile.x_pos = 0;
  tile.cnt = 1;
  tile.tile_ptr = (uint8_t *)buf;		/* tile_ptr should be const, but isn't */
  
  h = u8x8->display_info->tile_height;
  tile.y_pos = 0;
  do
  {
    u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_DRAW_TILE, u8x8->display_info->tile_width, (void *)&tile);
    tile.y_pos++;
  } while( tile.y_pos < h );
}

void u8x8_ClearDisplay(u8x8_t *u8x8)
{
  uint8_t buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  u8x8_ClearDisplayWithTile(u8x8, buf);
}

void u8x8_FillDisplay(u8x8_t *u8x8)
{
  uint8_t buf[8] = { 255, 255, 255, 255, 255, 255, 255, 255 };
  u8x8_ClearDisplayWithTile(u8x8, buf);
}

void u8x8_ClearLine(u8x8_t *u8x8, uint8_t line)
{
  uint8_t buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  u8x8_tile_t tile;
  if ( line < u8x8->display_info->tile_height )
  {
    tile.x_pos = 0;
    tile.y_pos = line;
    tile.cnt = 1;
    tile.tile_ptr = (uint8_t *)buf;		/* tile_ptr should be const, but isn't */
    u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_DRAW_TILE, u8x8->display_info->tile_width, (void *)&tile);
  }  
}



uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
    void *arg_ptr)
{
    uint8_t *data = NULL;
  switch (msg)
  {
  case U8X8_MSG_BYTE_SEND:
        data = (uint8_t*)arg_ptr;
        do
        {
            while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);            
            SPI_I2S_SendData(SPI2,*(data++));			
            SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	
            arg_int--;
        }while(arg_int > 0);
    break;
  case U8X8_MSG_BYTE_INIT:
    break;
  case U8X8_MSG_BYTE_SET_DC:
        if (arg_int == 1)
        {
            OLED_DATA;         
        }
        else if (arg_int == 0)
        {
            OLED_ORDER;
        }
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    break;
  default:
    return 0;
  }
  return 1;
}

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void *arg_ptr)
{
  switch (msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
        // OLED_Init();
        delay_ms(1);
      break;
    case U8X8_MSG_DELAY_MILLI:
        delay_ms(arg_int);
      break;
      default:
        break;

  }
  return 1;
}

