#ifndef __INTERVAL_KERNEL_MAIN_H__
#define __INTERVAL_KERNEL_MAIN_H__

#include <stddef.h>

// === types ===

typedef struct boot_region_t boot_region_t;

struct boot_region_t {
    void * region;
    size_t size;
    
    bool is_free;
};

typedef struct boot_params_t boot_params_t;

struct boot_params_t {
    const boot_region_t * region_list;
    size_t region_n;
    
    void(* putc)(char c);
};

// === functions ===

[[noreturn]]
void main(const boot_params_t * params);

#endif
