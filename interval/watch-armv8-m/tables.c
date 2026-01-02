#include <interval/watch-armv8-m/tables.h>

#include <interval/watch-armv8-m/entrypoint.h>

extern const void watch_armv8_m_sp;

[[gnu::section(".jump_table")]]
const armv8_m_jump_t jump_table[16 + 76] = {
    {.stack_head = (void *)(&(watch_armv8_m_sp))},
    {.fn         = watch_armv8_m_entrypoint},
};
