#ifndef __INTERVAL_KERNEL_THREAD_H__
#define __INTERVAL_KERNEL_THREAD_H__

#include <stddef.h>

/*
    Threads in interval act very simply, by just including regions of
    memory in both physical-space and thread-space, alongside some
    metadata to be used during scheduling and context switching.
*/

typedef struct thread_t thread_t;
typedef struct t_region_t t_region_t;

struct thread_t {
    t_region_t * regions;
    size_t       region_count;
};

struct t_region_t {
    // In physical-space:
    void * pages;
    size_t page_count;
    
    // In thread-space:
    void * here;
};

#endif
