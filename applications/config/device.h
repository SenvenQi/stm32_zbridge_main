//
// Created by 天琪王 on 2023/3/8.
//

#ifndef RTTHREAD_DEVICE_H
#define RTTHREAD_DEVICE_H
#include "rtthread.h"
#include "rtdevice.h"
#include "drv_gpio.h"
#include "fal.h"



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
extern rt_mq_t uart1_mq;
extern rt_mutex_t uart1_mutex;
extern rt_sem_t uart_protocol_sem;
/* 蜂鸣器  */

#define BUZZER GET_PIN(B,9)
extern rt_bool_t buzzer_enable;
/* 按钮1  */

#define KEY1 GET_PIN(C,13)
extern struct rt_semaphore key1_sem;

/* LED灯 */

#define LED GET_PIN(A,8)
#define LED1 GET_PIN(C,14)

/* lcd pwm设备 */

#define LCD_NAME "lcd"
#define LCD_PWM_DEV_NAME "pwm2"
#define PWM_DEV_CHANNEL 3
extern rt_sem_t lcd_sem;
extern struct rt_device_pwm *pwm_dev_lcd;
extern rt_uint32_t period, /* 周期为0.5ms，单位为纳秒ns */
pulse,  /* PWM脉冲宽度值的增减方向 */
dir;  /* PWM脉冲宽度值，单位为纳秒ns */
/* flash设备 */
#define FALSH_DEV fal_partition_find(FLASH_DEV_NAME)

/* 拨码开关 */
#define DAIL_SWITCH_NAME "dail_switch"
#define SW1 GET_PIN(C,10)
#define SW2 GET_PIN(C,11)
#define SW3 GET_PIN(C,12)
#define SW4 GET_PIN(D,2)
#define SW5 GET_PIN(B,3)
#define SW6 GET_PIN(B,4)
#define SW7 GET_PIN(B,5)
#define SW8 GET_PIN(B,6)
extern rt_sem_t sw_sem;
#endif //RTTHREAD_DEVICE_H
