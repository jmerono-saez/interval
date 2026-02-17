#ifndef __INTERVAL_WATCH_ARMV8_M_DEVICES_EFR32MG24_GPIO_H__
#define __INTERVAL_WATCH_ARMV8_M_DEVICES_EFR32MG24_GPIO_H__

#include <interval/kernel/device.h>

// === constants ===

#define EFR32MG24_GPIO_NAME "gpio0"

enum : long {
    efr32mg24_gpio_lane,
    
    efr32mg24_gpio_port_a_lane,
    efr32mg24_gpio_port_b_lane,
    efr32mg24_gpio_port_c_lane,
    efr32mg24_gpio_port_d_lane,
};

// === functions ===

void efr32mg24_gpio_init(void);

#endif
