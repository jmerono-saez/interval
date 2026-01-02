#ifndef __INTERVAL_KERNEL_PAGE_H__
#define __INTERVAL_KERNEL_PAGE_H__

#include <interval/pool.h>

// === constants ===

#ifndef PAGE_BYTES
#error "PAGE_BYTES must be defined in ninja.sh for this platform"
#endif

// === globals ===

extern pool_t page_pool;

// === functions ===

void * page_alloc(long page_count);
void page_free(void * p);

#endif
