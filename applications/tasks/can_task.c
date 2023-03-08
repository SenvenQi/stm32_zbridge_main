//
// Created by 25861 on 2023/3/5.
//
#include "protocols/can_msg.h"
#include "config/device.h"

void can_handler(){
    rt_device_t dev =  rt_device_find("can1");
    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    struct rt_can_msg msg = create_can_msg(0x78,msg1);
    rt_device_write(dev,0,&msg,sizeof msg);
}

void can_callback(void *parameter){
    rt_device_t dev = rt_device_find("can1");
    struct rt_can_msg rxmsg = {0};

#ifdef RT_CAN_USING_HDR1
    struct rt_can_filter_item items[1] =
    {
            RT_CAN_FILTER_ITEM_INIT(0x01, 0, 0, 1, 0x01, RT_NULL, RT_NULL),                                      /* std,match ID:0x555，hdr 为 7，指定设置 7 号过滤表 */
    };
    struct rt_can_filter_config cfg = {1, 1, items}; /* 一共有 5 个过滤表 */
    /* 设置硬件过滤表 */
    rt_device_control(dev, RT_CAN_CMD_SET_FILTER, &cfg);
    rt_device_control(dev, RT_CAN_CMD_SET_BAUD, (void *)CAN500kBaud);
    rt_device_control(dev, RT_CAN_CMD_SET_MODE, (void *) RT_CAN_MODE_NORMAL);
#endif

    while (1)
    {
        rxmsg.hdr = -1;
        rt_sem_take(&can_sem, RT_WAITING_FOREVER);
        rt_device_read(dev, 0, &rxmsg, sizeof(rxmsg));
        can_handler();
    }
}

int can_start(){
    rt_thread_t thread = rt_thread_create("can_task",can_callback,RT_NULL,1024,25,10);
    rt_thread_startup(thread);
    return RT_EOK;
}

INIT_APP_EXPORT(can_start);
