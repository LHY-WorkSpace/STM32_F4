#include "IncludeFile.h"
#include "font.h" 

//单个点的数据的大小
#define POINT_SIZE  (sizeof(u16))

//DMA 单次最大传输个数
#define DMA_MAX_BUFF  (60000)

static u32 DMA_TXCurrentAddr,DMA_EndAddr,SendLength;


//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=RED;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
//DMA传输控制参数


//管理LCD重要参数
//默认为竖屏
ILI9341_Dev_t ILI9341_Dev;
ILI9341_State_t ILI9341_State = { .Row_AddrMode = Up_Down,
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
void ILI9341_WriteCMD(vu16 regval)
{   
	LCD->ILI9341_REG=regval;//写入要写的指令序号	 
}


//写LCD数据
//data:要写入的值
void ILI9341_WriteData(vu16 data)
{	  
	LCD->ILI9341_RAM=data;		 
}


//读LCD数据
//返回值:读到的值
u16 ILI9341_ReadData(void)
{
	vu16 ram;			//防止被优化
	ram=LCD->ILI9341_RAM;	
	return ram;	 
}


//带参数写指令
//ILI9341_Cmd:指令地址
//ILI9341_CmdValue:要写入的数据
void ILI9341_WriteCmdPara(vu16 ILI9341_Cmd,vu16 ILI9341_CmdValue)
{	
	LCD->ILI9341_REG = ILI9341_Cmd;		//写入要写的指令序号	 
	LCD->ILI9341_RAM = ILI9341_CmdValue;//写入数据	    		 
}


//读ID
//ILI9341_Cmd:指令地址
//返回值:读到的数据
u16 ILI9341_ReadID(u16 ILI9341_Cmd)
{										   
	ILI9341_WriteCMD(ILI9341_Cmd);		//写入要读的指令序号
	Delay_us(5);		  
	return ILI9341_ReadData();		//返回读到的值
} 



//软件复位
void ILI9341_Reset()
{
	ILI9341_WriteCMD(ILI9341_SWRESET);
	Delay_ms(7);
}



//开始写GRAM
void ILI9341_WriteToRAM(void)
{
 	LCD->ILI9341_REG=ILI9341_Dev.UpToGRAM;	  
}	


//LCD开启显示
void ILI9341_DisplayOn(void)
{					   
	ILI9341_WriteCMD(ILI9341_DISPLAY_ON);	//开启显示
	ILI9341_BACK_LIGHT_ON;
}	


//LCD关闭显示
void ILI9341_DisplayOff(void)
{	   
	ILI9341_WriteCMD(ILI9341_DISPLAY_OFF);	//关闭显示
	ILI9341_BACK_LIGHT_OFF;
} 


//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 ILI9341_BGR2RGB(u16 c)
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
void ILI9341_Delay(u8 i)
{
	 u8 j;
	for(j=0;j<i;j++)
	{
		ILI9341_WriteCMD(ILI9341_NOP);
	}
}


void ILI9341_DMA_Init()
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

  	DMA_InitTypeDef DMA_InitConfig;
	NVIC_InitTypeDef  NVIC_Initstr;

    DMA_Cmd(DMA2_Stream3,DISABLE);
	DMA_InitConfig.DMA_Memory0BaseAddr = (u32)&(LCD->ILI9341_RAM);	
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
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream1,&DMA_InitConfig);

	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream1_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

	DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);
	DMA_ITConfig(DMA2_Stream1,DMA_IT_TC,ENABLE);	
	DMA_Cmd(DMA2_Stream1,DISABLE);

    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
	SendLength = 0;
}



