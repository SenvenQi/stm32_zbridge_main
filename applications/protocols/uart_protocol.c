//
// Created by 25861 on 2023/3/17.
//
#include "protocol.h"

void uart_filter(char buffer[],size_t size){
    if (size >=5){
        struct rx_uart_msg* msg = (struct rx_uart_msg*)buffer;
        if (msg->length + 4 >= size){
            if (msg -> head[0] == 0xAA
             && msg -> head[1] == 0xBB
             && msg->data[msg->length-3] == 0xCC
             && msg->data[msg->length-2] == 0xDD){
                if (msg->cmd == 0x01){
                    rt_kprintf("success uart filter OK!");
                }
            }
        }
    }
}