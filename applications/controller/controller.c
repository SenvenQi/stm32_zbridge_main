//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"

void uart1_work(struct rx_uart_data uart_data){
    switch (uart_data.cmd) {
        case 0x81:
            buzzer_enable = RT_TRUE;
            rt_uint8_t data[8] = {uart_data.data[1],uart_data.data[2],uart_data.data[3],uart_data.data[4],0xB1,0xF1,0xB3,0xF1};
            struct rt_can_msg message = create_can_msg(0xFF,data);
            send_can_msg(message);
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



void uart1_data_handler(){
    uart_protocol_handler(uart1_work);
}

void can_wrok(struct rx_can_data* rxCanData){
    lcd_write("hello data!");
}

void can_data_handler(){
    can_protocol_handler(can_wrok);
}

void buzzer_di_handler(){
    di();
}

void app_init(){
    fal_init();
    lcd_clear_color(0x0000,0xF000);
    lcd_write("hello 你好");
    config_id();
    config_filter();
}


void config_can_id(){
    config_id();
    config_filter();
}