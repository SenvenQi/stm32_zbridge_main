//
// Created by 25861 on 2023/3/5.
//

#include "protocol.h"

struct rt_can_msg create_can_msg(rt_uint32_t id,const rt_uint8_t data[8]){
    struct rt_can_msg msg;
    msg.id = id;              /* ID 为 0x78 */
    msg.ide = RT_CAN_STDID;     /* 标准格式 */
    msg.rtr = RT_CAN_DTR;       /* 数据帧 */
    msg.len = 8;                /* 数据长度为 8 */
    /* 待发送的 8 字节数据 */
    for(int i = 0; i < 8; i++)
        msg.data[i] = data[i];
    return msg;
}