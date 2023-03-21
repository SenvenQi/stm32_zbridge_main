//
// Created by 25861 on 2023/3/18.
//
#include "rtthread.h"
#include "controller/controller.h"

int app_start(){
    app_init();
    return RT_EOK;
}

INIT_APP_EXPORT(app_start);