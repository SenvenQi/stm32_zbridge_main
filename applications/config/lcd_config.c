//
// Created by 25861 on 2023/3/16.
//
#include "device.h"
rt_uint32_t period = 8000, /* 周期为0.5ms，单位为纳秒ns */
pulse = 4000,  /* PWM脉冲宽度值的增减方向 */
dir = 0;  /* PWM脉冲宽度值，单位为纳秒ns */
rt_sem_t lcd_sem;
struct rt_device_pwm *pwm_dev_lcd;
int lcd_config(void){
    lcd_sem  = rt_sem_create(LCD_NAME,0,RT_IPC_FLAG_FIFO);
    pwm_dev_lcd = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev_lcd,PWM_DEV_CHANNEL ,period,pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev_lcd, PWM_DEV_CHANNEL);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(lcd_config);