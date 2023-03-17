#include "LVGL_UI.h"

#ifdef ON_PC
    #include <stdlib.h>
    #include <unistd.h>
    #include "lvgl/lvgl.h"
    #include "lv_drivers/win32drv/win32drv.h"
    #include <windows.h>
#else
    #include "IncludeFile.h"
#endif


lv_obj_t *ALL_Bg;
lv_obj_t *Main;

// 逆时针（如下图）：
// x1=xcos(β)-ysin(β);
// y1=ycos(β)+xsin(β);

// 顺时针（图未给出）：
// x1=xcos(β)+ysin(β);
// y1=ycos(β)-xsin(β);


//旋转半径
#define R_LEN (45)
#define EYE_SIZE_W    (60)

#define ROTATEDIR_FORWARD     ( 1)//顺时针
#define ROTATEDIR_OPPOSITE    (-1)//逆时针

lv_obj_t *Eye_Group[4];
lv_anim_t Anima_Eye_Group[4];
lv_obj_t *Eye_base[4];//瞳孔
lv_anim_t Anima_Eye_Size[4];
uint8_t RotateDir = ROTATEDIR_FORWARD;
/*
	|
 2  |  3
---------
 1  |  0
	|
*/
 //口字形
int8_t Eye_Position[4][3]=
{
    { R_LEN,  R_LEN, 0},
    {-R_LEN,  R_LEN, 1},
    {-R_LEN, -R_LEN, 2},
    { R_LEN, -R_LEN, 3},
};

 ///// 十字型
// int8_t Eye_Position[4][3]=
// {
//     {0,      -R_LEN, 0},     //上
//     {R_LEN,  0,      1},     //右
//     {0,      R_LEN,  2},     //下
//     {-R_LEN, 0,      3},     //左
// };


static void Animation_CB(void *var, int32_t v)
{
    uint8_t i,j;
    int16_t x1,y1;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < 4; i++)
    {
        if(Eye_tmp == Eye_Group[i])
        {
			if( RotateDir == 1)
			{
				//顺时针
				x1=(Eye_Position[Eye_Position[i][2]][0])*FastCos(DEGTORAD(v))-(Eye_Position[Eye_Position[i][2]][1])*FastSin(DEGTORAD(v));
				y1=(Eye_Position[Eye_Position[i][2]][1])*FastCos(DEGTORAD(v))+(Eye_Position[Eye_Position[i][2]][0])*FastSin(DEGTORAD(v));  
			}
			else
			{
				//逆时针
				x1=(Eye_Position[Eye_Position[i][2]][0])*FastCos(DEGTORAD(v))+(Eye_Position[Eye_Position[i][2]][1])*FastSin(DEGTORAD(v));
				y1=(Eye_Position[Eye_Position[i][2]][1])*FastCos(DEGTORAD(v))-(Eye_Position[Eye_Position[i][2]][0])*FastSin(DEGTORAD(v));  
			}

			lv_obj_align_to(Eye_Group[i],Main,LV_ALIGN_CENTER,x1,y1);

			if( v == 90)
			{
				Eye_Position[i][2] = (Eye_Position[i][2] +RotateDir)%4;

            	lv_anim_set_repeat_count(&Anima_Eye_Size[i], 1);
				//旋转结束后调整眼部焦距
				lv_anim_start(&Anima_Eye_Size[i]);
			}
        }
    }
}

void Eye0_Create()
{
	Eye_Group[0] = lv_obj_create(Main);
	// Eye_Group[0] = lv_btn_create(Main);
	lv_obj_set_size(Eye_Group[0],EYE_SIZE_W,EYE_SIZE_W);
	lv_obj_set_style_bg_color(Eye_Group[0],lv_color_white(),LV_PART_MAIN);
	lv_obj_set_style_radius(Eye_Group[0],EYE_SIZE_W/2,LV_PART_MAIN);
	lv_obj_set_style_outline_width(Eye_Group[0],3,LV_PART_MAIN);
	lv_obj_set_style_outline_color(Eye_Group[0],lv_palette_main(LV_PALETTE_RED),LV_PART_MAIN);


	lv_obj_t * label = lv_label_create(Eye_Group[0]);

	lv_label_set_text_fmt(label, "%"LV_PRIu32, 0);
	lv_obj_align_to(label,Eye_Group[0],LV_ALIGN_CENTER,0,0);

}


