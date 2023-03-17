//
// Created by 25861 on 2023/3/17.
//

#include "controller.h"
#include "protocols/protocol.h"


void uart1_handler(rt_uint8_t buffer[],size_t size){
    uart_filter(buffer,size);
    rt_kprintf("%d",size);
}

void buzzer_di(){
    di();
}