#include "IncludeFile.h"
#include "font.h" 

//单个点的数据的大小
#define POINT_SIZE  (sizeof(u16))

//DMA 单次最大传输个数
#define DMA_MAX_BUFF  (60000)

static u32 DMA_TXCurrentAddr,DMA_EndAddr;


//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=RED;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
//DMA传输控制参数


//管理LCD重要参数
//默认为竖屏
LCD_Dev_t LCD_Dev;
LCD_State_t LCD_State = { .Row_AddrMode = Up_Down,
						  .Col_AddrMode = Left_Right,
						  .RowCol_Exchenge = 0,
						  .Ver_ScanMode = Up_Down,
						  .RGB_BGR_Mode = RGB,
						  .Hor_ScanMode = Left_Right,
						  .Pixel_Bit = 16,
						  .ID = 0Xffff,
						};
//写指令函数
//regval:指令值
void LCD_WriteCMD(vu16 regval)
{   
	LCD->LCD_REG=regval;//写入要写的指令序号	 
}


//写LCD数据
//data:要写入的值
void LCD_WriteData(vu16 data)
{	  
	LCD->LCD_RAM=data;		 
}


//读LCD数据
//返回值:读到的值
u16 LCD_ReadData(void)
{
	vu16 ram;			//防止被优化
	ram=LCD->LCD_RAM;	
	return ram;	 
}


//带参数写指令
//LCD_Cmd:指令地址
//LCD_CmdValue:要写入的数据
void LCD_WriteCmdPara(vu16 LCD_Cmd,vu16 LCD_CmdValue)
{	
	LCD->LCD_REG = LCD_Cmd;		//写入要写的指令序号	 
	LCD->LCD_RAM = LCD_CmdValue;//写入数据	    		 
}


//读ID
//LCD_Cmd:指令地址
//返回值:读到的数据
u16 LCD_ReadID(u16 LCD_Cmd)
{										   
	LCD_WriteCMD(LCD_Cmd);		//写入要读的指令序号
	Delay_us(5);		  
	return LCD_ReadData();		//返回读到的值
} 



//软件复位
void LCD_Reset()
{
	LCD_WriteCMD(LCD_SWRESET);
	Delay_ms(7);
}



//开始写GRAM
void LCD_WriteToRAM(void)
{
 	LCD->LCD_REG=LCD_Dev.UpToGRAM;	  
}	


//LCD开启显示
void LCD_DisplayOn(void)
{					   
	LCD_WriteCMD(LCD_DISPLAY_ON);	//开启显示
	LCD_BACK_LIGHT_ON;
}	


//LCD关闭显示
void LCD_DisplayOff(void)
{	   
	LCD_WriteCMD(LCD_DISPLAY_OFF);	//关闭显示
	LCD_BACK_LIGHT_OFF;
} 


//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 


//当mdk -O1时间优化时需要设置
//延时i
void LCD_Delay(u8 i)
{
	 u8 j;
	for(j=0;j<i;j++)
	{
		LCD_WriteCMD(LCD_NOP);
	}
}


void LCD_DMA_Init()
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

  	DMA_InitTypeDef DMA_InitConfig;
	NVIC_InitTypeDef  NVIC_Initstr;

    DMA_Cmd(DMA2_Stream3,DISABLE);
	DMA_InitConfig.DMA_Memory0BaseAddr = (u32)&(LCD->LCD_RAM);	
	DMA_InitConfig.DMA_PeripheralBaseAddr= (u32)0;
	DMA_InitConfig.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitConfig.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitConfig.DMA_BufferSize = DMA_MAX_BUFF;
	DMA_InitConfig.DMA_DIR=DMA_DIR_MemoryToMemory;
	DMA_InitConfig.DMA_Channel=DMA_Channel_0; 
	DMA_InitConfig.DMA_Mode=DMA_Mode_Normal;
	DMA_InitConfig.DMA_MemoryInc=DMA_MemoryInc_Disable;
	DMA_InitConfig.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_InitConfig.DMA_Priority=DMA_Priority_High;
	DMA_InitConfig.DMA_FIFOMode=DMA_FIFOMode_Enable;
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_HalfFull;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream1,&DMA_InitConfig);

	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream1_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);
	DMA_ITConfig(DMA2_Stream1,DMA_IT_TC,ENABLE);	
	DMA_Cmd(DMA2_Stream1,DISABLE);

    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
}



