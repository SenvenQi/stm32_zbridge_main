//
// Created by 25861 on 2023/3/15.
//

#ifndef RTTHREAD_FONT_FLASH_H
#define RTTHREAD_FONT_FLASH_H

#include "rtthread.h"
#include "fal.h"

void write_font(rt_off_t offset,uint8_t *buffer,size_t size);

#endif //RTTHREAD_FONT_FLASH_H
