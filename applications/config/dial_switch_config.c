//
// Created by 25861 on 2023/3/18.
//

#include "device.h"
struct rt_semaphore sw_sem;

#define RT_CONFIG_PIN_ENABLE_IRQ(num) \
        rt_pin_mode(SW##num,PIN_MODE_INPUT_PULLUP); \
        rt_pin_attach_irq(SW##num, PIN_IRQ_MODE_FALLING, dial_switch_handler, (void *) num); \
        rt_pin_irq_enable(SW##num,PIN_IRQ_ENABLE);

void dial_switch_handler(void *parameter){
    rt_kprintf("dail switch down");
}

int dial_switch_config(){
    sw_sem = *rt_sem_create(DAIL_SWITCH_NAME,0,RT_IPC_FLAG_FIFO);
    RT_CONFIG_PIN_ENABLE_IRQ(1)
    RT_CONFIG_PIN_ENABLE_IRQ(2)
    RT_CONFIG_PIN_ENABLE_IRQ(3)
    RT_CONFIG_PIN_ENABLE_IRQ(4)
    RT_CONFIG_PIN_ENABLE_IRQ(5)
    RT_CONFIG_PIN_ENABLE_IRQ(6)
    RT_CONFIG_PIN_ENABLE_IRQ(7)
    RT_CONFIG_PIN_ENABLE_IRQ(8)
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(dial_switch_config);