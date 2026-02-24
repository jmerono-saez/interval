#include <interval/kernel/thread.h>

// === globals ===

list_t threads;

// === functions ===

void thread_init(void) {
    list_init(&(threads));
}
