#ifndef __INTERVAL_PC_I586_MULTIBOOT2_H__
#define __INTERVAL_PC_I586_MULTIBOOT2_H__

typedef struct multiboot2_header_t multiboot2_header_t;

struct multiboot2_header_t {
    unsigned long magic;
    unsigned long platform;
    unsigned long size;
    unsigned long checksum;
};

#endif
