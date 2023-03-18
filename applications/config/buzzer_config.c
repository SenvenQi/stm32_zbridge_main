//
// Created by 25861 on 2023/3/18.
//

#include "device.h"
rt_bool_t buzzer_enable;
int buzzer_config(){
    buzzer_enable = RT_FALSE;
    rt_pin_mode(BUZZER,PIN_MODE_OUTPUT);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(buzzer_config);