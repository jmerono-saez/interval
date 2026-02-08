#include <interval/memory.h>
#include <interval/pool.h>

// === globals ===

list_t memory_pools;

// === functions ===

void memory_init(void) {
    list_init(&(memory_pools));
}

void memory_store(void * left, void * right) {
    pool_t * pool = left;
    
    pool_init(pool, round_down_units(right - left));
    pool_mark(pool, 0, round_up_units(pool_size(pool)));
    
    list_store(memory_pools.end, pool);
}

void * alloc(long bytes) {
    iterator_t * it = memory_pools.begin;
    
    while (it != memory_pools.end) {
        pool_t * pool = it->item;
        long o = pool_alloc(pool, round_up_units(bytes));
        
        if (o != pool_invalid) {
            return (o * BYTES_IN_UNIT + it->item);
        }
        
        it = it->next;
    }
    
    // this early allocator allows us to use lists to store allocator
    // data structures, and also serves to mandate some minimum units
    // to perform a graceful out-of-memory during startup.
    
    static unsigned char early_units[EARLY_BUMP_UNITS][BYTES_IN_UNIT];
    static long early_unit_count = 0;
    
    if (EARLY_BUMP_UNITS >= round_up_units(bytes) + early_unit_count) {
        void * pt = early_units + early_unit_count;
        
        early_unit_count += round_up_units(bytes);
        return pt;
    }
    
    return NULL;
}

void free(void * pt) {
    iterator_t * it = memory_pools.begin;
    
    while (it != memory_pools.end) {
        pool_t * pool = it->item;
        long o = (pt - it->item) / BYTES_IN_UNIT;
        
        if (o >= 0 && o < pool->count) {
            pool_free(pool, o);
            return;
        }
        
        it = it->next;
    }
}
