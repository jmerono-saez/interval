#include <interval/watch-armv8-m/devices/efr32mg24-gpio.h>

#include <interval/memory.h>
#include <interval/operations.h>

#include <interval/kernel/modes/gpio.h>

// === private functions ===

static long write(rwable_t * rw, const void * from, long bytes) {
    
}

static long read(rwable_t * rw, void * to, long bytes) {
    
}

static bool is_empty(rwable_t * rw) {
    
}

static void close(rwable_t * rw) {
    lane_free(rw);
}

static rwable_t * open(device_t * device, long id) {
    if (lane_present(device, id)) {
        return NULL;
    }
    
    rwable_t * rw = lane_alloc(device, id);
    
    rw->write = write;
    rw->read = read;
    rw->is_empty = is_empty;
    rw->close = close;
    
    return rw;
}

// === functions ===

void efr32mg24_gpio_init(void) {
    device_alloc(EFR32MG24_GPIO_NAME, open);
}
