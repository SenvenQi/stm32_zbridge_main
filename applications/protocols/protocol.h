//
// Created by 25861 on 2023/3/17.
//

#ifndef RTTHREAD_PROTOCOL_H
#define RTTHREAD_PROTOCOL_H

#include "rtdef.h"
#include "rtthread.h"
#include "rtdevice.h"
#include "config/device.h"

struct rt_can_msg create_can_msg(rt_uint32_t id, const rt_uint8_t data[8]);

struct rx_uart_msg{
    rt_uint8_t head[2];
    rt_uint16_t length;
    rt_uint8_t cmd;
    rt_uint8_t data[256];
};

struct rx_uart_data{
    rt_uint8_t cmd;
    rt_uint8_t data[256];
};


extern rt_sem_t uart_protocol_sem;
extern rt_uint16_t receive_size;
extern unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
//struct rx_uart_data* uart_filter(size_t size);
void uart_base_handler();
#endif //RTTHREAD_PROTOCOL_H
