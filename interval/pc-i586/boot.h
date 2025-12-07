#ifndef __INTERVAL_PC_I586_BOOT_H__
#define __INTERVAL_PC_I586_BOOT_H__

#include <stdint.h>

// === constants ===

#define RSDP_SIGN ((uint64_t)(0x2052545020445352))

#define FADT_SIGN ((uint32_t)(0x50434146))
#define MADT_SIGN ((uint32_t)(0x43495041))

// === types ===

typedef struct rsdp_t rsdp_t;

struct [[gnu::packed]] rsdp_t {
    uint64_t sign;
    unsigned char checksum;
    char oem_id[6];
    unsigned char revision;
    
    union {
        uint32_t p_32;
        void * p;
    } v1;
    
    uint32_t size;
    
    union {
        uint64_t p_64;
        void * p;
    } v2;
    
    uint32_t reserved[1];
};

typedef struct dt_header_t dt_header_t;

struct [[gnu::packed]] dt_header_t {
    uint32_t sign;
    uint32_t size;
    
    unsigned char revision;
    unsigned char checksum;
    char oem_id[6];
    char oem_table_id[8];
    
    uint32_t reserved[3];
};

typedef struct rsdt_t rsdt_t;

struct [[gnu::packed]] rsdt_t {
    dt_header_t header;
    
    union {
        union {
            uint32_t p_32;
            void * p;
        } v1[0];
        
        union {
            uint64_t p_64;
            void * p;
        } v2[0];
    };
};

typedef struct fadt_t fadt_t;

struct [[gnu::packed]] fadt_t {
    dt_header_t header;
};

typedef struct madt_t madt_t;

struct [[gnu::packed]] madt_t {
    dt_header_t header;
    
    uint32_t apic_32;
    uint32_t flags;
};

// === functions ===

rsdp_t * dp_find_in_memory(void * left, void * right);
void * dt_search(const rsdp_t * rsdp, bool is_v2, uint32_t sign);

#endif
