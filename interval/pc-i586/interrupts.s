.global pc_i586_ints_handle_list

.global pc_i586_ints_enable

.section .zero

pc_i586_ints_handle_list:
    .fill 64, 4, 0x00000000

.section .text

pc_i586_ints_enable:
    mov $0xff, %al
    out %al, $0x21
    mov $0xff, %al
    out %al, $0xa1
    
    lidt ints_descriptor
    sti
    
    mov $0x11, %al
    out %al, $0x20
    mov $0x11, %al
    out %al, $0xa0
    
    mov $0x20, %al
    out %al, $0x21
    mov $0x28, %al
    out %al, $0xa1
    mov $0x04, %al
    out %al, $0x21
    mov $0x02, %al
    out %al, $0xa1
    mov $0x01, %al
    out %al, $0x21
    mov $0x01, %al
    out %al, $0xa1
    mov $0x00, %al
    out %al, $0x21
    mov $0x00, %al
    out %al, $0xa1
    
    ret

handle_trap_common:
    pusha
    
    mov 0x20(%esp), %eax
    mov pc_i586_ints_handle_list(,%eax,4), %edx
    
    test %edx, %edx
    jz handle_trap_common.skip
    
    push %esp
    call %edx
    add $0x04, %esp
    
handle_trap_common.skip:
    popa
    
    add $0x04, %esp
    iret

handle_pic0_common:
    pusha
    
    mov 0x20(%esp), %eax
    mov pc_i586_ints_handle_list(,%eax,4), %edx
    
    test %edx, %edx
    jz handle_pic0_common.skip
    
    push %esp
    call %edx
    add $0x04, %esp
    
handle_pic0_common.skip:
    movb $0x20, %al
    outb %al, $0x20
    
    popa
    
    add $0x04, %esp
    iret

handle_pic1_common:
    pusha
    
    mov 0x20(%esp), %eax
    mov pc_i586_ints_handle_list(,%eax,4), %edx
    
    test %edx, %edx
    jz handle_pic1_common.skip
    
    push %esp
    call %edx
    add $0x04, %esp
    
handle_pic1_common.skip:
    movb $0x20, %al
    outb %al, $0x20
    movb $0x20, %al
    outb %al, $0xa0
    
    popa
    
    add $0x04, %esp
    iret

.section .interrupts

handle_list:
handle_trap_00:
    push $0x00
    jmp handle_trap_common
handle_trap_01:
    push $0x01
    jmp handle_trap_common
handle_trap_02:
    push $0x02
    jmp handle_trap_common
handle_trap_03:
    push $0x03
    jmp handle_trap_common
handle_trap_04:
    push $0x04
    jmp handle_trap_common
handle_trap_05:
    push $0x05
    jmp handle_trap_common
handle_trap_06:
    push $0x06
    jmp handle_trap_common
handle_trap_07:
    push $0x07
    jmp handle_trap_common
handle_trap_08:
    add $0x04, %esp
    push $0x08
    jmp handle_trap_common
handle_trap_09:
    push $0x09
    jmp handle_trap_common
handle_trap_0a:
    add $0x04, %esp
    push $0x0a
    jmp handle_trap_common
handle_trap_0b:
    add $0x04, %esp
    push $0x0b
    jmp handle_trap_common
handle_trap_0c:
    add $0x04, %esp
    push $0x0c
    jmp handle_trap_common
handle_trap_0d:
    add $0x04, %esp
    push $0x0d
    jmp handle_trap_common
handle_trap_0e:
    add $0x04, %esp
    push $0x0e
    jmp handle_trap_common
handle_trap_0f:
    push $0x0f
    jmp handle_trap_common
handle_trap_10:
    push $0x10
    jmp handle_trap_common
handle_trap_11:
    add $0x04, %esp
    push $0x11
    jmp handle_trap_common
handle_trap_12:
    push $0x12
    jmp handle_trap_common
handle_trap_13:
    push $0x13
    jmp handle_trap_common
handle_trap_14:
    push $0x14
    jmp handle_trap_common
handle_trap_15:
    add $0x04, %esp
    push $0x15
    jmp handle_trap_common
handle_trap_16:
    push $0x16
    jmp handle_trap_common
handle_trap_17:
    push $0x17
    jmp handle_trap_common
handle_trap_18:
    push $0x18
    jmp handle_trap_common
handle_trap_19:
    push $0x19
    jmp handle_trap_common
handle_trap_1a:
    push $0x1a
    jmp handle_trap_common
handle_trap_1b:
    push $0x1b
    jmp handle_trap_common
handle_trap_1c:
    push $0x1c
    jmp handle_trap_common
handle_trap_1d:
    add $0x04, %esp
    push $0x1d
    jmp handle_trap_common
handle_trap_1e:
    add $0x04, %esp
    push $0x1e
    jmp handle_trap_common
handle_trap_1f:
    push $0x1f
    jmp handle_trap_common

handle_pic0_20:
    push $0x20
    jmp handle_pic0_common

handle_pic0_21:
    push $0x21
    jmp handle_pic0_common

handle_pic0_22:
    push $0x22
    jmp handle_pic0_common

handle_pic0_23:
    push $0x23
    jmp handle_pic0_common

handle_pic0_24:
    push $0x24
    jmp handle_pic0_common

handle_pic0_25:
    push $0x25
    jmp handle_pic0_common

handle_pic0_26:
    push $0x26
    jmp handle_pic0_common

handle_pic0_27:
    push $0x27
    jmp handle_pic0_common

handle_pic1_28:
    push $0x28
    jmp handle_pic1_common

handle_pic1_29:
    push $0x29
    jmp handle_pic1_common

handle_pic1_2a:
    push $0x2a
    jmp handle_pic1_common

handle_pic1_2b:
    push $0x2b
    jmp handle_pic1_common

handle_pic1_2c:
    push $0x2c
    jmp handle_pic1_common

handle_pic1_2d:
    push $0x2d
    jmp handle_pic1_common

handle_pic1_2e:
    push $0x2e
    jmp handle_pic1_common

handle_pic1_2f:
    push $0x2f
    jmp handle_pic1_common

.section .rodata

ints_descriptor:
    .word (ints_table_right - ints_table_left)
    .long ints_table

ints_table:
ints_table_left:
    .word 0xffff & (handle_trap_00 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_00 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_01 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_01 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_02 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_02 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_03 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_03 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_04 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_04 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_05 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_05 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_06 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_06 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_07 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_07 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_08 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_08 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_09 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_09 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0a - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0a - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0b - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0b - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0c - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0c - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0d - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0d - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0e - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0e - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_0f - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_0f - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_10 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_10 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_11 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_11 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_12 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_12 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_13 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_13 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_14 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_14 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_15 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_15 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_16 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_16 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_17 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_17 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_18 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_18 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_19 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_19 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1a - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1a - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1b - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1b - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1c - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1c - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1d - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1d - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1e - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1e - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_trap_1f - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8f00
    .word 0xffff & (handle_trap_1f - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_20 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_20 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_21 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_21 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_22 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_22 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_23 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_23 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_24 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_24 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_25 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_25 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_26 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_26 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic0_27 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic0_27 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_28 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_28 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_29 - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_29 - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2a - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2a - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2b - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2b - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2c - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2c - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2d - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2d - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2e - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2e - handle_list + 0x00100080) >> 16
    .word 0xffff & (handle_pic1_2f - handle_list + 0x00100080)
    .word 0x0008
    .word 0x8e00
    .word 0xffff & (handle_pic1_2f - handle_list + 0x00100080) >> 16
ints_table_right:
