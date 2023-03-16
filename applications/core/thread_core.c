//
// Created by 25861 on 2023/3/16.
//
#include "thread_core.h"

int thread_init_start(const char *name,
                       void (*entry)(void *parameter),
                       void       *parameter,
                       rt_uint32_t stack_size,
                       rt_uint8_t  priority,
                       rt_uint32_t tick){
    rt_thread_t led_task_thread = rt_thread_create(name,entry,parameter,stack_size,priority,tick);
    rt_thread_startup(led_task_thread);
    return RT_EOK;
}
