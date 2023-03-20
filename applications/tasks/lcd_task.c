//
// Created by ּלחקֽץ on 2023/3/20.
//
#include "task.h"


void lcd_task(void* parameter){
    rt_err_t err;
    while(1){
        err = rt_sem_take(lcd_sem,RT_WAITING_FOREVER);
        if(err == RT_EOK)
            lcd_show_data();
    }
}

THREAD_INIT_START(lcd_task,RT_NULL,1024,20,10)
