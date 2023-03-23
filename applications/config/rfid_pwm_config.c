//
// Created by 天琪王 on 2023/3/23.
//
#include "device.h"

int rfid_pwm_config(){
    pwm_dev_rfid = (struct rt_device_pwm *)rt_device_find(RFID_PWM_DEV_NAME);
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev_lcd,PWM_DEV_CHANNEL ,period,pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev_lcd, PWM_DEV_CHANNEL);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rfid_pwm_config);