#ifndef __INTERVAL_WATCH_ARMV8_M_VECTOR_H__
#define __INTERVAL_WATCH_ARMV8_M_VECTOR_H__

typedef union armv8_m_vector_t armv8_m_vector_t;

union armv8_m_vector_t {
    void * stack_head;
    void(* handle)(void);
};

#endif
