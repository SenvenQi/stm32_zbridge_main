//
// Created by 25861 on 2023/3/16.
//

#ifndef RTTHREAD_THREAD_CORE_H
#define RTTHREAD_THREAD_CORE_H

#include "rtthread.h"

#define THREAD_INIT_START(fn,parameter,stack_size,priority,tick) \
                    int start_##fn(){ \
                    thread_init_start(#fn,fn,parameter,stack_size,priority,tick); \
                    return RT_EOK;\
                    } INIT_APP_EXPORT(start_##fn);

int thread_init_start(const char *name,
                       void (*entry)(void *parameter),
                       void       *parameter,
                       rt_uint32_t stack_size,
                       rt_uint8_t  priority,
                       rt_uint32_t tick);

#endif //RTTHREAD_THREAD_CORE_H
