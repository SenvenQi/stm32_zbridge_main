//
// Created by 天琪王 on 2023/3/20.
//
#include "service.h"

void config_filter(){
#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[1] =
    {
            RT_CAN_FILTER_ITEM_INIT(can_id, 0, 0, 1, 0x01, RT_NULL, RT_NULL),
    };
    struct rt_can_filter_config cfg = {1, 1, items}; /* 一共有 5 个过滤表 */
    /* 设置硬件过滤表 */
    rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
//    rt_device_control(dev, RT_CAN_CMD_SET_BAUD, (void *)CAN500kBaud);
//    rt_device_control(dev, RT_CAN_CMD_SET_MODE, (void *) RT_CAN_MODE_NORMAL);
#endif
}
