//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"



void buzzer_di_handler(){
    di();
}

void lcd_init_handler(){
    lcd_clear_color(0x0000,0xF000);
}

void lcd_show_data(){
    lcd_write((char *)uart_data.data);
}