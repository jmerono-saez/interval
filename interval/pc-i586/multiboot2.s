.global pc_i586_multiboot2_main

.extern pc_i586_zero
.extern pc_i586_sp

.extern pc_i586_main

.section .multiboot2

header:
    .long 0xE85250D6
    .long 0x00000000
    .long 0x00000030
    .long 0x17ADAEFA
    
    .long 0x00000001
    .long 0x00000018
    .long 0x00000006
    .long 0x00000008
    .long 0x0000000E
    .long 0x0000000F
    
    .long 0x00000000
    .long 0x00000008

.section .text

pc_i586_multiboot2_main:
    lgdt global_descriptor
    jmp $0x08, $.reload_cs
    
.reload_cs:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    
    mov $pc_i586_sp, %esp
    cld
    
    mov %ebx, %esi
    mov $pc_i586_zero, %edi
    mov (%ebx), %ecx
    rep movsb
    
    mov $pc_i586_zero, %ebx
    push %ebx
    
    call pc_i586_main

.section .rodata

global_descriptor:
    .word (global_table_right - global_table_left)
    .long global_table

global_table:
global_table_left:
    .word 0x0000
    .word 0x0000
    .word 0x0000
    .word 0x0000
    .word 0xffff
    .word 0x0000
    .word 0x9a00
    .word 0x00cf
    .word 0xffff
    .word 0x0000
    .word 0x9200
    .word 0x00cf
global_table_right:
