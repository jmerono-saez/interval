#include <interval/kernel/main.h>

#include <interval/kernel/heap.h>
#include <interval/kernel/logger.h>
#include <interval/kernel/page.h>

[[noreturn]]
void main(void) {
    logger_early_init();
    logger_print("hello from %s()!\n", __func__);
    
    heap_init(page_alloc, page_free);
    
    // time_update();
    // time_tick();
    
    // stream_write();
    // stream_read();
    
    // thread_switch();
    
    while (true);
}
