#ifndef __INTERVAL_STREAM_H__
#define __INTERVAL_STREAM_H__

#include <stddef.h>

// === types ===

typedef struct stream_t stream_t;

typedef long write_fn_t(stream_t * stream, const void * from, long bytes);
typedef long read_fn_t(stream_t * stream, void * to, long bytes);

typedef bool is_empty_fn_t(stream_t * stream);

struct stream_t {
    void * data;
    
    write_fn_t * write_fn;
    read_fn_t * read_fn;
    
    is_empty_fn_t * is_empty_fn;
};

// === functions ===

long write(stream_t * stream, const void * from, long bytes);
long read(stream_t * stream, void * to, long bytes);

bool is_empty(stream_t * stream);

#endif
