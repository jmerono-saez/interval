#ifndef __INTERVAL_KERNEL_PAGE_H__
#define __INTERVAL_KERNEL_PAGE_H__

#include <stddef.h>

// === constants ===

#ifndef PAGE_BYTES
#error "PAGE_BYTES is not defined"
#endif

#define P_UP(i)      ((i - 1) / 2)
#define P_DOWN(i, j) ((i * 2) + j)

#define P_FREE_NODE (unsigned char)(0x00)
#define P_USED_NODE (unsigned char)(0xFF)

// === globals ===

extern void * p_page_region;
extern size_t p_page_n;

extern unsigned char * p_tree;
extern unsigned char p_tree_d;

// === functions ===

void p_init(void * region, size_t n, unsigned char * tree);
void p_mark(void * p, size_t n);

void * p_alloc(size_t n);
void p_free(void * p);

// === inner functions ===

unsigned char p_depth(size_t i);
size_t p_index(size_t i);

size_t p_width(size_t i);

void * p_node_to_region(size_t i);
size_t p_region_to_node(void * p);

void p_sift(size_t i);

#endif
