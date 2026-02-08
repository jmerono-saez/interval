#ifndef __INTERVAL_KERNEL_DEVICE_H__
#define __INTERVAL_KERNEL_DEVICE_H__

#include <interval/list.h>
#include <interval/stream.h>

// devices are composed of multiple lanes and some set of modes. each
// mode represents one standard way of interfacing the device, and must
// come with a range of associated configuration/discovery lanes.

// === constants ===

#define lane_invalid (long)(0 - 1)

enum : long {
    mode_gpio,
};

// === types ===

typedef struct device_t device_t;

typedef stream_t * device_open_method_t(device_t * device, long lane);

struct device_t {
    long id;
    
    void * data;
    device_open_method_t * open;
    
    long pair_count;
    long pairs[/* (pair_count) */][2];
};

// === globals ===

extern list_t devices;

// === functions ===

void device_init(void);
void device_store(device_t * device);

device_t * device_find(const char * name);
stream_t * device_open(device_t * device, long lane);

#endif
