
lv_obj_t *Btn_OK;
lv_obj_t *Btn_BACK;
lv_obj_t *Btn_DOWN;
lv_obj_t *Btn_UP;
lv_obj_t *Bg;
lv_obj_t *Slider;


//***************************************************//
//  ��������: LVGL ��������
//  
//  ����: lv_event_t 
//  
//  ����ֵ: lv_event_cb_t
//  
//  ˵��: ��
//  
//***************************************************//
void OKKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        //printf("OK !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_YELLOW),LV_PART_MAIN);
    }
}


void DownKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    lv_obj_t *Target = lv_event_get_target(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        //printf("Down !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_GREEN),LV_PART_MAIN);
    }
}

void UpKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        //printf("Up !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_palette_main(LV_PALETTE_BLUE),LV_PART_MAIN);
        // lv_obj_add_flag(Roll,LV_OBJ_FLAG_SCROLL_ONE);
    }
}

void BackKeyProcess(lv_event_t *Event)
{
    lv_event_code_t Code = lv_event_get_code(Event);

    if( Code == LV_EVENT_CLICKED)
    {
        //printf("Back !! \r\n");
        lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    }
}

//***************************************************//
//  ��������: LVGL ��ͼ�Ͳ���
//  
//  ����:  
//  
//  ����ֵ: 
//  
//  ˵��: ��
//  
//***************************************************//
void Botn()
{
    lv_obj_t *Btn = lv_btn_create(lv_scr_act());
    lv_obj_align(Btn,LV_ALIGN_CENTER,0,0);
    lv_obj_set_size(Btn,200,200);
    lv_obj_set_style_bg_color(Btn,lv_palette_main( LV_PALETTE_BLUE),0);
    lv_obj_set_style_bg_grad_color(Btn, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_grad_dir(Btn, LV_GRAD_DIR_HOR, 0);
    lv_obj_set_style_border_width(Btn,3,LV_PART_MAIN);
    lv_obj_set_style_shadow_color(Btn,lv_color_black(),0);
    lv_obj_set_style_shadow_ofs_x(Btn,3,0);
    lv_obj_add_flag(Btn,LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_event_cb(Btn,Btn_Handle,LV_EVENT_ALL,NULL);

    lv_obj_t *label_A = lv_label_create(Btn);
    lv_label_set_text(label_A,"1 2 3 4 5 6 7 8 9 A B C D E F G");
    lv_obj_set_align(label_A,LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(label_A, LV_LABEL_LONG_SCROLL );
    lv_obj_set_style_anim_speed(label_A,150,0);
    lv_obj_set_size(label_A,100,50);


    lv_obj_t *label_C = lv_label_create(Btn);
    lv_label_set_text(label_C,"1 2 3 4 5 6 7 8 9 A B C D E F G");
    lv_obj_set_align(label_C,LV_ALIGN_CENTER);
    lv_label_set_long_mode(label_C, LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_style_anim_speed(label_C,100,0);
    lv_obj_set_size(label_C,100,50);



    lv_obj_t *label_B = lv_label_create(Btn);
    lv_label_set_text(label_B,"1 2 3 4 5 6 7 8 9 A B C D E F G");
    lv_obj_set_align(label_B,LV_ALIGN_BOTTOM_MID);
    lv_label_set_long_mode(label_B, LV_LABEL_LONG_SCROLL );
    lv_obj_set_style_anim_speed(label_B,150,0);
    lv_obj_set_size(label_B,100,50);

}


void KeyBtn_OK()
{
    Btn_OK = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_OK);

    lv_obj_set_size(Btn_OK,30,20);
    lv_obj_set_pos(Btn_OK,5,100);
    lv_obj_set_style_border_side(Btn_OK,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_OK,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_OK,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_OK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_OK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_OK,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    //lv_label_set_text(Lable,"OK");
    lv_label_set_text(Lable,LV_SYMBOL_OK);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    //lv_obj_add_event_cb(Btn_OK, OKKeyProcess ,LV_EVENT_CLICKED,NULL);

}

void  KeyBtn_BACK()
{
    Btn_BACK = lv_btn_create(lv_scr_act());

    lv_obj_t *Lable = lv_label_create(Btn_BACK);

    lv_obj_set_size(Btn_BACK,30,20);
    lv_obj_set_pos(Btn_BACK,205,100);
    lv_obj_set_style_border_side(Btn_BACK,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_BACK,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_BACK,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_BACK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_BACK,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_BACK,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Back");
    lv_label_set_text(Lable,LV_SYMBOL_CLOSE);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    //lv_obj_add_event_cb(Btn_BACK, BackKeyProcess ,LV_EVENT_CLICKED,NULL);


}

void  KeyBtn_UP()
{
    Btn_UP = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_UP);

    lv_obj_set_size(Btn_UP,30,20);
    lv_obj_set_pos(Btn_UP,5,200);
    lv_obj_set_style_border_side(Btn_UP,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_UP,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_UP,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_UP,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_UP,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_UP,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Up");
    lv_label_set_text(Lable,LV_SYMBOL_UP);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

   // lv_obj_add_event_cb(Btn_UP, UpKeyProcess ,LV_EVENT_CLICKED,NULL);
}




void  KeyBtn_DOWN()
{
    Btn_DOWN = lv_btn_create(lv_scr_act());
    lv_obj_t *Lable = lv_label_create(Btn_DOWN);

    lv_obj_set_size(Btn_DOWN,30,20);
    lv_obj_set_pos(Btn_DOWN,205,200);

    lv_obj_set_style_border_side(Btn_DOWN,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
    lv_obj_set_style_border_width(Btn_DOWN,2,LV_PART_MAIN);

    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_white(),LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_x(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_ofs_y(Btn_DOWN,2,LV_PART_MAIN );
    // lv_obj_set_style_shadow_color(Btn_DOWN,lv_color_black(),LV_PART_MAIN | LV_STATE_PRESSED);

    // lv_label_set_text(Lable,"Down");
    lv_label_set_text(Lable,LV_SYMBOL_DOWN);
    lv_obj_set_align(Lable,LV_ALIGN_CENTER);

    //lv_obj_add_event_cb(Btn_DOWN, DownKeyProcess ,LV_EVENT_CLICKED,NULL);

}



void BackGroung()
{
    Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,3,LV_PART_MAIN);

    // lv_obj_set_style_bg_grad_color(Bg, lv_palette_main(LV_PALETTE_GREY), 0);
    // lv_obj_set_style_bg_grad_dir(Bg, LV_GRAD_DIR_VER, 0);

//    lv_obj_t *boxPad = lv_canvas_create(lv_scr_act());
//    lv_obj_set_size(boxPad,20,20);
   
}

void LVGL_Line()
{
    lv_obj_t *Line = lv_line_create(lv_scr_act());
}


static void mask_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);        //��ȡ�¼�
    lv_obj_t * obj = lv_event_get_target(e);            //��ȡ��ǰ�¼�

    static int16_t mask_top_id = -1;                    //���嶥������
    static int16_t mask_bottom_id = -1;                 //����ײ�����

    if (code == LV_EVENT_COVER_CHECK) {                 //�¼����Ǽ��
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED); //���÷�������

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {      //ִ������ͼ
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);     //��ȡ��������
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);//��ȡ���������м��
        lv_coord_t font_h = lv_font_get_line_height(font);  //��ȡ�и�

        lv_area_t roller_coords;                        //���û����������
        lv_obj_get_coords(obj, &roller_coords);         //����һ����������굽һ������

        lv_area_t rect_area;                            //���û����������
        rect_area.x1 = roller_coords.x1;                //��ȡ��x1��ֵ
        rect_area.x2 = roller_coords.x2;                //��ȡ��x2��ֵ
        rect_area.y1 = roller_coords.y1;                //��ȡ��y1��ֵ
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;           //��ȡ��y2��ֵ

        lv_draw_mask_fade_param_t * fade_mask_top = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));  //�����ɰ���ɫ���� ����
        
        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);     //��ʼ��һ���������֡�
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);        //���һ�����������ɰ�

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;      //��ȡy1����
        rect_area.y2 = roller_coords.y2;                            //��ȡy2����

        lv_draw_mask_fade_param_t * fade_mask_bottom =lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));//�����ɰ���ɫ���� �ײ�

        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);  //��ʼ��һ���������֡�
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);  //���һ�����������ɰ�

    } else if (code == LV_EVENT_DRAW_POST_END) {                    //���post���ƽ׶�(��������Ԫ�ض�����ʱ)
        lv_draw_mask_fade_param_t * fade_mask_top = lv_draw_mask_remove_id(mask_top_id);        //�Ƴ��ɰ�        
        lv_draw_mask_fade_param_t * fade_mask_bottom = lv_draw_mask_remove_id(mask_bottom_id);  //�Ƴ��ɰ�
        lv_draw_mask_free_param(fade_mask_top);                     //�ͷŲ����е����ݡ�        
        lv_draw_mask_free_param(fade_mask_bottom);                  //�ͷŲ����е����ݡ�
        lv_mem_buf_release(fade_mask_top);                          //�ֶ��ͷ��ڴ�    
        lv_mem_buf_release(fade_mask_bottom);                       //�ֶ��ͷ��ڴ�
        mask_top_id = -1;                                           
        mask_bottom_id = -1;
    }
}

