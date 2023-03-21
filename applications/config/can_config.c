//
// Created by 25861 on 2023/3/16.
//

#include "device.h"

rt_device_t can_dev;
rt_sem_t can_sem;

static rt_err_t can_rx_call(rt_device_t dev,rt_size_t size){
    rt_sem_release(can_sem);
    return RT_EOK;
}

int can_config(){
    can_dev = rt_device_find(CAN_NAME);
    can_sem = rt_sem_create(CAN_NAME,0,RT_IPC_FLAG_FIFO);
    rt_device_open(can_dev,RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(can_dev,can_rx_call);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(can_config);
