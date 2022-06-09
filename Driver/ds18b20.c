#include"IncludeFile.h"


 //PC8 --------DATE

static void GPIO_Out(u8 state)
{

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_8;                       
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);

	if(state == HIGH )
	{	
		DS18B20_HIGH;
	}
	else 
	{	
		DS18B20_LOW;
	}
}




static void GPIO_In()
{
	GPIO_InitTypeDef GPIOB_Initstruc;
	
	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_8;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);
}



void DS18B20_Write_Byte(u8 data)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		GPIO_Out(LOW); 
		Delay_us(15);		
		if((0x01&data)==0)
		{		
			GPIO_Out(LOW); 
		}
		else
		{		
			GPIO_Out(HIGH); 
		}

		Delay_us(55);
		GPIO_Out(HIGH); 
		data = data>>1;
		Delay_us(3);
	}
}
	

u8 DS18B20_Read_Byte()
{
	char i;
	u32	data=0;
	u32 temp=0;		
	for(i=0;i<8;i++)
	{
		GPIO_Out(LOW);
		Delay_us(8);
		GPIO_Out(HIGH);
		GPIO_In();	

		if(IO_STATE==1)
		{
			temp=0x80;
		}
		else
		{
			temp=0x00;
		}

		Delay_us(40);
		data=data|(temp>>(7-i));
		GPIO_Out(HIGH);
		Delay_us(4);
	}
	return data;
}
	
u8 DS18B20_Init()
{
	u8 State=0;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_Out(HIGH); 
	Delay_us(10);
  	GPIO_Out(LOW);        //拉低总线		
	Delay_us(500);
	GPIO_Out(HIGH);      	//释放总线
	GPIO_In();
	Delay_us(120);		//延时检测
	
	if(IO_STATE==0)        //18b20应答检测
	{	
		State = TRUE;
	}
	else
	{
		State = FALSE;
	}
	GPIO_Out(HIGH);
	
	return State;
}

void Get_Temperature(u8 *Temperature)
{
	u8 LSB,MSB;
	u32 wendu;
	
	__disable_irq();
	
	if(DS18B20_Init()==TRUE)
	{
		DS18B20_Write_Byte(0xcc);
		DS18B20_Write_Byte(0x44);

		DS18B20_Init();

		DS18B20_Write_Byte(0xcc);
		DS18B20_Write_Byte(0xbe);

		LSB=DS18B20_Read_Byte();
		MSB=DS18B20_Read_Byte();
	
	wendu=(LSB|((MSB&0x7)<<8))*625;
	*Temperature=(u8)(wendu/10000);
		
	}
	__enable_irq();


}
