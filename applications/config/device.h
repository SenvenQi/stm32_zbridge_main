//
// Created by 天琪王 on 2023/3/8.
//

#ifndef RTTHREAD_DEVICE_H
#define RTTHREAD_DEVICE_H

#include "rtdevice.h"

#define CAN_NAME "can1"
#define UART1_NAME "uart1"

struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};

static rt_device_t can_dev;
static rt_device_t uart1_dev;

static struct rt_semaphore can_sem;
static struct rt_messagequeue uart1_mq;

static char msg_pool[256];
#endif //RTTHREAD_DEVICE_H
