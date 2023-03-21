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

extern char lcd_num[256];
/* 亮度调节 */
void brightness(rt_uint32_t brightness_size);
/* 修改lcd屏文字 */
void lcd_write(char *str);
/* lcd 死循环闪屏 */
void splash_screen();
void lcd_clear_color(rt_uint16_t back_color,rt_uint16_t fore_color);

/*拨码开关*/
extern rt_uint8_t can_id;
void config_id();

/* can总线 */
void config_filter();
void send_can_msg(struct rt_can_msg message);
#endif //RTTHREAD_SERVICE_H
