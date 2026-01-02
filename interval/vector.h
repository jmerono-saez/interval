#ifndef __INTERVAL_VECTOR_H__
#define __INTERVAL_VECTOR_H__

#include <stddef.h>

// === constants ===

#define vector_null(type) ((struct vector_##type) {NULL, 0, 0})

#define vector_$(vector) (void *)(vector), sizeof(vector->at[0])

// === types ===

typedef long compare_fn_t(const void *, const void *, long);

#define vector_t(type) struct vector_##type {type * at; long count; long limit;}

// === vector_t functions ===

void vector_reduce_$(vector_t(void) * vector, long item_bytes);

#define vector_reduce(vector) vector_reduce_$(vector_$(vector))

void vector_grow_$(vector_t(void) * vector, long item_bytes);

#define vector_grow(vector) vector_grow_$(vector_$(vector))

#define vector_push(vector, item) (vector_grow(vector), vector->at[vector->count++] = item)
#define vector_pull(vector) (vector->at[--vector->count])

void vector_sort_$(vector_t(void) * vector, long item_bytes, compare_fn_t * fn);

#define vector_sort(vector, fn) vector_sort_$(vector_$(vector), fn)

void vector_heaped_push(vector_t(void) * vector, long item_bytes, compare_fn_t * fn);

#define vector_heaped_push(vector, fn, item) (vector_push(vector, item), vector_heaped_push_$(vector_$(vector), fn))

void vector_heaped_pull(vector_t(void) * vector, long item_bytes, compare_fn_t * fn);

#define vector_heaped_pull(vector, fn) (vector_heaped_pull_$(vector_$(vector), fn), vector_pull(vector))

#endif
