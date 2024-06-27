#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>

#include "aos/hal/gpio.h"
#include "hal_iomux_haas1000.h"
#include "aos/hal/pwm.h"
#include "sh1106.h"
#include "aos/hal/i2c.h"
#include "aos/hal/adc.h"

#define IIC_PORT 1
#define IIC_ADDR 0x40
#define IIC_REG 0x00
i2c_dev_t iic = {0};
void temp_hum_get(float *temp, float *hum)
{
    iic.port = IIC_PORT;
    iic.config.address_width = I2C_HAL_ADDRESS_WIDTH_7BIT;
    iic.config.mode = I2C_MODE_MASTER;
    iic.config.freq = I2C_BUS_BIT_RATES_100K;
    iic.config.dev_addr = IIC_ADDR;
    hal_i2c_init(&iic);
    uint8_t buf[4] = {0};
    unsigned int temp_now = 0;
    unsigned int hum_now = 0;
    uint8_t reg = IIC_REG;
    hal_i2c_master_send(&iic, IIC_ADDR, &reg, 1, 1000);
    aos_msleep(1000);
    hal_i2c_master_recv(&iic, IIC_ADDR, buf, 4, 1000);
    temp_now = (buf[0] << 8) + buf[1];
    hum_now = (buf[2] << 8) + buf[3];
    *temp = (165.0f * (float)temp_now)/65535.0f - 40.0f;
    *hum = (100.0f * (float)hum_now)/65535.0f;
}

int application_start(int argc, char *argv[])
{
    float temp, hum;
    uint8_t Temp[50] = {0};
    uint8_t Hum[50] = {0};
    sh1106_init();

   while(1)
   {
       temp_hum_get(&temp, &hum);
    //    sprintf(Temp, "Temp: %.2f C", temp);
    //    sprintf(Hum, "Hum: %.2f %%", hum);
       printf("temp: %f, hum: %f\n", temp, hum);
       aos_msleep(1000);
   }
}
