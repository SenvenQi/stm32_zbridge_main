//
// Created by 天琪王 on 2023/3/8.
//

#include "device.h"

rt_device_t uart1_dev;
rt_mq_t uart1_mq;
rt_sem_t uart_protocol_sem;
static rt_err_t uart1_rx_call(rt_device_t dev,rt_size_t size) {
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(uart1_mq, &msg, sizeof(msg));
    if (result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full！\n");
    }
    return result;
}

int uart1_config(){
    uart1_dev = rt_device_find(UART1_NAME);
    uart1_mq = rt_mq_create(UART1_NAME,                /* 存放消息的缓冲区 */
                               sizeof(struct rx_msg),    /* 一条消息的最大长度 */
                               256,RT_IPC_FLAG_FIFO);
    uart_protocol_sem = rt_sem_create(UART1_NAME,0,RT_IPC_FLAG_FIFO);
    rt_device_open(uart1_dev,RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    rt_device_set_rx_indicate(uart1_dev,uart1_rx_call);
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(uart1_config);