void ILI9341_IO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//使能PD,PE,PF,PG时钟  
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


	readWriteTiming.FSMC_AddressSetupTime = 0X05;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
	readWriteTiming.FSMC_DataSetupTime = 30;			//数据保存时间为60个HCLK	=6*60=360ns
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 


	writeTiming.FSMC_AddressSetupTime =0x02;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
	writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
	writeTiming.FSMC_DataSetupTime = 10;		 //数据保存时间为6ns*9个HCLK=54ns
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
void ILI9341_GetID()
{
	u8 temp;
	ILI9341_Dev.ID = 0;
	ILI9341_WriteCMD(ILI9341_READ_ID4);
	for(temp=0;temp<2;temp++)
	{
		ILI9341_ReadData();
	}
	ILI9341_Dev.ID = ILI9341_ReadData()<<8;
	ILI9341_Dev.ID |= ILI9341_ReadData();

	if(ILI9341_Dev.ID == 0)
	{
		ILI9341_Dev.ID = 0xFFFF;
	}
}



//查询显示模式(只支持部分参数，需要查询其他参数时再另外添加)
void ILI9341_GetState(ILI9341_State_t *ILI9341_State)
{
	u16 DataTemp[2];
	ILI9341_WriteCMD(ILI9341_RDDST);
	ILI9341_ReadData();
	DataTemp[0] = ILI9341_ReadData();
	DataTemp[1] = ILI9341_ReadData();
	if( DataTemp[0] & 0x02) 
	{
		ILI9341_State->Hor_ScanMode = Right_Left;
	}
	else
	{
		ILI9341_State->Hor_ScanMode = Left_Right;
	}

	if( DataTemp[0] & 0x04)
	{
		ILI9341_State->RGB_BGR_Mode = BGR;
	}
	else
	{
		ILI9341_State->RGB_BGR_Mode = RGB;
	}
	if( DataTemp[0] & 0x08)
	{
		ILI9341_State->Ver_ScanMode = Down_Up;
	}
	else
	{
		ILI9341_State->Ver_ScanMode = Up_Down;
	}

	if( DataTemp[0] & 0x10)
	{
		ILI9341_State->RowCol_Exchenge = 1;
	}
	else
	{
		ILI9341_State->RowCol_Exchenge = 0;
	}
	if( DataTemp[0] & 0x20)
	{
		ILI9341_State->Col_AddrMode = Right_Left;
	}
	else
	{
		ILI9341_State->Col_AddrMode = Left_Right;
	}

	if( DataTemp[0] & 0x40)
	{
		ILI9341_State->Row_AddrMode = Down_Up;
	}
	else
	{
		ILI9341_State->Row_AddrMode = Up_Down;
	}

	if( DataTemp[1] & 0x50)
	{
		ILI9341_State->Pixel_Bit = 16;
	}
	else
	{
		ILI9341_State->Pixel_Bit = 18;
	}
	ILI9341_State->ID = ILI9341_Dev.ID; 
}



//设置光标起始位置
//Xpos:横坐标
//Ypos:纵坐标
void ILI9341_SetXY_Start(u16 Xpos, u16 Ypos)
{ 	    
	ILI9341_WriteCMD(ILI9341_Dev.Set_X_CMD); 
	ILI9341_WriteData(Xpos>>8);
	ILI9341_WriteData(Xpos&0XFF); 
	ILI9341_WriteCMD(ILI9341_Dev.Set_Y_CMD); 
	ILI9341_WriteData(Ypos>>8);
	ILI9341_WriteData(Ypos&0XFF); 
		
} 


//设置光标移动范围
//  x_S  x起始
//  y_S  x结束
//  x_E  y起始
//  y_E  y结束

void ILI9341_SetXY_Area(u16 x_S, u16 y_S,u16 x_E,u16 y_E)
{ 	    
	ILI9341_WriteCMD(ILI9341_Dev.Set_X_CMD); 
	ILI9341_WriteData(x_S>>8);
	ILI9341_WriteData(x_S&0XFF); 
	ILI9341_WriteData(x_E>>8);
	ILI9341_WriteData(x_E&0XFF);			 
	ILI9341_WriteCMD(ILI9341_Dev.Set_Y_CMD); 
	ILI9341_WriteData(y_S>>8);
	ILI9341_WriteData(y_S&0XFF); 
	ILI9341_WriteData(y_E>>8);
	ILI9341_WriteData(y_E&0XFF);  			
} 





