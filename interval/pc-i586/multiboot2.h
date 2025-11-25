#ifndef __INTERVAL_PC_I586_MULTIBOOT2_H__
#define __INTERVAL_PC_I586_MULTIBOOT2_H__

#include <stdint.h>

// === constants ===

enum : uint32_t {
    MULTIBOOT2_TAIL      = 0x00,
    MULTIBOOT2_ZONE_LIST = 0x06,
};

enum : uint32_t {
    MULTIBOOT2_FREE_ZONE = 0x01,
};

#define MULTIBOOT2_ZONE_N(info) (((info)->size - 16) / 24)

// === types ===

typedef struct mbt2_header_t mbt2_header_t;

struct [[gnu::packed]] mbt2_header_t {
    uint32_t size;
    uint32_t reserved;
};

typedef struct mbt2_info_t mbt2_info_t;

struct [[gnu::packed]] mbt2_info_t {
    uint32_t type;
    uint32_t size;
    
    union {
        struct [[gnu::packed]] {
            // MULTIBOOT2_ZONE_LIST
            
            uint32_t reserved[2];
            
            struct [[gnu::packed]] {
                union {
                    uint64_t region_64;
                    void * region;
                };
                
                union {
                    uint64_t size_64;
                    size_t size;
                };
                
                uint32_t type;
                uint32_t reserved[1];
            } zone_list[/* MULTIBOOT_ZONE_N(...) */];
        };
    };
};

#endif
