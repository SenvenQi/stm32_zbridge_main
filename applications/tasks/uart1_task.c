//
// Created by 25861 on 2023/3/5.
//
#include "rtdevice.h"
#include "protocols/can_msg.h"
#include "config/device.h"
#include "zb_task.h"

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
    static char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
    static rt_uint16_t size = 0;
    static rt_off_t offset = 0;
    while (1){
        result = rt_mq_recv(&uart1_mq,&rxMsg,sizeof rxMsg,RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            size = rt_device_read(uart1_dev, 0, rx_buffer, rxMsg.size);
//            for (rt_uint16_t i = 0; i < size; i++)
//            {
//                rt_kprintf("%2x",rx_buffer[i]);
//                rx_buffer[i] = '\0';
//            }

            rt_kprintf("%d",size);
//             write_font(offset,rx_buffer,size);
//             offset += size;
//            if (size >= 8){
//                lan_handler();
//            }
        }
    }
}
void (*uart1_task)(void *parameter) = lan_callback;
