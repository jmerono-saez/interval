MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 0x00180000
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00040000
}

SECTIONS {
    .text : ALIGN(0x80) {
        *(.jump_table)
        
        . = ALIGN(0x80);
        
        *(.text)
        *(.rodata)
    } > FLASH
    
    .data : ALIGN(0x80) {
        watch_armv8_m_data_left = .;
        
        *(.data)
        
        . = ALIGN(0x80);
        
        watch_armv8_m_data_right = .;
    } > SRAM AT> FLASH
    
    watch_armv8_m_data_flash = LOADADDR(.data);
    
    .zero : ALIGN(0x80) {
        *(.zero)
        *(.bss)
        
        . = ALIGN(0x0400) + 0x0400;
        
        watch_armv8_m_sp = .;
        
        . = ALIGN(0x0400);
        
        watch_armv8_m_zero_left = .;
        
        . = ALIGN(0x00040000);
        
        watch_armv8_m_zero_right = .;
    } > SRAM
}
