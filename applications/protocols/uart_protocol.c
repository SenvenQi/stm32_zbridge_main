//
// Created by 25861 on 2023/3/17.
//
#include "protocol.h"
#include "service/service.h"

static struct rx_uart_data uart_data;
rt_uint16_t receive_size = 0;
unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
rt_uint16_t message_length = 0;

void uart_base_handler(){
    rt_mutex_take(uart1_mutex, RT_WAITING_FOREVER);
    if (receive_size >= message_length + 4){
        if(rx_buffer[0] !=0xAA || rx_buffer[1] != 0xBB)
            receive_size = 0;
        if (message_length == 0)
            message_length = (((rt_uint16_t)rx_buffer[2]) + ((rt_uint16_t)rx_buffer[3]<<8));
        if(message_length +4 <= receive_size){
            size_t size = message_length +4;
            rt_uint8_t data[size];
            for (int i = 0; i < size; ++i) {
                data[i] = rx_buffer[i];
                rx_buffer[i] = rx_buffer[i+1];
            }

            receive_size -= size;
            struct rx_uart_msg* msg = (struct rx_uart_msg*)data;
            if (msg->length + 4 >= size){
                if (msg -> head[0] == 0xAA
                    && msg -> head[1] == 0xBB
                    && msg->data[msg->length-3] == 0xCC
                    && msg->data[msg->length-2] == 0xDD){
                    uart_data.cmd = msg->cmd;
                    for (int i = 0; i < msg->length - 1; ++i) {
                        if (i == (msg->length -3))
                            break;
                        uart_data.data[i] = msg->data[i];
                    }
                    buzzer_enable = RT_TRUE;
                    message_length = 0;
                    lcd_write((char*)uart_data.data);
                }else
                    receive_size = 0;
            }
        }
        rt_mutex_release(uart1_mutex);
    } else
        rt_mutex_release(uart1_mutex);
}

//struct rx_uart_data* uart_filter(size_t size){
//    if(receive_size <=4) {
//        receive_size += size;
//    }
//    if(receive_size >4 && rx_buffer[0] == 0xAA && rx_buffer[1] == 0xBB){
//        receive_size += size;
//        rt_uint16_t message_length = (((rt_uint16_t)rx_buffer[2]) + ((rt_uint16_t)rx_buffer[3]<<8));
//        if(message_length +4 <= receive_size){
//            rt_uint8_t data[size];
//            for (int i = 0; i < size; ++i) {
//                data[i] = rx_buffer[i];
//                rx_buffer[i] = rx_buffer[i+1];
//            }
//            receive_size -= size;
//            struct rx_uart_msg* msg = (struct rx_uart_msg*)data;
//            if (msg->length + 4 >= size){
//                if (msg -> head[0] == 0xAA
//                    && msg -> head[1] == 0xBB
//                    && msg->data[msg->length-3] == 0xCC
//                    && msg->data[msg->length-2] == 0xDD){
//                    uart_data.cmd = msg->cmd;
//                    for (int i = 0; i < msg->length - 1; ++i) {
//                        if (i == (msg->length -3))
//                            break;
//                        uart_data.data[i] = msg->data[i];
//                    }
//                }
//            }
//        }
//    }
//    return &uart_data;
//}