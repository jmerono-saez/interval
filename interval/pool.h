#ifndef __INTERVAL_POOL_T__
#define __INTERVAL_POOL_T__

#include <stddef.h>

// === constants ===

#define pool_null(unit_bytes) ((pool_t) {unit_bytes, NULL})

#define pool_up(i) ((i - 1) / 2)
#define pool_down(i, j) ((i * 2) + j)

// === enums ===

enum : unsigned char {
    pool_free_node = 0x00,
    pool_used_node = 0xFF,
};

// === types ===

typedef struct pool_zone_t pool_zone_t;

struct pool_zone_t {
    void * begin;
    long unit_count;
    
    long depth;
    pool_zone_t * next;
    
    unsigned char tree[/* (2 << depth) */];
};

typedef struct pool_t pool_t;

struct pool_t {
    long unit_bytes;
    pool_zone_t * first_zone;
};

// === functions ===

void pool_store_zone(pool_t * pool, void * begin, long unit_count);

void * pool_alloc(pool_t * pool, long unit_count);
void pool_free(pool_t * pool, void * p);

// === inner functions ===

long pool_needed_depth(long unit_count);

void pool_mark(pool_t * pool, pool_zone_t * zone, void * p, long unit_count);
void pool_sift(pool_t * pool, pool_zone_t * zone, long i);

#endif