void LCD_IO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,PE,PF,PG时钟  
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PB15 推挽输出,控制背光
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化 //PB15 推挽输出,控制背光

	GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PF12,FSMC_A6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PF12,FSMC_A6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化 

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);//PD0,AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);//PD1,AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);//PD15,AF12

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);//PE7,AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);//PE15,AF12

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);//PF12,AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);


	readWriteTiming.FSMC_AddressSetupTime = 0X0F;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
	readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 


	writeTiming.FSMC_AddressSetupTime =0x0F;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
	writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
	writeTiming.FSMC_DataSetupTime = 60;		 //数据保存时间为6ns*9个HCLK=54ns
	writeTiming.FSMC_BusTurnAroundDuration = 0x00;
	writeTiming.FSMC_CLKDivision = 0x00;
	writeTiming.FSMC_DataLatency = 0x00;
	writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 


	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // 使能BANK1 

}


//获取ID
void LCD_GetID()
{
	u8 temp;
	LCD_Dev.ID = 0;
	LCD_WriteCMD(LCD_READ_ID4);
	for(temp=0;temp<2;temp++)
	{
		LCD_ReadData();
	}
	LCD_Dev.ID = LCD_ReadData()<<8;
	LCD_Dev.ID |= LCD_ReadData();

	if(LCD_Dev.ID == 0)
	{
		LCD_Dev.ID = 0xFFFF;
	}
}



//查询显示模式(只支持部分参数，需要查询其他参数时再另外添加)
void LCD_GetState(LCD_State_t *LCD_State)
{
	u16 DataTemp[2];
	LCD_WriteCMD(LCD_RDDST);
	LCD_ReadData();
	DataTemp[0] = LCD_ReadData();
	DataTemp[1] = LCD_ReadData();
	if( DataTemp[0] & 0x02) 
	{
		LCD_State->Hor_ScanMode = Right_Left;
	}
	else
	{
		LCD_State->Hor_ScanMode = Left_Right;
	}

	if( DataTemp[0] & 0x04)
	{
		LCD_State->RGB_BGR_Mode = BGR;
	}
	else
	{
		LCD_State->RGB_BGR_Mode = RGB;
	}
	if( DataTemp[0] & 0x08)
	{
		LCD_State->Ver_ScanMode = Down_Up;
	}
	else
	{
		LCD_State->Ver_ScanMode = Up_Down;
	}

	if( DataTemp[0] & 0x10)
	{
		LCD_State->RowCol_Exchenge = 1;
	}
	else
	{
		LCD_State->RowCol_Exchenge = 0;
	}
	if( DataTemp[0] & 0x20)
	{
		LCD_State->Col_AddrMode = Right_Left;
	}
	else
	{
		LCD_State->Col_AddrMode = Left_Right;
	}

	if( DataTemp[0] & 0x40)
	{
		LCD_State->Row_AddrMode = Down_Up;
	}
	else
	{
		LCD_State->Row_AddrMode = Up_Down;
	}

	if( DataTemp[1] & 0x50)
	{
		LCD_State->Pixel_Bit = 16;
	}
	else
	{
		LCD_State->Pixel_Bit = 18;
	}
	LCD_State->ID = LCD_Dev.ID; 
}



//设置光标起始位置
//Xpos:横坐标
//Ypos:纵坐标
void LCD_SetXY_Start(u16 Xpos, u16 Ypos)
{ 	    
	LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
	LCD_WriteData(Xpos>>8);
	LCD_WriteData(Xpos&0XFF); 
	LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
	LCD_WriteData(Ypos>>8);
	LCD_WriteData(Ypos&0XFF); 
		
} 


//设置光标移动范围
//  x_S  x起始
//  y_S  x结束
//  x_E  y起始
//  y_E  y结束

void LCD_SetXY_Area(u16 x_S, u16 y_S,u16 x_E,u16 y_E)
{ 	    
	LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
	LCD_WriteData(x_S>>8);
	LCD_WriteData(x_S&0XFF); 
	LCD_WriteData(x_E>>8);
	LCD_WriteData(x_E&0XFF);			 
	LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
	LCD_WriteData(y_S>>8);
	LCD_WriteData(y_S&0XFF); 
	LCD_WriteData(y_E>>8);
	LCD_WriteData(y_E&0XFF);  			
} 





