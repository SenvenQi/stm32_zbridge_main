//
// Created by 25861 on 2023/3/18.
//

#include "service.h"

void lcd_write(char *str){
    lcd_set_color(BLACK,0xFC99);
    lcd_clear(BLACK);
    lcd_show_string(0,10,32,str);
}

void brightness(rt_uint32_t brightness_size){
    rt_pwm_set_pulse(pwm_dev_lcd,PWM_DEV_CHANNEL,brightness_size);
}