#include <interval/watch-armv8-m/main.h>

#include <interval/kernel/main.h>
#include <interval/kernel/page.h>
#include <interval/operations.h>
#include <interval/watch-armv8-m/clocks.h>

extern const void watch_armv8_m_data_left;
extern const void watch_armv8_m_data_right;

extern const void watch_armv8_m_data_flash;

extern const void watch_armv8_m_zero_left;
extern const void watch_armv8_m_zero_right;

void watch_armv8_m_main(void) {
    void * data_left  = (void *)(&(watch_armv8_m_data_left));
    void * data_right = (void *)(&(watch_armv8_m_data_right));
    
    void * data_flash = (void *)(&(watch_armv8_m_data_flash));
    
    copy(data_left, data_flash, data_right - data_left);
    
    void * zero_left  = (void *)(&(watch_armv8_m_zero_left));
    void * zero_right = (void *)(&(watch_armv8_m_zero_right));
    
    page_insert_zone(zero_left, (zero_right - zero_left) / PAGE_BYTES);
    
    mg24_clocks_init();
    
    main();
}
