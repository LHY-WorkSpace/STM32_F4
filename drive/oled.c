#include "IncludeFile.h"


												//  PB13-------SCLK          PB15------SDA
												//  PB12-------D/C           PB14------RST 

#define play_speed           100



u8 OLED_GRAM[8][128];



u8 CharModel[][16]=
{
	{0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00,0x00,0xF0,0x08,0x04,0x04,0x08,0xF0,0x00},/*"0",0*/
	{0x00,0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00},/*"1",1*/
	{0x00,0x0E,0x10,0x10,0x10,0x10,0x0F,0x00,0x00,0x0C,0x14,0x24,0x44,0x84,0x0C,0x00},/*"2",2*/
	{0x00,0x0C,0x10,0x10,0x10,0x11,0x0E,0x00,0x00,0x18,0x04,0x84,0x84,0x44,0x38,0x00},/*"3",3*/
	{0x00,0x00,0x01,0x02,0x0C,0x1F,0x00,0x00,0x00,0x60,0xA0,0x24,0x24,0xFC,0x24,0x24},/*"4",4*/
	{0x00,0x1F,0x11,0x11,0x11,0x10,0x10,0x00,0x00,0x98,0x04,0x04,0x04,0x88,0x70,0x00},/*"5",5*/
	{0x00,0x07,0x08,0x11,0x11,0x09,0x00,0x00,0x00,0xF0,0x88,0x04,0x04,0x04,0xF8,0x00},/*"6",6*/
	{0x00,0x18,0x10,0x10,0x11,0x16,0x18,0x00,0x00,0x00,0x00,0x7C,0x80,0x00,0x00,0x00},/*"7",7*/
	{0x00,0x0E,0x11,0x10,0x10,0x11,0x0E,0x00,0x00,0x38,0x44,0x84,0x84,0x44,0x38,0x00},/*"8",8*/
	{0x00,0x0F,0x10,0x10,0x10,0x08,0x07,0x00,0x00,0x80,0x48,0x44,0x44,0x88,0xF0,0x00},/*"9",9*/

	{0x00,0x00,0x03,0x1C,0x07,0x00,0x00,0x00,0x04,0x3C,0xC4,0x40,0x40,0xE4,0x1C,0x04},/*"A",0*/
	{0x10,0x1F,0x11,0x11,0x11,0x0E,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x88,0x70,0x00},/*"B",1*/
	{0x03,0x0C,0x10,0x10,0x10,0x10,0x1C,0x00,0xE0,0x18,0x04,0x04,0x04,0x08,0x10,0x00},/*"C",2*/
	{0x10,0x1F,0x10,0x10,0x10,0x08,0x07,0x00,0x04,0xFC,0x04,0x04,0x04,0x08,0xF0,0x00},/*"D",3*/
	{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x04,0xC4,0x04,0x18,0x00},/*"E",4*/
	{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x00,0xC0,0x00,0x00,0x00},/*"F",5*/
	{0x03,0x0C,0x10,0x10,0x10,0x1C,0x00,0x00,0xE0,0x18,0x04,0x04,0x44,0x78,0x40,0x00},/*"G",6*/
	{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x04,0xFC,0x84,0x80,0x80,0x84,0xFC,0x04},/*"H",7*/
	{0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"I",8*/
	{0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00,0x00},/*"J",9*/
	{0x10,0x1F,0x11,0x03,0x14,0x18,0x10,0x00,0x04,0xFC,0x04,0x80,0x64,0x1C,0x04,0x00},/*"K",10*/
	{0x10,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x04,0x0C,0x00},/*"L",11*/
	{0x10,0x1F,0x1F,0x00,0x1F,0x1F,0x10,0x00,0x04,0xFC,0x80,0x7C,0x80,0xFC,0x04,0x00},/*"M",12*/
	{0x10,0x1F,0x0C,0x03,0x00,0x10,0x1F,0x10,0x04,0xFC,0x04,0x00,0xE0,0x18,0xFC,0x00},/*"N",13*/
	{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00},/*"O",14*/
	{0x10,0x1F,0x10,0x10,0x10,0x10,0x0F,0x00,0x04,0xFC,0x84,0x80,0x80,0x80,0x00,0x00},/*"P",15*/
	{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x14,0x14,0x0C,0x0A,0xF2,0x00},/*"Q",16*/
	{0x10,0x1F,0x11,0x11,0x11,0x11,0x0E,0x00,0x04,0xFC,0x04,0x00,0xC0,0x30,0x0C,0x04},/*"R",17*/
	{0x00,0x0E,0x11,0x10,0x10,0x10,0x1C,0x00,0x00,0x1C,0x04,0x84,0x84,0x44,0x38,0x00},/*"S",18*/
	{0x18,0x10,0x10,0x1F,0x10,0x10,0x18,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"T",19*/
	{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"U",20*/
	{0x10,0x1E,0x11,0x00,0x00,0x13,0x1C,0x10,0x00,0x00,0xE0,0x1C,0x70,0x80,0x00,0x00},/*"V",21*/
	{0x10,0x1F,0x00,0x1F,0x00,0x1F,0x10,0x00,0x00,0xC0,0x7C,0x80,0x7C,0xC0,0x00,0x00},/*"W",22*/
	{0x10,0x18,0x16,0x01,0x01,0x16,0x18,0x10,0x04,0x0C,0x34,0xC0,0xC0,0x34,0x0C,0x04},/*"X",23*/
	{0x10,0x1C,0x13,0x00,0x13,0x1C,0x10,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"Y",24*/
	{0x08,0x10,0x10,0x10,0x13,0x1C,0x10,0x00,0x04,0x1C,0x64,0x84,0x04,0x04,0x18,0x00},/*"Z",25*/

	{0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x98,0x24,0x24,0x48,0xFC,0x04,0x00},/*"a",0*/
	{0x08,0x0F,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0xFC,0x88,0x04,0x04,0x88,0x70,0x00},/*"b",1*/
	{0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x70,0x88,0x04,0x04,0x04,0x88,0x00},/*"c",2*/
	{0x00,0x00,0x01,0x01,0x01,0x09,0x0F,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"d",3*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x24,0x24,0x24,0x24,0xE8,0x00},/*"e",4*/
	{0x00,0x01,0x01,0x07,0x09,0x09,0x04,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"f",5*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xD6,0x29,0x29,0x29,0xC9,0x06,0x00},/*"g",6*/
	{0x08,0x0F,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"h",7*/
	{0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"i",8*/
	{0x00,0x00,0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00},/*"j",9*/
	{0x08,0x0F,0x00,0x00,0x01,0x01,0x01,0x00,0x04,0xFC,0x24,0x60,0x94,0x0C,0x04,0x00},/*"k",10*/
	{0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"l",11*/
	{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x04,0xFC,0x04,0x00,0xFC,0x04,0x00,0xFC},/*"m",12*/
	{0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"n",13*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"o",14*/
	{0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x01,0xFF,0x89,0x04,0x04,0x88,0x70,0x00},/*"p",15*/
	{0x00,0x00,0x00,0x01,0x01,0x00,0x01,0x00,0x00,0x70,0x88,0x04,0x04,0x89,0xFF,0x01},/*"q",16*/
	{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x04,0x04,0xFC,0x84,0x04,0x00,0x80,0x00},/*"r",17*/
	{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xCC,0x24,0x24,0x24,0x24,0x98,0x00},/*"s",18*/
	{0x00,0x01,0x01,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0xF8,0x04,0x04,0x08,0x00},/*"t",19*/
	{0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"u",20*/
	{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0xC0,0x30,0x0C,0x30,0xC0,0x00,0x00},/*"v",21*/
	{0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x80,0x70,0x0C,0x30,0xE0,0x1C,0x60,0x80},/*"w",22*/
	{0x00,0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x04,0x8C,0x70,0x74,0x8C,0x04,0x00},/*"x",23*/
	{0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x00,0x81,0x61,0x1E,0x18,0x60,0x80,0x00},/*"y",24*/
	{0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x84,0x0C,0x34,0x44,0x84,0x0C,0x00},/*"z",25*/

	{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x00,0x00},/*"!",0*/
	{0x00,0x08,0x30,0x40,0x08,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",1*/
	{0x00,0x02,0x03,0x1E,0x02,0x03,0x1E,0x00,0x00,0x20,0xFC,0x20,0x20,0xFC,0x20,0x00},/*"#",2*/
	{0x00,0x0E,0x11,0x11,0x3F,0x10,0x0C,0x00,0x00,0x18,0x04,0x04,0xFF,0x84,0x78,0x00},/*"$",3*/
	{0x0F,0x10,0x0F,0x01,0x06,0x18,0x00,0x00,0x00,0x8C,0x30,0xC0,0x78,0x84,0x78,0x00},/*"%",4*/
	{0x00,0x0F,0x10,0x11,0x0E,0x00,0x00,0x00,0x78,0x84,0xC4,0x34,0x98,0xE4,0x84,0x08},/*"&",5*/
	{0x00,0x48,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",6*/
	{0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00},/*"(",7*/
	{0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00},/*")",8*/
	{0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00},/*"*",9*/
	{0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xF0,0x80,0x80,0x80},/*"+",10*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x0E,0x00,0x00,0x00,0x00,0x00},/*",",11*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00},/*"-",12*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00},/*".",13*/
	{0x00,0x00,0x00,0x00,0x03,0x1C,0x20,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00},/*"/",14*/

	{0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00},/*":",0*/
	{0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00},/*";",1*/
	{0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x00},/*"<",2*/
	{0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00},/*"=",3*/
	{0x00,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x80,0x00},/*">",4*/
	{0x00,0x0E,0x12,0x10,0x10,0x11,0x0E,0x00,0x00,0x00,0x00,0x0C,0xEC,0x00,0x00,0x00},/*"?",5*/
	{0x03,0x0C,0x13,0x14,0x17,0x08,0x07,0x00,0xE0,0x18,0xE4,0x14,0xF4,0x14,0xE8,0x00},/*"@",6*/
};
// /*          8*8                        */
// u8 num0[]={0X00,0X00,0X7F,0X41,0X41,0X41,0X7F,0X00};
// u8 num1[]={0X00,0X00,0X42,0X42,0X7F,0X40,0X00,0X00};
// u8 num2[]={0X00,0X00,0X7B,0X49,0X49,0X49,0X4F,0X00};
// u8 num3[]={0X00,0X00,0X63,0X49,0X49,0X49,0X7F,0X00};
// u8 num4[]={0X00,0X00,0X0F,0X08,0X7E,0X08,0X08,0X00};
// u8 num5[]={0X00,0X00,0X4F,0X49,0X49,0X49,0X79,0X00};
// u8 num6[]={0X00,0X00,0X7F,0X49,0X49,0X49,0X79,0X00};
// u8 num7[]={0X00,0X00,0X01,0X01,0X7D,0X03,0X01,0X00};
// u8 num8[]={0X00,0X00,0X7F,0X49,0X49,0X49,0X7F,0X00};
// u8 num9[]={0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00};




// u8 charA[8]={0X00,0X00,0X7C,0X12,0X11,0X12,0X7C,0X00};
// u8 charB[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X36,0X00};
// u8 charC[8]={0X00,0X00,0X3E,0X41,0X41,0X41,0X22,0X00};
// u8 charD[8]={0X00,0X00,0X7F,0X41,0X41,0X41,0X22,0X1C};
// u8 charE[8]={0X00,0X00,0X7F,0X49,0X49,0X49,0X49,0X00};
// u8 charF[8]={0X00,0X00,0X7F,0X09,0X09,0X09,0X01,0X00};
// u8 charG[8]={0X00,0X00,0X3E,0X41,0X59,0X49,0X32,0X00};
// u8 charH[8]={0X00,0X00,0X7F,0X08,0X08,0X08,0X7F,0X00};
// u8 charI[8]={0X00,0X00,0X41,0X41,0X7F,0X41,0X41,0X00};
// u8 charJ[8]={0X00,0X00,0X31,0X41,0X21,0X1F,0X01,0X00};
// u8 charK[8]={0X00,0X00,0X7F,0X08,0X14,0X22,0X41,0X00};
// u8 charL[8]={0X00,0X00,0X7F,0X40,0X40,0X40,0X40,0X00};
// u8 charM[8]={0X00,0X7F,0X02,0X04,0X04,0X02,0X7F,0X00};
// u8 charN[8]={0X00,0X7F,0X02,0X04,0X08,0X10,0X7F,0X00};
// u8 charO[8]={0X00,0X00,0X3E,0X41,0X41,0X41,0X3E,0X00};
// u8 charP[8]={0X00,0X00,0X7F,0X09,0X09,0X09,0X06,0X00};
// u8 charQ[8]={0X00,0X3E,0X41,0X41,0X51,0X3E,0X40,0X00};
// u8 charR[8]={0X00,0X7F,0X09,0X19,0X29,0X46,0X00,0X00};
// u8 charS[8]={0X00,0X4E,0X49,0X49,0X49,0X39,0X00,0X00};
// u8 charT[8]={0X00,0X00,0X01,0X01,0X7F,0X01,0X01,0X00};
// u8 charU[8]={0X00,0X00,0X3F,0X40,0X40,0X40,0X3F,0X00};
// u8 charV[8]={0X00,0X00,0X1F,0X20,0X40,0X20,0X1F,0X00};
// u8 charW[8]={0X00,0X3F,0X40,0X20,0X20,0X40,0X3F,0X00};
// u8 charX[8]={0X00,0X42,0X24,0X18,0X18,0X24,0X42,0X00};
// u8 charY[8]={0X00,0X01,0X02,0X04,0X78,0X04,0X02,0X01};	
// u8 charZ[8]={0X00,0X00,0X61,0X51,0X49,0X45,0X43,0X00};																					
// u8 charcolom[8]={0X00,0X00,0X00,0X66,0X66,0X00,0X00,0X00};    //冒号
// u8 char_tempure[8]={0X03,0X03,0X1C,0X62,0X81,0X81,0X42,0X44};
// u8 point[8]={0X00,0X00,0X00,0X60,0X60,0X00,0X00,0X00};	

// //	
// u8 windows[]=
// {0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0X80,0X80,0X80,0X80,
// 0X80,0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0XE0,0XF0,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
// 0XFF,0XFF,0XFF,0XFF,0XFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X00,0X80,0X80,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0XC0,0XE0,0XF0,0XF8,0XFC,0X00,
// 0X02,0X02,0X7E,0X02,0X02,0X00,0X00,0X7E,0X04,0X08,0X04,0X7E,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X7F,0X7F,0XBF,0X9F,0XDF,0XEF,0XE7,0XF7,0XFB,0XF7,0XF7,0XF7,
// 0XF7,0XEF,0XDF,0X9F,0XBF,0X7F,0X7F,0XFF,0XFF,0XFF,0X00,0XFF,0XFF,0XFF,0XFF,0XFE,
// 0XFE,0XFE,0XFE,0XFE,0XFE,0XFE,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X3F,0X3F,0X3F,0X3F,0X3F,
// 0X3F,0X3F,0X3F,0X3F,0X7F,0XFF,0XFF,0XFE,0XFE,0XFC,0X00,0XFD,0XFB,0XF7,0XFF,0XEF,
// 0XEF,0XEF,0XEF,0XEF,0XEF,0XEF,0XF7,0XF7,0XF7,0XF3,0XFB,0XFD,0XFD,0XFE,0XFE,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X1F,0X0F,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X07,0X07,0X08,0X1F,0X1F,0X3F,0X3F,0X7F,
// 0X7F,0X7F,0X7F,0X7F,0X7F,0X7F,0X7F,0X3F,0X3F,0X1F,0X4F,0X0F,0X07,0X03,0X01,0X00,
// 0X00,0X00,0X40,0X00,0X00,0XE0,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0XC0,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,0X00,0XD8,0XD8,0X00,0X00,0X00,0XC0,
// 0X20,0X10,0X10,0X10,0X10,0X10,0X10,0X20,0XC0,0X00,0X80,0X40,0X20,0X20,0X20,0X20,
// 0X20,0X20,0X20,0XFE,0X00,0XE0,0X10,0X10,0X10,0X10,0X10,0X10,0X10,0XE0,0X00,0XF0,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF0,0X00,0XE0,0X10,0X10,0X10,0X10,
// 0X10,0X10,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X04,0X10,0X40,0X10,
// 0X04,0X01,0X00,0X00,0X00,0XFF,0X08,0X08,0X08,0X08,0X08,0X08,0X08,0X07,0X00,0X00,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
// 0X02,0X04,0X08,0X10,0X20,0X20,0X10,0X08,0X02,0X01,0X00,0X01,0X02,0X08,0X10,0X20,
// 0X20,0X10,0X08,0X04,0X02,0X00,0X00,0X00,0X00,0X00,0X7F,0X7F,0X00,0X00,0X00,0X7F,
// 0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X1F,0X20,0X40,0X40,0X40,0X40,
// 0X40,0X40,0X40,0X3F,0X00,0X3F,0X40,0X40,0X40,0X40,0X40,0X40,0X40,0X3F,0X00,0X0F,
// 0X10,0X20,0X10,0X08,0X0C,0X08,0X10,0X20,0X10,0X0F,0X00,0X21,0X42,0X42,0X42,0X42,
// 0X42,0X42,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X04,0X01,0X00,0X01,
// 0X04,0X10,0X00,0X00,0X00,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
// };



	


//	
//void show_All()
//{
//	u8 i;
//				OLED_SetMode(0x21);           
//				OLED_SetMode(0x00);	        
//				OLED_SetMode(0x7f);	          
//				delay_us(50);                     
//				OLED_SetMode(0x22);	            
//				OLED_SetMode(0x00);	          	
//				OLED_SetMode(0x07);           
//				delay_us(50);
//	for(i=0;i<8;i++)
//	  OLED_SendData(num0[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num1[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num2[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num3[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num4[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num5[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num6[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(num7[i]);	
//	  for(i=0;i<8;i++)
//	  OLED_SendData(num8[i]);

//	for(i=0;i<8;i++)
//	  OLED_SendData(charR[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charT[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charA[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charB[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charX[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charY[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charZ[i]);
//	  	for(i=0;i<8;i++)
//	  OLED_SendData(charQ[i]);
//}




void OLED_SPI_Init()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIOB_InitTypeDefinsture;
	SPI_InitTypeDef SPI_InitTypeDefinsture;
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;                 
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                        
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
	
	GPIOB_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;                
	GPIOB_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_InitTypeDefinsture.GPIO_Speed=GPIO_High_Speed;
	GPIOB_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
	GPIOB_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIOB_InitTypeDefinsture);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);	
	
	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;//32
	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

	SPI_Init(SPI2,&SPI_InitTypeDefinsture);

	SPI_Cmd(SPI2 ,ENABLE);



}





void OLED_Init(void)
{

	OLED_SPI_Init();
	OLED_RST_ON;
	delay_ms(2);	
	OLED_RST_OFF;
	delay_ms(2);	

    OLED_SetMode(0XA8);
    OLED_SetMode(0X3F);
    OLED_SetMode(0XD3);
    OLED_SetMode(0X00);
    OLED_SetMode(0X40);
    OLED_SetMode(0Xd5);      //设置刷新频率和分频值
    OLED_SetMode(0Xf1);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
    OLED_SetMode(0XA0);      //A0--首列对应0      A1------首列对应127
    OLED_SetMode(0XC0);
    OLED_SetMode(0XDA);
    OLED_SetMode(0X12);
    OLED_SetMode(0X81);     //对比度设置
    OLED_SetMode(0Xff);     //设置对比度值
    OLED_SetMode(0XD9);
    OLED_SetMode(0XF1);
    OLED_SetMode(0XDB);
    OLED_SetMode(0X30);
    OLED_SetMode(0XA4);       //0xA4-正常      0XA5-全亮
    OLED_SetMode(0XA6);       //0XA6-正常      0XA7-反相
	OLED_SetMode(0x20);       /*设置显示模式                 参考：  https://blog.csdn.net/gengyuchao/article/details/86608037             */
	OLED_SetMode(0x00);	      /*[页地址----10b    水平模式---00b     垂直模式---01b        */	
	OLED_SetMode(0xc0);	     //0xc8---正常      0xc0------垂直反转  
	OLED_SetMode(0xa1);				
	OLED_SetMode(0x23);
	OLED_SetMode(0x00);        //[5:4]--00禁用闪烁或淡出       10使能消退      11使能闪烁                 [3:0]-----0000(8帧)  0001(16帧)     0010(16帧)。。。。1111(128帧)
	OLED_SetMode(0X8D);     //设置电荷泵
	OLED_SetMode(0X14);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0XAf);

	OLED_ClearScreen(0x00);	

//	memset( &CharModel[ sizeof(CharModel)/sizeof(CharModel[0][0])-1 ][0],0xFF,sizeof(CharModel)/sizeof(CharModel[0][0]));

}





void  display_position(u8 x,u8 y,u8 length)
{
		OLED_SetMode(0x21);                       //列地址 	
		OLED_SetMode(0x00|x);	                    //起始地址 	 0-127
		OLED_SetMode(0x00|(x+length*8)-1);	      //终止地址   
		OLED_SetMode(0x22);	                      //页地址	
		OLED_SetMode(0x00|y);	                    //起始地址	0-7
		OLED_SetMode(0x00|y);                     //终止地址
 	

}

void show_picture(u8 x_start,u8 y_start,u8 x_length,u8 y_length,u8* data)      //像素的坐标x_start ，y_start 宽度x_length,高度y_length 图像数组data
{

	u8 i=0,j=x_length*(y_length>>3);
	
		OLED_SetMode(0x21);                             //列地址 	
		OLED_SetMode(x_start);	                    //起始地址 	 0-127
		OLED_SetMode(x_length-1+x_start);	                      //终止地址   

		OLED_SetMode(0x22);	                           //页地址	
		OLED_SetMode(y_start);	                   //起始地址	0-7
		OLED_SetMode(((y_length>>3)-1)+y_start);                     //终止地址
 	
   for(i=0;i<j;i++)
	  OLED_SendData(data[i]);

	

}



void OLED_SendData(u8 Tdata)
{
	OLED_DATA;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);            
	SPI_I2S_SendData(SPI2,Tdata);			
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	


}

void OLED_SetMode(u8 Tdata)
{
	OLED_ORDER;	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);           
	SPI_I2S_SendData(SPI2,Tdata);			
    SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);	

}

/*
打开显示
只打开显示屏幕的电源，保留GDDRAM
*/
void OLED_TurnON()
{
	OLED_SetMode(0X8D);     //设置电荷泵
	OLED_SetMode(0X14);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0XAF);

}

/*
关闭显示
只关闭显示屏幕的电源，保留GDDRAM
*/
void OLED_TurnOFF()
{

	OLED_SetMode(0X8D);     //设置电荷泵
	OLED_SetMode(0X10);      //0x14-----开启     0x10----关闭
	OLED_SetMode(0XAE);
}



void OLED_ScrollStart()
{

	OLED_SetMode(0x2F);

}
void OLED_ScrollStop()
{

	OLED_SetMode(0x2E);

}

/*
左右滚屏设置
Direction：SCROLL_R[向右]   SCROLL_L[向左] 
FrameFrq：0x00-0x07  多少帧滚动一次
PageStart~PageEnd
*/
void OLED_Scroll_LR(u8 Direction,u8 FrameFrq,u8 PageStart,u8 PageEnd)
{
	OLED_SetMode(0x2E);
    OLED_SetMode(Direction);
    OLED_SetMode(0x00);
    OLED_SetMode(PageStart);
    OLED_SetMode(FrameFrq);
    OLED_SetMode(PageEnd);
    OLED_SetMode(0X00);	
    OLED_SetMode(0XFF);		
	OLED_SetMode(0x2F);

}


/*
垂直滚屏设置：无法单独垂直滚屏，必须带左右移动
Direction：SCROLL_VR[垂直向右]   SCROLL_VL[垂直向左] 
FrameFrq：0x00-0x07  多少帧滚动一次
Offset：垂直偏移[1-63]
PageStart~PageEnd[指左右滚屏的范围]
*/
void OLED_Scroll_Vx(u8 Direction,u8 FrameFrq,u8 Offset,u8 PageStart,u8 PageEnd)
{
	OLED_SetMode(0x2E);
    OLED_SetMode(Direction);
    OLED_SetMode(0x00);
    OLED_SetMode(PageStart);
    OLED_SetMode(FrameFrq);
    OLED_SetMode(PageEnd);
    OLED_SetMode(Offset);		
	OLED_SetMode(0x2F);

}


/*
设置扫描硬件频率：fre/div=越大越快，越小越闪屏
fre:0x00-0xff
div:0x00-0xff
*/
void OLED_SetScanFre(u8 fre,u8 div)    //闪烁设置fre[0-f]  div[0-f] 
{
    OLED_SetMode(0Xd5);                 //设置刷新频率和分频值  
    OLED_SetMode(0X00|fre<<4|div);      //高四位(复位=8)-刷新频率   低四位(复位=1)---分频值
}


/*
设置屏幕对比度(亮度)
value:0x00-0xff
*/
void OLED_CetContrast(u8 value)   
{
    OLED_SetMode(0X81);           //对比度设置
    OLED_SetMode(value);     //设置对比度值
}



void windows_open(u32 speed)
{
u32 i;
	for(i=0;i<896;i++)
//	OLED_SendData(windows[i]);
	
	display_position(0,7,16);
	
	for(i=0;i<128;i++)
	{
	OLED_SendData(0xff);
	delay_ms(speed);        //进度条速度

	}
	OLED_ClearScreen(0x00);

}


void tempure_unit(void)            //   温度单位   .C
{
u8 i;
		for(i=0;i<8;i++)
		{
///	OLED_SendData(char_tempure[i]);
		
		}
}








void power_on_check_display(void)
{
windows_open(10);                                //进度条速度
delay_ms(500);

OLED_ClearScreen(0x00);

OLED_SetScanFre(15,6);		
delay_ms(500);

//display_position(40,0,5);
////display_str_and_speed("CHECK",play_speed);
//delay_ms(200);
	


//从此处开始添加开机检查项目
	
//display_position(0,2,6);
////display_str_and_speed("18B20:",play_speed);
//delay_ms(500);	
//display_position(87,2,5);
//ds18B20_init(1);	                             //18B20
//delay_ms(500);



//display_position(0,4,4);
////display_str_and_speed("RTC:",play_speed);
//delay_ms(500);
//display_position(87,4,5);
//RTC_configinit();
//delay_ms(500);
//	
//	

//display_position(1,7,6);
////display_str_and_speed("POWER:",play_speed);
//delay_ms(500);
//display_position(87,7,2);
////display_str_and_speed("OK",play_speed);
//delay_ms(500);

//OLED_ClearScreen();	

//display_position(0,2,6);
////display_str_and_speed("VOICE:",play_speed);
//delay_ms(500);
//display_position(86,2,2);
////display_str_and_speed("OK",play_speed);
//delay_ms(500);





//display_position(0,4,5);
////display_str_and_speed("WIFI:",play_speed);
//delay_ms(500);
//display_position(87,4,2);
////display_str_and_speed("OK",play_speed);
//delay_ms(500);



//display_position(1,6,7);
////display_str_and_speed("SENSOR:",play_speed);
//delay_ms(500);
//display_position(87,6,2);

////display_str_and_speed("OK",play_speed);
//delay_ms(500);

//OLED_ClearScreen();

//display_position(1,8,4);
////display_str_and_speed("LED:",play_speed);
//delay_ms(500);
//display_position(87,8,5);
////display_str_and_speed("READY",play_speed);

////delay_ms(500);


// OLED_ClearScreen();	



//<-------此处检查完毕

display_position(1,4,13);
//display_str_and_speed("ENTER SYSTEM:",play_speed);
delay_ms(500);
delay_ms(500);
display_position(105,4,2);
//display_str_and_speed("..",100);
delay_ms(500);
OLED_SetScanFre(15,0);		                 
//OLED_ClearScreen();	

}


//void Test()
//{
//u8 i;
//	for(i=0;i<8;i++)
//	{
//	OLED_GRAM[0][i]|=charG[i];
//	OLED_GRAM[0][i+8]|=charH[i];
//	OLED_GRAM[0][i+16]|=charI[i];
//	OLED_GRAM[0][i+24]|=charJ[i];
//	OLED_GRAM[0][i+32]|=charK[i];
//	OLED_GRAM[0][i+40]|=charL[i];
//	}



//}









void OLED_Draw_Point(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;

	if(x>127||y>63)
		return;
	pos=y/8; 
	bx=y%8;     
	temp=1<<bx;
	if(t)
		OLED_GRAM[pos][x]|=temp;  
	else 
		OLED_GRAM[pos][x]&=~temp;        

}





void OLED_ClearScreen(u8 Data)
{
	memset(OLED_GRAM,Data,sizeof(OLED_GRAM));
	OLED_UpdateGRAM();
}





void OLED_UpdateGRAM()
{
	u8 i,j;
	OLED_SetMode(0x21);           
	OLED_SetMode(0x00);	        
	OLED_SetMode(0x7f);	          
	delay_us(5);                     
	OLED_SetMode(0x22);	            
	OLED_SetMode(0x00);	          	
	OLED_SetMode(0x07);           
	delay_us(5);

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_SendData(OLED_GRAM[i][j]);
		}
	}
}







void OLED_Data2GRAM(u8 *Data,u16 length)
{
	u8 i,j;
	u16 k=0;

	if(length>1024)
	return;

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			OLED_GRAM[i][j]=Data[k++];
			if(k>length)
			return;
		}
	}

}




