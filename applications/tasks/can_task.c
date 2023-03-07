//
// Created by 25861 on 2023/3/5.
//
#include "can_task.h"
#include "protocols/can_msg.h"


void can_handler(){
    rt_device_t dev =  rt_device_find("can1");
    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
    struct rt_can_msg msg = create_can_msg(0x78,msg1);
    rt_device_write(dev,0,&msg,sizeof msg);
}

void can_callback(void *parameter){
    rt_device_t dev = rt_device_find("can1");
    struct rt_can_msg rxmsg = {0};

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[5] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x100~0x1ff，hdr 为 - 1，设置默认过滤表 */
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x300~0x3ff，hdr 为 - 1 */
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7ff, RT_NULL, RT_NULL), /* std,match ID:0x211，hdr 为 - 1 */
        RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),                  /* std,match ID:0x486，hdr 为 - 1 */
        {0x78, 0, 0, 0, 0x7ff, -1,}                                       /* std,match ID:0x555，hdr 为 7，指定设置 7 号过滤表 */
    };
    struct rt_can_filter_config cfg = {5, 1, items}; /* 一共有 5 个过滤表 */
    /* 设置硬件过滤表 */
    rt_device_control(dev, RT_CAN_CMD_SET_FILTER, &cfg);
#endif

    while (1)
    {
        rxmsg.hdr = -1;
        rt_sem_take(parameter, RT_WAITING_FOREVER);
        rt_device_read(dev, 0, &rxmsg, sizeof(rxmsg));
        can_handler();
    }
}

int can_start(){
    device_task_create("can1", can_callback, RT_Object_Class_Semaphore, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    return RT_EOK;
}

INIT_APP_EXPORT(can_start);
