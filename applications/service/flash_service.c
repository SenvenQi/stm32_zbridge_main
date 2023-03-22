//
// Created by 25861 on 2023/3/21.
//
#include "service.h"


const struct fal_partition* falPartition;
void flash_write(void *buffer,rt_uint64_t addr,size_t size){
    if (falPartition == RT_NULL){
        falPartition = fal_partition_find(FLASH_DEV_NAME);
    }
    fal_partition_write(falPartition,addr,buffer,size);
}

void flash_read_config() {
    if (falPartition == RT_NULL) {
        falPartition = fal_partition_find(FLASH_DEV_NAME);
    }
    rt_uint8_t data[2];
    fal_partition_read(falPartition, 0, data, 2);
    if (data[0] == 0xAA && data[1] == 0xBB)
        return;
    else{
        fal_partition_erase_all(falPartition);
        data[0] = 0xAA; data[1] = 0xBB;
        fal_partition_write(falPartition,0,data,2);
    }
}