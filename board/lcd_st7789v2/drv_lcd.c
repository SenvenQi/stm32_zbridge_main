//
// Created by 天琪王 on 2023/3/9.
//
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-08-14    flybreak           the first version
 * 2018-09-18    balanceTWK         add sleep mode function
 * 2018-09-27    ZYLX               optimized display speed
 */

#include "rt-thread/components/drivers/include/rtdevice.h"
#include "drv_spi.h"
#include "drv_lcd.h"

#define DBG_SECTION_NAME    "LCD"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG

#include "rt-thread/include/rtdbg.h"
#include "fal.h"

#define LCD_DC_PIN            GET_PIN(B, 0)
#define LCD_RES_PIN           GET_PIN(B, 1)

#define LCD_CLEAR_SEND_NUMBER 5760

rt_uint16_t BACK_COLOR = WHITE, FORE_COLOR = BLACK;

static struct rt_spi_device *spi_dev_lcd;


static int rt_hw_lcd_config(void) {
    spi_dev_lcd = (struct rt_spi_device *) rt_device_find("spi20");

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
//        spi_dev_lcd->bus->owner = spi_dev_lcd;
        cfg.max_hz = 42 * 1000 * 1000; /* 42M,SPI max 42MHz,lcd 4-wire spi */

        rt_spi_configure(spi_dev_lcd, &cfg);
    }

    return RT_EOK;
}

