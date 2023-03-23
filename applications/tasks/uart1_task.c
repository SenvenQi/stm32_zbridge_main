//
// Created by 25861 on 2023/3/5.
//
#include "task.h"
#include "controller/controller.h"

void lan_callback(void *parameter){
    struct rx_msg rxMsg;
    rt_err_t result;
    static unsigned char rx_received_buffer[BSP_UART1_RX_BUFSIZE * 2 + 1];
    struct rt_serial_rx_fifo *fifo = ((struct rt_serial_device*)uart1_dev)->serial_rx;
//    static rt_uint64_t addr = 7 * 1024 * 1024;
    while (1){
        result = rt_mq_recv(uart1_mq, &rxMsg, sizeof(rxMsg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
//            size_t size = rt_device_read(uart1_dev, 0, rx_received_buffer, 256);
//            flash_write_fonts(rx_received_buffer,addr,size);
//            addr += size;
            /* 从串口读取数据 */
            if (rt_ringbuffer_get_size(&fifo->rb) >= 4){
                size_t size = rt_device_read(uart1_dev, 0, rx_received_buffer, 256);
                for (int i = 0; i < size; ++i) {
                    rx_buffer[receive_size + i] = rx_received_buffer[i];
                }
                receive_size += size;
                rt_sem_release(uart_protocol_sem);
            }
        }
    }
}

THREAD_INIT_START(lan_callback,RT_NULL,1024,10,10)