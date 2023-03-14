//
// Created by 25861 on 2023/3/15.
//
#include "font_flash.h"

static const struct fal_partition* falPartition;

void write_font(rt_off_t offset,uint8_t *buffer,size_t data_size){
    rt_size_t size = fal_partition_write(falPartition,offset,buffer,data_size);
    if (size == 0){
        rt_kprintf("upload success!");
    }
}
int start_flash(){
    fal_init();
    falPartition = fal_partition_find("easyflash");
    return RT_EOK;
}

INIT_APP_EXPORT(start_flash);