static rt_err_t lcd_write_cmd(const rt_uint8_t cmd) {
    rt_size_t len;

    rt_pin_write(LCD_DC_PIN, PIN_LOW);

    len = rt_spi_send(spi_dev_lcd, &cmd, 1);

    if (len != 1) {
        LOG_I("lcd_write_cmd error. %d", len);
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

static rt_err_t lcd_write_data(const rt_uint8_t data) {
    rt_size_t len;

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);

    len = rt_spi_send(spi_dev_lcd, &data, 1);

    if (len != 1) {
        LOG_I("lcd_write_data error. %d", len);
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

static rt_err_t lcd_write_half_word(const rt_uint16_t da) {
    rt_size_t len;
    char data[2] = {0};

    data[0] = da >> 8;
    data[1] = da;

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    len = rt_spi_send(spi_dev_lcd, data, 2);
    if (len != 2) {
        LOG_I("lcd_write_half_word error. %d", len);
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

static void lcd_gpio_init(void) {
    rt_hw_lcd_config();

    rt_pin_mode(LCD_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_RES_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(LCD_RES_PIN, PIN_LOW);
    //wait at least 100ms for reset
    rt_thread_delay(RT_TICK_PER_SECOND / 10);
    rt_pin_write(LCD_RES_PIN, PIN_HIGH);
}

static int rt_hw_lcd_init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    rt_hw_spi_device_attach("spi2", "spi20", GPIOC, GPIO_PIN_5);
    lcd_gpio_init();
//    rt_thread_delay(RT_TICK_PER_SECOND);
//    rt_pin_write(LCD_RES_PIN, PIN_LOW);
//    //wait at least 100ms for reset
//    rt_thread_delay(RT_TICK_PER_SECOND);
//    rt_pin_write(LCD_RES_PIN, PIN_HIGH);
//    rt_thread_delay(800);
    lcd_write_cmd(0x11);

#ifdef LCD_147
    /* Memory Data Access Control */
    lcd_write_cmd(0x36);
    lcd_write_data(0x60);
    /* RGB 5-6-5-bit  */
    lcd_write_cmd(0x3A);
    lcd_write_data(0x65);
    /* Porch Setting */
    lcd_write_cmd(0xB2);
    lcd_write_data(0x0C);
    lcd_write_data(0x0C);
    lcd_write_data(0x00);
    lcd_write_data(0x33);
    lcd_write_data(0x33);
    /*  Gate Control */
    lcd_write_cmd(0xB7);
    lcd_write_data(0x35);
    /* VCOM Setting */
    lcd_write_cmd(0xBB);
    lcd_write_data(0x19);
    /* LCM Control */
    lcd_write_cmd(0xC0);
    lcd_write_data(0x2C);
    /* VDV and VRH Command Enable */
    lcd_write_cmd(0xC2);
    lcd_write_data(0x01);
    /* VRH Set */
    lcd_write_cmd(0xC3);
    lcd_write_data(0x12);
    /* VDV Set */
    lcd_write_cmd(0xC4);
    lcd_write_data(0x20);
    /* Frame Rate Control in Normal Mode */
    lcd_write_cmd(0xC6);
    lcd_write_data(0x0F);
    /* Power Control 1 */
    lcd_write_cmd(0xD0);
    lcd_write_data(0xA4);
    lcd_write_data(0xA1);
    /* Positive Voltage Gamma Control */
    lcd_write_cmd(0xE0);
    lcd_write_data(0xD0);
    lcd_write_data(0x04);
    lcd_write_data(0x0D);
    lcd_write_data(0x11);
    lcd_write_data(0x13);
    lcd_write_data(0x2B);
    lcd_write_data(0x3F);
    lcd_write_data(0x54);
    lcd_write_data(0x4C);
    lcd_write_data(0x18);
    lcd_write_data(0x0D);
    lcd_write_data(0x0B);
    lcd_write_data(0x1F);
    lcd_write_data(0x23);
    /* Negative Voltage Gamma Control */
    lcd_write_cmd(0xE1);
    lcd_write_data(0xD0);
    lcd_write_data(0x04);
    lcd_write_data(0x0C);
    lcd_write_data(0x11);
    lcd_write_data(0x13);
    lcd_write_data(0x2C);
    lcd_write_data(0x3F);
    lcd_write_data(0x44);
    lcd_write_data(0x51);
    lcd_write_data(0x2F);
    lcd_write_data(0x1F);
    lcd_write_data(0x1F);
    lcd_write_data(0x20);
    lcd_write_data(0x23);
    /* Display Inversion On */
    lcd_write_cmd(0x21);
    /* Sleep Out */
    lcd_write_cmd(0x11);
#endif
#ifdef LCD_161
    //--------------------------------------Display Setting------------------------------------------//
    lcd_write_cmd(0x36);
    lcd_write_data(0x60);
    lcd_write_cmd(0x3a);
    lcd_write_data(0x55);
    lcd_write_cmd(0x2a);
    lcd_write_data(0x00);
    lcd_write_data(0x1e);
    lcd_write_data(0x00);
    lcd_write_data(0xd1);
    lcd_write_cmd(0x2b);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x01);
    lcd_write_data(0x3f);
//--------------------------------ST7789V Frame rate setting----------------------------------//
    lcd_write_cmd(0xb2);
    lcd_write_data(0x0c);
    lcd_write_data(0x0c);
    lcd_write_data(0x00);
    lcd_write_data(0x33);
    lcd_write_data(0x33);
    lcd_write_cmd(0xb7);
    lcd_write_data(0x35);
//---------------------------------ST7789V Power setting--------------------------------------//
    lcd_write_cmd(0xbb);
    lcd_write_data(0x21);
    lcd_write_cmd(0xc0);
    lcd_write_data(0x2c);
    lcd_write_cmd(0xc2);
    lcd_write_data(0x01);
    lcd_write_cmd(0xc3);
    lcd_write_data(0x13);
    lcd_write_cmd(0xc4);
    lcd_write_data(0x20);
    lcd_write_cmd(0xc6);
    lcd_write_data(0x0f);
    lcd_write_cmd(0xd0);
    lcd_write_data(0xa4);
    lcd_write_data(0xa1);
//--------------------------------ST7789V gamma setting--------------------------------------//
    lcd_write_cmd(0xe0);
    lcd_write_data(0xd0);
    lcd_write_data(0x02);
    lcd_write_data(0x09);
    lcd_write_data(0x0d);
    lcd_write_data(0x0f);
    lcd_write_data(0x19);
    lcd_write_data(0x38);
    lcd_write_data(0x44);
    lcd_write_data(0x49);
    lcd_write_data(0x3b);
    lcd_write_data(0x18);
    lcd_write_data(0x16);
    lcd_write_data(0x19);
    lcd_write_data(0x1c);
    lcd_write_cmd(0xe1);
    lcd_write_data(0xd0);
    lcd_write_data(0x03);
    lcd_write_data(0x0a);
    lcd_write_data(0x0e);
    lcd_write_data(0x0e);
    lcd_write_data(0x0a);
    lcd_write_data(0x37);
    lcd_write_data(0x44);
    lcd_write_data(0x49);
    lcd_write_data(0x3b);
    lcd_write_data(0x17);
    lcd_write_data(0x16);
    lcd_write_data(0x19);
    lcd_write_data(0x1c);
    lcd_write_cmd(0x29);
#endif
    /* wait for power stability */
    rt_thread_mdelay(100);

    lcd_clear(WHITE);

    /* display on */
//    rt_pin_write(LCD_PWR_PIN, PIN_HIGH);
    lcd_write_cmd(0x29);

    return RT_EOK;

}

INIT_COMPONENT_EXPORT(rt_hw_lcd_init);

/**
 * Set background color and foreground color
 *
 * @param   back    background color
 * @param   fore    fore color
 *
 * @return  void
 */
void lcd_set_color(rt_uint16_t back, rt_uint16_t fore) {
    BACK_COLOR = back;
    FORE_COLOR = fore;
}


/**
 * Set drawing area
 *
 * @param   x1      start of x position
 * @param   y1      start of y position
 * @param   x2      end of x position
 * @param   y2      end of y position
 *
 * @return  void
 */
void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2) {
#ifdef LCD_147
    lcd_write_cmd(0x2a);
    lcd_write_data(x1 >> 8);
    lcd_write_data(x1);
    lcd_write_data(x2 >> 8);
    lcd_write_data(x2);

    lcd_write_cmd(0x2b);
    lcd_write_data((y1 + 34) >> 8);
    lcd_write_data(y1 + 34);
    lcd_write_data((y2 + 34) >> 8);
    lcd_write_data(y2 + 34);
#endif

#ifdef LCD_161
    lcd_write_cmd(0x2a);
    lcd_write_data(x1 >> 8);
    lcd_write_data(x1);
    lcd_write_data(x2 >> 8);
    lcd_write_data(x2);

    lcd_write_cmd(0x2b);
    lcd_write_data((y1+30) >> 8);
    lcd_write_data(y1+30);
    lcd_write_data((y2+30) >> 8);
    lcd_write_data(y2+30);
#endif


    lcd_write_cmd(0x2C);
}

/**
 * clear the lcd.
 *
 * @param   color       Fill color
 *
 * @return  void
 */
void lcd_clear(rt_uint16_t color) {
    rt_uint16_t i, j;
    rt_uint8_t data[2] = {0};
    rt_uint8_t *buf = RT_NULL;

    data[0] = color >> 8;
    data[1] = color;
    lcd_address_set(0, 0, LCD_W - 1, LCD_H - 1);

    /* 5760 = 240*240/20 */
    buf = rt_malloc(LCD_CLEAR_SEND_NUMBER);
    if (buf) {
        /* 2880 = 5760/2 color is 16 bit */
        for (j = 0; j < LCD_CLEAR_SEND_NUMBER / 2; j++) {
            buf[j * 2] = data[0];
            buf[j * 2 + 1] = data[1];
        }

        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        for (i = 0; i < 20; i++) {
            rt_spi_send(spi_dev_lcd, buf, LCD_CLEAR_SEND_NUMBER);
        }
        rt_free(buf);
    } else {
        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        for (i = 0; i < LCD_W; i++) {
            for (j = 0; j < LCD_H; j++) {
                rt_spi_send(spi_dev_lcd, data, 2);
            }
        }
    }
}

/**
 * display a point on the lcd.
 *11
 * @param   x   x position
 * @param   y   y position
 *
 * @return  void
 */
void lcd_draw_point(rt_uint16_t x, rt_uint16_t y) {
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(FORE_COLOR);
}

/**
 * display a point on the lcd using the given colour.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   color   color of point
 *
 * @return  void
 */
void lcd_draw_point_color(rt_uint16_t x, rt_uint16_t y, rt_uint16_t color) {
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(color);
}

/**
 * full color on the lcd.
 *
 * @param   x_start     start of x position
 * @param   y_start     start of y position
 * @param   x_end       end of x position
 * @param   y_end       end of y position
 * @param   color       Fill color
 *
 * @return  void
 */
void lcd_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint16_t color) {
    rt_uint16_t i = 0, j = 0;
    rt_uint32_t size = 0, size_remain = 0;
    rt_uint8_t *fill_buf = RT_NULL;

    size = (x_end - x_start) * (y_end - y_start) * 2;

    if (size > LCD_CLEAR_SEND_NUMBER) {
        /* the number of remaining to be filled */
        size_remain = size - LCD_CLEAR_SEND_NUMBER;
        size = LCD_CLEAR_SEND_NUMBER;
    }

    lcd_address_set(x_start, y_start, x_end, y_end);

    fill_buf = (rt_uint8_t *) rt_malloc(size);
    if (fill_buf) {
        /* fast fill */
        while (1) {
            for (i = 0; i < size / 2; i++) {
                fill_buf[2 * i] = color >> 8;
                fill_buf[2 * i + 1] = color;
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, fill_buf, size);

            /* Fill completed */
            if (size_remain == 0)
                break;

            /* calculate the number of fill next time */
            if (size_remain > LCD_CLEAR_SEND_NUMBER) {
                size_remain = size_remain - LCD_CLEAR_SEND_NUMBER;
            } else {
                size = size_remain;
                size_remain = 0;
            }
        }
        rt_free(fill_buf);
    } else {
        for (i = y_start; i <= y_end; i++) {
            for (j = x_start; j <= x_end; j++)lcd_write_half_word(color);
        }
    }
}

/**
 * display a line on the lcd.
 *
 * @param   x1      x1 position
 * @param   y1      y1 position
 * @param   x2      x2 position
 * @param   y2      y2 position
 *
 * @return  void
 */
void lcd_draw_line(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2) {
    rt_uint16_t t;
    rt_uint32_t i = 0;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;

    if (y1 == y2) {
        /* fast draw transverse line */
        lcd_address_set(x1, y1, x2, y2);

        rt_uint8_t line_buf[480] = {0};

        for (i = 0; i < x2 - x1; i++) {
            line_buf[2 * i] = FORE_COLOR >> 8;
            line_buf[2 * i + 1] = FORE_COLOR;
        }

        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        rt_spi_send(spi_dev_lcd, line_buf, (x2 - x1) * 2);

        return;
    }

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    row = x1;
    col = y1;
    if (delta_x > 0)incx = 1;
    else if (delta_x == 0)incx = 0;
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;
    else {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x;
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++) {
        lcd_draw_point(row, col);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * display a rectangle on the lcd.
 *
 * @param   x1      x1 position
 * @param   y1      y1 position
 * @param   x2      x2 position
 * @param   y2      y2 position
 *
 * @return  void
 */
void lcd_draw_rectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2) {
    lcd_draw_line(x1, y1, x2, y1);
    lcd_draw_line(x1, y1, x1, y2);
    lcd_draw_line(x1, y2, x2, y2);
    lcd_draw_line(x2, y1, x2, y2);
}

/**
 * display a circle on the lcd.
 *
 * @param   x       x position of Center
 * @param   y       y position of Center
 * @param   r       radius
 *
 * @return  void
 */
void lcd_draw_circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint8_t r) {
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);
    while (a <= b) {
        lcd_draw_point(x0 - b, y0 - a);
        lcd_draw_point(x0 + b, y0 - a);
        lcd_draw_point(x0 - a, y0 + b);
        lcd_draw_point(x0 - b, y0 - a);
        lcd_draw_point(x0 - a, y0 - b);
        lcd_draw_point(x0 + b, y0 + a);
        lcd_draw_point(x0 + a, y0 - b);
        lcd_draw_point(x0 + a, y0 + b);
        lcd_draw_point(x0 - b, y0 + a);
        a++;
        //Bresenham
        if (di < 0)di += 4 * a + 6;
        else {
            di += 10 + 4 * (a - b);
            b--;
        }
        lcd_draw_point(x0 + a, y0 + b);
    }
}

void lcd_show_font(rt_uint16_t x, rt_uint16_t y, const char *data, rt_uint32_t size) {
    rt_uint8_t temp;
    rt_uint8_t num = 0;
    rt_uint32_t pos, t;
    rt_uint16_t colortemp = FORE_COLOR;
    rt_uint8_t *font_buf = RT_NULL;
    rt_uint64_t addr;
#ifdef GB2312
    addr = 128 + (((*data) - 0xa1) * 94  +  ((*(data +1))-0xa1)) * 128;
#endif
#ifdef GBK
    if ((*(data + 1)) < 0x7F)
        addr = 256 + (((*data) - 0x81) * 190 + (*(data + 1)) - 0X40) * size * size / 8;
    if ((*(data + 1)) > 0x80)
        addr = 256 + (((*data) - 0x81) * 190 + (*(data + 1)) - 0X41) * size * size / 8;
#endif
    rt_uint8_t *buf = (rt_uint8_t *) rt_malloc(size * size / 8);
    const struct fal_partition *falPartition = fal_partition_find(FLASH_DEV_NAME);
    fal_partition_read(falPartition, addr, buf, size * size / 8);

    if (x > LCD_W - size / 2 || y > LCD_H - size)return;
    lcd_address_set(x, y, x + size - 1, y + size - 1);
    font_buf = (rt_uint8_t *) rt_malloc(size * size * 2);
    if (!font_buf) {
        /* fast show char */
        for (pos = 0; pos < size * size / 8; pos++) {
            temp = buf[pos];
            for (t = 0; t < 8; t++) {
                if (temp & 0x80)colortemp = FORE_COLOR;
                else colortemp = BACK_COLOR;
                lcd_write_half_word(colortemp);
                temp <<= 1;
            }
        }
    } else {
        for (pos = 0; pos < size * size / 8; pos++) {
            temp = buf[pos];
            for (t = 0; t < 8; t++) {
                if (temp & 0x80)colortemp = FORE_COLOR;
                else colortemp = BACK_COLOR;
                font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                font_buf[2 * (8 * pos + t) + 1] = colortemp;
                temp <<= 1;
            }
        }
        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        rt_spi_send(spi_dev_lcd, font_buf, size * size * 2);
        rt_free(buf);
        rt_free(font_buf);
    }
}

static void lcd_show_char(rt_uint16_t x, rt_uint16_t y, rt_uint8_t data, rt_uint32_t size) {
    rt_uint8_t temp;
    rt_uint8_t num = 0;;
    rt_uint32_t pos, t;
    rt_uint16_t colortemp = FORE_COLOR;
    rt_uint8_t *font_buf = RT_NULL;

    if (x > LCD_W - size / 2 || y > LCD_H - size)return;

    data = data - ' ';
#ifdef ASC2_1608
    if (size == 16) {
        lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);//(x,y,x+8-1,y+16-1)

        font_buf = (rt_uint8_t *) rt_malloc(size * size);
        if (!font_buf) {
            /* fast show char */
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = asc2_1608[(rt_uint16_t) data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    lcd_write_half_word(colortemp);
                    temp <<= 1;
                }
            }
        } else {
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = asc2_1608[(rt_uint16_t) data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                    font_buf[2 * (8 * pos + t) + 1] = colortemp;
                    temp <<= 1;
                }
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, font_buf, size * size);
            rt_free(font_buf);
        }
    } else
