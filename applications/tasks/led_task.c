//
// Created by 天琪王 on 2023/3/7.
//
#include "rtdevice.h"
#include "rtthread.h"
#include "drv_gpio.h"
#include "config/device.h"
#include "core/thread_core.h"
#include "config/device.h"
void led_shan(){
    while (1){
        rt_uint32_t e;
        rt_err_t result = rt_event_recv(uart1_event,1,RT_EVENT_FLAG_OR ,
                               RT_WAITING_FOREVER,&e);
        if(result == RT_EOK){
            rt_pin_write(LED1,PIN_LOW);
            rt_pin_write(LED,PIN_HIGH);
            rt_thread_delay(300);
            rt_pin_write(LED,PIN_LOW);
            rt_pin_write(LED1,PIN_HIGH);
            rt_thread_delay(300);
        }
    }
}

THREAD_INIT_START(led_shan,RT_NULL,1024,25,10);