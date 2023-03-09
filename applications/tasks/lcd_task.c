//
// Created by 天琪王 on 2023/3/9.
//
#include "drv_lcd.h"

void lcd_task(){
    while (1){
        lcd_fill(0,0,LCD_W,LCD_H,3355);
        lcd_show_string(30,30,32,"ZBridge");
        rt_thread_delay(30000000);
    }
}


int lcd_start(){
    rt_thread_t led_thread = rt_thread_create("lcd",lcd_task,RT_NULL,1024,25,10);
    rt_thread_startup(led_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(lcd_start);
