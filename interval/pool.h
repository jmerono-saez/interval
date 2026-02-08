#ifndef __INTERVAL_POOL_T__
#define __INTERVAL_POOL_T__

#include <stddef.h>

// === constants ===

#define pool_invalid (long)(0 - 1)

enum : unsigned char {
    pool_free_node = 0x00,
    pool_used_node = 0xFF,
};

// === macros ===

#define pool_up(n) ((n - 1) / 2)
#define pool_down(n, c) ((n * 2) + c)

// === types ===

typedef struct pool_t pool_t;

struct pool_t {
    long count, depth;
    unsigned char tree[/* (2 << depth) */];
};

// === inner functions ===

long pool_needed_depth(long count);
long pool_size(pool_t * pool);

void pool_sift(pool_t * pool, long n);

// === functions ===

void pool_init(pool_t * pool, long count);

void pool_mark(pool_t * pool, long o_left, long o_right);

long pool_alloc(pool_t * pool, long count);
void pool_free(pool_t * pool, long o);

#endif
