#include <interval/watch-armv8-m/main.h>

#include <interval/memory.h>
#include <interval/operations.h>

#include <interval/kernel/device.h>
#include <interval/kernel/main.h>

#include <interval/watch-armv8-m/devices/efr32mg24-gpio.h>

extern const void watch_armv8_m_data_left;
extern const void watch_armv8_m_data_right;

extern const void watch_armv8_m_data_flash;

extern const void watch_armv8_m_zero_left;
extern const void watch_armv8_m_zero_right;

bool do_sleep = true;

void watch_armv8_m_main(void) {
    void * data_left  = (void *)(&(watch_armv8_m_data_left));
    void * data_right = (void *)(&(watch_armv8_m_data_right));
    
    void * data_flash = (void *)(&(watch_armv8_m_data_flash));
    
    move(data_left, data_flash, data_right - data_left);
    
    while (do_sleep);
    
    void * zero_left  = (void *)(&(watch_armv8_m_zero_left));
    void * zero_right = (void *)(&(watch_armv8_m_zero_right));
    
    memory_init();
    memory_store(zero_left, zero_right);
    
    device_init();
    
    // efr32mg24_clocks_init();
    // efr32mg24_energy_init();
    // ...
    
    efr32mg24_gpio_init();
    
    main();
}
