#include <interval/kernel/entrypoint.h>

#include <interval/kernel/page.h>
#include <interval/memory.h>

#include <interval/io.h>

void entrypoint(void) {
    memory_init(page_alloc, PAGE_BYTES);
    
    io_printf("hello from interval!\n");
    io_printf("reaching this point means a lot of things have gone well :D.\n");
    
    while (true);
}
