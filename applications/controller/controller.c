//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"
#include "protocols/protocol.h"


void uart1_handler(void *buffer,size_t size){
    struct rx_uart_data* uart_data = uart_filter(buffer,size);
    rt_kprintf("%d",size);
}

void buzzer_di_handler(){
    di();
}

void lcd_init_handler(){
    lcd_write("hello 代码修改过的初始化");
}