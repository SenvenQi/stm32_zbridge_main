//
// Created by 天琪王 on 2023/3/21.
//
#include "protocol.h"

struct rt_can_msg rx_msg = {0};
void can_protocol_handler(void (*handler)(struct rx_can_data* rxCanData)){
    struct rx_can_data* data = (struct rx_can_data *)rx_msg.data;
    handler(data);
}