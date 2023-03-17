//
// Created by 25861 on 2023/3/18.
//
#include "rtthread.h"
#include "controller/controller.h"

int app_start(){
    lcd_init_handler();
    return RT_EOK;
}

INIT_APP_EXPORT(app_start);