#include <interval/watch-armv8-m/entrypoint.h>

#include <interval/kernel/page.h>
#include <interval/operations.h>

#include <interval/io.h>

#include <interval/kernel/entrypoint.h>

extern const void watch_armv8_m_data_left;
extern const void watch_armv8_m_data_right;

extern const void watch_armv8_m_data_flash;

extern const void watch_armv8_m_zero_left;
extern const void watch_armv8_m_zero_right;

bool do_sleep = true;

static stream_t kernel_stream = (stream_t) {
    .data = NULL,
    
    .write_fn = NULL,
    .read_fn = NULL,
    
    .is_empty_fn = NULL,
};

void watch_armv8_m_entrypoint(void) {
    void * data_left  = (void *)(&(watch_armv8_m_data_left));
    void * data_right = (void *)(&(watch_armv8_m_data_right));
    
    void * data_flash = (void *)(&(watch_armv8_m_data_flash));
    
    move(data_left, data_flash, data_right - data_left);
    
    while (do_sleep);
    
    void * zero_left  = (void *)(&(watch_armv8_m_zero_left));
    void * zero_right = (void *)(&(watch_armv8_m_zero_right));
    
    pool_store_zone(&(page_pool), zero_left, (zero_right - zero_left) / PAGE_BYTES);
    
    io_init(&(kernel_stream));
    
    entrypoint();
}
