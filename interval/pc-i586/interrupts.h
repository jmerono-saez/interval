#ifndef __INTERVAL_PC_I586_INTERRUPTS_H__
#define __INTERVAL_PC_I586_INTERRUPTS_H__

#include <stdint.h>

// === types ===

typedef struct pc_i586_iframe_t pc_i586_iframe_t;

struct [[gnu::packed]] pc_i586_iframe_t {
    uint32_t di;
    uint32_t si;
    uint32_t bp;
    uint32_t sp;
    uint32_t bx;
    uint32_t dx;
    uint32_t cx;
    uint32_t ax;
    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
};

// === globals ===

extern void(* pc_i586_ints_handle_list[48])(pc_i586_iframe_t *);

// === functions ===

void pc_i586_ints_enable(void);

#endif
