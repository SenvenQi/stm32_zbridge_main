//
// Created by 25861 on 2023/3/19.
//
#include "task.h"

void uart_protocol_task(){
    while (1){
            uart_base_handler();
//            rt_pin_write(LED1,PIN_LOW);
//            rt_pin_write(LED,PIN_HIGH);
//            rt_thread_delay(300);
//            rt_pin_write(LED,PIN_LOW);
//            rt_pin_write(LED1,PIN_HIGH);
//            rt_thread_delay(300);


    }
}

THREAD_INIT_START(uart_protocol_task,RT_NULL,1024,11,100)