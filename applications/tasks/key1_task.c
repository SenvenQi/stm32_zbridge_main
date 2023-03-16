//
// Created by 天琪王 on 2023/3/16.
//
#include "rtdevice.h"
#include "rtthread.h"
#include "drv_gpio.h"
#include "pwm.h"

void key1_handler(void *parameter){
    if (ENABLE_LCD_PWM)
        ENABLE_LCD_PWM = DISABLE;
    else
        ENABLE_LCD_PWM = ENABLE;
    toggle_pwm();
}

void key1_config(){
    rt_base_t key1= GET_PIN(C,13);
    rt_pin_mode(key1,PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(key1,PIN_IRQ_MODE_FALLING,key1_handler,RT_NULL);
    rt_pin_irq_enable(key1,PIN_IRQ_ENABLE);
}



int key1_start(){
    key1_config();
    return RT_EOK;
}

INIT_APP_EXPORT(key1_start);