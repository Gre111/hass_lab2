/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>

#include <aos/hal/gpio.h>
#include <hal_iomux_haas1000.h>
//led声名
gpio_dev_t greenled = {0};
gpio_dev_t redled = {0};
gpio_dev_t blueled = {0};
void led_init(void)
{
    greenled.port = HAL_GPIO_PIN_P4_3;
    greenled.config = OUTPUT_PUSH_PULL;
    greenled.priv = NULL;
    redled.port = HAL_GPIO_PIN_P4_4;
    redled.config = OUTPUT_PUSH_PULL;
    redled.priv = NULL;
    blueled.port = HAL_GPIO_PIN_P4_2;
    blueled.config = OUTPUT_PUSH_PULL;
    blueled.priv = NULL;
    hal_gpio_init(&greenled);
    hal_gpio_init(&blueled);
    hal_gpio_init(&redled);
}

//key4声名
gpio_dev_t key1 = {0};
gpio_dev_t key3 = {0};
gpio_dev_t key4 = {0};
uint32_t val = 1;
void key134_init(void)
{
    key4.port = HAL_IOMUX_PIN_P3_2;
    key4.config = INPUT_PULL_UP;
    key4.priv = NULL;
    
    key3.port = HAL_IOMUX_PIN_P2_5;
    key3.config = INPUT_PULL_UP;
    key3.priv = NULL;
    
    key1.port = HAL_IOMUX_PIN_P2_7;
    key1.config = INPUT_PULL_UP;
    key1.priv = NULL;

    hal_gpio_init(&key1);
    hal_gpio_init(&key3);
    hal_gpio_init(&key4);
}

void key4_check()
{
    hal_gpio_input_get(&key4, &val);
    if(val == 0)
    {
        aos_msleep(10);//消抖
        hal_gpio_input_get(&key4, &val);
        if(val == 0)
        {
            hal_gpio_output_high(&greenled);//低电平点亮LED
            //上升沿触发
            while(val == 0)
                hal_gpio_input_get(&key4, &val);
            hal_gpio_output_low(&greenled);//上升沿熄灭LED
        }
    }
}

void key3_check()
{
    hal_gpio_input_get(&key3, &val);
    if(val == 0)
    {
        aos_msleep(10);//消抖
        hal_gpio_input_get(&key3, &val);
        if(val == 0)
        {
            hal_gpio_output_high(&blueled);//低电平点亮LED
            //上升沿触发
            while(val == 0)
                hal_gpio_input_get(&key3, &val);
            hal_gpio_output_low(&blueled);//上升沿熄灭LED
        }
    }
}
void key1_check()
{
    hal_gpio_input_get(&key1, &val);
    if(val == 0)
    {
        aos_msleep(10);//消抖
        hal_gpio_input_get(&key1, &val);
        if(val == 0)
        {
            hal_gpio_output_high(&redled);//低电平点亮LED
            //上升沿触发
            while(val == 0)
                hal_gpio_input_get(&key1, &val);
            hal_gpio_output_low(&redled);//上升沿熄灭LED
        }
    }
    
}
int application_start(int argc, char *argv[])
{
   key134_init();
   led_init();
   hal_gpio_output_low(&greenled);
   hal_gpio_output_low(&blueled);
   hal_gpio_output_low(&redled);
   while(1)
   {
        key1_check();
        key3_check();
        key4_check();
   }
}
