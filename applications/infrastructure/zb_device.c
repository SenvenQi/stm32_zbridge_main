//
// Created by 天琪王 on 2023/3/2.
//
#include "zb_device.h"

rt_device_t dev_open(char *dev_name,rt_uint16_t oflag){
    rt_device_t dev = rt_device_find(dev_name);
    rt_device_open(dev, oflag);
    return dev;
}

rt_err_t rx_call(rt_device_t dev, rt_size_t size)
{
    switch (rt_object_get_type(dev->user_data)) {
        case RT_Object_Class_Semaphore:
            rt_sem_release((rt_sem_t)dev->user_data);
            break;
        case RT_Object_Class_MessageQueue:
            {
                char msg[8];
                rt_memset(&msg, 0, 8);
                rt_mq_send((rt_mq_t)dev->user_data, &msg, sizeof(msg));
            }
            break;
    }

    return RT_EOK;
}

void device_task_create(char *device_name,void (*callback)(void *buffer),enum rt_object_class_type type,rt_uint16_t flag){
    rt_object_t rx_mq;
    switch (type) {
        case RT_Object_Class_Semaphore:
            rx_mq = (rt_object_t) rt_sem_create(device_name, 0, RT_IPC_FLAG_FIFO);
            break;
        case RT_Object_Class_MessageQueue:
            rx_mq = (rt_object_t) rt_mq_create(device_name, 8, 1024, RT_IPC_FLAG_FIFO);
            break;
    }
    device_task_t device_task_p;
    device_task_p = (device_task_t) rt_malloc(1024);
    rt_memset(device_task_p, 0, 1024);
    rt_device_t dev = dev_open(device_name,flag);
    char *name = device_name;
    rt_object_t rx_sem = (rt_object_t) rx_mq;
    device_task_p->callback = callback;
    zb_task_create(device_task_p);
    rt_device_set_rx_indicate(dev,rx_call);
    rt_thread_t task = rt_thread_create(name,callback,rx_sem,1024,25,10);
    rt_thread_startup(task);
}