//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 ILI9341_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;

	if(ILI9341_Dev.Dir == Horizontal)  //横屏
	{
		if(   x > (ILI9341_HIGH-1) ||
			  y > (ILI9341_WIDTH-1)
			)
		{
			return 0;	//超过了范围,直接返回	
		}
	}
	else
	{
		if(   x > (ILI9341_WIDTH-1) ||
			  y > (ILI9341_HIGH-1)
			)
		{
			return 0;	//超过了范围,直接返回			
		}
	}

	ILI9341_SetXY_Start(x,y);	    
	ILI9341_WriteCMD(ILI9341_RAMRD);	//读GRAM
 	ILI9341_ReadData();	

 	r = ILI9341_ReadData();  		//实际坐标颜色  
	b = ILI9341_ReadData() >> 11; 
	g = r & 0x00FC;
	r &= 0xF800;	 
	g <<= 3;
	return r|g|b;
}


//垂直滚动函数
// XStart:起始行
// Xend:终止行
// High:滚动区域高度(单位：行)
void ILI9341_VerScroll(u16 XStart,u16 Xend,u16 High)
{
	ILI9341_WriteCMD(ILI9341_VSCRDEF);
	ILI9341_WriteData( XStart >> 8 );
	ILI9341_WriteData( XStart & 0xFF);
	ILI9341_WriteData( High >> 8 );
	ILI9341_WriteData( High & 0xFF);
	ILI9341_WriteData( Xend >> 8 );
	ILI9341_WriteData( Xend & 0xFF);
	ILI9341_Delay(2);
	ILI9341_WriteCMD(ILI9341_VSCRSADD);
	ILI9341_WriteData( XStart >> 8 );
	ILI9341_WriteData( XStart & 0xFF);
}




//设置LCD的数据写入方向  	   
void ILI9341_WriteData_Dir(u8 Dir)
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

		ILI9341_WriteCmdPara(ILI9341_MAC,regval);

		if(regval&0X20)
		{
			if(ILI9341_Dev.Width<ILI9341_Dev.Height)//交换X,Y
			{
				temp=ILI9341_Dev.Width;
				ILI9341_Dev.Width=ILI9341_Dev.Height;
				ILI9341_Dev.Height=temp;
			}
		}
		else  
		{
			if(ILI9341_Dev.Width>ILI9341_Dev.Height)//交换X,Y
			{
				temp=ILI9341_Dev.Width;
				ILI9341_Dev.Width=ILI9341_Dev.Height;
				ILI9341_Dev.Height=temp;
			}
		}  

		ILI9341_WriteCMD(ILI9341_Dev.Set_X_CMD); 
		ILI9341_WriteData(0);
		ILI9341_WriteData(0);
		ILI9341_WriteData((ILI9341_Dev.Width-1)>>8);
		ILI9341_WriteData((ILI9341_Dev.Width-1)&0XFF);
		ILI9341_WriteCMD(ILI9341_Dev.Set_Y_CMD); 
		ILI9341_WriteData(0);
		ILI9341_WriteData(0);
		ILI9341_WriteData((ILI9341_Dev.Height-1)>>8);
		ILI9341_WriteData((ILI9341_Dev.Height-1)&0XFF);  


}   


//快速画点
//x,y:坐标
//color:颜色
void ILI9341_DrawPoint(u16 x,u16 y,u16 color)
{	   
	ILI9341_WriteCMD(ILI9341_Dev.Set_X_CMD); 
	ILI9341_WriteData(x>>8);
	ILI9341_WriteData(x&0XFF);  			 
	ILI9341_WriteCMD(ILI9341_Dev.Set_Y_CMD); 
	ILI9341_WriteData(y>>8);
	ILI9341_WriteData(y&0XFF); 		 	 			 
	ILI9341_WriteToRAM();
	LCD->ILI9341_RAM=color; 
}




//设置背光LED亮度
void ILI9341_Set_BackLight(u8 pwm)
{	
	ILI9341_WriteCMD(ILI9341_WCD);	    //亮度控制
	ILI9341_WriteData(0x2C);

	ILI9341_WriteCMD(ILI9341_BACKLIGHT8);	//配置PWM模式
	ILI9341_WriteData(0x00);	

	ILI9341_WriteCMD(ILI9341_BACKLIGHT7);	//配置PWM输出
	ILI9341_WriteData(pwm);	        //1设置PWM频率

}



