//
// Created by 25861 on 2023/3/5.
//


#ifndef RTTHREAD_CAN_MSG_H
#define RTTHREAD_CAN_MSG_H

#include "rtthread.h"
#include "rtdevice.h"

struct rt_can_msg create_can_msg(rt_uint32_t id, const rt_uint8_t data[8]);

#endif //RTTHREAD_CAN_MSG_H
