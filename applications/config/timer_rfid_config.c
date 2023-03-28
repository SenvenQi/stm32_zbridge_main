//
// Created by 天琪王 on 2023/3/27.
//
#include "device.h"
#include "protocols/protocol.h"

rt_device_t rfid_hw_dev;
rt_uint32_t freq = 1000000;



void rfid_handler(void *parameter) {
    if (N == 256) {
        rt_sem_release(rfid_sem);
        N = 0;
        TIM4->CNT = 0;
        return;
    }
    TT_Buffer[N] = TIM4->CNT; //数组记录计时器计时时间
    TT_voltage[N] = rt_pin_read(RFID_INPUT);//数组保存此时IO电平
    TIM4->CNT = 0;
    N++;
}

int timer_rfid_config(){
    rt_hwtimerval_t timeout_s;
    timeout_s.sec = 0xFFF;
    timeout_s.usec = 0xFFF;

    rfid_sem  = rt_sem_create(LCD_NAME,0,RT_IPC_FLAG_FIFO);
    rt_pin_mode(RFID_INPUT,PIN_MODE_INPUT);
    rt_pin_attach_irq(RFID_INPUT, PIN_IRQ_MODE_RISING_FALLING,rfid_handler,RT_NULL);
    rt_pin_irq_enable(RFID_INPUT,ENABLE);

    rfid_hw_dev = rt_device_find(RFID_TIMER_DEV_NAME);
    rt_device_control(rfid_hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    rt_hwtimer_mode_t mode = HWTIMER_MODE_PERIOD;
    rt_err_t ret = rt_device_control(rfid_hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("timer4 mode set error!!!\r\n");
    }
    rt_device_open(rfid_hw_dev, RT_DEVICE_OFLAG_RDWR);
    rt_err_t err = rt_device_write(rfid_hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s);
    if (err != RT_EOK)
    {
        rt_kprintf("timer4 start error!!!\r\n");
    }

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(timer_rfid_config);