//设置LCD显示方向
//Dir:0,竖屏；1,横屏
void ILI9341_Display_Dir(u8 Dir)
{
	if(Dir==Vertical)			//竖屏
	{
		ILI9341_Dev.Dir=Vertical;	//竖屏
		ILI9341_Dev.Width=ILI9341_WIDTH;
		ILI9341_Dev.Height=ILI9341_HIGH;
		ILI9341_Dev.UpToGRAM=ILI9341_GRAM;
		ILI9341_Dev.Set_X_CMD=ILI9341_COLUMN_ADDR;
		ILI9341_Dev.Set_Y_CMD=ILI9341_PAGE_ADDR;  
		ILI9341_WriteData_Dir(L2R_U2D);	//默认填充方向	 
	}
	else 				//横屏
	{	  				
		ILI9341_Dev.Dir=Horizontal;	//横屏
		ILI9341_Dev.Width=ILI9341_HIGH;
		ILI9341_Dev.Height=ILI9341_WIDTH;
		ILI9341_Dev.UpToGRAM=ILI9341_GRAM;
		ILI9341_Dev.Set_X_CMD=ILI9341_COLUMN_ADDR;
		ILI9341_Dev.Set_Y_CMD=ILI9341_PAGE_ADDR;  	 
		ILI9341_WriteData_Dir(U2D_R2L);	//默认填充方向
	} 
	
}




//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//Width,Height:窗口宽度和高度,必须大于0!!
//窗体大小:Width*Height. 
void ILI9341_Set_Window(u16 sx,u16 sy,u16 Width,u16 Height)
{    
	u16 twidth,theight;
	twidth=sx+Width-1;
	theight=sy+Height-1;


	if(ILI9341_Dev.Dir == Horizontal)  //横屏
	{
		if(   twidth > (ILI9341_HIGH-1) ||
			  theight > (ILI9341_WIDTH-1)
			)
		{
			twidth = ILI9341_HIGH -1;
			theight = ILI9341_WIDTH -1;	
		}

	}
	else
	{

		if(   twidth > (ILI9341_WIDTH-1) ||
			  theight > (ILI9341_HIGH-1)
			)
		{
			twidth = ILI9341_WIDTH -1;
			theight = ILI9341_HIGH -1;
			
		}
	}

	ILI9341_WriteCMD(ILI9341_Dev.Set_X_CMD); 
	ILI9341_WriteData(sx>>8); 
	ILI9341_WriteData(sx&0XFF);	 
	ILI9341_WriteData(twidth>>8); 
	ILI9341_WriteData(twidth&0XFF);  
	ILI9341_WriteCMD(ILI9341_Dev.Set_Y_CMD); 
	ILI9341_WriteData(sy>>8); 
	ILI9341_WriteData(sy&0XFF); 
	ILI9341_WriteData(theight>>8); 
	ILI9341_WriteData(theight&0XFF); 
	
}