void Eye1_Create()
{
	Eye_Group[1] = lv_obj_create(Main);
	lv_obj_set_size(Eye_Group[1],EYE_SIZE_W,EYE_SIZE_W);
	lv_obj_set_style_bg_color(Eye_Group[1],lv_color_white(),LV_PART_MAIN);
	lv_obj_set_style_radius(Eye_Group[1],EYE_SIZE_W/2,LV_PART_MAIN);
	lv_obj_set_style_outline_width(Eye_Group[1],3,LV_PART_MAIN);
	lv_obj_set_style_outline_color(Eye_Group[1],lv_palette_main(LV_PALETTE_BLUE),LV_PART_MAIN);

	lv_obj_t * label = lv_label_create(Eye_Group[1]);

	lv_label_set_text_fmt(label, "%"LV_PRIu32, 1);
	lv_obj_align_to(label,Eye_Group[1],LV_ALIGN_CENTER,0,0);

}


void Eye2_Create()
{
	Eye_Group[2] = lv_obj_create(Main);
	lv_obj_set_size(Eye_Group[2],EYE_SIZE_W,EYE_SIZE_W);
	lv_obj_set_style_bg_color(Eye_Group[2],lv_color_white(),LV_PART_MAIN);
	lv_obj_set_style_radius(Eye_Group[2],EYE_SIZE_W/2,LV_PART_MAIN);
	lv_obj_set_style_outline_width(Eye_Group[2],3,LV_PART_MAIN);
	lv_obj_set_style_outline_color(Eye_Group[2],lv_palette_main(LV_PALETTE_GREEN),LV_PART_MAIN);

	lv_obj_t * label = lv_label_create(Eye_Group[2]);

	lv_label_set_text_fmt(label, "%"LV_PRIu32, 2);
	lv_obj_align_to(label,Eye_Group[2],LV_ALIGN_CENTER,0,0);

}


void Eye3_Create()
{
	Eye_Group[3] = lv_obj_create(Main);
	lv_obj_set_size(Eye_Group[3],EYE_SIZE_W,EYE_SIZE_W);
	lv_obj_set_style_bg_color(Eye_Group[3],lv_color_white(),LV_PART_MAIN);
	lv_obj_set_style_radius(Eye_Group[3],EYE_SIZE_W/2,LV_PART_MAIN);
	lv_obj_set_style_outline_width(Eye_Group[3],3,LV_PART_MAIN);
	lv_obj_set_style_outline_color(Eye_Group[3],lv_palette_main(LV_PALETTE_DEEP_ORANGE),LV_PART_MAIN);

	lv_obj_t * label = lv_label_create(Eye_Group[3]);

	lv_label_set_text_fmt(label, "%"LV_PRIu32, 3);
	lv_obj_align_to(label,Eye_Group[3],LV_ALIGN_CENTER,0,0);

}


void ChangeSizeAnimaCB(void *var, int32_t v)
{
	uint8_t i,j;

    lv_obj_t *Eye_tmp = (lv_obj_t *)var;

    for ( i = 0; i < 4; i++)
    {
        if(Eye_tmp == Eye_base[i])
        {
			lv_obj_set_size(Eye_tmp,v,v);
			lv_obj_set_style_radius(Eye_tmp,v/2,LV_PART_MAIN);
			lv_obj_align_to(Eye_tmp,Eye_Group[i],LV_ALIGN_CENTER,0,0);
        }
    }
}

void ChangeSizeAnima()
{
	uint8_t i=0;

	for (i = 0; i < 4; i++)
	{
		
		lv_anim_init(&Anima_Eye_Size[i]);
        lv_anim_set_var(&Anima_Eye_Size[i],Eye_base[i]);
        lv_anim_set_values(&Anima_Eye_Size[i],40,30);
        lv_anim_set_time(&Anima_Eye_Size[i], 200);
		lv_anim_set_delay(&Anima_Eye_Size[i], 500);//1500
        lv_anim_set_exec_cb(&Anima_Eye_Size[i], ChangeSizeAnimaCB);

        lv_anim_set_path_cb(&Anima_Eye_Size[i],lv_anim_path_ease_in_out);
		// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_ease_in_out);
		// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_linear);
		// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
		// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);//==


		lv_anim_set_playback_time(&Anima_Eye_Size[i],200);
		lv_anim_set_playback_delay(&Anima_Eye_Size[i],200);
        lv_anim_set_repeat_delay(&Anima_Eye_Size[i],500);
        lv_anim_set_repeat_count(&Anima_Eye_Size[i], 1);

	}

    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&Anima_Eye_Size[i]);
    }
}


