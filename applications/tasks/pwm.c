//
// Created by 天琪王 on 2023/3/13.
//
#include "task.h"
#include "config/device.h"
#include "core/thread_core.h"

static struct rt_device_pwm *pwm_dev_lcd;

static int rt_hw_lcd_pwr_config(void){
    pwm_dev_lcd = (struct rt_device_pwm *)rt_device_find("pwm2");
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev_lcd,PWM_DEV_CHANNEL ,period,pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev_lcd, PWM_DEV_CHANNEL);
    return RT_EOK;
}

void lcd_pwm_start(void *parameter){
    rt_hw_lcd_pwr_config();
    while (1)
    {
        rt_thread_mdelay(10);
            if (dir)
            {
                pulse += 10000;      /* 从0值开始每次增加5000ns */
            }
            else
            {
                pulse -= 10000;      /* 从最大值开始每次减少5000ns */
            }
            if (pulse >= period)
            {
                dir = 0;
            }
            if (0 == pulse)
            {
                dir = 1;
            }

            /* 设置PWM周期和脉冲宽度 */
            rt_pwm_set(pwm_dev_lcd, PWM_DEV_CHANNEL, period, pulse);
    }
}

THREAD_INIT_START(lcd_pwm_start,RT_NULL,1024,25,10)