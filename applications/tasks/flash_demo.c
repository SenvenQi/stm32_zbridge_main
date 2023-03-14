//
// Created by 天琪王 on 2023/3/14.
//

#include "fal.h"

int read_data(void){
    fal_init();
    struct fal_partition *falPartition= fal_partition_find("easyflash");
    uint8_t buf[8];
    rt_uint32_t size = fal_partition_read(falPartition,0,buf,8);
    for (int i = 0; i < size; ++i) {
        rt_kprintf("%d",buf[i]);
    }
    return RT_EOK;
}


INIT_APP_EXPORT(read_data);