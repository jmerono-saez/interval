#include <interval/kernel/main.h>

#include <interval/kernel/logger.h>

[[noreturn]]
void main(const boot_info_t * info) {
    // main() needs to have memory and early logging set up, the rest
    // can we done afterwards using modules.
    
    logger_print("hello from %s()!\n", __func__);
    
    while (true);
}
