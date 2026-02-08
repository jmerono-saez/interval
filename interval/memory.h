#ifndef __INTERVAL_MEMORY_H__
#define __INTERVAL_MEMORY_H__

#include <interval/list.h>

// === constants ===

#define BYTES_IN_UNIT 32
#define EARLY_BUMP_UNITS 12

// === macros ===

#define round_up_units(bytes) (((long)(bytes) + BYTES_IN_UNIT - 1) / BYTES_IN_UNIT)
#define round_down_units(bytes) ((long)(bytes) / BYTES_IN_UNIT)

// === globals ===

extern list_t memory_pools;

// === functions ===

void memory_init(void);
void memory_store(void * left, void * right);

void * alloc(long bytes);
void free(void * pt);

#endif
