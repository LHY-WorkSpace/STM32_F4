#ifndef  U8G2_USERGUI_H
#define  U8G2_USERGUI_H

#define  SSD1306    (1)
#define  SH1106     (2)

#define  OLED_TYPE  SH1106

#define  ALWAYS     (0x0000)

typedef enum
{
    Main_ui,
    UI_MAX,
}UI_Index_e;



typedef struct 
{
    KeyInfo_t KeyInfo;
    UI_Index_e Index; 
    void (*UI_List[UI_MAX])(void);
}GUI_t;



void u8g2_TaskCreate(void);
void u8g2_Init(void);
void Display_U8g2_Logo(void);











#endif
