//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


void buzzer_task(){
    while (1){
        rt_sem_take(buzzer_sem, RT_WAITING_FOREVER);
        buzzer_di_handler();
    }
}

THREAD_INIT_START(buzzer_task,RT_NULL,1024,25,10);