//
// Created by 天琪王 on 2023/3/2.
//

#include "protocols/temperature.h"
#include "tasks/can_task.h"
#include "tasks/uart1_task.h"


int start(){
    CAN_TASK_INIT
    LAN_TASK_INIT
    return RT_EOK;
}

INIT_APP_EXPORT(start);


