#include <interval/kernel/main.h>
#include <interval/kernel/device.h>

void main(void) {
    // io_printf("hello from interval!\n");
    // io_printf("reaching this point means a lot of things have gone well :D.\n");
    
    // requires (alongside platform-specific setups):
    // - wide_pool
    // - io_stream
    
    // provides:
    // - thin_pool
    // - device_*
    // - config_*
    
    // requires (alongside required and provided by Stage-A):
    // - some clock device
    // - some disk device
    // - platform-specific thread switching code
    
    // provides:
    // - thread_*
    // - file_*
    // - timer_*
    // - ui_*
    // - returns as if running thread w/ ID 0
    
    while (true);
}
