#include <interval/lw-efr32mg24/vectors.h>
#include <interval/lw-efr32mg24/main.h>

extern const void lw_sp;

// === globals ===

[[gnu::section(".vectors")]]
const lw_vector_t lw_vectors[16 + 76] = {
    {.stack_head = (void *)(&(lw_sp))},
    {.method     = lw_main},
};
