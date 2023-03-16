//
// Created by Ììç÷Íõ on 2023/3/9.
//
#include "drv_lcd.h"
#include "fal.h"


void lcd_task(){
    lcd_set_color(BLACK,WHITE);
    lcd_clear(BLACK);
//    rt_uint32_t erase_size = fal_partition_erase_all(falPartition);
    lcd_show_string(64,32,32,"hello£¡ÄãºÃ°¡");

}


int lcd_start(){
    rt_thread_t led_thread = rt_thread_create("lcd",lcd_task,RT_NULL,1024,25,10);
    rt_thread_startup(led_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(lcd_start);