#ifndef __INTERVAL_RWABLE_H__
#define __INTERVAL_RWABLE_H__

#include <stddef.h>

// === types ===

typedef struct rwable_t rwable_t;

struct rwable_t {
    void * data;
    long head;
    
    bool(* write)(rwable_t * rw, const void * from, long bytes);
    bool(* read)(rwable_t * rw, void * to, long bytes);
    bool(* is_empty)(rwable_t * rw);
    bool(* close)(rwable_t * rw);
};

// === functions ===

bool write_ul(rwable_t * rw, unsigned long ul);
unsigned long read_ul(rwable_t * rw, unsigned long empty_ul);

bool write_ch(rwable_t * rw, char ch);
char read_ch(rwable_t * rw, char empty_ch);

long format(rwable_t * rw, const char * text, ...);

#endif
