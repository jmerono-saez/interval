#include <interval/kernel/device.h>

// === globals ===

list_t devices;

// === functions ===

void device_init(void) {
    list_init(&(devices));
}

void device_store(device_t * device) {
    list_store(devices.end, device);
}

device_t * device_find(long id) {
    iterator_t * it = devices.begin;
    
    while (it != devices.end) {
        device_t * device = it->item;
        
        if (device->id == id) {
            return device;
        }
        
        it = it->next;
    }
    
    return NULL;
}

stream_t * device_open(device_t * device, long lane) {
    if (device == NULL || device->open == NULL) {
        return NULL;
    }
    
    return device->open(device, lane);
}
