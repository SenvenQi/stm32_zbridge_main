//
// Created by 25861 on 2023/3/18.
//
#include "task.h"


THREAD_WHILE_INIT_START(twinkle,RT_NULL,1024,25,10)
THREAD_WHILE_INIT_START(read_rfid_handle,RT_NULL,1024,9,10)
THREAD_SEM_INIT_START(buzzer_di_handler,buzzer_sem,RT_NULL,1024,25,10)
THREAD_SEM_INIT_START(can_data_handler,can_sem,RT_NULL,1024,10,10)
THREAD_SEM_INIT_START(config_can_id,sw_sem,RT_NULL,1024,20,10)
THREAD_SEM_INIT_START(lcd_show_data,lcd_sem,RT_NULL,1024,20,10)
THREAD_SEM_INIT_START(uart1_data_handler,uart_protocol_sem,RT_NULL,1024,11,10)