/*************************************************
 *  �������� :  roller_show_3
 *  ��    �� �� e 
 *  �������� �� �����ص���ʾ
 *************************************************/
void roller_show_3(void)
{
    static lv_style_t style;                            //������ʽ����
    lv_style_init(&style);                              //��ʼ����ʽ
    lv_style_set_bg_color(&style, lv_color_black());    //���ñ�����ɫ
    lv_style_set_text_color(&style, lv_color_white());  //����������ɫ
    lv_style_set_border_width(&style, 0);               //���ñ߿���
    lv_style_set_pad_all(&style, 0);                    //���ñ߾�
    lv_obj_add_style(lv_scr_act(), &style, 0);          //�����ʽ

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act()); //����roller����
    lv_obj_add_style(roller1, &style, 0);               //�����ʽ
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);  //���ö����͸����

    lv_obj_set_style_text_font(roller1, &lv_font_montserrat_14, LV_PART_SELECTED);  //���ö�������

    lv_roller_set_options(roller1,                      //���ö���ѡ��
                        "January\n"
                        "February\n"
                        "March\n"
                        "April\n"
                        "May\n"
                        "June\n"
                        "July\n"
                        "August\n"
                        "September\n"
                        "October\n"
                        "November\n"
                        "December",
                        LV_ROLLER_MODE_INFINITE);

    lv_obj_center(roller1);                             //���ж���
    lv_roller_set_visible_row_count(roller1, 5);        //���ö�����
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);   //���ûص�

    // lv_group_t *Group = lv_group_create();
    // lv_group_add_obj(Group,roller1);
    // lv_group_add_obj(Group,Btn_OK);
    // lv_group_add_obj(Group,Btn_BACK);
    // lv_group_add_obj(Group,Btn_DOWN);
    // lv_group_add_obj(Group,Btn_UP);
    // lv_group_add_obj(Group,Slider);
    // lv_indev_set_group(indev_encoder,Group);
}


