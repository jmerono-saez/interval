#ifndef __INTERVAL_KERNEL_DEVICE_H__
#define __INTERVAL_KERNEL_DEVICE_H__

#include <interval/list.h>
#include <interval/rwable.h>

// devices are composed of multiple lanes and some set of modes. each
// mode represents one standard way of interfacing the device, and must
// come with a range of associated configuration/discovery lanes.

// === constants ===

#define LANE_NULL (long)(0 - 1)
#define DEVICE_NULL (long)(0 - 1)

// === types ===

typedef struct lane_t lane_t;

typedef struct device_mode_t device_mode_t;
typedef struct device_t device_t;

struct lane_t {
    long id;
    device_t * device;
    
    rwable_t rw;
};

struct device_mode_t {
    long kind, base;
};

struct device_t {
    long id;
    list_t lanes;
    
    const char * category;
    const char * group;
    
    device_mode_t * modes;
    long mode_count;
    
    rwable_t *(* open)(device_t * device, long id);
};

// === globals ===

extern list_t devices;
extern long next_device_id;

// === lane_t functions ===

long lane_id(rwable_t * rw);

rwable_t * lane_alloc(device_t * device, long id);
void lane_free(rwable_t * rw);

bool lane_present(device_t * device, long left, long right);

// === device_t functions ===

void device_init(void);

device_t * device_alloc(const char * category, const char * group, device_mode_t * modes, long mode_count, rwable_t *(* open)(device_t *, long));
void device_free(device_t * device);

device_t * device_match(const char * category, const char * group, long start_id);

#endif
