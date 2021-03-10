#include"IncludeFile.h"

/*





124




u8 i=1;

/*
����
����
˳��
8*16
*/
void OLED_ShowChar(u8 x,u8 y,u8* Data)
{
	u8 k,l;
	for(k=0;k<2;k++)
	{
		for(l=0;l<8;l++)
			OLED_GRAM[7-k-y][l+x]|=Data[k*8+l];          //���ϵ����֤
	}

}

void OLED_ShowStrings(u8 x,u8 y,u8* Data,u8 Length)
{	
	u8 PositionBuff[64];
	u8 i;

	if( Length > 64 || Length == 0 )
	 	return;    //d�������64��(8*16�ߴ���ַ�)

	while( i < Length )
	{
		if( '0' <= Data[i] &&  Data[i] <= '9')
		{
			PositionBuff[i]=Data[i]-'0';
		}
		else if('A' <= Data[i] &&  Data[i] <= 'Z')
		{
			PositionBuff[i]=Data[i]-'A'+10;	   //�������б���(0~9)��ƫ��
		}
		else if('a' <= Data[i] &&  Data[i] <= 'z')
		{
			PositionBuff[i]=Data[i]-'a'+36;		//�������б���(0~9,A~Z)��ƫ��
		}
		else
		{
			PositionBuff[i]=0xFF;         
		}

		i++;
	}


}









int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	usart_init(115200);
	led_init();
	OLED_Init();



//show_All();

	
	while(1)
	{	


		LED1_OFF;
		delay_ms(100);
		LED1_ON;
		delay_ms(100);

		OLED_UpdateGRAM();

	}



	
}	

	












