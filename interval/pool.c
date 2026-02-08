#include <interval/pool.h>

// === functions ===

long pool_needed_depth(long count) {
    long depth = 0;
    
    while (count >= 2) {
        count = (count + 1) / 2, depth++;
    }
    
    return depth;
}

long pool_size(pool_t * pool) {
    return (sizeof(pool_t) + (2 << pool->depth));
}

void pool_sift(pool_t * pool, long n) {
    unsigned char u, v, w;
    
    while (n) {
        n = pool_up(n);
        
        u = pool->tree[pool_down(n, 1)];
        v = pool->tree[pool_down(n, 2)];
        w = (u < v ? u : v) + 1;
        
        if (u == v) {
            if (u == pool_free_node || u == pool_used_node) {
                w = u;
            }
        }
        
        if (pool->tree[n] == w) {
            break;
        }
        
        pool->tree[n] = w;
    }
}

void pool_init(pool_t * pool, long count) {
    pool->depth = pool_needed_depth(pool->count = count);
    
    for (long n = 0; n < (2 << pool->depth); n++) {
        pool->tree[n] = pool_free_node;
    }
    
    pool_mark(pool, count, 1 << pool->depth);
}

void pool_mark(pool_t * pool, long o_left, long o_right) {
    for (long o = o_left; o < o_right; o++) {
        long n = o + (1 << pool->depth) - 1;
        
        pool->tree[n] = pool_used_node;
        pool_sift(pool, n);
    }
}

long pool_alloc(pool_t * pool, long count) {
    long depth = pool->depth;
    long n = 0, needed_depth = pool_needed_depth(count);
    
    if (depth - pool->tree[0] < needed_depth) {
        return pool_invalid;
    }
    
    while (true) {
        if (depth - pool->tree[pool_down(n, 1)] > needed_depth) {
            n = pool_down(n, 1), depth--;
            continue;
        }
        
        if (depth - pool->tree[pool_down(n, 2)] > needed_depth) {
            n = pool_down(n, 2), depth--;
            continue;
        }
        
        pool->tree[n] = pool_used_node;
        pool_sift(pool, n);
        
        while (pool_down(n, 1) < (2 << pool->depth)) {
            n = pool_down(n, 1);
        }
        
        return n - (1 << pool->depth) + 1;
    }
}

void pool_free(pool_t * pool, long o) {
    long n = o + (1 << pool->depth) - 1;
    
    while (n >= 1) {
        if (pool->tree[n] == pool_used_node) {
            break;
        }
        
        n = pool_up(n);
    }
    
    pool->tree[n] = pool_free_node;
    pool_sift(pool, n);
}
