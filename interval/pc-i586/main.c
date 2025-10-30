#include <interval/pc-i586/main.h>

#include <interval/kernel/main.h>
#include <interval/pc-i586/multiboot2.h>

[[gnu::section(".multiboot2")]]
const unsigned long header[] = {
    0xE85250D6,
    0x00000000,
    0x0000003C,
    
    0 - (0xE85250D6 + 0x00000000 + 0x0000003C),
    
    0x00000003,
    0x00000010,
    
    (unsigned long)(&(pc_i586_main)),
    
    0x00000000, // padding
    
    0x00000002,
    0x00000018,
    
    (unsigned long)(&(header)),
    
    0xFFFFFFFF,
    0x00200000,
    0x00000000,
    0x00000000,
    
    0x00000000,
    0x00000008,
};

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
void pc_i586_main(void) {
    const boot_params_t params = (boot_params_t) {
        .region_list = NULL,
        .region_n = 0,
        
        .putc = putc,
    };
    
    main(&(params));
}
