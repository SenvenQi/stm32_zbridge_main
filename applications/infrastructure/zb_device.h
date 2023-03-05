//
// Created by 天琪王 on 2023/3/2.
//

#ifndef RTTHREAD_ZB_DEVICE_H
#define RTTHREAD_ZB_DEVICE_H

#include <rtthread.h>

void device_task_create(char *device_name,void (*callback)(void *buffer),enum rt_object_class_type type,rt_uint16_t flag);
rt_device_t dev_open(char *dev_name,rt_uint16_t oflag);
#endif //RTTHREAD_ZB_DEVICE_H
