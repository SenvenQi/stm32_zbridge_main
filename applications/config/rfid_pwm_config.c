//
// Created by 天琪王 on 2023/3/23.
//
#include "device.h"
rt_uint32_t rfid_pwm_period = 8000, /* 周期为0.5ms，单位为纳秒ns */
rfid_pwm_pulse = 4000,  /* PWM脉冲宽度值的增减方向 */
rfid_pwm_dir = 0;  /* PWM脉冲宽度值，单位为纳秒ns */
struct rt_device_pwm *pwm_dev_rfid;

int rfid_pwm_config(){
    pwm_dev_rfid = (struct rt_device_pwm *)rt_device_find(RFID_PWM_DEV_NAME);
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev_rfid,PWM_DEV_RFID_CHANNEL ,rfid_pwm_period,rfid_pwm_pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev_rfid, PWM_DEV_RFID_CHANNEL);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rfid_pwm_config);