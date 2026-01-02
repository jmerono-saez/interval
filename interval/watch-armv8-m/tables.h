#ifndef __INTERVAL_WATCH_ARMV8_M_TABLES_H__
#define __INTERVAL_WATCH_ARMV8_M_TABLES_H__

// === types ===

typedef struct armv8_m_jump_t armv8_m_jump_t;

typedef void armv8_m_fn_t(void);

struct armv8_m_jump_t {
    union {
        void * stack_head;
        armv8_m_fn_t * fn;
    };
};

// === globals ===

[[gnu::section(".jump_table")]]
extern const armv8_m_jump_t armv8_m_jump_table[16 + 76];

#endif
