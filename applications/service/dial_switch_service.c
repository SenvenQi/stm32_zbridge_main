//
// Created by 天琪王 on 2023/3/20.
//

#include "config/device.h"

rt_uint8_t id = 0;

void config_id() {
    rt_uint8_t one = rt_pin_read(SW1);
    rt_uint8_t two = rt_pin_read(SW2);
    rt_uint8_t three = rt_pin_read(SW3);
    rt_uint8_t four = rt_pin_read(SW4);
    rt_uint8_t five = rt_pin_read(SW5);
    rt_uint8_t six = rt_pin_read(SW6);
    rt_uint8_t seven = rt_pin_read(SW7);
    rt_uint8_t eight = rt_pin_read(SW8);
    id = one + (two << 1) + (three << 2) + (four<< 3) + (five << 4) + (six << 5) + (seven << 6) + (eight << 7);
}