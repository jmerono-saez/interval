#ifndef __INTERVAL_WATCH_ARMV8_M_VECTORS_H__
#define __INTERVAL_WATCH_ARMV8_M_VECTORS_H__

#include <stddef.h>

// === types ===

typedef struct armv8_m_vector_t armv8_m_vector_t;

typedef void armv8_m_method_t(void);

struct armv8_m_vector_t {
    union {
        void * stack_head;
        armv8_m_method_t * method;
    };
};

// === globals ===

extern const armv8_m_vector_t armv8_m_vectors[16 + 76];

#endif
