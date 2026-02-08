#include <interval/watch-armv8-m/devices/efr32mg24-gpio.h>

#include <interval/memory.h>
#include <interval/operations.h>

// === globals ===

device_t efr32mg24_gpio = (device_t) {
    .pair_count = 1,
    
    .pairs = {
        {mode_gpio, efr32mg24_gpio_lane},
    },
};

/// === functions ===

static stream_t * __open(device_t * device, long lane);

static long __write(stream_t * stream, const void * from, long bytes);
static long __read(stream_t * stream, void * to, long bytes);

static bool __is_empty(stream_t * stream);
static bool __close(stream_t * stream);

void efr32mg24_gpio_init(void) {
    efr32mg24_gpio.id = hash(EFR32MG24_GPIO_NAME, length_of(EFR32MG24_GPIO_NAME)); // TODO: make better.
    
    efr32mg24_gpio.data = NULL; // TODO
    efr32mg24_gpio.open = __open;
    
    device_store(&(efr32mg24_gpio));
}

static stream_t * __open(device_t * device, long lane) {
    // TODO: check if this lane is valid (and what should it do).
    // TODO: check that no incompatible lanes are open.
    
    stream_t * stream = alloc(sizeof(stream_t));
    
    stream->data = NULL;
    
    stream->write = __write;
    stream->read = __read;
    
    stream->is_empty = __is_empty;
    stream->close = __close;
    
    return stream;
}

static long __write(stream_t * stream, const void * from, long bytes) {
    return 0; // TODO
}

static long __read(stream_t * stream, void * to, long bytes) {
    return 0; // TODO
}

static bool __is_empty(stream_t * stream) {
    return false;
}

static bool __close(stream_t * stream) {
    free(stream);
    return true;
}
