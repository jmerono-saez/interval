#include <interval/pool.h>

void pool_store_zone(pool_t * pool, void * begin, long unit_count) {
    pool_zone_t * zone = begin;
    
    zone->begin = begin;
    zone->unit_count = unit_count;
    
    zone->next = pool->first_zone;
    pool->first_zone = zone;
    
    zone->depth = pool_needed_depth(unit_count);
    
    long tree_width = (1 << zone->depth);
    long meta_bytes = sizeof(pool_zone_t) + tree_width * 2;
    
    for (long i = 0; i < tree_width * 2; i++) {
        zone->tree[i] = pool_free_node;
    }
    
    pool_mark(pool, zone, begin, (meta_bytes + pool->unit_bytes - 1) / pool->unit_bytes);
    pool_mark(pool, zone, begin + unit_count * pool->unit_bytes, tree_width - unit_count);
}

void * pool_alloc(pool_t * pool, long unit_count) {
    pool_zone_t * zone = pool->first_zone;
    
    long needed_depth = pool_needed_depth(unit_count);
    
    while (zone != NULL) {
        long depth = zone->depth;
        long i = 0;
        
        if (depth - zone->tree[0] < needed_depth) {
            zone = zone->next;
            continue;
        }
        
        while (true) {
            if (depth - zone->tree[pool_down(i, 1)] > needed_depth) {
                i = pool_down(i, 1), depth--;
                continue;
            }
            
            if (depth - zone->tree[pool_down(i, 2)] > needed_depth) {
                i = pool_down(i, 2), depth--;
                continue;
            }
            
            zone->tree[i] = pool_used_node;
            pool_sift(pool, zone, i);
            
            long tree_width = (1 << zone->depth);
            
            while (pool_down(i, 1) < tree_width * 2) {
                i = pool_down(i, 1);
            }
            
            long o = i + 1 - (1 << zone->depth);
            return zone->begin + o * pool->unit_bytes;
        }
    }
    
    return NULL;
}

void pool_free(pool_t * pool, void * p) {
    pool_zone_t * zone = pool->first_zone;
    
    while (zone != NULL) {
        if (p < zone->begin) {
            zone = zone->next;
            continue;
        }
        
        if (p >= zone->begin + zone->unit_count * pool->unit_bytes) {
            zone = zone->next;
            continue;
        }
        
        long o = (p - zone->begin) / pool->unit_bytes;
        long i = o + (1 << zone->depth) - 1;
        
        while (i >= 1) {
            if (zone->tree[i] == pool_used_node) {
                break;
            }
            
            i = pool_up(i);
        }
        
        zone->tree[i] = pool_free_node;
        pool_sift(pool, zone, i);
        
        break;
    }
}

// === inner functions ===

long pool_needed_depth(long unit_count) {
    long depth = 0;
    
    while (unit_count >= 2) {
        unit_count = (unit_count + 1) / 2;
        depth++;
    }
    
    return depth;
}

void pool_mark(pool_t * pool, pool_zone_t * zone, void * p, long unit_count) {
    long o = (p - zone->begin) / pool->unit_bytes;
    long i = (1 << zone->depth) + o - 1;
    
    while (unit_count >= 1) {
        zone->tree[i] = pool_used_node;
        pool_sift(pool, zone, i);
        
        i++, unit_count--;
    }
}

void pool_sift(pool_t * pool, pool_zone_t * zone, long i) {
    unsigned char u, v, w;
    
    while (i >= 1) {
        i = pool_up(i);
        
        u = zone->tree[pool_down(i, 1)];
        v = zone->tree[pool_down(i, 2)];
        w = (u < v ? u : v) + 1;
        
        if (u == v) {
            if (u == pool_free_node || u == pool_used_node) {
                w = u;
            }
        }
        
        if (zone->tree[i] == w) {
            break;
        }
        
        zone->tree[i] = w;
    }
}
