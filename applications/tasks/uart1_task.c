//
// Created by 25861 on 2023/3/5.
//
#include "uart1_task.h"

void handler(){
    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    rt_device_t dev =  rt_device_find("can1");
    struct rt_can_msg msg = create_can_msg(0x78,msg1);
    rt_device_write(dev,0,&msg,8);
}

void  lan_callback(void *parameter){
    rt_uint8_t msg1[8];
    rt_device_t dev = rt_device_find("uart1");
    rt_err_t result;
    static char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
    while (1){
        result = rt_mq_recv(parameter,msg1,8,RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            rt_device_read(dev, 0, rx_buffer, 8);
            handler();
        }
    }
}


