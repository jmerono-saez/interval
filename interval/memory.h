#ifndef __INTERVAL_MEMORY_H__
#define __INTERVAL_MEMORY_H__

#include <stddef.h>

// === types ===

typedef void * wide_alloc_fn_t(long wide_count);

// === functions ===

void memory_init(wide_alloc_fn_t * wide_alloc_fn, long wide_bytes);

void * alloc(long bytes);
void free(void * p);

#endif
