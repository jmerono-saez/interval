#ifndef __INTERVAL_STREAM_H__
#define __INTERVAL_STREAM_H__

#include <stddef.h>

// === types ===

typedef struct stream_t stream_t;

typedef long write_method_t(stream_t * stream, const void * from, long bytes);
typedef long read_method_t(stream_t * stream, void * to, long bytes);

typedef bool is_empty_method_t(stream_t * stream);
typedef bool close_method_t(stream_t * stream);

struct stream_t {
    void * data;
    
    write_method_t * write;
    read_method_t * read;
    
    is_empty_method_t * is_empty;
    close_method_t * close;
};

// === basic functions ===

long write(stream_t * stream, const void * from, long bytes);
long read(stream_t * stream, void * to, long bytes);

bool is_empty(stream_t * stream);
bool close(stream_t * stream);

// === char-wide functions ===

bool write_char(stream_t * stream, char ch);
char read_char(stream_t * stream, char empty_ch);

// === text-wide functions ===

bool write_text(stream_t * stream, const char * from);
long read_text(stream_t * stream, char * to, long limit, const char stop_ch);

#endif
