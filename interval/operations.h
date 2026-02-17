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

// === generic functions ===

long hash(const void * pt, long bytes);

void move(void * to, const void * from, long bytes);
bool equals(const void * pt_1, const void * pt_2, long bytes);

void swap(void * pt_1, void * pt_2, long bytes);
void sort(void * items, long item_bytes, long item_count, bool(* is_ordered)(const void *, const void *));

long length_of(const char * text);

// === text functions ===

long hash_text(const char * text);

void move_text(char * to, const char * from);
bool equals_text(const char * text_1, const char * text_2);

#endif
