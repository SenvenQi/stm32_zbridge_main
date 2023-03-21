//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


void buzzer_task(){
    rt_err_t err;
    while (1){
        err = rt_sem_take(buzzer_sem, RT_WAITING_FOREVER);
        if (err == RT_EOK)
            buzzer_di_handler();
    }
}

THREAD_INIT_START(buzzer_task,RT_NULL,1024,25,10);