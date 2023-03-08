//
// Created by 天琪王 on 2023/3/7.
//
#include "rtdevice.h"
#include "rtthread.h"
#include "drv_gpio.h"

void led_shan(){
    rt_base_t led = GET_PIN(A,8);
    rt_pin_mode(led,PIN_MODE_OUTPUT);
    while (1){
        rt_pin_write(led,PIN_HIGH);
        rt_thread_delay(300);
        rt_pin_write(led,PIN_LOW);
        rt_thread_delay(300);
    }
}

int led_start(){
    rt_thread_t led_thread = rt_thread_create("led",led_shan,RT_NULL,1024,25,10);
    rt_thread_startup(led_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(led_start);