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
    rt_uint32_t e;
    static unsigned char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
    while (1){
        result = rt_event_recv(uart1_event,1,RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_FOREVER,&e);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            rt_uint16_t size = rt_device_read(uart1_dev, 0, rx_buffer, rxMsg.size);
            rt_uint8_t data[size];
            for (int i = 0; i < size; ++i) {
                data[i] = rx_buffer[i];
            }
            uart1_handler(data,size);
        }
    }
}

THREAD_INIT_START(lan_callback,RT_NULL,1024,10,10)