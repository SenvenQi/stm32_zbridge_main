//
// Created by 25861 on 2023/3/18.
//

#include "device.h"
rt_sem_t buzzer_sem;

int buzzer_config(){
    buzzer_sem = rt_sem_create(BUZZER_NAME,0,RT_IPC_FLAG_FIFO);
    rt_pin_mode(BUZZER,PIN_MODE_OUTPUT);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(buzzer_config);