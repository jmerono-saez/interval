#ifndef __INTERVAL_LW_EFR32MG24_VECTORS_H__
#define __INTERVAL_LW_EFR32MG24_VECTORS_H__

#include <stddef.h>

// === types ===

typedef struct lw_vector_t lw_vector_t;

struct lw_vector_t {
    union {
        void * stack_head;
        void(* method)(void);
    };
};

// === globals ===

extern const lw_vector_t lw_vectors[16 + 76];

#endif
