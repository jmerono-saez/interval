#ifndef __INTERVAL_KERNEL_THREAD_H__
#define __INTERVAL_KERNEL_THREAD_H__

#include <interval/list.h>
#include <interval/rwable.h>

// threads are composed of multiple mapped zones and a couple of rwable
// bridges for the thread to communicate with other threads directly,
// alongside some platform-specific state that gets saved and read when
// switching threads.

// === constants ===

#define THREAD_NULL (long)(0 - 1)

// === types ===

typedef struct bridge_t bridge_t;
typedef struct zone_t zone_t;

typedef struct thread_t thread_t;

struct bridge_t {
    long id;
    rwable_t * rw;
};

struct zone_t {
    long id;
    void * physical;
    
    void * user_left;
    void * user_right;
};

struct thread_t {
    long id;
    
    list_t bridges;
    list_t zones;
};

// === globals ===

extern list_t threads;
extern iterator_t * thread_iterator;

// === functions ===

void thread_init(void);

#endif
