//
// Created by 25861 on 2023/3/17.
//
#include "protocol.h"

rt_uint16_t receive_size = 0;
unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
rt_uint16_t message_length = 0;
size_t size;
size_t count = 0;
void uart_protocol_handler(void (*handler)(struct rx_uart_data rxUartData)){
    while (receive_size >= message_length){
        if (receive_size < 4){
            break;
        }
        if(rx_buffer[0] !=0xCC || rx_buffer[1] != 0xDD){
            message_length = 0;
            receive_size = 0;
            break;
        }
        if (message_length == 0)
            message_length = (((rt_uint16_t)rx_buffer[2]<<8) + ((rt_uint16_t)rx_buffer[3])) + 4;
        if(message_length <= receive_size) {
            size = message_length;
            rt_uint8_t *data = (rt_uint8_t *) rt_malloc(size);
            for (int i = 0; i < size; ++i) {
                data[i] = rx_buffer[i];
            }
            for (int i = 0; i < sizeof rx_buffer - size; ++i) {
                rx_buffer[i] = rx_buffer[size + i];
            }

            struct rx_uart_data uart_data;
            if (data[size -2] == 0xEE
                && data[size - 1] == 0xFF) {
                uart_data.cmd = data[4];
                for (int i = 5; i < size - 2; ++i) {
                    uart_data.data[i] = data[i];
                }
                message_length = 0;
                receive_size -= size;
                count++;
                handler(uart_data);
                rt_free(data);
            } else {
                message_length = 0;
                receive_size = 0;
                break;
            }
        } else
            break;
    }
}