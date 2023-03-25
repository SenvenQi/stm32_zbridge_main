//
// Created by 25861 on 2023/3/18.
//

#include "service.h"
char lcd_num[256];
void lcd_write(char *str){
    lcd_show_string(0,0,48,str);
}

void lcd_clear_color(rt_uint16_t back_color,rt_uint16_t fore_color){
    lcd_set_color(back_color,fore_color);
    lcd_clear(back_color);
}

void brightness(rt_uint32_t brightness_size){
    rt_pwm_set_pulse(pwm_dev_lcd,PWM_DEV_LCD_CHANNEL,brightness_size);
}

void lcd_point_shan(){
    rt_uint16_t point_color = 0xFFFF;
    while (1){
        rt_thread_delay(300);
        char head[13] = {0xA2,0xD9,0xBA,0xC5,0xD4,0xBF,0xB3,0xD7,0xD4,0xDA,0xCE,0xBB};
        char middle[7] = {0xD3,0xE0,0xC7,0xE1,0xCB,0xC9};
        char footer[11] = {0xCB,0xD5,0x45,0x2D,0x31,0x32,0x33,0x34,0xBE,0xAF};
//        lcd_show_string(15,2,48,(char *)head);
        lcd_show_string(45*2,52,48,(char *)middle);
//        lcd_show_string(38,52* 2,48,(char *)footer);
        if (point_color == 0)
            point_color += 0x08;
        else
            point_color -= 0x08;

        lcd_set_color(0x0000,point_color);
    }
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
        rt_pwm_set(pwm_dev_lcd, PWM_DEV_LCD_CHANNEL, period, pulse);
    }
}