//
// Created by 25861 on 2023/3/16.
//
#include "rtthread.h"
#include "fal.h"
#include "tasks/zb_task.h"

int startup(){
    fal_init();
    rt_thread_t led_task_thread = rt_thread_create("led",led_task,RT_NULL,1024,25,10);
    rt_thread_t uart1_task_thread = rt_thread_create("uart1",uart1_task,RT_NULL,1024,25,10);
    rt_thread_t lcd_task_thread = rt_thread_create("lcd",lcd_task,RT_NULL,1024,25,10);
    rt_thread_startup(led_task_thread);
    rt_thread_startup(uart1_task_thread);
    rt_thread_startup(lcd_task_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(startup);