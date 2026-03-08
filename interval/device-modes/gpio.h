#ifndef __INTERVAL_DEVICE_MODES_GPIO_H__
#define __INTERVAL_DEVICE_MODES_GPIO_H__

// === constants ===

#define GPIO_KIND (long)('gpio')

// === types ===

typedef struct gpio_t gpio_t;

struct gpio_t {
    char name[8];
    long width;
    
    long output_lane, input_lane;
};

#endif
