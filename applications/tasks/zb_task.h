//
// Created by 25861 on 2023/3/16.
//

#ifndef RTTHREAD_ZB_TASK_H
#define RTTHREAD_ZB_TASK_H

extern void (*led_task)(void* parameter);
extern void (*lcd_task)(void* parameter);
extern void (*key1_task)(void* parameter);
extern void (*can_task)(void* parameter);
extern void (*uart1_task)(void* parameter);

#endif //RTTHREAD_ZB_TASK_H