void Eye_Create()
{
    uint8_t i=0;
	lv_obj_t *Eye_in;

    ALL_Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ALL_Bg,240,240);
    lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_style_border_side(ALL_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(ALL_Bg,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_border_width(ALL_Bg,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(ALL_Bg,LV_SCROLLBAR_MODE_OFF);

    Main = lv_obj_create(ALL_Bg);
    lv_obj_set_size(Main,240,240);
    lv_obj_set_style_bg_color(Main,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Main,120,LV_PART_MAIN);
    lv_obj_set_style_border_side(Main,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_color(Main,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
    lv_obj_set_style_border_width(Main,5,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(Main,LV_SCROLLBAR_MODE_OFF);
    lv_obj_center(Main);

	// Eye0_Create();
	// Eye1_Create();
	// Eye2_Create();
	// Eye3_Create();

    for ( i = 0; i < 4; i++)
    {
		//眼球
		Eye_Group[i] = lv_obj_create(Main);
		lv_obj_set_size(Eye_Group[i],EYE_SIZE_W,EYE_SIZE_W);
		lv_obj_set_style_bg_color(Eye_Group[i],lv_color_make(56,110,23),LV_PART_MAIN);
		lv_obj_set_style_radius(Eye_Group[i],EYE_SIZE_W/2,LV_PART_MAIN);
		lv_obj_set_style_outline_width(Eye_Group[i],3,LV_PART_MAIN);
		lv_obj_set_style_outline_color(Eye_Group[i],lv_color_make(84,104,58),LV_PART_MAIN);

		//瞳孔
		Eye_base[i] = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_base[i],40,40);
		lv_obj_set_style_radius(Eye_base[i],20,LV_PART_MAIN);
		lv_obj_align_to(Eye_base[i],Eye_Group[i],LV_ALIGN_CENTER,0,0);
		lv_obj_set_style_bg_color(Eye_base[i],lv_color_black(),LV_PART_MAIN);
		lv_obj_set_scrollbar_mode(Eye_base[i],LV_SCROLLBAR_MODE_OFF);

		//眼部高光
		Eye_in = lv_obj_create(Eye_Group[i]);
		lv_obj_set_size(Eye_in,12,12);
		lv_obj_set_style_radius(Eye_in,6,LV_PART_MAIN);
		lv_obj_align_to(Eye_in,Eye_Group[i],LV_ALIGN_TOP_RIGHT,5,-7);
		lv_obj_set_scrollbar_mode(Eye_in,LV_SCROLLBAR_MODE_OFF);

		lv_obj_set_scrollbar_mode(Eye_Group[i],LV_SCROLLBAR_MODE_OFF);//关闭滚动条
        lv_obj_align_to(Eye_Group[i],Main,LV_ALIGN_CENTER,Eye_Position[i][0],Eye_Position[i][1]);

        lv_anim_init(&Anima_Eye_Group[i]);
        lv_anim_set_var(&Anima_Eye_Group[i],Eye_Group[i]);
        lv_anim_set_values(&Anima_Eye_Group[i],0,90);
        lv_anim_set_time(&Anima_Eye_Group[i], 300);
		// lv_anim_set_delay(&Anima_Eye_Group[i], 500);
        lv_anim_set_exec_cb(&Anima_Eye_Group[i], Animation_CB);
        lv_anim_set_path_cb(&Anima_Eye_Group[i],lv_anim_path_ease_in_out);

		// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_ease_in_out);
		// lv_anim_set_path_cb(&Anima_Eye1,lv_anim_path_linear);
		// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_in);
		// lv_anim_set_path_cb(&Anima,lv_anim_path_ease_out);//==

		// lv_anim_set_playback_time(&Anima_Eye_Size[i],200);
		// lv_anim_set_playback_delay(&Anima_Eye_Size[i],200);
        lv_anim_set_repeat_delay(&Anima_Eye_Group[i],2000);
        lv_anim_set_repeat_count(&Anima_Eye_Group[i], LV_ANIM_REPEAT_INFINITE);

    }

	ChangeSizeAnima();

    for ( i = 0; i < 4; i++)
    {
        lv_anim_start(&Anima_Eye_Group[i]);
    }
}


//***************************************************//
//  功能描述: LVGL Demo测试
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 无
//  
//***************************************************//
void LVGL_Demo()
{
	// lv_ex_keyboard_1();
	// lv_demo_stress();
	lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_REAL);
	// lv_demo_keypad_encoder();
}

//***************************************************//
//  功能描述: LVGL初始化
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: 无
//  
//***************************************************//
void LVGL_Init()
{

#ifndef ON_PC
	LVGLTimerInit(1);
    lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
#endif

    // StateBar();
    // EYE_FACE();
    // LVGL_Build_GUI();
    // roller_show_3();
//    LVGL_Demo();
   Eye_Create();
}


//***************************************************//
//  功能描述: LVGL定时任务
//  
//  参数: 无
//  
//  返回值: 无
//  
//  说明: RTOS中不建议加临界保护,周期不小于 10 ms
// 	      建议lv_tick_inc()执行后在执行此函数
//  
//***************************************************//
void LVGL_Task()
{
    lv_task_handler();
}



