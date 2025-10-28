#include <interval/watch-armv8-m/handle.h>
#include <interval/watch-armv8-m/vector.h>

[[gnu::section(".vector")]]
const armv8_m_vector_t vector_list[16 + 76] = {
    {.stack_head = (void *)(0x20040000)},
    {.handle     = watch_armv8_m_reset_handle},
};
