//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


void buzzer_task(){
    rt_err_t result;
    rt_uint32_t e;
    while (1){
        result = rt_event_recv(uart1_event,1,RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_FOREVER,&e);
        if (result == RT_EOK)
        {
            di();
        }
    }
}