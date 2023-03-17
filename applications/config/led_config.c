//
// Created by 25861 on 2023/3/16.
//
#include "device.h"

int led_config(){
    rt_pin_mode(LED,PIN_MODE_OUTPUT);
    rt_pin_mode(LED1,PIN_MODE_OUTPUT);
    rt_pin_write(LED,PIN_HIGH);
    rt_pin_write(LED1,PIN_HIGH);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(led_config);