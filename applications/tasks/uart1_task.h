//
// Created by 25861 on 2023/3/5.
//

#ifndef RTTHREAD_UART1_TASK_H
#define RTTHREAD_UART1_TASK_H

#include "rtdef.h"
#include "rtthread.h"
#include "protocols/can_msg.h"
#include "infrastructure/zb_device.h"

#define LAN_TASK_INIT  device_task_create("uart1",lan_callback,RT_Object_Class_MessageQueue,RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
void  lan_callback(void *parameter);

#endif //RTTHREAD_UART1_TASK_H
