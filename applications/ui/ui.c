//
// Created by 天琪王 on 2023/3/10.
//
#include "lvgl.h"
#include "drv_lcd.h"
void lv_user_gui_init() {
    static lv_coord_t col_dsc[] = {LCD_W -30,LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LCD_H/2 -15, LCD_H/2 -15,LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, LCD_W, LCD_H);
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_t * label;
    lv_obj_t * obj;

    uint32_t i;
    for(i = 0; i < 2; i++) {
        uint8_t col = 0;
        uint8_t row = i;

        obj = lv_btn_create(cont);
        /*Stretch the cell horizontally and vertically too
         *Set span to 1 to make the cell 1 column/row sized*/
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1,
                             LV_GRID_ALIGN_STRETCH, row, 1);

        label = lv_label_create(obj);
        lv_label_set_text_fmt(label, "c%d, r%d 2222222222222", col, row);
        lv_obj_center(label);
    }
}