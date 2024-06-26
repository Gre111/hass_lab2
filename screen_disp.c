#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>

#include <aos/hal/gpio.h>
#include <hal_iomux_haas1000.h>
#include <sh1106.h>


int application_start(int argc, char *argv[])
{
   sh1106_init();
   OLED_Clear();
   sh1106_show_string(0, 0, "Just make money", 16, 1);
   sh1106_show_string(56, 40, "saul goodman", 12, 1);
   OLED_Refresh_GRAM();
}
