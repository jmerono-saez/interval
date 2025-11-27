#include <interval/kernel/main.h>

#include <interval/kernel/heap.h>
#include <interval/kernel/logger.h>

[[noreturn]]
void main(void) {
    // main() needs to have memory and early logging set up, the rest
    // can we done afterwards using modules.
    
    logger_print("hello from %s()!\n", __func__);
    
    heap_init();
    
    for (long i = 0; i < 10; i++) {
        void * p = heap_alloc(i * 50 + 1);
        
        logger_print("allocated %z bytes, got %z\n", i * 40 + 1, p);
    }
    
    for (long i = 0; i < 10; i++) {
        void * p = heap_alloc(20);
        heap_free(p);
        
        logger_print("allocated and freed 20 bytes, got %z\n", p);
    }
    
    // heap_alloc();
    
    // time_update();
    // time_tick();
    
    // stream_write();
    // stream_read();
    
    // thread_switch();
    
    while (true);
}
