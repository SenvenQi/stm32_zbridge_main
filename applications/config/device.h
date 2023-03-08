//
// Created by 天琪王 on 2023/3/8.
//

#ifndef RTTHREAD_DEVICE_H
#define RTTHREAD_DEVICE_H

#include "rtdevice.h"

struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};

#define CAN_NAME "can1"
extern rt_device_t can_dev;
extern struct rt_semaphore can_sem;

#define UART1_NAME "uart1"
extern rt_device_t uart1_dev;
extern struct rt_messagequeue uart1_mq;

#endif //RTTHREAD_DEVICE_H
