//
// Created by 25861 on 2023/3/19.
//
#include "task.h"

void uart_protocol_task(){
    rt_err_t err;
    while (1){
            err = rt_sem_take(uart_protocol_sem, RT_WAITING_FOREVER);
            if(err == RT_EOK)
                uart1_data_handler();
    }
}

THREAD_INIT_START(uart_protocol_task,RT_NULL,1024,11,10)