#ifndef __INTERVAL_KERNEL_DEVICE_H__
#define __INTERVAL_KERNEL_DEVICE_H__

#include <interval/list.h>
#include <interval/rwable.h>

// devices are composed of multiple lanes and some set of modes. each
// mode represents one standard way of interfacing the device, and must
// come with a range of associated configuration/discovery lanes.

// === constants ===

#define lane_null (long)(0 - 1)

enum : long {
    mode_discovery,
    mode_gpio,
};

// === types ===

typedef struct lane_t lane_t;
typedef struct device_t device_t;

struct lane_t {
    long id;
    device_t * device;
    
    rwable_t rw;
};

struct device_t {
    const char * name;
    rwable_t *(* open)(device_t * device, long id);
    
    list_t lanes;
};

// === globals ===

extern list_t devices;

// === lane_t functions ===

bool lane_present(device_t * device, long id);

rwable_t * lane_alloc(device_t * device, long id);
void lane_free(rwable_t * rw);

// === device_t functions ===

void device_init(void);

device_t * device_alloc(const char * name, rwable_t *(* open)(device_t *, long));
device_t * device_by_name(const char * name);

#endif