// static lv_obj_t * meter;

// static void set_value(void * indic, int32_t v)
// {
//     lv_meter_set_indicator_end_value(meter, indic, v);
// }

// void MeterTest()
// {


//     meter = lv_meter_create(lv_scr_act());
//     lv_obj_center(meter);
//     lv_obj_set_size(meter, 200, 200);

//     /*Remove the circle from the middle*/
//     lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

//     /*Add a scale first*/
//     lv_meter_scale_t * scale = lv_meter_add_scale(meter);
//     lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
//     lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 30, lv_color_hex3(0xeee), 15);
//     lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

//     /*Add a three arc indicator*/
//     lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_meter_indicator_t * indic2 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_GREEN), -10);
//     lv_meter_indicator_t * indic3 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_BLUE), -20);

//     /*Create an animation to set the value*/
//     lv_anim_t a;
//     lv_anim_init(&a);
//     lv_anim_set_exec_cb(&a, set_value);
//     lv_anim_set_values(&a, 0, 100);
//     lv_anim_set_repeat_delay(&a, 100);
//     lv_anim_set_playback_delay(&a, 100);
//     lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

//     lv_anim_set_time(&a, 2000);
//     lv_anim_set_playback_time(&a, 500);
//     lv_anim_set_var(&a, indic1);
//     lv_anim_start(&a);

