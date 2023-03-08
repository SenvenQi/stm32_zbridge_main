//
// Created by 天琪王 on 2023/3/8.
//

#include "device.h"

rt_device_t device_config(char* name,rt_uint16_t oflag){
    rt_device_t dev = rt_device_find(name);
    rt_device_open(dev,oflag);
    return dev;
}

static rt_err_t can_rx_call(rt_device_t dev,rt_size_t size){
    rt_sem_release(&can_sem);
    return RT_EOK;
}

static rt_err_t uart1_rx_call(rt_device_t dev,rt_size_t size) {
    struct rx_msg r_msg;
    rt_err_t result;
    r_msg.dev = dev;
    r_msg.size = size;

    result = rt_mq_send(&uart1_mq, &r_msg, sizeof(r_msg));
    if (result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full！\n");
    }
    return result;
}

int device_init(){
    can_dev = rt_device_find(CAN_NAME);
    rt_sem_init(&can_sem,CAN_NAME,0,RT_IPC_FLAG_FIFO);
    rt_device_open(can_dev,RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);

    uart1_dev = rt_device_find(UART1_NAME);
    rt_mq_init(&uart1_mq,UART1_NAME,msg_pool,sizeof(struct rx_msg),sizeof msg_pool,RT_IPC_FLAG_FIFO);
    rt_device_open(uart1_dev,RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);


    rt_device_set_rx_indicate(can_dev,can_rx_call);
    rt_device_set_rx_indicate(uart1_dev,uart1_rx_call);
    return RT_EOK;
}


INIT_APP_EXPORT(device_init);