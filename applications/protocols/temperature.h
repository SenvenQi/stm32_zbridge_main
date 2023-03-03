//
// Created by 天琪王 on 2023/3/3.
//

#ifndef RTTHREAD_TEMPERATURE_H
#define RTTHREAD_TEMPERATURE_H

#include "rtdef.h"

struct temperature{
    rt_uint8_t head[2];
    rt_uint16_t length;
    rt_uint8_t* data;
};

void filter(rt_uint8_t *buffer);

#endif //RTTHREAD_TEMPERATURE_H
