//
// Created by 25861 on 2023/3/16.
//

#ifndef RTTHREAD_CONTROLLER_H
#define RTTHREAD_CONTROLLER_H

#include "service/service.h"

void uart1_handler(void *buffer,size_t size);
void lcd_init_handler();
void buzzer_di_handler();
#endif //RTTHREAD_CONTROLLER_H