#endif

#ifdef ASC2_2412
    if (size == 24) {
        lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

        font_buf = (rt_uint8_t *) rt_malloc(size * size);
        if (!font_buf) {
            /* fast show char */
            for (pos = 0; pos < (size * 16) / 8; pos++) {
                temp = asc2_2412[(rt_uint16_t) data * (size * 16) / 8 + pos];
                if (pos % 2 == 0) {
                    num = 8;
                } else {
                    num = 4;
                }

                for (t = 0; t < num; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    lcd_write_half_word(colortemp);
                    temp <<= 1;
                }
            }
        } else {
            for (pos = 0; pos < (size * 16) / 8; pos++) {
                temp = asc2_2412[(rt_uint16_t) data * (size * 16) / 8 + pos];
                if (pos % 2 == 0) {
                    num = 8;
                } else {
                    num = 4;
                }

                for (t = 0; t < num; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    if (num == 8) {
                        font_buf[2 * (12 * (pos / 2) + t)] = colortemp >> 8;
                        font_buf[2 * (12 * (pos / 2) + t) + 1] = colortemp;
                    } else {
                        font_buf[2 * (8 + 12 * (pos / 2) + t)] = colortemp >> 8;
                        font_buf[2 * (8 + 12 * (pos / 2) + t) + 1] = colortemp;
                    }
                    temp <<= 1;
                }
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, font_buf, size * size);
            rt_free(font_buf);
        }
    } else
