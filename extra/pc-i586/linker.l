ENTRY(pc_i586_main)

SECTIONS {
    . = 0x00200000;
    
    .text : {
        *(.multiboot2)
        *(.text)
        *(.rodata)
    }
    
    .data : {
        *(.data)
        *(.bss)
    }
}
