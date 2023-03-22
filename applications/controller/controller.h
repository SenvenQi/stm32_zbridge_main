//
// Created by 25861 on 2023/3/16.
//

#ifndef RTTHREAD_CONTROLLER_H
#define RTTHREAD_CONTROLLER_H

#include "service/service.h"
#include "protocols/protocol.h"

void flash_write_fonts(void *buffer,rt_uint64_t addr,size_t size);
void uart1_data_handler();
void can_data_handler();
void buzzer_di_handler();
void lcd_show_data();
void config_can_id();
void app_init();
#endif //RTTHREAD_CONTROLLER_H
