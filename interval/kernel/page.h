#ifndef __INTERVAL_KERNEL_PAGE_H__
#define __INTERVAL_KERNEL_PAGE_H__

#include <stddef.h>

// === constants ===

#define PAGE_UP(i)      ((i - 1) / 2)
#define PAGE_DOWN(i, j) ((i * 2) + j)

#define PAGE_FREE_NODE (unsigned char)(0x00)
#define PAGE_USED_NODE (unsigned char)(0xFF)

// === types ===

typedef struct page_zone_t page_zone_t;

struct page_zone_t {
    void * region;
    size_t n;
    
    page_zone_t * next;
    
    long depth;
    
    unsigned char tree[/* (2 << depth) */];
};

// === globals ===

extern page_zone_t * page_chain;

// === functions ===

void page_insert_zone(void * region, size_t n);
void page_mark(page_zone_t * zone, void * p, size_t n);

void * page_alloc(size_t n);
void page_free(void * p);

// === inner functions ===

long page_needed_depth(size_t n);
void page_sift(page_zone_t * zone, size_t i);

#endif
