#ifndef __INTERVAL_KERNEL_THREAD_H__
#define __INTERVAL_KERNEL_THREAD_H__

#include <stddef.h>

// === constants ===

// a single tick is a 1024th of a second.

#define THREAD_TICKS 20

// === types ===

typedef struct thread_zone_t thread_zone_t;

struct thread_zone_t {
    void * region;
    size_t n;
    
    void * mapped; // matches region on MMU-less platforms.
    
    thread_zone_t * next;
};

typedef struct thread_t thread_t;

struct thread_t {
    thread_zone_t * zone_chain;
    
    thread_t * prev, * next;
};

// === globals ===

extern thread_t * thread_queue;

// === functions ===

#endif
