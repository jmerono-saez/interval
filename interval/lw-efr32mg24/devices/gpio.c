#include <interval/lw-efr32mg24/devices/gpio.h>

#include <interval/memory.h>
#include <interval/operations.h>

#include <interval/device-modes/gpio.h>

// === private functions ===

static long write(rwable_t * rw, const void * from, long bytes) {
    const long port      = ((id - LW_GPIO_BASE) >> 5) & 0x0F;
    const long wire      = ((id - LW_GPIO_BASE) >> 1) & 0x0F;
    const long direction = ((id - LW_GPIO_BASE) >> 0) & 0x01;
    
    if (direction == gpio_write) {
        // write output value.
    }
    
    if (direction == gpio_read) {
        // write push up/down value.
    }
}

static long read(rwable_t * rw, void * to, long bytes) {
    const long port      = ((id - LW_GPIO_BASE) >> 5) & 0x0F;
    const long wire      = ((id - LW_GPIO_BASE) >> 1) & 0x0F;
    const long direction = ((id - LW_GPIO_BASE) >> 0) & 0x01;
    
    if (direction == gpio_write) {
        // read fixed output value.
    }
    
    if (direction == gpio_read) {
        // read input value.
    }
}

static bool is_empty(rwable_t * rw) {
    return false;
}

static void close(rwable_t * rw) {
    lane_free(rw);
}

static rwable_t * open(device_t * device, long id) {
    // must be between base and base + pitch.
    // if individual wire, both wire lanes and grouped lanes must not be open.
    // if grouped port, all lanes in that port must not be open.
    
    if (id >= LW_GPIO_BASE + GPIO_PITCH || id < LW_GPIO_BASE) {
        return NULL;
    }
    
    const long port      = ((id - LW_GPIO_BASE) >> 5) & 0x0F;
    const long wire      = ((id - LW_GPIO_BASE) >> 1) & 0x0F;
    const long direction = ((id - LW_GPIO_BASE) >> 0) & 0x01;
    
    if (wire == 0x0E) {
        if (lane_present(device, LW_GPIO_BASE + (port << 5), LW_GPIO_BASE + (port << 5) + PORT_PITCH)) {
            return NULL;
        }
    } else {
        if (lane_present(device, LW_GPIO_BASE + (port << 5) + (wire << 1), LW_GPIO_BASE + (port << 5) + (wire << 1) + WIRE_PITCH)) {
            return NULL;
        }
        
        if (lane_present(device, LW_GPIO_BASE + (port << 5) + (0x0E << 1), LW_GPIO_BASE + (port << 5) + (0x0E << 1) + WIRE_PITCH)) {
            return NULL;
        }
    }
    
    rwable_t * rw = lane_alloc(device, id);
    
    rw->write = write;
    rw->read = read;
    rw->is_empty = is_empty;
    rw->close = close;
    
    return rw;
}

// === functions ===

void lw_gpio_init(void) {
    static const device_mode_t modes[1] = {
        {.kind = GPIO_KIND, .base = LW_GPIO_BASE},
    };
    
    device_alloc("gpio", "efr32mg24", modes, 1, open);
    
    mg24_write()
    mg24_turn_on()
    mg24_turn_off()
    mg24_toggle()
    
    mg24_read()
}
