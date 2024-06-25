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

#include <time.h>
#include <aos/hal/gpio.h>
#include <hal_iomux_haas1000.h>
gpio_dev_t greenled = {0};
gpio_dev_t redled = {0};
gpio_dev_t blueled = {0};
int application_start(int argc, char *argv[])
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
    srand((unsigned)time(NULL));
    while(1)
    {
        
        int a = rand()%3+0;
        switch (a)
        {
        case 0:
            for(int i=0;i<2;i++)
        {
            hal_gpio_output_high(&greenled);
            aos_msleep(100);
            hal_gpio_output_low(&greenled);
            aos_msleep(100);
        }
            break;
        case 1:
            for(int i=0;i<2;i++)
        {
            hal_gpio_output_high(&redled);
            aos_msleep(100);
            hal_gpio_output_low(&redled);
            aos_msleep(100);
        }
            break;
        case 2:
        for(int i=0;i<2;i++)
        {
            hal_gpio_output_high(&blueled);
            aos_msleep(100);
            hal_gpio_output_low(&blueled);
            aos_msleep(100);
        }
        default:
            break;
        }
    }
}
