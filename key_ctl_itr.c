
#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>

#include <aos/hal/gpio.h>
#include <hal_iomux_haas1000.h>
/*
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
*/
//key4声名
gpio_dev_t key4 = {0};


//中断处理函数
void key4_irq()
{
    printf("key4 is pressed\n");
}

void key4_init(void)
{
    key4.port = HAL_IOMUX_PIN_P3_2;

    key4.config = IRQ_MODE;
    //key4.priv = NULL;
    hal_gpio_init(&key4);
    //中断使能
    hal_gpio_enable_irq(&key4, IRQ_TRIGGER_RISING_EDGE, key4_irq, (void *)0); 
}

//中断处理函数



int application_start(int argc, char *argv[])
{
   key4_init();
   while(1)
   {
        aos_msleep(1000);
   }
}
