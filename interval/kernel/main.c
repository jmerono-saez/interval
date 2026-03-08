#include <interval/kernel/main.h>
#include <interval/kernel/device.h>

#include <interval/device-modes/gpio.h>
#include <interval/operations.h>

void main(void) {
    device_t * gpio = device_match("gpio", NULL, DEVICE_NULL);
    device_mode_t mode;
    
    for (long i = 0; i < gpio->mode_count; i++) {
        if (gpio->modes[i].kind == GPIO_KIND) {
            mode = gpio->modes[i];
            break;
        }
    }
    
    rwable_t * discovery = gpio->open(gpio, mode.base);
    gpio_t wire;
    
    while (discovery->read(discovery, &(wire), sizeof(gpio_t))) {
        if (equals_text(wire.name, "A7")) {
            break;
        }
    }
    
    discovery->close(discovery);
    rwable_t * light = gpio->open(gpio, wire.output_lane);
    
    while (true) {
        write_ul(light, 1);
        
        for (long i = 0; i < 1048576; i++) {
            __asm__("");
        }
        
        write_ul(light, 0);
        
        for (long i = 0; i < 1048576; i++) {
            __asm__("");
        }
    }
    
    light->close(light);
}
