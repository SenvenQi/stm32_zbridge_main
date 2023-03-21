//
// Created by 25861 on 2023/3/5.
//
#include "task.h"

void can_callback(void *parameter){
    while (1)
    {
        rt_sem_take(can_sem, RT_WAITING_FOREVER);
        can_data_handler();
    }
}

THREAD_INIT_START(can_callback,RT_NULL,1024,10,10);