#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>

#include <aos/hal/gpio.h>
#include <hal_iomux_haas1000.h>
#include <aos/hal/pwm.h>

#define BUZZPORT 0
pwm_dev_t buzz = {0};

void buzz_init(void)
{
    buzz.port = BUZZPORT;
    buzz.config.duty_cycle = 0.5;
    buzz.config.freq = 2000;
    hal_pwm_init(&buzz);
}

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

int application_start(int argc, char *argv[])
{
   buzz_init();
   while(1) {
       hal_pwm_start(&buzz);
       aos_msleep(1000);
       hal_pwm_stop(&buzz);
       aos_msleep(1000);
   }
}
