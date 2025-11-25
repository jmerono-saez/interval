ENTRY(pc_i586_multiboot2_main)

SECTIONS {
    . = 0x00100000;
    
    pc_i586_left = .;
    
    .text : {
        *(.multiboot2)
        *(.text)
        *(.rodata)
    }
    
    . = ALIGN(0x1000);
    
    .data : {
        *(.data)
    }
    
    . = ALIGN(0x1000);
    
    .zero : {
        *(.bss)
        
        . = ALIGN(0x1000);
        
        pc_i586_zero = .;
        
        . = . + 0x2000;
        
        pc_i586_sp = .;
    }
    
    . = ALIGN(0x1000);
    
    pc_i586_right = .;
}
