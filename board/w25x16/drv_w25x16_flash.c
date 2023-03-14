//
// Created by 25861 on 2023/3/13.
//

#include "drv_spi.h"
#include "spi_flash_sfud.h"


static int rt_hw_spi_flash_init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    int result = rt_hw_spi_device_attach("spi1","spi10",GPIOA,GPIO_PIN_2);
    rt_kprintf("result:%d",result);
    if(rt_sfud_flash_probe("w25x16","spi10") == RT_NULL){
        rt_kprintf("failed w25x16 init!!!!!!1");
        return -RT_ERROR;
    }
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);