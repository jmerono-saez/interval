#include <interval/pc-i586/main.h>

#include <interval/kernel/main.h>
#include <interval/pc-i586/multiboot2.h>

/*
[[gnu::section(".multiboot2")]]
const multiboot2_header_t header = {
    .magic = 0xE85250D6,
    .platform = 0x00000000,
    .size = sizeof(multiboot2_header_t),
    .checksum = 0 - (0xE85250D6 + sizeof(multiboot2_header_t)),
};
*/

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

static const char * text = "interval r01 :D";

volatile unsigned char * vga_text = (unsigned char *)(0x000B8000);

[[noreturn]]
void pc_i586_main(void) {
    while (*(text)) {
        *(vga_text++) = *(text++);
        *(vga_text++) = 0x03;
    }
    
    main();
}
