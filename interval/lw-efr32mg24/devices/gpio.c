#include <interval/lw-efr32mg24/devices/gpio.h>
#include <interval/lw-efr32mg24/registers.h>

#include <interval/memory.h>
#include <interval/operations.h>

#include <interval/kernel/device.h>

// === globals ===

static const gpio_t gpios[/* (...) */] = {
    {.name = "A*", .width = 0x0A, .output_lane = 0x0A04, .input_lane = 0x0A01},
    
    {.name = "A0", .width = 0x01, .output_lane = 0xA004, .input_lane = 0xA001},
    {.name = "A1", .width = 0x01, .output_lane = 0xA104, .input_lane = 0xA101},
    {.name = "A2", .width = 0x01, .output_lane = 0xA204, .input_lane = 0xA201},
    {.name = "A3", .width = 0x01, .output_lane = 0xA304, .input_lane = 0xA301},
    {.name = "A4", .width = 0x01, .output_lane = 0xA404, .input_lane = 0xA401},
    {.name = "A5", .width = 0x01, .output_lane = 0xA504, .input_lane = 0xA501},
    {.name = "A6", .width = 0x01, .output_lane = 0xA604, .input_lane = 0xA601},
    {.name = "A7", .width = 0x01, .output_lane = 0xA704, .input_lane = 0xA701},
    {.name = "A8", .width = 0x01, .output_lane = 0xA804, .input_lane = 0xA801},
    {.name = "A9", .width = 0x01, .output_lane = 0xA904, .input_lane = 0xA901},
    
    {.name = "B*", .width = 0x06, .output_lane = 0x0B04, .input_lane = 0x0B01},
    
    {.name = "B0", .width = 0x01, .output_lane = 0xB004, .input_lane = 0xB001},
    {.name = "B1", .width = 0x01, .output_lane = 0xB104, .input_lane = 0xB101},
    {.name = "B2", .width = 0x01, .output_lane = 0xB204, .input_lane = 0xB201},
    {.name = "B3", .width = 0x01, .output_lane = 0xB304, .input_lane = 0xB301},
    {.name = "B4", .width = 0x01, .output_lane = 0xB404, .input_lane = 0xB401},
    {.name = "B5", .width = 0x01, .output_lane = 0xB504, .input_lane = 0xB501},
    
    {.name = "A*", .width = 0x0A, .output_lane = 0x0C04, .input_lane = 0x0C01},
    
    {.name = "C0", .width = 0x01, .output_lane = 0xC004, .input_lane = 0xC001},
    {.name = "C1", .width = 0x01, .output_lane = 0xC104, .input_lane = 0xC101},
    {.name = "C2", .width = 0x01, .output_lane = 0xC204, .input_lane = 0xC201},
    {.name = "C3", .width = 0x01, .output_lane = 0xC304, .input_lane = 0xC301},
    {.name = "C4", .width = 0x01, .output_lane = 0xC404, .input_lane = 0xC401},
    {.name = "C5", .width = 0x01, .output_lane = 0xC504, .input_lane = 0xC501},
    {.name = "C6", .width = 0x01, .output_lane = 0xC604, .input_lane = 0xC601},
    {.name = "C7", .width = 0x01, .output_lane = 0xC704, .input_lane = 0xC701},
    {.name = "C8", .width = 0x01, .output_lane = 0xC804, .input_lane = 0xC801},
    {.name = "C9", .width = 0x01, .output_lane = 0xC904, .input_lane = 0xC901},
    
    {.name = "D*", .width = 0x06, .output_lane = 0x0D04, .input_lane = 0x0D01},
    
    {.name = "D0", .width = 0x01, .output_lane = 0xD004, .input_lane = 0xD001},
    {.name = "D1", .width = 0x01, .output_lane = 0xD104, .input_lane = 0xD101},
    {.name = "D2", .width = 0x01, .output_lane = 0xD204, .input_lane = 0xD201},
    {.name = "D3", .width = 0x01, .output_lane = 0xD304, .input_lane = 0xD301},
    {.name = "D4", .width = 0x01, .output_lane = 0xD404, .input_lane = 0xD401},
    {.name = "D5", .width = 0x01, .output_lane = 0xD504, .input_lane = 0xD501},
};

