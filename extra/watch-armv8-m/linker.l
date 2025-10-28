MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 0x00180000
    DATA(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00040000
}

SECTIONS {
    .text : {
        *(.vector)
        *(.text)
        *(.rodata)
    } > FLASH
    
    .data : {
        *(.data)
        *(.bss)
    } > DATA
}