//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;

	if(LCD_Dev.Dir == Horizontal)  //横屏
	{
		if(   x > (LCD_HIGH-1) ||
			  y > (LCD_WIDTH-1)
			)
		{
			return 0;	//超过了范围,直接返回	
		}
	}
	else
	{
		if(   x > (LCD_WIDTH-1) ||
			  y > (LCD_HIGH-1)
			)
		{
			return 0;	//超过了范围,直接返回			
		}
	}

	LCD_SetXY_Start(x,y);	    
	LCD_WriteCMD(LCD_RAMRD);	//读GRAM
 	LCD_ReadData();	

 	r = LCD_ReadData();  		//实际坐标颜色  
	b = LCD_ReadData() >> 11; 
	g = r & 0x00FC;
	r &= 0xF800;	 
	g <<= 3;
	return r|g|b;
}


//垂直滚动函数
// XStart:起始行
// Xend:终止行
// High:滚动区域高度(单位：行)
void LCD_VerScroll(u16 XStart,u16 Xend,u16 High)
{
	LCD_WriteCMD(LCD_VSCRDEF);
	LCD_WriteData( XStart >> 8 );
	LCD_WriteData( XStart & 0xFF);
	LCD_WriteData( High >> 8 );
	LCD_WriteData( High & 0xFF);
	LCD_WriteData( Xend >> 8 );
	LCD_WriteData( Xend & 0xFF);
	LCD_Delay(2);
	LCD_WriteCMD(LCD_VSCRSADD);
	LCD_WriteData( XStart >> 8 );
	LCD_WriteData( XStart & 0xFF);
}