// === functions ===

static bool write(rwable_t * rw, const void * from, long bytes) {
    lane_t * lane = rw->data;
    
    const long id = lane->id;
    device_t * device = lane->device;
    
    if (id == LW_GPIO_BASE) {
        return false; // cannot write to read-only GPIO enumeration.
    }
    
    unsigned long ul = 0;
    
    move(&(ul), from, bytes > sizeof(unsigned long) ? sizeof(unsigned long) : bytes);
    
    if (take_digit(id, 3)) {
        auto func = ul ? mg24_raise : mg24_lower;
        
        switch (take_digit(id, 3)) {
            case 0x0A: func(MG24_GPIO_BASE, mg24_gpio_port_a_output, 1ul << (take_digit(id, 2) * 1)); break;
            case 0x0B: func(MG24_GPIO_BASE, mg24_gpio_port_b_output, 1ul << (take_digit(id, 2) * 1)); break;
            case 0x0C: func(MG24_GPIO_BASE, mg24_gpio_port_c_output, 1ul << (take_digit(id, 2) * 1)); break;
            case 0x0D: func(MG24_GPIO_BASE, mg24_gpio_port_d_output, 1ul << (take_digit(id, 2) * 1)); break;
        }
    } else {
        switch (take_digit(id, 2)) {
            case 0x0A: mg24_write(MG24_GPIO_BASE, mg24_gpio_port_a_output, ul); break;
            case 0x0B: mg24_write(MG24_GPIO_BASE, mg24_gpio_port_b_output, ul); break;
            case 0x0C: mg24_write(MG24_GPIO_BASE, mg24_gpio_port_c_output, ul); break;
            case 0x0D: mg24_write(MG24_GPIO_BASE, mg24_gpio_port_d_output, ul); break;
        }
    }
    
    return true;
}

static bool read(rwable_t * rw, void * to, long bytes) {
    lane_t * lane = rw->data;
    
    const long id = lane->id;
    device_t * device = lane->device;
    
    if (id == LW_GPIO_BASE) {
        if (rw->head + bytes > sizeof(gpios)) {
            return false;
        }
        
        move(to, (void *)(gpios) + rw->head, bytes);
        rw->head += bytes;
        
        return true;
    }
    
    unsigned long ul = 0;
    
    if (take_digit(id, 3)) {
        switch (take_digit(id, 3)) {
            case 0x0A: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_a_input); break;
            case 0x0B: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_b_input); break;
            case 0x0C: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_c_input); break;
            case 0x0D: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_d_input); break;
        }
        
        ul = (ul >> (take_digit(id, 2) * 1)) & 1;
    } else {
        switch (take_digit(id, 2)) {
            case 0x0A: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_a_input); break;
            case 0x0B: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_b_input); break;
            case 0x0C: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_c_input); break;
            case 0x0D: ul = mg24_read(MG24_GPIO_BASE, mg24_gpio_port_d_input); break;
        }
    }
    
    move(to, &(ul), bytes > sizeof(unsigned long) ? sizeof(unsigned long) : bytes);
    
    return true;
}

static bool is_empty(rwable_t * rw) {
    lane_t * lane = rw->data;
    
    const long id = lane->id;
    device_t * device = lane->device;
    
    if (id != LW_GPIO_BASE) {
        return false;
    }
    
    return (rw->head < sizeof(gpios));
}

