//
// Created by 天琪王 on 2023/3/9.
//
#include "drv_lcd.h"
#include "fal.h"


void lcd_task(){
//    LCD_ShowChar64x32(30,0,"1",RED,0x0000,64,1);
//    LCD_ShowChar64x32(62,0,"1",RED,0x0000,64,1);
//    LCD_ShowChinese64x64(94,0,"号",0xFFFF,0x0000,64,1);
//    LCD_ShowChinese64x64(158,0,"在",GREEN,0x0000,64,1);
//    LCD_ShowChinese64x64(222,0,"位",0xFFFF,0x0000,64,1);
//    LCD_ShowChinese64x64(0,80,"苏",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(64,80,"E",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(96,80,"-",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(128,80,"1",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(160,80,"1",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(192,80,"1",0xffff,0x0000,64,1);
//    LCD_ShowChar64x32(224,80,"1",0xffff,0x0000,64,1);
//    LCD_ShowChinese64x64(256,80,"警",0xffff,0x0000,64,1);
    lcd_set_color(WHITE,BLACK);
    lcd_clear(WHITE);
    const struct fal_partition *falPartition= fal_partition_find("easyflash");
    uint8_t buf[32];
//    rt_uint32_t erase_size = fal_partition_erase_all(falPartition);
    fal_partition_read(falPartition,32,buf,32);
    lcd_show_string(64,32,16,"hello");
    char *name = "你";
    rt_kprintf("0x%x \t 0x%x",*name,*(name+1));
    lcd_show_font(32,32,"陈",16,buf);
}


int lcd_start(){
    rt_thread_t led_thread = rt_thread_create("lcd",lcd_task,RT_NULL,1024,25,10);
    rt_thread_startup(led_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(lcd_start);