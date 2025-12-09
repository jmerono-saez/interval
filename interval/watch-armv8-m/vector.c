#include <interval/watch-armv8-m/vector.h>

#include <interval/watch-armv8-m/main.h>

extern const void watch_armv8_m_sp;

[[gnu::section(".vector")]]
const armv8_m_vector_t vector_list[16 + 76] = {
    {.stack_head = (void *)(&(watch_armv8_m_sp))},
    {.handle     = watch_armv8_m_main},
};
