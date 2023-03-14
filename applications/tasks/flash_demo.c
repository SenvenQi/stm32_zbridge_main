//
// Created by 天琪王 on 2023/3/14.
//

#include "fal.h"

int read_data(void){

    const struct fal_partition *falPartition= fal_partition_find("easyflash");
    uint8_t buf[128];
//    rt_uint32_t erase_size = fal_partition_erase_all(falPartition);
    rt_uint32_t size = fal_partition_read(falPartition,128,buf,128);
//    fal_partition_write(falPartition,203,buf,8);
    for (int i = 0; i < size; ++i) {
        rt_kprintf("%2x\t\t",buf[i]);
    }
    rt_kprintf("success");
    return RT_EOK;
}


INIT_APP_EXPORT(read_data);