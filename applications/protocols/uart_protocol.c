//
// Created by 25861 on 2023/3/17.
//
#include "protocol.h"

static struct rx_uart_data uart_data;
struct rx_uart_data* uart_filter(void *buffer,size_t size){
    if (size >=5){
        struct rx_uart_msg* msg = (struct rx_uart_msg*)buffer;
        if (msg->length + 4 >= size){
            if (msg -> head[0] == 0xAA
             && msg -> head[1] == 0xBB
             && msg->data[msg->length-3] == 0xCC
             && msg->data[msg->length-2] == 0xDD){
                uart_data.cmd = msg->cmd;
                for (int i = 0; i < 256; ++i) {
                    uart_data.data[i] = msg->data[i];
                }
            }
        }
    }
    return &uart_data;
}