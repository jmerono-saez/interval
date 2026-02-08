#include <interval/watch-armv8-m/vectors.h>

#include <interval/watch-armv8-m/main.h>

extern const void watch_armv8_m_sp;

// === globals ===

[[gnu::section(".vectors")]]
const armv8_m_vector_t vectors[16 + 76] = {
    {.stack_head = (void *)(&(watch_armv8_m_sp))},
    {.method     = watch_armv8_m_main},
};
