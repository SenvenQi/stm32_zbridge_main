//
// Created by 25861 on 2023/3/18.
//

#include "service.h"

void di(){
    rt_pin_write(BUZZER,PIN_HIGH);
    rt_thread_delay(1000);
    rt_pin_write(BUZZER,PIN_LOW);
}