#endif

#ifdef ASC2_3216
    if (size == 32) {
        lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

        font_buf = (rt_uint8_t *) rt_malloc(size * size);
        if (!font_buf) {
            /* fast show char */
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = asc2_3216[(rt_uint16_t) data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    lcd_write_half_word(colortemp);
                    temp <<= 1;
                }
            }
        } else {
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = asc2_3216[(rt_uint16_t) data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                    font_buf[2 * (8 * pos + t) + 1] = colortemp;
                    temp <<= 1;
                }
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, font_buf, size * size);
            rt_free(font_buf);
        }
    } else
#endif
    if (size == 48) {
        lcd_address_set(x, y, x + size/2 - 1, y + size - 1);
        font_buf = (rt_uint8_t *) rt_malloc(size * size);
        rt_uint64_t addr = 7 * 1024 * 1024 + (rt_uint64_t) data * size * (size / 2) / 8;
        rt_uint8_t *buf = (rt_uint8_t *) rt_malloc(size * size / 8);
        const struct fal_partition *falPartition = fal_partition_find(FLASH_DEV_NAME);
        fal_partition_read(falPartition, addr, buf, size * size / 2  / 8);
        if (!font_buf) {
            /* fast show char */
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = buf[pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    lcd_write_half_word(colortemp);
                    temp <<= 1;
                }
            }
        } else {
            for (pos = 0; pos < size * (size / 2) / 8; pos++) {
                temp = buf[pos];
                for (t = 0; t < 8; t++) {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                    font_buf[2 * (8 * pos + t) + 1] = colortemp;
                    temp <<= 1;
                }
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, font_buf, size * size);
            rt_free(buf);
            rt_free(font_buf);
        }
    } else
    {
        LOG_E("There is no any define ASC2_1208 && ASC2_2412 && ASC2_2416 && ASC2_3216 !");
    }
}

