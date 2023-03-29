//
// Created by 天琪王 on 2023/3/29.
//
#include "device.h"

rt_device_t wgd_dev;

int watchdog_config(){
    wgd_dev = rt_device_find(WATCHDOG_DEV_NAME);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(watchdog_config);