//设置LCD的数据写入方向  	   
void LCD_WriteData_Dir(u8 Dir)
{
	u16 regval=0;
	u16 temp;  
	
	switch(Dir)
	{
		case L2R_U2D://从左到右,从上到下
			regval|=(0<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case L2R_D2U://从左到右,从下到上
			regval|=(1<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case R2L_U2D://从右到左,从上到下
			regval|=(0<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case R2L_D2U://从右到左,从下到上
			regval|=(1<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;	 
		case U2D_L2R://从上到下,从左到右
			regval|=(0<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case U2D_R2L://从上到下,从右到左
			regval|=(0<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case D2U_L2R://从下到上,从左到右
			regval|=(1<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case D2U_R2L://从下到上,从右到左
			regval|=(1<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;	 
	}


		regval|=0X08;//5310/5510/1963不需要BGR    

		LCD_WriteCmdPara(LCD_MAC,regval);

		if(regval&0X20)
		{
			if(LCD_Dev.Width<LCD_Dev.Height)//交换X,Y
			{
				temp=LCD_Dev.Width;
				LCD_Dev.Width=LCD_Dev.Height;
				LCD_Dev.Height=temp;
			}
		}
		else  
		{
			if(LCD_Dev.Width>LCD_Dev.Height)//交换X,Y
			{
				temp=LCD_Dev.Width;
				LCD_Dev.Width=LCD_Dev.Height;
				LCD_Dev.Height=temp;
			}
		}  

		LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
		LCD_WriteData(0);
		LCD_WriteData(0);
		LCD_WriteData((LCD_Dev.Width-1)>>8);
		LCD_WriteData((LCD_Dev.Width-1)&0XFF);
		LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
		LCD_WriteData(0);
		LCD_WriteData(0);
		LCD_WriteData((LCD_Dev.Height-1)>>8);
		LCD_WriteData((LCD_Dev.Height-1)&0XFF);  


}   


//快速画点
//x,y:坐标
//color:颜色
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{	   
	LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
	LCD_WriteData(x>>8);
	LCD_WriteData(x&0XFF);  			 
	LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
	LCD_WriteData(y>>8);
	LCD_WriteData(y&0XFF); 		 	 			 
	LCD_WriteToRAM();
	LCD->LCD_RAM=color; 
}




//设置背光LED亮度
void LCD_Set_BackLight(u8 pwm)
{	
	LCD_WriteCMD(LCD_WCD);	    //亮度控制
	LCD_WriteData(0x2C);

	LCD_WriteCMD(LCD_BACKLIGHT8);	//配置PWM模式
	LCD_WriteData(0x00);	

	LCD_WriteCMD(LCD_BACKLIGHT7);	//配置PWM输出
	LCD_WriteData(pwm);	        //1设置PWM频率

}



//设置LCD显示方向
//Dir:0,竖屏；1,横屏
void LCD_Display_Dir(u8 Dir)
{
	if(Dir==Vertical)			//竖屏
	{
		LCD_Dev.Dir=Vertical;	//竖屏
		LCD_Dev.Width=LCD_WIDTH;
		LCD_Dev.Height=LCD_HIGH;
		LCD_Dev.UpToGRAM=LCD_GRAM;
		LCD_Dev.Set_X_CMD=LCD_COLUMN_ADDR;
		LCD_Dev.Set_Y_CMD=LCD_PAGE_ADDR;  
		LCD_WriteData_Dir(L2R_U2D);	//默认填充方向	 
	}
	else 				//横屏
	{	  				
		LCD_Dev.Dir=Horizontal;	//横屏
		LCD_Dev.Width=LCD_HIGH;
		LCD_Dev.Height=LCD_WIDTH;
		LCD_Dev.UpToGRAM=LCD_GRAM;
		LCD_Dev.Set_X_CMD=LCD_COLUMN_ADDR;
		LCD_Dev.Set_Y_CMD=LCD_PAGE_ADDR;  	 
		LCD_WriteData_Dir(U2D_R2L);	//默认填充方向
	} 
	
}




//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//Width,Height:窗口宽度和高度,必须大于0!!
//窗体大小:Width*Height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 Width,u16 Height)
{    
	u16 twidth,theight;
	twidth=sx+Width-1;
	theight=sy+Height-1;


	if(LCD_Dev.Dir == Horizontal)  //横屏
	{
		if(   twidth > (LCD_HIGH-1) ||
			  theight > (LCD_WIDTH-1)
			)
		{
			twidth = LCD_HIGH -1;
			theight = LCD_WIDTH -1;	
		}

	}
	else
	{

		if(   twidth > (LCD_WIDTH-1) ||
			  theight > (LCD_HIGH-1)
			)
		{
			twidth = LCD_WIDTH -1;
			theight = LCD_HIGH -1;
			
		}
	}

	LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
	LCD_WriteData(sx>>8); 
	LCD_WriteData(sx&0XFF);	 
	LCD_WriteData(twidth>>8); 
	LCD_WriteData(twidth&0XFF);  
	LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
	LCD_WriteData(sy>>8); 
	LCD_WriteData(sy&0XFF); 
	LCD_WriteData(theight>>8); 
	LCD_WriteData(theight&0XFF); 
	
}










//初始化lcd
void LCD_Init(void)
{ 	
	LCD_IO_Init();
	LCD_DMA_Init();

	LCD_Reset();
	LCD_Delay(100);//NOP
	//读设备ID	
	LCD_GetID();   			   

	LCD_WriteCMD(LCD_POWERB);  //功耗B设置
	LCD_WriteData(0x00); 
	LCD_WriteData(0xC1); 
	LCD_WriteData(0X30);

	LCD_WriteCMD(LCD_POWER_SEQ);  //电源序列设置
	LCD_WriteData(0x64); 
	LCD_WriteData(0x03); 
	LCD_WriteData(0X12); 
	LCD_WriteData(0X81); 

	LCD_WriteCMD(LCD_DTCA);  //驱动时序A设置
	LCD_WriteData(0x85); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x7A); 

	LCD_WriteCMD(LCD_POWERA);  //功耗设置A
	LCD_WriteData(0x39); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x34); 
	LCD_WriteData(0x02); 

	LCD_WriteCMD(LCD_PRC);  //泵比控制
	LCD_WriteData(0x20); 

	LCD_WriteCMD(LCD_DTCB);  //驱动时序B设置


	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 

	LCD_WriteCMD(LCD_POWER1);    //功耗1设置
	LCD_WriteData(0x1B);   //VRH[5:0] 

	LCD_WriteCMD(LCD_POWER2);    //功耗2设置
	LCD_WriteData(0x01);   //SAP[2:0];BT[3:0] 

	LCD_WriteCMD(LCD_VCOM1);    //VCM 控制 1
	LCD_WriteData(0x30); 	 //3F
	LCD_WriteData(0x30); 	 //3C

	LCD_WriteCMD(LCD_VCOM2);    //VCM 控制 2
	LCD_WriteData(0XB7); 

	LCD_WriteCMD(LCD_MAC);    // 存储器访问控制 
	LCD_WriteData(0x48); 

	LCD_WriteCMD(LCD_PIXEL_FORMAT);   //像素格式控制
	LCD_WriteData(0x55); 

	LCD_WriteCMD(LCD_FRMCTR1);   //帧速率控制
	LCD_WriteData(0x00);   
	LCD_WriteData(0x1A); 

	LCD_WriteCMD(LCD_DFC);    // 显示功能控制
	LCD_WriteData(0x0A); 
	LCD_WriteData(0xA2); 

	LCD_WriteCMD(LCD_3GAMMA_EN);    // 伽马3使能
	LCD_WriteData(0x00); 

	LCD_WriteCMD(LCD_GAMMA);    //伽马设置
	LCD_WriteData(0x01); 

	LCD_WriteCMD(LCD_PGAMMA);    //正极伽马校准
	LCD_WriteData(0x0F); 
	LCD_WriteData(0x2A); 
	LCD_WriteData(0x28); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x0E); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x54); 
	LCD_WriteData(0XA9); 
	LCD_WriteData(0x43); 
	LCD_WriteData(0x0A); 
	LCD_WriteData(0x0F); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 	

	LCD_WriteCMD(LCD_NGAMMA);    //负极伽马校准
	LCD_WriteData(0x00); 
	LCD_WriteData(0x15); 
	LCD_WriteData(0x17); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x11); 
	LCD_WriteData(0x06); 
	LCD_WriteData(0x2B); 
	LCD_WriteData(0x56); 
	LCD_WriteData(0x3C); 
	LCD_WriteData(0x05); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x0F); 
	LCD_WriteData(0x3F); 
	LCD_WriteData(0x3F); 
	LCD_WriteData(0x0F); 

	LCD_WriteCMD(LCD_PAGE_ADDR); //行地址设置
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x3f);

	LCD_WriteCMD(LCD_COLUMN_ADDR); //列地址设置
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0xef);	 

	LCD_WriteCMD(LCD_SLEEP_OUT); //退出睡眠
	Delay_ms(120);
	LCD_WriteCMD(LCD_DISPLAY_ON); //开显示
 
	LCD_Display_Dir(Vertical);		//默认为竖屏	
	LCD_Clear(WHITE);
	LCD_GetState(&LCD_State);
	LCD_BACK_LIGHT_ON;
}  



