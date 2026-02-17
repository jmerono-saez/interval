#ifndef __INTERVAL_RWABLE_H__
#define __INTERVAL_RWABLE_H__

#include <stddef.h>

// === types ===

typedef struct rwable_t rwable_t;

struct rwable_t {
    void * data;
    
    long(* write)(rwable_t * rw, const void * from, long bytes);
    long(* read)(rwable_t * rw, void * to, long bytes);
    bool(* is_empty)(rwable_t * rw);
    void(* close)(rwable_t * rw);
};

// === functions ===

bool write_char(rwable_t * rw, char ch);
char read_char(rwable_t * rw, char empty_ch);

long format(rwable_t * rw, const char * text, ...);

#endif
