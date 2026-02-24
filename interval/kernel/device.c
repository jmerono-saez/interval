#include <interval/kernel/device.h>

#include <interval/memory.h>
#include <interval/operations.h>

// === globals ===

list_t devices;
long next_device_id;

// === lane_t functions ===

long lane_id(rwable_t * rw) {
    lane_t * lane = rw->data;
    return lane->id;
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

bool lane_present(device_t * device, long left, long right) {
    iterator_t * it = device->lanes.begin;
    
    while (it != device->lanes.end) {
        lane_t * lane = it->item;
        
        if (lane->id >= left && lane->id < right) {
            return true;
        }
        
        it = it->next;
    }
    
    return false;
}

// === device_t functions ===

void device_init(void) {
    list_init(&(devices));
    next_device_id = 0;
}

device_t * device_alloc(const char * category, const char * group, device_mode_t * modes, long mode_count, rwable_t *(* open)(device_t *, long)) {
    device_t * device = alloc(sizeof(device_t));
    
    device->id = next_device_id++;
    list_init(&(device->lanes));
    
    device->category = category;
    device->group = group;
    
    device->modes = modes;
    device->mode_count = mode_count;
    
    device->open = open;
    
    iterator_store(devices.end, device);
    return device;
}

void device_free(device_t * device) {
    if (device->lanes.count) {
        return;
    }
    
    iterator_t * it = devices.begin;
    
    while (it != devices.end) {
        if (it->item == device) {
            it->item = NULL;
        }
        
        it = it->next;
    }
    
    free(device);
}

device_t * device_match(const char * category, const char * group, long start_id) {
    iterator_t * it = devices.begin;
    
    while (it != devices.end) {
        device_t * device = it->item;
        
        const bool match_category = (category == NULL || equals_text(device->category, category));
        const bool match_group = (group == NULL || equals_text(device->group, group));
        
        if (match_category && match_group && device->id >= start_id) {
            return device;
        }
        
        it = it->next;
    }
    
    return NULL;
}
