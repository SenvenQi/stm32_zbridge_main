//
// Created by 25861 on 2023/3/16.
//
#include "device.h"
#include "drv_gpio.h"
struct rt_semaphore key1_sem;

void key1_handler(void *parameter){
    rt_kprintf("key1 down");
    rt_sem_release(&key1_sem);
}

int key1_config(){
    key1_sem = *rt_sem_create(CAN_NAME,0,RT_IPC_FLAG_FIFO);
    rt_pin_mode(KEY1,PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY1,PIN_IRQ_MODE_FALLING,key1_handler,RT_NULL);
    rt_pin_irq_enable(KEY1,PIN_IRQ_ENABLE);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(key1_config);