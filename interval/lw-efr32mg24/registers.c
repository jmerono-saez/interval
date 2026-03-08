#include <interval/lw-efr32mg24/registers.h>
#include <stdint.h>

// === functions ===

void mg24_write(void * base, long offset, unsigned long ul) {
    ((uint32_t *)(base))[offset >> 2] = ul;
}

void mg24_raise(void * base, long offset, unsigned long ul) {
    mg24_write(base, offset | 0x1000, ul);
}

void mg24_lower(void * base, long offset, unsigned long ul) {
    mg24_write(base, offset | 0x2000, ul);
}

void mg24_flip(void * base, long offset, unsigned long ul) {
    mg24_write(base, offset | 0x3000, ul);
}

unsigned long mg24_read(void * base, long offset) {
    return ((uint32_t *)(base))[offset >> 2];
}