/**
 * display the number on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   num     number
 * @param   len     length of number
 * @param   size    size of font
 *
 * @return  void
 */
void lcd_show_num(rt_uint16_t x, rt_uint16_t y, rt_uint32_t num, rt_uint8_t len, rt_uint32_t size) {
    lcd_show_string(x, y, size, "%d", num);
}

/**
 * display the string on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   size    size of font
 * @param   p       the string to be display
 *
 * @return   0: display success
 *          -1: size of font is not support
 */
rt_err_t lcd_show_string(rt_uint16_t x, rt_uint16_t y, rt_uint32_t size, const char *fmt, ...) {
#define LCD_STRING_BUF_LEN 128

    va_list args;
    rt_uint8_t buf[LCD_STRING_BUF_LEN] = {0};
    rt_uint8_t *p = RT_NULL;

    if (size != 16 && size != 24 && size != 32 && size != 48) {
        LOG_E("font size(%d) is not support!", size);
        return -RT_ERROR;
    }

    va_start(args, fmt);
    rt_vsnprintf((char *) buf, 100, (const char *) fmt, args);
    va_end(args);

    p = buf;
    while (*p != '\0') {
        if (*p & 0x80) {
            if (x > (LCD_W - size)) {
                x = 0;
                y += size;
            }
        } else {
            if (x > (LCD_W - size / 2)) {
                x = 0;
                y += size;
            }
        }
        if (y > LCD_H - size) {
            y = x = 0;
            lcd_clear(RED);
        }
        if (*p & 0x80) {
            char *c = {p, p + 1};
            lcd_show_font(x, y, c, size);
            p++;
            x += size / 2;
        } else {
            lcd_show_char(x, y, *p, size);
        }
        x += size / 2;
        p++;
    }

    return RT_EOK;
}

