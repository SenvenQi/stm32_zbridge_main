//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


void buzzer_task(){
    rt_err_t result;
    rt_uint32_t e;
    while (1){
            di();
    }
}
THREAD_INIT_START(buzzer_task,RT_NULL,1024,10,10);