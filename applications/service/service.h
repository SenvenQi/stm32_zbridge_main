//
// Created by 25861 on 2023/3/18.
//

#ifndef RTTHREAD_SERVICE_H
#define RTTHREAD_SERVICE_H

#include "drv_lcd.h"
#include "config/device.h"
#include "protocols/protocol.h"
/* 蜂鸣器 */
void di();

/* lcd */

/* 亮度调节 */
void brightness(rt_uint32_t brightness_size);
/* 修改lcd屏文字 */
void lcd_write(char *str);
/* lcd 死循环闪屏 */
void splash_screen();
void lcd_clear_color(rt_uint16_t back_color,rt_uint16_t fore_color);

#endif //RTTHREAD_SERVICE_H