//     lv_anim_set_time(&a, 1000);
//     lv_anim_set_playback_time(&a, 1000);
//     lv_anim_set_var(&a, indic2);
//     lv_anim_start(&a);

//     lv_anim_set_time(&a, 1000);
//     lv_anim_set_playback_time(&a, 2000);
//     lv_anim_set_var(&a, indic3);
//     lv_anim_start(&a);

// }


void EncodeControl()
{

   Slider = lv_slider_create(lv_scr_act());

    lv_obj_set_size(Slider,100,20);
    lv_obj_set_pos(Slider,30,220);
    // lv_obj_center(Slider);






    // lv_group_t *Group = lv_group_create();
    // lv_group_add_obj(Group,Slider);
    // lv_group_add_obj(Group,Btn_OK);
    // lv_group_add_obj(Group,Btn_BACK);
    // lv_group_add_obj(Group,Btn_DOWN);
    // lv_group_add_obj(Group,Btn_UP);
    // lv_indev_set_group(indev_encoder,Group);
}



static void scroll_event_cb(lv_event_t * e)
{
    //>>>>>>>>>>>-----------------<!>---Link
    ///E1.----------------------------�õ�����
    lv_obj_t * cont = lv_event_get_target(e); //ͨ�����˸��¼��Ķ�������ȡ�������

    ///E2.---------------------------ͨ��һ���㷨���õ�������y������λ�ã�Ŀ�ģ����ں�������Ԫ�ذ�ť����y������ƫ��Ƚϣ�
    lv_area_t cont_a; //���� cont_area
    lv_obj_get_coords(cont, &cont_a); //��cont�����긳ֵ��cont_a (��cont_aԼ��Ϊcontainer�Ĵ�С��200 * 200)  coords������(x1,y1); (x2,y1); (x1,y2); (x2,y2)

    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2; //��ȡContainer��y������

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10; // 200*7 / 10 = 140

    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont); //child_cnt : child count �������� ��ȡcontainer����Ԫ�ظ���

    ///E3.------------------���������������Ԫ�أ���ť�����Ա������ЩԪ�ص����ԣ��û���ֱ����ʱ�򣬰�ť����ˮƽƫ�ƣ��������ò�ͬ��͸���ȣ�
    for(i = 0; i < child_cnt; i++)  //����Buttons
    {
        lv_obj_t * child = lv_obj_get_child(cont, i); //��ȡcontainer�ĵ�i��button
        lv_area_t child_a; //����һ�����ڶ�������
        lv_obj_get_coords(child, &child_a); //��child_aԼ��Ϊbutton�Ĵ�С��200 * 200��
        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2; //����õ�button��y������

        lv_coord_t diff_y = child_y_center - cont_y_center; // button��y������ - Container��y������ = Button�����Container�Ĵ�ֱƫ��
        diff_y = LV_ABS(diff_y); // ��ƫ��ȡ����ֵ��ABS��

        ///E3.1------------------����ƫ���ť�����������y��������λ�ã���������ͬ��xֵ
        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) // diff_y >= 140
        {
            x = r; //x = 140
        }
        else     // diff_y < 140
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y; // 140 * 140  - diff_y��ƽ��
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }
        ///E3.2--------------------����xֵ����button�ƶ�x����λ���룬����rӳ�����ͬ��͸����ֵ�����ð�ť��ͬ͸����
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0); //��button �ƶ� x����λ����

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);  //ͨ��r�Ĳ�ֵͬ����̬ӳ�䴴����͸����ֵ opa: opacity
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0); //����ťӦ�ò�͸����ֵ  opa: opacity
    }
}


