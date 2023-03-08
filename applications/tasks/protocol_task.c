//
// Created by 25861 on 2023/3/8.
//
#include "rtthread.h"


void protocol_handle_task(){
    while (1){
    }
}

int protocol_handle_thread_start(){
    rt_thread_t protocol_handle_thread = rt_thread_create("protocol_handle_task",protocol_handle_task,RT_NULL,1024,25,10);
    rt_thread_startup(protocol_handle_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(protocol_handle_thread_start);