//清屏函数
//color:要清屏的填充色
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=LCD_Dev.Width;
	totalpoint*=LCD_Dev.Height; 			//得到总点数
	LCD_SetXY_Start(0x00,0x00);		//设置光标位置 
	LCD_WriteToRAM();     		//开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
	}
}  




void LCD_ShowPicture()
{
    
	u32 x=0,y=0;
	Data_Buff DataTemp;				//存放LCD ID字符串
	u32 P=0;
	//u32 totalpoint=LCD_Dev.Height*LCD_Dev.Width; 			//得到总点数
	 LCD_Display_Dir(Vertical);
	 LCD_SetXY_Area(0,0,239,319);	//设置光标位置 
	 LCD_WriteToRAM();     		//开始写入GRAM
	FIL fils;
////////////////////////////////////////////////////////////

	// totalpoint=File_GetFileSize("1:/SD/Data_1.bin");

	// File_ReadData("1:/SD/Data_1.bin",(u8*)&(LCD->LCD_RAM),totalpoint,P);

////////////////////////////////////////////////////////////

		for(y=0;y<64;y++)
		{
			File_ReadData(&fils,"1:/SD/Data_1.bin",DataTemp.Data_8,2400,P);
			P+=2400;		
			for(x=0;x<1200;x++)
			{
				LCD_WriteData(DataTemp.Data_16[x]);
			}
		}

		//Delay_ms(100);

		P=0;
		for(y=0;y<64;y++)
		{
			File_ReadData(&fils,"1:/SD/Data_2.bin",DataTemp.Data_8,2400,P);
			P+=2400;		
			for(x=0;x<1200;x++)
			{
				LCD_WriteData(DataTemp.Data_16[x]);
			}
		}

		//Delay_ms(100);

		LCD_Display_Dir(Horizontal);
	 	LCD_SetXY_Area(0,0,319,239);	//设置光标位置 
		LCD_WriteToRAM();     		//开始写入GRAM
		P=0;
		for(y=0;y<240;y++)
		{
			File_ReadData(&fils,"1:/SD/Data_3.bin",DataTemp.Data_8,640,P);
			P+=640;		
			for(x=0;x<320;x++)
			{
				LCD_WriteData(DataTemp.Data_16[x]);
			}
		}
		//Delay_ms(100);

//////////////////////////////////////////////////////////////////

} 