void lv_example_soll_6(void)
{


    Bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Bg,240,240);
    lv_obj_set_style_bg_color(Bg,lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_radius(Bg,0,LV_PART_MAIN);
    
    ///�游����
    //lv_obj_t *screenA = lv_scr_act();
    ///������
    lv_obj_t * cont = lv_obj_create(lv_scr_act()); //����Ļ�ϴ���һ��container
    lv_obj_set_size(cont, 200, 200); //����cont�ĳߴ磺 w200, h200  �������Σ�
    lv_obj_center(cont);//��cont��ֱˮƽ���У�����ڸ�����
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);//����cont���Ӽ���layout: ���Բ��ֵ�������flex-flow��(����+��������)
    ///���������
    //1.����¼� // Link---<!>----------------------------------->>>>>>>>>>>>
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);//��cont���event���¼��Ļص��������¼����ͣ�Scroll��
    //2.������ʽ
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0); //���þ���Բ�� LV_RADIUS_CIRCLE��Բ�����
    lv_obj_set_style_clip_corner(cont, true, 0); //���ӳ�����������
    lv_obj_set_scroll_dir(cont, LV_DIR_VER); //����Scroll��������direction����ֱ����
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER); //��׽Cont Y������Ӷ��󣬽�������Container���Ķ��� �� snap �����񣻲�׽
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);//����scrollbar

    ///�Ӷ���
    uint32_t i;
    ///��container�ϴ������ɸ�button


    lv_group_t *Group = lv_group_create();

    for(i = 0; i < 20; i++)
    {
        lv_obj_t * btn = lv_btn_create(cont); //��container�ϴ���button
        lv_obj_set_width(btn, lv_pct(100)); //����button��width = lv_pct(100); //pct : percentage ����ڸ��׵Ŀ��100%

        ///�����
        lv_obj_t * label = lv_label_create(btn); //��button�ϴ���һ��label����ǩ��
        lv_label_set_text_fmt(label, "Button %d", i);  //��̬����label���ı�����  fmt: format����ʽ��
        lv_group_add_obj(Group,btn);
    }

    lv_indev_set_group(indev_encoder,Group);
    /*Update the buttons position manually for first*/ //�״��ֶ����°�ť��λ��
    lv_event_send(cont, LV_EVENT_SCROLL, NULL); //TODO

    /*Be sure the fist button is in the middle*/ //ȷ����һ����ť�����м�
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_ON); //��һ����ť�Ƿ��Թ���������������ָ��λ�ã�Ĭ��λ�ã�
}






extern lv_indev_t * indev_encoder;
#define UI_SIZE    (100)



lv_obj_t *Arc_Out;
lv_obj_t *ALL_Bg;
lv_obj_t *Arc_In;
lv_obj_t *Center;
lv_group_t *Group;
lv_anim_t Anima;
lv_obj_t *Btn;
lv_obj_t *Btn_Start;
lv_obj_t *text,*Atext;
BarState_e BarState = Charing;


void BarAnimation_CB(void * var, int32_t v)
{
    printf(" BarAnim Val: %d \r\n",v);

    if( BarState != InRelease)
    {
        lv_obj_set_style_arc_width(Arc_Out,10-v,LV_PART_MAIN);
    }
    else
    {
        lv_arc_set_value(Arc_In,100 - v);

        if(v == 100)
        {
            lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
        }
    }
    lv_label_set_text_fmt(text,"%d%s",lv_arc_get_value(Arc_In),"%");
}



void Btn_CB(lv_event_t *e)
{
    printf(" Btn_CB \r\n");
    if( lv_event_get_code(e) == LV_EVENT_PRESSED)
    {
        if( BarState == Full)
        {
            lv_anim_set_values(&Anima,0,100);
            lv_anim_set_time(&Anima, 3000);
            lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
            lv_anim_set_repeat_count(&Anima, 1);
            lv_anim_start(&Anima);
            lv_obj_add_flag(Arc_Out,LV_OBJ_FLAG_HIDDEN);

            lv_group_add_obj(Group,Arc_In);
            lv_group_focus_obj(Arc_In);
            lv_group_remove_obj(Btn);

            BarState = InRelease;
        }

    }
}


void Arc_Out_CB(lv_event_t *e)
{
    printf(" Arc_Out_CB \r\n");

    if(lv_arc_get_value(Arc_In) == 100)
    {
        lv_obj_clear_flag(Btn,LV_OBJ_FLAG_HIDDEN);
    }

}

