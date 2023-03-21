//
// Created by 天琪王 on 2023/3/7.
//
#include "task.h"

void led_shan(){
    while (1){
        twinkle();
    }
}

THREAD_INIT_START(led_shan,RT_NULL,1024,25,1000);