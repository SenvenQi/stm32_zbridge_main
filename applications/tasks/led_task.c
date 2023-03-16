//
// Created by 天琪王 on 2023/3/7.
//
#include "rtdevice.h"
#include "rtthread.h"
#include "drv_gpio.h"
#include "config/device.h"

void led_shan(){
    while (1){
        rt_pin_write(LED,PIN_HIGH);
        rt_pin_write(LED1,PIN_LOW);
        rt_thread_delay(300);
        rt_pin_write(LED,PIN_LOW);
        rt_pin_write(LED1,PIN_HIGH);
        rt_thread_delay(300);
    }
}
void (*led_task)(void *parameter) = led_shan;