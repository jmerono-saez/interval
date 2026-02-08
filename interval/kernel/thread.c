#include <interval/kernel/thread.h>

// === globals ===

list_t threads;
iterator_t * thread_iterator;

// === functions ===

void thread_init(void) {
    list_init(&(threads));
    thread_iterator = threads.begin;
}
