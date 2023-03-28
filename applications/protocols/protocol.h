//
// Created by 25861 on 2023/3/17.
//

#ifndef RTTHREAD_PROTOCOL_H
#define RTTHREAD_PROTOCOL_H

#include "rtdef.h"
#include "rtthread.h"
#include "rtdevice.h"
#include "config/device.h"
#include "controller/controller.h"

struct rx_can_data{
    rt_uint8_t cmd;
    rt_uint8_t cabinet_no;
    rt_uint8_t data[5];
    rt_uint8_t check;
};

struct rt_can_msg create_can_msg(rt_uint32_t id, const rt_uint8_t data[8]);

extern struct rt_can_msg rx_msg;

struct rx_uart_data{
    rt_uint8_t cmd;
    rt_uint8_t data[256];
};


extern rt_uint16_t receive_size;
extern unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
//struct rx_uart_data* uart_filter(size_t size);
void uart_protocol_handler(void (*handler)(struct rx_uart_data rxUartData));
void can_protocol_handler(void (*handler)(struct rx_can_data* rxCanData));

extern rt_uint16_t TT_Buffer[555];
extern rt_uint8_t TT_voltage[555];
unsigned char Decode(void);
#endif //RTTHREAD_PROTOCOL_H
