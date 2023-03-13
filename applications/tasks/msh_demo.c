//
// Created by 25861 on 2023/3/13.
//

#include "rtthread.h"

void my_hello(){
    rt_kprintf("hello msh");
}

MSH_CMD_EXPORT(my_hello,msh cmd test);