static bool close(rwable_t * rw) {
    lane_t * lane = rw->data;
    
    const long id = lane->id;
    device_t * device = lane->device;
    
    if (id != LW_GPIO_BASE) {
        if (take_digit(id, 3)) {
            switch (take_digit(id, 3)) {
                case 0x0A:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_a_mode_l, 0x0Ful << (take_digit(id, 2) * 4));
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_a_mode_h, 0x0Ful << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0B:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_b_mode_l, 0x0Ful << (take_digit(id, 2) * 4));
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_b_mode_h, 0x0Ful << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0C:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_c_mode_l, 0x0Ful << (take_digit(id, 2) * 4));
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_c_mode_h, 0x0Ful << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0D:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_d_mode_l, 0x0Ful << (take_digit(id, 2) * 4));
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_d_mode_h, 0x0Ful << (take_digit(id, 2) * 4 - 0x20));
                    break;
            }
        } else {
            switch (take_digit(id, 2)) {
                case 0x0A:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_a_mode_l, 0xFFFFFFFFul);
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_a_mode_h, 0xFFFFFFFFul);
                    break;
                    
                case 0x0B:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_b_mode_l, 0xFFFFFFFFul);
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_b_mode_h, 0xFFFFFFFFul);
                    break;
                    
                case 0x0C:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_c_mode_l, 0xFFFFFFFFul);
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_c_mode_h, 0xFFFFFFFFul);
                    break;
                    
                case 0x0D:
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_d_mode_l, 0xFFFFFFFFul);
                    mg24_lower(MG24_GPIO_BASE, mg24_gpio_port_d_mode_h, 0xFFFFFFFFul);
                    break;
            }
        }
    }
    
    lane_free(rw);
    
    if (device->lanes.count == 0) {
        mg24_lower(MG24_CLOCK_BASE, mg24_clock_enable_l, 1ul << 0x1A);
    }
    
    return true;
}

static rwable_t * open(device_t * device, long id) {
    if (id >> 0x10) {
        return NULL; // ignore lanes over 64k, to simplify logic.
    }
    
    if (device->lanes.count == 0) {
        mg24_raise(MG24_CLOCK_BASE, mg24_clock_enable_l, 1ul << 0x1A);
    }
    
    if (id != LW_GPIO_BASE) {
        if (lane_present(device, id, 0xFF00)) {
            return NULL; // pins cannot be opened twice simultaneously.
        }
        
        if (take_digit(id, 3)) {
            if (lane_present(device, id >> 0x04, 0xFF00)) {
                return NULL; // if individual, check for grouped pins.
            }
            
            switch (take_digit(id, 3)) {
                case 0x0A:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_a_mode_l, take_digit(id, 0) << (take_digit(id, 2) * 4));
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_a_mode_h, take_digit(id, 0) << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0B:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_b_mode_l, take_digit(id, 0) << (take_digit(id, 2) * 4));
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_b_mode_h, take_digit(id, 0) << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0C:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_c_mode_l, take_digit(id, 0) << (take_digit(id, 2) * 4));
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_c_mode_h, take_digit(id, 0) << (take_digit(id, 2) * 4 - 0x20));
                    break;
                    
                case 0x0D:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_d_mode_l, take_digit(id, 0) << (take_digit(id, 2) * 4));
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_d_mode_h, take_digit(id, 0) << (take_digit(id, 2) * 4 - 0x20));
                    break;
            }
        } else {
            if (lane_present(device, id << 0x04, 0xF000)) {
                return NULL; // if grouped, check for individual pins.
            }
            
            switch (take_digit(id, 2)) {
                case 0x0A:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_a_mode_l, take_digit(id, 0) * 0x11111111ul);
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_a_mode_h, take_digit(id, 0) * 0x11111111ul);
                    break;
                    
                case 0x0B:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_b_mode_l, take_digit(id, 0) * 0x11111111ul);
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_b_mode_h, take_digit(id, 0) * 0x11111111ul);
                    break;
                    
                case 0x0C:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_c_mode_l, take_digit(id, 0) * 0x11111111ul);
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_c_mode_h, take_digit(id, 0) * 0x11111111ul);
                    break;
                    
                case 0x0D:
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_d_mode_l, take_digit(id, 0) * 0x11111111ul);
                    mg24_raise(MG24_GPIO_BASE, mg24_gpio_port_d_mode_h, take_digit(id, 0) * 0x11111111ul);
                    break;
            }
        }
    }
    
    rwable_t * rw = lane_alloc(device, id);
    
    rw->write = write;
    rw->read = read;
    rw->is_empty = is_empty;
    rw->close = close;
    
    return rw;
}

void lw_gpio_init(void) {
    static device_mode_t modes[1] = {
        {.kind = GPIO_KIND, .base = LW_GPIO_BASE},
    };
    
    device_alloc("gpio", "efr32mg24", modes, 1, open);
}