/**
 * display the image on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   length  length of image
 * @param   wide    wide of image
 * @param   p       image
 *
 * @return   0: display success
 *          -1: the image is too large
 */
rt_err_t lcd_show_image(rt_uint16_t x, rt_uint16_t y, rt_uint16_t length, rt_uint16_t wide, const rt_uint8_t *p) {
    RT_ASSERT(p);

    if (x + length > LCD_W || y + wide > LCD_H) {
        return -RT_ERROR;
    }

    lcd_address_set(x, y, x + length - 1, y + wide - 1);

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    rt_spi_send(spi_dev_lcd, p, length * wide * 2);

    return RT_EOK;
}

void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor) {
    rt_uint32_t size = 0;

    size = (x_end - x_start + 1) * (y_end - y_start + 1) * 2/*16bit*/;
    lcd_address_set(x_start, y_start, x_end, y_end);
    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    rt_spi_send(spi_dev_lcd, pcolor, size);
}

#ifdef PKG_USING_QRCODE
QRCode qrcode;

static rt_uint8_t get_enlargement_factor(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size)
{
    rt_uint8_t enlargement_factor = 1 ;

    if (x + size * 8 <= LCD_W && y + size * 8 <= LCD_H)
    {
        enlargement_factor = 8;
    }
    else if (x + size * 4 <= LCD_W &&y + size * 4 <= LCD_H)
    {
        enlargement_factor = 4;
    }
    else if (x + size * 2 <= LCD_W && y + size * 2 <= LCD_H)
    {
        enlargement_factor = 2;
    }

    return enlargement_factor;
}

