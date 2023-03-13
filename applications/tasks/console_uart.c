//
// Created by 25861 on 2023/3/14.
//

#include "rtdef.h"
#include "rtdevice.h"

static void console_uart_init(void){
    rt_device_t console_device = NULL;
    struct serial_configure console_device_config;

    console_device = rt_device_find(RT_CONSOLE_DEVICE_NAME);
    if (console_device){
        console_device_config.baud_rate = BAUD_RATE_115200;
        console_device_config.data_bits = DATA_BITS_8;
        console_device_config.stop_bits = STOP_BITS_1;
        console_device_config.parity = PARITY_NONE;
        console_device_config.bit_order = BIT_ORDER_LSB;
        rt_device_control(console_device,RT_DEVICE_CTRL_CONFIG,&console_device_config);
    }


}

int console_init(){
    console_uart_init();
    return RT_EOK;
}

INIT_COMPONENT_EXPORT(console_init);