void OLED_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2)
{
	unsigned int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 

	if(delta_x>0)
	{
		incx=1; //设置单步方向 
	}		
	else if(delta_x==0)
	{
		incx=0;//垂直线 
	}
	else 
	{
		incx=-1;delta_x=-delta_x;
	} 

	if(delta_y>0)
	{
		incy=1; 
	}
	else if(delta_y==0)
	{
		incy=0;
	}//水平线 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 

	if( delta_x>delta_y)
	{
		distance=delta_x; //选取基本增量坐标轴 
	}
	else 
	{
		distance=delta_y; 
	}
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		OLED_Draw_Point(uRow,uCol,1);//画点 
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




void OLED_Draw_Circle(u8 x0,u8 y0,u8 r) 
{
	u8 x,y;
	for(x = 0;x <= 63;x++)
	{
		y = sqrt(pow(r,2)-pow(x-x0,2))+y0; //圆方程  x,y反置
		OLED_Draw_Point(y,x,1);      //上半圆
		OLED_Draw_Point(63-y,x,1);   //下半圆
	}
}


void OLED_Draw_FullCircle(u16 x0,u16 y0,u8 r)
{
	s16 a,b;
	s16 di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		s16 i = a,p = b;

		while(i>0)
		{		
			OLED_Draw_Point(x0+b,y0-i,1);
			OLED_Draw_Point(x0-i,y0+b,1);
			i--;
		}		
		while(p>0)
		{		
			OLED_Draw_Point(x0-a,y0-p,1);
			OLED_Draw_Point(x0-p,y0-a,1);
			OLED_Draw_Point(x0+a,y0-p,1);
			OLED_Draw_Point(x0-p,y0+a,1);
			OLED_Draw_Point(x0+a,y0+p,1);
			OLED_Draw_Point(x0+p,y0+a,1);
			p--;
		}

		a++;
		//Bresenham算法画圆    
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	OLED_Draw_Point(x0,y0,1); //圆心坐标
}

//六角星
void Boot_Animation(void)
{
		static u8 x=0,y=0;
		for(x = 63;x>=18;x--)
		{
				OLED_Draw_Point(108-0.7*x,x,1);//Draw a diagonal line ≈√3/3
				OLED_Draw_Point(17 +0.7*x,x,1);
				y = 64-x;
				OLED_Draw_Point(64-0.7*y,y,1);
				OLED_Draw_Point(64+0.7*y,y,1);
				delay_ms(20);
			  	OLED_UpdateGRAM();
		}
		for(x = 30;x <= 94;x++)
		{
				OLED_Draw_Point(125-x,47,1);
				OLED_Draw_Point(x,18,1);
				delay_ms(20);
				OLED_UpdateGRAM();
		}

		
}







/*
阴码
列行
顺向
8*16
*/
void OLED_ShowChar(u8 x,u8 y,u8* Data)
{
	u8 k,l;
	for(k=0;k<2;k++)
	{
		for(l=0;l<8;l++)
			OLED_GRAM[7-k-y*2][l+x]=Data[k*8+l];          //或关系待验证
	}

}

void OLED_ShowStrings(u8 x,u8 y,char* Data,u8 Length)
{	
	u8 PositionBuff[64];
	u8 i=0;

	if( Length > 64 || Length == 0 )
	 	return;    //d单屏最多64个(8*16尺寸的字符)

	while( i < Length )
	{
		if( '0' <= Data[i] &&  Data[i] <= '9')
		{
			PositionBuff[i]=Data[i]-'0';
		}
		else if('A' <= Data[i] &&  Data[i] <= 'Z')
		{
			PositionBuff[i]=Data[i]-'A'+10;	   //加上在列表中(0~9)的偏移
		}
		else if('a' <= Data[i] &&  Data[i] <= 'z')
		{
			PositionBuff[i]=Data[i]-'a'+36;		//加上在列表中(0~9,A~Z)的偏移
		}
		else if('!' <= Data[i] &&  Data[i] <= '/')
		{
			PositionBuff[i]=Data[i]-'!'+62;         
		}
		else if(':' <= Data[i] &&  Data[i] <= '@')
		{
			PositionBuff[i]=Data[i]-':'+77;         
		}

		i++;
	}

	for(i=0;i<Length;i++)
	{

		if(x>119)
		{
			x=0;
			y++;

		}
		OLED_ShowChar(x,y,&CharModel[PositionBuff[i]][0]);
		x+=8;
	}


}








