#ifndef KEY_H
#define KEY_H

#include "stdint.h"
#include "string.h"


#define KEY_LEFT        gpio_input_bit_get(GPIOE,GPIO_PIN_2)
#define KEY_DOWN        gpio_input_bit_get(GPIOE,GPIO_PIN_3)
#define KEY_UP          gpio_input_bit_get(GPIOE,GPIO_PIN_4)
#define KEY_RIGHT       gpio_input_bit_get(GPIOE,GPIO_PIN_5)


//According to your need to modify the constants.
#define TICKS_INTERVAL    20	//ms
#define DEBOUNCE_TICKS    2	//MAX 8
#define SHORT_TICKS       (200 /TICKS_INTERVAL)
#define LONG_TICKS        (800 /TICKS_INTERVAL)


typedef void (*BtnCallback)(void*);


typedef enum
{
    Key_Left,
    Key_Down,
    Key_Up,
    Key_Right,
    Key_Release,
}Key_State_e;



typedef enum {
	PRESS_DOWN = 0,
	PRESS_UP,
	PRESS_REPEAT,
	SINGLE_CLICK,
	DOUBLE_CLICK,
	LONG_PRESS_START,
	LONG_PRESS_HOLD,
	number_of_event,
	NONE_PRESS
}PressEvent;

typedef struct Button {
	uint16_t ticks;
	uint8_t  repeat : 4;
	uint8_t  event : 4;
	uint8_t  state : 3;
	uint8_t  debounce_cnt : 3;
	uint8_t  active_level : 1;
	uint8_t  button_level : 1;
	uint8_t  button_id;
	uint8_t  (*hal_button_Level)(uint8_t button_id_);
	BtnCallback  cb[number_of_event];
	struct Button* next;
}Button;



typedef struct  
{
	uint8_t Index;
	uint8_t KeyState[4];
}KeyState_t;




void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);



void Key_Init(void);
void KeyScan(void);
uint8_t GetKeyState(void);
void KeyTask(void);
#endif 
