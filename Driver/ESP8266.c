#include"IncludeFile.h"



//设置AP模式时的参数///
char CMD_RST[]="AT+RST\r\n";
char CMD_CWMODE[]="AT+CWMODE=3\r\n";
char CMD_CWSAP[]="AT+CWSAP=\"DEVICE1\",\"123456789\",6,3\r\n";
char CMD_CIFSR[]="AT+CIFSR\r\n";
char CMD_CIPMUX[]="AT+CIPMUX=1\r\n";
char CMD_CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";
char CMD_CIPSEND[]="AT+CIPSEND=0,79\r\n";
char Wifi_Name[]="WIFI:DEVICE1";
char Wifi_Password[]="KEY:123456789";
char Port[]="PORT:8080";

//设置STA模式时的参数///


char Local_IP[12];
char Net_Name[15];
char Net_Password[10];
char Wifi_Data[300];
u8 USED_FLAG;
u8 DataBuff[1024];



u8 ESP8266_GetDaTaState()
{
	if( USART_GetData(&USART2_Data,sizeof(DataBuff),DataBuff,&length) != TRUE)
	{
		return FALSE;
	}
	return TRUE;
}




void ESP8266_SendData(u8 *Data)
{

}



u8 ESP8266_SearchData(char *Data,u16 DataSzie,u16 *Position)
{	
	u8 i;
	u16 length,k=0;

	if( USART_GetData(&USART2_Data,sizeof(DataBuff),DataBuff,&length) == TRUE)
	{
		do
		{
			if(memcmp(Data,(char *)(DataBuff+k),DataSzie) == 0 )
			{
				*Position = k;
				return TRUE;
			}
			k++;
		}
		while( k < sizeof(DataBuff) );
	}

	return FALSE;

}


void GetConnectState()
{

	if( ESP8266_SearchData("CONNECT",strlen("CONNECT")) != TRUE)
	{
		return 2;
	}

}


u8 ESP8266_CMD_Check()
{

	if ( ESP8266_GetDaTaState() != TRUE )
	{
		
	}




}





u8 ESP8266_Init()
{
	USART_ITSendData(USART2,&USART2_Data,sizeof(CMD_RST),(u8 *)CMD_RST);
	Delay_ms(500);
	if( ESP8266_SearchData("ready",strlen("ready")) != TRUE)
	{
		return 2;
	}
	USART_ITSendData(USART2,&USART2_Data,sizeof(CMD_CIPMUX),(u8 *)CMD_CIPMUX);
	Delay_ms(100);
	if( ESP8266_SearchData("OK",strlen("OK")) != TRUE)
	{
		return 3;
	}
	USART_ITSendData(USART2,&USART2_Data,sizeof(CMD_CIPSERVER),(u8 *)CMD_CIPSERVER);
	Delay_ms(100);
	if( ESP8266_SearchData("OK",strlen("OK")) != TRUE)
	{
		return 4;
	}

	return TRUE;
}



























char Local_IP[12];
char Net_Name[15];
char Net_Password[10];
char Wifi_Data[300];
u8 USED_FLAG;

	
	

// void Set_Mode()
// {	
// 	printf("%s",CMD_RST);
// 	Delay_ms(500);
// 	printf("%s",CMD_CWMODE);
// 	Delay_ms(100);
// 	printf("%s",CMD_CWSAP);
// 	Delay_ms(100);
// 	printf("%s",CMD_CIFSR);
// 	USED_FLAG=1;	                     //清除缓存，从头开始接收
// 	Delay_ms(100);
// 	Get_IP(Wifi_Data,Local_IP);        //提取IP
// 	display_position(0,0,12);
// 	//display_str_and_speed(Wifi_Name,10);
// 	display_position(0,2,13);
// 	//display_str_and_speed(Wifi_Password,10);
// 	display_position(0,4,9);
// 	//display_str_and_speed(Port,10);
// 	display_position(0,6,3);
// 	//display_str_and_speed("IP:",10);
// 	display_position(24,6,11);
// 	//display_str_and_speed(Local_IP,10);
// 	printf("%s",CMD_CIPMUX);
// 	Delay_ms(100);
// 	printf("%s",CMD_CIPSERVER);
// 	Delay_ms(100);
// 	USED_FLAG=1;
// 	while(1)
// 	{
// 		if(Wifi_Data[3]=='O')
// 		{
// 		USED_FLAG=1;
// 		display_position(0,7,3);	
// 		//display_str_and_speed(":OK",10);
//     break;
// 		}
// 		else
// 		{
// 		display_position(0,7,3);	
// 		//display_str_and_speed(":XX",10);
// 	  USED_FLAG=1;
// 		}
		
// 		Delay_ms(100);
// //	  times++;
// //		if(times>250)
// //		{
// //		clear_screen();
// //		display_position(0,0,8);	
// //		//display_str_and_speed("TIME OUT",1);
// //		display_position(0,2,9);	
// //		//display_str_and_speed("TRY RESET",1);
// //		USED_FLAG=1;
// //		break;
// //		}
		
		
// 	}
// printf("%s",CMD_CIPSEND);
// Delay_ms(100);
// printf("%s",user_message);
// Delay_ms(500);
// memset(Wifi_Data,0,sizeof(Wifi_Data));	
// 	while(1)
// 	{
// 		if(Wifi_Data[0]=='+')
// 		{
// //		clear_screen();
// //		show_All();
// //		//display_str_and_speed(Wifi_Data,100);			
			
			
// //    Get_NetName(Wifi_Data,Net_Name);	
// //    Get_NetPassword(Wifi_Data,Net_Password);
// //		display_position(0,1,3);	
// //		//display_str_and_speed(Net_Name,100);	
// //		display_position(0,3,3);	
// //		//display_str_and_speed(Net_Password,10);	
// //		Delay_ms(500);
// 		USED_FLAG=1;			
//     break;
// 		}
// 		else
// 		{

// 	  USED_FLAG=1;
// 		}
		
		
		
// 	}	
	
// 		while(1)
// 		{
// 			clear_screen();
// 			show_All();
// 			//display_str_and_speed(Wifi_Data,100);
			
	
// ////		display_position(0,1,16);	
// //		//display_str_and_speed(Net_Name,100);	
// ////		display_position(0,3,strlen(Net_Password));	
// //		//display_str_and_speed(Net_Password,10);
// //				//display_str_and_speed("OK",10);	
// 			break;

// 		}




// }


//void Get_IP(char *str,char *temp)
//{
//	u8 i=0;
//	str+=24;
//	for(i=0;i<12;i++)
//	{
//	*(temp+i)=*(str+i);	
//	}
//	*(temp+11)='\0';
//	
//}	




// void Get_NetName(char *str,char *temp)
// {
// 	while(*str!='\0')
// 	{
// 		if((*str==*IP_begin)&&*(str+1)==*(IP_begin+1))	
// 		{
// 		str+=2;
// 			while((*str!=*IP_end)&&*(str+1)!=*(IP_end+1))
// 			{
// 				*temp=*str;
// 				temp++;
// 				str++;
// 			}
// 		}
// 		str++;
// 	}
// }	


// void Get_NetPassword(char *str,char *temp)
// {

// 	while(*str!='\0')
// 	{
// 		if((*str==*password_begin)&&*(str+1)==*(password_begin+1))	
// 		{
// 			str+=2;
// 			while((*str!=*password_end)&&*(str+1)!=*(password_end+1))
// 			{
// 				*temp=*str;
// 				temp++;
// 				str++;
// 			}
// 		}
// 		str++;
// 	}

// }































