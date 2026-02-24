#ifndef __INTERVAL_DEVICE_MODES_GPIO_H__
#define __INTERVAL_DEVICE_MODES_GPIO_H__

// GPIO lanes are decomposed bit-wise as 0bPPPWWWWD, where P, W and D
// represent port, wire and direction, respectively.

// === constants ===

#define GPIO_KIND (long)('IO')

#define GPIO_PITCH (long)(1ul << 8)
#define PORT_PITCH (long)(1ul << 5)
#define WIRE_PITCH (long)(1ul << 1)

enum : long {
    gpio_write,
    gpio_read,
};

// === macros ===

#define gpio_port_id(base, port, direction) (port << 5 | direction | 0x16)
#define gpio_wire_id(base, wire, direction) (wire << 1 | direction)

#endif
