#include <interval/kernel/page.h>

#include <interval/macros.h>
#include <interval/values.h>

// === globals ===

page_zone_t * page_chain = NULL;

// === functions ===

void page_insert_zone(void * region, size_t n) {
    page_zone_t * zone = region;
    
    zone->region = region;
    zone->n = n;
    
    zone->next = page_chain;
    page_chain = zone;
    
    zone->depth = page_needed_depth(n);
    
    size_t tree_width = (uz(1) << zone->depth);
    size_t meta_bytes = sizeof(page_zone_t) + tree_width * 2;
    
    for (size_t i = 0; i < tree_width * 2; i++) {
        zone->tree[i] = PAGE_FREE_NODE;
    }
    
    page_mark(zone, region, (meta_bytes + PAGE_BYTES - 1) / PAGE_BYTES);
    page_mark(zone, region + n * PAGE_BYTES, tree_width - n);
}

void page_mark(page_zone_t * zone, void * p, size_t n) {
    size_t o = (p - zone->region) / PAGE_BYTES;
    size_t i = (uz(1) << zone->depth) + o - 1;
    
    while (n >= 1) {
        zone->tree[i] = PAGE_USED_NODE;
        page_sift(zone, i);
        
        i++, n--;
    }
}

void * page_alloc(size_t n) {
    page_zone_t * zone = page_chain;
    
    long needed_depth = page_needed_depth(n);
    
    while (zone != NULL) {
        long depth = zone->depth;
        size_t i = 0;
        
        if (depth - zone->tree[0] < needed_depth) {
            zone = zone->next;
            continue;
        }
        
        while (true) {
            if (depth - zone->tree[PAGE_DOWN(i, 1)] > needed_depth) {
                i = PAGE_DOWN(i, 1), depth--;
                continue;
            }
            
            if (depth - zone->tree[PAGE_DOWN(i, 2)] > needed_depth) {
                i = PAGE_DOWN(i, 2), depth--;
                continue;
            }
            
            zone->tree[i] = PAGE_USED_NODE;
            page_sift(zone, i);
            
            size_t tree_width = (uz(1) << zone->depth);
            
            while (PAGE_DOWN(i, 1) < tree_width * 2) {
                i = PAGE_DOWN(i, 1);
            }
            
            size_t o = i + 1 - (uz(1) << zone->depth);
            return zone->region + o * PAGE_BYTES;
        }
    }
    
    return NULL;
}

void page_free(void * p) {
    page_zone_t * zone = page_chain;
    
    while (zone != NULL) {
        if (p < zone->region) {
            zone = zone->next;
            continue;
        }
        
        if (p >= zone->region + zone->n * PAGE_BYTES) {
            zone = zone->next;
            continue;
        }
        
        size_t o = (p - zone->region) / PAGE_BYTES;
        size_t i = o + (uz(1) << zone->depth) - 1;
        
        while (i >= 1) {
            if (zone->tree[i] == PAGE_USED_NODE) {
                break;
            }
            
            i = PAGE_UP(i);
        }
        
        zone->tree[i] = PAGE_FREE_NODE;
        page_sift(zone, i);
        
        break;
    }
}

// === inner functions ===

long page_needed_depth(size_t n) {
    long d = 0;
    
    while (n >= 2) {
        n = (n + 1) / 2;
        d++;
    }
    
    return d;
}

void page_sift(page_zone_t * zone, size_t i) {
    unsigned char u, v, w;
    
    while (i >= 1) {
        i = PAGE_UP(i);
        
        u = zone->tree[PAGE_DOWN(i, 1)];
        v = zone->tree[PAGE_DOWN(i, 2)];
        w = macro_min(u, v) + 1;
        
        if (u == v) {
            if (u == PAGE_FREE_NODE || u == PAGE_USED_NODE) {
                w = u;
            }
        }
        
        if (zone->tree[i] == w) {
            break;
        }
        
        zone->tree[i] = w;
    }
}
