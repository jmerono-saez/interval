#ifndef __INTERVAL_KERNEL_THREAD_H__
#define __INTERVAL_KERNEL_THREAD_H__

#include <interval/list.h>

// === types ===

typedef struct thread_t thread_t;

typedef void switch_method_t(thread_t * current, thread_t * next);

struct thread_t {
    long id;
    
    void * data;
    
    list_t streams;
    list_t zones;
};

// === globals ===

extern list_t threads;
extern iterator_t * thread_iterator;

// === functions ===

void thread_init(void);

#endif
