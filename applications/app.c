//
// Created by 天琪王 on 2023/3/2.
//

#include <rtthread.h>
#include <rtdevice.h>
#include "infrastructure/zb_device.h"
#include "protocols/temperature.h"

static device_task_t lan;
static device_task_t can;



void can_callback(void *parameter){
    int i;
    struct rt_can_msg rxmsg = {0};

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[5] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x100~0x1ff，hdr 为 - 1，设置默认过滤表 */
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x300~0x3ff，hdr 为 - 1 */
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7ff, RT_NULL, RT_NULL), /* std,match ID:0x211，hdr 为 - 1 */
        RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),                  /* std,match ID:0x486，hdr 为 - 1 */
        {0x555, 0, 0, 0, 0x7ff, 7,}                                       /* std,match ID:0x555，hdr 为 7，指定设置 7 号过滤表 */
    };
    struct rt_can_filter_config cfg = {5, 1, items}; /* 一共有 5 个过滤表 */
    /* 设置硬件过滤表 */
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
#endif

    while (1)
    {
        /* hdr 值为 - 1，表示直接从 uselist 链表读取数据 */
        rxmsg.hdr = -1;
        /* 阻塞等待接收信号量 */
        rt_sem_take(parameter, RT_WAITING_FOREVER);
        /* 从 CAN 读取一帧数据 */
        rt_device_read(lan->dev, 0, &rxmsg, sizeof(rxmsg));
        /* 打印数据 ID 及内容 */
        rt_kprintf("ID:%x", rxmsg.id);
        for (i = 0; i < 8; i++)
        {
            rt_kprintf("%2x", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

static void  lan_callback(void *parameter){
    char msg1[8];
    struct rt_can_msg msg;
    rt_err_t result;
    static char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
    while (1){
        result = rt_mq_recv(parameter,msg1,8,RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            rt_device_read(lan->dev, 0, rx_buffer, 8);
            rt_kprintf(rx_buffer);
            msg.id = 0x78;              /* ID 为 0x78 */
            msg.ide = RT_CAN_STDID;     /* 标准格式 */
            msg.rtr = RT_CAN_DTR;       /* 数据帧 */
            msg.len = 8;                /* 数据长度为 8 */
            /* 待发送的 8 字节数据 */
            msg.data[0] = 0x00;
            msg.data[1] = 0x11;
            msg.data[2] = 0x22;
            msg.data[3] = 0x33;
            msg.data[4] = 0x44;
            msg.data[5] = 0x55;
            msg.data[6] = 0x66;
            msg.data[7] = 0x77;
            rt_device_write(can->dev,0,&msg,8);
        }
    }
}

void config(){
    lan = device_task_create("uart1",lan_callback,RT_Object_Class_MessageQueue,RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    can = device_task_create("can1",can_callback,RT_Object_Class_Semaphore,RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
}

int start(){
    config();
    return RT_EOK;
}

INIT_APP_EXPORT(start);


