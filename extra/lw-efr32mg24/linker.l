MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 0x00180000
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00040000
}

SECTIONS {
    .text : ALIGN(0x80) {
        *(.vector_table)
        
        . = ALIGN(0x80);
        
        *(.text)
        *(.rodata)
    } > FLASH
    
    .data : ALIGN(0x80) {
        lw_data_left = .;
        
        *(.data)
        
        . = ALIGN(0x80);
        
        lw_data_right = .;
    } > SRAM AT> FLASH
    
    lw_data_flash = LOADADDR(.data);
    
    .zero : ALIGN(0x80) {
        *(.zero)
        *(.bss)
        
        . = ALIGN(0x0400) + 0x0400;
        
        lw_sp = .;
        
        . = ALIGN(0x0400);
        
        lw_zero_left = .;
        
        . = ALIGN(0x00040000);
        
        lw_zero_right = .;
    } > SRAM
}
