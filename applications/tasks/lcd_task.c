//
// Created by 天琪王 on 2023/3/9.
//
#include "drv_lcd.h"
#include "core/thread_core.h"

void lcd_init_task(void* parameter){
    lcd_set_color(BLACK,0xFC99);
    lcd_clear(BLACK);
//    rt_uint32_t erase_size = fal_partition_erase_all(falPartition);
    while (1){
        lcd_show_string(0,0,32,"hello！zbridge 你好啊 陈博文 为中华之崛起而读书");
        lcd_set_color(BLACK,0xFCFF);
        rt_thread_delay(300);
        lcd_show_string(0,0,32,"hello！zbridge 你好啊 陈博文 为中华之崛起而读书");
        lcd_set_color(BLACK,0x0C99);
        rt_thread_delay(300);

    }
}

THREAD_INIT_START(lcd_init_task,RT_NULL,1024,25,10)