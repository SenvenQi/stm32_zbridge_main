//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"
#include "protocols/protocol.h"



void buzzer_di_handler(){
    di();
}

void lcd_init_handler(){
    lcd_clear_color(0x0000,0xF000);
}