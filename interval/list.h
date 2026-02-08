#ifndef __INTERVAL_LIST_H__
#define __INTERVAL_LIST_H__

#include <stddef.h>

// === types ===

typedef struct iterator_t iterator_t;
typedef struct list_t list_t;

struct iterator_t {
    void * item;
    list_t * list;
    
    iterator_t * next;
};

struct list_t {
    long count;
    
    iterator_t * begin;
    iterator_t * end;
    
    iterator_t __iterator; // this avoids an initial allocation or dangling memory.
};

// === functions ===

void list_init(list_t * list);
void list_store(iterator_t * iterator, void * item);

void list_clean(list_t * list);

#endif
