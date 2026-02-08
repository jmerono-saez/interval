#ifndef __INTERVAL_KERNEL_MODES_GPIO_H__
#define __INTERVAL_KERNEL_MODES_GPIO_H__

// === types ===

typedef struct gpio_t gpio_t;

struct gpio_t {
    long port_left;
    long port_right;
};

struct gpio_port_t {
    long input_lane;
    long output_lane;
    
    long wire_left;
    long wire_right;
};

struct gpio_wire_t {
    long input_lane;
    long output_lane;
};

#endif
