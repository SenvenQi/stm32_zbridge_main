//
// Created by 25861 on 2023/3/21.
//
#include "service.h"


const struct fal_partition* falPartition;
void flash_write(void *buffer,rt_uint64_t addr,size_t size){
    if (falPartition == RT_NULL){
        falPartition = fal_partition_find(FLASH_DEV_NAME);
    }
    fal_partition_erase(falPartition,0,size);
    fal_partition_write(falPartition,addr,buffer,size);
}
