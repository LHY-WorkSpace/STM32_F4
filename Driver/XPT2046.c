/**
 * @file XPT2046.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "IncludeFile.h"



#include <stddef.h>
#include LV_DRV_INDEV_INCLUDE

/*********************
 *      DEFINES
 *********************/
#define CMD_X_READ  0x90
#define CMD_Y_READ  0xD0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
int16_t avg_buf_x[XPT2046_AVG];
int16_t avg_buf_y[XPT2046_AVG];
uint8_t avg_last;
u8 irq = LV_DRV_INDEV_IRQ_READ;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the XPT2046
 */
void XPT2046_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);



	GPIO_InitTypeDef GPIO_InitTypeDefinsture;
	SPI_InitTypeDef SPI_InitTypeDefinsture;
	GPIO_InitTypeDef GPIOE_Initstruc;

	
	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_6;                 // PA5---SCLK       PA7-----SDA
	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                     
	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_4;                
	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
	

	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI1,&SPI_InitTypeDefinsture);
    SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE|SPI_I2S_FLAG_TXE);
	SPI_Cmd(SPI1,ENABLE);

	GPIOE_Initstruc.GPIO_Pin=GPIO_Pin_3;
	GPIOE_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOE_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOE_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIOE_Initstruc);



}

u8 XPT2046_SendData(u8 Tdata)
{
    u8 Temp=0;
	SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_TXE);	
	SPI_I2S_SendData(SPI1,Tdata);	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);            


	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);            
	Temp = SPI_I2S_ReceiveData(SPI1);			
	SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE);

    return Temp;

}

void XPT2046_CS(u8 State)
{
    if ( State )
    {
        XPT2046_SPI_SEL;

    }
    else
    {
        XPT2046_SPI_NO_SEL;
    }
}


/**
 * Get the current position and state of the touchpad
 * @param data store the read data here
 * @return false: because no ore data to be read
 */
u8 XPT2046_Read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static int16_t last_x = 0;
    static int16_t last_y = 0;
    uint8_t buf;

    int16_t x = 0;
    int16_t y = 0;

    if( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0) 
    {
        LV_DRV_INDEV_SPI_CS(0);

        LV_DRV_INDEV_SPI_XCHG_BYTE(CMD_X_READ);         /*Start x read*/

        buf = LV_DRV_INDEV_SPI_XCHG_BYTE(0);           /*Read x MSB*/
        x = buf << 8;
         buf = LV_DRV_INDEV_SPI_XCHG_BYTE(0);           /*Read x MSB*/
        x += buf;
			
        LV_DRV_INDEV_SPI_XCHG_BYTE(CMD_Y_READ);  /*Until x LSB converted y command can be sent*/

        buf =  LV_DRV_INDEV_SPI_XCHG_BYTE(0);   /*Read y MSB*/
        y = buf << 8;

        buf =  LV_DRV_INDEV_SPI_XCHG_BYTE(0);   /*Read y LSB*/
        y += buf;

        /*Normalize Data*/
        x = x >> 3;
        y = y >> 3;

        if( x > 4000 )
        {
            x=0;
        }

        if( y > 4000 )
        {
            y=0;
        }

        xpt2046_corr(&x, &y);
        xpt2046_avg(&x, &y);

        last_x = x;
        last_y = y;
		data->state = LV_INDEV_STATE_PR;

        LV_DRV_INDEV_SPI_CS(1);

    } 
    else 
    {
        x = last_x;
        y = last_y;
        avg_last = 0;
		data->state = LV_INDEV_STATE_REL;
    }

    data->point.x = x;
    data->point.y = y;




    return false;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
 void xpt2046_corr(int16_t * x, int16_t * y)
{
#if XPT2046_XY_SWAP != 0
    int16_t swap_tmp;
    swap_tmp = *x;
    *x = *y;
    *y = swap_tmp;
#endif

    if((*x) > XPT2046_X_MIN)
        (*x) -= XPT2046_X_MIN;
    else
        (*x) = 0;


    if((*y) > XPT2046_Y_MIN)
        (*y) -= XPT2046_Y_MIN;
    else
        (*y) = 0;




    (*x) = (uint32_t)((uint32_t)(*x) * XPT2046_HOR_RES) /
           (XPT2046_X_MAX - XPT2046_X_MIN);

    (*y) = (uint32_t)((uint32_t)(*y) * XPT2046_VER_RES) /
           (XPT2046_Y_MAX - XPT2046_Y_MIN);


#if XPT2046_X_INV != 0
    (*x) =  XPT2046_HOR_RES - (*x);
#endif

#if XPT2046_Y_INV != 0
    (*y) =  XPT2046_VER_RES - (*y);
#endif


}


 void xpt2046_avg(int16_t * x, int16_t * y)
{
    /*Shift out the oldest data*/
    uint8_t i;
    for(i = XPT2046_AVG - 1; i > 0 ; i--)
     {
        avg_buf_x[i] = avg_buf_x[i - 1];
        avg_buf_y[i] = avg_buf_y[i - 1];
    }

    /*Insert the new point*/
    avg_buf_x[0] = *x;
    avg_buf_y[0] = *y;
    if(avg_last < XPT2046_AVG) 
        avg_last++;

    /*Sum the x and y coordinates*/
    int32_t x_sum = 0;
    int32_t y_sum = 0;
    for(i = 0; i < avg_last ; i++) 
    {
        x_sum += avg_buf_x[i];
        y_sum += avg_buf_y[i];
    }

    /*Normalize the sums*/
    (*x) = (int32_t)x_sum / avg_last;
    (*y) = (int32_t)y_sum / avg_last;
}

