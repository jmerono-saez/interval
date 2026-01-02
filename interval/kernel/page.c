#include <interval/kernel/page.h>

pool_t page_pool = pool_null(PAGE_BYTES);

void * page_alloc(long page_count) {
    return pool_alloc(&(page_pool), page_count);
}

void page_free(void * p) {
    pool_free(&(page_pool), p);
}
