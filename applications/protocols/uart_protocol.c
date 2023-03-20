//
// Created by 25861 on 2023/3/17.
//
#include "protocol.h"

rt_uint16_t receive_size = 0;
unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
rt_uint16_t message_length = 0;
size_t size;
size_t count = 0;
void uart_base_handler(void (*handler)(struct rx_uart_data rxUartData)){
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


            struct rx_uart_msg *msg = (struct rx_uart_msg *) data;

            struct rx_uart_data uart_data;
            if (msg->data[msg->length - 3] == 0xEE
                && msg->data[msg->length - 2] == 0xFF) {
                uart_data.cmd = msg->cmd;
                for (int i = 0; i < msg->length - 1; ++i) {
                    if (i == (msg->length - 3))
                        break;
                    uart_data.data[i] = msg->data[i];
                }
                message_length = 0;
                receive_size -= size;
                count++;
                handler(uart_data);
                rt_free(msg);
            } else {
                message_length = 0;
                receive_size = 0;
                break;
            }

        } else
            break;
    }
}