//初始化lcd
void ILI9341_Init(void)
{ 	
	ILI9341_IO_Init();
	ILI9341_DMA_Init();

	ILI9341_Reset();
	ILI9341_Delay(100);//NOP
	//读设备ID	
	ILI9341_GetID();   			   

	ILI9341_WriteCMD(ILI9341_POWERB);  //功耗B设置
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0xC1); 
	ILI9341_WriteData(0X30);

	ILI9341_WriteCMD(ILI9341_POWER_SEQ);  //电源序列设置
	ILI9341_WriteData(0x64); 
	ILI9341_WriteData(0x03); 
	ILI9341_WriteData(0X12); 
	ILI9341_WriteData(0X81); 

	ILI9341_WriteCMD(ILI9341_DTCA);  //驱动时序A设置
	ILI9341_WriteData(0x85); 
	ILI9341_WriteData(0x10); 
	ILI9341_WriteData(0x7A); 

	ILI9341_WriteCMD(ILI9341_POWERA);  //功耗设置A
	ILI9341_WriteData(0x39); 
	ILI9341_WriteData(0x2C); 
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x34); 
	ILI9341_WriteData(0x02); 

	ILI9341_WriteCMD(ILI9341_PRC);  //泵比控制
	ILI9341_WriteData(0x20); 

	ILI9341_WriteCMD(ILI9341_DTCB);  //驱动时序B设置


	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x00); 

	ILI9341_WriteCMD(ILI9341_POWER1);    //功耗1设置
	ILI9341_WriteData(0x1B);   //VRH[5:0] 

	ILI9341_WriteCMD(ILI9341_POWER2);    //功耗2设置
	ILI9341_WriteData(0x01);   //SAP[2:0];BT[3:0] 

	ILI9341_WriteCMD(ILI9341_VCOM1);    //VCM 控制 1
	ILI9341_WriteData(0x30); 	 //3F
	ILI9341_WriteData(0x30); 	 //3C

	ILI9341_WriteCMD(ILI9341_VCOM2);    //VCM 控制 2
	ILI9341_WriteData(0XB7); 

	ILI9341_WriteCMD(ILI9341_MAC);    // 存储器访问控制 
	ILI9341_WriteData(0x48); 

	ILI9341_WriteCMD(ILI9341_PIXEL_FORMAT);   //像素格式控制
	ILI9341_WriteData(0x55); 

	ILI9341_WriteCMD(ILI9341_FRMCTR1);   //帧速率控制
	ILI9341_WriteData(0x00);   
	ILI9341_WriteData(0x10); 

	ILI9341_WriteCMD(ILI9341_DFC);    // 显示功能控制
	ILI9341_WriteData(0x0A); 
	ILI9341_WriteData(0xA2); 

	ILI9341_WriteCMD(ILI9341_3GAMMA_EN);    // 伽马3使能
	ILI9341_WriteData(0x00); 

	ILI9341_WriteCMD(ILI9341_GAMMA);    //伽马设置
	ILI9341_WriteData(0x01); 

	ILI9341_WriteCMD(ILI9341_PGAMMA);    //正极伽马校准
	ILI9341_WriteData(0x0F); 
	ILI9341_WriteData(0x2A); 
	ILI9341_WriteData(0x28); 
	ILI9341_WriteData(0x08); 
	ILI9341_WriteData(0x0E); 
	ILI9341_WriteData(0x08); 
	ILI9341_WriteData(0x54); 
	ILI9341_WriteData(0XA9); 
	ILI9341_WriteData(0x43); 
	ILI9341_WriteData(0x0A); 
	ILI9341_WriteData(0x0F); 
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x00); 	

	ILI9341_WriteCMD(ILI9341_NGAMMA);    //负极伽马校准
	ILI9341_WriteData(0x00); 
	ILI9341_WriteData(0x15); 
	ILI9341_WriteData(0x17); 
	ILI9341_WriteData(0x07); 
	ILI9341_WriteData(0x11); 
	ILI9341_WriteData(0x06); 
	ILI9341_WriteData(0x2B); 
	ILI9341_WriteData(0x56); 
	ILI9341_WriteData(0x3C); 
	ILI9341_WriteData(0x05); 
	ILI9341_WriteData(0x10); 
	ILI9341_WriteData(0x0F); 
	ILI9341_WriteData(0x3F); 
	ILI9341_WriteData(0x3F); 
	ILI9341_WriteData(0x0F); 

	ILI9341_WriteCMD(ILI9341_PAGE_ADDR); //行地址设置
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x01);
	ILI9341_WriteData(0x3f);

	ILI9341_WriteCMD(ILI9341_COLUMN_ADDR); //列地址设置
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0xef);	 

	ILI9341_WriteCMD(ILI9341_SLEEP_OUT); //退出睡眠
	Delay_ms(120);
	ILI9341_WriteCMD(ILI9341_DISPLAY_ON); //开显示
 
	ILI9341_Display_Dir(Vertical);		//默认为竖屏	
	ILI9341_Clear(WHITE);
	ILI9341_GetState(&ILI9341_State);
	ILI9341_BACK_LIGHT_ON;
}  



//清屏函数
//color:要清屏的填充色
void ILI9341_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=ILI9341_Dev.Width;
	totalpoint*=ILI9341_Dev.Height; 			//得到总点数
	ILI9341_SetXY_Start(0x00,0x00);		//设置光标位置 
	ILI9341_WriteToRAM();     		//开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->ILI9341_RAM=color;	
	}
}  




void ILI9341_ShowPicture()
{
    
	u32 x=0,y=0;
	Data_Buff DataTemp;				//存放LCD ID字符串
	static u32 P=0;
	//u32 totalpoint=ILI9341_Dev.Height*ILI9341_Dev.Width; 			//得到总点数
	//  ILI9341_Display_Dir(Vertical);
	//  ILI9341_SetXY_Area(0,0,239,319);	//设置光标位置 
	//  ILI9341_WriteToRAM();     		//开始写入GRAM


	FIL fils;
////////////////////////////////////////////////////////////

	// totalpoint=File_GetFileSize("1:/SD/Data_1.bin");

	// File_ReadData("1:/SD/Data_1.bin",(u8*)&(LCD->ILI9341_RAM),totalpoint,P);

////////////////////////////////////////////////////////////
		// ST7789_SetArea(0,y*10-1,239,y*10+10-1);
		ST7789_SetArea(0,0,239,239);
		for(y=0;y<24;y++)
		{
			File_ReadData(&fils,"1:/SD/Data_1.bin",DataTemp.Data_8,4800,P);
			P+=4800;

			ST7789_DMA_SetAddr((u32)(DataTemp.Data_8),2400);
			ST7789_DMA_Start();
			while (ST7789_DMA_GetTXState() != TRUE);
		}

		// //Delay_ms(100);

		// P=0;
		// for(y=0;y<64;y++)
		// {
		// 	File_ReadData(&fils,"1:/SD/Data_2.bin",DataTemp.Data_8,2400,P);
		// 	P+=2400;		
		// 	for(x=0;x<1200;x++)
		// 	{
		// 		ILI9341_WriteData(DataTemp.Data_16[x]);
		// 	}
		// }

		// //Delay_ms(100);

		// ILI9341_Display_Dir(Horizontal);
	 	// ILI9341_SetXY_Area(0,0,319,239);	//设置光标位置 
		// ILI9341_WriteToRAM();     		//开始写入GRAM
		// P=0;
		// for(y=0;y<240;y++)
		// {
		// 	File_ReadData(&fils,"1:/SD/Data_3.bin",DataTemp.Data_8,640,P);
		// 	P+=640;		
		// 	for(x=0;x<320;x++)
		// 	{
		// 		ILI9341_WriteData(DataTemp.Data_16[x]);
		// 	}
		// }
		//Delay_ms(100);

//////////////////////////////////////////////////////////////////

} 


// void DMA2_Stream3_IRQHandler()
// {
//     if(DMA_GetITStatus(DMA2_Stream3,DMA_IT_TCIF3))
//     {
//         DMA_ClearITPendingBit(DMA2_Stream3,DMA_IT_TCIF3);

//         if( ILI9341_DMA_ISR_GetTXComplateFlag() == TRUE )
//         {
//             ILI9341_DMA_Stop();
//             LED1_ON;
//         }
//         else
//         {
//             ILI9341_DMA_Start();
//         }
//     }    
// }


//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void ILI9341_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		ILI9341_SetXY_Start(sx,i);      				//设置光标位置 
		ILI9341_WriteToRAM();     			//开始写入GRAM	  
		for(j=0;j<xlen;j++)
			LCD->ILI9341_RAM=color;	//显示颜色 	    
	} 
}  





