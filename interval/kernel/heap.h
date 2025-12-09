#ifndef __INTERVAL_KERNEL_HEAP_H__
#define __INTERVAL_KERNEL_HEAP_H__

#include <stddef.h>

// === constants ===

#ifndef HEAP_N
#error "HEAP_N is not defined"
#endif

// === types ===

typedef struct heap_unit_t heap_unit_t;

struct heap_unit_t {
    union {
        size_t i;
        void * next;
    };
};

// === globals ===

extern heap_unit_t * heap_chain_list[HEAP_N];
extern size_t heap_f_list[HEAP_N];

extern void *(* heap_expand_pages)(size_t);
extern void(* heap_free_pages)(void *);

// === functions ===

void heap_init(void *(* expand)(size_t), void(* free)(void *));

void * heap_alloc(size_t bytes);
void heap_free(void * p);

// === inner functions ===

size_t heap_unit_bytes(size_t i);

bool heap_obtain(size_t i);

void heap_insert_unit(heap_unit_t * unit, size_t i);
bool heap_expand(void);

#endif