static void show_qrcode_by_point(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size, rt_uint8_t enlargement_factor)
{
    rt_uint32_t width = 0, high = 0;
    for (high = 0; high < size; high++)
    {
        for (width = 0; width < size; width++)
        {
            if (qrcode_getModule(&qrcode, width, high))
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        lcd_draw_point(x + enlargement_factor * width + offset_x, y + enlargement_factor * high + offset_y);
                    }
                }
            }
        }
    }
}

static void show_qrcode_by_line(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size, rt_uint8_t enlargement_factor,rt_uint8_t *qrcode_buf)
{
    rt_uint32_t width = 0, high = 0;
    for (high = 0; high < qrcode.size; high++)
    {
        for (width = 0; width < qrcode.size; width++)
        {
            if (qrcode_getModule(&qrcode, width, high))
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        /* save the information of modules */
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor)] = FORE_COLOR >> 8;
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor) + 1] = FORE_COLOR;
                    }
                }
            }
            else
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        /* save the information of blank */
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor)] = BACK_COLOR >> 8;
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor) + 1] = BACK_COLOR;
                    }
                }
            }
        }
        /* display a line of qrcode */
        lcd_show_image(x, y + high * enlargement_factor, qrcode.size * enlargement_factor, enlargement_factor, qrcode_buf);
    }
}

/**
 * display the qrcode on the lcd.
 * size = (4 * version +17) * enlargement
 *
 * @param   x           x position
 * @param   y           y position
 * @param   version     version of qrcode
 * @param   ecc         level of error correction
 * @param   data        string
 * @param   enlargement enlargement_factor
 *
 * @return   0: display success
 *          -1: generate qrcode failed
*           -5: memory low
 */
rt_err_t lcd_show_qrcode(rt_uint16_t x, rt_uint16_t y, rt_uint8_t version, rt_uint8_t ecc, const char *data, rt_uint8_t enlargement)
{
    RT_ASSERT(data);

    rt_int8_t result = 0;
    rt_uint8_t enlargement_factor = 1;
    rt_uint8_t *qrcode_buf = RT_NULL;

    if (x + version * 4 + 17 > LCD_W || y + version * 4 + 17 > LCD_H)
    {
        LOG_E("The qrcode is too big!");
        return -RT_ERROR;
    }

    rt_uint8_t *qrcodeBytes = (rt_uint8_t *)rt_calloc(1, qrcode_getBufferSize(version));
    if (qrcodeBytes == RT_NULL)
    {
        LOG_E("no memory for qrcode!");
        return -RT_ENOMEM;
    }

    /* generate qrcode */
    result = qrcode_initText(&qrcode, qrcodeBytes, version, ecc, data);
    if (result >= 0)
    {
        /* set enlargement factor */
        if(enlargement == 0)
        {
            enlargement_factor = get_enlargement_factor(x, y, qrcode.size);
        }
        else
        {
            enlargement_factor = enlargement;
        }

        /* malloc memory for quick display of qrcode */
        qrcode_buf = rt_malloc(qrcode.size * 2 * enlargement_factor * enlargement_factor);
        if (qrcode_buf == RT_NULL)
        {
            /* clear lcd */
            lcd_fill(x, y, x + qrcode.size, y + qrcode.size, BACK_COLOR);

            /* draw point to display qrcode */
            show_qrcode_by_point(x, y, qrcode.size, enlargement_factor);
        }
        else
        {
            /* quick display of qrcode */
            show_qrcode_by_line(x, y, qrcode.size, enlargement_factor,qrcode_buf);
        }
        result = RT_EOK;
    }
    else
    {
        LOG_E("QRCODE(%s) generate falied(%d)\n", data, result);
        result = -RT_ENOMEM;
        goto __exit;
    }

__exit:
    if (qrcodeBytes)
    {
        rt_free(qrcodeBytes);
    }

    if (qrcode_buf)
    {
        rt_free(qrcode_buf);
    }

    return result;
}
#endif