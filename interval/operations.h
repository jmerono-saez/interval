#ifndef __INTERVAL_OPERATIONS_H__
#define __INTERVAL_OPERATIONS_H__

// === constants ===

#define HASH_MULTIPLY (\
    (1ul << (sizeof(long) * 8 - 4)) |\
    (1ul << (sizeof(long) * 8 - 9)) |\
    (1ul << (sizeof(long) * 5 - 1)) |\
    (1ul << (sizeof(long) * 3 - 2)) |\
    (1ul << (sizeof(long) * 2 - 1)) |\
0xF9ul)

// === types ===

typedef bool is_ordered_method_t(const void * pt_1, const void * pt_2);

// === functions ===

long hash(const void * pt, long bytes);

void move(void * to, const void * from, long bytes);
void swap(void * pt_1, void * pt_2, long bytes);

bool equals(const void * pt_1, const void * pt_2, long bytes);

void sort(void * items, long item_bytes, long item_count, is_ordered_method_t * is_ordered);

long length_of(const char * text);

#endif
