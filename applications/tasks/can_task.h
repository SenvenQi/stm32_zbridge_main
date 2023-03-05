//
// Created by 25861 on 2023/3/5.
//

#ifndef RTTHREAD_CAN_TASK_H
#define RTTHREAD_CAN_TASK_H

#include "infrastructure/zb_device.h"
#include "rtdevice.h"
#define CAN_TASK_INIT device_task_create("can1",can_callback,RT_Object_Class_Semaphore,RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
void can_callback(void *parameter);

#endif //RTTHREAD_CAN_TASK_H
