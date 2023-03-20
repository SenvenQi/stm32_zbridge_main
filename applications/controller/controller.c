//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"


void uart1_data_handler(){
    switch (uart_data.cmd) {
        case 0x81:
            buzzer_enable = RT_TRUE;
            rt_sem_release(lcd_sem);
            break;
        case 0xE1:
            break;
        case 0x92:
            break;
        case 0x85:
            break;
        default:
            break;
    }
}

void buzzer_di_handler(){
    di();
}

void lcd_init_handler(){
    lcd_clear_color(0x0000,0xF000);
    lcd_write("loading .....");
}

void lcd_show_data(){
    lcd_write((char *)uart_data.data);
}

void config_can_id(){
    config_id();
    config_filter();
}