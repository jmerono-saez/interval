#include <interval/kernel/main.h>
#include <interval/kernel/device.h>

#include <interval/device-modes/gpio.h>

void main(void) {
    device_t * gpio = device_match("gpio", NULL, DEVICE_NULL);
    device_mode_t mode;
    
    for (long i = 0; i < gpio->mode_count; i++) {
        if (gpio->modes[i].kind == GPIO_KIND) {
            mode = gpio->modes[i];
            break;
        }
    }
    
    const long id = mode.base + (PORT_A | WIRE_7 | DIRECTION_WRITE);
    rwable_t * light = gpio->open(gpio, id);
    
    while (true) {
        write_char(light, 1);
        
        for (long i = 0; i < 4000000; i++) {
            __asm__("");
        }
        
        write_char(light, 0);
        
        for (long i = 0; i < 4000000; i++) {
            __asm__("");
        }
    }
    
    light->close(light);
}
