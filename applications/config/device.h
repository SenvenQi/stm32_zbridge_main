//
// Created by 天琪王 on 2023/3/8.
//

#ifndef RTTHREAD_DEVICE_H
#define RTTHREAD_DEVICE_H

#include "rtdevice.h"
#include "drv_gpio.h"



/* can总线  */

struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};

#define CAN_NAME "can1"
extern rt_device_t can_dev;
extern struct rt_semaphore can_sem;

/* 串口1  */

#define UART1_NAME "uart1"
extern rt_device_t uart1_dev;
extern struct rt_messagequeue uart1_mq;

/* 按钮1  */

#define KEY1 GET_PIN(C,13)
extern struct rt_semaphore key1_sem;

/* LED灯 */

#define LED GET_PIN(A,8)
#define LED1 GET_PIN(D,2)

/* lcd pwm设备 */

#define LCD_PWM_DEV_NAME "pwm2"
#define PWM_DEV_CHANNEL 3
extern rt_uint32_t period, /* 周期为0.5ms，单位为纳秒ns */
pulse,  /* PWM脉冲宽度值的增减方向 */
dir;  /* PWM脉冲宽度值，单位为纳秒ns */

#endif //RTTHREAD_DEVICE_H
