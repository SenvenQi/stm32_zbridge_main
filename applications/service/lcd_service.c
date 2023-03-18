//
// Created by 25861 on 2023/3/18.
//

#include "service.h"

void lcd_write(char *str){
    lcd_show_string(0,10,32,str);
}

void lcd_clear_color(rt_uint16_t back_color,rt_uint16_t fore_color){
    lcd_set_color(back_color,fore_color);
    lcd_clear(back_color);
}

void brightness(rt_uint32_t brightness_size){
    rt_pwm_set_pulse(pwm_dev_lcd,PWM_DEV_CHANNEL,brightness_size);
}

void splash_screen(){
    while (1){
        rt_thread_mdelay(10);
        if (dir)
        {
            pulse += 10000;      /* 从0值开始每次增加5000ns */
        }
        else
        {
            pulse -= 10000;      /* 从最大值开始每次减少5000ns */
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }

        /* 设置PWM周期和脉冲宽度 */
        rt_pwm_set(pwm_dev_lcd, PWM_DEV_CHANNEL, period, pulse);
    }
}