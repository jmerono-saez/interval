#include <interval/memory.h>

#include <interval/pool.h>

static wide_alloc_fn_t * memory_wide_alloc_fn;
static long memory_wide_bytes;

static pool_t memory_pool;

void memory_init(wide_alloc_fn_t * wide_alloc_fn, long wide_bytes) {
    memory_wide_alloc_fn = wide_alloc_fn;
    memory_wide_bytes = wide_bytes;
    
    memory_pool = pool_null(sizeof(long));
}

void * alloc(long bytes) {
    const long units = (bytes + memory_pool.unit_bytes - 1) / memory_pool.unit_bytes;
    void * p = pool_alloc(&(memory_pool), units);
    
    if (p != NULL) {
        return p;
    }
    
    const long pages = (bytes + memory_wide_bytes - 1) / memory_wide_bytes;
    const long wide_units = (pages * memory_wide_bytes) / memory_pool.unit_bytes;
    
    pool_store_zone(&(memory_pool), memory_wide_alloc_fn(pages * 4), wide_units);
    
    return alloc(bytes);
}

void free(void * p) {
    pool_free(&(memory_pool), p);
}
