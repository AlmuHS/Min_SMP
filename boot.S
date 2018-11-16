
#define MULTIBOOT_MAGIC 0x1badb002
#define MULTIBOOT_FLAGS 0x0
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)


#define STACK_SIZE (4096 * 2)


    .section .boot, "awx"


    .align 0x10

    .long MULTIBOOT_MAGIC
    .long MULTIBOOT_FLAGS
    .long MULTIBOOT_CHECKSUM


    .text
    .globl _start
_start:
    /* loading idt and gdt */
    lidt idt_descr
    lgdt gdt_descr

    ljmp $0x8, $1f
1:
    mov $0x10, %eax
    movw %ax, %ds
    movw %ax, %es

    movw %ax, %ss
    movl $(stack + STACK_SIZE), %esp


    /* first argument: multiboot */
    push %ebx
    call main


    cli
1:
    hlt
    jmp 1b

    .section .rodata
    .align 0x10

    .globl idt_descr
idt_descr:
    .word 0
    .long 0

    .align 0x10
gdt_descr:
    .word 0x8*5 - 1
    .long gdt

    .align 0x10
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
    /* rm CS = 0x18 */
    .word 0xffff
    .word 0
    .byte 0
    .byte 0x9a
    .byte 0x8f
    .byte 0
    /* rm DS = 0x20 */
    .word 0xffff
    .word 0
    .byte 0
    .byte 0x92
    .byte 0x8f


    .bss
    .p2align 4
    .comm stack, STACK_SIZE


