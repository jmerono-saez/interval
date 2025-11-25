#include <interval/pc-i586/main.h>

#include <interval/kernel/logger.h>
#include <interval/kernel/main.h>
#include <interval/kernel/page.h>
#include <interval/macros.h>
#include <interval/pc-i586/multiboot2.h>

#include <stddef.h>

extern const void pc_i586_left;
extern const void pc_i586_right;

static void putc(char c) {
    static long offset = 0;
    
    volatile unsigned char * vga_text = (unsigned char *)(0x000B8000);
    
    if (c == '\x0A') {
        offset = ((offset / 160) + 1) * 160;
    } else {
        vga_text[offset++] = c;
        vga_text[offset++] = 0x0F;
    }
}

[[noreturn]]
void pc_i586_main(void * mbt2) {
    void * load_left  = (void *)(&(pc_i586_left));
    void * load_right = (void *)(&(pc_i586_right));
    
    mbt2_header_t * header = mbt2;
    
    mbt2 += sizeof(mbt2_header_t);
    align(mbt2, 8);
    
    while (mbt2 < (void *)(header) + header->size) {
        mbt2_info_t * info = mbt2;
        
        mbt2 += info->size;
        align(mbt2, 8);
        
        if (info->type == MULTIBOOT2_TAIL) {
            break;
        }
        
        if (info->type != MULTIBOOT2_ZONE_LIST) {
            continue;
        }
        
        size_t zone_n = MULTIBOOT2_ZONE_N(info);
        
        for (size_t i = 0; i < zone_n; i++) {
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
    
    logger_early_init(putc);
    
    main();
}
