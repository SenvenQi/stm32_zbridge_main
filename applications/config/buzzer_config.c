//
// Created by 25861 on 2023/3/18.
//

#include "device.h"

int buzzer_config(){
    rt_pin_mode(BUZZER,PIN_MODE_OUTPUT);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(buzzer_config);