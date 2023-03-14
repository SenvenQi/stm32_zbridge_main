//
// Created by 天琪王 on 2023/3/9.
//
#include "drv_lcd.h"



void lcd_task(){
    LCD_ShowChar64x32(30,0,"1",RED,0x0000,64,1);
    LCD_ShowChar64x32(62,0,"1",RED,0x0000,64,1);
    LCD_ShowChinese64x64(94,0,"号",0xFFFF,0x0000,64,1);
    LCD_ShowChinese64x64(158,0,"在",GREEN,0x0000,64,1);
    LCD_ShowChinese64x64(222,0,"位",0xFFFF,0x0000,64,1);
    LCD_ShowChinese64x64(0,80,"苏",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(64,80,"E",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(96,80,"-",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(128,80,"1",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(160,80,"1",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(192,80,"1",0xffff,0x0000,64,1);
    LCD_ShowChar64x32(224,80,"1",0xffff,0x0000,64,1);
    LCD_ShowChinese64x64(256,80,"警",0xffff,0x0000,64,1);
}


int lcd_start(){
    rt_thread_t led_thread = rt_thread_create("lcd",lcd_task,RT_NULL,1024,25,10);
    rt_thread_startup(led_thread);
    return RT_EOK;
}

INIT_APP_EXPORT(lcd_start);