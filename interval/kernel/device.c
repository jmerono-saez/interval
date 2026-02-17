#include <interval/kernel/device.h>

#include <interval/memory.h>
#include <interval/operations.h>

// === globals ===

list_t devices;

// === lane_t functions ===

bool lane_present(device_t * device, long id) {
    iterator_t * it = device->lanes.begin;
    
    while (it != device->lanes.end) {
        lane_t * lane = it->item;
        
        if (lane->id == id) {
            return true;
        }
        
        it = it->next;
    }
    
    return false;
}

rwable_t * lane_alloc(device_t * device, long id) {
    lane_t * lane = alloc(sizeof(lane_t));
    
    lane->id = id;
    lane->device = device;
    
    lane->rw.data = lane;
    
    iterator_store(device->lanes.end, lane);
    return (&(lane->rw));
}

void lane_free(rwable_t * rw) {
    lane_t * lane = rw->data;
    
    device_t * device = lane->device;
    iterator_t * it = device->lanes.begin;
    
    while (it != device->lanes.end) {
        if (it->item == lane) {
            it->item = NULL;
        }
        
        it = it->next;
    }
    
    list_clean(&(device->lanes));
    free(lane);
}

// === device_t functions ===

void device_init(void) {
    list_init(&(devices));
}

device_t * device_alloc(const char * name, rwable_t *(* open)(device_t *, long)) {
    device_t * device = alloc(sizeof(device_t));
    
    device->name = name;
    device->open = open;
    
    list_init(&(device->lanes));
    
    iterator_store(devices.end, device);
    return device;
}

device_t * device_by_name(const char * name) {
    iterator_t * it = devices.begin;
    
    while (it != devices.end) {
        device_t * device = it->item;
        
        if (equals_text(device->name, name)) {
            return device;
        }
        
        it = it->next;
    }
    
    return NULL;
}
