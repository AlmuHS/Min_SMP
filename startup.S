
#define M(addr) (addr - _start + 0x7000)


    .text
    .globl _start
    .code16
_cpuboot:
cpuboot:

    cli
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0x7000, %sp

    ljmp $0x0, $M(1f)
1:

    lgdt M(gdt_descr)
    
    mov %cr0, %eax
    or $0x1, %eax
    mov %eax, %cr0
    
    
    ljmp $0x8, $M(1f)
1:
    .code32

    mov $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0x7000, %esp
    






1:
    hlt
    jmp 1b



gdt_descr:
    .short 0x8*3 - 1
    .long M(gdt)


gdt:
    /* 0 */
    .quad 0
    /* boot CS = 0x8 */
    .word 0xffff
    .word 0x0000
    .byte 0x00
    .byte 0x9a
    .byte 0xcf
    .byte 0x00
    /* boot DS = 0x10 */
    .word 0xffff
    .word 0x0000
    .byte 0x00
    .byte 0x92
    .byte 0xcf
    .byte 0x00

    





    . = 0x1fe
    .word 0xaa55

_cpubootend:
cpubootend:
