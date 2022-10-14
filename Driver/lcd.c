#include "IncludeFile.h"
#include "font.h" 

//����������ݵĴ�С
#define POINT_SIZE  (sizeof(u16))

//DMA ������������
#define DMA_MAX_BUFF  (60000)

static u32 DMA_TXCurrentAddr,DMA_EndAddr,SendLength;


//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=RED;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 
//DMA������Ʋ���


//����LCD��Ҫ����
//Ĭ��Ϊ����
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
//дָ���
//regval:ָ��ֵ
void LCD_WriteCMD(vu16 regval)
{   
	LCD->LCD_REG=regval;//д��Ҫд��ָ�����	 
}


//дLCD����
//data:Ҫд���ֵ
void LCD_WriteData(vu16 data)
{	  
	LCD->LCD_RAM=data;		 
}


//��LCD����
//����ֵ:������ֵ
u16 LCD_ReadData(void)
{
	vu16 ram;			//��ֹ���Ż�
	ram=LCD->LCD_RAM;	
	return ram;	 
}


//������дָ��
//LCD_Cmd:ָ���ַ
//LCD_CmdValue:Ҫд�������
void LCD_WriteCmdPara(vu16 LCD_Cmd,vu16 LCD_CmdValue)
{	
	LCD->LCD_REG = LCD_Cmd;		//д��Ҫд��ָ�����	 
	LCD->LCD_RAM = LCD_CmdValue;//д������	    		 
}


//��ID
//LCD_Cmd:ָ���ַ
//����ֵ:����������
u16 LCD_ReadID(u16 LCD_Cmd)
{										   
	LCD_WriteCMD(LCD_Cmd);		//д��Ҫ����ָ�����
	Delay_us(5);		  
	return LCD_ReadData();		//���ض�����ֵ
} 



//�����λ
void LCD_Reset()
{
	LCD_WriteCMD(LCD_SWRESET);
	Delay_ms(7);
}



//��ʼдGRAM
void LCD_WriteToRAM(void)
{
 	LCD->LCD_REG=LCD_Dev.UpToGRAM;	  
}	


//LCD������ʾ
void LCD_DisplayOn(void)
{					   
	LCD_WriteCMD(LCD_DISPLAY_ON);	//������ʾ
	LCD_BACK_LIGHT_ON;
}	


//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
	LCD_WriteCMD(LCD_DISPLAY_OFF);	//�ر���ʾ
	LCD_BACK_LIGHT_OFF;
} 


//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 


//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
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



void LCD_IO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��PD,PE,PF,PGʱ��  
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//ʹ��FSMCʱ��  
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PB15 �������,���Ʊ���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ�� //PB15 �������,���Ʊ���

	GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��  

	GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PF12,FSMC_A6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PF12,FSMC_A6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ�� 

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


	readWriteTiming.FSMC_AddressSetupTime = 0X01;	 //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns	
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
	readWriteTiming.FSMC_DataSetupTime = 10;			//���ݱ���ʱ��Ϊ60��HCLK	=6*60=360ns
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 


	writeTiming.FSMC_AddressSetupTime =0x01;	      //��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns 
	writeTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
	writeTiming.FSMC_DataSetupTime = 10;		 //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
	writeTiming.FSMC_BusTurnAroundDuration = 0x00;
	writeTiming.FSMC_CLKDivision = 0x00;
	writeTiming.FSMC_DataLatency = 0x00;
	writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 


	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK1 

}


//��ȡID
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



//��ѯ��ʾģʽ(ֻ֧�ֲ��ֲ�������Ҫ��ѯ��������ʱ���������)
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



//���ù����ʼλ��
//Xpos:������
//Ypos:������
void LCD_SetXY_Start(u16 Xpos, u16 Ypos)
{ 	    
	LCD_WriteCMD(LCD_Dev.Set_X_CMD); 
	LCD_WriteData(Xpos>>8);
	LCD_WriteData(Xpos&0XFF); 
	LCD_WriteCMD(LCD_Dev.Set_Y_CMD); 
	LCD_WriteData(Ypos>>8);
	LCD_WriteData(Ypos&0XFF); 
		
} 


//���ù���ƶ���Χ
//  x_S  x��ʼ
//  y_S  x����
//  x_E  y��ʼ
//  y_E  y����

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





//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;

	if(LCD_Dev.Dir == Horizontal)  //����
	{
		if(   x > (LCD_HIGH-1) ||
			  y > (LCD_WIDTH-1)
			)
		{
			return 0;	//�����˷�Χ,ֱ�ӷ���	
		}
	}
	else
	{
		if(   x > (LCD_WIDTH-1) ||
			  y > (LCD_HIGH-1)
			)
		{
			return 0;	//�����˷�Χ,ֱ�ӷ���			
		}
	}

	LCD_SetXY_Start(x,y);	    
	LCD_WriteCMD(LCD_RAMRD);	//��GRAM
 	LCD_ReadData();	

 	r = LCD_ReadData();  		//ʵ��������ɫ  
	b = LCD_ReadData() >> 11; 
	g = r & 0x00FC;
	r &= 0xF800;	 
	g <<= 3;
	return r|g|b;
}


//��ֱ��������
// XStart:��ʼ��
// Xend:��ֹ��
// High:��������߶�(��λ����)
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




//����LCD������д�뷽��  	   
void LCD_WriteData_Dir(u8 Dir)
{
	u16 regval=0;
	u16 temp;  
	
	switch(Dir)
	{
		case L2R_U2D://������,���ϵ���
			regval|=(0<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case L2R_D2U://������,���µ���
			regval|=(1<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case R2L_U2D://���ҵ���,���ϵ���
			regval|=(0<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;
		case R2L_D2U://���ҵ���,���µ���
			regval|=(1<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(0<<XY_Dir_ExchengeBit); 
			break;	 
		case U2D_L2R://���ϵ���,������
			regval|=(0<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case U2D_R2L://���ϵ���,���ҵ���
			regval|=(0<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case D2U_L2R://���µ���,������
			regval|=(1<<Y_Dir_Bit)|(0<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;
		case D2U_R2L://���µ���,���ҵ���
			regval|=(1<<Y_Dir_Bit)|(1<<X_Dir_Bit)|(1<<XY_Dir_ExchengeBit); 
			break;	 
	}


		regval|=0X08;//5310/5510/1963����ҪBGR    

		LCD_WriteCmdPara(LCD_MAC,regval);

		if(regval&0X20)
		{
			if(LCD_Dev.Width<LCD_Dev.Height)//����X,Y
			{
				temp=LCD_Dev.Width;
				LCD_Dev.Width=LCD_Dev.Height;
				LCD_Dev.Height=temp;
			}
		}
		else  
		{
			if(LCD_Dev.Width>LCD_Dev.Height)//����X,Y
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


//���ٻ���
//x,y:����
//color:��ɫ
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




//���ñ���LED����
void LCD_Set_BackLight(u8 pwm)
{	
	LCD_WriteCMD(LCD_WCD);	    //���ȿ���
	LCD_WriteData(0x2C);

	LCD_WriteCMD(LCD_BACKLIGHT8);	//����PWMģʽ
	LCD_WriteData(0x00);	

	LCD_WriteCMD(LCD_BACKLIGHT7);	//����PWM���
	LCD_WriteData(pwm);	        //1����PWMƵ��

}



//����LCD��ʾ����
//Dir:0,������1,����
void LCD_Display_Dir(u8 Dir)
{
	if(Dir==Vertical)			//����
	{
		LCD_Dev.Dir=Vertical;	//����
		LCD_Dev.Width=LCD_WIDTH;
		LCD_Dev.Height=LCD_HIGH;
		LCD_Dev.UpToGRAM=LCD_GRAM;
		LCD_Dev.Set_X_CMD=LCD_COLUMN_ADDR;
		LCD_Dev.Set_Y_CMD=LCD_PAGE_ADDR;  
		LCD_WriteData_Dir(L2R_U2D);	//Ĭ����䷽��	 
	}
	else 				//����
	{	  				
		LCD_Dev.Dir=Horizontal;	//����
		LCD_Dev.Width=LCD_HIGH;
		LCD_Dev.Height=LCD_WIDTH;
		LCD_Dev.UpToGRAM=LCD_GRAM;
		LCD_Dev.Set_X_CMD=LCD_COLUMN_ADDR;
		LCD_Dev.Set_Y_CMD=LCD_PAGE_ADDR;  	 
		LCD_WriteData_Dir(U2D_R2L);	//Ĭ����䷽��
	} 
	
}




//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//Width,Height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:Width*Height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 Width,u16 Height)
{    
	u16 twidth,theight;
	twidth=sx+Width-1;
	theight=sy+Height-1;


	if(LCD_Dev.Dir == Horizontal)  //����
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










//��ʼ��lcd
void LCD_Init(void)
{ 	
	LCD_IO_Init();
	LCD_DMA_Init();

	LCD_Reset();
	LCD_Delay(100);//NOP
	//���豸ID	
	LCD_GetID();   			   

	LCD_WriteCMD(LCD_POWERB);  //����B����
	LCD_WriteData(0x00); 
	LCD_WriteData(0xC1); 
	LCD_WriteData(0X30);

	LCD_WriteCMD(LCD_POWER_SEQ);  //��Դ��������
	LCD_WriteData(0x64); 
	LCD_WriteData(0x03); 
	LCD_WriteData(0X12); 
	LCD_WriteData(0X81); 

	LCD_WriteCMD(LCD_DTCA);  //����ʱ��A����
	LCD_WriteData(0x85); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x7A); 

	LCD_WriteCMD(LCD_POWERA);  //��������A
	LCD_WriteData(0x39); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x34); 
	LCD_WriteData(0x02); 

	LCD_WriteCMD(LCD_PRC);  //�ñȿ���
	LCD_WriteData(0x20); 

	LCD_WriteCMD(LCD_DTCB);  //����ʱ��B����


	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 

	LCD_WriteCMD(LCD_POWER1);    //����1����
	LCD_WriteData(0x1B);   //VRH[5:0] 

	LCD_WriteCMD(LCD_POWER2);    //����2����
	LCD_WriteData(0x01);   //SAP[2:0];BT[3:0] 

	LCD_WriteCMD(LCD_VCOM1);    //VCM ���� 1
	LCD_WriteData(0x30); 	 //3F
	LCD_WriteData(0x30); 	 //3C

	LCD_WriteCMD(LCD_VCOM2);    //VCM ���� 2
	LCD_WriteData(0XB7); 

	LCD_WriteCMD(LCD_MAC);    // �洢�����ʿ��� 
	LCD_WriteData(0x48); 

	LCD_WriteCMD(LCD_PIXEL_FORMAT);   //���ظ�ʽ����
	LCD_WriteData(0x55); 

	LCD_WriteCMD(LCD_FRMCTR1);   //֡���ʿ���
	LCD_WriteData(0x00);   
	LCD_WriteData(0x10); 

	LCD_WriteCMD(LCD_DFC);    // ��ʾ���ܿ���
	LCD_WriteData(0x0A); 
	LCD_WriteData(0xA2); 

	LCD_WriteCMD(LCD_3GAMMA_EN);    // ٤��3ʹ��
	LCD_WriteData(0x00); 

	LCD_WriteCMD(LCD_GAMMA);    //٤������
	LCD_WriteData(0x01); 

	LCD_WriteCMD(LCD_PGAMMA);    //����٤��У׼
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

	LCD_WriteCMD(LCD_NGAMMA);    //����٤��У׼
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

	LCD_WriteCMD(LCD_PAGE_ADDR); //�е�ַ����
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x3f);

	LCD_WriteCMD(LCD_COLUMN_ADDR); //�е�ַ����
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0xef);	 

	LCD_WriteCMD(LCD_SLEEP_OUT); //�˳�˯��
	Delay_ms(120);
	LCD_WriteCMD(LCD_DISPLAY_ON); //����ʾ
 
	LCD_Display_Dir(Vertical);		//Ĭ��Ϊ����	
	LCD_Clear(WHITE);
	LCD_GetState(&LCD_State);
	LCD_BACK_LIGHT_ON;
}  



//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=LCD_Dev.Width;
	totalpoint*=LCD_Dev.Height; 			//�õ��ܵ���
	LCD_SetXY_Start(0x00,0x00);		//���ù��λ�� 
	LCD_WriteToRAM();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
	}
}  




void LCD_ShowPicture()
{
    
	u32 x=0,y=0;
	Data_Buff DataTemp;				//���LCD ID�ַ���
	u32 P=0;
	//u32 totalpoint=LCD_Dev.Height*LCD_Dev.Width; 			//�õ��ܵ���
	 LCD_Display_Dir(Vertical);
	 LCD_SetXY_Area(0,0,239,319);	//���ù��λ�� 
	 LCD_WriteToRAM();     		//��ʼд��GRAM
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
	 	LCD_SetXY_Area(0,0,319,239);	//���ù��λ�� 
		LCD_WriteToRAM();     		//��ʼд��GRAM
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





//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		LCD_SetXY_Start(sx,i);      				//���ù��λ�� 
		LCD_WriteToRAM();     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)
			LCD->LCD_RAM=color;	//��ʾ��ɫ 	    
	} 
}  





//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 Height,Width;
	u16 i,j;
	Width=ex-sx+1; 			//�õ����Ŀ��
	Height=ey-sy+1;			//�߶�
 	for(i=0;i<Height;i++)
	{
 		LCD_SetXY_Start(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteToRAM();     //��ʼд��GRAM
		for(j=0;j<Width;j++)LCD->LCD_RAM=color[i*Width+j];//д������ 
	}		  
}  



//***************************************************//
//  ��������: DMA����������ʼ��ַ�ͳ���
//  
//  ����: ���ݵ�ַ������
//  
//  ����ֵ: TRUE / FALSE
//  
//  ˵��: 
//  
//***************************************************//
void LCD_DMA_SetAddr(u32 StartAddr, u32 Point)
{
    DMA_TXCurrentAddr = StartAddr;
    DMA_EndAddr = StartAddr + Point;
}

//***************************************************//
//  ��������: ��ȡ��ǰ���͵�ַ
//  
//  ����: ��
//  
//  ����ֵ: u32
//  
//  ˵��: ��
//  
//***************************************************//
u32 LCD_DMA_GetCurrentAddr()
{
    return DMA_TXCurrentAddr;
}

//***************************************************//
//  ��������: ��ȡDMA����״̬
//  
//  ����: 
//  
//  ����ֵ: TRUE�������/ FALSE��δ���
//  
//  ˵��: ��
//  
//***************************************************//
u8 LCD_DMA_GetTXComplateFlag()
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
//  ��������: ����DMA����
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ����DMA����ʱ�ȵ��� TFT_DMA_SetAddr(),ȷ��������ʼ��ַ�ͳ���
//        �ж���ֱ�ӵ���
//***************************************************//
void LCD_DMA_Start()
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
//  ��������: ֹͣDMA
//  
//  ����: ��
//  
//  ����ֵ: 
//  
//  ˵��: ���ݴ��䵽���趨���Ⱥ�ֹͣDMA
//  
//***************************************************//
void LCD_DMA_Stop()
{
    DMA_Cmd(DMA2_Stream1,DISABLE);
    DMA_TXCurrentAddr = 0;
    DMA_EndAddr = 0;
	SendLength = 0;
}



















// u32 i=0,k=0;

// u8 Flag=TRUE;

// u32 Total=240*320;
// u32 Lengthddd=0;
// u32 SendLen=0;

// u16 CData[] = {WHITE,BLACK,BLUE,GBLUE,RED,GREEN,YELLOW,BRRED,MAGENTA,BLUE,GRAY,RED,GRED,MAGENTA,WHITE,BLACK,BLUE,GBLUE,RED,GREEN,YELLOW};

// void DMATest()
// {
// 	if( Flag == TRUE )
// 	{

//         LCD_SetXY_Area(0,0,239,319);
//         LCD_WriteToRAM();

// 		LED1_ON;
// 		for (i = 0; i < 240*80; i++)
// 		{
// 			LCD_WriteData(CData[k]);
// 		}
// 		k++;

// 		// if( Total >= DMA_MAX_BUFF)
// 		// {
// 		// 	Lengthddd = DMA_MAX_BUFF;
// 		// }
// 		// else
// 		// {
// 		// 	Lengthddd = Total;
// 		// }
// 		// SendLen  =0;
// 		// Flag = FALSE;
// 		// DMA_Cmd(DMA2_Stream1,DISABLE);
// 		// DMA2_Stream1->PAR = (u32)(&CData[k]);
// 		// DMA2_Stream1->NDTR = Lengthddd;
// 		// DMA_Cmd(DMA2_Stream1,ENABLE);
// 		// LED1_ON;

// 		if(k>=sizeof(CData)/sizeof(CData[0])-4)
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
// 			LED_Freq();
// 			LED1_OFF;
// 		}
//     }    

// }







