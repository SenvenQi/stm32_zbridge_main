//
// Created by 天琪王 on 2023/3/20.
//
#include "task.h"

void dial_switch_task(){
    while (1)
    {
        rt_sem_take(sw_sem, RT_WAITING_FOREVER);
        config_can_id();
    }
}

THREAD_INIT_START(dial_switch_task,RT_NULL,1024,20,          10)