//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void ILI9341_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 Height,Width;
	u16 i,j;
	Width=ex-sx+1; 			//得到填充的宽度
	Height=ey-sy+1;			//高度
 	for(i=0;i<Height;i++)
	{
 		ILI9341_SetXY_Start(sx,sy+i);   	//设置光标位置 
		ILI9341_WriteToRAM();     //开始写入GRAM
		for(j=0;j<Width;j++)LCD->ILI9341_RAM=color[i*Width+j];//写入数据 
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
void ILI9341_DMA_SetAddr(u32 StartAddr, u32 Point)
{
    DMA_TXCurrentAddr = StartAddr;
    DMA_EndAddr = StartAddr + Point;
	SendLength =0;
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
u8 ILI9341_DMA_GetTXComplateFlag()
{
	DMA_TXCurrentAddr += SendLength;

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
//  说明: 启动DMA传输时先调用 ILI9341_DMA_SetAddr(),确定数据起始地址和长度
//        中断里直接调用
//***************************************************//
void ILI9341_DMA_Start()
{
    SendLength = (DMA_EndAddr - DMA_TXCurrentAddr);

    if( SendLength > DMA_MAX_BUFF )
    {
        SendLength = DMA_MAX_BUFF;
    }

    DMA_Cmd(DMA2_Stream1,DISABLE);
	DMA2_Stream1->PAR = DMA_TXCurrentAddr;
	DMA2_Stream1->NDTR = SendLength;
    DMA_Cmd(DMA2_Stream1,ENABLE);
    
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
void ILI9341_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream1,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
	SendLength = 0;
}



















// u32 i=0,k=0;

// u8 Flag=TRUE;

// u32 Total=1600;
// u32 Lengthddd=0;
// u32 SendLen=0;

// u8 xxx=0,yyy=0;
// u16 CData[] = {WHITE,BLACK,BLUE,BRRED,RED,GREEN,YELLOW,BRRED,MAGENTA,BLUE,GRAY,RED,GRED,MAGENTA,WHITE,BLACK,BLUE,GBLUE,RED,GREEN,YELLOW};

// void DMATest()
// {
// 	if( Flag == TRUE )
// 	{

//         ILI9341_SetXY_Area(xxx,0+xxx,39+xxx,39+xxx);
//         ILI9341_WriteToRAM();
// 		xxx++;
// 		// LED1_ON;
// 		// for (i = 0; i < 240*80; i++)
// 		// {
// 		// 	ILI9341_WriteData(CData[k]);
// 		// }
// 		// k++;

// 		if( Total >= DMA_MAX_BUFF)
// 		{
// 			Lengthddd = DMA_MAX_BUFF;
// 		}
// 		else
// 		{
// 			Lengthddd = Total;
// 		}
// 		SendLen  =0;
// 		Flag = FALSE;
// 		DMA_Cmd(DMA2_Stream1,DISABLE);
// 		DMA2_Stream1->PAR = (u32)(&CData[k]);
// 		DMA2_Stream1->NDTR = Lengthddd;
// 		DMA_Cmd(DMA2_Stream1,ENABLE);
// 		LED1_ON;
// 		k++;
// 		if(k>=sizeof(CData)/sizeof(CData[0]))
// 		{
// 			k=0;
// 		}
// 	}
// }






// void DMA2_Stream1_IRQHandler()
// {
// 	u32 Length;

//     if(DMA_GetITStatus(DMA2_Stream1,DMA_IT_TCIF1))
//     {
//         DMA_ClearITPendingBit(DMA2_Stream1,DMA_IT_TCIF1);

// 		SendLen += Lengthddd;

// 		if( SendLen < Total)
// 		{
// 			DMA_Cmd(DMA2_Stream1,DISABLE);

// 			Lengthddd = Total - SendLen;

// 			if(  Lengthddd >= DMA_MAX_BUFF )
// 			{
// 				Lengthddd = DMA_MAX_BUFF;
// 			}

// 			DMA2_Stream1->NDTR = Lengthddd;

// 			DMA_Cmd(DMA2_Stream1,ENABLE);
// 		}
// 		else
// 		{
// 			DMA_Cmd(DMA2_Stream1,DISABLE);
// 			Flag = TRUE;
// 			//LED_Freq();
// 			LED1_OFF;
// 		}
//     }    

// }







