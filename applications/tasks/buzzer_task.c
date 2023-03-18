//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


void buzzer_task(){
    while (1){
        if(buzzer_enable){
            di();
            buzzer_enable = RT_FALSE;
        }
    }
}
THREAD_INIT_START(buzzer_task,RT_NULL,1024,25,10);