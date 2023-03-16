//
// Created by 25861 on 2023/3/17.
//

#ifndef RTTHREAD_PROTOCOL_H
#define RTTHREAD_PROTOCOL_H

#include "rtdef.h"
#include "rtthread.h"
#include "rtdevice.h"

struct rt_can_msg create_can_msg(rt_uint32_t id, const rt_uint8_t data[8]);


struct temperature{
    rt_uint8_t head[2];
    rt_uint16_t length;
    rt_uint8_t* data;
};

void temperature_filter(rt_uint8_t *buffer);

struct rx_uart_msg{
    rt_uint8_t head[2];
    rt_uint16_t length;
    rt_uint8_t cmd;
    rt_uint8_t data[256];
};
void uart_filter(char buffer[],size_t size);

#endif //RTTHREAD_PROTOCOL_H
