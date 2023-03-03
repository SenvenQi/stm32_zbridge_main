//
// Created by 天琪王 on 2023/3/3.
//

#include "temperature.h"
#include "rtdef.h"

void filter(rt_uint8_t *buffer){
    struct temperature *temperature;
    temperature = buffer;
    if(sizeof &buffer <= 7)
        return;
    else if(buffer[0] == 0xAA && buffer[1] == 0xBB){

    }
}