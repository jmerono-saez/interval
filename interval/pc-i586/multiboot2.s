.global pc_i586_multiboot2_main

.extern pc_i586_zero
.extern pc_i586_sp

.extern pc_i586_main

.section .multiboot2

header:
    .long 0xE85250D6
    .long 0x00000000
    .long 0x00000028
    .long 0x17ADAF02
    
    .long 0x00000001
    .long 0x00000010
    .long 0x00000004
    .long 0x00000006
    
    .long 0x00000000
    .long 0x00000008

.section .text

pc_i586_multiboot2_main:
    mov $pc_i586_sp, %esp
    cld
    
    mov %ebx, %esi
    mov $pc_i586_zero, %edi
    mov (%ebx), %ecx
    rep movsb
    
    mov $pc_i586_zero, %ebx
    push %ebx
    
    call pc_i586_main
