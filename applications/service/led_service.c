//
// Created by 25861 on 2023/3/21.
//

#include "service.h"


void twinkle(){
    rt_pin_write(LED1,PIN_LOW);
    rt_pin_write(LED,PIN_LOW);
    rt_thread_delay(300);
    rt_pin_write(LED1,PIN_HIGH);
    rt_pin_write(LED,PIN_HIGH);
    rt_thread_delay(300);
}