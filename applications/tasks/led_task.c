//
// Created by 天琪王 on 2023/3/7.
//
#include "task.h"

void led_shan(){
    while (1){
        rt_uint32_t e;
            rt_pin_write(LED1,PIN_LOW);
            rt_pin_write(LED,PIN_HIGH);
            rt_thread_delay(300);
            rt_pin_write(LED,PIN_LOW);
            rt_pin_write(LED1,PIN_HIGH);
            rt_thread_delay(300);
    }
}

THREAD_INIT_START(led_shan,RT_NULL,1024,25,1000);