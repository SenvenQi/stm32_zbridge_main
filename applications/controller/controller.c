//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"

void uart1_work(struct rx_uart_data uart_data){
    switch (uart_data.cmd) {
        case 0x81:
            buzzer_enable = RT_TRUE;
            rt_uint8_t data[8] = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
            struct rt_can_msg message = create_can_msg(0xFF,data);
            send_can_msg(message);
//            lcd_write("\xb1\xf1");
//            rt_device_write(can_dev,0,RT_NULL,3);
//            rt_sem_release(lcd_sem);
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

void lcd_init_handler(){
    lcd_clear_color(0x0000,0xF000);
    lcd_write("loading .....");
    config_filter();
}

void lcd_show_data(){
    lcd_write(lcd_num);
}

void config_can_id(){
    config_id();
    config_filter();
    rt_sprintf(lcd_num,"%d",can_id);
    lcd_clear_color(0x0000,0xF000);
    lcd_write(lcd_num);
//    rt_sem_release(lcd_sem);
}