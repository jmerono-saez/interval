#include <interval/pc-i586/main.h>

#include <interval/kernel/main.h>
#include <interval/kernel/page.h>
#include <interval/macros.h>
#include <interval/values.h>
#include <interval/pc-i586/boot.h>
#include <interval/pc-i586/interrupts.h>
#include <interval/pc-i586/multiboot2.h>

#include <stddef.h>

extern const void pc_i586_left;
extern const void pc_i586_right;

static void putc(char c) {
    static long offset = 0;
    
    if (offset >= 4000) {
        return;
    }
    
    volatile unsigned char * vga_text = (unsigned char *)(0x000B8000);
    
    if (c == '\x0A') {
        offset = ((offset / 160) + 1) * 160;
    } else {
        vga_text[offset++] = c;
        vga_text[offset++] = 0x0F;
    }
}

static void load_zone_list(mbt2_info_t * info) {
    void * load_left  = (void *)(&(pc_i586_left));
    void * load_right = (void *)(&(pc_i586_right));
    
    size_t zone_n = MULTIBOOT2_ZONE_N(info);
    
    for (size_t i = 0; i < zone_n; i++) {
        if (info->zone_list[i].type != MULTIBOOT2_FREE_ZONE) {
            continue;
        }
        
        void * region = info->zone_list[i].region;
        size_t size = info->zone_list[i].size;
        
        if (region < load_left) {
            void * region_left = region;
            size_t size_left = macro_min(size, load_left - region);
            
            page_insert_zone(region_left, size_left / PAGE_BYTES);
        }
        
        if (load_right < region + size) {
            void * region_right = macro_max(region, load_right);
            size_t size_right = region + size - region_right;
            
            page_insert_zone(region_right, size_right / PAGE_BYTES);
        }
    }
}

[[noreturn]]
void pc_i586_main(void * mbt2) {
    mbt2_header_t * header = mbt2;
    
    mbt2_info_t * zone_info = NULL;
    
    rsdp_t * rsdp = NULL;
    bool rsdp_is_v2 = false;
    
    mbt2 += sizeof(mbt2_header_t);
    align(mbt2, 8);
    
    while (mbt2 < (void *)(header) + header->size) {
        mbt2_info_t * info = mbt2;
        
        mbt2 += info->size;
        align(mbt2, 8);
        
        if (info->type == MULTIBOOT2_TAIL) {
            break;
        }
        
        if (info->type == MULTIBOOT2_ZONE_LIST) {
            load_zone_list(info);
        }
        
        if (info->type == MULTIBOOT2_RSDP_V1) {
            if (rsdp_is_v2) {
                continue;
            }
            
            rsdp = &(info->rsdp);
            rsdp_is_v2 = false;
        }
        
        if (info->type == MULTIBOOT2_RSDP_V2) {
            rsdp = &(info->rsdp);
            rsdp_is_v2 = true;
        }
    }
    
    if (rsdp == NULL) {
        void * bios_left  = (void *)(0x000E0000);
        void * bios_right = (void *)(0x00100000);
        
        rsdp = dp_find_in_memory(bios_left, bios_right);
        rsdp_is_v2 = (rsdp->revision >= 2);
    }
    
    fadt_t * fadt = dt_search(rsdp, rsdp_is_v2, FADT_SIGN);
    madt_t * madt = dt_search(rsdp, rsdp_is_v2, MADT_SIGN);
    
    // pc_i586_ints_enable();
    
    main();
}
