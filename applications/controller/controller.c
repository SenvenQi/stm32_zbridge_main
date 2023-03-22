//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"

void uart1_work(struct rx_uart_data uart_data){
    switch (uart_data.cmd) {
        case 0x81: {
            rt_uint8_t data[8] = {uart_data.data[1], uart_data.data[2], uart_data.data[3], uart_data.data[4], 0xB1,
                                  0xF1, 0xB3, 0xF1};
            struct rt_can_msg message = create_can_msg(0xFF, data);
            send_can_msg(message);
            rt_sem_release(buzzer_sem);
            break;
        }
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

void flash_write_fonts(void *buffer,rt_uint64_t addr,size_t size){
    flash_write(buffer,addr,size);
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

void config_can_id(){
    config_id();
    config_filter();
}

void lcd_show_data(){
    lcd_clear_color(0x0000,0xF000);
    lcd_write("loading ......");
}

void app_init(){
    lcd_show_data();
    fal_init();
    flash_read_config();
    config_can_id();
    char data[8] = { 0xBC,0xD3,0xD4,0xD8,0xB3,0xC9,0xB9,0xA6 };
    lcd_write((char *)data);
}

