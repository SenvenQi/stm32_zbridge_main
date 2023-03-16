//
// Created by 25861 on 2023/3/13.
//

#ifndef RTTHREAD_FAL_CFG_H
#define RTTHREAD_FAL_CFG_H

#include <rtconfig.h>
#include <board.h>

#define NOR_FLASH_DEV_NAME             "w25x16"
#define FLASH_DEV_NAME                 "easyflash"

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32_onchip_flash;
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash,                                           \
    &nor_flash0,                                                     \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD,           "app",     "onchip_flash",   0,  256*1024,    0}, \
    {FAL_PART_MAGIC_WORD,  FLASH_DEV_NAME, NOR_FLASH_DEV_NAME,   0,  2*1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif //RTTHREAD_FAL_CFG_H
