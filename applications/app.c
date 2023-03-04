//
// Created by 天琪王 on 2023/3/2.
//

#include <rtthread.h>
#include <rtdevice.h>
#include "infrastructure/zb_device.h"
#include "protocols/temperature.h"
#include "protocols/can_msg.h"

static device_task_t lan;
static device_task_t can;



void can_callback(void *parameter){
    struct rt_can_msg rxmsg = {0};

#ifdef RT_CAN_USING_HDR1
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
    rt_device_control(can, RT_CAN_CMD_SET_FILTER, &cfg);
#endif

    while (1)
    {
        rxmsg.hdr = -1;
        rt_sem_take(parameter, RT_WAITING_FOREVER);
        rt_device_read(can->dev, 0, &rxmsg, sizeof(rxmsg));
    }
}

static void  lan_callback(void *parameter){
    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    rt_err_t result;
    static char rx_buffer[BSP_UART1_RX_BUFSIZE + 1];
    while (1){
        result = rt_mq_recv(parameter,msg1,8,RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据 */
            rt_device_read(lan->dev, 0, rx_buffer, 8);
            struct rt_can_msg msg = create_can_msg(0x78,msg1);
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


