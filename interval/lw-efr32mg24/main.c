#include <interval/lw-efr32mg24/main.h>

#include <interval/memory.h>
#include <interval/operations.h>

#include <interval/kernel/device.h>
#include <interval/kernel/main.h>

#include <interval/lw-efr32mg24/devices/gpio.h>

extern const void lw_data_left;
extern const void lw_data_right;

extern const void lw_data_flash;

extern const void lw_zero_left;
extern const void lw_zero_right;

bool do_sleep = true;

void lw_main(void) {
    void * data_left  = (void *)(&(lw_data_left));
    void * data_right = (void *)(&(lw_data_right));
    
    void * data_flash = (void *)(&(lw_data_flash));
    
    move(data_left, data_flash, data_right - data_left);
    
    while (do_sleep);
    
    void * zero_left  = (void *)(&(lw_zero_left));
    void * zero_right = (void *)(&(lw_zero_right));
    
    memory_init();
    memory_store(zero_left, zero_right);
    
    device_init();
    
    // lw_clocks_init();
    // lw_energy_init();
    // ...
    
    lw_gpio_init();
    
    main();
}
