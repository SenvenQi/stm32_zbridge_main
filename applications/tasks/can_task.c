//
// Created by 25861 on 2023/3/5.
//
#include "task.h"

void can_handler(){
//    rt_uint8_t msg1[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
//    struct rt_can_msg msg = create_can_msg(0x78,msg1);
//    rt_device_write(can_dev,0,&msg,sizeof msg);
}

void can_callback(void *parameter){
    struct rt_can_msg rxmsg = {0};
    while (1)
    {
        rxmsg.hdr = -1;
        rt_sem_take(&can_sem, RT_WAITING_FOREVER);
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        can_handler();
    }
}

THREAD_INIT_START(can_callback,RT_NULL,1024,10,10);