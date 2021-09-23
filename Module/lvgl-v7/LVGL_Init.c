#include "IncludeFile.h"
#include "lv_obj.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

void LVGL_Init()
{
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();

}



