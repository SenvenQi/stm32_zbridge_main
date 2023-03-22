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

#define THREAD_SEM_INIT_START(task_method,sem,parameter,stack_size,priority,tick) \
    void task_##task_method(void *p){ \
        rt_err_t err; \
        while (1) \
        { \
            err = rt_sem_take(sem , RT_WAITING_FOREVER); \
            if (err == RT_EOK)                                                    \
            {                                                                 \
                task_method();                                                  \
            }                                                                          \
        } \
    } \
    THREAD_INIT_START(task_##task_method,parameter,stack_size,priority,tick)

#define THREAD_WHILE_INIT_START(task_method,sem,parameter,stack_size,priority,tick) \
    void task_##task_method(void *p){ \
        rt_err_t err; \
        while (1) \
        { \
                task_method();                                                  \
        } \
    } \
    THREAD_INIT_START(task_##task_method,parameter,stack_size,priority,tick)

int thread_init_start(const char *name,
                       void (*entry)(void *parameter),
                       void       *parameter,
                       rt_uint32_t stack_size,
                       rt_uint8_t  priority,
                       rt_uint32_t tick);

#endif //RTTHREAD_THREAD_CORE_H
