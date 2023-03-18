//
// Created by 25861 on 2023/3/5.
//
#include "task.h"
#include "controller/controller.h"


void lan_handler(){
    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    struct rt_can_msg msg = create_can_msg(0x01,msg1);
    rt_device_write(uart1_dev,0,&msg1,sizeof msg1);
    rt_size_t size = rt_device_write(can_dev,0,&msg,sizeof msg);
    if (size== 0){
        rt_kprintf("failed!!!");
    }
}
void lan_callback(void *parameter){
    struct rx_msg rxMsg;
    rt_err_t result;
    while (1){
        rt_mutex_take(uart1_mutex, RT_WAITING_FOREVER);
        result = rt_mq_recv(uart1_mq, &rxMsg, sizeof(rxMsg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            rt_uint16_t size = rt_device_read(uart1_dev, receive_size, rx_buffer, rxMsg.size);
            receive_size += size;
            rt_mutex_release(uart1_mutex);
        }
    }
}

THREAD_INIT_START(lan_callback,RT_NULL,1024,10,10)