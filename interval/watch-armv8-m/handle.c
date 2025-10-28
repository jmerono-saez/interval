#include <interval/kernel/main.h>
#include <interval/watch-armv8-m/handle.h>

void watch_armv8_m_dummy_handle(void) {
    while (true);
}

void watch_armv8_m_reset_handle(void) {
    main();
}