void Arc_In_CB(lv_event_t *e)
{
    int16_t Arc_Val=0;

    Arc_Val = lv_arc_get_value(Arc_In);

    printf("Angle %d  State  %d\r\n",Arc_Val,BarState);

    if( Arc_Val == 100)
    {
        lv_obj_set_style_arc_color(Arc_In,lv_palette_main( LV_PALETTE_YELLOW),LV_PART_INDICATOR);
        lv_group_add_obj(Group,Btn);
        lv_group_focus_obj(Btn);
        lv_group_remove_obj(Arc_In);
        BarState = Full;
    }

    if(Arc_Val == 1)
    {
        lv_obj_set_style_arc_color(Arc_In,lv_palette_main( LV_PALETTE_BLUE),LV_PART_INDICATOR);
        lv_obj_clear_flag(Arc_Out,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
        BarState = Charing;
    }

    lv_arc_set_bg_angles(Arc_Out,lv_arc_get_angle_start(Arc_In),lv_arc_get_angle_end(Arc_In));

    switch (BarState)
    {
        case Charing:
                lv_anim_set_var(&Anima,Arc_Out);
                lv_anim_set_values(&Anima,0,10);
                lv_anim_set_time(&Anima, 500);
                lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
                lv_anim_set_repeat_count(&Anima, 1);
                lv_anim_start(&Anima);
            break;
        case Full:
                lv_anim_set_values(&Anima,0,10);
                lv_anim_set_time(&Anima, 500);
                lv_anim_set_repeat_delay(&Anima, 500);
                lv_anim_set_repeat_count(&Anima, LV_ANIM_PLAYTIME_INFINITE);
                lv_anim_set_exec_cb(&Anima, BarAnimation_CB);
                lv_anim_start(&Anima);
            break;
        case InRelease:
            break;
        default:
            break;
    }

}

// void StateBar()
// {

//     //��������
//     ALL_Bg = lv_obj_create(lv_scr_act());
//     lv_obj_set_size(ALL_Bg,240,240);
//     lv_obj_set_style_bg_color(ALL_Bg,lv_color_black(),LV_PART_MAIN);
//     lv_obj_set_style_radius(ALL_Bg,0,LV_PART_MAIN);
//     lv_obj_set_style_border_side(ALL_Bg,LV_BORDER_SIDE_FULL,LV_PART_MAIN);
//     lv_obj_set_style_border_color(ALL_Bg,lv_color_white(),LV_PART_MAIN);
//     lv_obj_set_style_border_width(ALL_Bg,0,LV_PART_MAIN);
//     lv_obj_set_scrollbar_mode(ALL_Bg,LV_SCROLLBAR_MODE_OFF);


//     Arc_Out =lv_arc_create(ALL_Bg); 
//     lv_obj_set_size(Arc_Out,UI_SIZE,UI_SIZE);
//     lv_obj_set_style_arc_color(Arc_Out,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
//     lv_obj_set_style_arc_opa(Arc_Out,LV_OPA_50,LV_PART_MAIN);
//     lv_obj_remove_style(Arc_Out, NULL, LV_PART_KNOB);//ɾ������
//     lv_obj_remove_style(Arc_Out, NULL, LV_PART_INDICATOR);//ɾ��������
//     lv_obj_set_style_arc_rounded(Arc_Out,0,LV_PART_MAIN);
//     lv_obj_set_style_arc_width(Arc_Out,10,LV_PART_MAIN);
//     lv_arc_set_value(Arc_Out,0);
//     lv_obj_align(Arc_Out,LV_ALIGN_BOTTOM_LEFT,-5,10);
//     lv_obj_add_event_cb(Arc_Out,Arc_Out_CB,LV_EVENT_DRAW_MAIN_END,NULL);

//     Arc_In =lv_arc_create(ALL_Bg); 
//     lv_obj_set_size(Arc_In,UI_SIZE-25,UI_SIZE-25);
//     lv_obj_align_to(Arc_In,Arc_Out,LV_ALIGN_CENTER,0,0);
//     lv_obj_set_style_arc_color(Arc_In,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);
//     lv_obj_set_style_arc_opa(Arc_In,LV_OPA_50,LV_PART_MAIN);
//     lv_obj_set_style_arc_width(Arc_In,5,LV_PART_MAIN);
//     lv_obj_set_style_arc_width(Arc_In,5,LV_PART_INDICATOR);
//     lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_MAIN);
//     lv_obj_set_style_arc_rounded(Arc_In,0,LV_PART_INDICATOR);
//     lv_arc_set_value(Arc_In,0);
//     lv_obj_remove_style(Arc_In, NULL, LV_PART_KNOB);
//     lv_obj_add_event_cb(Arc_In,Arc_In_CB,LV_EVENT_VALUE_CHANGED,NULL);
//     lv_arc_set_bg_angles(Arc_Out,lv_arc_get_angle_start(Arc_In),lv_arc_get_angle_end(Arc_In));


//     Center = lv_obj_create(ALL_Bg); 
//     lv_obj_set_size(Center,UI_SIZE-45,UI_SIZE-45);
//     lv_obj_align_to(Center,Arc_In,LV_ALIGN_CENTER,0,0);
//     lv_obj_set_style_radius(Center,LV_RADIUS_CIRCLE,0);
//     lv_obj_set_style_bg_opa(Center,LV_OPA_50,LV_PART_MAIN);
//     lv_obj_set_style_border_width(Center,0,LV_PART_MAIN);
//     lv_obj_set_style_bg_color(Center,lv_palette_main(LV_PALETTE_GREY),LV_PART_MAIN);


    
//     text = lv_label_create(ALL_Bg);
//     lv_obj_set_style_text_color(text,lv_color_white(),LV_PART_MAIN);
//     lv_obj_set_style_text_opa(text,LV_OPA_COVER,LV_PART_MAIN);
//     lv_label_set_text_fmt(text,"%d%s",lv_arc_get_value(Arc_In),"%");
//     lv_obj_set_style_text_font(text,&lv_font_montserrat_10,LV_PART_MAIN);
//     lv_obj_align_to(text,Center,LV_ALIGN_BOTTOM_MID,-3,15);


//     Btn = lv_btn_create(ALL_Bg);
//     Btn_Start = lv_label_create(Btn);
//     lv_obj_set_size(Btn,8,10);
//     lv_obj_set_style_radius(Btn,0,LV_PART_MAIN);
//     lv_label_set_text(Btn_Start,"V");
//     lv_obj_set_style_text_font(Btn_Start,&lv_font_montserrat_10,LV_PART_MAIN);
//     lv_obj_align(Btn_Start,LV_ALIGN_CENTER,0,0);
//     lv_obj_add_event_cb(Btn,Btn_CB,LV_EVENT_PRESSED,NULL);
//     lv_obj_add_flag(Btn,LV_OBJ_FLAG_HIDDEN);
//     lv_obj_align_to(Btn,Arc_In,LV_ALIGN_BOTTOM_RIGHT,-13,0);
    

//     Atext = lv_label_create(ALL_Bg);
//     lv_obj_set_style_text_color(Atext,lv_color_white(),LV_PART_MAIN);
//     lv_obj_set_style_flex_flow(Center,LV_FLEX_FLOW_ROW,LV_PART_MAIN);
//     lv_label_set_text_fmt(Atext,LV_SYMBOL_DOWN"\n"LV_SYMBOL_DOWN"\n"LV_SYMBOL_DOWN);   
//     lv_obj_set_style_text_font(Atext,&lv_font_montserrat_10,LV_PART_MAIN);
//     lv_obj_align_to(Atext,Center,LV_ALIGN_CENTER,0,0);


//     lv_anim_init(&Anima);

//     Group = lv_group_create();
//     lv_group_add_obj(Group,Arc_In);
//     lv_indev_set_group(indev_encoder,Group);

// }

//***************************************************//
//  ��������: LVGL UI����
//  
//  ����: ��
//  
//  ����ֵ: ��
//  
//  ˵��: ��
//  
//***************************************************//
static void LVGL_Build_GUI()
{
    BackGroung();
    lv_meter_1();
    // KeyBtn_OK();
    // KeyBtn_BACK();
    // KeyBtn_UP();
    // KeyBtn_DOWN();
//    EncodeControl();
    // lv_example_meter_1();
    // lv_indev_set_group(indev_encoder,Group);
    // Btn();
    // MeterTest();
}
