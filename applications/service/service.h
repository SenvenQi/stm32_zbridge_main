//
// Created by 25861 on 2023/3/18.
//

#ifndef RTTHREAD_SERVICE_H
#define RTTHREAD_SERVICE_H

#include "drv_lcd.h"
#include "config/device.h"
/* 蜂鸣器 */
void di();

/* lcd */

/* 亮度调节 */
void brightness(rt_uint32_t brightness_size);
/* 修改lcd屏文字 */
void lcd_write(char *str);

#endif //RTTHREAD_SERVICE_H