//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		LCD_SetXY_Start(sx,i);      				//设置光标位置 
		LCD_WriteToRAM();     			//开始写入GRAM	  
		for(j=0;j<xlen;j++)
			LCD->LCD_RAM=color;	//显示颜色 	    
	} 
}  





//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 Height,Width;
	u16 i,j;
	Width=ex-sx+1; 			//得到填充的宽度
	Height=ey-sy+1;			//高度
 	for(i=0;i<Height;i++)
	{
 		LCD_SetXY_Start(sx,sy+i);   	//设置光标位置 
		LCD_WriteToRAM();     //开始写入GRAM
		for(j=0;j<Width;j++)LCD->LCD_RAM=color[i*Width+j];//写入数据 
	}		  
}  




//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  




//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}





//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b,color);             //5
 		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-a,y0+b,color);             //1       
 		LCD_DrawPoint(x0-b,y0+a,color);             
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
  		LCD_DrawPoint(x0-b,y0-a,color);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 






//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=LCD_Dev.Height)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=LCD_Dev.Width)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}   





//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 





//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)
					LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else 
					LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 





//显示字符串
//x,y:起点坐标
//Width,Height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 Width,u16 Height,u8 size,u8 *p)
{         
	u8 x0=x;
	Width+=x;
	Height+=y;
    while(1)//判断是不是非法字符!
    {       
        if(x>=Width){x=x0;y+=size;}
        if(y>=Height)break;//退出
		if((*p<='~')&&(*p>=' '))
		{
			LCD_ShowChar(x,y,*p,size,1);
		}
		else
		{
			LCD_ShowChar(x,y,' ',size,1);
		}
        x+=size/2;
        p++;
    }  
}


//***************************************************//
//  功能描述: DMA发送数据起始地址和长度
//  
//  参数: 数据地址，点数
//  
//  返回值: TRUE / FALSE
//  
//  说明: 
//  
//***************************************************//
void LCD_DMA_SetAddr(u32 StartAddr, u32 Point)
{
    DMA_TXCurrentAddr = StartAddr;
    DMA_EndAddr = StartAddr + Point*POINT_SIZE;
}

//***************************************************//
//  功能描述: 获取当前发送地址
//  
//  参数: 无
//  
//  返回值: u32
//  
//  说明: 无
//  
//***************************************************//
u32 LCD_DMA_GetCurrentAddr()
{
    return DMA_TXCurrentAddr;
}

//***************************************************//
//  功能描述: 获取DMA发送状态
//  
//  参数: 
//  
//  返回值: TRUE：已完成/ FALSE：未完成
//  
//  说明: 无
//  
//***************************************************//
u8 LCD_DMA_GetTXComplateFlag()
{
    if( DMA_TXCurrentAddr < DMA_EndAddr )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//***************************************************//
//  功能描述: 启动DMA传输
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 启动DMA传输时先调用 TFT_DMA_SetAddr(),确定数据起始地址和长度
//        中断里直接调用
//***************************************************//
void LCD_DMA_Start()
{
    u32 Length;

    TFT_DATA;

    Length = (DMA_EndAddr - DMA_TXCurrentAddr);

    if( Length > DMA_MAX_BUFF )
    {
         Length = DMA_MAX_BUFF;
    }
	
	LCD_WriteToRAM();

    DMA_Cmd(DMA2_Stream1,DISABLE);
	DMA2_Stream1->PAR = DMA_TXCurrentAddr;
	DMA2_Stream1->NDTR = Length;
    DMA_Cmd(DMA2_Stream1,ENABLE);
    
    DMA_TXCurrentAddr += Length;

}

//***************************************************//
//  功能描述: 停止DMA
//  
//  参数: 无
//  
//  返回值: 
//  
//  说明: 数据传输到达设定长度后停止DMA
//  
//***************************************************//
void LCD_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream1,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;

}












